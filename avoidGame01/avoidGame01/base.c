#include<stdio.h>
#include<stdbool.h>
#include<Windows.h>
#include <time.h>
#include "Position.h"

//����� ���� �����ݷ� �������
#define CT 13
#define WIDTH 34
#define HEIGHT 15
#define TRUE 1
#define FALSE 0
#define LV1 100
#define LV2 40
#define LV3 17
#define LV4 0


//�������� ����
Snow snow[WIDTH];
Player one;
clock_t start, c;
double time1;
double max_time = 0, cn;
int revelnum;
int nowrevel;
int speed;

//// �ʱⰪ ////
void init()
{
    int i;
    for (i = CT; i < WIDTH; i++)
        snow[i].con = FALSE;
    //�÷��̾� ��ġ�� �߾�
    one.x = (WIDTH+ CT) / 2;
}

//// ���� ���� ó�� ////
/* �� ���� */
void CreateEnemy()
{
    int i;

    for (i = CT; i < WIDTH; i++)
    {
        //�ش� �ε���[i]�� ���� ������ (FALSE �̸� ����)
        if (!snow[i].con)
        {
            //���� (x��) �������� �� ����, ����(y��)�� ���� ��ġ �׻� ��ġ
            snow[i].x = (rand() % (WIDTH-CT))+CT;
            snow[i].y = HEIGHT - 2;
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
    for (i = CT; i < WIDTH; i++)
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
    for (i = CT; i < WIDTH; i++)
    {
        if (snow[i].con && snow[i].y < 0)
            snow[i].con = FALSE;
    }
}
/* �÷��̾ ������ ���� ��� (�й�) */
int DamagedPlayer()
{
    int i;
    for (i = CT; i < WIDTH; i++)
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
    if (one.x < CT)
        one.x = CT;
    if (one.x > WIDTH - 1)
        one.x = WIDTH - 1;
}

//// ���� ȭ�� ��� ////
void PrintGame()
{
    //��� ȭ�� clear
    system("cls");

    //gotoxy(0, HEIGHT + 2); // (WIDTH /2) - 7
    //���� ���
    //printf("\n");
    gotoxy(CT, 1);
    switch (nowrevel) {
    case 1: {printf("��  Lv.1 ��");  break; }
    case 2: {printf("��  Lv.2 ��");  break; }
    case 3: {printf("��  Lv.3 ��");  break; }
    default: {printf("��   Lv.4 ��"); break; }
    }
    printf("  CPU ���ϱ� ����  "); //�߰� title
    //����ð� ���
    printf("��   %.1f��   ��\n", cn);
    gotoxy(CT, 2);
    int i;
    for (i = CT; i < WIDTH; i++)
        printf("����");//��

    for (i = CT; i < WIDTH; i++)
    {
        if (snow[i].con)
        {
            //�� ��ġ�� ���� ���
            gotoxy(snow[i].x, HEIGHT - snow[i].y);
            printf("o");
        }
    }
    //�÷��̾� ���
    gotoxy(one.x, HEIGHT);
    printf("��");

    //�ٴ� ���
    gotoxy(CT, HEIGHT + 1);
    for (i = CT; i < WIDTH; i++)
        printf("��");//��
    printf("\n");

}

//Ÿ�̸� �Լ� : clock();
//Ÿ�̸� ����
void startTimer() {
    start = clock();
}
//Ÿ�̸� ��
void endTimer() {
    system("cls");

    clock_t end = clock();
    time1 = (double)(end - start) / CLOCKS_PER_SEC; //�ʴ��� ��ȯ

}

//���� �������� �޴�
bool Outgame(void) {
    bool Bet;
    int wt = 17;    //���߾� ������
    //����ð� ���
    gotoxy(wt, 5); 
    printf("��������������������������������������������������\n"); 
    gotoxy(wt, 6);
    printf("��                       ��\n");
    gotoxy(wt, 7);
    if (time1 < 10.0)  printf("��  ����ð� :  %0.1lf��    ��\n", time1); //10�̸��̸� �տ� 0���̱�
    else  printf("��  ����ð� : %0.1lf��                ��\n", time1); //���� ���ڸ��� �״��
    gotoxy(wt, 8);
    printf("��                       ��\n");
    gotoxy(wt, 9);
    printf("�� �����������릢\n");

    //�ְ��� ���ϱ�
    if (time1 > max_time) { max_time = time1; }

    //�ְ��� ���
    gotoxy(wt, 10);
    printf("��                       ��\n");
    gotoxy(wt, 11);
    if (max_time < 10.0) printf("��  �ְ��� : %0.1lf��     ��\n", max_time); //10�̸��̸� �տ� 0���̱�
    else printf("�� �ְ��� : %0.1lf��      ��\n", max_time); //���� ���ڸ��� �״��
    gotoxy(wt, 12);
    printf("��                       ��\n");
    gotoxy(wt, 13);
    printf("�� �����������릢\n");
    gotoxy(wt, 14);
    printf("��                       ��\n");
    gotoxy(wt, 15);
    printf("��  �׸��ϱ�   �ٽ��ϱ�  ��\n");
    gotoxy(wt, 16);
    printf("��                       ��\n");
    gotoxy(wt, 17);
    printf("��     Y     :    N      ��");
    gotoxy(wt, 18);
    printf("��������������������������������������������������\n");

    //Y/N �߿� �ϳ��� ���������� �ݺ�
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
//���� ���� �ȳ���
void startMenu(void) {
    int ws = 13;
    while (1) {
        /*gotoxy(ws, 3); Ÿ��Ʋ �����κ� �׵θ�
        for (int i = 0; i < 45; i++)
            printf(".");  */ 
        
        //���� ��� �׵θ�
        for (int i = 4; i < 14; i++) {
            gotoxy(ws, i);
            printf(".");
        }
        //�ʹ� �����
        gotoxy(ws, 4);
        printf("................���� ���ϱ⡹................");
        gotoxy(ws + 1, 6);
        printf("�ܶ������� �����̸� ���� ��Ƴ�������!��");
        gotoxy(ws + 9, 7);
        printf("�� �� ��");
        gotoxy(ws + 3, 8);
        printf("�������Ϸ��� �ƹ�Ű�� �������䡷");

        //�ؿ��κ� �׵θ�
        gotoxy(ws, 14); 
        for (int i = 0; i < 45; i++)
            printf(".");
        //������ ��� �׵θ�
        for (int i = 4; i < 14; i++) {
            gotoxy(ws + 22, i);
            printf(".");
        }
        Sleep(200);
        if (_kbhit()) break;
    }
}
//������ �� �޴�
int revel() {
    system("cls");
    startMenu(); //�ȳ��� ȣ��
    //���� ���� ���� ���
    int ws = 18;
    gotoxy(ws+1, 10);
    printf("��  * �������� * \t��");
    // gotoxy(ws, 11);
     //printf("------------------------\n");
    gotoxy(ws, 12);
    printf("   ��    ��    ��   �� ");
    //gotoxy(ws, 13);
    //printf("------------------------");



    /*0�̳� (0x0000) : ������ ���� ���� ���� ȣ�� �������� �ȴ��� ����
    0x8000 : ������ ���� ���� ���� ȣ�� �������� ���� ����
    0x8001 : ������ ���� ���� �ְ� ȣ�� �������� ���� ����
    1�̳� (0x0001) :������ ���� ���� �ְ� ȣ�� �������� �ȴ��� ����*/

    while (1) {
        //���� ���ڸ� �����ų� ����Ű�е��� ���ڸ� �������� ����
        if (GetAsyncKeyState('1') & 0x8000 || GetAsyncKeyState(VK_NUMPAD1) & 0x8000) {
            revelnum = LV1; //1�ܰ�
            nowrevel = 1;
            break;
        }
        else if (GetAsyncKeyState('2') & 0x8000 || GetAsyncKeyState(VK_NUMPAD2) & 0x8000) {
            revelnum = LV2;  //2�ܰ�
            nowrevel = 2;
            break;
        }
        else if (GetAsyncKeyState('3') & 0x8000 || GetAsyncKeyState(VK_NUMPAD3) & 0x8000) {
            revelnum = LV3;  //3�ܰ�
            nowrevel = 3;
            break;
        }
        else if (GetAsyncKeyState('4') & 0x8000 || GetAsyncKeyState(VK_NUMPAD4) & 0x8000) {
            revelnum = LV4;   //4�ܰ�
            nowrevel = 4;
            break;
        }
    }
    return revelnum;
}

//��� ����
bool ing() {
    init();
    //system("color f0");
    //���� �����ϱ�
    int speed = revel();
    startTimer(); //Ÿ�̸� ����

    do {
        //�Ź� ������ ������ �ٸ� ���� �ֱ� ���� �õ尪 ����
        srand((int)malloc(NULL));

        CreateEnemy();  //������
        FallEnemy();    //�� �����̱�
        DelEnemy();     //������ �� ���ֱ�

        MovePlayer();   //����� ������

        PrintGame();    //ȭ�� �����

        //����ð� ���ϱ�
        c = clock();
        cn = (double)(c - start) / CLOCKS_PER_SEC;

        //������ �ӵ� ������ ���� Sleep ����
        Sleep(speed);

    } while (!(DamagedPlayer()));    //���� ������ �ݺ�
    endTimer(); //Ÿ�̸� ����
    return Outgame(); // �ٽ��ϱ� �޴� ȣ��
}
//// main �Լ� ////
void main(void)
{
    bool t;

    //���� ���๮ ȣ��- �׸��ϱ� ������ ������ �ݺ�
    do {
        t = ing();
    } while (t);

    system("cls");
    gotoxy(18, 3);
    printf("-----����Ǿ����ϴ�.----\n\n");
}