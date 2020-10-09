#include <stdio.h>
#include <time.h>

/*
파일이름 : m_Array-Project
기능 : 10마리의 서로 다른 동물 (각 카드 2장씩)
사용자로부터 2개의 입력 값을 받아 >> 같은 동물 찾으면 카드 뒤집기
모든 동물 쌍을 찾으면 게임종료
총 실패횟수 알려주기
게임제한시간 내에 다 찾아야 한다. (120초)

*/

int arrayAnimal[4][5]; // 카드 지도 (20장)            5개 칸 배열이 4개 생성된다.
int checkAnimal[4][5]; // 뒤집혔는지 여부를 확인한다.
char *strAnimal[10];   // 배열 인덱스의 주소값을 저장해 빠르게 데이터에 접근할 수 있다??

//함수 선언
void initAnimalArray();
void initAnumalName();
int getEmptyPosition();
int conv_pos_x(int x);
int conv_pos_y(int y);
void printAnimals();
void printQuestion();
int foundAllAnimals();
void shuffleAnimal();

int main_void()
{
    srand(time(NULL)); // 난수생성

    initAnimalArray();
    initAnumalName();
    shuffleAnimal();

    int failCount = 0; // 실패 횟수

    while (1)
    {
        int select1 = 0; // 사용자가 선택한 처음 수
        int select2 = 0; // 사용자가 선택한 두번째 수

        printAnimals();  // 동물 위치 출력
        printQuestion(); // 문제 출력 (카드지도)
        printf("뒤집을 카드를 2개 고르세요 : ");
        scanf_s("%d %d", &select1, &select2);
        if (select1 == select2) // 같은 카드 선택 시 무효
        {
            printf("동일한 카드를 선택할 수 없습니다.\n다시 선택해주세요\n");
            continue;
        }
        //좌표에 해당하는 카드를 뒤집어보고	같은지 안같은지 비교한다.

        //정수 좌표를 (x, y)로 변환한다.

        // 첫번째 카드 좌표
        int firstSelect_x = conv_pos_x(select1);
        int firstSelect_y = conv_pos_y(select1);
        // 두번째 카드 좌표
        int secondSelect_x = conv_pos_x(select2);
        int secondSelect_y = conv_pos_y(select2);

        //같은 동물인 경우
        //
        if (
            checkAnimal[firstSelect_x][firstSelect_y] == 0 && checkAnimal[secondSelect_x][secondSelect_y] == 0 //카드가 뒤집히지 않은 경우   좌표값이 0이면 뒤집히지 않았다는 의미이다.
            &&
            (arrayAnimal[firstSelect_x][firstSelect_y] == arrayAnimal[secondSelect_x][secondSelect_y]) //두 동물이 같은지
        )
        {
            //정답을 출력한다.
            printf("\n%s 발견!!", strAnimal[arrayAnimal[firstSelect_x][firstSelect_y]]);
            checkAnimal[firstSelect_x][firstSelect_y] = 1;
            checkAnimal[secondSelect_x][secondSelect_y] = 1;
        }
        else //다른 동물인 경우
        {
            printf("\n\n 땡! 틀렸거나 뒤집힌 카드 입니다.\n");
            printf("%d %s", select1, strAnimal[arrayAnimal[firstSelect_x][firstSelect_y]]);
            printf("%d %s", select2, strAnimal[arrayAnimal[secondSelect_x][secondSelect_y]]);
            printf("\n\n");
            failCount++;
        }

        if (foundAllAnimals() == 1) // 모든 동물을 찾았는지 여부를 출력한다. 참 : 1     거짓 : 0
        {
            printf("\n\n 축하합니다. 모든 동물을 다 찾으셨어요!!!!!!\n");
            printf("%d 번 틀리셨네요..ㅠㅠ", failCount);
            break; // 다 찾아서 if 문을 빠져나온다.
        }
    }
    return 0;
}

//함수 정의
void initAnimalArray()
{
    // 배열을 출력한다.
    for (int i = 0; i < 4; i++) // arrayAnimal[4]를 의미
    {
        for (int j = 0; j < 5; j++) //  arrayAnimal[5]를 의미
        {
            arrayAnimal[i][j] = -1;
        }
    }
}

void initAnumalName()
{
    // 동물 이름을 정하는 함수
    strAnimal[0] = "강아지";
    strAnimal[1] = "고양이";
    strAnimal[2] = "돼지";
    strAnimal[3] = "낙타";
    strAnimal[4] = "타조";
    strAnimal[5] = "기린";
    strAnimal[6] = "호랑이";
    strAnimal[7] = "사자";
    strAnimal[8] = "코뿔소";
    strAnimal[9] = "코끼리";
}

void shuffleAnimal()
// 동물들의 자리를 랜덤으로 정하는 함수
{
    // ⬜⬜⬜⬜⬜        동물 한개당 예를들어 첫번째줄의 3번칸 세번째의 4번째 칸에 저장되어야 하므로  이중 for문 사용
    // ⬜⬜⬜⬜⬜			동물은 총 10마리며 한 쌍씩 저장되어야 하므로 1마리당 for문이 2번 돌아야하므로 아래와 같이 작성한다.
    // ⬜⬜⬜⬜⬜
    // ⬜⬜⬜⬜⬜

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            int pos = getEmptyPosition();
            int x = conv_pos_x(pos);
            int y = conv_pos_y(pos);

            arrayAnimal[x][y] = i;
        }
    }
}

// 좌표에서 빈 공간 찾기
int getEmptyPosition()
{
    while (1)
    {
        // ⬜⬜⬜⬜⬜			1,   2,	 3,	 4,	 5
        // ⬜⬜⬜⬜⬜			6,	 7,	 8,	 9,	10
        // ⬜⬜⬜⬜⬜			11, 12, 13, 14, 15
        // ⬜⬜⬜⬜⬜			16, 17, 18, 19, 20
        // 19 >> 3,4
        // 6  >> 1,0

        int randPos = rand() % 20; // 0 ~ 19 사이 숫자 반환
        int x = conv_pos_x(randPos);
        int y = conv_pos_y(randPos);

        if (arrayAnimal[x][y] == -1)
        {
            return randPos;
        }
    }
    return 0;
}

int conv_pos_x(int x)
{
    // ⬜⬜⬜⬜⬜			0,	1,	2,	3,	4
    // ⬜⬜⬜⬜⬜			5,	6,	7,	8,	9
    // ⬜⬜⬜⬜⬜			10,	11,	12,	13,	14
    // ⬜⬜⬜⬜⬜			15,	16,	17,	18,	19
    // 각 줄을 5로 나눈다.
    // 0 / 5 | 1 / 5 | 2 / 5 >> 0
    // 5 / 5 | 6 / 5 | 7 / 5 >> 1
    // 10 / 5 | 11 / 5 | 12 / 5 >> 2
    // 19 >> 3,4

    return x / 5;
}

int conv_pos_y(int y)
{
    // ⬜⬜⬜⬜⬜			0,	1,	2,	3,	4
    // ⬜⬜⬜⬜⬜			5,	6,	7,	8,	9
    // ⬜⬜⬜⬜⬜			10,	11,	12,	13,	14
    // ⬜⬜⬜⬜⬜			15,	16,	17,	18,	19
    // 각 줄을 5로 나눠 나머지 값을 y 로 사용한다.
    // 10 / 5 >> 몫은 2 나머지는 0 |  11 / 5 >> 몫은 2 나머지는 1 | 12 / 5 >> 못은 2 나머지는 2

    return y % 5;
}

void printAnimals() // 동물 위치 출력
{
    // ⬜⬜⬜⬜⬜			1,   2,	 2,  3,  4
    // ⬜⬜⬜⬜⬜			5,	 6,	 6,	 5,	 7
    // ⬜⬜⬜⬜⬜			11, 12, 13, 14, 15
    // ⬜⬜⬜⬜⬜

    printf("\n\n===이건 비밀인데.. 몰래  보여줍니다.. ===\n\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%8s", strAnimal[arrayAnimal[i][j]]);
        }
        printf("\n");
    }
    printf("\n\n==========================================\n\n");
}

void printQuestion() // 문제를 출력하는 함수
{
    printf("\n\n(문제)\n");
    int seq = 0; // 동물 카드의 순서를 나타낸다.

    //seq 배열					//checkAnimal 배열			// 1은 정답을 나타냄

    // ⬜⬜⬜⬜⬜			하마,  1,	2,	 3,   4				1	0	0	0	0
    // ⬜⬜⬜⬜⬜			5,	   6,	7, 	 8,   9				0	0	0	0	0
    // ⬜⬜⬜⬜⬜			10,	  11,  12, 하마, 14				0	0	0	1	0
    // ⬜⬜⬜⬜⬜			15,	  16,  17,  18,	 19				0	0	0	0	0

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (checkAnimal[i][j] != 0) // 카드를 뒤집어서 정답을 맞혔으면 '동물 이름' 출력
            {
                // 좌표값이 0 이 아니면 정답이다.
                printf("%8s", strAnimal[arrayAnimal[i][j]]);
            }
            else // // 아직 뒤집지 못했으면 (정답을 못맞혔으면) 뒷면 >> 위치를 나타내는 숫자
            {
                printf("%8d", seq);
            }
            // 값을 입력할 때마다 seq 값이 증가한다.
            seq++;
        }
        printf("\n");
    }
}

int foundAllAnimals() // 정수값 1을 리턴하므로 반환형을 int로 사용한다.
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            // 모든 카드가 뒤집혔는지 여부를 체크하므로 checkAnimal 배열을 사용한다.
            if (checkAnimal[i][j] == 0)
            {
                //뒤집히지 않은 카드가 1장이라도 있을 경우
                return 0;
            }
        }
    }
    // 모든 카드가 뒤집혀서 " 0 " 을 return 하지 않고 for문이 종료되어 1 을 리턴한다.

    return 1;
}
