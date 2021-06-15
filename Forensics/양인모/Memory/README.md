# 메모리 포렌식

**주 기억장치(메모리)에 존재하는 휘발성 데이터**를 덤프 분석하는 과정을 의미한다.

## 메모리 포렌식을 왜 하는가

최근의 공격들은 매우 은밀하게 이뤄져 흔적을 찾기 힘들다. 하지만 악성코드가 실행되기 위해서는 메모리로 로드되어야 해 메모리는 악성코드를 가지고 있을 가능성이 높다. 피해 시스템의 RAM은 악의적인 코드가 할당한 자원과 악성코드 관련 증거들을 포함하고 있어 분석 시 유용한 흔적을 찾을 수 있다.

### 분석 시 얻을 수 있는 정보

1. 프로세스 정보
2. 네트워크 연결 정보
3. 윈도우 레지스터리 정보
4. 패스워드, 캐시정보, 클립보드 정보 등
5. 악성코드 파일 정보
6. 하드웨어 설정 정보

### 장점

하드 디스크와 네트워크 패킷을 분석해 얻은 증거는 완전 재구성을 가능하게 하는 RAM의 콘텐츠나 악성 코드에 의한 감염 혹은 침해사고 발생 전후 어떤 일들이 발생했는가를 판단하는데 필요한 **퍼즐 조각의 일부**이다.
하지만 메모리에서 찾은 단서들을 공통점이 없는 것처럼 보였던 포렌식 흔적들과 연결 지어 인식하지 못한 증거들을 알 수 있다.

만약 유출된 데이터가 네트워크를 통해 암호화되어 있다면 패킷 포렌식은 어떤 민감한 정보가 유출되는지 알 수 없다.
그러나 메모리 포렌식은 종종 암호화 키와 패스워드, 심지어 암호화 되기 전 일반 텍스트를 복구할 수 있어 결론을 도출하고 공격을 파악할 수 있도록 도와준다.

### 단점

휘발성 데이터로 전원 차단 시 데이터가 사라
지며 온전한 데이터 수집이 어렵다.

### 메모리 덤프

RAM에 존재하는 모든 데이터를 덤프해 **분석가능한 파일 형태**로 변환하는 작업

#### 메모리 덤프 방식

1. 하드웨어를 이용한 덤프 : FireWire Attack(IEEE 1394)를 이용한 메모리 덤프, Tribble를 PCI 장치를 이용해 덤프

   - 장점
     - 악성 프로그램에 영향을 받지 않는다.
     - 빠른 메모리 덤프 가능
     - 무결성 최소화
   - 단점
     - 안전성에 대한 검증이 필요하다
     - 간혹 시스템 크래시 발생

2. 소프트웨어를 이용한 덤프 방식
   DD, MDD, Winen, WIN32/64dd & Dumplt, Memorize ProDiscovery, HBGary, FastDumpPro, 크래시 덤프, 절전 덤프 등 - 장점 - 추가 장치가 필요없다. - 오픈소스 및 프리웨어 도구가 다양함 - 단점 - 커널 루트킷에 취약하다. - OS 제약을 받는다. - 수집하는 메모리쪽에 흔적이 남는다.

3. Virtual Machine Imaging

   - VMware 세션이 정지되면 물리 메모리 내용은 .vmem 확장자를 가지는 파일에 포함된다.
   - vmem은 raw 포맷과 유사하고 다른 메모리 분석 도구를 통해 분석 가능하다.
   - 악성코드를 가상머신에 올리고 폴더에 보면 .vmem이 생기는데 이것을 이용해서 덤프를 뜰 수 있다.

4. 절전모드 덤프(Hibernation)

   - 전력 관리를 보다 효율적으로 하기 위해 절전 상태에 돌입되면 하드 드라이브에 메모리 데이터를 기록한 다음 전력을 차단해 버리는 기능이다.

   - 윈도우는 절전모드로 들어갈 경우 물리메모리 내용을 압축해 C:hiberfil.sys파일로 저장한다.

   - 부팅 과정에서 hiberfil.sys가 설정되어 있으면 NTLDR에 의해서 메모리로 로드 된 후에 이전 상태로 돌아간다.

# Volatility

메모리 분석을 위한 대표적인 프레임워크 도구
위키 페이지 : https://github.com/volatilityfoundation
볼라틸리티 기본 명령어, 플러그인 예제 활용 사례, 샘플을 제공한다.

32비트/64비트 윈도우즈XP, 윈도우즈 2003, 윈도우즈 비스타(Vista), 윈도우즈 7, 10 계열 등 모든 메모리 분석이 지원 되며, 리눅스, 안드로이드, MAC OS 환경 프로파일도 포함

## 주요 옵션 설명

- **-h, --help :** 도움말 보기, 모든 옵션 및 기본설정 명령어 확인 _# 기본설정은 /etc/volatilityrc에 저장되어 있다._
- **--conf-file=.volatilityrc :** 설정 파일을 지정
- -d, --debug : 볼라틸리티 실행 중 디버깅
- --plugins=PLUGINS : 사용할 플러그인 디렉터리 추가 설정 (세미콜론으로 구분)
- --info : 등록되어 있는 모든 오브젝트의 정보 확인
- --cache-directory=C:\Users\kb1736/.cache\volatility : 캐쉬파일이 저장되어 있는 디렉터리 지정
- --cache : 캐쉬 사용 설정
- **--profile= : 덤프된 파일 프로파일 지정**
- -l LOCATION, --location=LOCATION : 주소 공간을 불러오는 곳으로부터 URN 위치
- --dtb=DTB : DTB주소
- --output=text : 출력 포멧 설정
- --output-file=OUTPUT_FILE : 지정된 파일에 출력 저장
- -v, --verbose : 상세 정보 확인
- -g KDBG, --kdbg=KDBG : 특정 KDBG 가상주소 지정
- -k KPCR, --kpcr=KPCR : 특정 KPRC 가상주소 지정

## 주요 플러그인

#### 운영체제 분석

**imageinfo :** 덤프 파일의 이미지 정보 분석
`python vol.py -f [덤프 파일] imageinfo` _# vol.py : 볼라틸리티 실행 파일_

#### 프로세스 분석

**psscan :** 실행 중인 프로세스/종료된 프로세스 정보 분석
`python vol.py -f [덤프 파일] --profile=WinXPSP2x86 psscan`

**psxview :** pslist, psscan 등 여러 가지 방법으로 확인한 프로세스 정보 비교
`python vol.py -f [덤프 파일] --profile=WinXPSP2x86 psxview`

**pstree :** 프로세스의 부모/자식관계 분석
`python vol.py -f [덤프 파일] --profile=WinXPSP2x86 pstree`

#### 네트워크 분석

**connections :** 활성화 상태의 네트워크 연결 정보(윈도우 xp/Vista)
`python vol.py -f [덤프 파일] --profile=WinXPSP2x86 connections`

**connscan :** 활성화 상태의 네트워크 연결 정보/ 이미 종료된 네트워크 연결 정보
`python vol.py -f [덤프 파일] --profile=WinXPSP2x86 connscan`

**netscan :** 활성화 상태의 네트워크 연결 정보(윈도우7 이상)
`python vol.py -f [덤프 파일] --profile=WinXPSP2x86 netscan`

#### DLL, Thread 분석

**dlllist :** 특정 프로세스에서 로드 한 DLL의 정보 분석
`python vol.py -f [덤프 파일] --profile=WinXPSP2x86 dlllist -p [PID]`

**ldrmodules :** 은폐된 DLL 정보 분석
`python vol.py -f [덤프 파일] --profile=WinXPSP2x86 ldrmodules`

**dlldump :** 특정 프로세스에서 로드 한 DLL 추출(바이너리 형태)
`python vol.py -f [덤프 파일] --profile=WinXPSP2x86 dlldump -p [PID] -D ./`

**malfind :** 사용자 모드 형태로 은폐되어 있거나 인젝션 된 코드 또는 DLL 정보 분석
`python vol.py -f [덤프 파일] --profile=WinXPSP2x86 malfind -p [PID]`

#### 파일 분석

**filescan :** 메모리에 로드 된 파일정보 스캔, 특정 확장자 및 파일 정보 찾기
`python vol.py -f [덤프 파일] --profile=WinXPSP2x86 filescan | findstr ".jpg"`

- 윈도우 : filescan | findstr “.jpg” _# 메모리에 로드 된 jpg 파일 검색_
- 리눅스 : filescan | grep “.jpg”

**dumpfiles :** 메모리에서 검색한 파일 복구
`python vol.py -f [덤프 파일] --profile=WinXPSP2x86 dumpfiles -Q [복구 파일의 메모리 주소] -D ./` _# `-D ./`은 현재 디렉토리에 파일을 덤프하겠다는 의미로 덤프관련 플러그인은 필수 옵션이다._

**memdump :** 메모리에 존재하는 프로세스 복구
`python vol.py -f [덤프 파일] --profile=WinXPSP2x86 memdump -p [PID] -D ./`

#### 커맨드 및 인터넷기록 분석

**cmdscan :** 명령 프롬프트로 실행된 정보 분석
`python vol.py -f [덤프 파일] --profile=WinXPSP2x86 cmdscan`

**consoles :** 콘솔로 실행된 정보 분석
`python vol.py -f [덤프 파일] --profile=WinXPSP2x86 consoles`

**iehistory :** 인터넷접속 기록 분석
`python vol.py -f [덤프 파일] --profile=WinXPSP2x86 iehistory`

#### 행위 분석

**userassist :** 메모리에 저장된 레지스트리 정보를 바탕으로 실행되었던 응용프로그램에 대한
정보를 분석
`python vol.py -f [덤프 파일] --profile=WinXPSP2x86 userassist`

**mftparser :** NTFS 파일시스템에서 파일의 메타데이터를 관리하는 \$MFT의 정보를 분석
`python vol.py -f [덤프 파일] --profile=WinXPSP2x86 mftparser >> mft.txt`
