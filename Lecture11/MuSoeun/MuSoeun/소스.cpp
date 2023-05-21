#include <iostream>
#include <windows.h>
#include <vector>
#include <conio.h>

// �й� : 202227016 �̸� : ������, 11����
namespace MuSoeun // �׷��� ����Ƽ ������ �������� ���߾��
{
    void gotoxy(int x, int y) {
        //x, y ��ǥ ����
        COORD pos = { x,y };
        //Ŀ�� �̵�
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }

    class Object // �����̸� ������
    {
    public:
        int positionX;
        int positionY;
        float scale;
        float rotation;

        virtual void Render(char* screenBuf) // �����̸� �׷���
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

    class Scene // ���� ȭ��
    {
    public:
        int width; // ȭ�� ����
        int height; // ȭ�� ����
        std::vector<Object> objList; // ������ �����ϴ� �ǰ�??

        //screenBuf[width + (width * height)];

        char* screenBuf; // ȭ�� ǥ��

        void InitScreenBuf(int stage) // screenBuf �ʱ�ȭ
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

            screenBuf = new char[(width + 1) * height + 5]; // width�� height ���� ���� ����Ͽ� �����Ҵ�?�ϴ� �� ��,,�ƿ�? �ƴ�,,��?
            
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

            /*for (int i = 0; i < height; i++) // i�� ȭ�� ���̺��� ���������� �ݺ�
            {
                screenBuf[(width + 1) + (width + 1) * i - 1] = '\n';

            }
            screenBuf[(width + 1) + (width + 1) * (height - 1) - 1] = '\0';*/
        }

        void Title() { // stage 0
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

        void stage2() {
            DrawScreenBuf(); // ���۸� ����մϴ�.

            gotoxy(19, 5);
            printf("help");

        }
        
        void ReleaseScreenBuf() // �޸� ����
        {
            if (screenBuf != nullptr) // nullptr�� ���� ���� �˻��غôµ� null�� ���� 0�� �ִ� ������ �ν��ؼ� �������� screenBuf�� null�� ������ �����Ҵ��� �ȵǼ��ΰ�,,,? ��...�Ҽ���
            {
                delete(screenBuf); // �ƹ�ư �޸𸮸� ������
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
            std::cout << screenBuf; // screenBuf�� ���
        }
    };

    

    class Component //Unity MonoBehavior
    {
        void Start(); // Ȱ��ȭ �ؿ�
        void Update() { // �����

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
                ch = _getch(); // �Է¹ޱ�
            }
            printf("��ġ�� ������ �ּ���! => ");
            if (scanf_s("%d%d", &n1, &n2) != 2) {
                while (getchar() != '\n');
            }
            scene.ClearScreenBuf();
            scene.InitScreenBuf(1);
            scene.DrawScreenBuf();
            if (ch == '4' || ch == 27) {
                gameLoop = false;
                break; // ���� ����
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
            printf("��ġ�� ������ �ּ���! => ");
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