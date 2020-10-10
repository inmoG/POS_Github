# 메모리 구조

![](https://images.velog.io/images/kmk9502/post/5436236c-33e2-408a-bd19-e2cfd9f75174/%EB%A9%94%EB%AA%A8%EB%A6%AC%20%EA%B5%AC%EC%A1%B0.png)

- ## 컴파일 타임에 크기 결정
  - ### 스택(Stack)
    - 함수 호출 시 생성되는 `지역 변수`와 `매개 변수(인자 값)` 등이 저장되는 영역 
    - 높은 주소에서 낮은 주소로 증가
    - 함수가 종료되면 할당된 영역이 사라짐
    - LIFO 구조
      - Last In First Out의 약자로, 마지막으로 들어온 값이 먼저 나감
- ## 실행할 때에 크기 결정 (Run time에 크기 결정)
  - ### 힙(Heap)
    - 동적으로 메모리 할당 시 사용하는 영역, 즉 프로그래머가 Heap 영역에 직접 메모리를 할당할 때 사용한다.
    - 낮은 주소에서 높은 주소로 증가 (동적으로 할당하는 만큼 증가)
    - Heap 영역에 메모리를 할당하기 위한 명령어가 따로 있다.
- ## Data 영역
  - 문자열, 전역변수(global), 정적변수(static), 배열(array), 구조체(structure) 등의 변하지 않는 값들이 저장된다.
  - 프로그램이 실행 될 때 생성되고 프로그램이 종료 되면 시스템에 반환 된다.
    - ### .data 영역
      - 초기화 된 데이터가 저장된 영역
    - ### .bss (Block Stated Symbol) 영역
      - 초기화 되지 않은 데이터가 저장된 영역
- ## Code 영역
  - 코드 자체가 저장된 메모리 영역이다.
  - 코드가 어셈블리 언어로 번역되어 저장된다.

<디버거에서 볼 수 있는 영역>

![](https://images.velog.io/images/kmk9502/post/733e4f7c-f4b8-4c70-87c4-c3a3c26e9eab/%EB%94%94%EB%B2%84%EA%B1%B0%EC%99%80%20%EB%A9%94%EB%AA%A8%EB%A6%AC%20%EA%B5%AC%EC%A1%B0%20%EC%97%B0%EA%B4%80%EC%84%B1.png)

</br></br></br></br>

# 주소 표기법

![](https://images.velog.io/images/kmk9502/post/2d512371-24d2-41cd-a7a0-6fd6e0bd096b/%EC%A3%BC%EC%86%8C%20%ED%91%9C%EA%B8%B0%EB%B2%95_%EB%A6%AC%ED%8B%80%20%EC%9D%B8%EB%94%94%EC%96%B8_%EB%B9%85%20%EC%9D%B8%EB%94%94%EC%96%B8%20.png)

- ## 리틀 인디언
  - 우리가 보통 읽고 쓰는 방법과는 반대로 데이터를 저장
  - 주로 인텔 프로세서 계열에서 많이 사용하는 byte 순서
  - 메모리 시작 주소를 하위 byte부터 기록
  - 디버거의 DATA DUMP에서 볼 수 있다.
- ## 빅 인디언
  - 우리가 보통 읽고 쓰는 방법과 같은 방법을 데이터를 저장
  - 주로 유닉스 시스템인 RISC 프로세서 계열에서 사용하는 byte 순서
  - 메모리 시작 주소를 상위 byte부터 기록
  - 네트워크 패킷에서도 이 방식을 사용

</br></br></br></br>

# arm 아키텍처

- ## 요약
  - 데이터 타입 : 어셈블리 기본
  - 주소 표기법 : 명령어는 리틀 인디언, 데이터는 `혼합 사용 (리틀 인디언과 빅 인디언 혼합 사용)`
  - 레지스터 : 13개의 범용 레지스터, 3개의 특수 레지스터
  - 명령어 세트 : `고정 길이 명령어` 형식을 사용
  - 피연산자 : 레지스터, 메모리 주소, 주소값, 숫자
  - 기본 문법 : `모든 작업은 레지스터에서 수행`, Load / Store 구조(Load : 메모리 -> 레지스터 / Store : 레지스터 -> 메모리)
  - 주로 임베디드 장비에 많이 쓰인다.

- ## ARM 레지스터 
  - 13개의 범용 레지스터 + 3개의 특수 레지스터
  - CPSR 레지스터 : Current Program Status Register의 약자로, `x86의 flag 레지스터와 동일한 기능`
  
    ![](https://images.velog.io/images/kmk9502/post/3e634ac0-2ecc-44d9-a7cd-efb021de14f8/CPSR%20%EB%A0%88%EC%A7%80%EC%8A%A4%ED%84%B0%20%EA%B5%AC%EC%A1%B0.png)

    - ### Fleg Field
      - N : 연산 결과가 음수인 경우 활성화
      - Z : 연산 결과가 0인 경우 활성화
      - C : 연산 결과에 자리올림이 발생했을 때 활성화
      - V : 연산 결과가 overflow 됐을 경우 활성화
      - Q : 포화 상태일 때 활성화, 이 때 반드시 Clear 필요
      - J : 자바 byte 코드 실행 상태
    - ### Control bit
      - I가 1인 경우 : IRQ 비활성화 상태
      - F가 1인 경우 : FIQ 비활성화 상태
      - T가 1인 경우 : Thumb mode 활성화 </br> T가 0인 경우 : ARM mode 활성화
    - ### Mode bit
      - 10000 : USR mode
      - 11111 : SYS mode
      - 10001 : FIQ mode
      - 10010 : IRQ mode
      - 10011 : SVC mode
      - 10111 : ABT mode
      - 11011 : UND mode
    - ### 예시
      - 0x80000010 => 1000 0000 0000 0000 0000 0000 0001 0000 => 32번째, 5번째 자리가 1 = N, USR mode 활성화
    - ### Thumb mode / ARM mode
      - ARM mode
        - 처리속도를 우선시 할 때 사용
        - 일반적으로 사용하는 모드
        - 명령어 크기는 4byte로, 비교적 크다.
        - ARM은 32bit 프로세서이며 16bit 명령어를 처리하기 위해선 처리과정을 한 번 더 거치게 된다. (즉, 효율성이 감소)
      - Thumb mode
        - 프로그램의 크기를 줄일 때 사용
        - ARM 모드로 작성한 프로그램의 크기의 70%밖에 되지 않는다.
        - 명령어 크기가 2byte로, 비교적 작다.
        - ARM 모드에서 쓸 수 있지만 Thumb 모드에선 쓸 수 없는 명령어가 존재한다.
  </br></br>

  - SPSR 레지스터 : Saved Program Status Register의 약자로, `Mode가 바뀔 때 이전 모드의 CPSR을 백업하는 역할을 한다.` USR / SYS mode를 제외한 나머지 mode에 공통으로 존재한다.
  - ### Mode
    - Exception이 발생하면 진행하던 동작을 멈추고 `Exception의 종류에 해당하는 mode에 진입`하고 </br>그 `mode에 해당하는 주소로 pc를 jump` 시킨 후 Exception에 대한 처리를 한다.
      - Exception?
        - interrupt를 포함한 더 큰 사건, 즉 외부 요청 혹은 오류에 관련된 사건
      - Interrupt?
        - 시스템의 원활한 작업 수행에 방해가 되는 SW / HW적인 방해요소
    - mode에 따라 사용할 수 있는 레지스터가 다르다.
    - User mode에서는 CPSR의 Control Field를 제어할 수 없는 Read only (읽기 전용)이다.
    - User mode에서 CPSR의 Flag Field는 읽기 / 쓰기 모두 가능하다.
  
- ## R13(=SP)
  - 스택의 최상단 주소를 가리키는 레지스터
  - x86의 SP(Stack Pointer)와 동일한 기능
- ## R14(=LR)
  - 서브루틴 진입 시 `서브루틴 함수 종료 후 복귀할 주소(PC) ` 저장을 위해 사용하는 레지스터
  - x86의 BP(Base Pointer)와 동일한 기능
- ## R15(=PC)
  - 다음 실행할 명령어 주소를 저장하는 레지스터
  - x86의 IP(Instruction Pointer)와 동일한 기능
    
