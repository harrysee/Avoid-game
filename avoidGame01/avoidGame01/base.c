#include<stdio.h>
#include<stdbool.h>
#include<Windows.h>
#include <time.h>
#include "Position.h"

//����� ���� �����ݷ� �������
#define WIDTH 30
#define HEIGHT 20
#define TRUE 1
#define FALSE 0

//�������� ����
Snow snow[WIDTH];
Player one;
clock_t start;

//// �ʱⰪ ////
void init()
{
    int i;
    for (i = 0; i < WIDTH; i++)
        snow[i].con = FALSE;
    //�÷��̾� ��ġ�� �߾�
    one.x = WIDTH / 2;
}

//// ���� ���� ó�� ////
/* �� ���� */
void CreateEnemy()
{
    int i;

    for (i = 0; i < WIDTH; i++)
    {
        //�ش� �ε���[i]�� ���� ������ (FALSE �̸� ����)
        if (!snow[i].con)
        {
            //���� (x��) �������� �� ����, ����(y��)�� ���� ��ġ �׻� ��ġ
            snow[i].x = rand() % WIDTH;
            snow[i].y = HEIGHT - 1;
            //���� ������ �ε��� [i]�� ���� = TRUE�� ����
            snow[i].con = TRUE;
            return;
        }
    }
}
/* ���� ������ */
void FallEnemy()
{
    int i;
    for (i = 0; i < WIDTH; i++)
    {
        //�ش� �ε��� [i]�� ���� ������ (TRUE���) ������ ����
        if (snow[i].con)
        {
            snow[i].y--;
        }
    }
}
/* ���ϱ� ������ ��(�ٴڿ� ������ ��) ���� */
void DelEnemy()
{
    int i;
    for (i = 0; i < WIDTH; i++)
    {
        if (snow[i].con && snow[i].y < 0)
            snow[i].con = FALSE;
    }
}
/* �÷��̾ ������ ���� ��� (�й�) */
int DamagedPlayer()
{
    int i;
    for (i = 0; i < WIDTH; i++)
    {
        //���� ���°� TRUE && ���� ��ġ�� y=0 �� �ٴ� && ���� x�� ��ġ = �÷��̾��� x�� ��ġ
        if ((snow[i].con && snow[i].y == 0) && (snow[i].x == one.x))
            return TRUE;
    }
    //���� �ʾ����� FALSE ��ȯ
    return FALSE;
}

//// �÷��̾� ó�� ////
/* Ű �ٿ� ó�� */
int isKeyDown(int key)
{
    //***GetAsyncKey�� Ű�� ���ȴٸ� �ֻ��� ��Ʈ�� 1�� ����, ������ Ű�� ���ȴٸ� ������ ��Ʈ�� 1�� ����
    //0x8000�� �ֻ��� ��Ʈ -> 16������ 2��Ʈ�� 4�� ���� ��Ʈ -> 0x8000 = 1000 0000 0000 0000�� �ǹ�
    // �� ������ ��Ʈ�� 0x0001 -> 0000 0000 0000 0001
    // ���� (GetAsyncKeyState(key) & 0x8000) != 0 �� ���� Ű�� �����ִٸ� ��(TRUE)
    return ((GetAsyncKeyState(key) & 0x8000) != 0);
}

/* �÷��̾� �̵� (��/��) */
void MovePlayer()
{
    //���� ����Ű �Է� ��
    if (isKeyDown(VK_LEFT))
        one.x--;
    if (isKeyDown(VK_RIGHT))
        one.x++;
    //��ġ ���� ����
    if (one.x < 0)
        one.x = 0;
    if (one.x > WIDTH - 1)
        one.x = WIDTH - 1;
}

//// ���� ȭ�� ��� ////
void PrintGame()
{
    //��� ȭ�� clear
    system("cls");

    gotoxy((WIDTH / 2) - 7, HEIGHT + 2);
    printf("CPU AVOID GAME");

    int i;
    for (i = 0; i < WIDTH; i++)
    {
        if (snow[i].con)
        {
            //�� ��ġ�� ���� ���
            gotoxy(snow[i].x, HEIGHT - snow[i].y);
            printf("|");
        }
    }
    //�÷��̾� ���
    gotoxy(one.x, HEIGHT);
    printf("8");

    //�ٴ� ���
    gotoxy(0, HEIGHT + 1);
    for (i = 0; i < WIDTH; i++)
        printf("��");
}

//Ÿ�̸� �Լ�
//Ÿ�̸� ����
void startTimer() {
    start = clock();
}
//Ÿ�̸� ��
void endTimer() {
    system("cls");

    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC; //�ʴ��� ��ȯ
    printf("\n����ð� : %0.3lf��\n", time); //�Ҽ��� ��° �ڸ�����
}
//���� �������� �޴�
bool Outgame(void) {
    bool Bet;
    // while(1){
    //system("cls");
    printf("\n");
    printf("��������/�ٽ��ϱ�");
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

//��� ����
bool ing() {
    init();
    startTimer();
    do {
        //�Ź� ������ ������ �ٸ� ���� �ֱ� ���� �õ尪 ����
        srand((int)malloc(NULL));

        CreateEnemy();
        FallEnemy();
        DelEnemy();

        MovePlayer();

        PrintGame();
        //������ �ӵ� ������ ���� Sleep ����
        Sleep(50);
    } while (!(DamagedPlayer()));    //���� ������ �ݺ�
    endTimer();
    return Outgame();
}
//// main �Լ� ////
void main(void)
{
    bool t;

    do  {
        t = ing();
    } while (t);

    printf("\n\n-----����Ǿ����ϴ�.----\n\n");
    
}

