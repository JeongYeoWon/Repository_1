#pragma once

char ScreenBuffer[65536];

void setScreenSize(int width, int height); // ȭ�� ũ��
void setCursorIcon(int isActive); // Ŀ�� �������̿�..?
void setCursorPos(int x, int y); // Ŀ�� ��ġ ����
void setCursorVisibility(int isVisible); // ����,,��?
void SetColor(unsigned short backgroundColor, unsigned short textColor); // ����/�ؽ�Ʈ �� ������

void ClearBuffer(); // ȭ�� ���� �ʱ�ȭ(������� ������~)
int WriteToBuffer(int x, int y, const char* str);
