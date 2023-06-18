#include <Windows.h>
#include "object.h"

void InitApple() // ���
{
	//apple �ʱ�ȭ
	srand(time(NULL));
	apple.posX = (rand() % 68) + 2; // ��ǥ ����
	apple.posY = (rand() % 18) + 2; // 22
	apple.isActive = 1; // Ȱ��ȭ��
}

int objectInitialize() {
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


	if (snakeSkin[0].posX < 1 || snakeSkin[0].posX >= 70 ||
		snakeSkin[0].posY < 1 || snakeSkin[0].posY >= 20)
	{
		// ���� �Ӹ� ��ġ�� ȭ���� �ݴ������� �̵���Ŵ
		if (snakeSkin[0].posX < 1)
			snakeSkin[0].posX = 70 - 1;
		else if (snakeSkin[0].posX >= 70)
			snakeSkin[0].posX = 1;
		else if (snakeSkin[0].posY < 1)
			snakeSkin[0].posY = 20 - 1;
		else if (snakeSkin[0].posY > 20)
			snakeSkin[0].posY = 1;
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

