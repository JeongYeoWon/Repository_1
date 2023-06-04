#include "screen.h"
#include <Windows.h>

// 화면의 차지하는 최대 메모리 65536
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

/*  색
	글자
	0000
	1111

	배경
	10000
*/

/* 배경색을 파랑, 텍스트 색을 검정으로 할 경우
*  0b0001         0b0000
* color를 0b0000 초기화
* color를 0b0000 + 0b10000 = ob000010000(근데 이게 맞나 이게 아닐지도 내가 또,,) */

void SetColor(unsigned short backgroundColor, unsigned short textColor) {
	unsigned short color = textColor;
	color = color + (backgroundColor << 4); // 0001(파랑)을 넣었을때 배경으로 넣으려면 0001 0000으로 들어가야하기 때문에 4칸 비트시프팅
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void ClearBuffer() {
	int y = 0;
	while (y < screenHeight + 2) {
		int x = 0;
		while (x < screenWidth + 2) {
			if (y == 0 || y == screenHeight + 1) {
				ScreenBuffer[x + (y * (screenWidth + 3))] = '-'; // 개행문자를 포함해야하기 때문에 3
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

int WriteToBuffer(int x, int y, const char* str) { // x, y가 배열의 밖으로 넘어갈 경우를 대비해 int,,,,
	int i = 0;
	while (i < strlen(str)) {
		ScreenBuffer[x + (y * (screenWidth + 3)) + i] = str[i]; // 개행문자 주의(사이즈 맞추어야함)
		i = i + 1;
	}

	return 0;
}