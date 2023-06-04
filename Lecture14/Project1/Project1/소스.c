#include <stdio.h>
#include <time.h>
#include "screen.h"
#include "util.h"

int Gamestate = 0;

int Initialize();
int Relaese();
int DrawBuffer();

int main() {
	int isGameRunning = 1;

	CHECKERROR(Initialize());

	unsigned long time_end = GetTickCount(); // 현재 시스템의 시간을 기록
	unsigned long deltaTime = GetTickCount();

	while (isGameRunning) {
		SetColor(0b1111, 0b0000); // 색

		WriteToBuffer(30, 6, "지렁이 게임");
		WriteToBuffer(2, 14, "1. 게임 시작");
		WriteToBuffer(2, 16, "2. 게임 설명");
		WriteToBuffer(2, 18, "3. 랭킹");
		WriteToBuffer(2, 20, "4. 게임 종료");
		/*isGameRunning = 0;*/
		DrawBuffer();
		deltaTime = GetTickCount() - time_end;
		time_end = GetTickCount();
		if (time < 17) {
			Sleep(17- deltaTime);
		}

		if (deltaTime != 0) {
			printf("time : %d \nfps %d\n", deltaTime, 1000 / deltaTime);
		}
	}

	CHECKERROR(Relaese());

	exit(1);
	return 0;
}

int Initialize() { //
	Gamestate = 0;
	setScreenSize(70, 20);

	ClearBuffer();

	return 0;
}

int Relaese() { // 끌때
	return 0;
}

int DrawBuffer() {
	setCursorPos(0, 0);
	printf("%s", ScreenBuffer);
	return 0;
}