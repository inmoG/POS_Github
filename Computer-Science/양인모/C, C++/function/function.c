#include <stdio.h>

//선언
void p(int num); // 반환값이 없고 전달값이 잇는 경우
void p2();       // 반환값 전달값이 없는 경우
//char[50] p3();
int p4(int num1, int num2);

int main()
{
    int num = 2;
    p(num);
    p2();
    //printf(p3());
    int add = p4(10, 15);
    printf("%d", add);
    return 0;
}

//정의
void p(int num)
{
    printf("num은 %d 입니다.\n", num);
}

void p2()
{
    printf("이 함수는 반환값, 전달값이 없습니다.\n");
}

char p3()
{
    return "이 함수는 반환값은 있고 전달값이 없습니다.\n";
}

int p4(int num1, int num2)
{
    return num1 + num2;
}

//반환형 함수이름 전달값
// int로 반환하면 int, double, float은 double, float, char은 char 반환할 값이 없다면 void를 사용한다.
//함수를 정의했으면 선언할 때 역시 동일해야한다.