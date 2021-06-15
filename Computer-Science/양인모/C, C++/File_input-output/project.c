#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 10000

int main(void)
{
    /*
	비밀번호를 입력 받는다.
		맞는 경우 : 비밀 일기를 읽어와 보여주고, 계속 작성할 수 있도록 한다.
		틀릴 경우 : 경고메시지 출력 > 프로그램 종료
	*/

    char line[MAX];     // 파일을 읽을 때 데이터를 담을 배열
    char contents[MAX]; // 일기장에 작성할 내용을 담는 배열
    char password[20];  // 비밀번호 입력
    char c;             // 비밀번호 입력할 때 키값 확인용(마스킹)

    printf("굿노트에 오신 걸 환영합니다. \n");
    printf("비밀번호를 입력해주세요 : ");

    int i = 0;

    while (1)
    {
        /*
		getchar() | getch()
		getchar() : 엔터를 입력받아야 동작을 한다.
		getch() : 키 입력시 바로바로 동작을 한다.
		*/
        c = getch(); // 비밀번호 입력
        if (c == 13) // 13은 아스키코드로 Enter를 나타낸다.
        {
            // 비밀번호를 다 입력하면 Enter를 누르고 이는 입력 종료를 나타냄.
            // Enter >> 비밀번호 입력 종료
            password[i] = '\0'; // 배열 마지막
            break;
        }
        else
        {
            printf("*");
            password[i] = c;
        }
        i++;
    }

    printf("\n\n === 비밀번호 확인 중입니다.... === \n\n");
    if (strcmp(password, "inmoYang") == 0) // strcmp함수는 비밀번호가 맞다면 0을 리턴하고 그렇지 않다면 1 or -1 을 리턴한다.
    {
        printf("비밀번호 확인 완료! \n\n");
        char *fileName = "D:\\Study\\Coding\\C_lang\\File_put-get\\File_put-get\\GoodNotes.txt";
        FILE *file = fopen(fileName, "a+b"); // 파일이 없으면 생성, 존재하면 append 한다. 즉 파일에 내용을 추가해 작성한다.

        if (file == NULL)
        {
            printf("파일 열기 실패");
            return 1;
        }

        while (fgets(line, MAX, file) != NULL) // 작성한 일기 출력
        {
            printf("%s", line);
        }

        printf("\n\n내용을 계속 작성하세요, 종료하시려면 'EXIT'를 입력하세요\n");

        while (1) // 일기 작성
        {
            scanf("%[^\n]", contents); // 줄바꿈(\n)이 나오기 전까지 읽어들인다. 즉 한 문장씩 읽어들인다.
            getchar();                 // Enter 입력(\n), Flush 처리 >> 문장을 작성하고 다음 문장을 작성하기 위해 Enter를 입력하는데 이 Enter를 임시로 무시한다.

            if (strcmp(contents, "EXIT") == 0) // 일기장 작성 종료
            {
                printf("일기장 작성을 종료합니다.");
                break;
            }
            fputs(contents, file); // 작성한 내용을 일기장에 저장한다.
            fputs("\n", file);     // Enter(\n)를 getchar()을 사용해 임시로 무시(Flush) 처리 하였으므로 추가해 한줄씩 작성하도록 한다.
        }
        fclose(file);
    }
    else
    {
        printf(" === 비밀번호가 틀렸습니다. ===");
    }
    return 0;
}