#include <stdio.h>

void swap(int a, int b);
void swap_Addr(int *a, int *b);
void changeArray(int *ptr);

int main(void)
{

    int asus = 5; //암호
    int *samsung = &asus;
    int *apple = samsung;

    printf("asus의 주소 : %d, asus의 값 : %d\n", &asus, asus);
    // 1100240696, 5

    printf("samsung 자기 자신의 주소 : %d\n", &samsung);
    // 1100240688

    printf("samsung의 주소 : %d, samsung의 값: %d\n", samsung, *samsung);
    // 1100240696, 5

    printf("apple 자기자신의 주소 : %d, apple의 주소 : %d, apple의 값 : %d\n",
           &apple, apple, *apple);

    *apple = *apple - 3;
    printf("apple의 값 : %d\n", *apple);
    printf("----------------------------------------------------------\n");

    int arr[] = {1, 2, 3, 4};
    int *ptr = arr;

    for (int i = 0; i < 4; i++)
    {
        printf("arr[%d]의 주소 : %d, arr[%d]의 값 : %d\n", i, &arr[i], i, arr[i]);
    }
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < 4; i++)
    {
        printf("ptr[%d]의 주소 : %d, ptr[%d]의 값 : %d\n", i, &ptr[i], i, ptr[i]);
    }

    ptr[0] = 100;
    ptr[1] = 200;
    ptr[2] = 300;
    ptr[3] = 400;

    printf("배열 업데이트!!\n\n");
    for (int i = 0; i < 4; i++)
    {
        printf("arr[%d]의 주소 : %d, arr[%d]의 값 : %d\n", i, &arr[i], i, arr[i]);
    }
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < 4; i++)
    {
        printf("ptr[%d]의 주소 : %d, ptr[%d]의 값 : %d\n", i, &ptr[i], i, ptr[i]);
    }
    // 포인터로 값 변경이 가능하다.

    printf("arr 자체의 값 : %d\n", arr);
    printf("arr 배열의 첫번째 값 : %d\n", &arr[0]);
    printf("arr 자체의 값이 가지는 주소 :%d의 실제 값 :%d\n", arr, *arr);
    printf("arr[0]의 실제 값 : %d\n", *&arr[0]);
    printf("포인터 ptr[%d]의 값 : %d\n", 0, ptr);

    printf("\\nnarr[] 과 ptr[]의 주소값은 같을까?\n");
    for (int i = 0; i < 3; i++)
    {
        printf("arr[%d] 자체의 값 : %d |     %d 주소의 실제 값 : %d\n", i, &arr[i], &arr[i], arr[i]);
    }
    printf("ptr[] 의 값 \n");
    for (int i = 0; i < 3; i++)
    {
        printf("ptr[%d] 자체의 값 : %d |     %d 주소의 실제 값 : %d\n", i, &ptr[i], &ptr[i], ptr[i]);
    }

    printf("\n\n ptr 자체의 값 : %d\n", &ptr); // 7338992    ptr이 담고있는 arr이 아니라 *ptr의 주소이다.
    printf("arr 자체의 값 : %d\n", &arr);      // 7338980

    printf("----------------------------------------------\n");
    // SWAP

    int a = 10;
    int b = 20;

    printf("a의 주소 => a : %d\n", &a);
    printf("b의 주소 => b : %d\n", &b);

    //a와 b의 값을 바꾼다.
    printf("swap 함수 전 -> a : %d\n, b : %d\n", a, b);
    printf("\n\n-----------------------------\n\n");
    swap(a, b);
    printf("swap 함수 후 -> a : %d, b : %d\n", a, b);
    // 함수 내에서만 값이 변한다. 이것은 값에 의한 복사(Call by Value)이기 때문이다.
    // 값만 복사한다는 의미.

    printf("\n\n-----------------------------\n\n");
    // 값이 아닌 메모리 공간의 주소를 넘긴다.

    printf("(주소 값 전달) swap_Addr 함수 전 => a : %d, b : %d\n", a, b); // a와 b의 값을 출력
    swap_Addr(&a, &b);
    printf("(주소 값 전달) swap_Addr 함수 후 => a : %d, b : %d\n", a, b); // a와 b의 값 출력

    printf("\n\n-----------------------------\n\n");

    // 포인터로 배열 값 변경하기

    int arr2[3] = {10, 20, 30}; // 인덱스 3개짜리 배열생성
    for (int i = 0; i < 3; i++)
    {
        printf("변경 전 arr2[%d] : %d\narr2[%d] 주소 : %d\n", i, arr2[i], i, &arr2[i]);
    }

    //changeArray(&arr2[0]); // 배열 arr2는 주소이기 때문에 &를 붙이지 않는다.
    changeArray(arr2); // 위와 동일함.
    for (int i = 0; i < 3; i++)
    {
        printf("변경 후 arr2[%d] : %d\narr2[%d] 주소 : %d\n", i, arr2[i], i, &arr2[i]);
    }

    // scanf 에서 값을 입력받을 때 "&"를 사용한다
    // 그 이유는 입력받은 값을 변수의 메모리 공간(주소)에 할당하기 위해서다.
    return 0;
}

void swap(int a, int b)
{
    //swap 함수 안에서의 주소와 밖에서의 주소가 다르다.
    // 함수  밖의 a와 함수 안의 a는 다른 변수다.

    printf("swap 함수 내 a의 주소 => a : %d\n", &a);
    printf("swap 함수 내 b의 주소 => b : %d\n", &b);

    int temp = a;
    a = b;
    b = temp;

    // 함수 내의 a 와 b의 값
    printf("swap 함수 내 => a : %d\, b : %d\n", a, b);
}

void swap_Addr(int *a, int *b)
{
    printf("swap 함수 내 주소값을 받아온 a의 주소 : %d\n", a); // 전역변수 a의 주소
    printf("swap 함수 내 주소값을 받아온 b의 주소 : %d\n", b); // 전역변수 b의 주소
    printf("----------------------------\n");
    printf("swap 함수 내 a의 주소 : %d\n", &a); // 함수에서 사용하는 a의 주소
    printf("swap 함수 내 b의 주소 : %d\n", &b); // 함수에서 사용하는 b의 주소

    int temp = *a; // a의 값을 바꿔야 되 a 값 가져오는 *a 사용
    *a = *b;
    *b = temp;
    printf("(주소값 전달 swap_Addr 함수 내) => a : %d, b : %d\n", *a, *b);
    // a와 b의 값을 출력하므로 *a, *b 사용
}

void changeArray(int *ptr) // 주소를 받을 때는 포인터 변수 [* 변수] 를 사용해야 한다.
{
    ptr[2] = 50;
    for (int i = 0; i < 3; i++)
    {
        printf("changeArray 함수 내 ptr[%d] : %d\nptr[%d] 주소 : %d\n", i, ptr[i], i, &ptr[i]);
    }
    printf("\n\n----------------------------\n\n");
}