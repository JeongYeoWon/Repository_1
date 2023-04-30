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

// 학번 : 202227016 이름 : 정여원 8주차 ESC기능 구현
namespace MuSoeun {
	void gotoxy(int x, int y) {
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
			gotoxy(3, 15);
			std::cout << ANSI_COLOR_RESET"초기화중" << std::endl;
		}
		void Release() {
			gotoxy(3, 16);
			std::cout << ANSI_COLOR_RESET"게임 종료" << std::endl;
		}

		void Update() {
			gotoxy(3, 18);
			std::cout << ANSI_COLOR_RESET"게임 키입력 대기" << std::endl;
			if (_kbhit()) {
				KeyEvent(_getch()); //입력받은 값을 KeyEvent()함수 호출
			}
		}

		void Reader() {
			gotoxy(3, 17);
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
			case KEY_ESC: // esc키를 누를 경우

				// 학번 : 202227016 이름 : 정여원 8주차 ESC기능 구현
				// 
				// switch문으로 시도 -> 뭔가 이상함... 이게 맞나,,?ㅜㅜ
				std::cout << ANSI_COLOR_RESET"종료하시겠습니까?" << std::endl;
				std::cout << ANSI_COLOR_RESET"[예]		[아니오]" << std::endl;
				switch (_getch()) { //입력받은 값이
				case KEY_LEFT: // 왼쪽일 경우(소문자a)
					gotoxy(0, 20);
					std::cout << ANSI_COLOR_YELLOW"[예]" << std::endl; // [예]를 활성화함(노란색)
					if (_getch() == KEY_ENTER) { // 엔터를 누를 시
						isGameLoopRunning = false; // 프로그램 종료
					}
					else { // 아닌 경우
						gotoxy(0, 20);
						std::cout << ANSI_COLOR_RESET"[예]" << std::endl; // 비활성화(흰색글씨)로 전환 후 다시 반복
					}
					break;
				case KEY_RIGHT: // 오른쪽을 누를 경우(소문자f)
					gotoxy(16, 20);
					std::cout << ANSI_COLOR_YELLOW"[아니오]" << std::endl; // [아니오]를 활성화함(노란글씨)
					if (_getch() == KEY_ENTER) { // 엔터를 누를 시
						std::cout << ANSI_COLOR_RESET"[아니오]" << std::endl; // 비활성화 후 반복
					}
					else { // 아닐 경우
						gotoxy(16, 20);
						std::cout << ANSI_COLOR_RESET"[아니오]" << std::endl; // 똑같다!
					}
					break;
				}
				/*isGameLoopRunning = false;*/
				break;
			case KEY_ENTER:
				gotoxy(5, 5);
				std::cout << ANSI_COLOR_YELLOW"엔터 눌림　" << std::endl;
				break;
			case KEY_LEFT:
				gotoxy(5, 5);
				std::cout << ANSI_COLOR_RED"왼쪽 눌림　" << std::endl;
				break;
			case KEY_RIGHT:
				gotoxy(5, 5);
				std::cout << ANSI_COLOR_GREEN"오른쪽 눌림" << std::endl;
				break;
			default:
				isGameLoopRunning = true;
				break;
			}
		}
	};

}