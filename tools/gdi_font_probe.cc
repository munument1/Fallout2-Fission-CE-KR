// Standalone Windows regression probe for the production GDI renderer.
// Stub the game's compatibility and callback globals; no game data is needed.
#define NOMINMAX
#define PLATFORM_COMPAT_H
#define COMPAT_MAX_PATH 260
#include <cstring>
namespace fallout {
int compat_stricmp(const char* a, const char* b) { return _stricmp(a, b); }
}
#include "../src/legacy_gdi_font.cc"
#include <iostream>
#include <stdexcept>

namespace fallout {
Settings settings;
unsigned char _colorTable[32768] = {};
FontManagerDrawTextProc* fontDrawText;
FontManagerGetLineHeightProc* fontGetLineHeight;
FontManagerGetStringWidthProc* fontGetStringWidth;
FontManagerGetCharacterWidthProc* fontGetCharacterWidth;
FontManagerGetMonospacedStringWidthProc* fontGetMonospacedStringWidth;
FontManagerGetLetterSpacingProc* fontGetLetterSpacing;
FontManagerGetBufferSizeProc* fontGetBufferSize;
FontManagerGetMonospacedCharacterWidth* fontGetMonospacedCharacterWidth;
}

static void require(bool ok, const char* message)
{
    if (!ok) {
        throw std::runtime_error(message);
    }
}

int main()
{
    using namespace fallout;
    try {
        settings.system.language = "korean";
        require(legacyGdiFontsEnabled(), "Korean auto GDI selection failed");
        legacyGdiFontSetCurrent(101);
        require(gGdi.dc != nullptr, "GDI initialization failed");
        bool bundled = false;
        for (const auto& file : gGdi.privateFontFiles) {
            bundled |= file.find(L"Cafe24OhsquareAir-v2.0.ttf") != std::wstring::npos;
        }
        require(bundled, "Bundled Cafe24 font was not loaded privately");
        require(fontGetLineHeight() + 1 == 11, "Skill rows must have 11 px pitch");
        require(27 + 17 * (fontGetLineHeight() + 1) + 11 <= 233, "Skill list overlaps footer");

        const char* sample = "\xB1\xE2\xBC\xFA \xC0\xDA\xB9\xB0\xBC\xE8 \xB5\xFB\xB1\xE2";
        for (int font : { 100, 101, 102, 103, 104 }) {
            legacyGdiFontSetCurrent(font);
            wchar_t actualFace[LF_FACESIZE] = {};
            GetTextFaceW(gGdi.dc, LF_FACESIZE, actualFace);
            if (font >= 102) {
                char faceUtf8[256] = {};
                WideCharToMultiByte(CP_UTF8, 0, actualFace, -1, faceUtf8, sizeof(faceUtf8), nullptr, nullptr);
                std::cout << "font " << font << ": " << faceUtf8 << '\n';
            }
            require(font < 102 ? (std::wstring(actualFace) == L"Dotum" || std::wstring(actualFace) == L"\uB3CB\uC6C0") : std::wstring(actualFace) == L"Cafe24 Ohsquare air Light", "Wrong font selected");
            LOGFONTW actual = {};
            GetObjectW(fontForCurrentSelection(), sizeof(actual), &actual);
            require(actual.lfHeight == (font < 102 ? -11 : -16), "Wrong font size");
            require(actual.lfWeight == (font < 102 ? 400 : 700), "Wrong font weight");
            require(actual.lfQuality == NONANTIALIASED_QUALITY, "Raster quality differs from Korean Text Engine");
            for (int offset : { 0, -2, 2 }) {
                settings.font.baseline_offset = offset;
                int width = fontGetStringWidth(sample);
                int size = fontGetBufferSize(sample);
                require(width > 0 && size >= width * (11 + std::abs(offset)), "Raster buffer too small");
                std::vector<unsigned char> pixels(static_cast<size_t>(size) + 64, 0);
                std::fill(pixels.begin() + size, pixels.end(), static_cast<unsigned char>(0xCD));
                fontDrawText(pixels.data(), sample, width, width, 42);
                require(std::find(pixels.begin(), pixels.begin() + size, 42) != pixels.begin() + size, "Empty Korean raster");
                require(std::all_of(pixels.begin() + size, pixels.end(), [](unsigned char p) { return p == 0xCD; }), "Raster wrote beyond allocated buffer");
            }
            settings.font.baseline_offset = 0;
            int width = fontGetStringWidth("\x95");
            std::vector<unsigned char> bullet(fontGetBufferSize("\x95"), 0);
            require(width > 0 && !bullet.empty(), "Bullet dimensions missing");
            fontDrawText(bullet.data(), "\x95", width, width, 42);
            require(std::find(bullet.begin(), bullet.end(), 42) != bullet.end(), "Menu bullet disappeared");
        }
        legacyGdiFontsExit();
        require(gGdi.privateFontFiles.empty(), "Private fonts not released");
        std::cout << "PASS: bundled faces, sizes, weights, 18 skill rows, raster guards, menu bullets\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        legacyGdiFontsExit();
        return 1;
    }
}
