#include <stdio.h>

int main()
{
    char name[256];
    /*
	int koreanScore;
	int englishScore;
	scanf_s("%s %d %d", name, sizeof(name), &koreanScore, &englishScore);
	printf("%s %d %d", name, koreanScore, englishScore);

	*/

    printf("이름이 뭐예요? ");
    scanf_s("%s", name, sizeof(name)); //배열은 %s, &대신 변수명, 변수사이즈 체크를 위해 sizeof()사용

    int age;
    printf("몇살이예요? ");
    scanf_s("%d", &age);

    float weight;
    printf("몸무게는 몇 kg 이예요? ");
    scanf_s("%f", &weight);

    double height;
    printf("키는 몇 cm 이예요? ");
    scanf_s("%lf", &height);

    char what[256];
    printf("무슨 범죄를 저질렀나요? ");
    scanf_s("%s", what, sizeof(what));

    printf("\n\n------범죄자 정보------\n\n");
    printf("이름   : %s\n", name);
    printf("나이   : %d\n", age);
    printf("몸무게 : %.2f\n", weight);
    printf("키     : %.2lf\n", height);
    printf("범죄   : %s\n", what);

    return 0;

    /*
	scanf 대신 scanf_s를 써야한다. 버퍼오버플로우를 막기위해서
	배열은 char name[256] 이라 정의한다.
	입력받을 때 배열은 %s, 변수명, sizeof(변수명) 식으로 입력한다., 그 외는 &변수명을 사용
	int는 %d, float은 %f, double은 %f, char는 %c, string은 %s, short는 %d, long은 %ld로 출력한다.
	int는 %d, float은 %f, double은 %lf, char는 %c, string은 %s, short는 %hd, long은 %ld로 출력한다.
	
-------------------------------------------

	int one, two, three;
	printf("입력해주세요 : \n");
	scanf_s("%d %d %d", &one, &two, &three);
	printf('%d\n', one);
	printf('%d\n', two);
	printf('%d\n', three);
	
	char ch;

	short sh; //정수
	int i;
	long lo;

	float fl;
	double du;

	printf("char 형 변수 입력 : ");
	scanf("%c", &ch);
	//한글은 2바이트 이상을 차지해서 1바이트인 char 형에다 할당하면 버퍼 오버플로우 발생
	//허용된 데이터 이상을 집어넣는지 검사해야 한다.
	printf("short 형 변수 입력 : ");
	scanf("%d", &sh); // 입력받을 변수를 지정한다.
	printf("int 형 변수 입력 : ");
	scanf("%d", &i);
	printf("long 형 변수 입력 : ");
	scanf("%d", &lo);

	printf("float 형 변수 입력 : ");
	scanf("%f", &fl);
	printf("double 형 변수 입력 : ");
	scanf("%lf", &du);

	printf("char형 : %c, short형 : %d, int형 : %d", ch, sh, i);
	printf("long형 : %d, float형 : %f, double형 : %f\n", lo, fl, du);

	*/

    //문자 : char c = 'A';

    //char str[256]; //문자열 문자 256개를 사용할 수 있는 공간.
    //scanf_s("%s", str, sizeof(str)); //sizeof()를 사용해 256개까지만 문자를 받겠다고 선언
    //printf("%s\n", str);
}