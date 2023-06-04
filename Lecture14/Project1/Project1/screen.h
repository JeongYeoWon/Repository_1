#pragma once

// 화면의 차지하는 최대 메모리 65536
char ScreenBuffer[65536];

void setScreenSize(int width, int height);
void setCursorPos(int x, int y);
void SetColor(unsigned short backgroundColor, unsigned short textColor); // 테두리

void ClearBuffer();
int WriteToBuffer(int x, int y, const char* str);

