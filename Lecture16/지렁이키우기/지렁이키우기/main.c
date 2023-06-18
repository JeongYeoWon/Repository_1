#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "screen.h"
#include "util.h"
#include "menu.h"
#include "object.h"

int Initialize(); // �ʱ�ȭ
int Release(); // ����
int DrawBuffer(int DeltaTime); // ȭ�� ���
int objectDraw(int DeltaTime);

int GameState; // ���� Ȱ��ȭ ����

int main() {

	CHECKERROR(Initialize());

	introMenu();
	printf("%s", ScreenBuffer);
	setCursorPos(30, 22);

	unsigned long time_end = GetTickCount(); // ���� �ý����� �ð��� ��?�� ����� ����
	unsigned long deltaTime = GetTickCount(); // ���� �ý����� �ð��� ����� ����
	
	char ch;
	int menuSelected = 0; // ���õ� �޴�

	while (1) {
		if (_kbhit()) {
			ch = getch();
			switch (ch) {
			case '1':
				menuSelected = 1; // 1�� �޴� ����
				break;
			case '2':
				menuSelected = 2; // 2�� �޴� ����
				break;
			case '3':
			case 27:
				exit(0);
				break;
			default:

				break;
			}

			if (menuSelected != 0) {
				break; // �޴� ������ �Ǿ����� �ݺ��� ����
			}
		}
	}

	while (menuSelected != 4) { // �޴��� 4�� �ƴҶ�����
		if (menuSelected == 1) { // 1�� ���
			setCursorPos(0, 0);
			Initialize();
			objectInitialize();
			while (GameState) {
				deltaTime = GetTickCount() - time_end;
				time_end = GetTickCount();

				objectDraw(deltaTime);// ����ϱ�
				setCursorPos(0, 24);
				if (deltaTime < 33)
					Sleep(33 - deltaTime); // ������ ����,,?
				for (int i = 1; i < GameStartSnakeLength; i++) {
					if (snakeSkin[0].posX == snakeSkin[i].posX && snakeSkin[0].posY == snakeSkin[i].posY) {
						setCursorPos(31, 6);
						SetColor(0b0000, 0b1111);
						printf("���� ����");
						setCursorPos(25, 7);
						printf("����� ������ %d�Դϴ�!", score);
						setCursorPos(27, 8);
						printf("�ٽ� �Ͻðڽ��ϱ�?");

						setCursorPos(26, 10);
						printf("[ YES ]	[ N0 ]");
						while (1) {
							if (_kbhit()) {
								ch = getch();
								if (ch == 'Y' || ch == 'y') {
									GameState = 1;
									menuSelected = 1;
									score = 0;
									break;
								}
								else if (ch == 'N' || ch == 'n') {
									GameState = 0;
									menuSelected = 0;
									break;
								}
							}
						}
						break;
					}
				}
			}
			introMenu();
			printf("%s", ScreenBuffer);
		}
		else if (menuSelected == 2) { // 2�� ���
			screenInitialize();
			printf("%s", ScreenBuffer);
			GameStory();
			printf("%s", ScreenBuffer);

			while (1) {
				if (_kbhit()) {
					ch = getch();
					if (ch == 'Y' || ch == 'y') { // Y�� ������ ���
						Initialize();
						menuSelected = 0; // ���õ� �޴� �ʱ�ȭ
						break; // �ݺ��� ����
					}
					else if (ch == 'N' || ch == 'n') { // Y�� ������ ���
						
					}
				}
			}
			introMenu();
			printf("%s", ScreenBuffer);
		}

		while (1) {
			if (_kbhit()) {
				ch = getch();
				switch (ch) {
				case '1':
					menuSelected = 1; // 1�� �޴� ����
					break;
				case '2':
					menuSelected = 2; // 2�� �޴� ����
					break;
				case '3':
				case 27:
					exit(0);
					break;
				default:
					// �߸��� �Է� ó��
					break;
				}

				if (menuSelected != 0) {
					break; // �޴� ������ �Ǿ����� �ݺ��� ����
				}
			}
		}
	}

	CHECKERROR(Release()); // �������ֱ�

	exit(1);
	return 0;
}

int Initialize() {
	score = 0;
	GameState = 1; // �� ����
	GameStartSnakeLength = 3; // ó�� ���� �� ���� ũ��
	ActiveSnakeNum = GameStartSnakeLength; // ���� ���̸� Ȱ��ȭ�ƴ��� �ʱ�ȭ
	setScreenSize(70, 20); // �� ������
	setCursorVisibility(0); // �ȱ����Ÿ�
	SetColor(0b1111, 0b0000); // ���� ��� ��
	ClearBuffer(); // ȭ�� �ʱ�ȭ
	return 0;
}

int Release()
{
	return 0;
}

int DrawBuffer(int DeltaTime) {
	SetColor(0b0000, 0b1001);
	setCursorPos(0, 22); // �ð� ����� ��ġ
	if (DeltaTime != 0){ // 0�� �ƴҶ� ���
		printf("time : %d                 \nfps :%d                  \n", DeltaTime, 1000 / DeltaTime);
	}
	setCursorPos(35, 22);
	printf("�� ��");
	setCursorPos(37, 23);
	printf("%d", score);
	return 0;
}

int DeltaTimeSum = 0;

int objectDraw(int DeltaTime) {
	ProcessInput();

	setCursorPos(0, 0);
	SetColor(0b1111, 0b1001);
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
	printf("��"); // ���

	//snake
	int i = 0;
	while (i < GameStartSnakeLength) // i�� �� ���̺��� ���������� �ݺ�
	{
		setCursorPos(snakeSkin[i].posX, snakeSkin[i].posY); // ��ǥ
		SetColor(0b1111, 0b0010); // ����
		printf("O"); // ����
		i = i + 1; // �߰�
	}
	DrawBuffer(DeltaTime);
	return 0;
}