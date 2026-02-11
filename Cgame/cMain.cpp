#include <stdio.h>
#include <Windows.h>

#define Black		0
#define DarkBlue	1
#define DarkGreen	2
#define DarkCyan	3
#define DarkRed		4
#define DarkMagenta	5
#define DarkYellow	6
#define Gray		7
#define DarkGray	8
#define Blue		9
#define Green		10
#define Cyan		11
#define Red			12
#define Magenta		13
#define Yellow		14
#define White		15


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

void SetTextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main()
{
	//CONSOLE_CURSOR_INFO
	//CONSOLE : 콘솔창
	//CURSOR : 커서
	//INFO : 정보
	CONSOLE_CURSOR_INFO info;
	//bVisible
	//b : bool
	//visible : 보이냐 마냐
	info.bVisible = false;
	//dw : DWORD 4byte 짜리 자료형
	//Size : 크기
	info.dwSize = 1;
	//SetConsoleCursorInfo
	//Set : 값을 넣어주다
	//Console : 콘솔창
	//Cursor : 커서
	//Info : 정보
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);


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