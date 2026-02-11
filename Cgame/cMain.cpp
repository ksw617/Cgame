#include <stdio.h>
#include <Windows.h>

enum Color
{
	Black,
	DarkBlue,
	DarkGreen,
	DarkCyan,
	DarkRed,
	DarkMagenta,
	DarkYellow,
	Gray,
	DarkGray,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Yellow,
	White,
};

struct Obj
{		  
	int x;
	int y;
	const char* shape;

};

void SetPosition(int x, int y);
void SetTextColor(Color color);
void MakeInvisible();


int main()
{

	MakeInvisible();

	Obj obj;
	obj.x = 10;
	obj.y = 10;
	obj.shape = "бс";

	Obj obj2;
	obj2.x = 20;
	obj2.y = 20;
	obj2.shape = "б▄";

	while (true)
	{
		system("cls");
		if (GetAsyncKeyState(0x25))
		{
			obj.x--;
		}
		if (GetAsyncKeyState(0x27))
		{
			obj.x++;
		}

		SetPosition(obj.x , obj.y);
		SetTextColor(Blue);
		printf(obj.shape);

		SetPosition(obj2.x, obj2.y);
		SetTextColor(Yellow);
		printf(obj2.shape);

		Sleep(50);
	}

	return 0;
} 

void SetPosition(int x, int y)
{
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetTextColor(Color color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void MakeInvisible()
{
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}