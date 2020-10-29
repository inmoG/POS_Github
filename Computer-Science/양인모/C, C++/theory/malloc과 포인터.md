# 초기화되지 않은 포인터 변수

```c
#include <stdio.h>

int main(void)
{
    int *x;
    int *y;

    x = malloc(sizeof(int));

    *x = 42;
    *y = 13;

    printf("%d, %d\n", *x, *y);
}
```

x에는 malloc 함수를 이용해 int 자료형 크기에 해당하는 메모리를 할당한다. x와 y 포인터가 가리키는 곳에 42와 13을 저장한다. 4바이트 메모리를 할당했기에 포인터 변수 x는 `42`를 저장할 공간이 있다. 그러나 **포인터 변수 y는 할당받은 메모리가 없는, 초기화되지 않은 변수이다. 따라서 포인터 변수 y는 가리키는 주소가 없으며 잘못된 주소를 가리킬 수도 있다. 만약 잘못된 주소를 가리킨다면 시스템과 충돌하거나 잘못 가리킨 주소 값이 변경될 수도 있다.** 그리고 포인터 변수가 할당받은 메모리 공간이 없어 값을 저장하려고 해도 저장할 공간이 없을 뿐만 아니라 가리킬 수 있는 주소도 없어 값이 어디있는 지 알 수 없다. 따라서 메모리 공간에서 돌아다니는 쓰레기 값이 된다.

```c

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *x;
    int *y;

    x = malloc(sizeof(int));

    *x = 42;
    *y = x;
    *y = 13;

    printf("%d, %d\n", *x, *y);
}
```

포인터 변수 x가 가리키는 주소를 포인터 변수 y에 저장한다. **이제 x와 y는 동일한 주소를 가리킨다.** 따라서 포인터 변수 y에 13을 저장하면 x와 y가 가리키는 주소에 13이 저장되고 포인터 변수 x도 13을 저장하게 된다.

## 배열 크기 조정하기

컴퓨터 안의 메모리는 사물함과 같은 구조다. 사용하려는 사물함 개수를 한 번 정한 이후에는, 공간이 모자라도 주변 사물함을 마음대로 더 사용할 수는 없다. 이미 다른 목적으로 사용되고 있을 수 있기 때문이다. 이와 같이 일정한 크기의 메모리가 할당되어 있는 상황에서 메모리 크기를 변경하는 것도 쉽지 않다. 이미 할당된 메모리를 임시 메모리에 할당하고 새 메모리를 할당받아 임시 메모리에 옮겨 놓은 값을 새 메모리에 할당해야 한다. 왜냐하면 임시 메모리를 할당하지 않고 메모리 크기를 늘려버리면 옆 메모리 공간을 침범해 데이터 손상이 일어날 수 있다.

`int *list = malloc(3 * sizeof(int));` int 자료형 3개로 이루어진 포인터 변수를 선언해 4바이트 크기 메모리 3개를 할당받았다. 이 메모리 공간은 4바이트, 4바이트, 4바이트로 이루어져 배열과 같은 모양을 띄고있다. 따라서 배열처럼 대괄호를 사용해 `list[0], list[1], list[2]`로 표현할 수 있다.

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	// int 자료형 3개로 이루어진 list 포인터를 선언하고 메모리 할당
	int *list = malloc(3 * sizeof(int));

	// 포인터가 잘 선언되었는지 확인
	if (list == NULL)
	{
		return 1;
	}

	//list 배열 각 인덱스에 값 저장
	list[0] = 1;
	list[1] = 2;
	list[2] = 3;

	int *tmp = malloc(4 * sizeof(int));

	if (tmp == NULL)
	{
		return 1;
	}

	for (int i = 0; i < 3; i++)
	{
		tmp[i] = list[i];
	}

	tmp[3] = 4; // tmp배열 네 번째 인덱스에 값 저장

	free(list); // list 메모리 초기화

	list = tmp; // list와 tmp가 같은 곳을 가리키도록 tmp 변수 주소값 저장

	for (int i = 0; i < 4; i++)
	{
		printf("%d\n", list[i]);
	}

	free(list);
}
```

realloc 함수를 사용하면 아래와 같이 더 쉽게 배열 크기를 조정할 수 있다.

```c
#include <stdio.h>  // print
#include <stdlib.h> // malloc, realloc, free
#include <string.h> // strlen()

int main(void)
{
	int* list = malloc(3 * sizeof(int));
	if (list == NULL)
	{
		return 1;
	}

	list[0] = 1;
	list[1] = 2;
	list[2] = 3;

	//tmp 포인터에 16바이트 메모리 할당하고 list 값 복사
	int* tmp = realloc(list, 4 * sizeof(int));

	if (tmp == NULL)
	{
		return 1;
	}

	//list가 tmp와 같은 곳을 가리키도록 지정
	list = tmp;

	tmp[3] = 4;

	for (int i = 0; i < sizeof list; i++)
	{
		printf("%d\n", list[i]);
	}

	free(list);

}
```
