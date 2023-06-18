#include <Windows.h>
#include "object.h"

void InitApple() // 사과
{
	//apple 초기화
	srand(time(NULL));
	apple.posX = (rand() % 68) + 2; // 좌표 랜덤
	apple.posY = (rand() % 18) + 2; // 22
	apple.isActive = 1; // 활성화함
}

int objectInitialize() {
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


	if (snakeSkin[0].posX < 1 || snakeSkin[0].posX >= 70 ||
		snakeSkin[0].posY < 1 || snakeSkin[0].posY >= 20)
	{
		// 뱀의 머리 위치를 화면의 반대편으로 이동시킴
		if (snakeSkin[0].posX < 1)
			snakeSkin[0].posX = 70 - 1;
		else if (snakeSkin[0].posX >= 70)
			snakeSkin[0].posX = 1;
		else if (snakeSkin[0].posY < 1)
			snakeSkin[0].posY = 20 - 1;
		else if (snakeSkin[0].posY > 20)
			snakeSkin[0].posY = 1;
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

