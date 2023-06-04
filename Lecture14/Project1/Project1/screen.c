#include "screen.h"
#include <Windows.h>

// ȭ���� �����ϴ� �ִ� �޸� 65536
int screenWidth = 70;
int screenHeight = 20;

void setScreenSize(int width, int height) {
	screenWidth = width;
	screenHeight = height;
}

void setCursorPos(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*  ��
	����
	0000
	1111

	���
	10000
*/

/* ������ �Ķ�, �ؽ�Ʈ ���� �������� �� ���
*  0b0001         0b0000
* color�� 0b0000 �ʱ�ȭ
* color�� 0b0000 + 0b10000 = ob000010000(�ٵ� �̰� �³� �̰� �ƴ����� ���� ��,,) */

void SetColor(unsigned short backgroundColor, unsigned short textColor) {
	unsigned short color = textColor;
	color = color + (backgroundColor << 4); // 0001(�Ķ�)�� �־����� ������� �������� 0001 0000���� �����ϱ� ������ 4ĭ ��Ʈ������
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void ClearBuffer() {
	int y = 0;
	while (y < screenHeight + 2) {
		int x = 0;
		while (x < screenWidth + 2) {
			if (y == 0 || y == screenHeight + 1) {
				ScreenBuffer[x + (y * (screenWidth + 3))] = '-'; // ���๮�ڸ� �����ؾ��ϱ� ������ 3
			}
			else {
				if (x == 0 || x == screenWidth + 1) {
					ScreenBuffer[x + (y * (screenWidth + 3))] = '|';
				}
				else {
					ScreenBuffer[x + (y * (screenWidth + 3))] = ' ';
				}
			}
			x = x + 1;
		}
		ScreenBuffer[x + (y * (screenWidth + 3))] = '\n';
		y = y + 1;
	}
	ScreenBuffer[(y * (screenWidth + 3))] = '\0';
}

int WriteToBuffer(int x, int y, const char* str) { // x, y�� �迭�� ������ �Ѿ ��츦 ����� int,,,,
	int i = 0;
	while (i < strlen(str)) {
		ScreenBuffer[x + (y * (screenWidth + 3)) + i] = str[i]; // ���๮�� ����(������ ���߾����)
		i = i + 1;
	}

	return 0;
}