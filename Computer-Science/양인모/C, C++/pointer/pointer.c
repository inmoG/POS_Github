#include <stdio.h>
void swap(int a, int b);
void swap_addr(int *a, int *b);
void changeArray(int *ptr);

int pointer_main(void)
{

    int 철수 = 5; //암호
    int 영희 = 2;
    int 민수 = 3;

    printf("철수네 주소 : %d, 암호 : %d\n", &철수, 철수); // &는 변수의 주소를 가리킨다.

    printf("영희네 주소 : %d, 암호 : %d\n", &영희, 영희);
    printf("민수네 주소 : %d, 암호 : %d\n", &민수, 민수);

    int 미션맨;  // 변수
    int *미션맨; // 포인터 변수

    미션맨 = &철수; //철수의 주소를 할당한다.
    printf("미션맨이 방문하는 곳 주소 : %d, 암호 : %d\n", 미션맨, *미션맨);
    // 미션맨은 철수의 주소를 가진다. *미션맨은 철수의 값 즉 5를 가져온다.

    미션맨 = &영희; // 영희의 주소를 할당한다.
    printf("미션맨이 방문하는 곳 주소 : %d, 암호 : %d\n", 미션맨, *미션맨);
    // *미션맨은 변수의 값 즉 영희의 값을 가져온다.

    미션맨 = &민수;
    printf("미션맨이 방문하는 곳 주소 : %d, 암호 : %d\n", 미션맨, *미션맨);

    int *스파이 = 미션맨;

    /*
	스파이 (252114)
						>>> (252114) 누군가의 아파트 주소;
	미션맨 (252114)
	*/

    //미션맨은 포인터 변수이다. 스파이라는 포인터 변수가 포인터 변수인 미션맨을 가리킨다.
    //그래서 스파이 변수는 미션맨이 가지고 있는 철수의 주소를 가진다.

    스파이 = &철수; // 민수의 주소를 가지고 있어 초기화한다.

    printf("스파이가 미션 수행 중..\n");

    *스파이 = *스파이 - 2; //  *스파이는 스파이 변수의 값 즉 철수의 값을 가진다. 따라서 *스파이는 5를 의미한다.

    printf("스파이의 주소 : %d, 암호 : %d\n", 스파이, *스파이); // 철수의 주소와 값을 출력.

    스파이 = &영희; // 철수의 주소를 가지고 있어 초기화한다.

    *스파이 = *스파이 - 2;

    printf("스파이의 주소 : %d, 암호 : %d\n", 스파이, *스파이);

    스파이 = &민수; // 영희의 주소를 가지고 있어 초기화한다.

    *스파이 = *스파이 - 2;

    printf("스파이의 주소 : %d, 암호 : %d\n", 스파이, *스파이);

    printf("철수 영희 민수는 바뀐 암호를 보고 놀랐다..!\n\n");
    // 포인터 변수는 가리키는 변수의 값을 바꿀 수 있다

    printf("철수네 주소 : %d, 암호 : %d\n", &철수, 철수); // &는 변수의 주소를 가리킨다.
    printf("영희네 주소 : %d, 암호 : %d\n", &영희, 영희);
    printf("민수네 주소 : %d, 암호 : %d\n", &민수, 민수);

    printf("스파이와 미션맨은 어디에 살까요?\n");

    printf("스파이의 주소 : %d\n", &스파이);
    printf("미션맨의 주소 : %d\n", &미션맨);

    //  배열과 포인터의 관계
    int arr[3] = {5, 10, 15};
    int *ptr = arr;

    for (int i = 0; i < 3; i++)
    {
        printf("배열 arr[%d]의 값 : %d\n", i, arr[i]);
    }

    for (int i = 0; i < 3; i++)
    {
        printf("포인터 ptr[%d]의 값 : %d\n", i, ptr[i]);
    }

    ptr[0] = 100;
    ptr[1] = 200;
    ptr[2] = 300;

    printf("\nptr을 업데이트 했습니다.\n");
    // 포인터가 배열의 값에 접근해 값을 바꿈.
    for (int i = 0; i < 3; i++)
    {
        // printf("배열 arr[%d]의 값 : %d\n", i, arr[i]);
        printf("배열 arr[%d]의 값 : %d\n", i, *(arr + i)); // arr 주소의 i번째 값을 가져오란 의미.
    }

    for (int i = 0; i < 3; i++)
    {
        printf("포인터 ptr[%d]의 값 : %d\n", i, ptr[i]);
    }

    arr[i] == *(arr + i) 같은 의미.arr == &arr[0] "arr" 은 arr배열의 " 첫번째 값의 주소와 동일"

                                          printf("arr 자체의 값 : %d\n", arr); // 16383324
    printf("arr 배열의 첫번째 값 : %d\n", &arr[0]);                            // 16383324

    printf("\narr 자체의 값이 가지는 주소 : %d의 실제 값 : %d\n", arr, *arr); // *(arr + 0)
    printf("arr[0]의 실제 값 : %d\n", *&arr[0]);

    arr == &arr[0] 이 동일하기 때문에
                포인터가 arr 자체의 값을 가져와 각 인덱스의 값을 출력해도 arr[i] 와 ptr[i] 는 동일한 결과가 나오는 것이다.
                    //  int* ptr = arr;
                    //  printf("포인터 ptr[%d]의 값 : %d\n", i, ptr[i]);

                    *&는 주소의 값을 가져오란 의미지만 함께 사용하면 효과가 적용되지 않는다.서로 상쇄되는 효과가 생김.

            printf("arr[0]의 실제 값 : %d\n", *&*&*&*&*&*&*&arr[0]);
    printf("arr[0]의 실제 값 : %d\n", arr[0]);

    printf("\narr[] 과 ptr[]의 주소값은 같을까?\n");
    for (int i = 0; i < 3; i++)
    {
        printf("arr[%d] 자체의 값 : %d |     %d 주소의 실제 값 : %d\n", i, &arr[i], &arr[i], arr[i]);
    }
    printf("ptr[] 의 값 \n");
    for (int i = 0; i < 3; i++)
    {
        printf("ptr[%d] 자체의 값 : %d |     %d 주소의 실제 값 : %d\n", i, &ptr[i], &ptr[i], ptr[i]);
    }

    printf("\n\n ptr 자체의 값 : %d\n", &ptr);
    printf("arr 자체의 값 : %d\n", &arr);

    // SWAP

    int a = 10;
    int b = 20;

    //a와 b의 주소를 출력한다.
    printf("a의 주소 => a : %d\n", &a);
    printf("b의 주소 => b : %d\n", &b);

    // a와 b의 값을 바꾼다.
    printf("swap 함수 전 => a : %d, b : %d\n", a, b);
    printf("\n\n----------------------------------------\n\n");
    swap(a, b);
    printf("swap 함수 후 => a : %d, b : %d\n", a, b);
    // 값에 의한 복사 (Call by Value) => 값만 복사한다는 의미.

    printf("\n\n----------------------------------------\n\n");
    // 값이 아닌 메모리 공간의 주소를 넘긴다.

    printf("(주소값 전달) swap_Addr 함수 전 => a : %d, b : %d\n", a, b);
    swap_addr(&a, &b);
    printf("(주소값 전달) swap_Addr 함수 후 => a : %d, b : %d\n", a, b);

    // 포인터로 배열 값 변경하기

    int arr2[3] = {10, 20, 30};
    // 배열일 때 arr2 =>> 주소
    for (int i = 0; i < 3; i++)
    {
        printf("arr2[%d] : %d\n", i, arr2[i]);
    }
    // changeArray(arr2); // 배열 arr2는 주소이기 때문에 &를 붙이지 않는다.
    changeArray(&arr2[0]); // 위와 동일하게 실행된다.
    for (int i = 0; i < 3; i++)
    {
        printf("arr2[%d] : %d\n", i, arr2[i]);
    }

    // scanf 에서 값을 입력받을 때 "&"를 사용한다
    // 그 이유는 입력받은 값을 변수의 메모리 공간(주소)에 할당하기 위해서다.
    return 0;
}

void swap(int a, int b)
{
    // swap 함수 안에서의 주소와 밖에서의 주소가 다르다.
    // 즉 함수 밖의 a와 함수 안의 a는 다른 변수다.

    printf("(swap 함수 내) a의 주소 => a : %d\n", &a);
    printf("(swap 함수 내) b의 주소 => b : %d\n", &b);

    int temp = a;
    a = b;
    b = temp;
    printf("swap 함수 내 => a : %d, b : %d\n", a, b);
}

void swap_addr(int *a, int *b)
{
    printf("(swap_Addr 함수 내) a의 주소 => a : %d\n", a);
    printf("(swap_Addr 함수 내) b의 주소 => b : %d\n", b);
    printf("(swap_Addr 함수 내 주소값을 받아온) a의 주소 => a : %d\n", &a);
    printf("(swap_Addr 함수 내 주소값을 받아온) b의 주소 => b : %d\n", &b);

    int temp = *a; // a의 값을 바꿔야 되므로 a의 값을 가져오는 *a를 사용.
    *a = *b;
    *b = temp;
    printf("(주소값 전달 swap_Addr 함수 내) => a : %d, b : %d\n", *a, *b); // a와 b의 값을 출력하므로 *a, *b를 사용한다.
}

void changeArray(int *ptr) // 주소를 받을 때는 포인터 변수 [* 변수] 를 사용해야 한다.
{
    ptr[2] = 50;
}