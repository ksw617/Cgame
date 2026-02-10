#include <stdio.h>
#include <Windows.h>

struct Obj
{		  
	int x;
	int y;
	const char* shape;

};

int main()
{
	Obj obj;
	obj.x = 10;
	obj.y = 10;
	obj.shape = "Hello world";

	while (true)
	{
		system("cls");

		COORD pos;
		pos.X = obj.x;
		pos.Y = obj.y;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

		printf(obj.shape);

		Sleep(50);
	}

	return 0;
}