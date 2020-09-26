#include <stdio.h>
#include <time.h>

int main_void()
{
    srand(time(NULL));
    int num = rand() % 100 + 1;
    //printf("숫자는 ?! %d", num);
    int chance = 5;
    int answer = 0;

    while (chance > 0)
    {
        // 기회가 다 소진되면 게임 종료
        printf("기회가 %d번 남았습니다.\n", chance--);
        printf("숫자를 맞혀보세요! : \n");
        scanf_s("%d", &answer);
        if (num == answer)
        {
            printf("정답입니다!");
            break;
        }
        else if (answer > num)
        {
            if (chance == 0)
            {
                printf("안타깝게도~ 정답은! %d번 이였습니다 ㅎㅎ", num);
                break;
            }
            printf("땡 틀렸습니다. 숫자를 낮춰보세요\n");
        }
        else if (answer < num)
        {
            if (chance == 0)
            {
                printf("안타깝게도~ 정답은! %d번 이였습니다 ㅎㅎ", num);
                break;
            }
            printf("땡 틀렸습니다. 숫자를 높여보세요\n");
        }
        else
        {
            printf("안타깝게도~ 정답은! %d번 이였습니다 ㅎㅎ", num);
        }
    }

    return 0;

    /*
	int i = 1;
	switch (i)
	{
	case 1:
		printf("hello\n");
		break;
	case 2:
		printf("hi\n");
		break;
	default:
		break;
	}

	
	for (int i = 0; i <= 30; i++) {
		if (i >= 6 && i <= 10)
		{	
			if (i == 7)
			{
				printf("%d번은 결석했어요!\n", i);
				continue; // break와 달리 continue는 만나면 조건식으로 올라간다.

			}
			printf("%d번은 조별과제 하세요\n", i);
			
		}

	}


	
	for (int i = 1; i <= 30; i++)
	{
		if (i == 7)
		{
			printf("%d번 결석했어요!!\n", i);
			//break;
		}

		else if (i>=6 && i<=10)
		{
			printf("%d 번은 발표하세요!\n", i);
			
		}

	}
	*/

    /*
	for (int i = 1; i <= 30; i++)
	{
		if (i >= 6)
		{
			printf("나머지는 집에 가세요!\n");
			break;
		}
		else
		{
			printf("%d 번은 발표하세요!\n", i);
		}

	}
	*/

    /*
	int age = 120; 
	//8~13
	 //14~16
	 // 17 ~ 19
	
	if (age <= 13)
	{
		printf("넌 초등학생\n");
	}
	else if (age <= 16)
	{
		printf("넌 중학생\n");
	}
	else {
		printf("넌 고등학생\n");
	}
	*/
