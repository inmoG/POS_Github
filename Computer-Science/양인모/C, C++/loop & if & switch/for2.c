#include <stdio.h>
int main()
{
    int usranswer;

    printf("컴퓨터가 생각한 숫자를 맞추어 보세요! \n");

    for (;;) // ";;"는 계속 참을 의미한다. 정답을 맞추지 않는이상 for문이 계속 실행된다.
    {
        scanf_s("%d", &usranswer);
        if (usranswer == 5)
        {
            printf("정답입니다!\n");
            break; // break구문이 실행되면 for문 밖으로 탈출한다.
        }
        else
        {
            printf("땡땡땡\n");
        }
    }

    return 0;

    /*
	int i, sum = 0;
	for (i=0; i <= 10000; ++i)
	{
		sum += i;
		printf("%d부터 10000 까지의 합 : %d\n", i, sum);
	}
	
	int i,subject;
	double sum_score, score; // 과목 점수 총합
	sum_score = 0;

	printf("몇 개의 과목 점수를 입력 받을 것인가요?");
	scanf_s("%d", &subject);

	printf("각 과목의 점수를 입력해주세요 \n");
	for (i = 1; i <= subject; i++)
	{
		printf("%d번 과목 점수를 입력해주세요", i);
		scanf_s("%lf", &score); // 입력받은 값을 score 변수에 저장한다.
		sum_score += score;
	}
	printf("전체 과목 평균 : %.2f", sum_score / subject);
	*/
}