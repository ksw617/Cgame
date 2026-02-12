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

void HideCursor();
void SetTextColor(Color color);
void SetPosition(int x, int y);

struct Obj
{
	bool act;
	int x;
	int y;
	Color color;
	const char* shape;
};

#define BulletCount 10

int main()
{
	Obj player;
	player.x = 10;
	player.y = 10;
	player.color = Yellow;
	player.shape = "бс";

	Obj bullets[BulletCount];
	for (int i = 0; i < BulletCount; i++)
	{
		bullets[i].act = false;
		bullets[i].x = i;
		bullets[i].y = 0;
		bullets[i].color = Blue;
		bullets[i].shape = "б▄";
	}

	
	
	
	HideCursor();

	while (true)
	{
		system("cls");

		if (GetAsyncKeyState(VK_LEFT))
		{
			player.x--;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			player.x++;
		}
		if (GetAsyncKeyState(VK_UP))
		{			   
			player.y--;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			player.y++;
		}
		if (GetAsyncKeyState(VK_SPACE))
		{
		

			for (int i = 0; i < BulletCount; i++)
			{
				if (bullets[i].act == false)
				{
					bullets[i].x = player.x;
					bullets[i].y = player.y;
					bullets[i].color = Red;
					bullets[i].act = true;
					break;
				}
			
			}
		}


		SetTextColor(player.color);
		SetPosition(player.x, player.y);
		printf(player.shape);


		for (int i = 0; i < BulletCount; i++)
		{
			if (bullets[i].act)
			{
				bullets[i].x++;
				if (bullets[i].x >= 40)
				{
					bullets[i].x = i;
					bullets[i].y = 0;
					bullets[i].color = Blue;
					bullets[i].act = false;
				}
			}
		}

		for (int i = 0; i < BulletCount; i++)
		{
			SetTextColor(bullets[i].color);
			SetPosition(bullets[i].x, bullets[i].y);
			printf(bullets[i].shape);
		}

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

void HideCursor()
{
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}