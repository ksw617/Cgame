#include <stdio.h>
#include <Windows.h>


#pragma region DoubleBuffer
//버퍼 초기화
#define BufferWidth 80	// 가로 버퍼 크기
#define BufferHeight 40 // 세로 버퍼 크기


HANDLE hBuffer[2];	//창 두게를 제어하는 핸들
int screenIndex;	//hBuffer[screenIndex], screenIndex == 0 or 1


void InitBuffer();
void FlipBuffer();
void ClearBuffer();
void WriteBuffer(int x, int y, const char* shape, int color);
void CloseBuffer();

#pragma endregion
#pragma region Enum
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

enum  SCENE_ID
{
	LOGO,
	MENU,
	STAGE,
};
#pragma endregion

#pragma region Define
#define BulletCount 10
#define EnemyCount 10
#pragma endregion

#pragma region Struct

struct Bullet
{
	bool act;
	int x;
	int y;
	const char* shape;
	Color color;
};
typedef struct Obj
{
	bool act;
	int x;
	int y;
	const char* shape[3];
	Color color;
}Player, Enemy;
#pragma endregion

#pragma region Vairables
int spawnTimer = 0;
SCENE_ID id;
Player* player = nullptr;
Bullet* bullets[BulletCount] = {};
Enemy* enemies[EnemyCount] = {};
#pragma endregion

#pragma region GAME

void LogoInit();
void LogoProgress();
void LogoRender();
void LogoRelease();

void MenuInit();
void MenuProgress();
void MenuRender();
void MenuRelease();

void StageInit();
void StageProgress();
void StageRender();
void StageRelease();
#pragma endregion

int main()
{
	id = LOGO;
	LogoInit();
	InitBuffer();


	while (true)
	{
		switch (id)
		{
		case LOGO:
			LogoProgress();
			LogoRender();
			break;
		case MENU:
			MenuProgress();
			MenuRender();
			break;
		case STAGE:
			StageProgress();
			StageRender();
			break;
		default:
			break;
		}
		
		FlipBuffer();
		ClearBuffer();

		Sleep(50);

	}


	CloseBuffer();


	return 0;
}

#pragma region GAME

#pragma region LOGO
void LogoInit()
{
}

void LogoProgress()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		LogoRelease();
		id = MENU;
		MenuInit();
		return;
	}
}

void LogoRender()
{
	WriteBuffer(10, 10, "LOGO", WHITE);
}

void LogoRelease()
{
}
#pragma endregion
#pragma region MENU
void MenuInit()
{
}

void MenuProgress()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		MenuRelease();
		id = STAGE;
		StageInit();
		return;
	}
}

void MenuRender()
{
	WriteBuffer(10, 10, "MENU", WHITE);
}

void MenuRelease()
{
}

#pragma endregion
#pragma region STAGE
void StageInit()
{
	player = (Player*)malloc(sizeof(Player));
	player->x = 17;
	player->y = 33;
	player->shape[0] = "　■　";
	player->shape[1] = "■■■";
	player->shape[2] = "■■■";
	player->color = WHITE;

	for (int i = 0; i < BulletCount; i++)
	{
		bullets[i] = (Bullet*)malloc(sizeof(Bullet));
		bullets[i]->act = false;
		bullets[i]->x = i;
		bullets[i]->y = 0;
		bullets[i]->shape = "●";
		bullets[i]->color = BLUE;

	}

	for (int i = 0; i < EnemyCount; i++)
	{
		enemies[i] = (Enemy*)malloc(sizeof(Enemy));
		enemies[i]->act = false;
		enemies[i]->x = i * 4;
		enemies[i]->y = 1;
		enemies[i]->shape[0] = "■■■";
		enemies[i]->shape[1] = "■■■";
		enemies[i]->shape[2] = "■■■";
		enemies[i]->color = RED;
	}
}

void StageProgress()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		player->x--;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		player->x++;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		for (int i = 0; i < BulletCount; i++)
		{
			if (!bullets[i]->act)
			{
				bullets[i]->act = true;
				bullets[i]->x = player->x + 1;
				bullets[i]->y = player->y - 1;
				bullets[i]->color = RED;
				break;
			}
		}
	}

	for (int i = 0; i < BulletCount; i++)
	{
		if (bullets[i]->act)
		{
			bullets[i]->y--;
			if (bullets[i]->y < 0)
			{
				bullets[i]->act = false;
				bullets[i]->x = i;
				bullets[i]->y = 0;
				bullets[i]->color = BLUE;
			}
		}
	}

	spawnTimer++;
	if (spawnTimer > 50)
	{
		spawnTimer = 0;
		int actIdx = 0;
		do
		{
			actIdx = rand() % EnemyCount;

		} while (enemies[actIdx]->act);


		enemies[actIdx]->act = true;
		enemies[actIdx]->color = YELLOW;
	}

	for (int i = 0; i < EnemyCount; i++)
	{
		if (enemies[i]->act)
		{
			enemies[i]->y++;
			if (enemies[i]->y >= 38)
			{
				enemies[i]->act = false;
				enemies[i]->x = i * 4;
				enemies[i]->y = 1;
				enemies[i]->color = RED;
			}
		}
	}


}

void StageRender()
{
	for (int i = 0; i < 3; i++)
	{
		WriteBuffer(player->x, player->y + i, player->shape[i], player->color);
	}

	for (int i = 0; i < BulletCount; i++)
	{
		WriteBuffer(bullets[i]->x, bullets[i]->y, bullets[i]->shape, bullets[i]->color);
	}

	for (int i = 0; i < EnemyCount; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			WriteBuffer(enemies[i]->x, enemies[i]->y + j, enemies[i]->shape[j], enemies[i]->color);
		}
	}


}

void StageRelease()
{
	if (player != nullptr)
	{
		free(player);
		player = nullptr;
	}

	for (int i = 0; i < BulletCount; i++)
	{
		if (bullets[i] != nullptr)
		{
			free(bullets[i]);
			bullets[i] = nullptr;

		}
	}

	for (int i = 0; i < EnemyCount; i++)
	{
		if (enemies[i] != nullptr)
		{
			free(enemies[i]);
			enemies[i] = nullptr;

		}
	}
}
#pragma endregion

#pragma endregion

#pragma region DoubleBuffer
//버퍼 초기화
void InitBuffer()
{
	//현재 스크린 index값은 0
	screenIndex = 0;

	//size.x = 80, size.y = 40 : 화면 크기
	COORD size = { BufferWidth, BufferHeight };

	//창 크기 왼쪽 : 0, 위쪽 : 0 오른쪽 : 80 - 1, 아래쪽 : 40 - 1
	SMALL_RECT rect = { 0,0,BufferWidth - 1, BufferHeight - 1 };

	//0번 버퍼 만들기
	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//0번 화면 버퍼 사이즈 설정(만든 버퍼 주소, 크기)
	SetConsoleScreenBufferSize(hBuffer[0], size);
	//0번 창 사이즈 설정
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);

	//1번 버퍼 만들기
	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//1번 화면 버퍼 사이즈 설정(만든 버퍼 주소, 크기)
	SetConsoleScreenBufferSize(hBuffer[1], size);
	//1번 창 사이즈 설정
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);

	CONSOLE_CURSOR_INFO info;	//콘솔 커서 정보 구조체
	info.dwSize = 1;			//커서 크기
	info.bVisible = FALSE;		//커서 안보이게

	//0 & 1 각각의 버퍼에 커서 정보 등록
	SetConsoleCursorInfo(hBuffer[0], &info);
	SetConsoleCursorInfo(hBuffer[1], &info);
}


//버퍼 뒤집기 0->1 1->0 
void FlipBuffer()
{
	//해당 버퍼 활성화
	SetConsoleActiveScreenBuffer(hBuffer[screenIndex]);

	//[0]->[1] / [1]->[0]
	screenIndex = !screenIndex;
}

//버퍼 창 깨끗이
void ClearBuffer()
{
	//시작 위치
	//pos.x = 0; pos.y = 0;
	COORD pos = { 0,0 };
	//매개변수 값 넣어줄려고
	DWORD dw;

	//화면을 ' '로 채움
	FillConsoleOutputCharacter(hBuffer[screenIndex], ' ', BufferWidth * BufferHeight, pos, &dw);
}


//문자열 원하는 위치에 써주기 & 색깔 까지
//WriteBuffer(x좌표, y좌표, 문자열, 색깔 인덱스)
void WriteBuffer(int x, int y, const char* shape, int color)
{
	//위치 설정
	//pos.x = x * 2; pos.y = y;
	COORD pos = { x * 2, y };

	//커서 위치 이동
	SetConsoleCursorPosition(hBuffer[screenIndex], pos);

	//색깔 바꿔주기
	SetConsoleTextAttribute(hBuffer[screenIndex], color);

	//매개변수 값을 넣기 위해
	DWORD dw;

	//해당 버퍼에 쓰기
	WriteFile(hBuffer[screenIndex], shape, strlen(shape), &dw, NULL);
}

//버퍼 해제
void CloseBuffer()
{
	//버퍼 닫기
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}


#pragma endregion

