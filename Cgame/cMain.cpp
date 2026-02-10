#include <stdio.h>
#include <Windows.h>

int main()
{
	COORD pos;
	pos.X = 10;
	pos.Y = 10;


	while (true)
	{
		system("cls");

		pos.X++;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

		printf("Hello world");

		Sleep(50);
	}

	return 0;
}