#include <stdio.h>

int array_main()
{
    /*
    문장에 대문자가 있다면 소문자로 변환하는 프로그램
    */
	char upper_case[30];
	int count = 0;
	int casting = 0;
	gets(upper_case);

	for (int i = 0; i < sizeof(upper_case) / sizeof(upper_case[0]); i++) // 30번째 인덱스까지 검사
	{
		if (upper_case[i] == '\0')

		{
			break;
		}

		casting = (int)upper_case[i]; // i번째 인덱스 값을 정수로 바꾼다. 

		if (casting < 65 || casting > 90) // A(65) ~ Z(90) 가 아닌 값은 특수문자, 소문자이다. 대문자인 값만 변경해야 하므로 for문으로 올라간다.
		{
			continue;
		}
		else
		{

	
			// 1. i번째 값이 65 ~ 90이면 대문자이다. 따라서 아래 반복문 필요 없음
			for (int ASCII = 65; ASCII <= casting; ASCII++) // casting과 ASCII 값이 같은지 확인하기 위한 반복문
			{
				if (casting == ASCII) 
				{
					upper_case[i] = ASCII + 32; // 같다면 
					count++;
				}
			}
			
		}


	}
	printf("%s\n", upper_case);
	printf("%d\n", count);
	return 0;

}