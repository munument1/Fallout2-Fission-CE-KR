#include "legacy_gdi_font.h"

#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

#if defined(_WIN32)
#include <windows.h>
#endif

#include "color.h"
#include "platform_compat.h"
#include "settings.h"
#include "text_font.h"

namespace fallout {

#if defined(_WIN32)

struct GdiFontConfig {
    std::string face;
    int size;
    int weight;
    int lineHeight;
    DWORD quality;
};

struct GdiFontState {
    HDC dc = nullptr;
    HBITMAP bitmap = nullptr;
    HGDIOBJ previousBitmap = nullptr;
    HFONT textFont = nullptr;
    HFONT buttonFont = nullptr;
    HFONT titleFont = nullptr;
    HGDIOBJ previousFont = nullptr;
    unsigned int* pixels = nullptr;
    int bitmapWidth = 0;
    int bitmapHeight = 0;
    int currentFont = -1;
    std::vector<std::wstring> privateFontFiles;
};

static GdiFontState gGdi;

static int legacyCodepage()
{
    return settings.font.legacy_codepage > 0 ? settings.font.legacy_codepage : 949;
}

static GdiFontConfig getGdiFontConfig(int font)
{
    if (font == 104) {
        return {
            settings.font.gdi_title_face,
            std::max(1, settings.font.gdi_title_size),
            std::clamp(settings.font.gdi_title_weight, 0, 1000),
            std::max(1, settings.font.gdi_title_line_height),
            NONANTIALIASED_QUALITY,
        };
    }

    if (font == 103 || font == 102) {
        return {
            settings.font.gdi_button_face,
            std::max(1, settings.font.gdi_button_size),
            std::clamp(settings.font.gdi_button_weight, 0, 1000),
            std::max(1, settings.font.gdi_button_line_height),
            NONANTIALIASED_QUALITY,
        };
    }

    return {
        settings.font.gdi_text_face,
        std::max(1, settings.font.gdi_text_size),
        std::clamp(settings.font.gdi_text_weight, 0, 1000),
        std::max(1, settings.font.gdi_text_line_height),
        NONANTIALIASED_QUALITY,
    };
}

static std::wstring decodeConfigString(const std::string& value)
{
    if (value.empty()) {
        return L"Dotum";
    }

    int length = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, value.c_str(), static_cast<int>(value.size()), nullptr, 0);
    UINT codepage = CP_UTF8;
    DWORD flags = MB_ERR_INVALID_CHARS;
    if (length == 0) {
        codepage = legacyCodepage();
        flags = 0;
        length = MultiByteToWideChar(codepage, flags, value.c_str(), static_cast<int>(value.size()), nullptr, 0);
    }

    if (length <= 0) {
        return L"Dotum";
    }

    std::wstring result(static_cast<size_t>(length), L'\0');
    MultiByteToWideChar(codepage, flags, value.c_str(), static_cast<int>(value.size()), result.data(), length);
    return result;
}

static std::wstring executableDirectory()
{
    std::vector<wchar_t> path(MAX_PATH);
    for (;;) {
        DWORD length = GetModuleFileNameW(nullptr, path.data(), static_cast<DWORD>(path.size()));
        if (length == 0) {
            return L".";
        }
        if (length < path.size() - 1) {
            std::wstring result(path.data(), length);
            size_t separator = result.find_last_of(L"\\/");
            return separator == std::wstring::npos ? L"." : result.substr(0, separator);
        }
        path.resize(path.size() * 2);
    }
}

static void loadBundledFonts()
{
    const std::wstring base = executableDirectory() + L"\\fonts\\";
    const wchar_t* names[] = {
        L"NanumBarunGothic.ttf",
        L"Cafe24OhsquareAir-v2.0.ttf",
    };

    for (const wchar_t* name : names) {
        std::wstring path = base + name;
        if (GetFileAttributesW(path.c_str()) != INVALID_FILE_ATTRIBUTES
            && AddFontResourceExW(path.c_str(), FR_PRIVATE, nullptr) > 0) {
            gGdi.privateFontFiles.push_back(std::move(path));
        }
    }
}

static std::wstring decodeLegacyText(const char* string)
{
    std::wstring result;
    if (string == nullptr) {
        return result;
    }

    const unsigned char* p = reinterpret_cast<const unsigned char*>(string);
    while (*p != '\0') {
        if (*p == '\r' || *p == '\n') {
            break;
        }

        if (*p < 0x20) {
            if (*p == '\t') {
                result.push_back(L' ');
            }
            p++;
            continue;
        }

        if (*p == 0x95) {
            result.push_back(L'\x2022');
            p++;
            continue;
        }

        int byteCount = 1;
        if (*p >= 0x81 && *p <= 0xFE && *(p + 1) != '\0') {
            byteCount = 2;
        }

        wchar_t wide[2] = {};
        int converted = MultiByteToWideChar(legacyCodepage(), 0, reinterpret_cast<const char*>(p), byteCount, wide, 2);
        if (converted > 0) {
            result.append(wide, wide + converted);
        } else {
            result.push_back(static_cast<wchar_t>(*p));
        }
        p += byteCount;
    }

    return result;
}

static HFONT createGdiFont(const GdiFontConfig& config)
{
    std::wstring face = decodeConfigString(config.face);
    return CreateFontW(
        -config.size,
        0,
        0,
        0,
        config.weight,
        FALSE,
        FALSE,
        FALSE,
        HANGUL_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        config.quality,
        DEFAULT_PITCH | FF_DONTCARE,
        face.c_str());
}

static bool ensureContext()
{
    if (gGdi.dc != nullptr) {
        return true;
    }

    gGdi.dc = CreateCompatibleDC(nullptr);
    if (gGdi.dc == nullptr) {
        return false;
    }

    loadBundledFonts();
    gGdi.textFont = createGdiFont(getGdiFontConfig(101));
    gGdi.buttonFont = createGdiFont(getGdiFontConfig(102));
    gGdi.titleFont = createGdiFont(getGdiFontConfig(104));
    if (gGdi.textFont == nullptr || gGdi.buttonFont == nullptr || gGdi.titleFont == nullptr) {
        legacyGdiFontsExit();
        return false;
    }

    SetBkMode(gGdi.dc, OPAQUE);
    SetBkColor(gGdi.dc, RGB(0, 0, 0));
    SetTextColor(gGdi.dc, RGB(255, 255, 255));
    return true;
}

static bool ensureBitmap(int width, int height)
{
    width = std::max(1, width);
    height = std::max(1, height);
    if (gGdi.bitmap != nullptr && width <= gGdi.bitmapWidth && height <= gGdi.bitmapHeight) {
        return true;
    }

    int newWidth = std::max(width, gGdi.bitmapWidth);
    int newHeight = std::max(height, gGdi.bitmapHeight);

    if (gGdi.bitmap != nullptr) {
        SelectObject(gGdi.dc, gGdi.previousBitmap);
        DeleteObject(gGdi.bitmap);
        gGdi.bitmap = nullptr;
        gGdi.pixels = nullptr;
    }

    BITMAPINFO bitmapInfo = {};
    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.bmiHeader.biWidth = newWidth;
    bitmapInfo.bmiHeader.biHeight = -newHeight;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;

    void* bits = nullptr;
    gGdi.bitmap = CreateDIBSection(gGdi.dc, &bitmapInfo, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (gGdi.bitmap == nullptr || bits == nullptr) {
        gGdi.bitmap = nullptr;
        return false;
    }

    gGdi.previousBitmap = SelectObject(gGdi.dc, gGdi.bitmap);
    gGdi.pixels = static_cast<unsigned int*>(bits);
    gGdi.bitmapWidth = newWidth;
    gGdi.bitmapHeight = newHeight;
    return true;
}

static HFONT fontForCurrentSelection()
{
    if (gGdi.currentFont == 104) {
        return gGdi.titleFont;
    }
    if (gGdi.currentFont == 103 || gGdi.currentFont == 102) {
        return gGdi.buttonFont;
    }
    return gGdi.textFont;
}

static bool selectCurrentFont()
{
    if (!ensureContext()) {
        return false;
    }

    HFONT font = fontForCurrentSelection();
    HGDIOBJ previous = SelectObject(gGdi.dc, font);
    if (gGdi.previousFont == nullptr) {
        gGdi.previousFont = previous;
    }
    return true;
}

static SIZE measureText(const std::wstring& text)
{
    SIZE size = {};
    if (!selectCurrentFont() || text.empty()) {
        return size;
    }

    GetTextExtentPoint32W(gGdi.dc, text.c_str(), static_cast<int>(text.size()), &size);
    return size;
}

static int gdiFontGetLineHeight()
{
    int height = getGdiFontConfig(gGdi.currentFont).lineHeight;

    // The character editor adds one pixel between skill rows. Report 10 for
    // the 11 px body preset so all 18 skills fit, while drawing the full glyph.
    if (gGdi.currentFont == 101) {
        height--;
    }

    return std::max(1, height);
}

static int gdiFontGetStringWidth(const char* string)
{
    return measureText(decodeLegacyText(string)).cx;
}

static int gdiFontGetCharacterWidth(int ch)
{
    char encoded[3] = {};
    if (ch > 0xFF) {
        encoded[0] = static_cast<char>((ch >> 8) & 0xFF);
        encoded[1] = static_cast<char>(ch & 0xFF);
    } else {
        encoded[0] = static_cast<char>(ch & 0xFF);
    }
    return gdiFontGetStringWidth(encoded);
}

static int gdiFontGetMonospacedCharacterWidth()
{
    return gdiFontGetCharacterWidth('0');
}

static int gdiFontGetMonospacedStringWidth(const char* string)
{
    return gdiFontGetMonospacedCharacterWidth() * static_cast<int>(decodeLegacyText(string).size());
}

static int gdiFontGetLetterSpacing()
{
    return 0;
}

static int gdiFontGetBufferSize(const char* string)
{
    SIZE measured = measureText(decodeLegacyText(string));
    int rasterHeight = static_cast<int>(measured.cy) + std::abs(settings.font.baseline_offset);
    return static_cast<int>(measured.cx) * std::max(gdiFontGetLineHeight(), rasterHeight);
}

static void gdiFontDrawText(unsigned char* buf, const char* string, int length, int pitch, int color)
{
    if (buf == nullptr || string == nullptr || length <= 0 || pitch <= 0) {
        return;
    }

    if ((color & FONT_SHADOW) != 0) {
        int shadowColor = (color & ~FONT_SHADOW & ~0xFF) | _colorTable[0];
        gdiFontDrawText(buf + pitch + 1, string, length, pitch, shadowColor);
        color &= ~FONT_SHADOW;
    }

    std::wstring text = decodeLegacyText(string);
    if (text.empty() || !selectCurrentFont()) {
        return;
    }

    int fit = 0;
    SIZE measured = {};
    std::vector<int> advances(text.size());
    if (!GetTextExtentExPointW(gGdi.dc, text.c_str(), static_cast<int>(text.size()), length, &fit, advances.data(), &measured) || fit <= 0) {
        return;
    }

    text.resize(static_cast<size_t>(fit));
    GetTextExtentPoint32W(gGdi.dc, text.c_str(), fit, &measured);

    int lineHeight = gdiFontGetLineHeight();
    int measuredWidth = static_cast<int>(measured.cx);
    int measuredHeight = static_cast<int>(measured.cy);
    int surfaceHeight = std::max(lineHeight, measuredHeight + std::abs(settings.font.baseline_offset));
    if (!ensureBitmap(std::max(1, measuredWidth), surfaceHeight)) {
        return;
    }

    std::memset(gGdi.pixels, 0, static_cast<size_t>(gGdi.bitmapWidth) * gGdi.bitmapHeight * sizeof(unsigned int));
    TextOutW(gGdi.dc, 0, settings.font.baseline_offset, text.c_str(), fit);
    GdiFlush();

    // Some bundled faces contain a blank bullet glyph. Preserve menu markers.
    if (text.front() == L'\x2022' || text.front() == L'\x25CF') {
        SIZE marker = {};
        GetTextExtentPoint32W(gGdi.dc, text.c_str(), 1, &marker);
        int markerWidth = std::min(static_cast<int>(marker.cx), measuredWidth);
        bool hasInk = false;
        for (int y = 0; y < surfaceHeight && !hasInk; y++) {
            for (int x = 0; x < markerWidth; x++) {
                if ((gGdi.pixels[static_cast<size_t>(y) * gGdi.bitmapWidth + x] & 0xFFFFFF) != 0) {
                    hasInk = true;
                    break;
                }
            }
        }
        if (!hasInk && markerWidth > 0) {
            int diameter = std::min({ markerWidth, surfaceHeight, std::clamp(measuredHeight / 4, 2, 5) });
            int left = (markerWidth - diameter) / 2;
            int top = std::clamp((measuredHeight - diameter) / 2 + settings.font.baseline_offset, 0, surfaceHeight - diameter);
            HGDIOBJ previousBrush = SelectObject(gGdi.dc, GetStockObject(WHITE_BRUSH));
            HGDIOBJ previousPen = SelectObject(gGdi.dc, GetStockObject(WHITE_PEN));
            Ellipse(gGdi.dc, left, top, left + diameter, top + diameter);
            SelectObject(gGdi.dc, previousBrush);
            SelectObject(gGdi.dc, previousPen);
            GdiFlush();
        }
    }

    int threshold = std::clamp(settings.font.gdi_binary_threshold, 1, 255);
    int copyWidth = std::min(length, measuredWidth);
    // Match the old DLL: layout height and raster height are deliberately
    // independent. In particular font 101 is laid out one pixel tighter, but
    // its full 11 px Dotum glyph is copied to the destination buffer.
    int rasterHeight = measuredHeight + std::abs(settings.font.baseline_offset);
    int copyHeight = std::min(std::max(1, rasterHeight), gGdi.bitmapHeight);
    unsigned char paletteIndex = static_cast<unsigned char>(color & 0xFF);

    for (int y = 0; y < copyHeight; y++) {
        const unsigned int* source = gGdi.pixels + static_cast<size_t>(y) * gGdi.bitmapWidth;
        unsigned char* destination = buf + static_cast<size_t>(y) * pitch;
        for (int x = 0; x < copyWidth; x++) {
            unsigned int pixel = source[x];
            int blue = pixel & 0xFF;
            int green = (pixel >> 8) & 0xFF;
            int red = (pixel >> 16) & 0xFF;
            if (std::max({ red, green, blue }) >= threshold) {
                destination[x] = paletteIndex;
            }
        }
    }

    if ((color & FONT_UNDERLINE) != 0 && copyHeight > 0) {
        unsigned char* underline = buf + static_cast<size_t>(copyHeight - 1) * pitch;
        std::memset(underline, paletteIndex, static_cast<size_t>(copyWidth));
    }
}

bool legacyGdiFontsEnabled()
{
    if (settings.font.gdi_renderer < 0) {
        return false;
    }

    if (settings.font.gdi_renderer > 0) {
        return true;
    }

    return compat_stricmp(settings.system.language.c_str(), "korean") == 0;
}

void legacyGdiFontSetCurrent(int font)
{
    gGdi.currentFont = font;
    if (!selectCurrentFont()) {
        return;
    }

    fontDrawText = gdiFontDrawText;
    fontGetLineHeight = gdiFontGetLineHeight;
    fontGetStringWidth = gdiFontGetStringWidth;
    fontGetCharacterWidth = gdiFontGetCharacterWidth;
    fontGetMonospacedStringWidth = gdiFontGetMonospacedStringWidth;
    fontGetLetterSpacing = gdiFontGetLetterSpacing;
    fontGetBufferSize = gdiFontGetBufferSize;
    fontGetMonospacedCharacterWidth = gdiFontGetMonospacedCharacterWidth;
}

void legacyGdiFontsExit()
{
    if (gGdi.dc != nullptr && gGdi.previousFont != nullptr) {
        SelectObject(gGdi.dc, gGdi.previousFont);
    }
    if (gGdi.dc != nullptr && gGdi.bitmap != nullptr && gGdi.previousBitmap != nullptr) {
        SelectObject(gGdi.dc, gGdi.previousBitmap);
    }
    if (gGdi.bitmap != nullptr) {
        DeleteObject(gGdi.bitmap);
    }
    if (gGdi.textFont != nullptr) {
        DeleteObject(gGdi.textFont);
    }
    if (gGdi.buttonFont != nullptr) {
        DeleteObject(gGdi.buttonFont);
    }
    if (gGdi.titleFont != nullptr) {
        DeleteObject(gGdi.titleFont);
    }
    if (gGdi.dc != nullptr) {
        DeleteDC(gGdi.dc);
    }
    for (const std::wstring& path : gGdi.privateFontFiles) {
        RemoveFontResourceExW(path.c_str(), FR_PRIVATE, nullptr);
    }
    gGdi = {};
}

#else

bool legacyGdiFontsEnabled()
{
    return false;
}

void legacyGdiFontSetCurrent(int)
{
}

void legacyGdiFontsExit()
{
}

#endif

} // namespace fallout
