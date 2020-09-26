#include <stdio.h>

struct Gameinfo
{
    // 구조체 생성
    char *name;
    int year;
    int price;
    char *company;

    // 구조체 안의 구조체
    struct Gameinfo *friendGame; // 연관업체 게임
};

// typedef
typedef struct Gameinformation
{
    // 구조체 생성
    char *name;
    int year;
    int price;
    char *company;

    // 구조체 안의 구조체
    struct Gameinfo *friendGame; // 연관업체 게임
} GAME_INFO;                     // struct Gameinformation를 GAME_INFO 라고 부르겠다 선언.

typedef struct
{
    // 구조체 생성
    char *name;
    int year;
    int price;
    char *company;

    // 구조체 안의 구조체
    struct Gameinfo *friendGame; // 연관업체 게임
} GAME_INFO_2;                   // 이 struct의 이름을 따로 정의하지않고 바로 GAME_INFO_2 라 선언.

int main_exe()
{
    // [게임출시]
    // 이름 : 나도 게임
    // 발매년도 : 2017
    // 가격 : 50원
    // 제작사 : 나도회사

    char *name = "나도게임";
    int year = 2017;
    int price = 50;
    char *company = "나도회사";

    // [또다른 게임출시]
    // 이름 : 너도 게임
    // 발매년도 : 2017
    // 가격 : 100원
    // 제작사 : 너도회사

    char *name2 = "너도게임";
    int year2 = 2017;
    int price2 = 100;
    char *company2 = "너도회사";

    // [--구조체 사용--] [--구조체 변수명--]
    struct Gameinfo gameinfo1;

    //  [--구조체선언--] [변수명]
    gameinfo1.name = "나도게임";
    gameinfo1.year = 2017;
    gameinfo1.price = 50;
    gameinfo1.company = "나도회사";

    printf("--게임 출시 정보--\n");
    printf("게임     :  %s\n", gameinfo1.name);
    printf("년도     :  %d\n", gameinfo1.year);
    printf("가격     :  %d\n", gameinfo1.price);
    printf("제작사   :  %s\n", gameinfo1.company);

    // 구조체를 배열처럼 초기화
    struct Gameinfo gameinfo2 = {"너도게임", 2017, 100, "너도회사"};

    printf("\n--또 다른 게임 출시 정보--\n");
    printf("게임     :  %s\n", gameinfo2.name);
    printf("년도     :  %d\n", gameinfo2.year);
    printf("가격     :  %d\n", gameinfo2.price);
    printf("제작사   :  %s\n", gameinfo2.company);

    // 구조체 배열
    struct Gameinfo gameArray[2] =
        {
            {"나도게임", 2018, 150, "나도회사"},
            {"너도게임", 2018, 200, "너도회사"}};

    printf("\n--또 다른 게임 출시 정보--\n");
    printf("%s\n", gameArray[0].name);
    printf("%d\n", gameArray[0].year);
    printf("%d\n", gameArray[0].price);
    printf("%s\n", gameArray[0].company);

    printf("\n--또 다른 게임 출시 정보--\n");
    printf("%s\n", gameArray[1].name);
    printf("%d\n", gameArray[1].year);
    printf("%d\n", gameArray[1].price);
    printf("%s\n", gameArray[1].company);

    // 구조체 포인터
    struct Gameinfo *gamePtr; //미션맨
    gamePtr = &gameinfo1;

    /*
	printf("\n\n--미션맨의 게임 출시 정보--\n");
	printf("게임     :  %s\n", (*gamePtr).name);   //gameinfo1의 값을 가져오나..?
	printf("년도     :  %d\n", (*gamePtr).year);
	printf("가격     :  %d\n", (*gamePtr).price);
	printf("제작사   :  %s\n", (*gamePtr).company);
	*/

    //위 방식과 동일한 결과를 출력한다.
    printf("\n\n--미션맨의 게임 출시 정보--\n");
    printf("게임     :  %s\n", gamePtr->name); //gameinfo1의 값을 가져오나..?
    printf("년도     :  %d\n", gamePtr->year); //gamePtr이 가리키는 주소의 year변수 값을 가져온다.
    printf("가격     :  %d\n", gamePtr->price);
    printf("제작사   :  %s\n", gamePtr->company);

    // 구조체 안의 구조체
    gameinfo1.friendGame = &gameinfo2; // friendGame 구조체는 포인터이다. 따라서 gameinfo2의 주소값을 할당한다.
    printf("\n\n--연관업체의 게임 출시 정보--\n");
    printf("게임     :  %s\n", gameinfo1.friendGame->name);
    printf("년도     :  %d\n", gameinfo1.friendGame->year); //friendGame이 가리키는 주소 즉 gameinfo2의 year변수 값을 가져온다.
    printf("가격     :  %d\n", gameinfo1.friendGame->price);
    printf("제작사   :  %s\n", gameinfo1.friendGame->company);

    // typedef
    // 자료형에 별명을 지정한다.
    int i = 1;
    typedef int 정수;
    정수 정수변수 = 3; // int i = 3;

    typedef float 실수;
    실수 실수변수 = 4.32f; // float f = 4.32f;

    printf("\n\n----typedef----\n");
    printf("typedef 설정, 정수변수 : %d\n", 정수변수);
    printf("typedef 설정, 실수변수 : %.2f\n", 실수변수);
    printf("\n\n-------------------------------");

    //  구조체 사용 struct Gameinfo gameinfo1;
    typedef struct Gameinfo 게임정보;
    게임정보 game1;

    game1.name = "한글 게임"; // gameinfo1.name = "나도게임";
    game1.year = 2015;

    GAME_INFO game2; // struct Gameinformation의 별명 GAME_INFO 로 사용
    game2.name = "한글 게임2";
    game2.year = 2017;

    struct Gameinformation game3; // struct Gameinformation의 별명 GAME_INFO를 사용하지 않고 바로 사용
    game3.name = "한글 게임3";
    game3.year = 2018;

    GAME_INFO_2 game4; // 이 struct의 이름을 정의하지 않고 GAME_INFO_2 라 선언하였기에 GAME_INFO_2를 사용
    game4.name = "한글 게임4";

    return 0;
}