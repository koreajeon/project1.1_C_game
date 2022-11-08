
#include <Windows.h>
#include "header.h"


void main()
{
	Default(); //초기화

	//게임실행 무한루프
	while (true)
	{
		//현재 초단위 시간을 받아온다.
		int dwTime = GetTickCount();
		//0.005초 지연
		if (dwTime + 5 < GetTickCount())
		{
			dwTime = GetTickCount();

			//지우고 
			ClearScreen();

			//플레이어나 적이 움직이고
			Game();

			//그려주고
			PrintScreen();
		}
	}
}