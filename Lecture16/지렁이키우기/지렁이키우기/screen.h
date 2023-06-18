#pragma once

char ScreenBuffer[65536];

void setScreenSize(int width, int height); // 화면 크기룰 정할 함수
void setCursorPos(int x, int y); // 좌표
void setCursorVisibility(int isVisible); // 커서 가시성 설정
void SetColor(unsigned short backgroundColor, unsigned short textColor); // 배경색/텍스트 색 설정함

void ClearScreen();
void ClearBuffer(); // 화면 버퍼 초기화
int WriteToBuffer(int x, int y, const char* str); // 좌표를 설정해 문자 출력할 함수