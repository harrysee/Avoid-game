#include<stdio.h>
#include<stdbool.h>
#include<Windows.h>
#include <time.h>
#include "Position.h"

//사용자 정의 세미콜론 없어야함
#define WIDTH 22
#define HEIGHT 17
#define TRUE 1
#define FALSE 0
#define LV1 100
#define LV2 40
#define LV3 17
#define LV4 0


//전역변수 선언
Snow snow[WIDTH];
Player one;
clock_t start, c;
double time1;
double max_time = 0, cn;
int revelnum;
int nowrevel;
int speed;

//// 초기값 ////
void init()
{
    int i;
    for (i = 0; i < WIDTH; i++)
        snow[i].con = FALSE;
    //플레이어 위치는 중앙
    one.x = WIDTH / 2;
}

//// 피할 적들 처리 ////
/* 적 생성 */
void CreateEnemy()
{
    int i;

    for (i = 0; i < WIDTH; i++)
    {
        //해당 인덱스[i]에 적이 없으면 (FALSE 이면 실행)
        if (!snow[i].con)
        {
            //가로 (x축) 무작위로 적 출현, 세로(y축)은 출현 위치 항상 일치
            snow[i].x = rand() % WIDTH;
            snow[i].y = HEIGHT - 1;
            //적이 출현한 인덱스 [i]의 상태 = TRUE로 변경
            snow[i].con = TRUE;
            return;
        }
    }
}
/* 적의 움직임 */
void FallEnemy()
{
    int i;
    for (i = 0; i < WIDTH; i++)
    {
        //해당 인덱스 [i]에 적이 있으면 (TRUE라면) 움직임 실행
        if (snow[i].con)
        {
            snow[i].y--;
        }
    }
}
/* 피하기 성공한 적(바닥에 떨어진 적) 삭제 */
void DelEnemy()
{
    int i;
    for (i = 0; i < WIDTH; i++)
    {
        if (snow[i].con && snow[i].y < 0)
            snow[i].con = FALSE;
    }
}
/* 플레이어가 적에게 닿을 경우 (패배) */
int DamagedPlayer()
{
    int i;
    for (i = 0; i < WIDTH; i++)
    {
        //적의 상태가 TRUE && 적의 위치가 y=0 즉 바닥 && 적의 x축 위치 = 플레이어의 x축 위치
        if ((snow[i].con && snow[i].y == 0) && (snow[i].x == one.x))
            return TRUE;
    }
    //닿지 않았으면 FALSE 반환
    return FALSE;
}

//// 플레이어 처리 ////
/* 키 다운 처리 */
int isKeyDown(int key)
{
    //***GetAsyncKey는 키가 눌렸다면 최상위 비트를 1로 설정, 이전에 키가 눌렸다면 최하위 비트를 1로 설정
    //0x8000은 최상위 비트 -> 16진수는 2비트가 4개 모인 비트 -> 0x8000 = 1000 0000 0000 0000를 의미
    // 즉 최하위 비트는 0x0001 -> 0000 0000 0000 0001
    // 따라서 (GetAsyncKeyState(key) & 0x8000) != 0 은 현재 키가 눌려있다면 참(TRUE)
    return ((GetAsyncKeyState(key) & 0x8000) != 0);
}

/* 플레이어 이동 (좌/우) */
void MovePlayer()
{
    //왼쪽 방향키 입력 시
    if (isKeyDown(VK_LEFT))
        one.x--;
    if (isKeyDown(VK_RIGHT))
        one.x++;
    //위치 범위 제한
    if (one.x < 0)
        one.x = 0;
    if (one.x > WIDTH - 1)
        one.x = WIDTH - 1;
}

//// 게임 화면 출력 ////
void PrintGame()
{
    //모든 화면 clear
    system("cls");

    //gotoxy(0, HEIGHT + 2); // (WIDTH /2) - 7
    //레벨 출력
    printf("\n");
    switch (nowrevel) {
    case 1: {printf("【   Lv.1  │");  break; }
    case 2: {printf("【   Lv.2  │");  break; }
    case 3: {printf("【   Lv.3  │");  break; }
    default: {printf("【    Lv.4  │"); break; }
    } 
    printf("  CPU 피하기 게임  "); //중간 title
    //현재시간 출력
    printf("│   %.1f초   】\n", cn);
    int i;
    for (i = 0; i < WIDTH; i++)
        printf("──");//▩

    for (i = 0; i < WIDTH; i++)
    {
        if (snow[i].con)
        {
            //적 위치에 적군 출력
            gotoxy(snow[i].x, HEIGHT - snow[i].y);
            printf("o");
        }
    }
    //플레이어 출력
    gotoxy(one.x, HEIGHT);
    printf("♀");

    //바닥 출력
    gotoxy(0, HEIGHT + 1);
    for (i = 0; i < WIDTH; i++)
        printf("▲");//▩
    printf("\n");

}

//타이머 함수 : clock();
//타이머 시작
void startTimer() {
    start = clock();
}
//타이머 끝
void endTimer() {
    system("cls");

    clock_t end = clock();
    time1 = (double)(end - start) / CLOCKS_PER_SEC; //초단위 변환

}

//게임 끝났을때 메뉴
bool Outgame(void) {
    bool Bet;

    //경과시간 출력
    gotoxy(0, 5);
    printf("\t\t┌───────────────────────┐\n\t\t│                       │\n");
    if (time1 < 10.0)  printf("\t\t│  경과시간 :  %0.1lf초    │\n", time1); //10미만이면 앞에 0붙이기
    else  printf("\t\t│  경과시간 : %0.1lf초                │\n", time1); //앞이 두자리면 그대로
    printf("\t\t│                       │\n");
    printf("\t\t│ 〓〓〓〓〓〓〓〓〓〓〓│\n");

    //최고기록 구하기
    if (time1 > max_time) { max_time = time1; }

    //최고기록 출력
    printf("\t\t│                       │\n");
    if (max_time < 10.0) printf("\t\t│  최고기록 : %0.1lf초     │\n", max_time); //10미만이면 앞에 0붙이기
    else printf("\t\t│ 최고기록 : %0.1lf초      │\n", max_time); //앞이 두자리면 그대로
    printf("\t\t│                       │\n");

    printf("\t\t│ 〓〓〓〓〓〓〓〓〓〓〓│\n");
    printf("\t\t│                       │\n");
    // while(1){
    //system("cls");
    printf("\t\t│  그만하기   다시하기  │");
    printf("\n\t\t│                       │\n");
    printf("\t\t│     Y     :    N      │");
    printf("\n\t\t└───────────────────────┘\n");

    //Y/N 중에 하나를 누를때까지 반복
    while (1) {
        if (GetAsyncKeyState('Y') & 0x8000) {
            Bet = false;
            break;
        }
        if (GetAsyncKeyState('N') & 0x8000) {
            Bet = true;
            nowrevel++;
            break;

        }
    }
    return Bet;
}

//게임 시작 안내판
void startMenu(void) {
    int ws = 13;
    while (1) {
        //테두리
        gotoxy(ws, 3);
        for (int i=0;  i < 45; i++)
            printf(".");

        for (int i = 4; i < 14; i++) {
            gotoxy(ws, i);
            printf(".");
        }
        //초반 설명글
        gotoxy(ws+7, 4);
        printf(" 「눈 피하기」");
        gotoxy(ws+1, 6);
        printf("●떨어지는 눈덩이를 피해 살아남으세요!●");
        gotoxy(ws+11, 7);
        printf("▷");
        gotoxy(ws+3, 8);
        printf("《시작하려면 아무키를 누르세요》");
        
        //테두리
        gotoxy(ws, 14);
        for (int i = 0; i < 45; i++)
            printf(".");
        for (int i = 4; i < 14; i++) {
            gotoxy(ws+22, i);
            printf(".");
        }
        Sleep(300);
        if (_kbhit()) break;
    }
}
//시작할 때 메뉴
int revel() {
    int ws = 18;
    system("cls");
    startMenu(); //안내말 호출
    //레벨 선택 글자 출력
    gotoxy(ws, 10);
    printf("│\t * 레벨선택 *\t│\n");
   // gotoxy(ws, 11);
    //printf("------------------------\n");
    gotoxy(ws, 12);
    printf("  ¹    ²    ³    ⁴ \n");
    //gotoxy(ws, 13);
    //printf("------------------------");

    /*0이나 (0x0000) : 이전에 누른 적이 없고 호출 시점에서 안눌린 상태
    0x8000 : 이전에 누른 적이 없고 호출 시점에서 눌린 상태
    0x8001 : 이전에 누른 적이 있고 호출 시점에서 눌린 상태
    1이나 (0x0001) :이전에 누른 적이 있고 호출 시점에서 안눌린 상태*/

    while (1) {
        //위에 숫자를 누르거나 숫자키패드의 숫자를 눌렀을때 조건
        if (GetAsyncKeyState('1') & 0x8000 || GetAsyncKeyState(VK_NUMPAD1) & 0x8000) {
            revelnum = LV1; //1단계
            nowrevel = 1;
            break;
        }
        else if (GetAsyncKeyState('2') & 0x8000 || GetAsyncKeyState(VK_NUMPAD2) & 0x8000) {
            revelnum = LV2;  //2단계
            nowrevel = 2;
            break;
        }
        else if (GetAsyncKeyState('3') & 0x8000 || GetAsyncKeyState(VK_NUMPAD3) & 0x8000) {
            revelnum = LV3;  //3단계
            nowrevel = 3;
            break;
        }
        else if (GetAsyncKeyState('4') & 0x8000 || GetAsyncKeyState(VK_NUMPAD4) & 0x8000) {
            revelnum = LV4;   //4단계
            nowrevel = 4;
            break;
        }
    }
    return revelnum;
}

//사실 메인
bool ing() {
    init();
    //system("color f0");
    //레벨 선택하기
    int speed = revel();
    startTimer(); //타이머 시작

    do {
        //매번 실행할 때마다 다른 값을 주기 위한 시드값 설정
        srand((int)malloc(NULL));

        CreateEnemy();  //적생성
        FallEnemy();    //적 움직이기
        DelEnemy();     //떨어진 적 없애기

        MovePlayer();   //사용자 움직임

        PrintGame();    //화면 만들기

        //현재시간 구하기
        c = clock();
        cn = (double)(c - start) / CLOCKS_PER_SEC;

        //게임의 속도 조절을 위해 Sleep 설정
        Sleep(speed);

    } while (!(DamagedPlayer()));    //닿지 않으면 반복
    endTimer(); //타이머 종료
    return Outgame(); // 다시하기 메뉴 호출
}
//// main 함수 ////
void main(void)
{
    bool t;

    //게임 실행문 호출- 그만하기 누르기 전까지 반복
    do {
        t = ing();
    } while (t);

    system("cls");
    printf("\n\n-----종료되었습니다.----\n\n");
}

