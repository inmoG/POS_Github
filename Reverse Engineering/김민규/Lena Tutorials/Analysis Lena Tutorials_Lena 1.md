# Analysis: Lena Tutorials

## 개요

## 1. Analysis : Lena 1 
- ### 1-1. 분석 목표
- ### 1-2. 분석 과정
- ### 1-3. 목표 달성여부

</br></br>

# 1. Analysis : Lena 1

## 1-1. 분석 목표

![](https://images.velog.io/images/kmk9502/post/05739f6b-a651-46e6-87d9-ff31efef716a/1.%EC%8B%A4%ED%8C%A81_%ED%8C%8C%EC%9D%BC%20%EC%A1%B4%EC%9E%AC%ED%95%98%EC%A7%80%20%EC%95%8A%EC%9D%8C.png)

 - reverseMe.exe가 요구하는 조건에 알맞은 Key File을 만들어라.

## 1-2. 분석 과정

![](https://images.velog.io/images/kmk9502/post/6b9978cf-70f0-49ed-9f2c-fed603290682/2.Keyfile.dat%20%ED%8C%8C%EC%9D%BC%20%EC%A1%B4%EC%9E%AC%EC%9C%A0%EB%AC%B4%20%ED%99%95%EC%9D%B8.png)

<최초 실행시 오류 메시지를 출력하는 코드>

## 코드 분석
- ### CreateFileA() : 지정된 파일을 열거나 파일을 생성한다.
  - FileName 
    - 첫 번째 인자값, 프로그램이 위치한 경로에서 `Keyfile.dat` 파일을 대상으로 지정한다.
  - Mode
    - 다섯 번째 인자값, `OPEN_EXISTING` 모드는 지정된 파일이 **존재할 때** 여는 모드이다.
- ### EAX 레지스터 : 범용 레지스터이지만 주로 함수의 리턴값을 저장한다.
  - EAX가 -1이 아닐 경우
    - 해당 경로에 지정된 파일이 존재하며 그 파일을 여는 것이 성공
  - EAX = -1
    - -1은 0xFFFFFFFF이며 주로 함수가 목적 달성에 실패했을 때 리턴하는 값이다. 즉, 해당 경로에 파일이 존재하지 않는다는 의미이다. 
- ### JNZ
  - JCC 조건 점프 명령어 중 하나이며 `Jump if Not Zero` 의 축약어다. 
  - 주로 플래그 레지스터에 영향을 주는 연산자와 같이 쓰이며 플래그 값에 따라 코드 실행흐름을 제어한다.
    - Ex> CMP (마이너스 비트 연산자), TEST (AND 비트 연산자)
  - 즉, EAX 값이 -1일 경우 조건을 만족하지 않아 JNZ를 지나치게 되며 첫 번째 오류 메시지를 출력하는 함수를 호출한다.
## 정리
- 프로그램이 위치한 경로(현재 경로)에 `Keyfile.dat` 파일이 존재하지 않으면 오류 메시지 출력, 존재한다면 `0x40109A` 주소로 점프

</br>

![](https://images.velog.io/images/kmk9502/post/57599879-598d-4c5c-a83c-4c641155d1a1/3.%EC%A1%B0%EA%B1%B41_Keyfile.dat%20%ED%8C%8C%EC%9D%BC%20%EC%A1%B4%EC%9E%AC.png)

<조건에 따라 Keyfile.dat 파일 생성>

![](https://images.velog.io/images/kmk9502/post/b449749f-0aaa-4e23-a165-80cb135d463f/4.%EC%8B%A4%ED%8C%A82_%ED%8C%8C%EC%9D%BC%EC%9D%80%20%EC%A1%B4%EC%9E%AC%ED%95%98%EC%A7%80%EB%A7%8C%20%EB%8D%B0%EC%9D%B4%ED%84%B0%EB%8A%94%20%EC%97%86%EC%9D%8C.png)

<두 번째 오류 메시지, 파일의 경로와 이름은 일치하나 올바른 값이 아님>

</br>

![](https://images.velog.io/images/kmk9502/post/37413f6d-afeb-4c6c-840c-4be38e8240ba/5.%ED%8C%8C%EC%9D%BC%20%EB%82%B4%20%EB%8D%B0%EC%9D%B4%ED%84%B0%20%EC%A1%B4%EC%9E%AC%EC%9C%A0%EB%AC%B4%20%ED%99%95%EC%9D%B8.png)

<두 번째 오류 메시지를 출력하는 코드>

## 코드 분석
- ### ReadFile() : 열린 파일의 데이터를 읽어들이는 함수이다.
  - Buffer
    - 두 번째 인자값, 읽어들인 파일 데이터가 저장되는 버퍼 주소이다.
  - BytesToRead
    - 세 번째 인자값, 설정한 Byte 크기만큼 파일 데이터를 읽어들인다. 
    - 0x46. 즉, 70 byte를 읽어들임

- ### EAX 레지스터
    - EAX = 0
      - ReadFile()로 읽은 파일 데이터가 없다면 0을 리턴한다.
    - EAX가 0이 아닐 경우
      - 파일 데이터가 존재하며 이를 읽어 들였을 경우이다.
## 정리
- `Keyfile.dat` 파일에 데이터가 존재한다면 EAX가 0이 아니므로 `JNZ` 명령어로 0x4010B4 주소로 점프하지만, 데이터가 없다면 `JMP` 명령어로 무조건 오류 메시지를 출력하는 함수로 점프한다.

</br>

![](https://images.velog.io/images/kmk9502/post/16ab0494-1280-458e-93ea-4ec1feb2e446/6.%EC%A1%B0%EA%B1%B42_Keyfile%EC%97%90%20%EB%8D%B0%EC%9D%B4%ED%84%B0%20%EC%A1%B4%EC%9E%AC.png)

<Keyfile 파일에 임의의 값을 저장>

![](https://images.velog.io/images/kmk9502/post/69267dd8-232f-46fc-a1d1-61a29addb82a/7.%EC%8B%A4%ED%8C%A83_%EB%8D%B0%EC%9D%B4%ED%84%B0%EB%8A%94%20%EC%A1%B4%EC%9E%AC%ED%95%98%EC%A7%80%EB%A7%8C%20%EC%98%AC%EB%B0%94%EB%A5%B4%EC%A7%80%20%EC%95%8A%EC%9D%8C.png)

<임의로 입력한 값이 일치하지 않음>

</br>

![](https://images.velog.io/images/kmk9502/post/7383c7c5-3d07-48f9-b8cc-82950a138c5c/8.Key%20%EA%B0%92%20%EC%A1%B0%EA%B1%B4.png)

<오류 메시지를 출력하는 코드>

## 코드 분석
- ### 조건문 : if() 조건문의 어셈블리어 버전
  - 첫 번째 조건 : 0x4010B8 ~ 0x4010BF
    - Keyfile.dat 파일에 저장된 단어의 개수가 저장된 버퍼와 0x10. 즉, 16을 비교한다.
    - 이는 Keyfile.dat 파일에 저장된 단어가 16개 미만일 경우 오류 메시지를 출력함을 의미한다.
  - 두 번째 조건 : 0x4010CB ~ 0x4010CF & 0x4010D3 ~ 0x4010D8
    - 0x4010CB ~ 0x4010CF
      - 파일에 저장된 문자열 중 `G` 문자가 존재한다면 ESI를 1 증가시키고, 다르다면 다음 문자를 읽음을 의미한다.
    - 0x4010D3 ~ 0x4010D8
      - 문자열 내에서 `G` 문자가 총 8개 이상이라면 성공 메시지를 출력하지만, 8개 미만이라면 오류 메시지를 출력함을 의미한다.
  - 0x4010C1 ~ 0x4010C9 & 0x4010D0
    - 0x4010D0에서 EBX가 1 증가함에 따라 0x4010C1에서 [EBX+1+40211A]가 된다. </br>여기서 0x40211A 주소는 Keyfile.dat 파일에 입력한 문자열의 시작점(첫 번째 문자)을 가리키는데, EBX가 1 증가함에 따라 0x40211B가 되어 두 번째 문자를 가리키게 된다. </br>이렇게 지정된 문자는 AL에 저장되며 이러한 반복은 문자가 존재하지 않아 AL에 0이 저장될 때까지 반복된다.
## 정리
- Keyfile.dat 파일에 저장된 문자가 16개 이상이며 그중 `G` 문자가 총 8개 이상이 포함되어 있다면 성공 메시지를 출력한다.

</br>

![](https://images.velog.io/images/kmk9502/post/77973ec9-ce8e-47b4-91ae-1128c747f2e3/9.%EC%A1%B0%EA%B1%B43_%EB%AC%B8%EC%9E%90%20%EA%B0%9C%EC%88%98,%20G%EC%9D%98%20%EA%B0%9C%EC%88%98.png)

<조건에 맞는 문자열 작성>

![](https://images.velog.io/images/kmk9502/post/503912ad-8f2e-4c88-b89f-b4ce8cd15582/10.%EC%84%B1%EA%B3%B5_Keyfile%20%EA%B0%92%20%EC%9D%BC%EC%B9%98.png)

<성공 메시지 박스 출력!>