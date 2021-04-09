#include <stdio.h>
#include <windows.h>

//적(피할 것)
typedef struct
{
    int x;
    int y;
    //적의 상태 (TRUE, FALSE)로 컨트롤할 것
    int con;
}Snow;
//플레이어
typedef struct
{
    int x;
}Player;



////지정된 위치로 커서를 이동시키는 함수////
void gotoxy(int x, int y)
{
    //COORD : window.h에 있는 구조체, {SHORT x, SHORT y} 로 구성되어 있다.
    COORD pos = { x * 2, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


