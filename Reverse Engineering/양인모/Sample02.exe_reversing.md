# Sample 02.exe 흐름파악

![](https://images.velog.io/images/jjewqm/post/3200b04a-4bb8-44c6-bda1-c66b9c150c70/sample02-1.PNG)

실행 결과 CMD창이 생기고 3초뒤 사라진다. 정확한 분석을 위해 **디버깅**을 하겠다.

![](https://images.velog.io/images/jjewqm/post/17a1f36e-5134-4817-b8f6-c90210443cac/%EB%B6%84%EC%84%9D1.PNG)

`00401170` 메인함수 주소에 브레이크 포인트를 걸고 함수 내부로 들어가겠다.

![](https://images.velog.io/images/jjewqm/post/3599adf4-0636-4854-b1d0-f9cab209f21d/%EB%B6%84%EC%84%9D2.PNG)
F8버튼(실행)을 눌러 명령어를 하나씩 실행한 결과 `00401048` 주소에서 `00401079`주소로 점프한다.![](https://images.velog.io/images/jjewqm/post/1635d1cf-4c77-439c-8b5c-0f2d76353029/%EB%B6%84%EC%84%9D4.png)

다음 명령 실행결과 3초 대기 후 CMD창이 종료된다.
![](https://images.velog.io/images/jjewqm/post/1e6a02e9-bba1-453d-8528-f155c34f0328/%EB%B6%84%EC%84%9D7.png)

## 1차 분석

메인함수부터 다시 분석을 시작하겠다.

![](https://images.velog.io/images/jjewqm/post/1635d1cf-4c77-439c-8b5c-0f2d76353029/%EB%B6%84%EC%84%9D4.png)

`00401048`주소의 어셈블리어 `JNZ SHORT 00401079`를 해석하면 ZF가 `1`일 경우 다음명령을 수행하고 `0`이면 `00401079`주소로 이동한다는 의미이다.

![](https://images.velog.io/images/jjewqm/post/72c79a67-e602-4f48-9a5e-49bb3f1fce2c/%EB%B6%84%EC%84%9D12.png)
그럼 ZF를 1로 바꿔 실행해보겠다. 점프를 하지않고 다음명령이 실행되었다.
하지만 다음 코드들도 CMP, JNZ 어셈블리어 코드로 이루어져 있다.
`CMP`는 비교구문으로 A와 비를 비교해 같으면 `ZF`에 1을 할당, 다르면 0을 할당한다.  
`JNZ`는 ZF 값이 0이면 이동하고 1이면 다음명령을 실행한다.

## 2차 분석

조건문인 **CMP 코드가 실행될 때 ZF 값을 1로 변경할 수 있도록 Hex값을 변경하며** 분석하겠다.
![](https://images.velog.io/images/jjewqm/post/7f397ef0-408e-4a4d-b8cf-8680a59d4bad/%EB%B6%84%EC%84%9D9.png)

`00401040` 주소 어셈블리어 `CMP WORD PTR SS:[ESP+4], 7D5`는 `ESP+4` 주소 2바이트와 0x7D5값을 비교해 같으면 `ZF`에 `1`을 할당, 다르면 `0`을 할당하라는 의미이다.

![](https://images.velog.io/images/jjewqm/post/55eb71a7-eae1-42f1-bef0-3d3cdec13fa9/%EB%B6%84%EC%84%9D10.png)

`ESP+4` 주소 2바이트 `E4 07` 값을 `D5 07`로 변경하겠다.

![](https://images.velog.io/images/jjewqm/post/03ba7762-c67a-4076-b16b-db67e9578748/%EB%B6%84%EC%84%9D11.png)

`JNZ SHORT 00401079` 명령어가 실행될 때 `ZF` 값이 `1`이기 때문에 다음 명령인
`CMP WORD PTR SS:[ESP+2], 0` 코드가 실행된다.
![](https://images.velog.io/images/jjewqm/post/5ddc01ca-c586-4979-952a-958cf99becb9/%EB%B6%84%EC%84%9D12.png)

`ESP+2` 주소인 `0012FE3A` 2바이트를 `00 00`로 변경 후 CMP 코드를 실행하겠다.
![](https://images.velog.io/images/jjewqm/post/14f1b673-4b1a-4047-b3d5-0d392e54995b/%EB%B6%84%EC%84%9D13.png)

`ZF` 값이 `1`인 상태로 `JNZ` 명령어가 실행된다.
![](https://images.velog.io/images/jjewqm/post/9aa51718-1e7c-46e0-bb8d-88ec484251cb/%EB%B6%84%EC%84%9D14.png)

`JNZ` 코드가 실행되고 다음 명령인 `CMP` 코드를 실행하기 앞서 `ESP+6` 주소 2바이트 값을 `0x20`과 동일하게 수정한 뒤 실행하겠다.
![](https://images.velog.io/images/jjewqm/post/57d5a19b-68a6-4351-8c0c-74440c55b7ec/%EB%B6%84%EC%84%9D15.png)

### Hex 값 수정

![](https://images.velog.io/images/jjewqm/post/2e72443f-d801-45f4-a147-2eb65325be9d/%EB%B6%84%EC%84%9D16.png)

**Hex** 값을 수정해 다음 명령어가 실행된다.

### JNZ 어셈블리어

![](https://images.velog.io/images/jjewqm/post/1f22e6ef-aefd-4586-9009-8a25905d4bd0/%EB%B6%84%EC%84%9D17.png)

`JNZ` 명령어는 `ZF` 값이 `1` 이면 다음명령이 실행되고 `0`일 경우 지정한 주소로 이동한다.
현재 `ZF` 값은 `1` 이므로 다음 명령어 `LEA ECX, DWORD PTR SS:[ESP+10]` 코드가 실행된다.

### 스택 저장

`LEA ECX, DWORD PTR SS:[ESP+10]` 명령어는 `ESP+10` 주소 4바이트 값을 `ECX` 레지스터로 옮기라는 의미이다. ![](https://images.velog.io/images/jjewqm/post/a86be63d-ab89-4c1c-906a-cf0ff6c5bab4/%EB%B6%84%EC%84%9D19.png)

따라서 ECX 레지스터에 `if Code!!` 문자열이 저장된다.
다음명령어 `PUSH ECX`는 **ECX 레지스터 인자를 스택에 넣으라는 의미**이다.

![](https://images.velog.io/images/jjewqm/post/670b0c2f-a4d4-449f-a26c-0b2259eba084/%EB%B6%84%EC%84%9D20.png)

### 문자열 출력

`00401064` 주소의 명령어 `CALL 00401090` 가 실행되어 문자열 `if Code!!`가 출력되었다.
![](https://images.velog.io/images/jjewqm/post/0e2097c3-7088-4eb7-9977-322bfc414829/%EB%B6%84%EC%84%9D21.png)

### 정리

`Sample 02.exe`분석 결과 조건문이 일치하면 문자열 출력, 3초 대기 후 CMD창이 종료된다.
일치하지 않을 경우 문자열을 출력하지 않고 3초 대기 후 CMD창이 종료된다.

![](https://images.velog.io/images/jjewqm/post/fdf15ac5-ff0e-4f3d-bde0-6da4a6b14e70/%EB%B6%84%EC%84%9D23.png)

# 문제 해결

문자열이 출력되지 않는 원인은 조건식이 잘못되었기 때문이다.
어떻게 하면 조건식을 고칠 수 있을까?
![](https://images.velog.io/images/jjewqm/post/cadba513-ad8b-42f8-a776-ce755fdd8fb6/%EB%B6%84%EC%84%9D24.png)

## 1차 분석

우선 분석파일에 조건문은 3개 존재한다.

### CMP WORD PTR SS:[ESP+4], 7D5

![](https://images.velog.io/images/jjewqm/post/5349b327-72a0-4df1-861d-433fd1baa242/%EB%B6%84%EC%84%9D25.png)

### CMP WORD PTR SS:[ESP+2], 0

![](https://images.velog.io/images/jjewqm/post/e68aa818-5c51-4094-824a-96b5a582be33/%EB%B6%84%EC%84%9D26.png)

### CMP WORD PTR SS:[ESP+6], 20

![](https://images.velog.io/images/jjewqm/post/0f64fd7f-50e8-4b95-8bb9-6daaaf87e46f/%EB%B6%84%EC%84%9D27.png)

---

### 조건문 비교값

| Address  | Stack Value | comparison Value |
| :------: | :---------: | :--------------: |
| 0x12FE38 |    0x7E4    |      0x7D5       |
| 0x12FE3A |     0x2     |       0x0        |
| 0x12FE3E |    0x1A     |       0x20       |

### 해결방안

1. Stack Value 변경
2. comparison Value 변경

`Stack Value`를 변경하는 것은 일회성에 그치므로 `comparison Value`를 변경하겠다.

코드를 다시 실행해보자.

## 2차 분석

![](https://images.velog.io/images/jjewqm/post/b9f9269d-6012-43b9-85f5-2078b2e4eb52/%EB%B6%84%EC%84%9D28.png)

메인함수를 실행한 뒤 `0x12FE38`주소를 확인하니 저장된 데이터가 없다.
`F8 (명령어 한 개 실행)`버튼을 눌러 디버깅을 시작하겠다.

### GetLocalTime API

![](https://images.velog.io/images/jjewqm/post/4ccea7bf-34b8-49ab-981b-abfa295e1eb8/%EB%B6%84%EC%84%9D29.png)

디버깅 결과 `CALL DWORD PTR DS:[<&KERNEL 32.GetLocalTime>]` 명령어가 실행된다.

![](https://images.velog.io/images/jjewqm/post/bc626f08-50ea-4562-92a4-9d921dc58a04/%EB%B6%84%EC%84%9D32.png)

`GetLocalTime API`는 **현재 시간**을 인자로 받으며 분석파일에서는 `0012FE38`을 인자로 받는다.

### API 실행 결과

![](https://images.velog.io/images/jjewqm/post/5e6870df-49db-4f3a-a567-477c59621520/%EB%B6%84%EC%84%9D30.png)

`GetLocalTime API`가 실행되어 `0x12FE38`주소에 데이터가 저장되었다.

### 획득 값 | 비교 값

`API`가 실행되어 획득한 값과 조건문의 비교값을 확인하겠다.

|  항목  | 획득 값 |  의미  | 비교 값 |  의미  |
| :----: | :-----: | :----: | :-----: | :----: |
| wYear  |  0x7E4  | 2020년 |  0x7D5  | 2005년 |
| wMonth |   0x2   |  2월   |   0x0   |  0월   |
|  wDay  |  0x1A   |  26일  |  0x20   |  32일  |

`GetLocalTimeAPI`는 현재 시간 값을 반환하는데 비교값이 **2005년 0월 32일**과거 시간을 가지고 있어 조건문이 일치할 수 없었다.

## 해결 방안

1차 분석에서 예상했듯이 **"비교값"**을 변경하면 조건문이 일치한다.
하지만 다른 방법은 없을까? 비교값을 변경하는 방법을 포함해 4가지 해결방법이 있는 것 같다.

1. 비교값을 변경한다.
2. **ZF**값을 `1`로 변경한다.
3. **JNZ** 명령어를 변경한다.
4. API 호출 시 입력값을 변경한다.

`GetLocalTimeAPI`의 입력값을 과거시간으로 입력할 순 없으므로 3가지 방법을 사용해 문제를 해결하겠다.

### 비교 값 변경

![](https://images.velog.io/images/jjewqm/post/863487a9-9de9-4f86-b9b1-218907885377/%EB%B6%84%EC%84%9D34.png)

비교값 `0x7D5`를 `0x7E4`로 변경하겠다.

### ZF 값 변경

![](https://images.velog.io/images/jjewqm/post/623eec2d-f4b2-49e1-a79e-89c0508861f9/%EB%B6%84%EC%84%9D35.png)

`ZF`값을 `1`로 바꿔 다음 명령이 실행된다.

### JNZ 명령어 변경

![](https://images.velog.io/images/jjewqm/post/60111477-0df3-4952-b35b-df26edb07c96/%EB%B6%84%EC%84%9D36.png)

`JNE`명령어를 `JE`명령어로 변경하겠다.
`JE`명령어는 `ZF`값이 `0`이면 다음 명령을 실행하고 `1`이면 지정한 주소로 점프한다.
따라서 현재 `ZF` 값은 `0`이므로 다음 명령이 실행된다.

## 분석 결과

![](https://images.velog.io/images/jjewqm/post/ddc77a45-3d92-48ef-9f63-837ab0212de7/%EC%B5%9C%EC%A2%85.png)

순차적으로 명령이 실행되어 `if Code!!`문자열이 출력되었다.

---

본 글은 '리버싱 이정도는 알아야지' 인프런 강의를 정리합니다.
