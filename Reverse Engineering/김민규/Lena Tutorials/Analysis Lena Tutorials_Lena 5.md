# Analysis: Lena Tutorials

## 개요

## 2. Analysis : Lena 5
- ### 2-1. 분석 목표
- ### 2-2. 분석 과정
- ### 2-3. 목표 달성여부

</br></br>

# 2. Analysis : Lena 5

## 분석 대상

</br>

![](https://images.velog.io/images/kmk9502/post/4a0971f8-642b-4087-b407-ab848b5c037f/%EB%AC%B8%EC%A0%9C1_1_%EC%B2%B4%ED%97%98%ED%8C%90%20%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%A8.png)

<분석 대상 프로그램 : VisualSite Designer.exe : 체험판 모드>

![](https://images.velog.io/images/kmk9502/post/94f0f66d-8343-423a-865b-62ae70c9727f/%EB%AC%B8%EC%A0%9C1_%ED%8E%98%EC%9D%B4%EC%A7%80%20%EC%83%9D%EC%84%B1%20%EC%A0%9C%ED%95%9C.png)

<첫 번째 목표 : 페이지 추가  제한 해제>

![](https://images.velog.io/images/kmk9502/post/0305f828-bca9-40f2-b892-6ab8aa3c499e/%EB%AC%B8%EC%A0%9C2_%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%A8%20%EC%A2%85%EB%A3%8C%ED%9B%84%20%EA%B4%91%EA%B3%A0%EC%B0%BD%20%EC%B6%9C%EB%A0%A5.png)

<두 번째 목표 : 프로그램 종료 후 출력되는 광고창 제거>

![](https://images.velog.io/images/kmk9502/post/c5c25606-355a-40b4-8533-fc8b6750d67a/%EB%AC%B8%EC%A0%9C3_%EC%B2%B4%ED%97%98%ED%8C%90%20%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%A8%20%EC%8B%A4%ED%96%89%20%ED%9A%9F%EC%88%98%20%EC%A0%9C%ED%95%9C.png)

<세 번째 목표 : 체험판 프로그램 만료 해제>

- - -

</br>

## 2-1. 분석 목표 : 페이지 추가  제한 해제

![](https://images.velog.io/images/kmk9502/post/94f0f66d-8343-423a-865b-62ae70c9727f/%EB%AC%B8%EC%A0%9C1_%ED%8E%98%EC%9D%B4%EC%A7%80%20%EC%83%9D%EC%84%B1%20%EC%A0%9C%ED%95%9C.png)

<첫 번째 목표 : 페이지 추가  제한 해제>

## 2-2. 분석 과정

### 1. 첫 번째 분석목표 : 10개의 페이지까지 추가 가능한 제한 해제

</br>

![](https://images.velog.io/images/kmk9502/post/d147e94c-2359-44b6-ba7d-e7eaa8309709/%EB%AC%B8%EC%A0%9C1_%EB%AC%B8%EC%A0%9C%20%ED%8C%8C%EC%95%851_K%20%EB%A9%94%EB%89%B4.png)

<F9(실행) -> 분석 목표 고정 -> F12(정지) -> 상단 'K' 메뉴>

## 함수 분석
  - ### 페이지 추가 제한 메시지 출력함수 : 0x47DC03
    - 페이지 추가 제한 메시지 박스가 출력된 상태로 고정한 뒤 정지했기 때문에 응용 프로그램 영역에서 가장 최근 호출된 함수인 0x47DC03 주소가 답이다.

</br>

![](https://images.velog.io/images/kmk9502/post/4d6e851a-84ce-44f5-8b52-291d4f205136/%EB%AC%B8%EC%A0%9C1_%EB%AC%B8%EC%A0%9C%20%ED%8C%8C%EC%95%852_%EB%AC%B8%EC%A0%9C%20%EC%BD%94%EB%93%9C%20%EB%B0%9C%EA%B2%AC.png)

<페이지 추가 제한 메시지를 출력하는 코드>

## 코드 분석
- ### 0x47DC03 : 메시지 출력 함수를 호출한다.
- ### CMP ESI, 0A
  - 0x0A는 10진수로 환산하면 10이므로 10개까지 페이지 생성이 가능한 제한의 원인으로 추정할 수 있다.
  - 따라서 ESI는 현재 생성한 페이지의 개수이며 이를 10과 비교해 같다면 ZF가 활성화되어 0x47DC03에 의해 제한 메시지가 출력될 것이다. 
- ### JNZ 47DC35
  - CMP 연산결과가 ZF를 활성화 하지 않는다면(0이 아니라면) 페이지를 생성하는 함수로 점프할 것이다.

## 정리
- ESI에 현재 페이지의 개수를 저장하고 이를 10과 비교 연산하여 10과 같다면 제한 메시지를 출력하고 10 미만이라면 페이지를 추가 생성한다.

</br>

![](https://images.velog.io/images/kmk9502/post/8667d7dc-b0f2-4cef-acf0-0dda1a8d6c48/%EB%AC%B8%EC%A0%9C1_%EB%8C%80%EC%9D%91_JMP.png)

<조건 점프를 무조건 점프로 수정>

## 코드 분석
- ### JMP 47DC35
  - 기존 JNZ는 CMP 연산결과에 따라 점프 실행을 결정한다. 하지만 JMP는 조건이 없는 점프 명령어이기 때문에 CMP 연산결과에 영향을 받지 않고 페이지 생성 함수로 점프할 수 있다.

</br>

![](https://images.velog.io/images/kmk9502/post/301c63cb-35b9-45fa-aa3e-3c30c7704501/%EB%AC%B8%EC%A0%9C1_%EB%8C%80%EC%9D%91_%EB%8B%A4%EB%A5%B8%EC%9D%B4%EB%A6%84%EC%9C%BC%EB%A1%9C%20%EC%A0%80%EC%9E%A5.png)

<수정한 파일을 다른 이름으로 저장>

</br>

## 2-3. 목표 달성여부

![](https://images.velog.io/images/kmk9502/post/e86ee738-af1e-4542-92e9-3e2f7ca49c54/%EB%AC%B8%EC%A0%9C1_%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%A8%20%EC%9E%AC%EC%8B%A4%ED%96%89_%ED%8E%98%EC%9D%B4%EC%A7%80%20%EC%B6%94%EA%B0%80%20%EC%A0%9C%ED%95%9C%20%ED%95%B4%EC%A0%9C.png)

<10개를 초과한 페이지 : 성공>

- - -

</br>

## 2-1. 분석 목표 : 프로그램 종료 후 출력되는 광고창 제거

![](https://images.velog.io/images/kmk9502/post/0305f828-bca9-40f2-b892-6ab8aa3c499e/%EB%AC%B8%EC%A0%9C2_%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%A8%20%EC%A2%85%EB%A3%8C%ED%9B%84%20%EA%B4%91%EA%B3%A0%EC%B0%BD%20%EC%B6%9C%EB%A0%A5.png)

<프로그램 종료 후 광고창 출력>

## 2-2. 분석 과정 

![](https://images.velog.io/images/kmk9502/post/c189f4d9-a76c-4e63-8cb3-46b6d74ace8f/%EB%AC%B8%EC%A0%9C2_%EB%AC%B8%EC%A0%9C%20%ED%8C%8C%EC%95%851_K%20%EB%A9%94%EB%89%B4.png)

<F9(실행) -> 분석 목표 고정 -> F12(정지) -> 상단 'K' 메뉴>

## 함수 분석
  - ### 광고창 출력함수 : 0x480C24
    - 광고창이 출력된 상태로 고정한 뒤 정지했기 때문에 응용 프로그램 영역에서 가장 최근 호출된 함수인 0x480C24 주소가 답이다.

</br>

![](https://images.velog.io/images/kmk9502/post/53ef0ea4-0085-44ca-ac87-6f239a120d27/%EB%AC%B8%EC%A0%9C2_%EB%AC%B8%EC%A0%9C%ED%8C%8C%EC%95%852_%EB%AC%B8%EC%A0%9C%20%EC%BD%94%EB%93%9C%20%EB%B0%9C%EA%B2%AC.png)

<함수로 진입>

## 코드 분석 : 문제 발생
-  CMP, JCC 등의 흐름제어 명령어가 존재하지 않음
- JNZ 명령어를 같은 JCC 명령어에 포함되는 JE로 수정할 때 명령어의 크기의 변화가 없어 코드에 이상이 발생하지 않지만, MOV 등 다른 종류의 명령어를 JCC 명령어로 수정할 경우 크기가 맞지 않아 일부 정상코드가 `NOP` 처리가 되어 오류를 유발한다.

</br>

![](https://images.velog.io/images/kmk9502/post/5eae4136-e1be-41d7-a8e3-d131aee6e372/%EB%AC%B8%EC%A0%9C2_%EB%8C%80%EC%9D%91_NOP.png)

<광고창 출력함수를 NOP으로 처리>

## 코드 분석 : 문제 해결
- 기존 광고창을 출력하는 CALL 명령어 자체를 NOP으로 처리하여 광고창 출력 자체를 무시한다.
- 호출 함수 외 다른 명령어를 수정하지 않기 때문에 오류는 발생하지 않는다.

</br>

![](https://images.velog.io/images/kmk9502/post/17c149c0-b7ed-4a40-a6c5-f3d35f8fe7ed/%EB%AC%B8%EC%A0%9C2_%EB%8C%80%EC%9D%91_%EB%8B%A4%EB%A5%B8%EC%9D%B4%EB%A6%84%EC%9C%BC%EB%A1%9C%20%EC%A0%80%EC%9E%A5.png)

<수정본을 다른 이름으로 저장>

</br>

## 2-3. 목적 달성여부
- ### PPT의 P.32에서 동영상으로 확인 가능

- - -

</br>

## 2-1. 분석 목표 : 체험판 프로그램 만료 해제

![](https://images.velog.io/images/kmk9502/post/c5c25606-355a-40b4-8533-fc8b6750d67a/%EB%AC%B8%EC%A0%9C3_%EC%B2%B4%ED%97%98%ED%8C%90%20%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%A8%20%EC%8B%A4%ED%96%89%20%ED%9A%9F%EC%88%98%20%EC%A0%9C%ED%95%9C.png)

<체험판 프로그램 만료 메시지>

- 체험판 프로그램을 10회 실행할 경우 다음 실행부터 프로그램을 구매하지 않으면 프로그램을 실행할 수 없게 된다.

## 2-2. 분석 과정

![](https://images.velog.io/images/kmk9502/post/8475c6bf-2ab8-458d-92bf-b3d3b8e82d46/%EB%AC%B8%EC%A0%9C3_%EB%AC%B8%EC%A0%9C%ED%8C%8C%EC%95%85%201_K%20%EB%A9%94%EB%89%B4.png)

<F9(실행) -> 분석 목표 고정 -> F12(정지) -> 상단 'K' 메뉴>

## 함수 분석
  - ### 만료 메시지 출력함수 : 0x4899B3
    - 만료 메시지가 출력된 상태로 고정한 뒤 정지했기 때문에 응용 프로그램 영역에서 가장 최근 호출된 함수인 0x4899B3 주소가 답이다.

</br>

![](https://images.velog.io/images/kmk9502/post/cde6db21-2dd9-4338-bee5-800bacd22259/%EB%AC%B8%EC%A0%9C3_%EB%AC%B8%EC%A0%9C%ED%8C%8C%EC%95%852_%EB%AC%B8%EC%A0%9C%20%EC%BD%94%EB%93%9C%20%EB%B0%9C%EA%B2%AC.png)

<만료 메시지 출력 코드>

## 코드 분석
- ### 프로그램 만료 전
  - 0x4899B3에서 호출하는 함수에서 만료 여부를 판단한 결과, 만료 이전이라면 [구매] or [실행] 선택창을 출력한다.
    - [구매]를 선택하면 함수 내 링크를 통해 사용자를 구매 사이트로 이동시킨다.
    - [실행]을 선택하면 EAX에 리턴값 1을 저장한 뒤 함수 밖으로 나와 CMP EAX, 1 비교연산을 거쳐 점프한 뒤 프로그램을 실행한다.
- ### 프로그램 만료 후
  - 0x4899B3에서 호출하는 함수에서 만료 여부를 판단한 결과, 만료 후일 경우 [구매] or [종료] 선택창을 출력한다.
    - [구매]를 선택하면 프로그램 만료 전과 동일하게 작동한다.
    - [종료]를 선택하면 EAX에 리턴값 -1을 저장한 뒤 함수 밖으로 나와 비교연산을 거쳐 점프를 지나친 뒤 프로그램을 종료한다.

## 정리
- JE(Jump if Equal) 명령어를 통해 만료 전 [실행]을 선택하면 프로그램 정상동작, 만료 후 [종료]를 선택하면 프로그램 종료

</br>

![](https://images.velog.io/images/kmk9502/post/417cc4f9-222c-413e-aab6-aae8fb65e2e9/%EB%AC%B8%EC%A0%9C3_%EB%8C%80%EC%9D%91_NOP,%20JMP.png)

<만료 여부 판단 및 메시지 출력 함수를 NOP으로 처리 & 조건점프를 무조건 점프로 수정>

## 코드 분석
  - 만료 여부 판단 및 메시지 출력 함수를 NOP으로 처리했지만 동시에 조건 점프를 무조건 점프로 수정하여 만료 여부와 관계 없이 무조건 프로그램 실행이 가능하다.

</br>

![](https://images.velog.io/images/kmk9502/post/c6cb7e25-24f1-477c-a741-0aad32c7c6cd/%EB%AC%B8%EC%A0%9C3_%EB%8C%80%EC%9D%91_%EB%8B%A4%EB%A5%B8%EC%9D%B4%EB%A6%84%EC%9C%BC%EB%A1%9C%20%EC%A0%80%EC%9E%A5.png)

<수정본을 다른 이름으로 저장>

</br>

## 2-3. 목표 달성여부
- ### PPT의 P.39에서 확인 가능