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


		//SetConsoleTextAttribute
		//Set : 값을 넣어주다
		//Console : 콘솔창
		//Text : 문자
		//Attribute : 속성
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Blue);

		printf(obj.shape);

		SetPosition(obj2.x, obj2.y);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Yellow);
		printf(obj2.shape);

		Sleep(50);
	}

	return 0;
}