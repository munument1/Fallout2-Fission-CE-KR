# Legacy Multilingual TTF Text Support

This document explains the optional legacy-codepage TTF text renderer added in this fork of F.I.S.S.I.O.N. It is written for translators and mod maintainers who need non-English text support, especially languages that cannot be rendered well with the original `.fon` bitmap fonts.

The Korean CP949/EUC-KR support is the first practical use case, but the feature is intended to be configurable for other legacy Windows codepages as well.

## What Changed From Upstream

This fork keeps the original F.I.S.S.I.O.N. `.fon` font pipeline intact and adds an optional TTF rendering path.

Main differences:

- Added a `stb_truetype` based TTF glyph renderer.
- Added configurable legacy codepage conversion for multibyte text.
- Added CP949/EUC-KR Korean text handling.
- Added word wrapping that can account for 2-byte legacy characters.
- Added `[font]` settings in `fission.cfg`.
- Kept the default engine behavior compatible with upstream: TTF rendering is disabled by default and the original English / `.fon` fallback remains the default.

Relevant files:

- `src/korean_font.cc`
- `src/korean_font.h`
- `src/text_font.cc`
- `src/word_wrap.cc`
- `src/settings.h`
- `src/settings.cc`
- `src/game_config.h`
- `third_party/stb_truetype.h`

## Design Goal

The engine should not require Korean-specific files by default.

Default source behavior:

- TTF renderer is disabled.
- No Korean font file is hardcoded as a required default.
- Default font paths point to English fallback locations.
- Existing `.fon` behavior remains available.

Translation packages opt into TTF rendering through `fission.cfg`.

## Basic Configuration

Add or edit the `[font]` section in `fission.cfg`.

```ini
[font]
ttf_renderer=1
legacy_codepage=949
font_path=fonts/korean
fallback_font_path=data/fonts/korean
normal_font=NanumSquareNeo-aLt.ttf
default_font=ChungjuKimSaeng.ttf
normal_size=10
normal_line_height=10
width_scale=1.000000
baseline_offset=0
antialiased=1
```

For upstream-style default behavior:

```ini
[font]
ttf_renderer=0
legacy_codepage=0
font_path=fonts/english
fallback_font_path=data/fonts/english
```

## `ttf_renderer`

Controls whether the external TTF renderer is used.

```ini
ttf_renderer=1
```

Values:

- `0`: Disabled. Use the original `.fon` renderer.
- `1`: Enabled. Use the configured TTF renderer.
- `-1`: Auto. Kept for compatibility, but translation packages should usually use `1` explicitly.

## `legacy_codepage`

The Windows codepage used to convert legacy encoded text to Unicode codepoints before rendering.

```ini
legacy_codepage=949
```

Common values:

| Language / Region | Codepage |
| --- | ---: |
| Korean CP949 / EUC-KR | `949` |
| Japanese Shift-JIS | `932` |
| Simplified Chinese GBK | `936` |
| Traditional Chinese Big5 | `950` |
| Central European | `1250` |
| Cyrillic | `1251` |
| Western European | `1252` |
| Greek | `1253` |
| Turkish | `1254` |
| Hebrew | `1255` |
| Arabic | `1256` |
| Baltic | `1257` |
| Vietnamese | `1258` |
| Thai | `874` |

If your language is not listed in the GUI editor, choose `Custom / manual input` and enter the Windows codepage number directly.

Current limitation: conversion currently uses the Windows API, so this path is most reliable on Windows builds. For upstream cross-platform merge, this should eventually move behind a platform-neutral conversion layer such as SDL_iconv or a dedicated codepage conversion module.

## Font Paths

```ini
font_path=fonts/korean
fallback_font_path=data/fonts/korean
```

The engine first checks `font_path`, then `fallback_font_path`.

Recommended package layout:

```text
Fallout 2/
  fallout-fission-x64.exe
  fission.cfg
  data/
    fonts/
      korean/
        NanumSquareNeo-aLt.ttf
        ChungjuKimSaeng.ttf
```

For a different language, use a language-specific folder:

```ini
font_path=fonts/polish
fallback_font_path=data/fonts/polish
```

The upstream-friendly default fallback is:

```ini
font_path=fonts/english
fallback_font_path=data/fonts/english
```

## Font File Mapping

Different UI font groups can use different TTF files.

```ini
small_font=ExampleSans.ttf
normal_font=ExampleSans.ttf
large_font=ExampleDisplay.ttf
bold_font=ExampleBold.ttf
title_font=ExampleDisplay.ttf
default_font=ExampleSans.ttf
```

Approximate mapping:

- `small_font`: font 0 / 100
- `normal_font`: font 1 / 101
- `large_font`: font 2 / 102
- `bold_font`: font 3 / 103
- `title_font`: font 104
- `default_font`: fallback for other font numbers

If a specific font field is empty, the renderer falls back to `default_font`, then `normal_font`. If neither is set, the TTF renderer will not activate.

## Size And Layout

Each font group has a render size and line height.

```ini
normal_size=10
normal_line_height=10
```

- `*_size`: TTF render size.
- `*_line_height`: line height reported to the layout engine.

If text is clipped vertically, increase `*_line_height` or adjust `baseline_offset`.

If text overflows horizontally, reduce `*_size` or lower `width_scale`.

## Width And Baseline

```ini
width_scale=1.000000
baseline_offset=0
```

- `width_scale`: horizontal scale. Values like `0.90` can help fit text into narrow UI elements.
- `baseline_offset`: vertical shift. Positive moves text down, negative moves it up.

## Antialiasing

```ini
antialiased=1
```

Values:

- `0`: Harder, bitmap-like text.
- `1`: Smoother text.

## Korean Example

```ini
[system]
language=korean

[font]
ttf_renderer=1
legacy_codepage=949
font_path=fonts/korean
fallback_font_path=data/fonts/korean
small_font=NanumSquareNeo-aLt.ttf
normal_font=NanumSquareNeo-aLt.ttf
large_font=ChungjuKimSaeng.ttf
bold_font=ChungjuKimSaeng.ttf
title_font=ChungjuKimSaeng.ttf
default_font=ChungjuKimSaeng.ttf
small_size=16
normal_size=10
large_size=17
bold_size=13
title_size=22
default_size=13
small_line_height=16
normal_line_height=10
large_line_height=17
bold_line_height=13
title_line_height=22
default_line_height=13
width_scale=1.000000
baseline_offset=0
antialiased=1
```

## Other Language Example

Example for a Central European translation package:

```ini
[system]
language=polish

[font]
ttf_renderer=1
legacy_codepage=1250
font_path=fonts/polish
fallback_font_path=data/fonts/polish
normal_font=YourFont.ttf
default_font=YourFont.ttf
normal_size=10
normal_line_height=10
width_scale=1.000000
baseline_offset=0
antialiased=1
```

## Distribution Notes

Include:

- Modified F.I.S.S.I.O.N. source or source link.
- Original `LICENSE.md`.
- This document.
- `fission.cfg` example.
- Font license files.
- Translation text files.

Do not include:

- Fallout 2 original game data.
- Total conversion original data unless you have permission.
- `master.dat`.
- `critter.dat`.
- Original Fallout executables.

## Suggested Upstream Cleanup

Before proposing this upstream, consider:

- Rename `korean_font.*` to a neutral name such as `legacy_ttf_font.*`.
- Move Windows codepage conversion behind a cross-platform compatibility layer.
- Add small test samples for at least one single-byte and one multibyte codepage.
- Keep language-specific font filenames in example configs, not in engine defaults.
