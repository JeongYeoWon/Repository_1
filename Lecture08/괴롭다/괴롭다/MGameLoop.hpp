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

// �й� : 202227016 �̸� : ������ 8���� ESC��� ����
namespace MuSoeun {
	void gotoxy(int x, int y) {
		//x, y ��ǥ ����
		COORD pos = { x,y };
		//Ŀ�� �̵�
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
			std::cout << ANSI_COLOR_RESET"�ʱ�ȭ��" << std::endl;
		}
		void Release() {
			gotoxy(3, 16);
			std::cout << ANSI_COLOR_RESET"���� ����" << std::endl;
		}

		void Update() {
			gotoxy(3, 18);
			std::cout << ANSI_COLOR_RESET"���� Ű�Է� ���" << std::endl;
			if (_kbhit()) {
				KeyEvent(_getch()); //�Է¹��� ���� KeyEvent()�Լ� ȣ��
			}
		}

		void Reader() {
			gotoxy(3, 17);
			std::cout << ANSI_COLOR_RESET"���� ȭ�� �׸���" << std::endl;
		}

		void Run() {

			Initialize();

			while (isGameLoopRunning) {
				Update();
				Reader();
			}
			Release();
		}

		// ��� ���� �Լ�
		void KeyEvent(char KeyInput) {
			switch (KeyInput) {
				/*�ѹ� ESC������ �Ͻ� ���� �ǰ�
				���⼭ �����⸦ �����ϸ� ��������*/
			case KEY_ESC: // escŰ�� ���� ���

				// �й� : 202227016 �̸� : ������ 8���� ESC��� ����
				// 
				// switch������ �õ� -> ���� �̻���... �̰� �³�,,?�̤�
				std::cout << ANSI_COLOR_RESET"�����Ͻðڽ��ϱ�?" << std::endl;
				std::cout << ANSI_COLOR_RESET"[��]		[�ƴϿ�]" << std::endl;
				switch (_getch()) { //�Է¹��� ����
				case KEY_LEFT: // ������ ���(�ҹ���a)
					gotoxy(0, 20);
					std::cout << ANSI_COLOR_YELLOW"[��]" << std::endl; // [��]�� Ȱ��ȭ��(�����)
					if (_getch() == KEY_ENTER) { // ���͸� ���� ��
						isGameLoopRunning = false; // ���α׷� ����
					}
					else { // �ƴ� ���
						gotoxy(0, 20);
						std::cout << ANSI_COLOR_RESET"[��]" << std::endl; // ��Ȱ��ȭ(����۾�)�� ��ȯ �� �ٽ� �ݺ�
					}
					break;
				case KEY_RIGHT: // �������� ���� ���(�ҹ���f)
					gotoxy(16, 20);
					std::cout << ANSI_COLOR_YELLOW"[�ƴϿ�]" << std::endl; // [�ƴϿ�]�� Ȱ��ȭ��(����۾�)
					if (_getch() == KEY_ENTER) { // ���͸� ���� ��
						std::cout << ANSI_COLOR_RESET"[�ƴϿ�]" << std::endl; // ��Ȱ��ȭ �� �ݺ�
					}
					else { // �ƴ� ���
						gotoxy(16, 20);
						std::cout << ANSI_COLOR_RESET"[�ƴϿ�]" << std::endl; // �Ȱ���!
					}
					break;
				}
				/*isGameLoopRunning = false;*/
				break;
			case KEY_ENTER:
				gotoxy(5, 5);
				std::cout << ANSI_COLOR_YELLOW"���� ������" << std::endl;
				break;
			case KEY_LEFT:
				gotoxy(5, 5);
				std::cout << ANSI_COLOR_RED"���� ������" << std::endl;
				break;
			case KEY_RIGHT:
				gotoxy(5, 5);
				std::cout << ANSI_COLOR_GREEN"������ ����" << std::endl;
				break;
			default:
				isGameLoopRunning = true;
				break;
			}
		}
	};

}