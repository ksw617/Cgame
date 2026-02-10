#include <stdio.h>
#include <Windows.h>

struct Obj
{		  
	int x;
	int y;
	const char* shape;

};

void SetPosition(int x, int y)
{
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main()
{
	Obj obj;
	obj.x = 10;
	obj.y = 10;
	obj.shape = "■";

	Obj obj2;
	obj2.x = 20;
	obj2.y = 20;
	obj2.shape = "●";

	while (true)
	{
		system("cls");

		//GetAsyncKeyState
		//Get : 가져오다
		//A(not)sync : 비동기된
		//Key : 키
		//State : 상태
		//VK_LEFT
		//VK : virtual key 가상키
		//LEFT : 왼쪽
		if (GetAsyncKeyState(0x25))
		{
			obj.x--;
		}

		//VK_RIGHT
		//VK : virtual key 가상키
		//RIGHT : 오른쪽
		if (GetAsyncKeyState(0x27))
		{
			obj.x++;
		}

		SetPosition(obj.x , obj.y);
		printf(obj.shape);

		SetPosition(obj2.x, obj2.y);
		printf(obj2.shape);

		Sleep(50);
	}

	return 0;
}