#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "screen.h"
#include "util.h"
#include "menu.h"

#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75

int Initialize(); // 게임 설정 초기화
int Release(); // 해제해주기
int DrawBuffer(int DeltaTime); // 화면 출력

//게임스테이트가 0일때 무조건 게임 종료
int GameState;
int GameStartSnakeLength; // 뱀 몸통 길이
int ActiveSnakeNum; // 활성화된 뱀 몸통 갯수

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

int main()
{
	CHECKERROR(Initialize()); // 게임 설정을 초기화화면서 에러 검사..?하기

	introMenu(); // 메뉴를 출력해요
	unsigned long time_end = GetTickCount(); // 현재 시스템의 시간 기록할 변수
	unsigned long deltaTime = GetTickCount(); // 현재 시스템의 시간 기록할 변수

	while (GameState) // 게임종료되기 전까지 반복
	{
		if (kbhit()) // 키 입력받을 때까지 기다리는 것을 제어
		{
			char ch = getch();

			switch (ch)
			{
			case '1':

				break;
			case '2': // 숫자 2를 눌렀을때
				ClearScreen();
				GameStory();
				
				break;
			case '3':

				break;
			case '4':
			case 27:
				GameState = 0;
				break;
			default:
				// 잘못된 입력 처리
				break;
			}
		}

		deltaTime = GetTickCount() - time_end;
		time_end = GetTickCount();

		DrawBuffer(deltaTime); // 출력하기

		if (deltaTime < 33)
			Sleep(33 - deltaTime); // 프레임 조절,,?
	}

	CHECKERROR(Release()); // 해제해주기

	exit(1);
	return 0;
}

int Initialize() {
	GameState = 1;
	setScreenSize(70, 20);
	setCursorVisibility(0); // 안깜빡거림
	ClearBuffer();

	return 0;
}

int Release()
{
	return 0;
}

void ClearScreen() {
	setCursorPos(0, 0);
	SetColor(0b1000, 0b1000);
	setScreenSize(70, 20); // 화면을 초기화
	ClearBuffer();
}

void MoveSnake(int dir)
{
	//몸통이동 부분
	int i = GameStartSnakeLength - 1; // 몸통보다 - 1
	while (i > 0) // i가 0보다 작을때까지 반복
	{
		snakeSkin[i].posX = snakeSkin[i - 1].posX; // 몸통[i - 1]의 x좌표를 몸통[i]에 대입,, 그냥 1칸씩 이동함
		snakeSkin[i].posY = snakeSkin[i - 1].posY;
		i = i - 1;
	}
	//머리 이동부분
	snakeSkin[0].posX = snakeSkin[0].posX + 1; // 머리는 1칸씩 이동
	snakeSkin[0].posY = snakeSkin[0].posY;
}

int DeltaTimeSum = 0;

int DrawBuffer(int DeltaTime) // 출력함
{
	setCursorPos(0, 0); // 출력할 좌표
	SetColor(0b1111, 0b0000); // 색상
	printf("%s", ScreenBuffer);
	
	DeltaTimeSum = DeltaTimeSum + DeltaTime; // 게임 루프 사이의 경과 시간
	if (DeltaTimeSum >= 500) // 시간이 500보다 크거나 같을때,,??
	{
		MoveSnake(0); // 뱀을 이동시킴
		DeltaTimeSum = 0; // 0으로 초기화
	}


	//apple
	setCursorPos(apple.posX, apple.posY); // 사과 위치
	SetColor(0b1111, 0b0100); // 색상
	printf("*"); // 출력

	//snake
	int i = 0;
	while (i < GameStartSnakeLength) // i가 뱀 길이보다 작을때까지 반복
	{
		setCursorPos(snakeSkin[i].posX, snakeSkin[i].posY); // 좌표
		SetColor(0b1111, 0b0010); // 색상
		printf("O"); // 몸통
		i = i + 1; // 추가
	} 

	SetColor(0b0000, 0b1111);
	setCursorPos(0, 22); // 시간 출력할 위치
	if (DeltaTime != 0) // 0이 아닐때 출력
		printf("time : %d                 \nfps :%d                  \n", DeltaTime, 1000 / DeltaTime);

	return 0;
}