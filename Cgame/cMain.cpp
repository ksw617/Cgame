#include <stdio.h>
#include <Windows.h>
#include <time.h>


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
#pragma region ±¸Á¶Ã¼
struct Obj
{
    bool act;
    Dir dir;
    int x;
    int y;
    Color color;

    int ani = 0;
    // [¹æÇâ][ÀÚ¼¼][yÁÙ]
    const char* shape[4][8][13];
};
#pragma endregion



#pragma region ´õºí¹öÆÛ
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

#pragma region ÇÃ·¹ÀÌ¾î
#define SlimeCount 10

Obj player;    
Obj slimes[SlimeCount];

void PlayerInit();
void PlayerUpdate();
void SlimeInit();
void SlimeUpdate();
#pragma endregion

#pragma region Game
void GameInit()
{
    SlimeInit();
    PlayerInit();
}

void GameUpdate()
{
    SlimeUpdate();
    PlayerUpdate();
}
#pragma endregion

#define DeltaTime 20

#pragma region Main ÇÔ¼ö
int main()
{
    srand((unsigned)time(NULL));
    // 10
    ULONGLONG pastTime = GetTickCount64();
    InitBuffer();
    GameInit();

    while (true)
    {

        if (pastTime + DeltaTime <= GetTickCount64())
        {
            pastTime = GetTickCount64();

            GameUpdate();
            FlipBuffer();
            ClearBuffer();
        }

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

#pragma region ÇÃ·¹ÀÌ¾î ÀÌ¹ÌÁöµé

#pragma region ¿ÞÂÊ
    // ÀÚ¼¼ 0: ±âº»
    player.shape[0][0][0] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
    player.shape[0][0][1] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";
    player.shape[0][0][2] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][0][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][0][4] = "¡á¡á¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][0][5] = "¡á¡¡¡á¡á¡á¡¡¡¡¡á";
    player.shape[0][0][6] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡á";
    player.shape[0][0][7] = "¡¡¡á¡¡¡á¡¡¡¡¡á¡¡";
    player.shape[0][0][8] = "¡á¡¡¡¡¡¡¡¡¡á¡á¡¡";
    player.shape[0][0][9] = "¡¡¡á¡á¡á¡á¡á¡¡¡¡";
    player.shape[0][0][10] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡¡";
    player.shape[0][0][11] = "¡á¡¡¡á¡á¡¡¡á¡¡¡¡";
    player.shape[0][0][12] = "¡¡¡á¡¡¡¡¡á¡¡¡¡¡¡";

    // ÀÚ¼¼ 1: »ìÂ¦ ´­¸²
    player.shape[0][1][0] = "¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡";
    player.shape[0][1][1] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
    player.shape[0][1][2] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";
    player.shape[0][1][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][1][4] = "¡á¡á¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][1][5] = "¡á¡¡¡á¡á¡á¡¡¡¡¡á";
    player.shape[0][1][6] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡á";
    player.shape[0][1][7] = "¡¡¡á¡¡¡á¡¡¡¡¡á¡¡";
    player.shape[0][1][8] = "¡á¡¡¡¡¡¡¡¡¡á¡á¡¡";
    player.shape[0][1][9] = "¡¡¡á¡á¡á¡á¡á¡¡¡¡";
    player.shape[0][1][10] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡¡";
    player.shape[0][1][11] = "¡á¡¡¡á¡á¡¡¡á¡¡¡¡";
    player.shape[0][1][12] = "¡¡¡á¡¡¡¡¡á¡¡¡¡¡¡";

    // ÀÚ¼¼ 2: ¸ö±îÁö ´­¸²
    player.shape[0][2][0] = "¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡";
    player.shape[0][2][1] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
    player.shape[0][2][2] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";
    player.shape[0][2][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][2][4] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][2][5] = "¡á¡á¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][2][6] = "¡á¡¡¡á¡á¡á¡¡¡¡¡á";
    player.shape[0][2][7] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡á";
    player.shape[0][2][8] = "¡¡¡á¡¡¡á¡¡¡¡¡á¡¡";
    player.shape[0][2][9] = "¡á¡¡¡¡¡¡¡¡¡á¡á¡¡";
    player.shape[0][2][10] = "¡¡¡á¡á¡á¡á¡á¡¡¡¡";
    player.shape[0][2][11] = "¡á¡¡¡á¡á¡¡¡á¡¡¡¡";
    player.shape[0][2][12] = "¡¡¡á¡¡¡¡¡á¡¡¡¡¡¡";

#pragma endregion                                                           
#pragma region ¿À¸¥ÂÊ
    // ÀÚ¼¼ 0: ±âº»
    player.shape[1][0][0] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
    player.shape[1][0][1] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";
    player.shape[1][0][2] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[1][0][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[1][0][4] = "¡á¡¡¡¡¡¡¡¡¡¡¡á¡á";
    player.shape[1][0][5] = "¡á¡¡¡¡¡á¡á¡á¡¡¡á";
    player.shape[1][0][6] = "¡á¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][0][7] = "¡¡¡á¡¡¡¡¡á¡¡¡á¡¡";
    player.shape[1][0][8] = "¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][0][9] = "¡¡¡¡¡á¡á¡á¡á¡á¡¡";
    player.shape[1][0][10] = "¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][0][11] = "¡¡¡¡¡á¡¡¡á¡á¡¡¡á";
    player.shape[1][0][12] = "¡¡¡¡¡¡¡á¡¡¡¡¡á¡¡";

    // ÀÚ¼¼ 1: »ìÂ¦ ´­¸²
    player.shape[1][1][0] = "¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡";
    player.shape[1][1][1] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
    player.shape[1][1][2] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";
    player.shape[1][1][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[1][1][4] = "¡á¡¡¡¡¡¡¡¡¡¡¡á¡á";
    player.shape[1][1][5] = "¡á¡¡¡¡¡á¡á¡á¡¡¡á";
    player.shape[1][1][6] = "¡á¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][1][7] = "¡¡¡á¡¡¡¡¡á¡¡¡á¡¡";
    player.shape[1][1][8] = "¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][1][9] = "¡¡¡¡¡á¡á¡á¡á¡á¡¡";
    player.shape[1][1][10] = "¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][1][11] = "¡¡¡¡¡á¡¡¡á¡á¡¡¡á";
    player.shape[1][1][12] = "¡¡¡¡¡¡¡á¡¡¡¡¡á¡¡";

    // ÀÚ¼¼ 2: ¸ö±îÁö ´­¸²
    player.shape[1][2][0] = "¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡";
    player.shape[1][2][1] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
    player.shape[1][2][2] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";
    player.shape[1][2][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[1][2][4] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[1][2][5] = "¡á¡¡¡¡¡¡¡¡¡¡¡á¡á";
    player.shape[1][2][6] = "¡á¡¡¡¡¡á¡á¡á¡¡¡á";
    player.shape[1][2][7] = "¡á¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][2][8] = "¡¡¡á¡¡¡¡¡á¡¡¡á¡¡";
    player.shape[1][2][9] = "¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][2][10] = "¡¡¡¡¡á¡á¡á¡á¡á¡¡";
    player.shape[1][2][11] = "¡¡¡¡¡á¡¡¡á¡á¡¡¡á";
    player.shape[1][2][12] = "¡¡¡¡¡¡¡á¡¡¡¡¡á¡¡";

#pragma endregion
#pragma region µÚ
    // ÀÚ¼¼ 0: ±âº»
    player.shape[2][0][0] = "¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡";
    player.shape[2][0][1] = "¡¡¡á¡á¡á¡¡¡¡¡á¡¡";
    player.shape[2][0][2] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][0][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][0][4] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][0][5] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][0][6] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][0][7] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][0][8] = "¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡";
    player.shape[2][0][9] = "¡á¡¡¡á¡á¡á¡á¡¡¡á";
    player.shape[2][0][10] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][0][11] = "¡¡¡á¡¡¡á¡á¡¡¡á¡¡";
    player.shape[2][0][12] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";

    // ÀÚ¼¼ 1: »ìÂ¦ ´­¸²
    player.shape[2][1][0] = "¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡";
    player.shape[2][1][1] = "¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡";
    player.shape[2][1][2] = "¡¡¡á¡á¡á¡¡¡¡¡á¡¡";
    player.shape[2][1][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][1][4] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][1][5] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][1][6] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][1][7] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][1][8] = "¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡";
    player.shape[2][1][9] = "¡á¡¡¡á¡á¡á¡á¡¡¡á";
    player.shape[2][1][10] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][1][11] = "¡¡¡á¡¡¡á¡á¡¡¡á¡¡";
    player.shape[2][1][12] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";

    // ÀÚ¼¼ 2: ¸ö±îÁö ´­¸²
    player.shape[2][2][0] = "¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡";
    player.shape[2][2][1] = "¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡";
    player.shape[2][2][2] = "¡¡¡á¡á¡á¡¡¡¡¡á¡¡";
    player.shape[2][2][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][2][4] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][2][5] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][2][6] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][2][7] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][2][8] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][2][9] = "¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡";
    player.shape[2][2][10] = "¡á¡¡¡á¡á¡á¡á¡¡¡á";
    player.shape[2][2][11] = "¡¡¡á¡¡¡á¡á¡¡¡á¡¡";
    player.shape[2][2][12] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";

#pragma endregion
#pragma region ¾Õ
    // ÀÚ¼¼ 0: ±âº»
    player.shape[3][0][0] = "¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡";
    player.shape[3][0][1] = "¡¡¡á¡¡¡¡¡á¡á¡á¡¡";
    player.shape[3][0][2] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[3][0][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[3][0][4] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡á";
    player.shape[3][0][5] = "¡á¡¡¡á¡á¡á¡¡¡á¡á";
    player.shape[3][0][6] = "¡á¡á¡¡¡¡¡¡¡¡¡á¡á";
    player.shape[3][0][7] = "¡á¡¡¡á¡¡¡¡¡á¡¡¡á";
    player.shape[3][0][8] = "¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡";
    player.shape[3][0][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
    player.shape[3][0][10] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[3][0][11] = "¡¡¡á¡¡¡á¡á¡¡¡á¡¡";
    player.shape[3][0][12] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";

    // ÀÚ¼¼ 1: »ìÂ¦ ´­¸²
    player.shape[3][1][0] = "¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡";
    player.shape[3][1][1] = "¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡";
    player.shape[3][1][2] = "¡¡¡á¡¡¡¡¡á¡á¡á¡¡";
    player.shape[3][1][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[3][1][4] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡á";
    player.shape[3][1][5] = "¡á¡¡¡á¡á¡á¡¡¡á¡á";
    player.shape[3][1][6] = "¡á¡á¡¡¡¡¡¡¡¡¡á¡á";
    player.shape[3][1][7] = "¡á¡¡¡á¡¡¡¡¡á¡¡¡á";
    player.shape[3][1][8] = "¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡";
    player.shape[3][1][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
    player.shape[3][1][10] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[3][1][11] = "¡¡¡á¡¡¡á¡á¡¡¡á¡¡";
    player.shape[3][1][12] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";

    // ÀÚ¼¼ 2: ¸ö±îÁö ´­¸²
    player.shape[3][2][0] = "¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡";
    player.shape[3][2][1] = "¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡";
    player.shape[3][2][2] = "¡¡¡á¡¡¡¡¡á¡á¡á¡¡";
    player.shape[3][2][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[3][2][4] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[3][2][5] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡á";
    player.shape[3][2][6] = "¡á¡¡¡á¡á¡á¡¡¡á¡á";
    player.shape[3][2][7] = "¡á¡á¡¡¡¡¡¡¡¡¡á¡á";
    player.shape[3][2][8] = "¡á¡¡¡á¡¡¡¡¡á¡¡¡á";
    player.shape[3][2][9] = "¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡";
    player.shape[3][2][10] = "¡á¡á¡á¡á¡á¡á¡á¡á";
    player.shape[3][2][11] = "¡¡¡á¡¡¡á¡á¡¡¡á¡¡";
    player.shape[3][2][12] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";

#pragma endregion
#pragma region ¿ÞÂÊ
    // ÇÁ·¹ÀÓ 3: °È±â ÇÑÂÊ ¹ß µé±â
    player.shape[0][3][0] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
    player.shape[0][3][1] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";
    player.shape[0][3][2] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][3][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][3][4] = "¡á¡á¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][3][5] = "¡á¡¡¡á¡á¡á¡¡¡¡¡á";
    player.shape[0][3][6] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡á";
    player.shape[0][3][7] = "¡¡¡á¡¡¡á¡¡¡¡¡á¡¡";
    player.shape[0][3][8] = "¡á¡¡¡¡¡¡¡¡¡á¡á¡¡";
    player.shape[0][3][9] = "¡¡¡á¡á¡á¡á¡á¡¡¡¡";
    player.shape[0][3][10] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡¡";
    player.shape[0][3][11] = "¡á¡¡¡á¡¡¡á¡á¡¡¡¡";
    player.shape[0][3][12] = "¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡";

    // ÇÁ·¹ÀÓ 4: °È±â ±âº» ÀÚ¼¼·Î º¹±Í
    player.shape[0][4][0] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
    player.shape[0][4][1] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";
    player.shape[0][4][2] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][4][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][4][4] = "¡á¡á¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][4][5] = "¡á¡¡¡á¡á¡á¡¡¡¡¡á";
    player.shape[0][4][6] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡á";
    player.shape[0][4][7] = "¡¡¡á¡¡¡á¡¡¡¡¡á¡¡";
    player.shape[0][4][8] = "¡á¡¡¡¡¡¡¡¡¡á¡á¡¡";
    player.shape[0][4][9] = "¡¡¡á¡á¡á¡á¡á¡¡¡¡";
    player.shape[0][4][10] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡¡";
    player.shape[0][4][11] = "¡á¡¡¡á¡á¡¡¡á¡¡¡¡";
    player.shape[0][4][12] = "¡¡¡á¡¡¡¡¡á¡¡¡¡¡¡";

    // ÇÁ·¹ÀÓ 5: °È±â ¹Ý´ëÂÊ ¹ß µé±â
    player.shape[0][5][0] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
    player.shape[0][5][1] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";
    player.shape[0][5][2] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][5][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][5][4] = "¡á¡á¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][5][5] = "¡á¡¡¡á¡á¡á¡¡¡¡¡á";
    player.shape[0][5][6] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡á";
    player.shape[0][5][7] = "¡¡¡á¡¡¡á¡¡¡¡¡á¡¡";
    player.shape[0][5][8] = "¡á¡¡¡¡¡¡¡¡¡á¡á¡¡";
    player.shape[0][5][9] = "¡¡¡á¡á¡á¡á¡á¡¡¡¡";
    player.shape[0][5][10] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡¡";
    player.shape[0][5][11] = "¡á¡á¡¡¡á¡¡¡á¡¡¡¡";
    player.shape[0][5][12] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";

    // ÇÁ·¹ÀÓ 6: °È±â ±âº» ÀÚ¼¼·Î º¹±Í
    player.shape[0][6][0] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
    player.shape[0][6][1] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";
    player.shape[0][6][2] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][6][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][6][4] = "¡á¡á¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[0][6][5] = "¡á¡¡¡á¡á¡á¡¡¡¡¡á";
    player.shape[0][6][6] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡á";
    player.shape[0][6][7] = "¡¡¡á¡¡¡á¡¡¡¡¡á¡¡";
    player.shape[0][6][8] = "¡á¡¡¡¡¡¡¡¡¡á¡á¡¡";
    player.shape[0][6][9] = "¡¡¡á¡á¡á¡á¡á¡¡¡¡";
    player.shape[0][6][10] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡¡";
    player.shape[0][6][11] = "¡á¡¡¡á¡á¡¡¡á¡¡¡¡";
    player.shape[0][6][12] = "¡¡¡á¡¡¡¡¡á¡¡¡¡¡¡";

#pragma endregion
#pragma region ¿À¸¥ÂÊ
    // ÇÁ·¹ÀÓ 3: °È±â ÇÑÂÊ ¹ß µé±â
    player.shape[1][3][0] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
    player.shape[1][3][1] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";
    player.shape[1][3][2] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[1][3][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[1][3][4] = "¡á¡¡¡¡¡¡¡¡¡¡¡á¡á";
    player.shape[1][3][5] = "¡á¡¡¡¡¡á¡á¡á¡¡¡á";
    player.shape[1][3][6] = "¡á¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][3][7] = "¡¡¡á¡¡¡¡¡á¡¡¡á¡¡";
    player.shape[1][3][8] = "¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][3][9] = "¡¡¡¡¡á¡á¡á¡á¡á¡¡";
    player.shape[1][3][10] = "¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][3][11] = "¡¡¡¡¡á¡á¡¡¡á¡¡¡á";
    player.shape[1][3][12] = "¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á";

    // ÇÁ·¹ÀÓ 4: °È±â ±âº» ÀÚ¼¼·Î º¹±Í
    player.shape[1][4][0] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
    player.shape[1][4][1] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";
    player.shape[1][4][2] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[1][4][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[1][4][4] = "¡á¡¡¡¡¡¡¡¡¡¡¡á¡á";
    player.shape[1][4][5] = "¡á¡¡¡¡¡á¡á¡á¡¡¡á";
    player.shape[1][4][6] = "¡á¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][4][7] = "¡¡¡á¡¡¡¡¡á¡¡¡á¡¡";
    player.shape[1][4][8] = "¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][4][9] = "¡¡¡¡¡á¡á¡á¡á¡á¡¡";
    player.shape[1][4][10] = "¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][4][11] = "¡¡¡¡¡á¡¡¡á¡á¡¡¡á";
    player.shape[1][4][12] = "¡¡¡¡¡¡¡á¡¡¡¡¡á¡¡";

    // ÇÁ·¹ÀÓ 5: °È±â ¹Ý´ëÂÊ ¹ß µé±â
    player.shape[1][5][0] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
    player.shape[1][5][1] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";
    player.shape[1][5][2] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[1][5][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[1][5][4] = "¡á¡¡¡¡¡¡¡¡¡¡¡á¡á";
    player.shape[1][5][5] = "¡á¡¡¡¡¡á¡á¡á¡¡¡á";
    player.shape[1][5][6] = "¡á¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][5][7] = "¡¡¡á¡¡¡¡¡á¡¡¡á¡¡";
    player.shape[1][5][8] = "¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][5][9] = "¡¡¡¡¡á¡á¡á¡á¡á¡¡";
    player.shape[1][5][10] = "¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][5][11] = "¡¡¡¡¡á¡¡¡á¡¡¡á¡á";
    player.shape[1][5][12] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";

    // ÇÁ·¹ÀÓ 6: °È±â ±âº» ÀÚ¼¼·Î º¹±Í
    player.shape[1][6][0] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
    player.shape[1][6][1] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";
    player.shape[1][6][2] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[1][6][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[1][6][4] = "¡á¡¡¡¡¡¡¡¡¡¡¡á¡á";
    player.shape[1][6][5] = "¡á¡¡¡¡¡á¡á¡á¡¡¡á";
    player.shape[1][6][6] = "¡á¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][6][7] = "¡¡¡á¡¡¡¡¡á¡¡¡á¡¡";
    player.shape[1][6][8] = "¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][6][9] = "¡¡¡¡¡á¡á¡á¡á¡á¡¡";
    player.shape[1][6][10] = "¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á";
    player.shape[1][6][11] = "¡¡¡¡¡á¡¡¡á¡á¡¡¡á";
    player.shape[1][6][12] = "¡¡¡¡¡¡¡á¡¡¡¡¡á¡¡";

#pragma endregion
#pragma region µÚ
    // ÇÁ·¹ÀÓ 3: °È±â ÇÑÂÊ ¹ß µé±â
    player.shape[2][3][0] = "¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡";
    player.shape[2][3][1] = "¡¡¡á¡á¡á¡¡¡¡¡á¡¡";
    player.shape[2][3][2] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][3][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][3][4] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][3][5] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][3][6] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][3][7] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][3][8] = "¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡";
    player.shape[2][3][9] = "¡á¡¡¡á¡á¡á¡á¡¡¡á";
    player.shape[2][3][10] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][3][11] = "¡¡¡á¡¡¡á¡¡¡á¡á¡¡";
    player.shape[2][3][12] = "¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡";

    // ÇÁ·¹ÀÓ 4: °È±â ±âº» ÀÚ¼¼·Î º¹±Í
    player.shape[2][4][0] = "¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡";
    player.shape[2][4][1] = "¡¡¡á¡á¡á¡¡¡¡¡á¡¡";
    player.shape[2][4][2] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][4][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][4][4] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][4][5] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][4][6] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][4][7] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][4][8] = "¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡";
    player.shape[2][4][9] = "¡á¡¡¡á¡á¡á¡á¡¡¡á";
    player.shape[2][4][10] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][4][11] = "¡¡¡á¡¡¡á¡á¡¡¡á¡¡";
    player.shape[2][4][12] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";

    // ÇÁ·¹ÀÓ 5: °È±â ¹Ý´ëÂÊ ¹ß µé±â
    player.shape[2][5][0] = "¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡";
    player.shape[2][5][1] = "¡¡¡á¡á¡á¡¡¡¡¡á¡¡";
    player.shape[2][5][2] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][5][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][5][4] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][5][5] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][5][6] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][5][7] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][5][8] = "¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡";
    player.shape[2][5][9] = "¡á¡¡¡á¡á¡á¡á¡¡¡á";
    player.shape[2][5][10] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][5][11] = "¡¡¡á¡á¡¡¡á¡¡¡á¡¡";
    player.shape[2][5][12] = "¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡";

    // ÇÁ·¹ÀÓ 6: °È±â ±âº» ÀÚ¼¼·Î º¹±Í
    player.shape[2][6][0] = "¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡";
    player.shape[2][6][1] = "¡¡¡á¡á¡á¡¡¡¡¡á¡¡";
    player.shape[2][6][2] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][6][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][6][4] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][6][5] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][6][6] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][6][7] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][6][8] = "¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡";
    player.shape[2][6][9] = "¡á¡¡¡á¡á¡á¡á¡¡¡á";
    player.shape[2][6][10] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[2][6][11] = "¡¡¡á¡¡¡á¡á¡¡¡á¡¡";
    player.shape[2][6][12] = "¡¡¡á¡á¡¡¡¡¡á¡á¡¡";

#pragma endregion
#pragma region ¾Õ
    // ÇÁ·¹ÀÓ 3: °È±â Ã¹ ¹øÂ° Á¢Áö
    player.shape[3][3][0] = "¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡";
    player.shape[3][3][1] = "¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡";
    player.shape[3][3][2] = "¡¡¡á¡¡¡¡¡á¡á¡á¡¡";
    player.shape[3][3][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[3][3][4] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[3][3][5] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡á";
    player.shape[3][3][6] = "¡á¡¡¡á¡á¡á¡¡¡á¡á";
    player.shape[3][3][7] = "¡á¡á¡¡¡¡¡¡¡¡¡á¡á";
    player.shape[3][3][8] = "¡á¡¡¡á¡¡¡¡¡á¡¡¡á";
    player.shape[3][3][9] = "¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡";
    player.shape[3][3][10] = "¡á¡á¡á¡á¡á¡á¡á¡á";
    player.shape[3][3][11] = "¡á¡¡¡¡¡á¡á¡¡¡á¡¡";
    player.shape[3][3][12] = "¡á¡á¡¡¡¡¡¡¡á¡á¡¡";

    // ÇÁ·¹ÀÓ 4: °È±â ÇÑÂÊ ¹ß µé±â
    player.shape[3][4][0] = "¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡";
    player.shape[3][4][1] = "¡¡¡á¡¡¡¡¡á¡á¡á¡¡";
    player.shape[3][4][2] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[3][4][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[3][4][4] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡á";
    player.shape[3][4][5] = "¡á¡¡¡á¡á¡á¡¡¡á¡á";
    player.shape[3][4][6] = "¡á¡á¡¡¡¡¡¡¡¡¡á¡á";
    player.shape[3][4][7] = "¡á¡¡¡á¡¡¡¡¡á¡¡¡á";
    player.shape[3][4][8] = "¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡";
    player.shape[3][4][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
    player.shape[3][4][10] = "¡á¡¡¡¡¡¡¡¡¡¡¡á¡¡";
    player.shape[3][4][11] = "¡¡¡á¡¡¡¡¡á¡á¡á¡¡";
    player.shape[3][4][12] = "¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡";

    // ÇÁ·¹ÀÓ 5: °È±â ¹Ý´ëÂÊ Á¢Áö
    player.shape[3][5][0] = "¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡";
    player.shape[3][5][1] = "¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡";
    player.shape[3][5][2] = "¡¡¡á¡¡¡¡¡á¡á¡á¡¡";
    player.shape[3][5][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[3][5][4] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[3][5][5] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡á";
    player.shape[3][5][6] = "¡á¡¡¡á¡á¡á¡¡¡á¡á";
    player.shape[3][5][7] = "¡á¡á¡¡¡¡¡¡¡¡¡á¡á";
    player.shape[3][5][8] = "¡á¡¡¡á¡¡¡¡¡á¡¡¡á";
    player.shape[3][5][9] = "¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡";
    player.shape[3][5][10] = "¡á¡á¡á¡á¡á¡á¡á¡á";
    player.shape[3][5][11] = "¡¡¡á¡¡¡á¡á¡¡¡¡¡á";
    player.shape[3][5][12] = "¡¡¡á¡á¡¡¡¡¡¡¡á¡á";

    // ÇÁ·¹ÀÓ 6: °È±â ¹Ý´ëÂÊ ¹ß µé±â
    player.shape[3][6][0] = "¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡";
    player.shape[3][6][1] = "¡¡¡á¡¡¡¡¡á¡á¡á¡¡";
    player.shape[3][6][2] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[3][6][3] = "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[3][6][4] = "¡á¡¡¡¡¡¡¡¡¡á¡¡¡á";
    player.shape[3][6][5] = "¡á¡¡¡á¡á¡á¡¡¡á¡á";
    player.shape[3][6][6] = "¡á¡á¡¡¡¡¡¡¡¡¡á¡á";
    player.shape[3][6][7] = "¡á¡¡¡á¡¡¡¡¡á¡¡¡á";
    player.shape[3][6][8] = "¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡";
    player.shape[3][6][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
    player.shape[3][6][10] = "¡¡¡á¡¡¡¡¡¡¡¡¡¡¡á";
    player.shape[3][6][11] = "¡¡¡á¡á¡á¡¡¡¡¡á¡¡";
    player.shape[3][6][12] = "¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡";

#pragma endregion
#pragma endregion
}

void PlayerUpdate()
{


    bool isWalk = false;

    if (GetAsyncKeyState(VK_LEFT))
    {
        player.x--;  
        player.dir = LEFT;

        isWalk = true;
    }
    if (GetAsyncKeyState(VK_RIGHT))
    {
        player.x++;
        player.dir = RIGHT;

        isWalk = true;
    }
    if (GetAsyncKeyState(VK_UP))
    {
        player.y--;
        player.dir = UP;

        isWalk = true;
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        player.y++;
        player.dir = DOWN;

        isWalk = true;
    }

    for (int i = 0; i < 13; i++)
    {
        if (isWalk)
        {
            player.ani = (GetTickCount64() / 250) % 4;
            WriteBuffer(player.x, player.y + i, player.color, player.shape[player.dir][player.ani + 3][i]);
        }
        else
        {
            player.ani = (GetTickCount64() / 250) % 3;
            WriteBuffer(player.x, player.y + i, player.color, player.shape[player.dir][player.ani][i]);
        }
       
    }

}

#pragma endregion

#pragma region Slime
void SlimeInit()
{
    for (int i = 0; i < SlimeCount; i++)
    {
        slimes[i].act = false;
        slimes[i].x = rand() % 120;
        slimes[i].y = rand() % 80;
        slimes[i].color = (Color)(rand() % 7 + 9);
        slimes[i].dir = (Dir)(rand() % 2);

#pragma region ½½¶óÀÓ ÀÌ¹ÌÁöµé
#pragma region ¿ÞÂÊ
        // ÇÁ·¹ÀÓ 0: idle ±âº»
        slimes[i].shape[0][0][0] = "";
        slimes[i].shape[0][0][1] = "";
        slimes[i].shape[0][0][2] = "";
        slimes[i].shape[0][0][3] = "";
        slimes[i].shape[0][0][4] = "";
        slimes[i].shape[0][0][5] = "";
        slimes[i].shape[0][0][6] = "";
        slimes[i].shape[0][0][7] = "¡¡¡¡¡á¡á¡á¡á";
        slimes[i].shape[0][0][8] = "¡¡¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][0][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][0][10] = "¡á¡á¡¡¡á¡á¡á¡á¡á";
        slimes[i].shape[0][0][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][0][12] = "¡¡¡á¡á¡á¡á¡á¡á";

        // ÇÁ·¹ÀÓ 1: idle ¸öÀÌ ÆÛÁü
        slimes[i].shape[0][1][0] = "";
        slimes[i].shape[0][1][1] = "";
        slimes[i].shape[0][1][2] = "";
        slimes[i].shape[0][1][3] = "";
        slimes[i].shape[0][1][4] = "";
        slimes[i].shape[0][1][5] = "";
        slimes[i].shape[0][1][6] = "";
        slimes[i].shape[0][1][7] = "¡¡¡¡¡¡¡á¡á";
        slimes[i].shape[0][1][8] = "¡¡¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][1][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][1][10] = "¡á¡á¡¡¡á¡á¡á¡á¡á";
        slimes[i].shape[0][1][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][1][12] = "¡á¡á¡á¡á¡á¡á¡á¡á";

        // ÇÁ·¹ÀÓ 2: idle »ìÂ¦ ´­¸²
        slimes[i].shape[0][2][0] = "";
        slimes[i].shape[0][2][1] = "";
        slimes[i].shape[0][2][2] = "";
        slimes[i].shape[0][2][3] = "";
        slimes[i].shape[0][2][4] = "";
        slimes[i].shape[0][2][5] = "";
        slimes[i].shape[0][2][6] = "";
        slimes[i].shape[0][2][7] = "";
        slimes[i].shape[0][2][8] = "¡¡¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][2][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][2][10] = "¡á¡á¡¡¡á¡á¡á¡á¡á";
        slimes[i].shape[0][2][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][2][12] = "¡á¡á¡á¡á¡á¡á¡á¡á";

        // ÇÁ·¹ÀÓ 3: ÀÌµ¿ µµ¾à ÁØºñ
        slimes[i].shape[0][3][0] = "";
        slimes[i].shape[0][3][1] = "";
        slimes[i].shape[0][3][2] = "";
        slimes[i].shape[0][3][3] = "";
        slimes[i].shape[0][3][4] = "";
        slimes[i].shape[0][3][5] = "";
        slimes[i].shape[0][3][6] = "";
        slimes[i].shape[0][3][7] = "";
        slimes[i].shape[0][3][8] = "¡¡¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][3][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][3][10] = "¡á¡á¡¡¡á¡á¡á¡á¡á";
        slimes[i].shape[0][3][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][3][12] = "¡á¡á¡á¡á¡á¡á¡á¡á";

        // ÇÁ·¹ÀÓ 4: ÀÌµ¿ ¸öÀ» ´Ã·Á µµ¾à
        slimes[i].shape[0][4][0] = "";
        slimes[i].shape[0][4][1] = "";
        slimes[i].shape[0][4][2] = "";
        slimes[i].shape[0][4][3] = "";
        slimes[i].shape[0][4][4] = "¡¡¡¡¡¡¡á¡á";
        slimes[i].shape[0][4][5] = "¡¡¡¡¡á¡á¡á¡á";
        slimes[i].shape[0][4][6] = "¡¡¡¡¡á¡á¡á¡á";
        slimes[i].shape[0][4][7] = "¡¡¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][4][8] = "¡¡¡á¡¡¡á¡á¡á¡á";
        slimes[i].shape[0][4][9] = "¡¡¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][4][10] = "¡¡¡¡¡á¡á¡á¡á";
        slimes[i].shape[0][4][11] = "¡¡¡¡¡á¡á¡á¡á";
        slimes[i].shape[0][4][12] = "";

        // ÇÁ·¹ÀÓ 5: ÀÌµ¿ °øÁß
        slimes[i].shape[0][5][0] = "";
        slimes[i].shape[0][5][1] = "";
        slimes[i].shape[0][5][2] = "";
        slimes[i].shape[0][5][3] = "¡¡¡¡¡á¡á¡á¡á";
        slimes[i].shape[0][5][4] = "¡¡¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][5][5] = "¡¡¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][5][6] = "¡á¡á¡¡¡á¡á¡á¡á¡á";
        slimes[i].shape[0][5][7] = "¡¡¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][5][8] = "¡¡¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][5][9] = "¡¡¡¡¡á¡á¡á¡á";
        slimes[i].shape[0][5][10] = "";
        slimes[i].shape[0][5][11] = "";
        slimes[i].shape[0][5][12] = "";

        // ÇÁ·¹ÀÓ 6: ÀÌµ¿ ÂøÁö: ±âº» ÀÚ¼¼·Î º¹±Í
        slimes[i].shape[0][6][0] = "";
        slimes[i].shape[0][6][1] = "";
        slimes[i].shape[0][6][2] = "";
        slimes[i].shape[0][6][3] = "";
        slimes[i].shape[0][6][4] = "";
        slimes[i].shape[0][6][5] = "";
        slimes[i].shape[0][6][6] = "";
        slimes[i].shape[0][6][7] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[0][6][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[0][6][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][6][10] = "¡á¡á¡¡¡á¡á¡á¡á¡á";
        slimes[i].shape[0][6][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[0][6][12] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";

#pragma endregion

#pragma region ¿À¸¥ÂÊ
        // ÇÁ·¹ÀÓ 0: idle ±âº»
        slimes[i].shape[1][0][0] = "";
        slimes[i].shape[1][0][1] = "";
        slimes[i].shape[1][0][2] = "";
        slimes[i].shape[1][0][3] = "";
        slimes[i].shape[1][0][4] = "";
        slimes[i].shape[1][0][5] = "";
        slimes[i].shape[1][0][6] = "";
        slimes[i].shape[1][0][7] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[1][0][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[1][0][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[1][0][10] = "¡á¡á¡á¡á¡á¡¡¡á¡á";
        slimes[i].shape[1][0][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[1][0][12] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";

        // ÇÁ·¹ÀÓ 1: idle ¸öÀÌ ÆÛÁü
        slimes[i].shape[1][1][0] = "";
        slimes[i].shape[1][1][1] = "";
        slimes[i].shape[1][1][2] = "";
        slimes[i].shape[1][1][3] = "";
        slimes[i].shape[1][1][4] = "";
        slimes[i].shape[1][1][5] = "";
        slimes[i].shape[1][1][6] = "";
        slimes[i].shape[1][1][7] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
        slimes[i].shape[1][1][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[1][1][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[1][1][10] = "¡á¡á¡á¡á¡á¡¡¡á¡á";
        slimes[i].shape[1][1][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[1][1][12] = "¡á¡á¡á¡á¡á¡á¡á¡á";

        // ÇÁ·¹ÀÓ 2: idle »ìÂ¦ ´­¸²
        slimes[i].shape[1][2][0] = "";
        slimes[i].shape[1][2][1] = "";
        slimes[i].shape[1][2][2] = "";
        slimes[i].shape[1][2][3] = "";
        slimes[i].shape[1][2][4] = "";
        slimes[i].shape[1][2][5] = "";
        slimes[i].shape[1][2][6] = "";
        slimes[i].shape[1][2][7] = "";
        slimes[i].shape[1][2][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[1][2][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[1][2][10] = "¡á¡á¡á¡á¡á¡¡¡á¡á";
        slimes[i].shape[1][2][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[1][2][12] = "¡á¡á¡á¡á¡á¡á¡á¡á";

        // ÇÁ·¹ÀÓ 3: ÀÌµ¿ µµ¾à ÁØºñ
        slimes[i].shape[1][3][0] = "";
        slimes[i].shape[1][3][1] = "";
        slimes[i].shape[1][3][2] = "";
        slimes[i].shape[1][3][3] = "";
        slimes[i].shape[1][3][4] = "";
        slimes[i].shape[1][3][5] = "";
        slimes[i].shape[1][3][6] = "";
        slimes[i].shape[1][3][7] = "";
        slimes[i].shape[1][3][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[1][3][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[1][3][10] = "¡á¡á¡á¡á¡á¡¡¡á¡á";
        slimes[i].shape[1][3][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[1][3][12] = "¡á¡á¡á¡á¡á¡á¡á¡á";

        // ÇÁ·¹ÀÓ 4: ÀÌµ¿ ¸öÀ» ´Ã·Á µµ¾à
        slimes[i].shape[1][4][0] = "";
        slimes[i].shape[1][4][1] = "";
        slimes[i].shape[1][4][2] = "";
        slimes[i].shape[1][4][3] = "";
        slimes[i].shape[1][4][4] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
        slimes[i].shape[1][4][5] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[1][4][6] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[1][4][7] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[1][4][8] = "¡¡¡á¡á¡á¡á¡¡¡á¡¡";
        slimes[i].shape[1][4][9] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[1][4][10] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[1][4][11] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[1][4][12] = "";

        // ÇÁ·¹ÀÓ 5: ÀÌµ¿ °øÁß
        slimes[i].shape[1][5][0] = "";
        slimes[i].shape[1][5][1] = "";
        slimes[i].shape[1][5][2] = "";
        slimes[i].shape[1][5][3] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[1][5][4] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[1][5][5] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[1][5][6] = "¡á¡á¡á¡á¡á¡¡¡á¡á";
        slimes[i].shape[1][5][7] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[1][5][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[1][5][9] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[1][5][10] = "";
        slimes[i].shape[1][5][11] = "";
        slimes[i].shape[1][5][12] = "";

        // ÇÁ·¹ÀÓ 6: ÀÌµ¿ ÂøÁö: ±âº» ÀÚ¼¼·Î º¹±Í
        slimes[i].shape[1][6][0] = "";
        slimes[i].shape[1][6][1] = "";
        slimes[i].shape[1][6][2] = "";
        slimes[i].shape[1][6][3] = "";
        slimes[i].shape[1][6][4] = "";
        slimes[i].shape[1][6][5] = "";
        slimes[i].shape[1][6][6] = "";
        slimes[i].shape[1][6][7] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[1][6][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[1][6][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[1][6][10] = "¡á¡á¡á¡á¡á¡¡¡á¡á";
        slimes[i].shape[1][6][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[1][6][12] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";

#pragma endregion

#pragma region µÚ
        // ÇÁ·¹ÀÓ 0: idle ±âº»
        slimes[i].shape[2][0][0] = "";
        slimes[i].shape[2][0][1] = "";
        slimes[i].shape[2][0][2] = "";
        slimes[i].shape[2][0][3] = "";
        slimes[i].shape[2][0][4] = "";
        slimes[i].shape[2][0][5] = "";
        slimes[i].shape[2][0][6] = "";
        slimes[i].shape[2][0][7] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[2][0][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[2][0][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[2][0][10] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[2][0][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[2][0][12] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";

        // ÇÁ·¹ÀÓ 1: idle ¸öÀÌ ÆÛÁü
        slimes[i].shape[2][1][0] = "";
        slimes[i].shape[2][1][1] = "";
        slimes[i].shape[2][1][2] = "";
        slimes[i].shape[2][1][3] = "";
        slimes[i].shape[2][1][4] = "";
        slimes[i].shape[2][1][5] = "";
        slimes[i].shape[2][1][6] = "";
        slimes[i].shape[2][1][7] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
        slimes[i].shape[2][1][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[2][1][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[2][1][10] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[2][1][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[2][1][12] = "¡á¡á¡á¡á¡á¡á¡á¡á";

        // ÇÁ·¹ÀÓ 2: idle »ìÂ¦ ´­¸²
        slimes[i].shape[2][2][0] = "";
        slimes[i].shape[2][2][1] = "";
        slimes[i].shape[2][2][2] = "";
        slimes[i].shape[2][2][3] = "";
        slimes[i].shape[2][2][4] = "";
        slimes[i].shape[2][2][5] = "";
        slimes[i].shape[2][2][6] = "";
        slimes[i].shape[2][2][7] = "";
        slimes[i].shape[2][2][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[2][2][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[2][2][10] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[2][2][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[2][2][12] = "¡á¡á¡á¡á¡á¡á¡á¡á";

        // ÇÁ·¹ÀÓ 3: ÀÌµ¿ µµ¾à ÁØºñ
        slimes[i].shape[2][3][0] = "";
        slimes[i].shape[2][3][1] = "";
        slimes[i].shape[2][3][2] = "";
        slimes[i].shape[2][3][3] = "";
        slimes[i].shape[2][3][4] = "";
        slimes[i].shape[2][3][5] = "";
        slimes[i].shape[2][3][6] = "";
        slimes[i].shape[2][3][7] = "";
        slimes[i].shape[2][3][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[2][3][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[2][3][10] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[2][3][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[2][3][12] = "¡á¡á¡á¡á¡á¡á¡á¡á";

        // ÇÁ·¹ÀÓ 4: ÀÌµ¿ ¸öÀ» ´Ã·Á µµ¾à
        slimes[i].shape[2][4][0] = "";
        slimes[i].shape[2][4][1] = "";
        slimes[i].shape[2][4][2] = "";
        slimes[i].shape[2][4][3] = "";
        slimes[i].shape[2][4][4] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
        slimes[i].shape[2][4][5] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[2][4][6] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[2][4][7] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[2][4][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[2][4][9] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[2][4][10] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[2][4][11] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[2][4][12] = "";

        // ÇÁ·¹ÀÓ 5: ÀÌµ¿ °øÁß
        slimes[i].shape[2][5][0] = "";
        slimes[i].shape[2][5][1] = "";
        slimes[i].shape[2][5][2] = "";
        slimes[i].shape[2][5][3] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[2][5][4] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[2][5][5] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[2][5][6] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[2][5][7] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[2][5][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[2][5][9] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[2][5][10] = "";
        slimes[i].shape[2][5][11] = "";
        slimes[i].shape[2][5][12] = "";

        // ÇÁ·¹ÀÓ 6: ÀÌµ¿ ÂøÁö: ±âº» ÀÚ¼¼·Î º¹±Í
        slimes[i].shape[2][6][0] = "";
        slimes[i].shape[2][6][1] = "";
        slimes[i].shape[2][6][2] = "";
        slimes[i].shape[2][6][3] = "";
        slimes[i].shape[2][6][4] = "";
        slimes[i].shape[2][6][5] = "";
        slimes[i].shape[2][6][6] = "";
        slimes[i].shape[2][6][7] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[2][6][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[2][6][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[2][6][10] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[2][6][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[2][6][12] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";

#pragma endregion

#pragma region ¾Õ
        // ÇÁ·¹ÀÓ 0: idle ±âº»
        slimes[i].shape[3][0][0] = "";
        slimes[i].shape[3][0][1] = "";
        slimes[i].shape[3][0][2] = "";
        slimes[i].shape[3][0][3] = "";
        slimes[i].shape[3][0][4] = "";
        slimes[i].shape[3][0][5] = "";
        slimes[i].shape[3][0][6] = "";
        slimes[i].shape[3][0][7] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[3][0][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[3][0][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[3][0][10] = "¡á¡á¡¡¡á¡á¡¡¡á¡á";
        slimes[i].shape[3][0][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[3][0][12] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";

        // ÇÁ·¹ÀÓ 1: idle ¸öÀÌ ÆÛÁü
        slimes[i].shape[3][1][0] = "";
        slimes[i].shape[3][1][1] = "";
        slimes[i].shape[3][1][2] = "";
        slimes[i].shape[3][1][3] = "";
        slimes[i].shape[3][1][4] = "";
        slimes[i].shape[3][1][5] = "";
        slimes[i].shape[3][1][6] = "";
        slimes[i].shape[3][1][7] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
        slimes[i].shape[3][1][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[3][1][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[3][1][10] = "¡á¡á¡¡¡á¡á¡¡¡á¡á";
        slimes[i].shape[3][1][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[3][1][12] = "¡á¡á¡á¡á¡á¡á¡á¡á";

        // ÇÁ·¹ÀÓ 2: idle »ìÂ¦ ´­¸²
        slimes[i].shape[3][2][0] = "";
        slimes[i].shape[3][2][1] = "";
        slimes[i].shape[3][2][2] = "";
        slimes[i].shape[3][2][3] = "";
        slimes[i].shape[3][2][4] = "";
        slimes[i].shape[3][2][5] = "";
        slimes[i].shape[3][2][6] = "";
        slimes[i].shape[3][2][7] = "";
        slimes[i].shape[3][2][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[3][2][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[3][2][10] = "¡á¡á¡¡¡á¡á¡¡¡á¡á";
        slimes[i].shape[3][2][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[3][2][12] = "¡á¡á¡á¡á¡á¡á¡á¡á";

        // ÇÁ·¹ÀÓ 3: ÀÌµ¿ µµ¾à ÁØºñ
        slimes[i].shape[3][3][0] = "";
        slimes[i].shape[3][3][1] = "";
        slimes[i].shape[3][3][2] = "";
        slimes[i].shape[3][3][3] = "";
        slimes[i].shape[3][3][4] = "";
        slimes[i].shape[3][3][5] = "";
        slimes[i].shape[3][3][6] = "";
        slimes[i].shape[3][3][7] = "";
        slimes[i].shape[3][3][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[3][3][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[3][3][10] = "¡á¡á¡¡¡á¡á¡¡¡á¡á";
        slimes[i].shape[3][3][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[3][3][12] = "¡á¡á¡á¡á¡á¡á¡á¡á";

        // ÇÁ·¹ÀÓ 4: ÀÌµ¿ ¸öÀ» ´Ã·Á µµ¾à
        slimes[i].shape[3][4][0] = "";
        slimes[i].shape[3][4][1] = "";
        slimes[i].shape[3][4][2] = "";
        slimes[i].shape[3][4][3] = "";
        slimes[i].shape[3][4][4] = "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
        slimes[i].shape[3][4][5] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[3][4][6] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[3][4][7] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[3][4][8] = "¡¡¡á¡¡¡á¡á¡¡¡á¡¡";
        slimes[i].shape[3][4][9] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[3][4][10] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[3][4][11] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[3][4][12] = "";

        // ÇÁ·¹ÀÓ 5: ÀÌµ¿ °øÁß
        slimes[i].shape[3][5][0] = "";
        slimes[i].shape[3][5][1] = "";
        slimes[i].shape[3][5][2] = "";
        slimes[i].shape[3][5][3] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[3][5][4] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[3][5][5] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[3][5][6] = "¡á¡á¡¡¡á¡á¡¡¡á¡á";
        slimes[i].shape[3][5][7] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[3][5][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[3][5][9] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[3][5][10] = "";
        slimes[i].shape[3][5][11] = "";
        slimes[i].shape[3][5][12] = "";

        // ÇÁ·¹ÀÓ 6: ÀÌµ¿ ÂøÁö: ±âº» ÀÚ¼¼·Î º¹±Í
        slimes[i].shape[3][6][0] = "";
        slimes[i].shape[3][6][1] = "";
        slimes[i].shape[3][6][2] = "";
        slimes[i].shape[3][6][3] = "";
        slimes[i].shape[3][6][4] = "";
        slimes[i].shape[3][6][5] = "";
        slimes[i].shape[3][6][6] = "";
        slimes[i].shape[3][6][7] = "¡¡¡¡¡á¡á¡á¡á¡¡¡¡";
        slimes[i].shape[3][6][8] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";
        slimes[i].shape[3][6][9] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[3][6][10] = "¡á¡á¡¡¡á¡á¡¡¡á¡á";
        slimes[i].shape[3][6][11] = "¡á¡á¡á¡á¡á¡á¡á¡á";
        slimes[i].shape[3][6][12] = "¡¡¡á¡á¡á¡á¡á¡á¡¡";

#pragma endregion
#pragma endregion
    }

}


int slimeTime = 0;
int spawnTime = 0;
int maxSpawnTime = rand() % 50;

void SlimeUpdate()
{
    slimeTime++;
    if (slimeTime > 2)
    {

        spawnTime++;

        if (spawnTime > maxSpawnTime)
        {
            for (int i = 0; i < SlimeCount; i++)
            {
                if (slimes[i].act == false)
                {
                    slimes[i].act = true;
                    slimes[i].x = rand() % 120;
                    slimes[i].y = rand() % 80;
                    slimes[i].color = (Color)(rand() % 7 + 9);
                    slimes[i].dir = (Dir)(rand() % 2);
                    break;
                }
            }
            maxSpawnTime = rand() % 50;
            spawnTime = 0;
        }
      


        for (int i = 0; i < SlimeCount; i++)
        {

            if (slimes[i].act)
            {

                if (slimes[i].dir == LEFT && slimes[i].x <= 0)
                {
                    slimes[i].dir = RIGHT;
                }


                if (slimes[i].dir == RIGHT && slimes[i].x >= 142)
                {
                    slimes[i].dir = LEFT;
                }

                switch (slimes[i].dir)
                {
                case LEFT:
                    slimes[i].x--;
                    break;
                case RIGHT:
                    slimes[i].x++;
                    break;

                default:
                    break;
                }
            }
          
        }
        slimeTime = 0;
    }

   
    bool isWalk = true;


    for (int i = 0; i < SlimeCount; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            if (slimes[i].act)
            {

                if (isWalk)
                {
                    slimes[i].ani = (GetTickCount64() / 250) % 4;
                    WriteBuffer(slimes[i].x, slimes[i].y + j, slimes[i].color, slimes[i].shape[slimes[i].dir][slimes[i].ani + 3][j]);
                }
                else
                {
                    slimes[i].ani = (GetTickCount64() / 250) % 3;
                    WriteBuffer(slimes[i].x, slimes[i].y + j, slimes[i].color, slimes[i].shape[slimes[i].dir][slimes[i].ani][j]);
                }
            }

        }


        if (slimes[i].x < player.x + 8     &&
            player.x    < slimes[i].x + 8  &&
            slimes[i].y + 4 < player.y + 13    &&
            player.y    < slimes[i].y + 13)
        {
            slimes[i].act = false;
        }
    }

   
}

#pragma endregion




#pragma region ´õºí¹öÆÛ


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
    SetConsoleTextAttribute(hBuffer[screenIndex], color);

    COORD pos{ x * 2, y };
    SetConsoleCursorPosition(hBuffer[screenIndex], pos);

    DWORD dw;
    WriteFile(hBuffer[screenIndex], shape, strlen(shape), &dw, NULL);

}

#pragma endregion
