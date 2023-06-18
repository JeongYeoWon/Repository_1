#pragma once

char ScreenBuffer[65536];

void setScreenSize(int width, int height); // 화면 크기
void setCursorIcon(int isActive); // 커서 아이콘이요..?
void setCursorPos(int x, int y); // 커서 위치 설정
void setCursorVisibility(int isVisible); // 가시,,성?
void SetColor(unsigned short backgroundColor, unsigned short textColor); // 배경색/텍스트 색 설정함

void ClearBuffer(); // 화면 버퍼 초기화(빈공간을 만들어요~)
int WriteToBuffer(int x, int y, const char* str);
