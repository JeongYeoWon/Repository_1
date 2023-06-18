#include <Windows.h>
#include "screen.h"
#include "menu.h"

int introMenu() {
	setCursorPos(0, 0); // 출력할 좌표
	SetColor(0b1111, 0b1001); // 색상
	WriteToBuffer(29, 9, "사과먹어사각");
	WriteToBuffer(10, 15, "1. 게임 시작");
	WriteToBuffer(29, 15, "2. 게임 설명");
	WriteToBuffer(49, 15, "3. 게임 종료");
}

int screenInitialize() {
	setCursorPos(0, 0);
	SetColor(0b0000, 0b0000);
	setScreenSize(70, 20);
	ClearScreen();
}

int GameStory() {
	setCursorPos(0, 0);
	setScreenSize(70, 15);
	ClearBuffer();
	SetColor(0b1111, 0b1001);
	WriteToBuffer(18, 2, "◇지렁이에게 사과를 먹이는 게임◇");
	WriteToBuffer(2, 4, "◆ 이 게임은 방향 키를 사용하여 지렁이를 움직이는 게임입니다.");
	WriteToBuffer(2, 6, "◆ 사과를 먹으면 지렁이가 길어지며 점수가 오릅니다.");
	WriteToBuffer(2, 8, "◆ 지렁이가 벽에 닿을 경우 반대편 벽으로 이동됩니다.");
	WriteToBuffer(2, 10, "◆ 지렁이가 자신의 몸과 부딪힐 경우 게임이 종료됩니다.");
	WriteToBuffer(28, 13, "나가시겠습니까?");
	WriteToBuffer(26, 14, "[ YES ]      [ NO ]");
}