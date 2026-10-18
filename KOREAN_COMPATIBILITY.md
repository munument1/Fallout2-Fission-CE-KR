# Korean and Legacy Multilingual Text Support

이 문서는 F.I.S.S.I.O.N. 원본과 이 포크의 차이점, 그리고 한국어를 포함한 레거시 코드페이지 기반 언어에서 외부 TTF 폰트를 사용하는 방법을 설명합니다.

영어권/다국어 배포자를 위한 일반 문서는 `MULTILINGUAL_TTF_SUPPORT.md`를 참고하십시오.

## 원본과 달라진 점

이 포크는 원본 F.I.S.S.I.O.N.의 기존 `.fon` 폰트 렌더링 경로를 유지하면서, 선택적으로 외부 TTF 폰트 렌더러를 사용할 수 있게 합니다.

주요 변경 사항은 다음과 같습니다.

- `stb_truetype` 기반 TTF 글리프 렌더링 추가
- 레거시 멀티바이트 텍스트를 Unicode 코드포인트로 변환하는 경로 추가
- CP949/EUC-KR 한국어 텍스트 표시 지원
- 2바이트 문자 폭을 고려한 줄바꿈 처리 추가
- `fission.cfg`의 `[font]` 섹션으로 폰트 파일, 크기, 줄 높이, 코드페이지를 조정할 수 있게 변경
- 기본 소스 설정에서는 TTF 렌더러를 비활성화하여 원본의 영어/기존 `.fon` fallback 동작을 유지
- 한국어 배포판은 `fission.cfg`에서 명시적으로 TTF 렌더러와 한국어 폰트를 켜는 방식으로 동작

관련 소스 파일:

- `src/korean_font.cc`
- `src/korean_font.h`
- `src/text_font.cc`
- `src/word_wrap.cc`
- `src/settings.h`
- `src/settings.cc`
- `src/game_config.h`
- `third_party/stb_truetype.h`

## 기본 설계

상류 병합을 염두에 두고, 엔진 기본값은 한국어 전용 자산을 요구하지 않습니다.

기본 소스 설정에서는:

- TTF 렌더러가 꺼져 있습니다.
- 폰트 파일명이 비어 있습니다.
- 기존 F.I.S.S.I.O.N. `.fon` 폰트 로딩과 영어 fallback이 그대로 유지됩니다.

한국어 또는 다른 레거시 언어 패키지는 `fission.cfg`에 `[font]` 섹션을 추가하여 TTF 렌더러를 켭니다.

## 한국어 설정 예시

한국어 Sonora 패키지에서는 다음과 같은 설정을 사용합니다.

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

`legacy_codepage=949`는 Windows CP949입니다. 일반적인 EUC-KR 텍스트도 CP949 변환 경로에서 처리됩니다.

## 설정 항목

### `ttf_renderer`

TTF 렌더러 사용 여부입니다.

```ini
ttf_renderer=0
```

값:

- `0`: 끔. 원본 `.fon` 렌더러 사용
- `1`: 켬. `[font]`에 지정한 TTF 렌더러 사용
- `-1`: 자동. 호환 목적의 값이지만, 상류 병합 모델에서는 명시적으로 `1`을 권장합니다.

한국어 패키지에서는 혼동을 줄이기 위해 `ttf_renderer=1`을 권장합니다.

### `legacy_codepage`

레거시 텍스트를 Unicode로 변환할 때 사용할 Windows 코드페이지입니다.

```ini
legacy_codepage=949
```

예시:

- `949`: Korean CP949 / EUC-KR 계열
- `1251`: Cyrillic
- `1250`: Central European
- `1252`: Western European
- `932`: Japanese Shift-JIS
- `936`: Simplified Chinese GBK
- `950`: Traditional Chinese Big5

현재 변환은 Windows API를 사용하므로 Windows 빌드에서 가장 안정적입니다. 다른 플랫폼에 병합하려면 SDL_iconv 또는 별도 코드페이지 변환 계층으로 일반화하는 작업이 필요합니다.

다른 언어는 `fission.cfg`의 `[font]` 섹션에서 `legacy_codepage`에 Windows 코드페이지 번호를 지정합니다. 예를 들어 태국어는 `874`, 그리스어는 `1253`, 터키어는 `1254`, 히브리어는 `1255`, 아랍어는 `1256`, 발트어는 `1257`, 베트남어는 `1258`처럼 지정할 수 있습니다.

### `font_path` / `fallback_font_path`

TTF 파일을 찾을 폴더입니다.

```ini
font_path=fonts/korean
fallback_font_path=data/fonts/korean
```

엔진은 먼저 `font_path`에서 찾고, 실패하면 `fallback_font_path`에서 찾습니다. 상류 병합을 염두에 둔 기본 fallback은 `fonts/english`와 `data/fonts/english`입니다. 한국어 패키지는 자체 cfg에서 `fonts/korean`과 `data/fonts/korean`을 명시합니다.

배포 예시:

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

이 구조에서는 `fallback_font_path=data/fonts/korean`를 사용합니다.

### 폰트 파일 설정

엔진 폰트 번호 그룹별로 사용할 TTF 파일입니다.

```ini
small_font=NanumSquareNeo-aLt.ttf
normal_font=NanumSquareNeo-aLt.ttf
large_font=ChungjuKimSaeng.ttf
bold_font=ChungjuKimSaeng.ttf
title_font=ChungjuKimSaeng.ttf
default_font=ChungjuKimSaeng.ttf
```

대략적인 대응:

- `small_font`: 작은 UI 글꼴, font 0/100
- `normal_font`: 일반 대화/UI 글꼴, font 1/101
- `large_font`: 큰 글꼴, font 2/102
- `bold_font`: 강조 글꼴, font 3/103
- `title_font`: 제목 글꼴, font 104
- `default_font`: 위 분류에 들어가지 않는 font 번호의 fallback

특정 항목을 비워두면 `default_font`, 그 다음 `normal_font`를 fallback으로 사용합니다. 둘 다 비어 있으면 TTF 렌더러는 활성화되지 않습니다.

### 크기와 줄 높이

```ini
normal_size=10
normal_line_height=10
```

`*_size`는 TTF 렌더링 크기입니다.  
`*_line_height`는 레이아웃 엔진에 보고하는 줄 높이입니다.

텍스트가 위아래로 잘리면 `*_line_height`를 키우거나 `baseline_offset`을 조정합니다.  
글자가 너무 크거나 UI 밖으로 나가면 `*_size`를 줄입니다.

### `width_scale`

글자 폭 배율입니다.

```ini
width_scale=1.000000
```

값을 `0.9`처럼 낮추면 글자가 가로로 좁아집니다. 대화 선택지나 작은 버튼 안에서 글자가 넘칠 때 유용합니다.

### `baseline_offset`

글자의 세로 위치 보정값입니다.

```ini
baseline_offset=0
```

양수는 글자를 아래로, 음수는 위로 이동시킵니다.

### `antialiased`

안티앨리어싱 사용 여부입니다.

```ini
antialiased=1
```

값:

- `0`: 단색에 가까운 글자
- `1`: 부드러운 글자

## 다른 언어에서 사용하는 방법

다른 언어에서도 원리는 같습니다.

1. 번역 텍스트 파일을 해당 언어 폴더에 둡니다.
2. `language`를 해당 언어 이름으로 설정합니다.
3. `[font]`에서 `ttf_renderer=1`을 설정합니다.
4. 해당 언어 텍스트 인코딩에 맞는 `legacy_codepage`를 설정합니다.
5. 해당 글자를 포함하는 TTF 폰트를 지정합니다.

예시:

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
```

## 제한 사항

현재 구현은 상류 병합 전 단계의 호환 기능입니다.

- 코드페이지 변환은 Windows API에 의존합니다.
- UTF-8 텍스트를 직접 처리하는 범용 Unicode 텍스트 엔진은 아닙니다.
- 줄바꿈은 TTF 렌더러가 켜진 경우 2바이트 레거시 문자를 고려합니다.
- 폰트 파일은 배포자가 직접 라이선스를 확인하고 포함해야 합니다.
- 원본 Fallout 2 데이터, Sonora 원본 데이터, `master.dat`, `critter.dat`, 원본 실행 파일은 포함하지 않아야 합니다.

## 배포 시 권장 사항

한국어 패키지에는 다음을 포함하는 것을 권장합니다.

- 수정된 F.I.S.S.I.O.N. 소스 또는 소스 링크
- 원본 `LICENSE.md`
- 이 문서
- 사용한 폰트의 라이선스 파일
- `fission.cfg` 예시
- 한국어 번역 텍스트

패키지에는 다음을 포함하지 마십시오.

- Fallout 2 원본 게임 데이터
- Sonora 원본 데이터
- Dayglow/공식 배포 데이터
- `master.dat`
- `critter.dat`
- 원본 Fallout 실행 파일

## 상류 병합을 위한 추가 정리 방향

원본 main에 제안하려면 다음 작업을 권장합니다.

- `korean_font.*` 이름을 `ttf_font.*` 또는 `legacy_ttf_font.*`처럼 일반화
- Windows API 코드페이지 변환을 플랫폼 호환 계층으로 분리
- `ttf_renderer`를 더 명확한 기능 이름으로 문서화
- CJK/레거시 코드페이지 테스트 샘플 추가
- 한국어 기본 폰트명은 소스 기본값이 아니라 예시 cfg 또는 배포 패키지에만 유지
