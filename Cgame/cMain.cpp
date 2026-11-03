#include <stdio.h>
#include <Windows.h>

#pragma region Enum
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
enum Dir
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
};
#pragma endregion
#pragma region 구조체
struct Obj
{
    Dir dir;
    int x;
    int y;
    Color color;

    int ani = 0;
    // [방향][자세][y줄]
    const char* shape[4][3][13];
};
#pragma endregion



#pragma region 더블버퍼
#define BufferWidth 300    
#define BufferHeight 100

HANDLE hBuffer[2];
int screenIndex;

void InitBuffer();
void FlipBuffer();
void ClearBuffer();
void CloseBuffer();
void WriteBuffer(int x, int y, Color color, const char* shape);
#pragma endregion

#pragma region 플레이어
Obj player;

void PlayerInit();
void PlayerUpdate();
#pragma endregion

#pragma region Game
void GameInit()
{
    PlayerInit();
}

void GameUpdate()
{
    PlayerUpdate();
}
#pragma endregion

#pragma region Main 함수
int main()
{
    InitBuffer();

    GameInit();

    while (true)
    {
        GameUpdate();
     
        FlipBuffer();
        ClearBuffer();

        Sleep(10);
    }

    CloseBuffer();

    return 0;
}
#pragma endregion

#pragma region Player

void PlayerInit()
{
    player.x = 10;
    player.y = 10;
    player.color = LIGHT_WHITE;

#pragma region 왼쪽
    // 자세 0: 기본
    player.shape[0][0][0] = "　　　■■　　　";
    player.shape[0][0][1] = "　■■　　■■　";
    player.shape[0][0][2] = "■　　　　　　■";
    player.shape[0][0][3] = "■　　　　　　■";
    player.shape[0][0][4] = "■■　　　　　■";
    player.shape[0][0][5] = "■　■■■　　■";
    player.shape[0][0][6] = "■　　　　■　■";
    player.shape[0][0][7] = "　■　■　　■　";
    player.shape[0][0][8] = "■　　　　■■　";
    player.shape[0][0][9] = "　■■■■■　　";
    player.shape[0][0][10] = "■　　　　■　　";
    player.shape[0][0][11] = "■　■■　■　　";
    player.shape[0][0][12] = "　■　　■　　　";

    // 자세 1: 살짝 눌림
    player.shape[0][1][0] = "　　　　　　　　";
    player.shape[0][1][1] = "　　　■■　　　";
    player.shape[0][1][2] = "　■■　　■■　";
    player.shape[0][1][3] = "■　　　　　　■";
    player.shape[0][1][4] = "■■　　　　　■";
    player.shape[0][1][5] = "■　■■■　　■";
    player.shape[0][1][6] = "■　　　　■　■";
    player.shape[0][1][7] = "　■　■　　■　";
    player.shape[0][1][8] = "■　　　　■■　";
    player.shape[0][1][9] = "　■■■■■　　";
    player.shape[0][1][10] = "■　　　　■　　";
    player.shape[0][1][11] = "■　■■　■　　";
    player.shape[0][1][12] = "　■　　■　　　";

    // 자세 2: 몸까지 눌림
    player.shape[0][2][0] = "　　　　　　　　";
    player.shape[0][2][1] = "　　　■■　　　";
    player.shape[0][2][2] = "　■■　　■■　";
    player.shape[0][2][3] = "■　　　　　　■";
    player.shape[0][2][4] = "■　　　　　　■";
    player.shape[0][2][5] = "■■　　　　　■";
    player.shape[0][2][6] = "■　■■■　　■";
    player.shape[0][2][7] = "■　　　　■　■";
    player.shape[0][2][8] = "　■　■　　■　";
    player.shape[0][2][9] = "■　　　　■■　";
    player.shape[0][2][10] = "　■■■■■　　";
    player.shape[0][2][11] = "■　■■　■　　";
    player.shape[0][2][12] = "　■　　■　　　";

#pragma endregion

#pragma region 오른쪽
    // 자세 0: 기본
    player.shape[1][0][0] = "　　　■■　　　";
    player.shape[1][0][1] = "　■■　　■■　";
    player.shape[1][0][2] = "■　　　　　　■";
    player.shape[1][0][3] = "■　　　　　　■";
    player.shape[1][0][4] = "■　　　　　■■";
    player.shape[1][0][5] = "■　　■■■　■";
    player.shape[1][0][6] = "■　■　　　　■";
    player.shape[1][0][7] = "　■　　■　■　";
    player.shape[1][0][8] = "　　■　　　　■";
    player.shape[1][0][9] = "　　■■■■■　";
    player.shape[1][0][10] = "　　■　　　　■";
    player.shape[1][0][11] = "　　■　■■　■";
    player.shape[1][0][12] = "　　　■　　■　";

    // 자세 1: 살짝 눌림
    player.shape[1][1][0] = "　　　　　　　　";
    player.shape[1][1][1] = "　　　■■　　　";
    player.shape[1][1][2] = "　■■　　■■　";
    player.shape[1][1][3] = "■　　　　　　■";
    player.shape[1][1][4] = "■　　　　　■■";
    player.shape[1][1][5] = "■　　■■■　■";
    player.shape[1][1][6] = "■　■　　　　■";
    player.shape[1][1][7] = "　■　　■　■　";
    player.shape[1][1][8] = "　　■　　　　■";
    player.shape[1][1][9] = "　　■■■■■　";
    player.shape[1][1][10] = "　　■　　　　■";
    player.shape[1][1][11] = "　　■　■■　■";
    player.shape[1][1][12] = "　　　■　　■　";

    // 자세 2: 몸까지 눌림
    player.shape[1][2][0] = "　　　　　　　　";
    player.shape[1][2][1] = "　　　■■　　　";
    player.shape[1][2][2] = "　■■　　■■　";
    player.shape[1][2][3] = "■　　　　　　■";
    player.shape[1][2][4] = "■　　　　　　■";
    player.shape[1][2][5] = "■　　　　　■■";
    player.shape[1][2][6] = "■　　■■■　■";
    player.shape[1][2][7] = "■　■　　　　■";
    player.shape[1][2][8] = "　■　　■　■　";
    player.shape[1][2][9] = "　　■　　　　■";
    player.shape[1][2][10] = "　　■■■■■　";
    player.shape[1][2][11] = "　　■　■■　■";
    player.shape[1][2][12] = "　　　■　　■　";

#pragma endregion

#pragma region 뒤
    // 자세 0: 기본
    player.shape[2][0][0] = "　　　　■■　　";
    player.shape[2][0][1] = "　■■■　　■　";
    player.shape[2][0][2] = "■　　　　　　■";
    player.shape[2][0][3] = "■　　　　　　■";
    player.shape[2][0][4] = "■　　　　　　■";
    player.shape[2][0][5] = "■　　　　　　■";
    player.shape[2][0][6] = "■　　　　　　■";
    player.shape[2][0][7] = "■　　　　　　■";
    player.shape[2][0][8] = "　■　　　　■　";
    player.shape[2][0][9] = "■　■■■■　■";
    player.shape[2][0][10] = "■　　　　　　■";
    player.shape[2][0][11] = "　■　■■　■　";
    player.shape[2][0][12] = "　■■　　■■　";

    // 자세 1: 살짝 눌림
    player.shape[2][1][0] = "　　　　　　　　";
    player.shape[2][1][1] = "　　　　■■　　";
    player.shape[2][1][2] = "　■■■　　■　";
    player.shape[2][1][3] = "■　　　　　　■";
    player.shape[2][1][4] = "■　　　　　　■";
    player.shape[2][1][5] = "■　　　　　　■";
    player.shape[2][1][6] = "■　　　　　　■";
    player.shape[2][1][7] = "■　　　　　　■";
    player.shape[2][1][8] = "　■　　　　■　";
    player.shape[2][1][9] = "■　■■■■　■";
    player.shape[2][1][10] = "■　　　　　　■";
    player.shape[2][1][11] = "　■　■■　■　";
    player.shape[2][1][12] = "　■■　　■■　";

    // 자세 2: 몸까지 눌림
    player.shape[2][2][0] = "　　　　　　　　";
    player.shape[2][2][1] = "　　　　■■　　";
    player.shape[2][2][2] = "　■■■　　■　";
    player.shape[2][2][3] = "■　　　　　　■";
    player.shape[2][2][4] = "■　　　　　　■";
    player.shape[2][2][5] = "■　　　　　　■";
    player.shape[2][2][6] = "■　　　　　　■";
    player.shape[2][2][7] = "■　　　　　　■";
    player.shape[2][2][8] = "■　　　　　　■";
    player.shape[2][2][9] = "　■　　　　■　";
    player.shape[2][2][10] = "■　■■■■　■";
    player.shape[2][2][11] = "　■　■■　■　";
    player.shape[2][2][12] = "　■■　　■■　";

#pragma endregion

#pragma region 앞
    // 자세 0: 기본
    player.shape[3][0][0] = "　　■■　　　　";
    player.shape[3][0][1] = "　■　　■■■　";
    player.shape[3][0][2] = "■　　　　　　■";
    player.shape[3][0][3] = "■　　　　　　■";
    player.shape[3][0][4] = "■　　　　■　■";
    player.shape[3][0][5] = "■　■■■　■■";
    player.shape[3][0][6] = "■■　　　　■■";
    player.shape[3][0][7] = "■　■　　■　■";
    player.shape[3][0][8] = "　■　　　　■　";
    player.shape[3][0][9] = "■■■■■■■■";
    player.shape[3][0][10] = "■　　　　　　■";
    player.shape[3][0][11] = "　■　■■　■　";
    player.shape[3][0][12] = "　■■　　■■　";

    // 자세 1: 살짝 눌림
    player.shape[3][1][0] = "　　　　　　　　";
    player.shape[3][1][1] = "　　■■　　　　";
    player.shape[3][1][2] = "　■　　■■■　";
    player.shape[3][1][3] = "■　　　　　　■";
    player.shape[3][1][4] = "■　　　　■　■";
    player.shape[3][1][5] = "■　■■■　■■";
    player.shape[3][1][6] = "■■　　　　■■";
    player.shape[3][1][7] = "■　■　　■　■";
    player.shape[3][1][8] = "　■　　　　■　";
    player.shape[3][1][9] = "■■■■■■■■";
    player.shape[3][1][10] = "■　　　　　　■";
    player.shape[3][1][11] = "　■　■■　■　";
    player.shape[3][1][12] = "　■■　　■■　";

    // 자세 2: 몸까지 눌림
    player.shape[3][2][0] = "　　　　　　　　";
    player.shape[3][2][1] = "　　■■　　　　";
    player.shape[3][2][2] = "　■　　■■■　";
    player.shape[3][2][3] = "■　　　　　　■";
    player.shape[3][2][4] = "■　　　　　　■";
    player.shape[3][2][5] = "■　　　　■　■";
    player.shape[3][2][6] = "■　■■■　■■";
    player.shape[3][2][7] = "■■　　　　■■";
    player.shape[3][2][8] = "■　■　　■　■";
    player.shape[3][2][9] = "　■　　　　■　";
    player.shape[3][2][10] = "■■■■■■■■";
    player.shape[3][2][11] = "　■　■■　■　";
    player.shape[3][2][12] = "　■■　　■■　";

#pragma endregion


}

void PlayerUpdate()
{

    player.ani = (GetTickCount64() / 250) % 3;


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
        WriteBuffer(player.x, player.y + i, player.color, player.shape[player.dir][player.ani][i]);
    }

}

#pragma endregion



#pragma region 더블버퍼


void InitBuffer()
{
    screenIndex = 0;
    COORD size = { BufferWidth, BufferHeight };
    SMALL_RECT rect = { 0, 0, BufferWidth, BufferHeight };

    hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleScreenBufferSize(hBuffer[0], size);
    SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);

    hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleScreenBufferSize(hBuffer[1], size);
    SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);

    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 1;

    SetConsoleCursorInfo(hBuffer[0], &info);
    SetConsoleCursorInfo(hBuffer[1], &info);

}

void FlipBuffer()
{
    SetConsoleActiveScreenBuffer(hBuffer[screenIndex]);
    screenIndex = !screenIndex;
}

void ClearBuffer()
{
    COORD pos = { 0, 0 };
    DWORD dw;
    FillConsoleOutputCharacter(hBuffer[screenIndex], ' ', BufferWidth * BufferHeight, pos, &dw);
}

void CloseBuffer()
{
    CloseHandle(hBuffer[0]);
    CloseHandle(hBuffer[1]);
}

void WriteBuffer(int x, int y, Color color, const char* shape)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

    COORD pos{ x * 2, y };
    SetConsoleCursorPosition(hBuffer[screenIndex], pos);

    DWORD dw;
    WriteFile(hBuffer[screenIndex], shape, strlen(shape), &dw, NULL);

}

#pragma endregion
