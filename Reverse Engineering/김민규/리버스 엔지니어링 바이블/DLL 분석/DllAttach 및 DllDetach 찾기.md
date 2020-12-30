# DllAttach 및 DllDetach 찾기

# 배경지식

## DllMain() 함수
- ### 정의
  - Dll의 엔트리 포인트(시작점)에 해당하며 DLL 전체(프로세스, 스레드)의 초기화와 종료 처리를 담당한다(보통 초기화와 </br>종료 처리를 할 시기에 맞게 개발자가 정의한다).  
  - 만약 C계열의 프로그램에서만 활용 가능한 DLL을 제작한다고 하면 DllMain()은 생략해도 괜찮다. </br>왜냐하면 C 런타임 라이브러리와 링크할 경우 C 런타임이 자동으로 기본 DllMain()을 만들어주기 때문이다.

- ### DllMain()의 원형
        BOOL WINAPI DllMain(HINSTANCE hInst, DWORD fdwReason, LPVOID lpRes);

## DllAttach 및 DllDetach 기능
- ### DLL_PROCESS_ATTACH
  - DllMain() 에서 정의할 수 있다.
  - DLL이 프로세스(메인 스레드)에 올라갔을 때 호출된다.
  - 주로 메모리를 할당하거나 시스템 전역 핸들을 초기화 하는 데 사용된다.
- ### DLL_PROCESS_DETACH
  - DllMain() 에서 정의할 수 있다.
  - DLL이 프로세스에서 분리될 때 호출된다.
  - DLL_PROCESS_ATTACH 에서 할당된 메모리를 해제하거나 시스템 전역 핸들을 제거하는 데 사용된다.

## DllAttach 및 DllDetach의 기본 구조

- ### DllMain() 내의 fdwReason을 이용한 스위치 케이스 문

        BOOL WINAPI DllMain(HINSTANCE hInst, DWORD fdwReason, LPVOID lpRes)
        {
            switch(fdwReason)
            [
                case DLL_PROCESS_ATTACH:
                    lpBuffer = (LPBYTE)malloc(sizeof(LPBYTE)); // 메모리 할당
                    break;
                case DLL_PROCESS_DETACH:
                    free(lpBuffer); // free 함수를 이용해 할당된 메모리 해제
                    break;
            ]
            return TRUE;
        }

---

# 본론

## 어셈블리 코드에서 DllAttach 및 DllDetach 찾기

위의 코드를 빌드하면 다음과 같은 코드가 생성된다.

    00BB1030   mov eax, dword ptr ss:[esp+8]
    00BB1034   sub eax, 0                       ; Switch case가 0인지 확인
    00BB1037   je short Dll.00BB1053
    00BB1039   dec eax                          ; Swutch case가 1인지 확인
    00BB103A   jnz short Dll.00BB1061
    00BB103C   push 4                           ; case 값이 1일 때 실행 ; 메모리 동적 할당 크기 = 4byte
    00BB103E   call Dll.00BB10B1                ; malloc() 함수
    00BB1043   mov dword ptr ds:[BBAD08], eax
    00BB1048   add esp, 4
    00BB104B   mov eax, 1
    00BB1050   retn 0C
    00BB1053   mov eax, dword ptr ds:[BBAD08]   ; case 값이 0일 때 실행
    00BB1058   push eax
    00BB1059   call Dll.00BB11EB                ; free() 함수 호출
    00BB105E   add esp, 4
    00BB1061   mov eax, 1                       ; Default case ; 0과 1 외의 case 값일 때 실행
    00BB1066   retn 0C

- ### Switch case 문을 통해 DllAttach 및 DllDetach 찾기
  - ### 만약 DllAttach 및 DllDetach을 사용한 DLL이라면 
    - 위의 어셈블리 코드와 같이 eax에 0,1,2,3 등의 값이 담기고 이 값이 조건에 부합한지 확인한 뒤 조건 일치 여부에 따라 적절한 코드가 실행되는 **Switch case 문**을 확인할 수 있다.
    - 또한, 조건에 따라 점프한 곳에서 메모리를 할당하거나 free() 등의 함수를 호출하여 할당된 메모리를 해제하는 코드를 발견하면 DllMain()에서 DllAttach 및 DllDetach를 사용한 DLL이라는 것을 알 수 있다.
  - ### 주석 없이 어셈블리 코드만 보고 DllAttach와 DllDetach를 쉽게 판별할 수 있나?
    - 핵심을 짚어보면서 코드를 파악하는 '감'을 키워야 한다.
    - 위 코드의 핵심   
      - DLL 내부 / 엔트리 포인트부터 존재하는 코드는 DllMain() / eax에 0,1,2,3 등의 값이 담기고 이 값으로 조건을 비교하는 특징이 Switch case 문과 유사함
    - 메모리 할당 혹은 해제 코드를 간단히 판별하는 방법은?
      - 1. DLL의 IAT에서 메모리 할당 혹은 해제 API를 찾는다. : 간단함, 그러나 API로 구현하지 않았다면 알 수 없음.
      - 2. 호출 함수로 진입하여 해당 함수의 동작을 분석한다. : 어려움, 그러나 API가 아닌 코드로 작성되었다면 효과적이다.