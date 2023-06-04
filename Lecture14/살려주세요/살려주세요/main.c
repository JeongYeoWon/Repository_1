#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "screen.h"
#include "util.h"

#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75

int Gamestate = 0;
int isGameRunning = 1;

int Initialize();
int Relaese();
int DrawBuffer();
int ClearScreen();
int ChoiceMenu();
void InitializeSnake();

int main() {
	isGameRunning = 1;

	CHECKERROR(Initialize());

	unsigned long time_end = GetTickCount(); // ���� �ý����� �ð��� ���
	unsigned long deltaTime = GetTickCount();

	while (isGameRunning) {
		SetColor(0b1111, 0b0000); // ��
		/*DrawBuffer();*/
		

		/* deltaTime = GetTickCount() - time_end;
		time_end = GetTickCount();
		if (time < 17) {
			Sleep(17 - deltaTime);
		}

		if (deltaTime != 0) {
			setCursorPos(0, 22);
			printf("time : %d \nfps %d\n", deltaTime, 1000 / deltaTime);
		} */
		ChoiceMenu();
	}

	CHECKERROR(Relaese());

	exit(1);
	return 0;
}

int Initialize() { //
	/*Gamestate = 0;*/
	setScreenSize(70, 20);

	ClearBuffer();

	return 0;
}

int Relaese() { // ����
	return 0;
}

int DrawBuffer() {
	setCursorPos(0, 0);
	printf("%s", ScreenBuffer);
	return 0;
}

int ClearScreen() {
	SetColor(0b0000, 0b0000);
	setScreenSize(70, 20);
	help();
	DrawBuffer();
	return 0;
}

int GameStory() {
	SetColor(0b1111, 0b0000);
	setScreenSize(50, 10);
	ClearBuffer();
	DrawBuffer();
}


int ChoiceMenu() {
	char ch = 0;
	bool state0 = false;
	bool state1 = false;
	bool state2 = false;
	bool state3 = false;
	switch (Gamestate) {
	case 0:
		WriteToBuffer(30, 6, "������ ����");
		WriteToBuffer(4, 13, "1. ���� ����");
		WriteToBuffer(4, 15, "2. ���� ����");
		WriteToBuffer(4, 17, "3. ��ŷ");
		WriteToBuffer(4, 19, "4. ���� ����");
		DrawBuffer();
		ClearBuffer();

		if (!state0) {
			while (ch != '1' && ch != '2' && ch != '4' && ch != 27) { // 2��4�� ESC�� ������ �ʾ��� ������ �ݺ�
				ch = _getch(); // �Է¹ޱ�
			}
			state0 = true;
		}
		if (ch == '1') { // 1���� ���
			Gamestate = 1;
		}
		if (ch == '2') {
			Gamestate = 2;
		}
		if (ch == '3') {
			Gamestate = 3;
		}
		if (ch == '4' || ch == 27) {
			isGameRunning = 0;
		}
		break;

	case 1:
		ClearScreen();
		SetColor(0b1111, 0b0000);
		Initialize();
		DrawBuffer();

		InitializeSnake(35, 10);
		if (!state1) {
			ch = 0;
			while (ch != 27) {
				ch = _getch();
			}
			state1 = true;
		}
		break;
	case 2:
		ClearScreen();
		GameStory();
		WriteToBuffer(10, 5, "�̰��� ������ ���� ���丮�Դϴ�.");
		WriteToBuffer(18, 6, "�����ðڽ��ϱ�?");
		WriteToBuffer(16, 7, "[ YES ]      [ NO ]");
		DrawBuffer();

		if (!state2) {
			ch = 0;
			while (ch != 'y' && ch != 27) {
				ch = _getch();
			}
			state2 = true;
		}
		if (ch == 'y' || ch == 27) {
			ClearScreen();
			Initialize();
			Gamestate = 0;
		}
		break;
	}
	return 0;
}

int Item() {
	int random = rand();
	SetColor(0b1111, 0b0000);
	WriteToBuffer(random % 70, random %20, "*\n��");
}

void InitializeSnake(int snakeX, int snakeY) {
	char ch = 0;
	int i = 0;
	int j = 0;
	bool GameOver = true;
	setCursorPos(snakeX, snakeY);
	printf("#");
	while (GameOver) {
		if (_kbhit()) {
			ch = _getch();
			if (ch == RIGHT) {
				while (GameOver) {
					setCursorPos(snakeX + i, snakeY);
					printf("#");
					setCursorPos(snakeX + i - 1, snakeY);
					printf(" ");
					Sleep(500);
					i++;
				}
			}
			if (ch == LEFT) {
				while (GameOver) {
					setCursorPos(snakeX - i, snakeY);
					printf("#");
					setCursorPos(snakeX - i + 1, snakeY);
					printf(" ");
					Sleep(500);
					i++;
				}
			}
			if (ch == UP) {
				while (GameOver) {
					setCursorPos(snakeX, snakeY - i);
					printf("#");
					setCursorPos(snakeX, snakeY - i + 1);
					printf(" ");
					Sleep(500);
					i++;
				}
			}
			if (ch == DOWN) {
				while (GameOver) {
					setCursorPos(snakeX, snakeY + i);
					printf("#");
					setCursorPos(snakeX, snakeY + i - 1);
					printf(" ");
					Sleep(500);
					i++;
				}
			}
		}
	}
}