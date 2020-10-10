#include <stdio.h>

int main(void)
{
    //변수
    int age = 12;
    printf("%d\n", age);

    age = 13;
    printf("%d\n", age);

    float f = 60.5;
    printf("%.1f\n", f);
    double d = 4.429;
    printf("%.2lf\n", d);

    // 상수
    const int YEAR = 2000; // 상수는 자료형 앞에 const를 붙인다.
    printf("태어난 년도는 %d년도 입니다.\n", YEAR);
    //YEAR = 2001; YEAR 변수가 상수이므로 '2001'이란 값을 할당할 수 없다.
    return 0;
}