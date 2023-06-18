#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "screen.h"
#include "util.h"
#include "menu.h"

#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75

int Initialize(); // ���� ���� �ʱ�ȭ
int Release(); // �������ֱ�
int DrawBuffer(int DeltaTime); // ȭ�� ���

//���ӽ�����Ʈ�� 0�϶� ������ ���� ����
int GameState;
int GameStartSnakeLength; // �� ���� ����
int ActiveSnakeNum; // Ȱ��ȭ�� �� ���� ����

#define MAX_SNAKE_LENGTH 1400 // ���,, ¯���
struct GameObject // ���� ������Ʈ ��ǥ�� Ȱ��ȭ
{
	int posX;
	int posY;
	int isActive;
};

//0���� �Ӹ�
struct GameObject snakeSkin[MAX_SNAKE_LENGTH]; // �� ����
struct GameObject apple; // ���

int main()
{
	CHECKERROR(Initialize()); // ���� ������ �ʱ�ȭȭ�鼭 ���� �˻�..?�ϱ�

	introMenu(); // �޴��� ����ؿ�
	unsigned long time_end = GetTickCount(); // ���� �ý����� �ð� ����� ����
	unsigned long deltaTime = GetTickCount(); // ���� �ý����� �ð� ����� ����

	while (GameState) // ��������Ǳ� ������ �ݺ�
	{
		if (kbhit()) // Ű �Է¹��� ������ ��ٸ��� ���� ����
		{
			char ch = getch();

			switch (ch)
			{
			case '1':

				break;
			case '2': // ���� 2�� ��������
				ClearScreen();
				GameStory();
				
				break;
			case '3':

				break;
			case '4':
			case 27:
				GameState = 0;
				break;
			default:
				// �߸��� �Է� ó��
				break;
			}
		}

		deltaTime = GetTickCount() - time_end;
		time_end = GetTickCount();

		DrawBuffer(deltaTime); // ����ϱ�

		if (deltaTime < 33)
			Sleep(33 - deltaTime); // ������ ����,,?
	}

	CHECKERROR(Release()); // �������ֱ�

	exit(1);
	return 0;
}

int Initialize() {
	GameState = 1;
	setScreenSize(70, 20);
	setCursorVisibility(0); // �ȱ����Ÿ�
	ClearBuffer();

	return 0;
}

int Release()
{
	return 0;
}

void ClearScreen() {
	setCursorPos(0, 0);
	SetColor(0b1000, 0b1000);
	setScreenSize(70, 20); // ȭ���� �ʱ�ȭ
	ClearBuffer();
}

void MoveSnake(int dir)
{
	//�����̵� �κ�
	int i = GameStartSnakeLength - 1; // ���뺸�� - 1
	while (i > 0) // i�� 0���� ���������� �ݺ�
	{
		snakeSkin[i].posX = snakeSkin[i - 1].posX; // ����[i - 1]�� x��ǥ�� ����[i]�� ����,, �׳� 1ĭ�� �̵���
		snakeSkin[i].posY = snakeSkin[i - 1].posY;
		i = i - 1;
	}
	//�Ӹ� �̵��κ�
	snakeSkin[0].posX = snakeSkin[0].posX + 1; // �Ӹ��� 1ĭ�� �̵�
	snakeSkin[0].posY = snakeSkin[0].posY;
}

int DeltaTimeSum = 0;

int DrawBuffer(int DeltaTime) // �����
{
	setCursorPos(0, 0); // ����� ��ǥ
	SetColor(0b1111, 0b0000); // ����
	printf("%s", ScreenBuffer);
	
	DeltaTimeSum = DeltaTimeSum + DeltaTime; // ���� ���� ������ ��� �ð�
	if (DeltaTimeSum >= 500) // �ð��� 500���� ũ�ų� ������,,??
	{
		MoveSnake(0); // ���� �̵���Ŵ
		DeltaTimeSum = 0; // 0���� �ʱ�ȭ
	}


	//apple
	setCursorPos(apple.posX, apple.posY); // ��� ��ġ
	SetColor(0b1111, 0b0100); // ����
	printf("*"); // ���

	//snake
	int i = 0;
	while (i < GameStartSnakeLength) // i�� �� ���̺��� ���������� �ݺ�
	{
		setCursorPos(snakeSkin[i].posX, snakeSkin[i].posY); // ��ǥ
		SetColor(0b1111, 0b0010); // ����
		printf("O"); // ����
		i = i + 1; // �߰�
	} 

	SetColor(0b0000, 0b1111);
	setCursorPos(0, 22); // �ð� ����� ��ġ
	if (DeltaTime != 0) // 0�� �ƴҶ� ���
		printf("time : %d                 \nfps :%d                  \n", DeltaTime, 1000 / DeltaTime);

	return 0;
}