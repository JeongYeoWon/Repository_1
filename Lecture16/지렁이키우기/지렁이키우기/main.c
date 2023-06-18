#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "screen.h"
#include "util.h"
#include "menu.h"
#include "object.h"

int Initialize(); // 초기화
int Release(); // 해제
int DrawBuffer(int DeltaTime); // 화면 출력
int objectDraw(int DeltaTime);

int GameState; // 게임 활성화 유무

int main() {

	CHECKERROR(Initialize());

	introMenu();
	printf("%s", ScreenBuffer);
	setCursorPos(30, 22);

	unsigned long time_end = GetTickCount(); // 현재 시스템의 시간의 끝?을 기록할 변수
	unsigned long deltaTime = GetTickCount(); // 현재 시스템의 시간을 기록할 변수
	
	char ch;
	int menuSelected = 0; // 선택된 메뉴

	while (1) {
		if (_kbhit()) {
			ch = getch();
			switch (ch) {
			case '1':
				menuSelected = 1; // 1번 메뉴 선택
				break;
			case '2':
				menuSelected = 2; // 2번 메뉴 선택
				break;
			case '3':
			case 27:
				exit(0);
				break;
			default:

				break;
			}

			if (menuSelected != 0) {
				break; // 메뉴 선택이 되었으면 반복문 종료
			}
		}
	}

	while (menuSelected != 4) { // 메뉴가 4가 아닐때까지
		if (menuSelected == 1) { // 1일 경우
			setCursorPos(0, 0);
			Initialize();
			objectInitialize();
			while (GameState) {
				deltaTime = GetTickCount() - time_end;
				time_end = GetTickCount();

				objectDraw(deltaTime);// 출력하기
				setCursorPos(0, 24);
				if (deltaTime < 33)
					Sleep(33 - deltaTime); // 프레임 조절,,?
				for (int i = 1; i < GameStartSnakeLength; i++) {
					if (snakeSkin[0].posX == snakeSkin[i].posX && snakeSkin[0].posY == snakeSkin[i].posY) {
						setCursorPos(31, 6);
						SetColor(0b0000, 0b1111);
						printf("게임 오버");
						setCursorPos(25, 7);
						printf("당신의 점수는 %d입니다!", score);
						setCursorPos(27, 8);
						printf("다시 하시겠습니까?");

						setCursorPos(26, 10);
						printf("[ YES ]	[ N0 ]");
						while (1) {
							if (_kbhit()) {
								ch = getch();
								if (ch == 'Y' || ch == 'y') {
									GameState = 1;
									menuSelected = 1;
									score = 0;
									break;
								}
								else if (ch == 'N' || ch == 'n') {
									GameState = 0;
									menuSelected = 0;
									break;
								}
							}
						}
						break;
					}
				}
			}
			introMenu();
			printf("%s", ScreenBuffer);
		}
		else if (menuSelected == 2) { // 2일 경우
			screenInitialize();
			printf("%s", ScreenBuffer);
			GameStory();
			printf("%s", ScreenBuffer);

			while (1) {
				if (_kbhit()) {
					ch = getch();
					if (ch == 'Y' || ch == 'y') { // Y를 선택한 경우
						Initialize();
						menuSelected = 0; // 선택된 메뉴 초기화
						break; // 반복문 종료
					}
					else if (ch == 'N' || ch == 'n') { // Y를 선택한 경우
						
					}
				}
			}
			introMenu();
			printf("%s", ScreenBuffer);
		}

		while (1) {
			if (_kbhit()) {
				ch = getch();
				switch (ch) {
				case '1':
					menuSelected = 1; // 1번 메뉴 선택
					break;
				case '2':
					menuSelected = 2; // 2번 메뉴 선택
					break;
				case '3':
				case 27:
					exit(0);
					break;
				default:
					// 잘못된 입력 처리
					break;
				}

				if (menuSelected != 0) {
					break; // 메뉴 선택이 되었으면 반복문 종료
				}
			}
		}
	}

	CHECKERROR(Release()); // 해제해주기

	exit(1);
	return 0;
}

int Initialize() {
	score = 0;
	GameState = 1; // 겜 시작
	GameStartSnakeLength = 3; // 처음 시작 시 뱀의 크기
	ActiveSnakeNum = GameStartSnakeLength; // 뱀의 길이를 활성화됐는지 초기화
	setScreenSize(70, 20); // 맵 사이즈
	setCursorVisibility(0); // 안깜빡거림
	SetColor(0b1111, 0b0000); // 맵의 배경 색
	ClearBuffer(); // 화면 초기화
	return 0;
}

int Release()
{
	return 0;
}

int DrawBuffer(int DeltaTime) {
	SetColor(0b0000, 0b1001);
	setCursorPos(0, 22); // 시간 출력할 위치
	if (DeltaTime != 0){ // 0이 아닐때 출력
		printf("time : %d                 \nfps :%d                  \n", DeltaTime, 1000 / DeltaTime);
	}
	setCursorPos(35, 22);
	printf("점 수");
	setCursorPos(37, 23);
	printf("%d", score);
	return 0;
}

int DeltaTimeSum = 0;

int objectDraw(int DeltaTime) {
	ProcessInput();

	setCursorPos(0, 0);
	SetColor(0b1111, 0b1001);
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
	printf("●"); // 출력

	//snake
	int i = 0;
	while (i < GameStartSnakeLength) // i가 뱀 길이보다 작을때까지 반복
	{
		setCursorPos(snakeSkin[i].posX, snakeSkin[i].posY); // 좌표
		SetColor(0b1111, 0b0010); // 색상
		printf("O"); // 몸통
		i = i + 1; // 추가
	}
	DrawBuffer(DeltaTime);
	return 0;
}