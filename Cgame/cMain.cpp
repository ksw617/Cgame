#pragma region Header
#include <stdio.h>
#include <Windows.h>
#pragma endregion

#pragma region Enum
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

#pragma endregion

#pragma region ±¸Á¶Ã¼

struct Obj
{
	int x;
	int y;
	const char* shape;

};
#pragma endregion

#pragma region WIN_API
void SetPosition(int x, int y);
void SetTextColor(Color color);
void MakeInvisible();
#pragma endregion

#pragma region GAME

Obj obj;
Obj obj2;

void Init();
void Input();
void Render();

#pragma endregion


int main()
{

	MakeInvisible();
	Init();

	while (true)
	{
		system("cls");

		Input();
		Render();

		Sleep(50);
	}

	return 0;
} 

#pragma region WIN_API
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

#pragma endregion

#pragma region GAME
void Init()
{

	obj.x = 10;
	obj.y = 10;
	obj.shape = "¡á";

	
	obj2.x = 20;
	obj2.y = 20;
	obj2.shape = "¡Ü";
}
void Input()
{
	if (GetAsyncKeyState(0x25))
	{
		obj.x--;
	}
	if (GetAsyncKeyState(0x27))
	{
		obj.x++;
	}
}
void Render()
{
	SetPosition(obj.x, obj.y);
	SetTextColor(Blue);
	printf(obj.shape);

	SetPosition(obj2.x, obj2.y);
	SetTextColor(Yellow);
	printf(obj2.shape);
}
#pragma endregion

