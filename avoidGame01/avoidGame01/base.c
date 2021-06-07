#include<stdio.h>
#include<stdbool.h>
#include<Windows.h>
#include <time.h>
#include "Position.h"

//����� ���� �����ݷ� �������
#define WIDTH 22
#define HEIGHT 17
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

    //gotoxy(0, HEIGHT + 2); // (WIDTH /2) - 7
    //���� ���
    printf("\n");
    switch (nowrevel) {
    case 1: {printf("��   Lv.1  ��");  break; }
    case 2: {printf("��   Lv.2  ��");  break; }
    case 3: {printf("��   Lv.3  ��");  break; }
    default: {printf("��    Lv.4  ��"); break; }
    } 
    printf("  CPU ���ϱ� ����  "); //�߰� title
    //����ð� ���
    printf("��   %.1f��   ��\n", cn);
    int i;
    for (i = 0; i < WIDTH; i++)
        printf("����");//��

    for (i = 0; i < WIDTH; i++)
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
    gotoxy(0, HEIGHT + 1);
    for (i = 0; i < WIDTH; i++)
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

    //����ð� ���
    gotoxy(0, 5);
    printf("\t\t��������������������������������������������������\n\t\t��                       ��\n");
    if (time1 < 10.0)  printf("\t\t��  ����ð� :  %0.1lf��    ��\n", time1); //10�̸��̸� �տ� 0���̱�
    else  printf("\t\t��  ����ð� : %0.1lf��                ��\n", time1); //���� ���ڸ��� �״��
    printf("\t\t��                       ��\n");
    printf("\t\t�� �����������릢\n");

    //�ְ��� ���ϱ�
    if (time1 > max_time) { max_time = time1; }

    //�ְ��� ���
    printf("\t\t��                       ��\n");
    if (max_time < 10.0) printf("\t\t��  �ְ��� : %0.1lf��     ��\n", max_time); //10�̸��̸� �տ� 0���̱�
    else printf("\t\t�� �ְ��� : %0.1lf��      ��\n", max_time); //���� ���ڸ��� �״��
    printf("\t\t��                       ��\n");

    printf("\t\t�� �����������릢\n");
    printf("\t\t��                       ��\n");
    // while(1){
    //system("cls");
    printf("\t\t��  �׸��ϱ�   �ٽ��ϱ�  ��");
    printf("\n\t\t��                       ��\n");
    printf("\t\t��     Y     :    N      ��");
    printf("\n\t\t��������������������������������������������������\n");

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
        //�׵θ�
        gotoxy(ws, 3);
        for (int i=0;  i < 45; i++)
            printf(".");

        for (int i = 4; i < 14; i++) {
            gotoxy(ws, i);
            printf(".");
        }
        //�ʹ� �����
        gotoxy(ws+7, 4);
        printf(" ���� ���ϱ⡹");
        gotoxy(ws+1, 6);
        printf("�ܶ������� �����̸� ���� ��Ƴ�������!��");
        gotoxy(ws+11, 7);
        printf("��");
        gotoxy(ws+3, 8);
        printf("�������Ϸ��� �ƹ�Ű�� �������䡷");
        
        //�׵θ�
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
//������ �� �޴�
int revel() {
    int ws = 18;
    system("cls");
    startMenu(); //�ȳ��� ȣ��
    //���� ���� ���� ���
    gotoxy(ws, 10);
    printf("��\t * �������� *\t��\n");
   // gotoxy(ws, 11);
    //printf("------------------------\n");
    gotoxy(ws, 12);
    printf("  ��    ��    ��    �� \n");
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
    printf("\n\n-----����Ǿ����ϴ�.----\n\n");
}

