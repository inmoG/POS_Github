# __배열__
배열(array)은 같은 타입의 변수들로 이루어진 유한 집합으로 정의된다. 배열을 구성하는 각각의 값을 배열 요소(element)라고 하며, 배열에서의 위치를 가리키는 숫자는 인덱스(index)라고 한다.

아래와 같이 세 개의 점수를 저장하고 평균을 출력하는 프로그램이 있다.
```
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Scores
    int score1 = 72;
    int score2 = 73;
    int score3 = 33;

    // Print average
    printf("Average: %i\n", (score1 + score2 + score3) / 3);
}
```
점수의 개수가 훨씬 더 많아 진다면, 변수(score)의 값을 추가된 만큼 계속 추가시켜야 한다. 이 때 활용할 수 있는 것이 배열이다.

```
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Scores
    int scores[3];
    scores[0] = 72;
    scores[1] = 73;
    scores[2] = 33;

    // Print average
    printf("Average: %i\n", (scores[0] + scores[1] + scores[2]) / 3);
```
## __전역 변수__
아래 코드에서 scores 배열의 크기를 정해주는 N이라는 변수를 새로 선언했다.

만약 N이 고정된 값(상수)이라면 그 값을 선언할 때 const를 앞에 붙여서 전역 변수, 즉 코드 전반에 거쳐 바뀌지 않는 값임을 지정해줄 수 있다.

관례적으로 이런 전역 변수의 이름은 대문자로 표기 한다.
```
#include <cs50.h>
#include <stdio.h>

const int N = 3;

int main(void)
{
    // 점수 배열 선언 및 값 저장
    int scores[N];
    scores[0] = 72;
    scores[1] = 73;
    scores[2] = 33;

    // 평균 점수 출력
    printf("Average: %i\n", (scores[0] + scores[1] + scores[2]) / N);
```

## __배열의 동적 선언 및 저장__
위 코드는 값에 한계가 있었다. 좀 더 동적으로 실행하기 위해 아래와 같이 작성할 수 있다.
```
#include <cs50.h>
#include <stdio.h>

float average(int length, int array[]);

int main(void)
{
    // 사용자로부터 점수의 갯수 입력
    int n = get_int("Scores:  ");

    // 점수 배열 선언 및 사용자로부터 값 입력
    int scores[n];
    for (int i = 0; i < n; i++)
    {
        scores[i] = get_int("Score %i: ", i + 1);
    }

    // 평균 출력
    printf("Average: %.1f\n", average(n, scores));
}

//평균을 계산하는 함수
float average(int length, int array[])
{
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += array[i];
    }
    return (float) sum / (float) length;
}
```
