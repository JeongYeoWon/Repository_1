// 202300403_2-1_5weeks.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <conio.h>
#include <windows.h>

// 1. 스테이지가 나와야함

//game_state == 0 일때
int print_title_screen() {
    printf("**************************************\n");
    printf("*                                    *\n");
    printf("*                                    *\n");
    printf("*            지렁이 게임             *\n");
    printf("*           (Snake  Bite)            *\n");
    printf("*                                    *\n");
    printf("*   1. 게임 시작                     *\n");
    printf("*   2. 게임 설명                     *\n");
    printf("*   3. 게임 랭킹 보기                *\n");
    printf("*   4. 게임 종료 (esc)               *\n");
    printf("**************************************\n");
    return 0;
}

int print_introduction_screep() {
    printf("**************************************\n");
    printf("* 게임 설명 화면입니다.              *\n");
    printf("* 시대가 어시댄데 메뉴얼을 만드냐. . *\n");
    printf("**************************************\n");
    printf(" 타이틀 화면으로 돌아갈까요? (Y/N)\n");
    return 0;
}

void gotoxy(int x, int y) {
    //x, y 좌표 설정
    COORD pos = { x, y };
    //커서 이동
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main()
{
    gotoxy(10, 5);
    printf("여기가 (10, 5)입니다.\n");

    int game_state = 0; //게임 시작화면 = 0, 2 = 게임 설명
    int is_game_running = 1; // 게임 시작 = 1, 0 일 경우 종료

    while (is_game_running){ // 종료할때까지 반복
        char ch = 0;

        switch (game_state) { //시작할때 버튼
        case 0: //0 누를 경우
            print_title_screen();
            ch = _getch();
            if (ch == '4' || ch == 27) {
                is_game_running = 0;
            }
            break;
        case 2: 
            print_introduction_screep();
            ch = _getch();
            if (ch == 'y') {
                game_state = 0;   
            }
            break;
        default: break;
        }
        /*if (is_game_running == 0) {
            continue;
        }*/
    /*while (is_game_running) {

        char ch = 0;

        switch (game_state) {
        case 0:
            print_title_screen();
            ch = _getch();
            
            if (ch == '2') {
                game_state = 2;
            }
            else if (ch == '4' || ch == 27) {
                is_game_running = 0;
                continue;
            }
            break;
            
        case 2:
            print_introduction_screep();
            ch = 0;
            ch = _getch();

            if (ch == 'y') {
                game_state = 0;
            }
            break;
        default: 
            break;
        }*/
        //getch
    }
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
