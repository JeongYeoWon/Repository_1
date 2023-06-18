#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "screen.h"
#include "util.h"

int Initialize(); // ���� ���� �ʱ�ȭ
int Release(); // �������ֱ�
int DrawBuffer(int DeltaTime); // ȭ�� ���

//���ӽ�����Ʈ�� 0�϶� ������ ���� ����
int GameState;
int GameStartSnakeLength; // �� ���� ����
int ActiveSnakeNum; // Ȱ��ȭ�� �� ���� ����
int score;

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
	unsigned long time_end = GetTickCount(); // ���� �ý����� �ð� ����� ����
	unsigned long deltaTime = GetTickCount(); // ���� �ý����� �ð� ����� ����

	setCursorPos(0, 0); // ����� ��ǥ
	SetColor(0b1111, 0b0000); // ����
	printf("%s", ScreenBuffer);
	setCursorPos(30, 10);
	printf("������ Ű���\n\n			�����Ϸ��� 1���� �����ÿ�.\n	    	           1. ���� Ű�� �̵�\n		    2. ���� �Ӹ��� ���뿡 ���� �� ����");

	int startFlag = 0; // ���� �÷���
	while (startFlag != 1) // 1�� �Է��� ������ �ݺ�
	{
		if (_kbhit()) // Ű �Է� ���� Ȯ��
		{
			char key = _getch(); // Ű���� �Է� �ޱ�

			if (key == '1') // 1�� �Է��ϸ� ���� �÷��׸� 1�� �����ϰ� �ݺ��� ����
			{
				startFlag = 1;
				break;
			}
		}
	}

	while (GameState) // ��������Ǳ� ������
	{
		deltaTime = GetTickCount() - time_end;
		time_end = GetTickCount();

		DrawBuffer(deltaTime); // ����ϱ�

		if (deltaTime < 33)
			Sleep(33 - deltaTime); // ������ ����,,?

		for (int i = 1; i < GameStartSnakeLength; i++) {
			if (snakeSkin[0].posX == snakeSkin[i].posX && snakeSkin[0].posY == snakeSkin[i].posY) {
				setCursorPos(30, 6);
				SetColor(0b0000, 0b1111);
				printf("���� ����");
				/*Sleep(1000);*/
				setCursorPos(10, 23);
				GameState = 0;
			}
		}
	}

	CHECKERROR(Release()); // �������ֱ�

	exit(1);
	return 0;
}

void InitApple() // ���
{
	//apple �ʱ�ȭ
	srand(time(NULL));
	apple.posX = (rand() % 68) + 2; // ��ǥ ����
	apple.posY = (rand() % 18) + 2; // 22
	apple.isActive = 1; // Ȱ��ȭ��
}

int Initialize() // �ʱ�ȭ
{
	GameState = 1; // �� ����
	GameStartSnakeLength = 3; // ó�� ���� �� ���� ũ��
	ActiveSnakeNum = GameStartSnakeLength; // ���� ���̸� Ȱ��ȭ�ƴ��� �ʱ�ȭ
	setScreenSize(70, 20); // �� ������
	setCursorVisibility(0); // �ȱ����Ÿ�
	SetColor(0b1000, 0b1111); // ���� ��� ��
	ClearBuffer(); // ȭ�� �ʱ�ȭ

	//GameObject �ʱ�ȭ

	//��� �ʱ�ȭ
	InitApple();
	int i = 0;
	while (i < GameStartSnakeLength) // i�� ���� ���뺸�� ����������
	{
		if (snakeSkin[i].posX == apple.posX // ���� ������ x��ǥ�� ����� x��ǥ�� ���� ���� ���� y��ǥ�� ����� y��ǥ�� ���� ��
			&& snakeSkin[i].posY == apple.posY)
		{
			InitApple(); // ���
			i = 0; // i�� 0���� ����
		}
		else // �ƴ� ��� i + 1
		{
			i = i + 1;
		}
	}

	//�� ���׾Ƹ� �ʱ�ȭ
	i = 0;
	while (i < MAX_SNAKE_LENGTH) // i�� 1400���� ���� ������ �ݺ�
	{
		//snakeSkin[i].posX = 35; // ���Ǹ� x��ǥ�� 35;
		//snakeSkin[i].posY = 10; // ���Ǹ� y��ǥ�� 35;
		snakeSkin[i].isActive = 0; // Ȱ��ȭ ����
		i = i + 1;
	}

	i = 0;
	while (i < GameStartSnakeLength) // i�� �������̺��� ���� ������ �ݺ�
	{
		snakeSkin[i].posX = 35 - i; // ���Ǹ� x��ǥ�� 35-i;
		snakeSkin[i].posY = 10; // ���Ǹ� y��ǥ�� 10;
		snakeSkin[i].isActive = 1; // Ȱ��ȭ��
		i = i + 1;
	}

	return 0;
}

int Release()
{
	return 0;
}

int dir; // ���� ���� �̵� ������ �����ϴ� ����

void MoveSnake()
{
	//�����̵� �κ�
	int i = GameStartSnakeLength - 1; // ���뺸�� - 1
	while (i > 0) // i�� 0���� ���������� �ݺ�
	{
		snakeSkin[i].posX = snakeSkin[i - 1].posX; // ����[i - 1]�� x��ǥ�� ����[i]�� ����,, �׳� 1ĭ�� �̵���
		snakeSkin[i].posY = snakeSkin[i - 1].posY;
		i = i - 1;
	}

	switch (dir)
	{
	case 0: // ������
			snakeSkin[0].posX = snakeSkin[0].posX + 1;
			snakeSkin[0].posY = snakeSkin[0].posY;
		break;
	case 1: // ����
		snakeSkin[0].posX = snakeSkin[0].posX - 1;
		snakeSkin[0].posY = snakeSkin[0].posY;
		break;
	case 2: // ����
		snakeSkin[0].posX = snakeSkin[0].posX;
		snakeSkin[0].posY = snakeSkin[0].posY - 1;
		break;
	case 3: // �Ʒ���
		snakeSkin[0].posX = snakeSkin[0].posX;
		snakeSkin[0].posY = snakeSkin[0].posY + 1;
		break;
	default:
		break;
	}


	if (snakeSkin[0].posX < 0 || snakeSkin[0].posX >= 70 ||
		snakeSkin[0].posY < 0 || snakeSkin[0].posY >= 20)
	{
		// ���� �Ӹ� ��ġ�� ȭ���� �ݴ������� �̵���Ŵ
		if (snakeSkin[0].posX < 0)
			snakeSkin[0].posX = 70 - 1;
		else if (snakeSkin[0].posX >= 70)
			snakeSkin[0].posX = 0;
		else if (snakeSkin[0].posY < 0)
			snakeSkin[0].posY = 20 - 1;
		else if (snakeSkin[0].posY > 20)
			snakeSkin[0].posY = 0;
	}

	////�Ӹ� �̵��κ�
	//snakeSkin[0].posX = snakeSkin[0].posX + 1; // �Ӹ��� 1ĭ�� �̵�
	//snakeSkin[0].posY = snakeSkin[0].posY;
}

void ProcessInput()
{
	if (_kbhit()) // Ű �Է� ���� Ȯ��
	{
		char key = _getch(); // Ű���� �Է� �ޱ�

		switch (key)
		{
		case 72: // �������� �̵�
			dir = 2;
			break;
		case 80: // �Ʒ������� �̵�
			dir = 3;
			break;
		case 75: // �������� �̵�
			dir = 1;
			break;
		case 77: // ���������� �̵�
			dir = 0;
			break;
		default:
			break;
		}
	}

	if (snakeSkin[0].posX == apple.posX && snakeSkin[0].posY == apple.posY)
	{
		score++;
		// ����� �Ծ��� ��� ���� ���̸� ������Ŵ
		GameStartSnakeLength++;
		ActiveSnakeNum++;
		InitApple(); // ���ο� ��� ����
	}
}

int DeltaTimeSum = 0;


int DrawBuffer(int DeltaTime) // �����
{
	ProcessInput(); // ����Ű ����

	setCursorPos(0, 0); // ����� ��ǥ
	SetColor(0b1111, 0b0000); // ����
	printf("%s", ScreenBuffer);

	DeltaTimeSum = DeltaTimeSum + DeltaTime; // ���� ���� ������ ��� �ð�
	if (DeltaTimeSum >= 500) // �ð��� 500���� ũ�ų� ������,,??
	{
		MoveSnake(); // ���� �̵���Ŵ
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
	setCursorPos(10, 22);
	printf("���� : %d", score);
	return 0;
}