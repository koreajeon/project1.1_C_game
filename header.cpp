#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include "header.h"


//�̻��� ����ü
struct BULLET
{
	int x; //�̻��� x��ǥ
	int y; //�̻��� y��ǥ
	bool fire; //�̻��� �߻����
};

//�̻��� ����
BULLET playerBullet[20];

//�迭�� ������ ��ǥ 
char bg[25][80];

//�÷��̾� ��ǥ
int playerX;
int playerY;

//�� ��ǥ
int enemyX;
int enemyY;

int dwTime;



void Default()

{
	//�����Լ� �غ�
	srand((unsigned)time(NULL));

	//�÷��̾� ��ǥ��ġ
	playerX = 0;
	playerY = 12;

	//�� ��ǥ ��ġ
	enemyX = 77;
	enemyY = 12;

	//�÷��̾� �̻��� �ʱ�ȭ (�̻��� �߻��� �غ����)
	for (int i = 0; i < 20; i++)
	{
		playerBullet[i].x = 0;
		playerBullet[i].y = 0;
		playerBullet[i].fire = false;
	}


}

void ClearScreen()
{
	//�ܼ�â�� �׷��� ��� ���� ����
	system("cls");


	//�迭�� �������� �־ ����
	for (int y = 0; y < 25; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			bg[y][x] = ' ';
		}

	}
}

void PrintScreen() //��ü���� ���
{
	bg[24][79] = '\0';	//�� ���ڷ� �־ ��� ����� Ȯ��
	printf("%s", bg);	//���ڿ��� ��ü ����� ǥ��
}


void KeyControl()
{
	char pressKey;

	//Ű�� �ԷµǸ� ����ش�.
	if (_kbhit()) //Ű�� ������ if���� Ÿ�� ���´�
	{
		pressKey = _getch(); //Ű�� �ԷµǾ� ������ ����

		switch (pressKey)
		{
		case 72:
			//���� ȭ��ǥŰ �ƽ�Ű �ڵ尪
			playerY--;		//Y���� ������ // ���ڸ� ���ҽ��� ���� �������� 
			if (playerY < 1) //1���� �۾����� 1�� ���� ���̻� �� �ö󰡰� 
				playerY = 1;
			break;

		case 75:
			//���� ȭ��ǥŰ �ƽ�Ű �ڵ尪
			playerX--;
			if (playerX < 0)	//if�� �����̸� {} ���� ����
				playerX = 0;	// X������ 0���� �۾����� ���ϰ� ���� 
			break;

		case 77:
			//������ ����Ű �ƽ�Ű �ڵ尪
			playerX++;

			if (playerX > 75)
				playerX = 75;
			break;

		case 80:
			//�Ʒ��� ����Ű �ƽ�Ű �ڵ尪
			playerY++;
			if (playerY > 23)
				playerY = 23;
			break;

		case 32:
			//�����̽��� Ű(�ƽ�Ű �ڵ尪)�� ������ �Ѿ� �߻�
			for (int i = 0; i < 20; i++)
			{
				//�̻����� �غ�Ǿ��ִ� ������ ��쿡�� �߻簡��
				if (playerBullet[i].fire == false)
				{
					playerBullet[i].fire = true;
					//�÷��̾� �տ��� �̻����� ��� +5
					playerBullet[i].x = playerX + 5;
					playerBullet[i].y = playerY;
					//�� �߸� �߻��ϱ�
				}
			}
		}
	}
}

void BulletDraw()
{
	//�̻��� ��ü 20���߿�
	for (int i = 0; i < 20; i++)
	{
		//�÷��̾� �̻��� ���ư��� �ִ� ���� true
		if (playerBullet[i].fire == true)
		{
			//�̻����� �׸���.
			bg[playerBullet[i].y][playerBullet[i].x - 1] = '-'; //�̻����� ��ǥ x�� -1�Ͽ� �̻��� ���� �ޱ�
			bg[playerBullet[i].y][playerBullet[i].x - 0] = '>'; //�̻��� �Ӹ� �׸���
			bg[playerBullet[i].y - 1][playerBullet[i].x - 0] = '>';
			bg[playerBullet[i].y + 1][playerBullet[i].x - 0] = '>';

			//�̻��� ������ +1
			playerBullet[i].x++;


			//�̻����� 80�� �Ѿ���
			if (playerBullet[i].x > 79)
			{
				//�̻��� �غ���·� ��ȯ
				playerBullet[i].fire = false;
			}
		}
	}
}

void PlayerDraw()
{
	//�÷��̾� �׸���
	bg[playerY - 2][playerX + 1] = '*';
	bg[playerY - 1][playerX + 1] = '>';
	bg[playerY - 1][playerX + 0] = '-'; //c����� ��ǥ�� ������ ������ Ŀ��
	bg[playerY + 0][playerX + 1] = '>';
	bg[playerY + 0][playerX + 2] = '>';
	bg[playerY + 0][playerX + 3] = '>';
	bg[playerY + 1][playerX + 0] = '-';
	bg[playerY + 1][playerX + 1] = '>';
	bg[playerY + 2][playerX + 1] = '*';
}

void EnemyDraw()
{
	//���׸���
	bg[enemyY - 3][enemyX - 2] = '<';
	bg[enemyY - 3][enemyX - 1] = '<';
	bg[enemyY - 3][enemyX + 0] = '<';
	bg[enemyY - 3][enemyX + 1] = '<';
	bg[enemyY - 3][enemyX + 2] = '|';

	bg[enemyY - 2][enemyX - 2] = '<';
	bg[enemyY - 2][enemyX - 1] = '<';
	bg[enemyY - 2][enemyX + 0] = '<';
	bg[enemyY - 2][enemyX + 1] = '*';
	bg[enemyY - 2][enemyX + 2] = '*';

	bg[enemyY - 1][enemyX - 2] = '<';
	bg[enemyY - 1][enemyX - 1] = '-';
	bg[enemyY - 1][enemyX + 0] = 'O';
	bg[enemyY - 1][enemyX + 1] = '-';
	bg[enemyY - 1][enemyX + 2] = '>';

	bg[enemyY][enemyX - 9] = '<';
	bg[enemyY][enemyX - 8] = '<';
	bg[enemyY][enemyX - 7] = '<';
	bg[enemyY][enemyX - 6] = '|';
	bg[enemyY][enemyX - 5] = '|';
	bg[enemyY][enemyX - 4] = '|';
	bg[enemyY][enemyX - 3] = '+';

	bg[enemyY][enemyX - 2] = '<';
	bg[enemyY][enemyX - 1] = '-';
	bg[enemyY][enemyX + 0] = 'O';
	bg[enemyY][enemyX + 1] = '-';
	bg[enemyY][enemyX + 2] = ':';
	bg[enemyY][enemyX + 3] = ']';
	bg[enemyY][enemyX + 4] = '>';

	bg[enemyY + 1][enemyX - 2] = '<';
	bg[enemyY + 1][enemyX - 1] = '-';
	bg[enemyY + 1][enemyX + 0] = 'O';
	bg[enemyY + 1][enemyX + 1] = '-';
	bg[enemyY + 1][enemyX + 2] = '>';

	bg[enemyY + 2][enemyX - 2] = '<';
	bg[enemyY + 2][enemyX - 1] = '<';
	bg[enemyY + 2][enemyX + 0] = '<';
	bg[enemyY + 2][enemyX + 1] = '*';
	bg[enemyY + 2][enemyX + 2] = '*';

	bg[enemyY + 3][enemyX - 2] = '<';
	bg[enemyY + 3][enemyX - 1] = '<';
	bg[enemyY + 3][enemyX + 0] = '<';
	bg[enemyY + 3][enemyX + 1] = '<';
	bg[enemyY + 3][enemyX + 2] = '|';
}

void EnemyMove()
{
	//���� �������� ���� �Ѵ�.
	enemyX--;

	//���� �������� �� �� ���
	if (enemyX < 2)
	{
		//���� �����ϰ� y�� ��ǥ�� �ٲ��ش�.
		enemyX = 77;
		enemyY = (rand() % 20) + 2;
	}
}


//�浹ó�� �Լ�
void ClashEnemyAndBullet()
{
	//�̻��� 20�� ��ü �Ǻ�
	for (int i = 0; i < 20; i++)
	{
		//�̻����� ����ְ�
		if (
			playerBullet[i].fire == true)
		{
			//���� �̻����� y���� ����
			if (playerBullet[i].y == enemyY
				|| playerBullet[i].y == enemyY - 1
				|| playerBullet[i].y == enemyY + 1)
			{
				//�÷��̾� �̻��� x���� ������ �Ǻ�
				//x���� ���� ũ�⸸ŭ x-1 0 x+1
				// 3�� ��ǥ�� �� �浹�ǰ� �Ǻ�
				if (playerBullet[i].x >= (enemyX - 1)
					&& playerBullet[i].x <= (enemyX + 1))
				{
					//�浹�Ǹ� ��Y���� �ٲ��ֱ�
					enemyX = 77;
					enemyY = (rand() % 20) + 3; // �� �⿬ Y�� �������� 
					playerBullet[i].fire = false;
				}
			}
		}
	}
}


void Game()
{
	//Ű�� �Է��ϴ� �κ�
	KeyControl();

	//�̻����� �׷��ش�.
	BulletDraw();

	//�÷��̾ �׷��ش�
	PlayerDraw();

	//���� ������
	EnemyMove();

	//���� �׷��ִ� �κ�
	EnemyDraw();

	//�̻��� ���� �浹
	ClashEnemyAndBullet();

}