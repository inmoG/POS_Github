#include <stdio.h>
int main(void)
{
    /*
    int a;
    double b;

    b = 2.4;
    // a = b; 형 변환 오류 발생
    a = (int)b; // 강제 형 변환

    printf("%d\n", a);
    /*
    형 변환 즉 캐스팅 시 영구적으로 변형 되는 것은 아니다.
    계산식에서 일시적으로 캐스팅을 한다.
    따라서 b를 출력하면 2.4로 출력된다. 
    컴파일러는 형변환 하는 것을 알고 일부러 오류 메시지를 출력하지 않는다.
    
    printf("%f\n", b);

    
    
    int a, b;
    float c, d;

    printf("두 숫자 입력 : ");
    scanf_s("%d %d", &a, &b);

    c = a / b; // 정수형
    d = (float)a / b; // 실수형

    printf("두 수의 비율 : %f %f", c, d);

    형변환은 주로 실수형 변수에서 정수 부분만 추출할 때 사용된다.
    
    double a; 
    int b;
    b = (int)a;

    위 코드는 a의 정수 부분 데이터만 b로 넘어가는 코드이다. 물론 b = a; 로 해도 컴파일러가
    알아서 캐스팅을 해주지만 그렇게 된다면 다른 프로그래머가 보았을 때 이것이 실수 인건지,
    고의로 한 건지 모르므로 오해의 소지가 발생할 수 있다.
    */
    float f;
    int a;
    printf("실수를 입력하세요 : ");
    scanf_s("%f", &f);

    a = (int)f;

    printf("f의 소수점 앞 자리 값은 %d\n", a);

    printf("실수 %f X 100은 %f\n", f, f * 100);

    f = f * 100;

    a = a * 100;

    printf("f의 소수점 앞 자리 값 X 100은 %d\n", a);
    f = f - a;
    if (f < 0)
    {
        f = -1 * f;
        printf("f : %f\n", f);
        printf("f < 0 : 소수점 뒤 2자리는 %d", (int)f);
    }
    else
    {
        printf("f : %f\n", f);
        printf("f > 0 : 소수점 뒤 2자리는 %d", (int)f);
    }
    return 0;
}