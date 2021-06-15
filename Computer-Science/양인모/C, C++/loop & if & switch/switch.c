#include <stdio.h>

int main(void)
{
    /*
	switch 문을 공부합니다.

	switch ( 변수 ) {
		 case  값1 :
			// 명령들;
			break;
		case 값2 :
			// 명령들;
			break;
			//.. (생략) ..


	이 때 switch 문에 사용될 변수로는 반드시 정수 데이터를 보관하는 변수여야 합니다. 
	다시말해 '변수' 부분에 들어가는 변수들의 타입은 char, short, int, long 중 하나여야 한다. 
	만약 input 이 float 이나 double 이라면 컴파일시 오류가 발생되게 됩니다.

	'값' 에 위치하는 것들이 무조건 상수여야 한다.
	만약 '값' 부분에 변수들이 오게된다면 오류가 발생한다.
	*/

    /*
	int input;

	printf("마이펫 \n");
	printf("무엇을 하실 것인지 입력하세요 \n");
	printf("1. 밥주기 \n");
	printf("2. 씻기기 \n");
	printf("3. 재우기 \n");

	scanf_s("%d", &input, sizeof(input));

	----------------------------------------
	if (input == 1)
	{
		printf("아이 맛있어!! \n");
	}
	else if (input == 2)
	{
		printf("아이 시원해~! \n");
	}
	else if(input == 3)
	{
		printf("Zzzz..\n");
	}
	else
	{
		printf("무슨 말이야..!!\n");
	}
	----------------------------------------
	
	switch (input){
	case 1:
		printf("아이 맛있어!! \n");
		break;

	case 2:
		printf("아이 시원해!\n");
		break;

	case 3:
		printf("Zzzz..\n");
		break;

	default:
		printf("무슨 말이야..!\n");
	}
	*/

    char input;

    printf("(소문자) 알파벳 읽기 \n");
    printf("알파벳 : ");

    scanf_s("%c", &input, sizeof(input));

    switch (input)
    {
    case 'a':
        printf("에이 \n");
        break;
    case 'b':
        printf("비 \n");
        break;
    case 'c':
        printf("씨 \n");
        break;
    default:
        printf("죄송해요.. 머리가 나빠 못 읽어요 ㅠㅠ\n");
        break;
    }
    return 0;
}