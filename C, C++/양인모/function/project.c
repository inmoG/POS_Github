#include <stdio.h>
#include <time.h>

//함수 선언
int getRandomNumber(int level);
void showQuestion(int level, int num1, int num2);
void success();
void fail();

int main(void) // 전달값이 없고 반환값은 int인 함수
{
    //문이 5개가 있고, 각 문마다 점점 어려운 수식 퀴즈가 출제된다.
    //맞히면 통과, 틀리면 실패

    int count = 0;     //맞춘 정답 개수
    srand(time(NULL)); //난수 생성
    for (int i = 1; i <= 5; i++)
    {
        //x * y = ?
        int num1 = getRandomNumber(i); //난수 생성함수
        int num2 = getRandomNumber(i); // 난수 생성함수

        showQuestion(i, num1, num2); // 문제 안내 함수
        int answer = -1;
        scanf_s("%d", &answer); //정답을 입력받는다.

        if (answer == -1)
        {
            printf("프로그램을 종료합니다.\n");
            exit(0); // 프로그램 종료함수
                     //break;
        }
        else if (answer == num1 * num2)
        {
            success();
            count++;
        }
        else
        {
            fail();
        }
    }
    printf("%d개 맞추셨습니다!\n", count);
    return 0;
}

//함수 정의
int getRandomNumber(int level)
{
    return rand() % (level * 7) + 1; // 1 ~ level * 7 범위의 수를 리턴한다.
}

void showQuestion(int level, int num1, int num2)
{
    printf("\n############%d 번째 비밀번호############\n", level);
    printf("%d * %d는 얼마일까요?\n", num1, num2);
    printf("########################################\n");
    printf("\n비민번호를 입력하세요. (종료: -1) >> ");
}

void success()
{
    printf("정답입니다!\n");
}
void fail()
{
    printf("틀렸습니다!\n");
}