# DLL 번지 계산법

## 번지 계산 방법

    Base Address + Base of Code
    0x10000000 + 0x1000 (파일)
    -> 0x15100000 + 0x1000 (메모리)

## 파일과 실제 메모리 상의 DLL 번지가 다른 이유

- ### 고정되지 않은 DLL 로딩 주소
  DLL을 제작할 때 컴파일러는 기본적으로 0x10000000 번지를 Image Base로 지정해 준다. 이는 대부분의 DLL에 해당되는 사항이다. 만약 호출된 DLL이 저장될 0x10000000 번지를 이미 다른 DLL이 차지하고 있다면 그때는 내부적으로 다른 영역을 찾는 작업이 이루어지며, 비어 있는 메모리 공간에 DLL을 로드하게 된다. 더불어 CALL 문과 JMP 문의 상대주소를 계산하기 위한 **재배치 작업**도 이루어 진다.

    ![](https://images.velog.io/images/kmk9502/post/2dc42377-f9af-4cc9-8abf-72f40be7ef08/httpapi.dll%EC%9D%98%20image%20base.png)
    <httpapi.dll의 기본 Image Base>
    ![](https://images.velog.io/images/kmk9502/post/d22464a2-767d-450e-85d0-4eaf6ecfa7e9/mfc42.dll%EC%9D%98%20image%20base.png)
    
    <mfc42.dll의 기본 Image Base>

- ### 예외

    ![](https://images.velog.io/images/kmk9502/post/1b10f1b6-a459-49ed-9f5d-b14f0675b2eb/kernel32.dll%EC%9D%98%20Image%20Base.png)
    <kernel32.dll의 기본 Image Base>