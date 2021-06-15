#include <stdio.h>
#define SUBJECTCOUNT 2.0F;
int main()
{
    /*
	char name[256];
		int koreanScore;
		int englishScore;
		scanf_s("%s %d %d", name, sizeof(name), &koreanScore, &englishScore);
		printf("%s %d %d", name, koreanScore, englishScore);
		return 0;
	*/

    int floor;
    printf("몇 층으로 쌓을까요? : ");
    scanf_s("%d", &floor);
    printf("네 %d층으로 쌓겠습니다.\n결과입니다.\n-----------------\n\n", floor);

    for (int i = 0; i <= floor - 1; i++) // for문을 i번 실행한다.
    {
        for (int k = 0; k <= floor - i; k++)
        {
            printf(" "); // " "를 k 번 출력한다.
        }
        for (int j = 0; j < i * 2 + 1; j++)
        {
            printf("*"); // "*"를 j 번 출력한다.
        }
        printf("\n");
    }

    /*
	for (int i = 0; i < floor; i++)
	{
		for (int k = i; k < floor-1; k++)
		{
			printf("S");
		}
		for (int j = 0; j < i * 2 + 1; j++)
		{
			printf("*");

		}
		printf("\n");
	}

	for (int i = 0; i < floor; i++)
	{
		for (int k = i; k < floor; k++)
		{
			printf("S");
		}
		for (int j = 0; j < i * 2 + 1; j++)
		{
			printf("*");

		}
		printf("\n");
	}
	*/
}