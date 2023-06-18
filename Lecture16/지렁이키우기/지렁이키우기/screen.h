#pragma once

char ScreenBuffer[65536];

void setScreenSize(int width, int height); // ȭ�� ũ��� ���� �Լ�
void setCursorPos(int x, int y); // ��ǥ
void setCursorVisibility(int isVisible); // Ŀ�� ���ü� ����
void SetColor(unsigned short backgroundColor, unsigned short textColor); // ����/�ؽ�Ʈ �� ������

void ClearScreen();
void ClearBuffer(); // ȭ�� ���� �ʱ�ȭ
int WriteToBuffer(int x, int y, const char* str); // ��ǥ�� ������ ���� ����� �Լ�