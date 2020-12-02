#include <stdio.h>

int main()
{
	char upper_case[30];
	int count = 0;
	gets(upper_case); // 문장을 입력 받기 위해 gets 사용

    /*
    1. char은 정수형이다.
    2. if eles if else 구문을 적절하게 사용하자, if else를 2개 쓰는 건 비효율적이다.
    3. 중복되는 코드는 항상 제거하자
    4. 불필요한 변수를 사용하지 말자
    */
	for (int i = 0; i < sizeof(upper_case) / sizeof(upper_case[0]); i++) // 30번째 인덱스까지 검사
	{
		if (upper_case[i] == '\0') // i번째 인덱스가 '\0'이면 for문을 종료한다.

		{
			break;
		}
		else if (upper_case[i] < 65 || upper_case[i] > 90) // A(65) ~ Z(90) 가 아닌 값은 특수 문자, 소문자이다.
		{
			continue;
		}
		else
		{
			upper_case[i] += 32; // 대문자면 32 추가해 소문자로 변환 
			count++;
		}
	}

	printf("%s\n", upper_case);
	printf("%d\n", count);
	return 0;

}