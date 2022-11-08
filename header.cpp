#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include "header.h"


//미사일 구조체
struct BULLET
{
	int x; //미사일 x좌표
	int y; //미사일 y좌표
	bool fire; //미사일 발사상태
};

//미사일 갯수
BULLET playerBullet[20];

//배열로 배경범위 좌표 
char bg[25][80];

//플레이어 좌표
int playerX;
int playerY;

//적 좌표
int enemyX;
int enemyY;

int dwTime;



void Default()

{
	//랜덤함수 준비
	srand((unsigned)time(NULL));

	//플레이어 좌표위치
	playerX = 0;
	playerY = 12;

	//적 좌표 위치
	enemyX = 77;
	enemyY = 12;

	//플레이어 미사일 초기화 (미사일 발사전 준비상태)
	for (int i = 0; i < 20; i++)
	{
		playerBullet[i].x = 0;
		playerBullet[i].y = 0;
		playerBullet[i].fire = false;
	}


}

void ClearScreen()
{
	//콘솔창에 그려진 모든 것을 지움
	system("cls");


	//배열에 공백으로 넣어서 지움
	for (int y = 0; y < 25; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			bg[y][x] = ' ';
		}

	}
}

void PrintScreen() //전체적인 배경
{
	bg[24][79] = '\0';	//널 문자로 넣어서 배경 빈공간 확보
	printf("%s", bg);	//문자열로 전체 배경을 표현
}


void KeyControl()
{
	char pressKey;

	//키가 입력되면 잡아준다.
	if (_kbhit()) //키를 누르면 if문을 타고 들어온다
	{
		pressKey = _getch(); //키가 입력되어 변수에 저장

		switch (pressKey)
		{
		case 72:
			//위쪽 화살표키 아스키 코드값
			playerY--;		//Y방향 움직임 // 숫자를 감소시켜 위쪽 방향으로 
			if (playerY < 1) //1보다 작아지면 1로 만들어서 더이상 못 올라가게 
				playerY = 1;
			break;

		case 75:
			//왼쪽 화살표키 아스키 코드값
			playerX--;
			if (playerX < 0)	//if문 한줄이면 {} 생략 가능
				playerX = 0;	// X방향이 0보다 작아지지 못하게 설정 
			break;

		case 77:
			//오른쪽 방향키 아스키 코드값
			playerX++;

			if (playerX > 75)
				playerX = 75;
			break;

		case 80:
			//아래쪽 방향키 아스키 코드값
			playerY++;
			if (playerY > 23)
				playerY = 23;
			break;

		case 32:
			//스페이스바 키(아스키 코드값)가 눌리면 총알 발사
			for (int i = 0; i < 20; i++)
			{
				//미사일이 준비되어있는 상태인 경우에만 발사가능
				if (playerBullet[i].fire == false)
				{
					playerBullet[i].fire = true;
					//플레이어 앞에서 미사일을 쏘기 +5
					playerBullet[i].x = playerX + 5;
					playerBullet[i].y = playerY;
					//한 발만 발사하기
				}
			}
		}
	}
}

void BulletDraw()
{
	//미사일 전체 20개중에
	for (int i = 0; i < 20; i++)
	{
		//플레이어 미사일 날아가고 있는 상태 true
		if (playerBullet[i].fire == true)
		{
			//미사일을 그린다.
			bg[playerBullet[i].y][playerBullet[i].x - 1] = '-'; //미사일의 좌표 x축 -1하여 미사일 꼬지 달기
			bg[playerBullet[i].y][playerBullet[i].x - 0] = '>'; //미사일 머리 그리기
			bg[playerBullet[i].y - 1][playerBullet[i].x - 0] = '>';
			bg[playerBullet[i].y + 1][playerBullet[i].x - 0] = '>';

			//미사일 앞으로 +1
			playerBullet[i].x++;


			//미사일이 80을 넘어갈경우
			if (playerBullet[i].x > 79)
			{
				//미사일 준비상태로 전환
				playerBullet[i].fire = false;
			}
		}
	}
}

void PlayerDraw()
{
	//플레이어 그리기
	bg[playerY - 2][playerX + 1] = '*';
	bg[playerY - 1][playerX + 1] = '>';
	bg[playerY - 1][playerX + 0] = '-'; //c언어의 좌표는 밑으로 갈수록 커짐
	bg[playerY + 0][playerX + 1] = '>';
	bg[playerY + 0][playerX + 2] = '>';
	bg[playerY + 0][playerX + 3] = '>';
	bg[playerY + 1][playerX + 0] = '-';
	bg[playerY + 1][playerX + 1] = '>';
	bg[playerY + 2][playerX + 1] = '*';
}

void EnemyDraw()
{
	//적그리기
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
	//적은 왼쪽으로 오게 한다.
	enemyX--;

	//적이 왼쪽으로 다 올 경우
	if (enemyX < 2)
	{
		//적이 랜덤하게 y쪽 좌표를 바꿔준다.
		enemyX = 77;
		enemyY = (rand() % 20) + 2;
	}
}


//충돌처리 함수
void ClashEnemyAndBullet()
{
	//미사일 20개 전체 판별
	for (int i = 0; i < 20; i++)
	{
		//미사일이 살아있고
		if (
			playerBullet[i].fire == true)
		{
			//적과 미사일의 y값이 같고
			if (playerBullet[i].y == enemyY
				|| playerBullet[i].y == enemyY - 1
				|| playerBullet[i].y == enemyY + 1)
			{
				//플레이어 미사일 x값이 같은지 판별
				//x값은 적의 크기만큼 x-1 0 x+1
				// 3개 좌표로 잘 충돌되게 판별
				if (playerBullet[i].x >= (enemyX - 1)
					&& playerBullet[i].x <= (enemyX + 1))
				{
					//충돌되면 적Y값을 바꿔주기
					enemyX = 77;
					enemyY = (rand() % 20) + 3; // 적 출연 Y값 랜덤으로 
					playerBullet[i].fire = false;
				}
			}
		}
	}
}


void Game()
{
	//키를 입력하는 부분
	KeyControl();

	//미사일을 그려준다.
	BulletDraw();

	//플레이어를 그려준다
	PlayerDraw();

	//적의 움직임
	EnemyMove();

	//적을 그려주는 부분
	EnemyDraw();

	//미사일 적의 충돌
	ClashEnemyAndBullet();

}