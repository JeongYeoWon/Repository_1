#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "screen.h"
#include "util.h"

int Initialize(); // 게임 설정 초기화
int Release(); // 해제해주기
int DrawBuffer(int DeltaTime); // 화면 출력

//게임스테이트가 0일때 무조건 게임 종료
int GameState;
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

int main()
{
	CHECKERROR(Initialize()); // 게임 설정을 초기화화면서 에러 검사..?하기
	unsigned long time_end = GetTickCount(); // 현재 시스템의 시간 기록할 변수
	unsigned long deltaTime = GetTickCount(); // 현재 시스템의 시간 기록할 변수

	setCursorPos(0, 0); // 출력할 좌표
	SetColor(0b1111, 0b0000); // 색상
	printf("%s", ScreenBuffer);
	setCursorPos(30, 10);
	printf("지렁이 키우기\n\n			시작하려면 1번을 누르시오.\n	    	           1. 방향 키로 이동\n		    2. 뱀의 머리가 몸통에 닿을 시 종료");

	int startFlag = 0; // 시작 플래그
	while (startFlag != 1) // 1을 입력할 때까지 반복
	{
		if (_kbhit()) // 키 입력 여부 확인
		{
			char key = _getch(); // 키보드 입력 받기

			if (key == '1') // 1을 입력하면 시작 플래그를 1로 설정하고 반복문 종료
			{
				startFlag = 1;
				break;
			}
		}
	}

	while (GameState) // 게임종료되기 전까지
	{
		deltaTime = GetTickCount() - time_end;
		time_end = GetTickCount();

		DrawBuffer(deltaTime); // 출력하기

		if (deltaTime < 33)
			Sleep(33 - deltaTime); // 프레임 조절,,?

		for (int i = 1; i < GameStartSnakeLength; i++) {
			if (snakeSkin[0].posX == snakeSkin[i].posX && snakeSkin[0].posY == snakeSkin[i].posY) {
				setCursorPos(30, 6);
				SetColor(0b0000, 0b1111);
				printf("게임 오버");
				/*Sleep(1000);*/
				setCursorPos(10, 23);
				GameState = 0;
			}
		}
	}

	CHECKERROR(Release()); // 해제해주기

	exit(1);
	return 0;
}

void InitApple() // 사과
{
	//apple 초기화
	srand(time(NULL));
	apple.posX = (rand() % 68) + 2; // 좌표 랜덤
	apple.posY = (rand() % 18) + 2; // 22
	apple.isActive = 1; // 활성화함
}

int Initialize() // 초기화
{
	GameState = 1; // 겜 시작
	GameStartSnakeLength = 3; // 처음 시작 시 뱀의 크기
	ActiveSnakeNum = GameStartSnakeLength; // 뱀의 길이를 활성화됐는지 초기화
	setScreenSize(70, 20); // 맵 사이즈
	setCursorVisibility(0); // 안깜빡거림
	SetColor(0b1000, 0b1111); // 맵의 배경 색
	ClearBuffer(); // 화면 초기화

	//GameObject 초기화

	//사과 초기화
	InitApple();
	int i = 0;
	while (i < GameStartSnakeLength) // i가 뱀의 몸통보다 작을때까지
	{
		if (snakeSkin[i].posX == apple.posX // 뱀의 몸통의 x좌표가 사과의 x좌표와 같고 뱀의 몸통 y좌표가 사과의 y좌표와 같을 때
			&& snakeSkin[i].posY == apple.posY)
		{
			InitApple(); // 사과
			i = 0; // i를 0으로 대입
		}
		else // 아닐 경우 i + 1
		{
			i = i + 1;
		}
	}

	//뱀 몸뚱아리 초기화
	i = 0;
	while (i < MAX_SNAKE_LENGTH) // i가 1400보다 작을 때까지 반복
	{
		//snakeSkin[i].posX = 35; // 뱀의몸 x좌표를 35;
		//snakeSkin[i].posY = 10; // 뱀의몸 y좌표를 35;
		snakeSkin[i].isActive = 0; // 활성화 안함
		i = i + 1;
	}

	i = 0;
	while (i < GameStartSnakeLength) // i가 뱀몸통길이보다 작을 때까지 반복
	{
		snakeSkin[i].posX = 35 - i; // 뱀의몸 x좌표를 35-i;
		snakeSkin[i].posY = 10; // 뱀의몸 y좌표를 10;
		snakeSkin[i].isActive = 1; // 활성화함
		i = i + 1;
	}

	return 0;
}

int Release()
{
	return 0;
}

int dir; // 현재 뱀의 이동 방향을 저장하는 변수

void MoveSnake()
{
	//몸통이동 부분
	int i = GameStartSnakeLength - 1; // 몸통보다 - 1
	while (i > 0) // i가 0보다 작을때까지 반복
	{
		snakeSkin[i].posX = snakeSkin[i - 1].posX; // 몸통[i - 1]의 x좌표를 몸통[i]에 대입,, 그냥 1칸씩 이동함
		snakeSkin[i].posY = snakeSkin[i - 1].posY;
		i = i - 1;
	}

	switch (dir)
	{
	case 0: // 오른쪽
			snakeSkin[0].posX = snakeSkin[0].posX + 1;
			snakeSkin[0].posY = snakeSkin[0].posY;
		break;
	case 1: // 왼쪽
		snakeSkin[0].posX = snakeSkin[0].posX - 1;
		snakeSkin[0].posY = snakeSkin[0].posY;
		break;
	case 2: // 위쪽
		snakeSkin[0].posX = snakeSkin[0].posX;
		snakeSkin[0].posY = snakeSkin[0].posY - 1;
		break;
	case 3: // 아래쪽
		snakeSkin[0].posX = snakeSkin[0].posX;
		snakeSkin[0].posY = snakeSkin[0].posY + 1;
		break;
	default:
		break;
	}


	if (snakeSkin[0].posX < 0 || snakeSkin[0].posX >= 70 ||
		snakeSkin[0].posY < 0 || snakeSkin[0].posY >= 20)
	{
		// 뱀의 머리 위치를 화면의 반대편으로 이동시킴
		if (snakeSkin[0].posX < 0)
			snakeSkin[0].posX = 70 - 1;
		else if (snakeSkin[0].posX >= 70)
			snakeSkin[0].posX = 0;
		else if (snakeSkin[0].posY < 0)
			snakeSkin[0].posY = 20 - 1;
		else if (snakeSkin[0].posY > 20)
			snakeSkin[0].posY = 0;
	}

	////머리 이동부분
	//snakeSkin[0].posX = snakeSkin[0].posX + 1; // 머리는 1칸씩 이동
	//snakeSkin[0].posY = snakeSkin[0].posY;
}

void ProcessInput()
{
	if (_kbhit()) // 키 입력 여부 확인
	{
		char key = _getch(); // 키보드 입력 받기

		switch (key)
		{
		case 72: // 위쪽으로 이동
			dir = 2;
			break;
		case 80: // 아래쪽으로 이동
			dir = 3;
			break;
		case 75: // 왼쪽으로 이동
			dir = 1;
			break;
		case 77: // 오른쪽으로 이동
			dir = 0;
			break;
		default:
			break;
		}
	}

	if (snakeSkin[0].posX == apple.posX && snakeSkin[0].posY == apple.posY)
	{
		score++;
		// 사과를 먹었을 경우 뱀의 길이를 증가시킴
		GameStartSnakeLength++;
		ActiveSnakeNum++;
		InitApple(); // 새로운 사과 생성
	}
}

int DeltaTimeSum = 0;


int DrawBuffer(int DeltaTime) // 출력함
{
	ProcessInput(); // 방향키 제어

	setCursorPos(0, 0); // 출력할 좌표
	SetColor(0b1111, 0b0000); // 색상
	printf("%s", ScreenBuffer);

	DeltaTimeSum = DeltaTimeSum + DeltaTime; // 게임 루프 사이의 경과 시간
	if (DeltaTimeSum >= 500) // 시간이 500보다 크거나 같을때,,??
	{
		MoveSnake(); // 뱀을 이동시킴
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
	setCursorPos(10, 22);
	printf("점수 : %d", score);
	return 0;
}