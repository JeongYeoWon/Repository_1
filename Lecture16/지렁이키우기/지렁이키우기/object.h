#pragma once

int GameStartSnakeLength; // �� ���� ����
int ActiveSnakeNum; // Ȱ��ȭ�� �� ���� ����
int score;

#define MAX_SNAKE_LENGTH 1400 // ���,, ¯���
struct GameObject // ���� ������Ʈ ��ǥ�� Ȱ��ȭ
{
	int posX;
	int posY;
	int isActive;
};

//0���� �Ӹ�
struct GameObject snakeSkin[MAX_SNAKE_LENGTH]; // �� ����
struct GameObject apple; // ���

void InitApple();
void MoveSnake();
int objectInitialize();
void ProcessInput();