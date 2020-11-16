# For

C언어의 For문 형식은 아래와 같다.

```c

#include <stdio.h>
int main()
{
	int i;
	for (초기식; 조건식; 증감식)
	{
		명령
	}
}
```

```c
for (;;) 
	{
		scanf_s("%d", &usranswer);
		if (usranswer == 5) {
			printf("정답입니다!\n");
			break;
		}
		else
		{
			printf("틀렸습니다.\n");
		}
	}
```

`;;`는 참을 의미한다. 따라서 정답을 맞출 때 까지 for문이 실행된다.
`break` 구문이 실행되면 코드가 종료되어 for문 밖으로 탈출한다.

```c
for(int i = 0; i < 100; i++)
{
  if(i % 5 == 0) continue;
  printf("%d", i);
}
```

`break`는 조건문이 종료되지만 `continue`는 다시 조건식으로 점프한다.
`break`, `continue` 는 `return 0`과 같이 코드 뒤 부분이 실행되지 않는다.

# switch

```c
switch ( 변수 ) {
    case 값1 :
        // 명령들;
        break;
    case 값2 :
        // 명령들;
        break;
    default:
       // 명령들;
```

`switch` 문에 사용될 변수는 반드시 정수 데이터를 보관하는 변수여야 한다.

"변수" 부분에 들어가는 타입은 `char`, `short`, `int`, `long`중 하나여야 한다.
만약 `float`, `double` 같은 실수형 타입이라면 컴파일 시 오류가 발생한다.
**"값"** 에 위치하는 것들은 반드시 **"상수"** 여야 한다. 만약 **"값"** 부분에 **"변수"** 가 온다면 오류가 발생한다.

`break`를 통해 `switch` 문을 빠져나올 수 있다.
만약 첫번째 `case`에 `break`가 없다면 나머지 `case` 명령이 같이 실행된다.

# Reference

본 글은 이재범님의 모두의 코드 강좌를 정리합니다.
https://modoocode.com/16
