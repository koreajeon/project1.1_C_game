
#include <Windows.h>
#include "header.h"


void main()
{
	Default(); //�ʱ�ȭ

	//���ӽ��� ���ѷ���
	while (true)
	{
		//���� �ʴ��� �ð��� �޾ƿ´�.
		int dwTime = GetTickCount();
		//0.005�� ����
		if (dwTime + 5 < GetTickCount())
		{
			dwTime = GetTickCount();

			//����� 
			ClearScreen();

			//�÷��̾ ���� �����̰�
			Game();

			//�׷��ְ�
			PrintScreen();
		}
	}
}