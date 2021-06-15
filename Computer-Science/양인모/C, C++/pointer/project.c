#include <stdio.h>
#include <time.h> // clock() 를 선언하기 위해서 사용한다.

int level;
int arrayFish[6]; // 어항
int *cursor;

void initData();
void printfFishes();
void decreaseWater(long elapsedTime);
int checkFishAlive();

/*
물고기가 6마리 있다.
어항에 살고 있는데 사막이에요
사막이 너무 덥고 건조해 물이 빨리 증발합니다.
물이 다 증발하기 전에 물을 줘서 물고기를 살려주세요
물고기는 시간이 지날수록 커져서 결국에는 잡아먹힙니다..!!!

배열[5] 사용?
포인터 변수를 사용해 배열에 접근한다. =>> 배열의 인덱스 한 개는 곧 어항 한 개.
포인터로 배열에 접근해 값을 변화시킬려 하는듯?
배열의 값은 물? 어항? 
시간이 지날수록 물은 -- , 물고기는 ++
클릭하면 물을 줄 수 있다. => 갑을 입력..?

*/

int main_void(void)
{

    long startTime = 0;        // 게임 시작 시간
    long totalElapsedTime = 0; // 총 경과 시간
    long prevElapsedTime = 0;  // 직전 경과 시간 ( 최근에 물을 준 시간 간격)

    int num; // 몇 번 어항에 물을 줄 것인지, 사용자가 입력하는 공간.
    initData();

    cursor = arrayFish;  // arrayFish[0],  arrayFish[1],  arrayFish[2]에 접근 가능함.
    startTime = clock(); // 현재 시간을 millisecond (1000분의 1초) 단위로 반환

    while (1)
    {
        printfFishes();
        printf("몇 번 어항에 물을 주시겠어요? : \n");
        scanf_s("%d", &num);

        if (num < 1 || num > 6) // 어항은 1번 ~ 6번까지다. 그래서 1 ~ 6 을 벗어난 수를 입력하면 다시 입력해야 한다.
        {
            printf("잘못 입력하셨습니다.\n");
            continue; // if문을 벗어나 while문으로 올라간다.
        }
        else
        {
            // 총 경과시간
            totalElapsedTime = (clock() - startTime) / CLOCKS_PER_SEC; // millisecond 단위이므로 초 단위로 변환한다.
            printf("총 경과시간 :  %ld 초가 흘렀습니다. \n", totalElapsedTime);

            // 직전 물 준 시간 (마지막으로 물 준 시간) 이후로 흐른 시간
            prevElapsedTime = totalElapsedTime - prevElapsedTime;
            printf("마지막 물 준 시간 이후 : %ld 초가 흘렀습니다.\n", prevElapsedTime);

            //어항의 물이 감소
            decreaseWater(prevElapsedTime);

            //사용자가 입력한 어항에 물을 준다.
            // 1. 어항의 물이 이미 0이면 ? 물을 주지 않는다 >>  물이 0이면 물고기가 죽었으므로.
            if (cursor[num - 1] <= 0) // 어항은 0부터 시작하고 사용자가 입력하는 값은 1부터 시작하므로 1을 빼준다.
            {
                printf("%d번 어항의 물이 다 떨어져 물고기가 죽었습니다.\n", num);
            }
            // 2. 어항의 물이 0이 아닌경우 ? >> 물을 주고 100 이 넘는지 체크한다.   현재 어항의 물 + 1 <= 100
            else if (cursor[num - 1] + 1 <= 100)
            {
                // 물을 준다.
                printf("%d번 어항에 물을 주겠습니다.\n", num);
                cursor[num - 1] += 1;
            }

            // 3. 레벌업 하는 경우 >> 게임 경과시간이 20초가 넘었으면 레벨이 올라간다.
            if (totalElapsedTime / 20 > level - 1) // 25(총 경과시간) / 20 > 1 - 1
            {
                // 레벨업!
                level++;
                printf("레벨업!!!\n\n %d레벨에서 %d레벨로 업그레이드!\n", level - 1, level);
                if (level == 5)
                {
                    printf("%d레벨 달성!! 최종레벨을 달성했기 때문에 게임이 종료됩니다.\n", level);
                    exit(0); // 게임 종료
                }
            }
        }

        // 모든 물고기가 죽었는지 확인한다.
        if (checkFishAlive() == 0)
        {
            //물고기 죽음..
            printf("모든 물고기가 죽었습니다....ㅠㅠ\n");
            exit(0);
        }
        else
        {
            // 최소 한마리 이상의 물고기가 살음
            printf("물고기가 아직 살아있어요!!\n");
        }
        prevElapsedTime = totalElapsedTime;

        // 10초
    }

    return 0;
}

void initData()
{
    level = 1; // level 1 ~ 5

    for (int i = 0; i < 6; i++)
    {
        arrayFish[i] = 100; // 물 높이
    }
}

void printfFishes()
{
    printf("%3d번 %3d번 %3d번 %3d번 %3d번 %3d번\n", 1, 2, 3, 4, 5, 6);

    for (int i = 0; i < 6; i++)
    {
        printf("  %3d ", arrayFish[i]);
    }
    printf("\n\n");
}

void decreaseWater(long elapsedTime)
{
    for (int i = 0; i < 6; i++)
    {
        arrayFish[i] -= (level * 3 * (int)elapsedTime); // 3은 난이도 조절을 위한 값
        if (arrayFish[i] < 0)
        {
            //어항에 물이 0보다 작아지면 0으로 초기화해 물이 없다는 걸 알린다.
            arrayFish[i] = 0;
        }
    }
}

int checkFishAlive()
{
    for (int i = 0; i < 6; i++)
    {
        if (arrayFish[i] > 0)
        {
            // 최소 한 마리 이상 물고기가 살아있으면 1을 리턴한다.
            return 1;
        }
    }
    // 모든 물고기가 죽었으면 0을 리턴한다.
    return 0;
}