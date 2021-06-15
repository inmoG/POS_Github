# 분석 목표

쓰레기 값이 아닌 `For Code!!`문자열을 출력해야 한다.

![](https://images.velog.io/images/jjewqm/post/7f59788a-0b33-4d3b-a8ae-1dbf4a4568f6/1.png)

## 흐름파악

![](https://images.velog.io/images/jjewqm/post/8b3fe3e4-a8d6-4119-8fc8-c3e30eb82abc/2.png)

메인함수가 시작되는 `401140` 주소에 `Break Point`를 걸어 함수 내부로 들어가겠다.

![](https://images.velog.io/images/jjewqm/post/14900974-2a44-4f2f-b26a-d68b2d30b9ed/3.png)

코드를 살펴보니 `401031` 주소에 반복문 코드가 존재한다.
반복문을 실행하겠다.

### 반복문 실행

![](https://images.velog.io/images/jjewqm/post/874d96d5-6f44-4156-aeca-12a44af01d82/4.PNG)

실행 결과 디버깅 전 분석파일을 실행했을 때와 같이 쓰레기 값이 출력되었다. 반복문 부분을 정확히 확인하기 위해 다시 디버깅 하겠다.

### 반복문 디버깅

![](https://images.velog.io/images/jjewqm/post/cceace2e-aa8f-4964-b2f6-62bd0c51a1fb/5.png)

- MOVSX ECX, BYTE PTR SS:[ESP+ESI+4]

  - ESP + ESI + 4 주소의 1 바이트를 ECX 레지스터에 옮긴다.

- PUSH ECX

  - ECX 레지스터를 스택에 올린다.

- PUSH 00407030

  - 문자 한 글자를 스택에 올린다.

- CALL 00401060

  - 문자 출력

- ADD ESP, 8
  - ESP 레지스터에 8을 더한다.
- INC ESI
  - ESI 레지스터를 1 증가시킨다.
- CMP ESI, 14

  - ESI 레지스터 값과 0x14를 비교해 같으면 ZF=1, 다르면 ZF=0

- JL SHORT 00401031
  - ZF 값이 0이면 00401031 주소로 이동하고 1이면 다음 명령 실행

---

#### 디버깅 결과

디버깅 결과 반복문의 흐름은 아래와 같다.

1. `ESP + ESI + 4` 주소 1바이트를 ECX 레지스터에 저장해 스택에 올린다.
2. 스택에 올라온 문자를 출력한다.
3. ESI 레지스터 값을 1 증가시켜 0x14와 비교해 같으면 ZF=1, 다르면 ZF=0을 할당한다.
4. ZF 값이 0이면 00401031 주소로 이동해 반복문을 실행하고 1이면 다음 명령을 실행해 반복문을 탈출한다.

### 1차 원인 파악

출력해야 될 문자열은 `For Code!!`이다. 하지만 현재 출력 문자열은 알 수 없는 문자열이다. 원인을 파악해 코드를 수정하겠다.

#### MOVSX ECX, BYTE PTR SS:[ESP+ESI+4]

![](https://images.velog.io/images/jjewqm/post/67e72528-1901-4c24-80a9-29c702b2b1c9/6.PNG)

**ESP+ESI+4** 주소 1바이트 값은 `00`이며 아스키코드 `NULL`을 의미해 출력 결과 공백이 출력된다. 따라서 잘못된 주소가 아닌 올바른 주소의 바이트 값을 출력하면 정상적으로 문자열을 출력할 수 있을 것 같다.

## 분석

![](https://images.velog.io/images/jjewqm/post/81905c8d-3d7c-44e4-8e27-ef8abd116bae/7.PNG)

메인함수 코드가 시작되면 `For Code!!` 문자열은 `407034` 주소에 있다.
1 바이트씩 출력하면 정상적으로 문자열을 출력할 수 있을 것 같다.
`MOVSX ECX, BYTE PTR SS:[ESP+ESI+4]`의 주소값을 수정하겠다.

![](https://images.velog.io/images/jjewqm/post/37fe4d46-d8b0-4b28-9a62-80cc327f87db/8.png)

0x407034(문자열 주소) - 0xA(ESI) = 0x40702A
ESP 레지스터는 스택포인터여서 값을 수정할 수 없으니 EDI 레지스터에 `0x40702A`를 할당한 뒤 명령어를 수정하겠다.

### 수정 전 명령어

`MOVSX ECX, BYTE PTR SS:[ESP+ESI+4]`

### 수정 후 명령어

`MOVSX ECX, BYTE PTR SS:[ESD+ESI]`

명령어를 수정했으니 반복문을 다시 실행하겠다.

### 반복문 디버깅

![](https://images.velog.io/images/jjewqm/post/6bdc14b3-e76f-489a-bdc5-e3c769f83e7a/10.png)

디버깅 결과 `For Code!!`문자열이 출력된다. 하지만 현재 해결방안은 임시방편이다. `ESP+ESI+4` 주소에 `For Code!!`문자열이 아닌 다른 문자열이 있는 이유를 알아내야 한다.

## 2차 분석

### 문자열 저장 1

![](https://images.velog.io/images/jjewqm/post/8d224760-e314-479a-bb0e-09d3ae59cbaa/11.png)

메인함수가 시작되고 `407034` 주소의 4 바이트를 EAX 레지스터에 저장한다.

![](https://images.velog.io/images/jjewqm/post/e9295030-5d82-4d85-ba59-2daa14b3738b/12.png)

해당 주소에는 `0x20726F46` 즉 `For` 문자열이 존재한다.

### 문자열 저장 2

![](https://images.velog.io/images/jjewqm/post/da4f6143-8642-4cd5-8f37-33b251e39a42/13.png)

`407038` 주소의 4 바이트를 ECX 레지스터에 저장한다.

![](https://images.velog.io/images/jjewqm/post/cf585c3f-4664-47e2-8bc6-f1fb7f42d6a6/14.png)

해당 주소에는 `0x65646F43` 즉 `Code` 문자열이 존재한다.

### 문자열 저장 3

![](https://images.velog.io/images/jjewqm/post/89720c80-6fa9-4955-b5f2-a625e13d88d1/15.png)

`40703C` 주소의 2 바이트를 EDX 레지스터에 저장한다.
![](https://images.velog.io/images/jjewqm/post/1f1fc171-3eeb-4599-abc2-6991d46962ee/16.png)

해당 주소에는 `0x2121` 즉 `!!`문자열이 존재한다.

### 문자열 저장 4

![](https://images.velog.io/images/jjewqm/post/792b5df1-d125-4d86-b8bd-79bc171231fd/17.png)

EAX 레지스터의 4 바이트를 ESP 레지스터로 옮긴다.
따라서 `12FF40` 주소에 `For` 문자열이 저장된다.
![](https://images.velog.io/images/jjewqm/post/9d2b47dc-d075-4c0e-a512-bb525028cf12/19.png)

### 문자열 저장 5

![](https://images.velog.io/images/jjewqm/post/0ed81ea7-1093-4271-ae4b-685503f082c8/20.png)

ECX 레지스터의 4 바이트를 `ESP+8` 주소로 옮긴다.
따라서 `12FF44` 주소에 `Code` 문자열이 저장된다.

### 문자열 저장 6

![](https://images.velog.io/images/jjewqm/post/c76731c2-7b7c-4b23-bbb1-966d2e6206f3/22.png)

EDX 레지스터의 2 바이트를 `ESP+C` 주소로 옮긴다.
따라서 `12FF48` 주소에 `!!` 문자열이 저장된다.

![](https://images.velog.io/images/jjewqm/post/ac5244fb-bfb3-4f41-901f-90b5f1200f1d/23.png)

### 문자열 저장 7

![](https://images.velog.io/images/jjewqm/post/c78fb89d-402f-43dd-96b0-4beaa6b50e89/24.png)

EAX 하위 8bit인 AL의 1바이트를 `ESP+E` 주소로 옮긴다.
따라서 `12FF4A` 주소에 `00` 즉 공백이 저장된다.

### ESI 레지스터 저장

![](https://images.velog.io/images/jjewqm/post/10f9dfe4-0885-425a-953b-e29d9be786e0/25.png)

`0xA`를 ESI 레지스터에 옮긴다.
![](https://images.velog.io/images/jjewqm/post/6addb666-b4da-4057-bc06-7e8efa35ca41/26.png)

## 2차 원인 파악

![](https://images.velog.io/images/jjewqm/post/3e16afb7-ed99-428f-b29e-1fd7dcc543f5/27.png)

1차 원인 파악에서 알아냈듯이 `ESP + ESI + 4` 주소인 `12FF4A` 주소에는 현재 쓰레기 값이 저장되어 있고 올바른 문자열은 `12FF40` 주소에 저장되어 있다.

![](https://images.velog.io/images/jjewqm/post/00e9d609-353e-4125-8299-c2e5b9f8c62a/26.png)
`12FF40` 주소로 가려면 `12FF4A` 주소에서 `0xA`를 빼야한다.

0x12FF4A - 0x12FF40 = 0xA

![](https://images.velog.io/images/jjewqm/post/0d2c0867-44b8-4e65-be8a-6606711fe296/28.png)

`0xA`를 ESI 레지스터에 저장한 적이 있으므로 ESI 레지스터에 `0x0`을 저장하거나 해당 코드를 삭제하는 방식으로 코드를 변경하자.
해당 분석에선 ESI 레지스터에 `0x0`을 저장하도록 코드를 변경하겠다.

## 문제 해결

![](https://images.velog.io/images/jjewqm/post/23ce9401-90d5-46ee-8a00-04f1ef0043e6/29.png)
![](https://images.velog.io/images/jjewqm/post/9a90ee71-e10e-41cf-b2c9-3efb8111e9d2/31.png)

코드를 변경 후 실행하니 `For Code!!` 문자열이 잘 출력되나 쓰레기 값이 같이 출력된다.

![](https://images.velog.io/images/jjewqm/post/4364e8a4-6ca5-421d-bb18-1427a86b3bbd/32.png)

For Code!! 문자열은 10개의 Hex값으로 구성되어있어 반복문을 10번만 돌면 된다.

![](https://images.velog.io/images/jjewqm/post/2b808b43-58ec-4874-9216-2f9fa206f2b6/33.png)

ESI 레지스터 값과 0x14(20)을 비교하는 반복문 조건문 코드 `CMP ESI, 14`를
`CMP ESI, 0A`로 변경하겠다.

## 결과

![](https://images.velog.io/images/jjewqm/post/630dc777-6b4d-4f3c-8de6-1690730224da/34.png)

정상적으로 `For Code!!` 문자열이 출력된다.

---

본 글은 '리버싱 이정도는 알아야지' 인프런 강의를 정리합니다.
