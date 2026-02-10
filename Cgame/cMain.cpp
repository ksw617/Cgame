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
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main()
{
	Obj obj;
	obj.x = 10;
	obj.y = 10;
	obj.shape = "Hello world";

	Obj obj2;
	obj2.x = 20;
	obj2.y = 20;
	obj2.shape = "Hello world2";

	while (true)
	{
		system("cls");

		SetPosition(obj.x , obj.y);
		printf(obj.shape);

		SetPosition(obj2.x, obj2.y);
		printf(obj2.shape);

		Sleep(50);
	}

	return 0;
}