# Command Line Argument

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		printf("hello, %s\n", argv[1]);
	}
	else
	{
		printf("hello, world\n");
	}
}
```

## argc

argc 변수는 main 함수가 받게 될 입력의 개수이다.

## argv

argv[]는 입력이 포함되어 있는 배열이다. 프로그램을 명령행에서 실행하므로, 입력은 문자열로 주어진다. 따라서 argv[]는 char 배열이다.

argv[0]은 기본적으로 프로그램의 이름이 저장된다. 해당 코드는 argv-argc 프로그램 이름을 저장한다.

만약 하나의 입력이 더 주어진다면 argv[1]에 저장된다. 예를 들어 위 프로그램을 'argv-argc.c' 이름으로 저장, 컴파일 한 후 "./argv-argc"로 실행하면 "hello, world"값이 출력된다.
명령행 인자에 주어진 값이 프로그램 이름 하나밖에 없기 때문이다. 하지만 "./argv-argc David"로 실행하면 "hello, David"값이 출력된다. 명령행 인자에 David라는 값이 추가로 입력되었고, 따라서 argc는 2, argv[1]은 "David"가 되기 때문이다.
