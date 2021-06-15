#include <stdio.h>
#include <time.h>

/*
5마리의 고양이가 있다.
아무 키나 눌러 랜덤으로 고양이를 뽑되, 5마리 모두 다 수집하면 게임이 끝난다.

중복발생 가능!!
--------------------

고양이 구조체
{
	이름
	나이
	성격
	키우기 난이도 (레벨)
}
*/

typedef struct
{
    char *name;      // 이름
    int age;         // 나이
    char *character; // 성격
    int level;       // 키우기 난이도( 1 ~ 5 / 5가 가장 어려움)

} CAT;

// 구조체 배열 선언
// 현재까지 보유한 고양이 수를 나타내는 배열
int collection[5] = {0, 0, 0, 0, 0}; // 초기화

// 전체 고양이 리스트
CAT cats[5];

void initCats();
void printCat(int selected);
int checkCollection();

int main(void)
{
    srand(time(NULL));
    initCats();
    while (1)
    {
        printf("두근두근~! 어느 고양이의 집사가 될까요?!!!\n아무 키나 눌러서 확인하세요!\n");
        getchar(); // 입력 대기

        int selected = rand() % 5; // 0 ~ 4 사이의 숫자를 반환한다.
        printCat(selected);        // 뽑은 고양이 정보 출력
        collection[selected] = 1;  // 고양이 뽑기를 처리한다. 즉 n번째 고양이를 뽑았을 경우 해당 배열을 1로 초기화 해 고양이를 뽑았다는 걸 배열에 표시한다.

        int collectAll = checkCollection(); // 고양이 수집 결과를 반환한다.
        if (collectAll == 1)
        {
            break; // 모든 고양이를 수집했으므로 게임 종료
        }
    }

    return 0;
}

void initCats()
{
    cats[0].name = "깜냥이";
    cats[0].age = 1;
    cats[0].character = "조용함";
    cats[0].level = 1;

    cats[1].name = "돼냥이";
    cats[1].age = 2;
    cats[1].character = "게으름";
    cats[1].level = 2;

    cats[2].name = "사냥이";
    cats[2].age = 3;
    cats[2].character = "사나움";
    cats[2].level = 3;

    cats[3].name = "활냥이";
    cats[3].age = 4;
    cats[3].character = "활발함";
    cats[3].level = 4;

    cats[4].name = "개냥이";
    cats[4].age = 5;
    cats[4].character = "개같음";
    cats[4].level = 5;
}

void printCat(int selected)
{
    printf("\n\n===당신은 이 고양이의 집사가 되었어요!===\n\n");
    printf("이름    :    %s\n", cats[selected].name);
    printf("나이    :    %d\n", cats[selected].age);
    printf("특징    :    %s\n", cats[selected].name);
    printf("레벨    :    ");
    for (int i = 0; i < cats[selected].level; i++)
    {
        printf("%s", "♥");
    }
    printf("\n\n");
}

int checkCollection()
{
    // 1. 현재 보유한 고양이 목록을 출력한다.
    // 2. 다 모았는지 여부를 반환한다.
    int collectAll = 1; // 다 모았는지 여부를 체크하는 변수

    printf("\n\n === 보유한 고양이 목록입니다. === \n\n");
    for (int i = 0; i < 5; i++)
    {
        if (collection[i] == 0) // 빈 박스는 0을 가지고 있다. 즉 고양이 수집 X
        {
            printf("%10s", "(빈 박스)");
            collectAll = 0; // 다 모으지 못했을 경우 0을 할당한다.
        }
        else // 고양이 수집 O
        {
            printf("%10s", cats[i].name);
        }
    }
    printf("\n===================================\n\n");
    if (collectAll) // 고양이를 다 모았다면 기존 값인 1을 가진다. 1은 참을 의미해 if문이 실행된다.
    {
        printf("축하합니다! 모든 고양이를 수집하셨군요!! 잘 키워주세용~.~");
    }

    return collectAll;
    /*
	고양이를 다 수집했다면 collectAll 변수는 기존값인 1을 반환하지만 
	다 수집하지 못했다면 0을 반환한다.
	*/
}