#pragma once //define _IS_THIS_HEADER_INCLUED
#include <iostream>
#include <conio.h>
#include <windows.h>

#define KEY_ESC 27
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define KEY_ENTER 13

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"

namespace MuSoeun {
	void Gotoxy(int x, int y) {
		//x, y 좌표 설정
		COORD pos = { x,y };
		//커서 이동
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}
	class MGameLoop {
	public:
		MGameLoop() {};
		~MGameLoop() {};

		bool isGameLoopRunning = false;

		void Initialize() {
			isGameLoopRunning = true;
			Gotoxy(3, 15);
			std::cout <<ANSI_COLOR_RESET"초기화중" << std::endl;
		}
		void Release() {
			Gotoxy(3, 16);
			std::cout << ANSI_COLOR_RESET"게임 종료" << std::endl;
		}

		void Update() {
			Gotoxy(3, 18);
			std::cout << ANSI_COLOR_RESET"게임 키입력 대기" << std::endl;
			if (_kbhit()) {
				KeyEvent(_getch()); //입력받은 값을 KeyEvent()함수 호출
			}
		}

		void Reader() {
			Gotoxy(3, 17);
			std::cout << ANSI_COLOR_RESET"게임 화면 그리기" << std::endl;
		}

		void Run() {

			Initialize();

			while (isGameLoopRunning) {
				Update();
				Reader();
			}
			Release();
		}
		// 제어문 만든 함수
		void KeyEvent(char KeyInput) {
			switch (KeyInput) {
				/*한번 ESC누르면 일시 정지 되고
				여기서 나가기를 선택하면 나가진다*/
			case KEY_ESC:
				
				std::cout << ANSI_COLOR_RESET"나가시겠습니까?" << std::endl;
				switch () {
				case 'y':
					isGameLoopRunning = false; break;
				case 'n':
					break;
				default:break;
				}
				break;
			case KEY_ENTER:
				Gotoxy(5, 5);
				std::cout << ANSI_COLOR_YELLOW"엔터 눌림　" << std::endl;
				break;
			case KEY_LEFT:
				Gotoxy(5, 5);
				std::cout << ANSI_COLOR_RED"왼쪽 눌림　" << std::endl;
				break;
			case KEY_RIGHT:
				Gotoxy(5, 5);
				std::cout << ANSI_COLOR_GREEN"오른쪽 눌림" << std::endl;
				break;
			default:
				isGameLoopRunning = true;
				break;
			}
		}
	};

}