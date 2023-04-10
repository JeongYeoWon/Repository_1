// 202300403_2-1_5weeks.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

// 202227016 2-1 정여원 살려주세요 교수님 전 정말 모르겠어요.

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

void gotoxy(int x, int y) { // 좌표 설정
    //x, y 좌표 설정
    COORD pos = { x, y };
    //커서 이동
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int print_stage(int sw, int sh) { // 입력받은 숫자로 좌표 지정 및 크기 조절
    //printf("*"); //스테이지 만들라는 말을 이해하지 못했어요... 아이고 난..
    // 헐 스테이지 만들라는 거 이해함 아!!!! 난 바보 멍청이였던거임 좌표설정해서 만들라는게 상자 크기 정하는 거였구나 ㅋ,
    // 난 멍청이다 아직 이해 못했다.
    /*gotoxy(sw, sh);
    printf("**************************************\n");
    for (int i = 0; i < 10; i++) {
        gotoxy(sw, sh + i + 1);
        printf("*                                    *");
    }
    gotoxy(sw, sh + 11);
    printf("**************************************\n");*/

    // * 과제 3.1사이즈/ 스테이지만들기(5.5)일 경우 아무튼 교수님이 정리해주신다고했으니 걍 기절하고있어야겠다 전 틀렸어요...
    /* if (map == malloc) { //
        map = (char**)malloc(sizeof(char*) * stage)
                for (int i = 0; i < sw; i++) {
                map[i] = new char[sw];
            }
    } */

    return 0;
}

int main()
{

    // GameState
    // 0 : 게임 종료
    // 1 : 시작 화면
    // 2 : 게임 설명
    // 3 : 게임 랭킹

    /*char ch = 0;*/
    int game_state = 1;
    int sub_title_state = 1;

    while (game_state) {
        switch (game_state) {
        case 0:
            game_state = 0;
            break;
        case 1:
            print_title_screen();
            sub_title_state = 1;
            while (sub_title_state) {
                char ch = _getch();
                switch (ch) {
                case 0:
                    game_state = 0; break;
                case 1:
                    game_state = 1; break;
                case 2:
                    game_state = 2; break;
                case 3:
                    game_state = 3; break;
                default: break;
                }
            }
            break;
        case 2: break;
        case 3: break;
        }
    }

    /* // 내가 했던 것
    gotoxy(10, 5);
    printf("여기가 (10, 5)입니다.\n");

    int game_state = 0; // 게임 시작화면 = 0, 2 = 게임 설명
    int is_game_running = 1; // 게임 시작 = 1, 0 일 경우 종료
    int n1 = 0, n2 = 0;
    bool firststate = false;
    bool secondstate = false;
    bool stage = false;
     
    while(is_game_running){
        char ch = 0;

        switch (game_state) { // 시작할때 버튼
        case 0: // 0 누를 경우
            if (!firststate) { // 만약 firststate가 false일때 true를 반환함
                print_title_screen(); //함수 호출
                while (ch != '1' && ch != '2' && ch != '4' && ch != 27) { // 2나4나 ESC를 누르지 않았을 때까지 반복
                    ch = _getch(); // 입력받기
                }
                firststate = true; // 반복 제어
            }
            if (ch == '1') { // 1누를 경우
                stage = false;
                game_state = 1;
            }
            if (ch == '2') {
                secondstate = false;
                game_state = 2;
            }
            if (ch == '4' || ch == 27) {
                is_game_running = 0;
            }
            break;
        case 1:
            if (!stage) {
                ch = 0;
                printf("크기를 설정해 주세요! => ");
                if (scanf_s("%d%d", &n1, &n2) != 2) { // scanf에서 입력을 받아왔을 때 값 2개를 못 받아오면
                    while (getchar() != '\n'); //엔터 누르기 전까지 반복
                    break; //if문 빠져나옴
                }
                print_stage(n1, n2);

                while (ch != 27) {
                    ch = _getch();
                }
                stage = true;
            }
            if (ch == 27) {
                is_game_running = 0;
            }
            break;
        case 2:
            if (!secondstate) {
                print_introduction_screep();
                ch = 0;
                while (ch != 'y' && ch != 27) {
                    ch = _getch();
                }
                secondstate = true;
            }
            /*print_introduction_screep();
            ch = _getch();
            switch (ch) {
            case 'y': 
                firststate = false;
                game_state = 0; break;
            case 'n': break;
            default: break;
            } //주석 달아야함

            if (ch == 'y' || ch == 'Y') {
                firststate = false;
                game_state = 0;
            }
            if (ch == 'n' || ch == 'N') {
                game_state = 2;
            }
            if (ch == 27) {
                is_game_running = 0;
            }
            break;
        default: break;
        }
            //getch
    }*/
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
