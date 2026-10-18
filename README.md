<p align="center">
  <img src="files/fallout-fission-logo.jpg" alt="Fallout: F.I.S.S.I.O.N. Logo" width="1024">
</p>

# Fallout: F.I.S.S.I.O.N.
*Flexible Isometric Simulation System for Interactive Open-World Nuclear Roleplaying*

Fallout: F.I.S.S.I.O.N.은 [Fallout2-CE](https://github.com/alexbatalov/fallout2-ce)에서 갈라져 나온 Fallout 2 재구현 프로젝트입니다. 원작의 아이소메트릭 턴제 게임플레이를 보존하면서 모딩 확장, 와이드스크린 지원, 커뮤니티 중심의 확장성을 더했습니다. Windows, Linux, macOS, Android, iOS, 브라우저에서 실행할 수 있습니다.

> **F.I.S.S.I.O.N. 엔진으로 구동**
> *Flexible. Isometric. Simulation. System. Interactive. Open-World. Nuclear Roleplay.*
> **과거에서 분리되어, 미래를 움직입니다**

---

## 한국어 Windows 글꼴 프리셋

본문은 **돋움 11**, 버튼과 제목은 **카페24 아네모네 에어 16·굵게**를 사용합니다. 기술 목록은 **11픽셀 간격**으로 표시합니다.

[한국어 Windows 배포본](https://github.com/munument1/Fallout2-Fission-CE-KR/releases/tag/FISSION-CE-Korean-V0.97.4)의 파일을 게임 폴더에 풀고 `fallout-fission-x64.exe`를 실행하세요. `fonts` 폴더도 함께 복사합니다. 기존 `fission.cfg`를 유지하려면 배포본의 `[font]` 설정을 기존 파일의 같은 항목에 반영하세요.

카페24 글꼴과 배포 라이선스가 포함되어 있습니다.

## 한국어 호환성 포크

이 포크에는 Windows 환경에서 한국어를 사용하기 위한 호환성 작업이 포함되어 있습니다. 현재 소스는 Fission CE `beta-0.9.7.7` 이후 upstream `97fd1d5`까지 동기화했으며, 레거시 코드페이지/GDI 및 TTF 폰트 렌더링과 한국어 UI 리소스를 포함합니다.

- 한국어 버전 가이드: [KOR_README.md](KOR_README.md)
- 한국어 호환성 참고 사항: [KOREAN_COMPATIBILITY.md](KOREAN_COMPATIBILITY.md)
- 다국어 TTF/코드페이지 참고 사항: [MULTILINGUAL_TTF_SUPPORT.md](MULTILINGUAL_TTF_SUPPORT.md)

---

## 주요 기능

- **원작에 충실한 아이소메트릭 턴제 경험**: SPECIAL 시스템과 클래식 Fallout 게임플레이 유지
- **진정한 크로스 플랫폼 지원**: Windows, macOS, Linux, iOS, Android, Web
- **와이드스크린 및 고해상도 스케일링**: 픽셀 단위의 화면비 보존
- **모듈식 커스터마이징 시스템**: 커뮤니티 모드를 자연스럽게 연동
- **원본 Fallout 1 & 2 애셋과 100% 호환**: Fission CE 0.9.7 계열부터 Fallout 1 실행 지원
- **선택 가능한 편의 기능**: 부드러운 스크롤·줌과 홀로디스크 음성 재생 등
- **미래 확장성**: 새 콘텐츠와 Fallout 2 통합을 쉽게 확장할 수 있는 구조

---

## 스크린샷

<p align="center">
    <a href="https://cambragol.github.io/fallout-fission/assets/screenshot2.png">
    <img src="https://cambragol.github.io/fallout-fission/assets/screenshot2_thumb.png" width="240" alt="Screenshot 1"></a>
    <a href="https://cambragol.github.io/fallout-fission/assets/screenshot1.png">
    <img src="https://cambragol.github.io/fallout-fission/assets/screenshot1_thumb.png" width="240" alt="Screenshot 2"></a>
    <a href="https://cambragol.github.io/fallout-fission/assets/screenshot3.png">
    <img src="https://cambragol.github.io/fallout-fission/assets/screenshot3_thumb.png" width="240" alt="Screenshot 3"></a>
    <a href="https://cambragol.github.io/fallout-fission/assets/screenshot9.png">
    <img src="https://cambragol.github.io/fallout-fission/assets/screenshot9_thumb.png" width="240" alt="Screenshot 9"></a>
    <a href="https://cambragol.github.io/fallout-fission/assets/screenshot4.png">
    <img src="https://cambragol.github.io/fallout-fission/assets/screenshot4_thumb.png" width="240" alt="Screenshot 4"></a>
    <a href="https://cambragol.github.io/fallout-fission/assets/screenshot5.png">
    <img src="https://cambragol.github.io/fallout-fission/assets/screenshot5_thumb.png" width="240" alt="Screenshot 5"></a>
</p>

---

## F.I.S.S.I.O.N. 이름 풀이

| 글자 | 의미 | 설명 |
| --- | --- | --- |
| F | Flexible | 적응 가능하고, 모딩하기 쉬우며, 미래 확장에 대비한 구조 |
| I | Isometric | 클래식 2D 격자 시점에 충실한 화면 구성 |
| S | Simulation | AI, 세계 규칙, 능력치, 턴 진행을 관리 |
| S | System | 엔진과 런타임을 아우르는 통합 아키텍처 |
| I | Interactive | 플레이어 선택과 반응을 동적으로 처리 |
| O | Open-World | 넓은 맵을 끊김 없이 탐험 |
| N | Nuclear Roleplay | 몰입감 있는 포스트 뉴클리어 RPG 경험 |

---

## 모드/게임 호환성

**완전히 지원됨**:
- Fallout 1
- Fallout 2
- Fallout: Nevada
- Fallout: Sonora

**부분적으로 지원됨**:
- Restoration Project

**아직 지원되지 않으며, 앞으로도 지원되지 않을 수 있음**:
- Fallout Nevada 또는 Sonora 리팩 버전
- Fallout: Et Tu
- Olympus 2207 (미검증)
- Resurrection
- Yesterday (미검증)


---

## 설치

### 사전 준비

**Fallout 1 또는 Fallout 2** 정품 설치본이 필요합니다. F.I.S.S.I.O.N.은 원본 실행 파일을 대체하며, 실행을 위해 해당 게임의 완전한 데이터가 필요합니다.

**지원되는 기본 설치 환경:**
- **Vanilla Fallout 1** - 클래식 원본 게임
- **Vanilla Fallout 2** - 클래식 원본 게임
- **Fallout: Nevada** - 러시아어 토탈 컨버전 모드
- **Fallout: Sonora** - 러시아어 토탈 컨버전 모드

### 빠른 설치

1. **지원되는 Fallout 1 또는 Fallout 2 설치본이 정상 작동하는지 확인합니다.**
2. 최신 [F.I.S.S.I.O.N. 릴리스](https://github.com/munument1/Fallout2-Fission-CE-KR/releases)를 **다운로드**합니다.
3. F.I.S.S.I.O.N. 파일을 Fallout 2 폴더에 **압축 해제**합니다.
4. 한국어 Windows 빌드에서는 `fallout-fission-x64.exe`를 **실행**합니다.

이것으로 충분합니다. F.I.S.S.I.O.N.은 기존 콘텐츠를 자동으로 불러오고 향상된 모딩 기능을 적용합니다.

### 플랫폼별 안내

#### Windows

```bat
# 예: Steam Fallout 2 설치 폴더에 설치
# 1. Fallout 2 폴더로 이동합니다. 일반적인 경로는 다음과 같습니다.
cd "C:\Program Files (x86)\Steam\steamapps\common\Fallout 2"
# 2. 이 위치에 F.I.S.S.I.O.N. 파일을 압축 해제합니다.
# 3. fallout-fission-x64.exe를 실행합니다.
```

#### macOS

```sh
# 예: GOG Fallout 2 설치본 사용
# 1. Fallout2.app을 우클릭한 뒤 "패키지 내용 보기"를 선택합니다.
# 2. Contents/Resources/Data/로 이동합니다.
# 3. 이 위치에 F.I.S.S.I.O.N. 파일을 압축 해제합니다.
# 4. fallout-fission.app을 실행합니다.
```

#### Linux

```sh
# 예: Wine으로 설치한 Fallout 2 사용
# 1. Fallout 2 Wine prefix로 이동합니다.
cd ~/.wine/drive_c/Program\ Files/Fallout\ 2/
# 2. F.I.S.S.I.O.N. 파일을 압축 해제합니다.
# 3. 다음 명령으로 실행합니다: wine fallout-fission.exe
```

### 예상 폴더 구조

설치 후 Fallout 2 폴더는 다음과 비슷한 구조가 됩니다.

```text
Fallout 2/
├── fallout-fission.exe     # F.I.S.S.I.O.N. 실행 파일 (Windows)
├── fallout-fission.app     # F.I.S.S.I.O.N. 애플리케이션 (macOS)
├── fission.dat             # 엔진 데이터 파일
├── master.dat              # 원본 게임 데이터
├── critter.dat             # 원본 게임 데이터
├── patch000.dat            # 패치 데이터 (있는 경우)
├── data/                   # 게임 데이터 폴더
│   ├── proto/              # Proto 파일 (바닐라 + 모드)
│   ├── text/               # 텍스트 파일 (바닐라 + 모드)
│   └── maps/               # 맵 파일
└── data/lists/             # 자동 생성되는 모드 리포트 (최초 실행 시 생성)
```

### 중요 참고 사항

- F.I.S.S.I.O.N.에는 **게임 데이터가 포함되어 있지 않습니다**. Fallout 2를 직접 보유하고 있어야 합니다.
- **기존 저장 파일은 그대로 사용할 수 있어야 합니다**. F.I.S.S.I.O.N.은 높은 호환성을 유지합니다.
- **모드는 기존 위치에 그대로 두면 됩니다**. F.I.S.S.I.O.N.은 기존 `data/` 구조에서 데이터를 읽습니다.
- 기본 사용에는 **별도 설정이 필요하지 않습니다**. 실행 파일만 교체하면 바로 작동합니다.

---

## 설정

그래픽 설정은 게임 내 `preferences` 화면에서 변경할 수 있습니다.

그 외 설정은 `fission.cfg` 파일에서 변경할 수 있습니다.

고급 조정을 하려면 `fission.cfg`의 `[enhancements]` 섹션을 사용하세요.

```ini
[enhancements]
AutoOpenDoors=0
AutoPush=1
AutoQuickSave=0
DisplayBonusDamage=0
DisplayKarmaChanges=0
EnhancedBarter=0
ExplosionsEmitLight=0
GameSpeed=1
GaplessMusic=0
InventoryColumns=1
MassHighlight=1
Minimap=0
NpcArmor=1
GreenScreens=0
InventoryFilter=0
DisplayWeight=0
CompanionInventory=0
VockFloats=0
NumbersInDialogue=0
RemoveCriticalTimelimits=0
SkipOpeningMovies=2
StrictVanilla=0
```

와이드스크린만 적용하고 원본 `Fallout2.exe`와 최대한 같은 바닐라 경험을 원한다면 `StrictVanilla=1`로 설정하세요.

---

## 기여

기여는 언제든 환영합니다. GitHub에서 이슈를 열거나 풀 리퀘스트를 보내 주세요.
현지화 기여에 관한 내용은 [Localization](https://github.com/cambragol/fission-ce/tree/main/files/localization) 문서를 참고하세요.

---

## 크레딧

Fallout2.exe를 디컴파일하는 초기 작업을 해 준 Alex Batalov에게 감사드립니다. 그의 작업이 없었다면 FISSION은 존재할 수 없었습니다.

---

## 라이선스

[Sustainable Use License](LICENSE.md)에 따라 배포됩니다.
