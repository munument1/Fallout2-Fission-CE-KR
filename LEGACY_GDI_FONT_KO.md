# 레거시 한국어 GDI 폰트 렌더러

이 작업 사본에는 과거 한국어 패치의 `fallout2font.dll` 동작을 F.I.S.S.I.O.N. 소스로 옮긴 Windows 전용 렌더러가 들어 있다.

## 사용 방법

`fission.cfg`의 `[font]` 섹션에 다음 값을 추가한다.

```ini
[font]
gdi_renderer=1
ttf_renderer=0
legacy_codepage=949
gdi_text_face=Dotum
gdi_text_size=11
gdi_text_weight=400
gdi_text_line_height=11
gdi_button_face=Cafe24 Ohsquare air Light
gdi_button_size=16
gdi_button_weight=700
gdi_button_line_height=20
gdi_title_face=Cafe24 Ohsquare air Light
gdi_title_size=16
gdi_title_weight=700
gdi_title_line_height=20
gdi_binary_threshold=128
baseline_offset=0
```

전체 예시는 `GDI_FONT_PRESET.cfg`에 있다.

## 렌더링 방식

1. CP949 텍스트를 UTF-16으로 변환한다.
2. Windows GDI의 `CreateFontW`와 `TextOutW`로 32bpp DIBSection에 출력한다.
3. DIB 픽셀의 밝기가 `gdi_binary_threshold` 이상이면 Fallout 8비트 화면 버퍼에 요청된 팔레트 색을 기록한다.
4. font 100/101은 일반, 102는 큰 글꼴, 103은 굵은 중간 글꼴, 104는 제목 글꼴로 나눠 사용한다.

CR/LF 같은 개행 제어문자는 GDI에 전달하지 않으므로 줄 끝에 네모 글리프가 나타나지 않는다.

기본 임계값은 128이다. 본문은 돋움 11, 버튼과 제목은 카페24 아네모네 에어 16·굵게를 사용한다.

기술 목록은 font 101의 레이아웃 높이 10에 행 여백 1을 더해 11픽셀 간격으로 배치한다. 실제 글자는 11픽셀 높이를 모두 출력한다.

배포본의 `fonts/Cafe24OhsquareAir-v2.0.ttf`는 실행 시 전용으로 불러온다. 글꼴의 배포 조건은 같은 폴더의 `Cafe24-OhsquareAir-LICENSE.pdf`에 있다.

## 기존 렌더러와의 관계

- `gdi_renderer=1`: Windows GDI 경로를 강제로 사용한다.
- `gdi_renderer=0`: Windows에서 `language=korean`이면 GDI 경로를 자동 사용한다.
- `gdi_renderer=-1`: GDI 경로를 강제로 끈다.
- `gdi_renderer=0`, `ttf_renderer=1`: 기존 stb_truetype TTF 경로를 사용한다.
- 둘 다 0: 원본 FON/AAF 렌더러를 사용한다.
- Windows 이외의 플랫폼에서는 GDI 경로가 자동으로 비활성화된다.

## 구현 파일

- `src/legacy_gdi_font.cc`
- `src/legacy_gdi_font.h`
- `src/korean_font.cc`
- `src/settings.h`
- `src/settings.cc`
- `src/game_config.h`

## 현재 상태

Windows 배포 워크플로에서 `tools/gdi_font_probe.cc`를 실행해 전용 글꼴 로딩, 크기와 굵기, 기술 18개의 행 간격, 전체 글자 높이에 필요한 버퍼 경계와 메뉴 점 표시를 검증한다.
