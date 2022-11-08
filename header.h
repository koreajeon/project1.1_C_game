#pragma once


//함수설계
void Default(); // 초기화
void ClearScreen(); //화면을 지운다 
void Game();    //게임전체를 관리하는 함수
void PrintScreen();	//화면을 그려주는 함수
void KeyControl();	//키관련 함수
void BulletDraw();	//미사일을 그려주는 함수
void PlayerDraw();	//플레이어 그리는 함수
void EnemyDraw();	//적 그리는 함수
void EnemyMove();	//적 움직이는 함수
void ClashEnemyAndBullet();	//충돌처리 함수


