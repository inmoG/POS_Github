프로토스타 stack0 문제는 BOF 취약점과 이 취약점이 발생하는 gets()함수 관련한 문제이다. BOF는 Buffer OverFLow 약자로 메모리에 지정된 크기의 공간을 벗어나 다른 메모리를 수정할 수 있는 취약점이다. 버퍼 길이를 검사하지 않는 함수를 사용할 때 이런 취약점이 발생하며 해당 문제에서는 gets() 함수를 사용해 해당 취약점을 확인한다.

# 분석
0번 문제 파일을 실행하면 아무 반응이 없다. 데이터를 입력하고 실행하니 "Try again" 문자열이 출력된다. 따라서 0번 문제는 값을 입력하면 출력하는 형태로 추측할 수 있다.

![](https://images.velog.io/images/jjewqm/post/81fb8c71-3e18-4dcf-ad23-0b364f820723/image.png)

## 소스코드 분석
![](https://images.velog.io/images/jjewqm/post/e3b82cee-85fd-4425-9f82-3dd90add08f8/image.png)

4바이트 크기의 modified 변수에 0을 할당하고 64바이트 크기의 buffer 변수를 선언한다. buffer 변수는 gets 함수를 통해 사용자 입력 값을 buffer 변수에 저장한다. modified 변수가 0이면 "Try again?" 문자열을 출력하고 0이 아니면 "you have changed the 'modified' variable' 문자열을 출력한다.

## 스택 구조
스택은 데이터 구조의 하나로써 데이터를 1열로 나열하지만, 서류를 쌓아 놓은 경우처럼 **새롭게 추가한 데이터**에만 접근할 수 있다. 스택은 아래부터 위로 쌓이는 구조이기 때문에 위에서부터 데이터가 삭제되어 최신 데이터만 접근할 수 있다. 스택에 데이터가 들어가는 현상을 **push**, 스택에서 데이터가 나오는 현상을 **pop**이라 한다.

![](https://images.velog.io/images/jjewqm/post/a750701e-188b-4260-b55f-ddb05a42dfe5/image.png)

스택 아래 부분은 bottom, 위 부분은 top이라 부르며 bottom을 기준으로 스택이 쌓인다. 데이터를 입출력하면 bottom은 바뀌지 않고 **top만 데이터 양에 따라 움직인다.** 운영체제는 top을 ESP 레지스터로, bottom을 EBP 레지스터로 항상 가리킨다.

![](https://images.velog.io/images/jjewqm/post/5665a526-981f-441a-a04f-708f1ea21bd2/image.png)

스택은 운영체제 지역변수를 할당하고 함수 실행 규약에 따라 사용한다. 메인 함수가 지역변수를 할당할 때마다 그 변수는 아래에 깔리고 위에 하나씩 쌓인다. stack0은 modified 변수를 먼저 선언하기 때문에 아래에 가고 buffer는 그 다음에 할당돼 위에 존재한다.

함수는 호출에서 사용되는 파라미터와 나중에 돌아올 주소까지 스택에서 관리한다. 그리고 스택은 스택 프레임이라는 영역에 임의로 함수를 EBP와 Ret를 기준으로 나눠 구별한다. 그러나 스택 안에 함수마다 별도의 스택이 생성되는 것은 아니다.
CALL이라는 어셈블리어로 함수를 실행하면 함수를 실행한 뒤에 돌아갈 주소를 미리 스택에 저장한다. 예를 들어 main함수에서 A 함수를 실행하면 함수가 종료되고 main으로 돌아오는데 미리 스택에 돌아갈 주소를 저장했기에 가능한 일이다. 따라서 A 함수가 종료되면 주소로 돌아와 다음 명령어를 실행한다. 이러한 일을 `ret`가 수행한다. 메모리 크기에 따라 32bit 환경에서는 4바이트, 64bit 환경에서는 8byte 크기를 갖는다. ebp는 베이스 포인터로 스택의 bottom을 가리킨다. ebp를 저장하는 이유는 bottom을 복구하기 위해서다. 함수가 종료되면 ebp를 복구하려고 스택에 저장한 ebp를 사용한다. 복구한 epb를 사용해 다음 스택 프레임을 사용할 수 있다.

## GDB 분석
인텔형 어셈블리어로 볼 수 있게 `set disassembly-flavor intel` 설정한다. `disas main` 명령어로 메인함수를 디스어셈블한다. 

![](https://images.velog.io/images/jjewqm/post/c126b7d7-6d4d-4ffe-8878-ac9bd681e8e2/image.png)

0-3줄은 함수 프롤로그이다. 함수 프롤로그는 함수가 실행될 때 실행 후에 돌아갈 위치와 스택 구조 최하위를 가리키는 어셈블리어이다. 
- push ebp 
ebp를 스택에 저장한다.
- mov ebp, esp
현재 esp 위치에 ebp를 끌어올린다.


### 함수 프롤로그 전과 후
![](https://images.velog.io/images/jjewqm/post/b0c274be-582b-4c13-8f88-d249cd131113/image.png)

프롤로그 실행 전에는 스택프레임이 하나이다. 실행 직후에는 top과 bottom이 같은 자리를 가리킨다. 그리고 함수 내에서 사용된 변수들은 노란 영역에서 사용되며 이때 스택프레임은 두 개이다.

## 2차 분석
- sub esp, 0x60

    스택의 top을 지정하는 esp 레지스터에 main 함수가 사용할 60(10진수:96)을 빼고 그 결과를 esp 레지스터에 저장한다. 즉 60만큼 공간을 할당해 스택 높이를 올려 저장한다. 브레이크 포인트를 걸어 esp 레지스터 값이 어떻게 변화하는지 알아보겠다. 0x080483fa 주소에 브레이크 포인트를 걸고 esp 레지스터 값을 확인하면 0xffffd670 값이 존재한다. 


    ![](https://images.velog.io/images/jjewqm/post/dd6148a2-50aa-4a66-99b1-4d3b2f9e3468/image.png)

    0x080483fd 주소에 브레이크 포인트를 걸고 esp 레지스터 값을 확인하면 60이 빠져서 0xffffd610 값이 존재한다. 

    ![](https://images.velog.io/images/jjewqm/post/7614ad28-0371-45fa-bd0d-2a5f0ae4e3d8/image.png)

- mov DWORD PTR [esp+0x5c],0x0
`esp+0x5c` 주소에 0을 넣는다. 코드를 보면 0을 넣는 부분은 `modified = 0` 이다. 따라서 modified 변수 주소는 `[esp+0x5c]`이다.

    ![](https://images.velog.io/images/jjewqm/post/e3b82cee-85fd-4425-9f82-3dd90add08f8/image.png)

- lea eax, [esp+0x1c]
- mov DWORD PTR [esp], eax
- call 0x804830c <<gets@plt>>
gets 함수에 사용할 파라미터로 eax 레지스터에 저장된 esp+0x1c 값을 저장한다. gets 파라미터로 전달된 이 주소에 gets로 받아들이는 사용자 입력이 저장된다. 따라서 esp+0x1c 위치가 buffer 변수의 주소이다. 

- mov eax, DWORD PTR [esp+0x5c]
esp+0x5c 주소에는 0이 저장되어 있다. 정말 0이 들어있는지 eax 레지스터 값을 확인하겠다.

    ![](https://images.velog.io/images/jjewqm/post/06edab01-c35b-4367-bf28-1d1c0917b2ea/image.png)

- test eax,eax
test 명령어는 and 연산을 수행해 결과가 0이면 ZF가 1이 되고 1이면 ZF가 0이 된다. and 연산은 1과 1을 연산하면 결과가 1이고 그 외에는 모두 0이 된다. 현재 eax 레지스터에 0이 저장되어 있으므로 `test eax,eax` 연산 결과는 0이 되며 ZF는 1이된다.  
![](https://images.velog.io/images/jjewqm/post/29b8bdd2-a8c8-4510-aafb-9f649449a6a8/image.png)

- je 0x8048427 <main+51>

    je 명령어는 **jump if equa**l을 의미한다. 연산 결과가 0이면 ZF가 1이므로 main+51 주소로 이동하고 1이면 ZF가 0이므로 다음 명령 `mov DWORD PTR [esp],0x8048500` 으로 이동한다. 쉽게 설명하면 위 코드에서 modified 값이 0이 아닐 경우 you have changed the 'modifed' variable 문자열을 출력한다. 그러나 0이면 즉 modified 값이 **0과 같으면** Try again이 출력된다. 

- mov DWORD PTR [esp], 0x8048529

    0x8048529 주소 값을 esp 레지스터에 옮긴다. 현재 0x8048529 주소 값은 아래와 같다. 

    ![](https://images.velog.io/images/jjewqm/post/8b9e786d-9118-4cc5-ac09-b822033ab60e/image.png)

- call 0x804832c <puts@plt>

    puts 함수가 esp 레지스터에 있는 값을 출력한다.

    ![](https://images.velog.io/images/jjewqm/post/fb46f059-dd30-43a7-b4a3-5660f578a972/image.png)

- leave, ret
스택 프레임을 정리하고 메인함수가 종료된다.

## Exploit

modified 위치는 esp+0x5c, buffer 위치는 esp+0x1c이다. 스택은 위에 있을수록 작은 주소, 아래에 있을수록 높은 주소이다. buffer 주소가 더 작으므로 위에 위치하고 modified가 아래에 위치하며 buffer 크기를 지정하지 않는다. 따라서 buffer 크기를 가득 채우면 오버플로가 일어나 modified 변수에 영향을 준다.

![](https://images.velog.io/images/jjewqm/post/8989aa5f-f570-4290-86ac-81196aa58e5f/image.png)

오버플로가 발생하려면 modified 변수가 0이 아닌 값으로 변경되어 조건문을 통과해야 한다. 그러므로 유저가 modified 값을 조작하기 위해서는 buffer 변수로 오버플로를 발생시켜야 한다. gets 함수로 buffer 에 데이터를 넘치게 입력받아 다음 메모리에 존재하는 modified 변수에 영향을 줘야한다. buffer 크기는 64byte, modified는 4byte 이므로 문자열을 최소 68개 채우면 오버플로가 발생한다.

#### 문자열 생성

![](https://images.velog.io/images/jjewqm/post/b10af184-3dc3-4530-b11d-5d53c9e6c013/image.png)

#### exploit
문자열 "A"를 입력하고 실행하니 스택 오버플로가 발생해 `you have changed the 'modified' variable` 가 출력된다. 정확한 분석을 위해 gdb를 열어 디버깅하겠다.

![](https://images.velog.io/images/jjewqm/post/bfccbd9d-6fba-4855-a28d-08c3c2036f6a/image.png)

### 세부 분석
modified 변수 값이 변경되었는지 확인해야 하므로 조건문인 33번줄에 브레이크 포인트를 걸고 문자열을 입력한다.

![](https://images.velog.io/images/jjewqm/post/75b75335-99e0-4223-b728-d810aa6ddd98/image.png)

buffer가 입력받은 값은 esp 레지스터에 저장되고 buffer가 넘치면 modified 변수까지 A문자열로 채워질 것이다. 따라서 esp 레지스터와 modified 변수 메모리가 어떻게 변하였는지 확인한다.

![](https://images.velog.io/images/jjewqm/post/d71fedc3-4a7a-4e5e-b770-1d2f993c9446/2.png)

확인결과 esp 레지스터 0xffffd210 ~ 0xffffd240 까지 0x41(A)로 채워졌다. 이제 modified 변수는 어떻게 변했는지 확인하겠다. 

![](https://images.velog.io/images/jjewqm/post/8be160d7-a12f-45f4-b89e-b8e69602ace0/image.png)

modified 변수 값이 변하였다. continue 명령어를 사용해 프로그램 결과로 어떤 문구가 뜨는지 확인하겠다. 

![](https://images.velog.io/images/jjewqm/post/a2f980e8-5212-421c-b4d6-a5c55d364861/image.png)
