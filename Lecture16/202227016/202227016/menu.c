#include <Windows.h>
#include "menu.h"
#include "screen.h"

void introMenu() {
	SetColor(0b1111, 0b0000);
	WriteToBuffer(30, 6, "������ ����");
	WriteToBuffer(4, 13, "1. ���� ����");
	WriteToBuffer(4, 15, "2. ���� ����");
	WriteToBuffer(4, 17, "3. ��ŷ");
	WriteToBuffer(4, 19, "4. ���� ����");
}

void GameStory() {
	SetColor(0b0000, 0b0000);
	setScreenSize(50, 10);
	ClearBuffer();
	WriteToBuffer(10, 5, "�̰��� ������ ���� ���丮�Դϴ�.");
	WriteToBuffer(18, 6, "�����ðڽ��ϱ�?");
	WriteToBuffer(16, 7, "[ YES ]      [ NO ]");
}