#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 10000

int main_file()
{
    /*
	파일입출력
	메모리의 값은 다시 실행 시 다른 값이 저장된다.
	왜냐하면 메모리는 휘발성이여서 메모리에 올라와 있는 값을 저장하지 않는다.

	그래서 파일에 값을 저장해야 한다.
	파일은 HDD에서 저장해 항상 동일한 값을 가져 메모리에 올라갈 때도 언제나 동일한 값이 올라갈 수 있다.
	
	fputs : 파일에 어떤 데이터를 저장한다.
	fgets : 저장된 데이터를 불러온다.
	

	char line[MAX]; // char line[10000]
	/*
	경로 지정 시 \ 가 아니라 \\ 를 사용해야 한다.
	r 읽기
	w 쓰기
	a 이어쓰기
	t 텍스트
	b 바이너리

	이유는 모르겠다만 내 파일이 D 드라이브에 있어 C드라이브의 파일은 건들지 못하는 것 같다.
	
	-------------------------------------------------------------------------------------------
	fputs, fgets 는 문자열을 읽고 쓰고 할 때 사용한다.

	fputs : 파일에 쓰기

	FILE* file = fopen("D:\\test1.txt", "wb"); // w 는 파일의 데이터를 삭제하고 다시 쓴다. 이어서 작성할 경우 a 이어쓰기를 사용해야 한다.

	if (file == NULL) // 경로에 파일이 존재하지 않다면
	{
		printf("파일 열기 실패\n");
		return 1; // 열기 실패 시 종료
	}

	fputs("fputs를 이용해 파일에 글을 적겠습니다.\n", file);  // 포인터를 사용해 test1.txt의 주소에 접근 ->> 해당 주소에 텍스트 입력
	fputs("글이 잘 적히고 있나요?!!\n", file);
		
	fclose(file);
		// 파일을 종료시켜야 저장된다.
		// 파일을 열고나서 닫지 않은 상태에서 프로그램에 문제가 생긴다면 데이터 손실 가능성이 있다.

	

	// fgets : 파일 읽기
	FILE* file = fopen("D:\\test1.txt", "rb");

	if (file == NULL)
	{
		printf("파일 열기 실패\n");
		return 1; // 열기 실패 시 종료
	}
	while (fgets(line, MAX, file) != NULL)
	{
		/*
		fgets(line, MAX, file) != NULL
		line : 읽어올 텍스트를 담을 배열
		MAX : 크기
		file : 포인터, 파일경로
		
		printf("%s", line);
	}

	fclose(file);
	*/

    // fprintf, fscanf
    // printf("%d %d", num, num2)
    // scanf("%d %d", &num, num2)
    // fprintf, fscanf는 printf, scanf 와 마찬가지로 정형화된 포멧의 데이터를 읽고 쓰는 경우 사용한다.

    int num[6] = {0, 0, 0, 0, 0, 0}; // 로또 추첨번호
    int bonus = 0;                   // 보너스 번호
    char str1[MAX];
    char str2[MAX];
    // 이 변수들은 파일을 쓸 때 사용하는 변수다.

    // 파일 쓰기
    FILE *file = fopen("D:\\test3.txt", "wb");
    if (file == NULL)
    {
        printf("파일 열기 실패!");
        return 1;
    }

    fprintf(file, "%s %d %d %d %d %d %d\n", "추첨번호 ", 1, 2, 3, 4, 5, 6);
    fprintf(file, "%s %d\n", "보너스 번호 ", 7);

    fclose(file);

    // 파일 읽기

    FILE *file = fopen("D:\\test2.txt", "rb");
    if (file == NULL)
    {
        printf("파일 열기 실패!");
        return 1;
    }

    fscanf(file, "%s %d %d %d %d %d %d", str1,
           &num[0], &num[1], &num[2], &num[3], &num[4], &num[5]); // char 포인터 변수는 &를 사용하지 않아도 된다. str1은 문자열을 num은 정수를 불러온다.
    printf("%s %d %d %d %d %d %d\n", str1,
           num[0], num[1], num[2], num[3], num[4], num[5]);

    fscanf(file, "%s %d", str2, &bonus);
    printf("%s %d\n", str2, bonus);

    fclose(file);

    return 0;
}