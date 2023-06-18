#pragma once

int GameStartSnakeLength; // 뱀 몸통 길이
int ActiveSnakeNum; // 활성화된 뱀 몸통 갯수
int score;

#define MAX_SNAKE_LENGTH 1400 // 우아,, 짱길다
struct GameObject // 게임 오브젝트 좌표랑 활성화
{
	int posX;
	int posY;
	int isActive;
};

//0번이 머리
struct GameObject snakeSkin[MAX_SNAKE_LENGTH]; // 뱀 몸통
struct GameObject apple; // 사과

void InitApple();
void MoveSnake();
int objectInitialize();
void ProcessInput();