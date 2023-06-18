#include <Windows.h>
#include "screen.h"
#include "menu.h"

int introMenu() {
	setCursorPos(0, 0); // ����� ��ǥ
	SetColor(0b1111, 0b1001); // ����
	WriteToBuffer(29, 9, "����Ծ�簢");
	WriteToBuffer(10, 15, "1. ���� ����");
	WriteToBuffer(29, 15, "2. ���� ����");
	WriteToBuffer(49, 15, "3. ���� ����");
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
	WriteToBuffer(18, 2, "�������̿��� ����� ���̴� ���ӡ�");
	WriteToBuffer(2, 4, "�� �� ������ ���� Ű�� ����Ͽ� �����̸� �����̴� �����Դϴ�.");
	WriteToBuffer(2, 6, "�� ����� ������ �����̰� ������� ������ �����ϴ�.");
	WriteToBuffer(2, 8, "�� �����̰� ���� ���� ��� �ݴ��� ������ �̵��˴ϴ�.");
	WriteToBuffer(2, 10, "�� �����̰� �ڽ��� ���� �ε��� ��� ������ ����˴ϴ�.");
	WriteToBuffer(28, 13, "�����ðڽ��ϱ�?");
	WriteToBuffer(26, 14, "[ YES ]      [ NO ]");
}