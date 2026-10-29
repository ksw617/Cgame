#include <stdio.h>
#include <Windows.h>

enum Color
{
	//BLACK,
	BLUE = 1,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	YELLOW,
	LIGHT_GRAY,
	DARK_GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	LIGHT_YELLOW,
	LIGHT_WHITE,
};

//Direction : 방향
enum DIR
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

#define BufferWidth 300	//가로 버퍼 크기
#define BufferHeight 100 //세로 버퍼 크기

struct Obj
{
	DIR dir;
	int x;
	int y;
	Color color;
	const char* shape[4][13];
};


//HANDLE 주소를 담기위한 자료형 없는 포인터 void* == HANDLE
HANDLE hBuffer[2];	//콘솔창 두개를 제어하는 핸들
int screenIndex;	//0 or 1 hBuffer[screenIndex]: hBuffer[0] or hBuffer[1]

void InitBuffer();
void FlipBuffer();
void ClearBuffer();
void CloseBuffer();
void WriteBuffer(int x, int y, int color, const char* shape);


Obj player;
void Init();
void Update();


int main()
{
	InitBuffer();  
	Init();

	while (true)
	{

		Update();

		FlipBuffer();
		ClearBuffer();

		Sleep(10);
	}

	CloseBuffer();

	return 0;
}

void Init()
{
	player.dir = DOWN;
	player.x = 10;
	player.y = 10;
	player.color = LIGHT_WHITE;
	player.shape[0][0] = "　　　■■　　　";
	player.shape[0][1] = "　■■　　■■　";
	player.shape[0][2] = "■　　　　　　■";
	player.shape[0][3] = "■　　　　　　■";
	player.shape[0][4] = "■■　　　　　■";
	player.shape[0][5] = "■　■■■　　■";
	player.shape[0][6] = "■　　　　■　■";
	player.shape[0][7] = "　■　■　　■　";
	player.shape[0][8] = "■　　　　■■　";
	player.shape[0][9] = "　■■■■■　　";
	player.shape[0][10] = "■　　　　■　　";
	player.shape[0][11] = "■　■■　■　　";
	player.shape[0][12] = "　■　　■　　　";

	player.shape[1][0] = "　　　■■　　　";
	player.shape[1][1] = "　■■　　■■　";
	player.shape[1][2] = "■　　　　　　■";
	player.shape[1][3] = "■　　　　　　■";
	player.shape[1][4] = "■　　　　　■■";
	player.shape[1][5] = "■　　■■■　■";
	player.shape[1][6] = "■　■　　　　■";
	player.shape[1][7] = "　■　　■　■　";
	player.shape[1][8] = "　　■　　　　■";
	player.shape[1][9] = "　　■■■■■　";
	player.shape[1][10] = "　　■　　　　■";
	player.shape[1][11] = "　　■　■■　■";
	player.shape[1][12] = "　　　■　　■　";

	player.shape[2][0] = "　　　　■■　　";
	player.shape[2][1] = "　■■■　　■　";
	player.shape[2][2] = "■　　　　　　■";
	player.shape[2][3] = "■　　　　　　■";
	player.shape[2][4] = "■　　　　　　■";
	player.shape[2][5] = "■　　　　　　■";
	player.shape[2][6] = "■　　　　　　■";
	player.shape[2][7] = "■　　　　　　■";
	player.shape[2][8] = "　■　　　　■　";
	player.shape[2][9] = "■　■■■■　■";
	player.shape[2][10] = "■　　　　　　■";
	player.shape[2][11] = "　■　■■　■　";
	player.shape[2][12] = "　■■　　■■　";

	player.shape[3][0] = "　　■■　　　　";
	player.shape[3][1] = "　■　　■■■　";
	player.shape[3][2] = "■　　　　　　■";
	player.shape[3][3] = "■　　　　　　■";
	player.shape[3][4] = "■　　　　■　■";
	player.shape[3][5] = "■　■■■　■■";
	player.shape[3][6] = "■■　　　　■■";
	player.shape[3][7] = "■　■　　■　■";
	player.shape[3][8] = "　■　　　　■　";
	player.shape[3][9] = "■■■■■■■■";
	player.shape[3][10] = "■　　　　　　■";
	player.shape[3][11] = "　■　■■　■　";
	player.shape[3][12] = "　■■　　■■　";
}

void Update()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		player.x--;
		player.dir = LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		player.x++;
		player.dir = RIGHT;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		player.y--;
		player.dir = UP;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		player.y++;
		player.dir = DOWN;
	}

	for (int i = 0; i < 13; i++)
	{
		WriteBuffer(player.x, player.y + i, player.color, player.shape[(int)player.dir][i]);
	}
}


//더블 버퍼를 초기화 하는 함수
void InitBuffer()
{
	//현재 스크린 버퍼의 index값은 0
	screenIndex = 0;

	//size.X = 80, size.Y = 40 :  버퍼의 크기
	COORD size = { BufferWidth, BufferHeight };

	//창크기 -> 왼쪽 : 0, 위쪽 : 0, 오른쪽 : 80, 아래쪽 : 40
	SMALL_RECT rect = { 0, 0, BufferWidth, BufferHeight };

	//0번 스크린 버퍼 만들기
	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//0번 스크린 버퍼에 사이즈 설정(만든 버퍼 주소, 버퍼 크기);
	SetConsoleScreenBufferSize(hBuffer[0], size);
	//0번 창 정보 등록
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);

	//1번 스크린 버퍼 만들기
	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//1번 스크린 버퍼에 사이즈 설정(만든 버퍼 주소, 버퍼 크기);
	SetConsoleScreenBufferSize(hBuffer[1], size);
	//1번 창 정보 등록
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);

	CONSOLE_CURSOR_INFO info;			//콘솔 커서 정보 구조체
	info.bVisible = false;				//커서 안보이게
	info.dwSize = 1;					//커서 크기

	//0 & 1 각각의 화면에 커서 정보 등록 : 두개의 창 모두 커서 안보이게
	SetConsoleCursorInfo(hBuffer[0], &info);
	SetConsoleCursorInfo(hBuffer[1], &info);

}

void FlipBuffer()
{
	//해당 버퍼 hBuffer[0] or hBuffer[1]을 우리가 볼수 있게 활성화
	//콘솔의 활성화할 스크린 버퍼를 설정하다
	SetConsoleActiveScreenBuffer(hBuffer[screenIndex]);

	//[0] -> [1] / [1]->[0]
	screenIndex = !screenIndex;	//FlipBuffer를 할때 마다
	//hBuffer[0] or hBuffer[1]이 번갈아 가며 활성화 됨
}

//화면 깨끗이
void ClearBuffer()
{
	//시작위치
	//pos.X = 0, pos.Y = 0;
	COORD pos = { 0, 0 };

	//매개변수 값 채울려고 
	DWORD dw;

	//함수(매개변수들) // params == parameters == 매개변수들

	//문자(' ')로 화면을 채움
	//FillConsoleOutputCharacter(문자 채울 화면, 문자, 갯수, 시작위치, 값 담을 변수 주소)
	FillConsoleOutputCharacter(hBuffer[screenIndex], ' ', BufferWidth * BufferHeight, pos, &dw);
}

//버퍼 해제
void CloseBuffer()
{
	//해당 주소 메모리 해제
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}

void WriteBuffer(int x, int y, int color, const char* shape)
{
	//색깔 바꿔주고
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	//위치값 담을 구조체 할당 
	COORD pos{ x * 2, y };
	//커서 위치 이동
	SetConsoleCursorPosition(hBuffer[screenIndex], pos);

	//매개변수 값 채울라고
	DWORD dw;

	//해당 화면에 값ㅇ르 쓰기 == printf(shape);
	WriteFile(hBuffer[screenIndex], shape, strlen(shape), &dw, NULL);

}