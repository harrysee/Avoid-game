#include <stdio.h>
#include <windows.h>

//��(���� ��)
typedef struct
{
    int x;
    int y;
    //���� ���� (TRUE, FALSE)�� ��Ʈ���� ��
    int con;
}Snow;
//�÷��̾�
typedef struct
{
    int x;
}Player;



////������ ��ġ�� Ŀ���� �̵���Ű�� �Լ�////
void gotoxy(int x, int y)
{
    //COORD : window.h�� �ִ� ����ü, {SHORT x, SHORT y} �� �����Ǿ� �ִ�.
    COORD pos = { x * 2, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


