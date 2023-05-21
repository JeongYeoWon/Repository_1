#include <iostream>
#include <windows.h>
#include <vector>
#include <conio.h>

// 학번 : 202227016 이름 : 정여원, 11주차
namespace MuSoeun // 그런데 유니티 구조를 이해하지 못했어요
{
    void gotoxy(int x, int y) {
        //x, y 좌표 설정
        COORD pos = { x,y };
        //커서 이동
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }

    class Object // 지렁이를 만들어요
    {
    public:
        int positionX;
        int positionY;
        float scale;
        float rotation;

        virtual void Render(char* screenBuf) // 지렁이를 그려요
        {
        }
    };

    class SnakBody : public Object
    {
    public:
        SnakBody(int posX, int posY, float sc, float rot)
        {
            positionX = posX;
            positionY = posY;
            scale = sc;
            rotation = rot;
        }

        void Render(char* screenBuf) override
        {

        }
    };

    class Scene // 게임 화면
    {
    public:
        int width; // 화면 넓이
        int height; // 화면 높이
        std::vector<Object> objList; // 지렁이 저장하는 건가??

        //screenBuf[width + (width * height)];

        char* screenBuf; // 화면 표현

        void InitScreenBuf(int stage) // screenBuf 초기화
        {
            if (stage == 0) {
                gotoxy(0, 0);
                width = 50;
                height = 15;
            }
            else if (stage == 1) {
                gotoxy(0, 0);
                width = 50;
                height = 25;
            }
            else if (stage == 2) {
                gotoxy(0, 0);
                width = 50;
                height = 10;
            }

            screenBuf = new char[(width + 1) * height + 5]; // width와 height 값에 따라 계산하여 동적할당?하는 것 같,,아요? 아닌,,가?
            
            for (int i = 0; i < height; i++)
            {
                if (i == 0 || i == height - 1)
                {
                    for (int j = 0; j < width; j++)
                    {
                        screenBuf[j + (width + 1) * i] = '*';
                    }
                }
                else
                {
                    screenBuf[(width + 1) * i] = '*';
                    for (int j = 1; j < width - 1; j++)
                    {
                        screenBuf[j + (width + 1) * i] = ' ';
                    }
                    screenBuf[(width + 1) * i + width - 1] = '*';
                }
                screenBuf[(width + 1) * i + width] = '\n';
            }
            screenBuf[(width + 1) * height] = '\0';

            /*for (int i = 0; i < height; i++) // i가 화면 높이보다 작을때까지 반복
            {
                screenBuf[(width + 1) + (width + 1) * i - 1] = '\n';

            }
            screenBuf[(width + 1) + (width + 1) * (height - 1) - 1] = '\0';*/
        }

        void Title() { // stage 0
            gotoxy(19, 5);
            printf("지렁이 게임");
            gotoxy(18, 6);
            printf("(Snake  Bite)\n");
            gotoxy(4, 9);
            printf("1. 게임 시작\n");
            gotoxy(4, 10);
            printf("2. 게임 설명\n");
            gotoxy(4, 11);
            printf("3. 게임 랭킹 보기\n");
            gotoxy(4, 12);
            printf("4. 게임 종료\n");
        }

        void stage2() {
            DrawScreenBuf(); // 버퍼를 출력합니다.

            gotoxy(19, 5);
            printf("help");

        }
        
        void ReleaseScreenBuf() // 메모리 해제
        {
            if (screenBuf != nullptr) // nullptr가 뭔지 몰라서 검색해봤는데 null은 정수 0을 넣는 것으로 인식해서 포인터인 screenBuf에 null을 넣으면 동적할당이 안되서인가,,,? 아...닐수도
            {
                delete(screenBuf); // 아무튼 메모리를 해제함
            }
        }

        void ClearScreenBuf()
        {
            /*for (int i = 0; i < height; i++)
            {
                if (i == 0 || i == height - 1)
                {
                    for (int j = 0; j < width; j++)
                    {
                        screenBuf[j + (width + 1) * i] = ' ';
                    }
                }
                else
                {
                    screenBuf[(width + 1) * i] = ' ';
                    for (int j = 1; j < width - 1; j++)
                    {
                        screenBuf[j + (width + 1) * i] = ' ';
                    }
                    screenBuf[(width + 1) * i + width - 1] = ' ';
                }
                screenBuf[(width + 1) * i + width] = '\n';
            }
            screenBuf[(width + 1) * height] = '\0';*/
            system("cls");
        }

        void DrawScreenBuf()
        {
            std::cout << screenBuf; // screenBuf를 출력
        }
    };

    

    class Component //Unity MonoBehavior
    {
        void Start(); // 활성화 해요
        void Update() { // 살려줘

        }
    };
}

int main()
{
    /*bool gameLoop = true;
    int n1, n2;
    MuSoeun::Scene scene;

    scene.InitScreenBuf(0);

    while (gameLoop)
    {
        char ch = 0;
        ch = _getch();
        switch (ch) {
        case '1': {
            while (ch != '1' && ch != '2' && ch != '4' && ch != 27) {
                ch = _getch(); // 입력받기
            }
            printf("위치를 설정해 주세요! => ");
            if (scanf_s("%d%d", &n1, &n2) != 2) {
                while (getchar() != '\n');
            }
            scene.ClearScreenBuf();
            scene.InitScreenBuf(1);
            scene.DrawScreenBuf();
            if (ch == '4' || ch == 27) {
                gameLoop = false;
                break; // 루프 종료
            }
            break;
        }
        case '2': {
            scene.ClearScreenBuf();
            scene.InitScreenBuf(2);
            scene.DrawScreenBuf();
            scene.stage2();
            break;
        }
        default:
            break;
        }
        scene.ReleaseScreenBuf();
    }*/

    bool gameLoop = true;
    int state = 0, n1, n2;
    MuSoeun::Scene scene;

    scene.InitScreenBuf(0);

    while (gameLoop)
    {
        if (state == 0) {
            scene.DrawScreenBuf();
            scene.Title();
        }

        char ch = _getch();

        switch (ch) {
        case '1':
            state = 1;
            printf("위치를 설정해 주세요! => ");
            if (scanf_s("%d%d", &n1, &n2) != 2) {
                while (getchar() != '\n');
            }
            else {
                getchar();
            }
            scene.ClearScreenBuf();
            scene.InitScreenBuf(1);
            scene.DrawScreenBuf();
            break;
        case '2':
            scene.ClearScreenBuf();
            scene.InitScreenBuf(2);
            /*scene.DrawScreenBuf();*/
            scene.stage2();
            break;
        case '4':
        case 27:
            gameLoop = false;
            break;
        default:
            break;
        }
    }

    scene.ReleaseScreenBuf();
    return 0;
}