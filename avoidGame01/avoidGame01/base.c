#include<stdio.h>
#include<stdbool.h>
#include<Windows.h>
#include <time.h>
#include "Position.h"

//사용자 정의 세미콜론 없어야함
#define WIDTH 30
#define HEIGHT 20
#define TRUE 1
#define FALSE 0

//전역변수 선언
Snow snow[WIDTH];
Player one;
clock_t start;

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

    gotoxy((WIDTH / 2) - 7, HEIGHT + 2);
    printf("CPU AVOID GAME");

    int i;
    for (i = 0; i < WIDTH; i++)
    {
        if (snow[i].con)
        {
            //적 위치에 적군 출력
            gotoxy(snow[i].x, HEIGHT - snow[i].y);
            printf("|");
        }
    }
    //플레이어 출력
    gotoxy(one.x, HEIGHT);
    printf("8");

    //바닥 출력
    gotoxy(0, HEIGHT + 1);
    for (i = 0; i < WIDTH; i++)
        printf("▩");
}

//타이머 함수
//타이머 시작
void startTimer() {
    start = clock();
}
//타이머 끝
void endTimer() {
    system("cls");

    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC; //초단위 변환
    printf("\n경과시간 : %0.3lf초\n", time); //소수점 셋째 자리까지
}
//게임 끝났을때 메뉴
bool Outgame(void) {
    bool Bet;
    // while(1){
    //system("cls");
    printf("\n");
    printf("게임종료/다시하기");
    printf("\n");
    printf("continue......Y/N");
    while (1) {
        if (GetAsyncKeyState('Y') & 0x8000) {
            Bet = false;
            break;
        }
        if (GetAsyncKeyState('N') & 0x8000) {
            Bet = true;
            break;

        }
    }
    return Bet;
}

//사실 메인
bool ing() {
    init();
    startTimer();
    do {
        //매번 실행할 때마다 다른 값을 주기 위한 시드값 설정
        srand((int)malloc(NULL));

        CreateEnemy();
        FallEnemy();
        DelEnemy();

        MovePlayer();

        PrintGame();
        //게임의 속도 조절을 위해 Sleep 설정
        Sleep(50);
    } while (!(DamagedPlayer()));    //닿지 않으면 반복
    endTimer();
    return Outgame();
}
//// main 함수 ////
void main(void)
{
    bool t;

    do  {
        t = ing();
    } while (t);

    printf("\n\n-----종료되었습니다.----\n\n");
    
}

