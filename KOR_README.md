<p align="center">
  <img src="files/fallout-fission-logo.jpg" alt="Fallout: F.I.S.S.I.O.N. 로고" width="1024">
</p>

# Fallout: F.I.S.S.I.O.N.
*Flexible Isometric Simulation System for Interactive Open‑world Nuclear‑roleplaying (상호작용형 오픈월드 핵-롤플레잉을 위한 유연한 등각 투영 시뮬레이션 시스템)*

Fallout: F.I.S.S.I.O.N.은 [Fallout2-CE](https://github.com/alexbatalov/fallout2-ce)에서 포크된 차세대 크로스 플랫폼 폴아웃 1 & 2 재구현 프로젝트입니다. 원작의 쿼터뷰(등각 투영) 턴제 게임플레이를 그대로 보존하면서 모딩 확장성, 와이드스크린 지원, 그리고 커뮤니티 주도의 진정한 확장성을 더했습니다. Windows, Linux, macOS, Android, iOS는 물론 브라우저에서도 실행할 수 있습니다. 현재 한국어 호환 릴리즈는 Fission CE `beta-0.9.7.7` 기준입니다.

> **F.I.S.S.I.O.N. 엔진 구동**
> *Flexible(유연하고). Isometric(쿼터뷰 방식의). Simulation(시뮬레이션). System(시스템을 갖춘). Interactive(상호작용형). Open‑world(오픈월드). Nuclear‑roleplay(핵-롤플레잉).*
> **과거로부터의 분할, 미래를 향한 동력**

---

## 한국어 Windows 글꼴 프리셋

본문은 **돋움 11**, 버튼과 제목은 **카페24 아네모네 에어 16·굵게**를 사용합니다. 기술 목록은 **11픽셀 간격**으로 표시합니다.

[한국어 Windows 배포본](https://github.com/munument1/Fallout2-Fission-CE-KR/releases/tag/beta-0.9.7.8-korean.1)의 파일을 게임 폴더에 풀고 `fallout-fission-x64.exe`를 실행하세요. `fonts` 폴더도 함께 복사합니다. 기존 `fission.cfg`를 유지하려면 배포본의 `[font]` 설정을 기존 파일의 같은 항목에 반영하세요.

카페24 글꼴과 배포 라이선스가 포함되어 있습니다.

## 주요 기능

- **정통 쿼터뷰 턴제 경험** (SPECIAL 시스템, 오리지널 폴아웃 게임플레이)
- **완벽한 크로스 플랫폼 지원**: Windows, macOS, Linux, iOS, Android, Web
- **와이드스크린 및 고해상도 스케일링** (픽셀 단위의 완벽한 화면비 보존)
- **모듈형 맞춤 설정 시스템** — 커뮤니티 모드가 매끄럽게 연동됨 (현재 작동 중)
- **오리지널 폴아웃 1 & 2 에셋과 100% 호환** — Fission CE 0.9.7 계열부터 폴아웃 1 실행 지원
- **미래 지향적 설계**: 새로운 콘텐츠 및 폴아웃 2 통합을 위한 손쉬운 확장 가능 (현재 작동 중)

---

## F.I.S.S.I.O.N. 명칭 분석

```
╔═══════════════════════╦══════════════════════════════════════════════╗
║         속 성         ║                    설 명                      ║
╠═══════════════════════╬══════════════════════════════════════════════╣
║ F – Flexible          ║ 적응력이 뛰어나고, 모딩이 쉬우며, 미래 준비 완료 ║
║ I – Isometric         ║ 클래식 2D 그리드 시점에 충실함                  ║
║ S – Simulation        ║ AI, 월드 규칙, 능력치, 턴 타이밍 관리           ║
║ S – System            ║ 엔진/런타임을 위한 통합 아키텍처                ║
║ I – Interactive       ║ 역동적인 플레이어의 선택과 피드백               ║
║ O – Open‑world        ║ 심리스(Seamless)한 대형 지도 탐험              ║
║ N – Nuclear‑roleplay  ║ 몰입감 넘치는 포스트 뉴클리어 RPG 경험          ║
╚═══════════════════════╩══════════════════════════════════════════════╝
```

---

## 모드/게임 호환성

**완전 지원**:
- 폴아웃 1 (Fallout 1)
- 폴아웃 2 (Fallout 2)
- 폴아웃: 네바다 (Fallout: Nevada)
- 폴아웃: 소노라 (Fallout: Sonora)

**아직 지원되지 않음 (향후에도 미지원 가능성 있음)**:
- 폴아웃 네바다 또는 소노라 '리팩(repack)' 버전
- 리스토레이션 프로젝트 (Restoration Project)
- Fallout: Et Tu
- Olympus 2207
- Resurrection, Yesterday (테스트되지 않음)


---

## 설치 방법

### 사전 요구 사항
**폴아웃 1 또는 폴아웃 2** 정품 설치본이 필요합니다. F.I.S.S.I.O.N.은 원본 실행 파일을 대체하는 스탠드얼론 프로그램이며, 실행을 위해 해당 게임의 오리지널 데이터 전체가 필요합니다.

**지원되는 베이스 설치본:**
- **바닐라 폴아웃 1** - 클래식 원본 게임
- **바닐라 폴아웃 2** - 클래식 원본 게임
- **폴아웃: 네바다** - 러시아 토탈 컨버전 모드
- **폴아웃: 소노라** - 러시아 토탈 컨버전 모드

### 빠른 설치
1. **지원되는 폴아웃 1 또는 폴아웃 2 설치본이 정상적으로 작동하는지 확인합니다.**
2. 최신 [F.I.S.S.I.O.N. 한국어 릴리스](https://github.com/munument1/Fallout2-Fission-CE-KR/releases)를 **다운로드**합니다.
3. 다운로드한 F.I.S.S.I.O.N. 파일들을 폴아웃 2 설치 폴더에 **압축 해제**합니다.
4. 한국어 Windows 빌드에서는 `fallout-fission-x64.exe`를 **실행**합니다.

끝입니다! F.I.S.S.I.O.N.이 기존 콘텐츠를 자동으로 불러오고 강화된 모딩 기능을 적용합니다.

### 플랫폼별 설치 안내
※ 현재 한국어는 윈도우 버전만 지원 가능합니다.


#### Windows

예시: Steam 폴아웃 2 설치 경로에 설치하는 경우
1. 폴아웃 2 폴더로 이동합니다 (통상적인 경로):
cd "C:\Program Files (x86)\Steam\steamapps\common\Fallout 2"

2. 이 위치에 F.I.S.S.I.O.N. 파일들의 압축을 풉니다.
3. `fallout-fission-x64.exe`를 실행합니다.

#### macOS

예시: GOG 폴아웃 2 설치본을 사용하는 경우
1. Fallout2.app 우클릭 → "패키지 내용 보기" 선택
2. Contents/Resources/Data/ 경로로 이동
3. 이 위치에 F.I.S.S.I.O.N. 파일들의 압축을 풉니다.
4. fallout-fission.app을 실행합니다.

#### Linux

예시: Wine으로 폴아웃 2를 설치한 경우
1. 폴아웃 2 Wine 프리픽스 경로로 이동합니다.
cd ~/.wine/drive_c/Program\ Files/Fallout\ 2/

2. F.I.S.S.I.O.N. 파일들의 압축을 풉니다.
3. 다음 명령어로 실행합니다: wine fallout-fission.exe

### 올바른 폴더 구조

설치가 완료되면 폴아웃 2 폴더 구조는 다음과 같아야 합니다:

Fallout 2/
├── fallout-fission.exe     # F.I.S.S.I.O.N. 실행 파일 (Windows)
├── fallout-fission.app     # F.I.S.S.I.O.N. 애플리케이션 (macOS)
├── fission.dat             # 엔진 데이터 파일
├── master.dat              # 오리지널 게임 데이터
├── critter.dat             # 오리지널 게임 데이터
├── patch000.dat            # 패치 데이터 (존재하는 경우)
├── data/                   # 게임 데이터 폴더
│   ├── proto/              # 프로토 파일 (바닐라 + 모드)
│   ├── text/               # 텍스트 파일 (바닐라 + 모드)
│   └── maps/               # 맵 파일
└── data/lists/             # 자동 생성되는 모드 리포트 (최초 실행 시 생성)


### 중요 참고 사항

- F.I.S.S.I.O.N.에는 **게임 데이터가 포함되어 있지 않습니다** - 반드시 폴아웃 2를 소유하고 있어야 합니다.

- **기존 세이브 파일이 호환됩니다** - F.I.S.S.I.O.N.은 완벽한 하위 호환성을 유지합니다.

- **모드는 기존 위치에 그대로 두면 됩니다** - F.I.S.S.I.O.N.은 기존 `data/` 구조에서 직접 데이터를 읽어옵니다.

- 기본적인 사용에는 **별도의 설정이 필요하지 않습니다** - 실행 파일만 교체하면 바로 작동합니다.

---

## 환경 설정

'그래픽' 관련 설정은 게임 내 '환경 설정(preferences)' 화면을 이용하세요.

그 외의 설정은 `fission.cfg` 파일을 통해 변경할 수 있습니다.

고급 트윅을 적용하려면 `fission.cfg` 파일의 `[enhancements]` 섹션을 수정하세요:

[enhancements]
WorldMapTravelMarkers=1
GaplessMusic=1
EnhancedBarter=1
Minimap=1
GreenScreens=0
InventoryFilter=0
DisplayWeight=0
CompanionInventory=0
VockFeatures=0

와이드스크린 해상도만 적용하고 오리지널 Fallout2.exe와 완전히 동일한 바닐라 경험을 원하신다면 `StrictVanilla=1`로 설정하세요.

---

## 기여하기

기여는 언제나 환영합니다! GitHub에 이슈를 제보하거나 풀 리퀘스트(PR)를 보내주세요.

---

## 크레딧

Fallout2.exe를 리버스 엔지니어링(디컴파일)하여 초기 기틀을 마련해 준 Alex Batalov에게 감사드립니다. 그의 작업이 없었다면 FISSION도 존재하지 못했을 것입니다.

---

## 라이선스

본 프로젝트는 [Sustainable Use License](LICENSE.md) 라이선스 하에 배포됩니다.

## upstream 설정 변경 (2026-10-08)

현재 소스 기준은 `5056bfb`입니다. 기존 `[enhancements] VockFloats`는 `VockFeatures`로 변경되었습니다. `[vock-floats]` 섹션은 `[vock-features]`로, `VoicedFloats`는 `FloatAudio`로 변경되었습니다. `TextScramble`과 `PipBoyAudio`는 각각 독립적인 설정이며 홀로디스크 음성은 `sound/pipboy/`에서 읽습니다. 자세한 키와 기본값은 `src/mod_config.h` 및 `documentation/holodisk_mini-guide.md`를 참고하십시오.
