#include <Windows.h>
#include "menu.h"
#include "screen.h"

void introMenu() {
	SetColor(0b1111, 0b0000);
	WriteToBuffer(30, 6, "지렁이 게임");
	WriteToBuffer(4, 13, "1. 게임 시작");
	WriteToBuffer(4, 15, "2. 게임 설명");
	WriteToBuffer(4, 17, "3. 랭킹");
	WriteToBuffer(4, 19, "4. 게임 종료");
}

void GameStory() {
	SetColor(0b0000, 0b0000);
	setScreenSize(50, 10);
	ClearBuffer();
	WriteToBuffer(10, 5, "이것은 지렁이 게임 스토리입니다.");
	WriteToBuffer(18, 6, "나가시겠습니까?");
	WriteToBuffer(16, 7, "[ YES ]      [ NO ]");
}