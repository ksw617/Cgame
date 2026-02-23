#include <stdio.h>
#include <Windows.h>

#pragma region ENUM
enum Color
{
	BLACK,
	DARKBLUE,
	DARKGREEN,
	DARKCYAN,
	DARKRED,
	DARKMAGENTA,
	DARKYELLOW,
	GRAY,
	DARKGRAY,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	YELLOW,
	WHITE,
};

enum SCENE_ID
{
	LOGO,
	MENU, 
	STAGE,
};

#pragma endregion

#pragma region Struct
struct Obj
{
	int x;
	int y;
	Color color;
	const char* shape;
};
#pragma endregion


#pragma region WIN_API
void HideCursor();
void SetTextColor(Color color);
void SetPosition(int x, int y);
#pragma endregion

#pragma region GAME
const char* logoImg[13];
int timeStep = 0;
void LogoInit();
void LogoUpdate();

const char* menuImg[7];
Obj* menus[4];
Obj* arrow;
void MenuInit();
void MenuUpate();

void StageInit();
void StageUpate();
#pragma endregion

SCENE_ID id;

int main()
{	
	HideCursor();

	id = LOGO;
	LogoInit();

	while (true)
	{
		system("cls");

		switch (id)
		{
		case LOGO:
			LogoUpdate();
			break;
		case MENU:
			MenuUpate();
			break;
		case STAGE:
			StageUpate();
			break;
		default:
			break;
		}
		Sleep(50);
	}


	return 0;
}

#pragma region GAME

#pragma region LOGO

void LogoInit()
{
	 logoImg[0]  = "    ..........           @@@@@    @@@@@.......";
	 logoImg[1]  = "     .........          @     @  @     @.......";
	 logoImg[2]  = "      ........             @@@   @     @........";
	 logoImg[3]  = "       .......           @@      @     @  .......";
	 logoImg[4]  = "        ......          @@@@@@@   @@@@@  th ......";
	 logoImg[5]  = "         .....        ----------------------- .....";
	 logoImg[6]  = "          ....          C  E  N  T  U  R  Y     ....";
	 logoImg[7]  = "           ...        -----------------------     ...";
	 logoImg[8]  = "            ..        @@@@@ @@@@@ @   @ @@@@@       ..";
	 logoImg[9]  = "            ==          @   @      @ @    @          ==";
	 logoImg[10] = "          __||__        @   @@@@    @     @        __||__";
	 logoImg[11] = "         |      |       @   @      @ @    @       |      |";
	 logoImg[12] = "_________|______|_____  @   @@@@@ @   @   @  _____|______|_________";
}

void LogoUpdate()
{
	for (int i = 0; i < 13; i++)
	{
		SetTextColor(YELLOW);
		SetPosition(3, 10 + i);
		printf(logoImg[i]);
	}

	timeStep++;
	if (timeStep < 5)
	{
		SetTextColor(RED);
		SetPosition(16, 25);
		printf("PRESSED ENTER");
	
	}
	else
	{
		timeStep = 0;
	}


	if (GetAsyncKeyState(VK_RETURN))
	{
		
		MenuInit();
		id = MENU;
	}
}
#pragma endregion

#pragma region MENU
void MenuInit()
{
	menuImg[0] = "¡á¡¡¡¡¡¡¡á¡¡¡á¡á¡á¡á¡á¡¡¡á¡¡¡¡¡¡¡á¡¡¡á¡¡¡¡¡¡¡á";
	menuImg[1] = "¡á¡á¡¡¡á¡á¡¡¡á¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡¡¡á¡¡¡¡¡¡¡á";
	menuImg[2] = "¡á¡¡¡á¡¡¡á¡¡¡á¡¡¡¡¡¡¡¡¡¡¡á¡¡¡á¡¡¡á¡¡¡á¡¡¡¡¡¡¡á";
	menuImg[3] = "¡á¡¡¡¡¡¡¡á¡¡¡á¡á¡á¡á¡¡¡¡¡á¡¡¡¡¡á¡á¡¡¡á¡¡¡¡¡¡¡á";
	menuImg[4] = "¡á¡¡¡¡¡¡¡á¡¡¡á¡¡¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡á¡¡¡á¡¡¡¡¡¡¡á";
	menuImg[5] = "¡á¡¡¡¡¡¡¡á¡¡¡á¡¡¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡á¡¡¡á¡¡¡¡¡¡¡á";
	menuImg[6] = "¡á¡¡¡¡¡¡¡á¡¡¡á¡á¡á¡á¡á¡¡¡á¡¡¡¡¡¡¡á¡¡¡¡¡á¡á¡á";	


	for (int i = 0; i < 4; i++)
	{
		menus[i] = (Obj*)malloc(sizeof(Obj));
		menus[i]->x = 17;
		menus[i]->y = 20 + i * 2;
		menus[i]->color = WHITE;
	}

	menus[0]->shape = "START";
	menus[1]->shape = "LOAD";
	menus[2]->shape = "OPTION";
	menus[3]->shape = "EXIT";

	arrow = (Obj*)malloc(sizeof(Obj));;
	arrow->x = 15;
	arrow->y = 20;
	arrow->color = YELLOW;
	arrow->shape = "¢º";
}	
void MenuUpate()
{
	for (int i = 0; i < 7; i++)
	{
		SetTextColor(YELLOW);
		SetPosition(7, 10 + i);
		printf(menuImg[i]);
	}

	SetTextColor(arrow->color);
	SetPosition(arrow->x, arrow->y);
	printf(arrow->shape);

	for (int i = 0; i < 4; i++)
	{
		SetTextColor(menus[i]->color);
		SetPosition(menus[i]->x, menus[i]->y);
		printf(menus[i]->shape);
	}

	
}
#pragma endregion

#pragma region STAGE
void StageInit()
{
}

void StageUpate()
{
	SetTextColor(WHITE);
	SetPosition(10, 10);
	printf("STAGE");
}
#pragma endregion

#pragma endregion




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

void HideCursor()
{
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
#pragma endregion
