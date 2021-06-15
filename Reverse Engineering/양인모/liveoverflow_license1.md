license_1 파일을 실행하면 키를 입력하라 한다. 키를 입력하니 "WRONG!" 문자열이 출력되어 키 값이 틀렸다는 것을 추측할 수 있다.
![](https://images.velog.io/images/jjewqm/post/cb3bb265-135a-41ed-9c58-15fc9ef02a6a/image.png)

GDB와 IDA를 실행해 정확한 분석을 진행한다.

# 분석

`set disassembly-flavor intel` 명령어를 실행해 인텔형 어셈블리어로 설정한다. 초기분석처럼 키를 입력하지 않으면 "Usage: <`key`>" 문자열이 출력되고 키를 입력해 키가 틀리면 "WRONG!" 문자열이 출력된다.
![](https://images.velog.io/images/jjewqm/post/a57f8415-7b57-4151-bbf8-914ef6729685/image.png)


![](https://images.velog.io/images/jjewqm/post/2962ec01-6404-4a0b-a3a1-5d73ce74d7c4/image.png)

IDA로 license1 파일을 열어 확인한 결과 인자가 2개면 키 값이 맞는지 확인하고 2개가 아니면 키를 입력하라고 출력한다. 

![](https://images.velog.io/images/jjewqm/post/f431624f-b598-428c-9bb6-ec06d4f2ee6e/%ED%99%94%EB%A9%B4%20%EC%BA%A1%EC%B2%98%202020-11-19%20161405.png)

우선 첫 조건문으로 추측되는 `cmp [rbp+var_4], 2 jnz short loc_400623` 코드에 브레이크를 걸고 실행하겠다. 
![](https://images.velog.io/images/jjewqm/post /5e0d21b6-fb91-4c45-806c-7a5a43b072f5/image.png)

실행 결과 cmp 연산 값은 0이므로 ZF에 1이 할당되어 다음 명령 <main+102> 코드로 이동한다. `mov edi, 0x400701` 코드는 `0x400701` 주소를 `edi` 레지스터에 복사한다.  
![](https://images.velog.io/images/jjewqm/post/fdbc151a-3fa4-43c5-90a7-a7d0ab2cbf16/%ED%99%94%EB%A9%B4%20%EC%BA%A1%EC%B2%98%202020-11-19%20205923.png)

`0x400701` 메모리 주소 값은 "Usage: <`key`>이다. 해당 문자열 값은 puts 함수로 출력된다.
![](https://images.velog.io/images/jjewqm/post/176a87ea-ad9f-4a17-bc09-d9fd37b223e0/image.png)

![](https://images.velog.io/images/jjewqm/post/afa62eba-8eb0-46c7-ba1f-d23529001078/image.png)

## 2차 분석

첫 조건문을 분석했다. 다음 분석은 `KEY`를 정확히 입력하면 어떻게 동작하는지 분석하겠다. IDA로 `AAAA-Z10N-42-OK` 키를 확인할 수 있다.

![](https://images.velog.io/images/jjewqm/post/2a8454f6-0034-4b30-8b34-3fe07cd46153/1.png)

키를 입력하고 `jne 0x400617 <main+90>` 코드에 브레이크 포인트를 걸었다. `test` 어셈블리어 연산 결과가 0이면 `ZF` 값이 1이 되어 `jne` 어셈블리어는 다음 명령 즉, `mov edi, 0x4006ea` 코드를 실행한다. 
![](https://images.velog.io/images/jjewqm/post/147e51df-65ef-473e-b689-2324d9f50eb0/image.png)

ni 명령어는 다음 명령 실행 후 멈추는 의미이다. ZF 값이 1이므로 `mov edi, 0x4006ea` 명령이 실행된다. 
![](https://images.velog.io/images/jjewqm/post/d64e6ba6-1867-4d3f-ad6d-57717b417b8b/image.png)

`0x4006ea` 주소 값은 "Access Granted!" 문자열로 puts 함수 출력 값으로 사용한다.
![](https://images.velog.io/images/jjewqm/post/8e9d70ea-091e-4afd-b5b2-b2846a8d04ec/image.png)

puts 함수 실행결과 "Access Granted!" 문자열이 출력된다.
![](https://images.velog.io/images/jjewqm/post/d5833d47-f4c9-409d-a619-273f5936b827/image.png)

이후 `main+112` 주소로 이동해 0을 반환하며 함수가 종료된다.

### C 코드
![](https://images.velog.io/images/jjewqm/post/00f9e253-0255-4eba-a62a-2d6e30dc7113/image.png)