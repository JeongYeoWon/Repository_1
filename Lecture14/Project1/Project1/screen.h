#pragma once

// ȭ���� �����ϴ� �ִ� �޸� 65536
char ScreenBuffer[65536];

void setScreenSize(int width, int height);
void setCursorPos(int x, int y);
void SetColor(unsigned short backgroundColor, unsigned short textColor); // �׵θ�

void ClearBuffer();
int WriteToBuffer(int x, int y, const char* str);

