#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include "Scene.h"

// �й� : 202227016 �̸� : ������, 11���� �и� �ָ� ��ħ���� �ߴµ� �� ������ �ȳ�����
// �ᱹ ���� ���߽��ϴ� , ,  �� ��ħ�̴�~
namespace MuSoeun
{
    void gotoxy(int x, int y) {
        //x, y ��ǥ ����
        COORD pos = { x,y };
        //Ŀ�� �̵�
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }
    // ���� ���� �˻��� ���Ҵµ� ��� ��ũ��Ʈ�� ��ӹ޴� �⺻ Ŭ������� �մϴ�.
    class Component //Unity MonoBehavior
    {
        virtual void Start(){}
        virtual void Update(){}
    };

    class Object : Component
    {
    public:
        int positionX;
        int positionY;
        float scale;
        float rotation;

        std::vector<Component> ComList;
        virtual void Render(char* screenBuf) {

        }
    };

    class SnakeBody : public Object {
    public:
        Scene* scene; // Scene ��ü�� ���� ������ ��� ����

        void Render(char* screenBuf) override {
            positionX = 25;
            positionY = 10;
            if (scene != nullptr) {
                int sceneWidth = scene->width; // Scene ��ü�� width �� ��������
                screenBuf[positionY * (sceneWidth + 1) + positionX] = 'X';
            }
        }
    };

    class Scene : Component
    {
    public:
        int width;
        int height;
        int state;

        int gameLoop;
        std::vector<Object*> objList;

        //screenBuf[width + (width * height)];

        char* screenBuf;

        void InitScreenBuf()
        {
            screenBuf = new char[(width + 1) * height + 5];

            for (int i = 0; i < height; i++)
            {
                screenBuf[(width + 1) + (width + 1) * i - 1] = '\n';

            }
            screenBuf[(width + 1) + (width + 1) * (height - 1) - 1] = '\0';
        }
        void ReleaseScreenBuf()
        {
            if (screenBuf != nullptr)
            {
                delete(screenBuf);
            }
        }

        void ClearScreenBuf() {
            system("cls");
        }

        void DrawScreenBuf()
        {
            std::cout << screenBuf;
        }

        void Start() override { 
            ClearScreenBuf();
            gotoxy(0, 0);
            state = 3;
            width = 50;
            height = 15;
            InitScreenBuf();
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
            DrawScreenBuf();

            gotoxy(19, 5);
            printf("������ ����");
            gotoxy(18, 6);
            printf("(Snake  Bite)\n");
            gotoxy(4, 9);
            printf("1. ���� ����\n");
            gotoxy(4, 10);
            printf("2. ���� ����\n");
            gotoxy(4, 11);
            printf("3. ���� ��ŷ ����\n");
            gotoxy(4, 12);
            printf("4. ���� ����\n");
        }

        void Update() override {
            SnakeBody* snake = new SnakeBody();
            objList.push_back(snake);
            if (_kbhit()) {
                KeyEvent(_getch()); //�Է¹��� ���� KeyEvent()�Լ� ȣ��
            }

            switch (state) {
            case 0 :
                gameLoop = 0;
                break;
            case 1:
                SceneMap();
                /*RenderObjects();*/
                break;
            case 2:
                SceneStory(); break;
            case 3:
                Start(); break;
            default:break;
            }
        }

        //void RenderObjects() {
        //    for (Object* obj : objList) {
        //        obj->Render(screenBuf); // Object�� Render �Լ��� ȣ���Ͽ� ȭ�鿡 �׸��ϴ�.
        //    }

        //    DrawScreenBuf(); // ȭ�� ���۸� ���
        //}

        ~Scene()
        {
            for (Object* obj : objList)
            {
                delete obj;
            }
        }


        void SceneStory() {
            ClearScreenBuf();
            width = 50;
            height = 10;
            InitScreenBuf();
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
            DrawScreenBuf();

            gotoxy(3, 2);
            printf("�̰��� ������ ���� �Դϴ�.\n");
            gotoxy(3, 3);
            printf("�׷��� �̰� �´����� �𸣰ھ��..");
            gotoxy(4, 7);
            printf(" Ÿ��Ʋ ȭ������ ���ư����? (Y/N)");
        }

        void SceneMap() {
            ClearScreenBuf();
            width = 50;
            height = 25;
            InitScreenBuf();
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
            DrawScreenBuf();
        }

        void KeyEvent(char KeyInput) {
            /*switch (KeyInput)
            {
            case '4':
            case 27:
                state = 0; break;
            case '1':
                state = 1; break;
            case '2':
                state = 2;
                break;
            case '3':
                state = 3; break;
            }*/

            switch (state) {
            case 0:
                if (KeyInput == '4' || KeyInput == 27)
                    gameLoop = false;
                break;
            case 2:
                if (KeyInput == 'Y' || KeyInput == 'y')
                    state = 3;
                else if (KeyInput == 'N' || KeyInput == 'n')
                    state = 2;
                break;
            case 3:
                if (KeyInput == '1')
                    state = 1;
                else if (KeyInput == '2')
                    state = 2;
                else if (KeyInput == '3')
                    state = 3;
                else if (KeyInput == '4' || KeyInput == 27)
                    state = 0;
                break;
            }

        }
    };
}

int main()
{
    MuSoeun::Scene scene;
    scene.gameLoop = true;
    scene.Start();
    while (scene.gameLoop)
    {
        scene.Update();
    }
    scene.ReleaseScreenBuf();

    return 0;
}