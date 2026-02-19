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


#define HEIGHT 3
#define WIDTH 4

struct Rect
{
	short left;
	short right;
	short top;
	short bottom;
};

struct Obj
{
	int x;
	int y;
	Rect rect;
	Color color;
	const char* shape[3];

};


void HideCursor();
void SetTextColor(Color color);
void SetPosition(int x, int y);

void SetRect(Obj& obj);

bool IsCollision(int aX, int aY, int bX, int bY);
bool IsCollision(Rect rect, int x, int y);
bool IsCollision(Rect a, Rect b);


int main()
{

	Obj a;
	a.x = 10;
	a.y = 10;
	SetRect(a);
	a.color = Blue;
	a.shape[0] = "¡á¡á¡á¡á";
	a.shape[1] = "¡á¡á¡á¡á";
	a.shape[2] = "¡á¡á¡á¡á";
	
	Obj b;
	b.x = rand() % 35;
	b.y = rand() % 35;
	SetRect(b);
	b.color = Red;
	b.shape[0] = "¡á¡á¡á¡á";
	b.shape[1] = "¡á¡á¡á¡á";
	b.shape[2] = "¡á¡á¡á¡á";

	HideCursor();

	while (true)
	{
		system("cls");

		if (GetAsyncKeyState(VK_LEFT))
		{
			a.x--;
		}

		if (GetAsyncKeyState(VK_RIGHT))
		{
			a.x++;
		}
		if (GetAsyncKeyState(VK_UP))
		{
			a.y--;
		}

		if (GetAsyncKeyState(VK_DOWN))
		{
			a.y++;
		}
		SetRect(a);
		SetRect(b);

		if (IsCollision(a.rect, b.rect))
		{
			b.x = rand() % 35;
			b.y = rand() % 35;
		}

		for (int i = 0; i < 3; i++)
		{

			SetTextColor(a.color);
			SetPosition(a.x, a.y + i);
			printf(a.shape[i]);

			SetTextColor(b.color);
			SetPosition(b.x, b.y + i);
			printf(b.shape[i]);
		}

	

		Sleep(50);
	}

	return 0;
}

bool IsCollision(int aX, int aY, int bX, int bY)
{
	if (aX == bX && aY == bY)
		return true;

	return false;
}

bool IsCollision(Rect rect, int x, int y)
{
	if (rect.left <= x && x < rect.right &&
		rect.top <= y && y < rect.bottom)
		return true;

	return false;
}



bool IsCollision(Rect a, Rect b)
{
	if (a.left < b.right && b.left < a.right &&
		a.top < b.bottom && b.top < a.bottom)
		return true;

	return false;
}

void SetPosition(int x, int y)
{
	COORD pos;
	pos.X = x * 2;
	pos.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetRect(Obj& obj)
{
	obj.rect.left = obj.x;
	obj.rect.right = obj.x + WIDTH;
	obj.rect.top = obj.y;
	obj.rect.bottom = obj.y + HEIGHT;
}



void SetTextColor(Color color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}