# Sample 01.exe 분석

1. 실행파일 동작 확인
   분석을 시작하기 전에 파일을 실행시켜 보는 것이 좋다. 분석의 목적과 방향을
   설정할 수 있고, 그 외 분석에 필요한 정보를 얻을 수 있다.

## 실행 결과

![sample01-실행결과.png](https://images.velog.io/post-images/jjewqm/10373ac0-4285-11ea-b241-bd2f170b4f1c/sample01-실행결과.png)

실행 결과 비프음 소리와 함께 메시지 박스 출력을 확인했다. 실행이 된다는 것은 `Sample 01.exe`가 AntiVM 기법이 적용되어 있지 않고 32비트에서 동작하는 실행 파일이란 의미다.

# 분석 목표

- 비프음이 어떻게 발생하고, 메시지 박스는 어떻게 출력되는지 확인하기

## 코드분석\_Level.1 | 흐름 파악하기

중요! `나무를 보지말고 숲을 보기`
전체적인 흐름을 파악하는 것이 중요하다.

### StartUp 코드

![startUp코드0.png](https://images.velog.io/post-images/jjewqm/bc0b6e80-4289-11ea-8726-452aa24104a7/startUp코드0.png)

디버거에 올려보니 `0x00401030` 주소에서 멈춘다. 이 주소는 StartUP 코드이다.
StartUp 코드는 컴파일러가 실행파일을 만들 때 집어넣는 코드로 main() 함수 앞 단에 위치한다.
따라서 StartUp 코드는 건너뛰고 빠르게 main()를 찾아야 한다.

#### 디버깅 결과

![sample01-디버깅결과.png](https://images.velog.io/post-images/jjewqm/5bbf2df0-4289-11ea-9bec-2b631bf4fdeb/sample01-디버깅결과.png)

`0x004010DF` 주소에서 비프음과 메시지 박스가 실행된다. 해당 주소에 `BreakPoint`(F2)를 설치하고 실행(F9)하겠다. 그 다음 해당 함수 내부로 들어가겠다(F7).

#### 함수 내부 코드실행

![함수 내부 실행.png](https://images.velog.io/post-images/jjewqm/6437e1e0-428c-11ea-9278-d1fcd207a4e8/함수-내부-실행.png)

`0x0040100A`에서 명령어 한 개를 실행(F8)하니 비프음이 발생했다.
`0x00401024`에서 명령어 한 개를 실행하니 메시지 박스가 출력됬다.

분석 결과 `0x0040100A`주소와 `0x00401024`주소에 Beep() API, MessageBox() API가 실행됨을
알 수 있다.

## 코드분석\_Level.2 | API 호출 분석

### API

- Windows 운영체제는 비프음을 내고, 메시지 박스를 출력하는 것과 같은 `이벤트`를 발생시키고 싶을 경우 Win32 API로 전달 받아서 처리한다.

#### API 호출 분석

![beep_API.png](https://images.velog.io/post-images/jjewqm/1abc8db0-4811-11ea-8d96-e977c864a12a/beepAPI.png)

Beep() API MSDN문서를 보면 dwFreq는 `hertz`, `dwDuration`는 소리의 지속시간을 저장하는 인자이다.

함수가 정상적으로 작동하면 `0이 아닌 값`이 `return`되고 실패할 경우 `0`이 리턴된다.

#### Sample01.exe API 분석

![beep_API2.png](https://images.velog.io/post-images/jjewqm/739a7e10-4811-11ea-ade4-5d87fd8e5cb7/beepAPI2.png)

분석 파일에 저장된 값을 확인 결과 **0.768ms**, **512hertz**이다.

![beep_API3.png](https://images.velog.io/post-images/jjewqm/19c598a0-4813-11ea-808a-fd2499a972e2/beepAPI3.png)

Beep API 실행 결과 EAX 레지스터에 1이란 값이 입력된다.
운영체제가 호출 처리를 정상적으로 수행해 함수 호출에 대한 리턴 값이 EAX레지스터로 들어가게 된다. 그래서 비프음이 발생하는 것이다.

## 코드분석\_Level.3 | 파고들기

![hxd.png](https://images.velog.io/post-images/jjewqm/23d55bc0-4820-11ea-a6f2-cff7049c3a58/hxd.png)

Hxd.exe 를 사용해 분석 파일을 열어보면 실행파일 데이터를 확인할 수 있다.
실행파일의 데이터는 Microsoft에서 정한 규칙에 맞게 기록되어있으며 이것을 PE File Fomat이라 한다. PE File Format 은 ‘PE 파일이 어떻게 구성되어야 하는지에 대한 규칙’이며 크게
PE 헤더, text 섹션, data 섹션으로 나뉜다.

### PE File

![PE.png](https://images.velog.io/post-images/jjewqm/7e854d00-4820-11ea-a6f2-cff7049c3a58/PE.png)

PE 헤더는 파일을 실행시키기 위해 필요한 정보들이 기록되어 있는 영역이다.
'실행 파일이 맞는지', '실행될 때 데이터가 메모리의 어느 위치에 올라가야 하는 지'와 같은 정보가 기록된다.

- text Section - Beep()
  - MessageBoxA()
- data Section - "SecurityFactory"
  - "Hi, Have a nice day!"

![peview.png](https://images.velog.io/post-images/jjewqm/14c20910-4822-11ea-8221-4da73859da2d/peview.png)

PEView 를 사용해 분석파일의 PE 헤더를 살펴보겠다.
빨간 박스영역은 PE 헤더, SECTION.text 영역은 text섹션 그리고 rdata와 data 영역이 data섹션이다.

![image-base.png](https://images.velog.io/post-images/jjewqm/7d2beca0-4822-11ea-a6f2-cff7049c3a58/image-base.png)

Image Base는 파일데이터가 `메모리 어디에 올라갈지` 기록하는 영역 즉 메모리에서 분석파일의 위치이다.
`Address of Entry Point`와 `Image Base`가 더해진 주소가 코드 시작주소이다.

![00401030.png](https://images.velog.io/post-images/jjewqm/1d595370-4823-11ea-a70e-e13598bae77a/00401030.png)

디버깅결과 Startup 코드인 `0x00401030`가 코드시작주소임을 알 수 있다.

### Memory Map

`Alt+M`을 입력하면 Memory Map으로 이동한다.

![memoryMap01.png](https://images.velog.io/post-images/jjewqm/e506ba20-4823-11ea-841e-717d6f58d90d/memoryMap01.png)

Memory Map을 확인하면 Image Base 주소 `0x00400000`가 있다. 이 주소는 분석파일의 위치이다.
분석결과 PE 헤더는 파일을 실행시키기 위한 정보들을 담고있다.

### DLL (동적 연결 라이브러리)

![dll.png](https://images.velog.io/post-images/jjewqm/7d97e2f0-4824-11ea-841e-717d6f58d90d/dll.png)

PE 헤더 밑으로 내려가보면 DLL 파일들이 존재한다.
DLL은 간단히 설명하면 EXE 동작을 보조하는 비서이다.
Windows 운영체제는 EXE 파일을 도와주려고 `DLL`을 제공한다. EXE 파일이 모든 동작을 수행하지 않고 `DLL`에게 특정 동작을 요청해 `비프음 발생` 같은 `이벤트`가 발생한다.
이 `특정동작을 요청하는 행위`가 `API 호출`이다.

## 코드분석\_Level.4 | 분석행위 구현

분석파일의 중요동작을 코딩해 파일이 어떻게 동작하는지 확인하겠다.

### 중요 행위

1. 비프음 발생
2. 메시지 박스 출력

분석파일은 Beep(), MessageBoxA() API를 사용해 두 개의 행위가 발생했다.
이제 직접 코딩해 동작을 확인하겠다.

### Coding

```
# include <Windows.h>

int main()
{
	Beep(0x200, 0x300);
	MessageBoxA(0, "Hi, Have a nice day!", "SecurityFactory", 0);

    return 0;
}
```

![릴리즈.png](https://images.velog.io/post-images/jjewqm/e67ad800-482d-11ea-81e1-79cd3f96fe24/릴리즈.png)

릴리즈 모드로 실행파일을 생성하였고, 실행결과 분석파일과 동일한 동작을 수행한다.
![sample01_코딩결과.png](https://images.velog.io/post-images/jjewqm/46e21aa0-482e-11ea-b304-4b2307a19410/sample01코딩결과.png)

---

본 글은 '리버싱 이정도는 알아야지' 인프런 강의를 정리합니다.
