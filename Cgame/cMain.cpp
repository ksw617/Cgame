#include <stdio.h>
#include <Windows.h>

#define ENEMY_COUNT 3

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

struct Obj
{
    DIR dir;
    int step;
    int maxStep;
    int x;
    int y;
    Color color;
    const char* shape[4][13];
};

void SetColor(int color);
void SetPosition(int x, int y);
void HideCursor();

Obj player;
Obj enemies[ENEMY_COUNT];
void Init();
void Update();


int main()
{

    Init();
    HideCursor();

    while (true)
    {
        system("cls");

        Update();

        Sleep(1);
    }

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


    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        enemies[i].dir = (DIR)(rand () % 4);
        enemies[i].x = rand() % (150 - 8);
        enemies[i].y = rand() % 87;
        enemies[i].color = LIGHT_WHITE;

        enemies[i].step = 0;
        enemies[i].maxStep = rand() % 10 + 5;

        // 왼쪽 모습
        enemies[i].shape[0][0] = "　　■■　　　　";
        enemies[i].shape[0][1] = "　■　　■■■　";
        enemies[i].shape[0][2] = "　■　　　　　■";
        enemies[i].shape[0][3] = "　■　■　　　■";
        enemies[i].shape[0][4] = "■■　　　　　■";
        enemies[i].shape[0][5] = "■　　　　　　■";
        enemies[i].shape[0][6] = "　■■■■■■　";
        enemies[i].shape[0][7] = "　　■　　■　　";
        enemies[i].shape[0][8] = "　■　　　　■　";
        enemies[i].shape[0][9] = "■　■　　　■■";
        enemies[i].shape[0][10] = "　■　　　　■　";
        enemies[i].shape[0][11] = "　　■　■　■　";
        enemies[i].shape[0][12] = "　■■　■■　　";

        // 오른쪽 모습
        enemies[i].shape[1][0] = "　　　　■■　　";
        enemies[i].shape[1][1] = "　■■■　　■　";
        enemies[i].shape[1][2] = "■　　　　　■　";
        enemies[i].shape[1][3] = "■　　　■　■　";
        enemies[i].shape[1][4] = "■　　　　　■■";
        enemies[i].shape[1][5] = "■　　　　　　■";
        enemies[i].shape[1][6] = "　■■■■■■　";
        enemies[i].shape[1][7] = "　　■　　■　　";
        enemies[i].shape[1][8] = "　■　　　　■　";
        enemies[i].shape[1][9] = "■■　　　■　■";
        enemies[i].shape[1][10] = "　■　　　　■　";
        enemies[i].shape[1][11] = "　■　■　■　　";
        enemies[i].shape[1][12] = "　　■■　■■　";

        // 뒷모습
        enemies[i].shape[2][0] = "　■■　　■■　";
        enemies[i].shape[2][1] = "■　　■■　　■";
        enemies[i].shape[2][2] = "■　　　　　　■";
        enemies[i].shape[2][3] = "■　　　　　　■";
        enemies[i].shape[2][4] = "■　　　　　　■";
        enemies[i].shape[2][5] = "　■　　　　■　";
        enemies[i].shape[2][6] = "　　■■■■　　";
        enemies[i].shape[2][7] = "　■　　　　■　";
        enemies[i].shape[2][8] = "■　　　　　　■";
        enemies[i].shape[2][9] = "■■　■■　■■";
        enemies[i].shape[2][10] = "　■　　　　■　";
        enemies[i].shape[2][11] = "　■　■■　■　";
        enemies[i].shape[2][12] = "　■■　　■■　";

        // 앞모습
        enemies[i].shape[3][0] = "　■■　　■■　";
        enemies[i].shape[3][1] = "■　　■■　　■";
        enemies[i].shape[3][2] = "■　　　　　　■";
        enemies[i].shape[3][3] = "■　■　　■　■";
        enemies[i].shape[3][4] = "■　　■■　　■";
        enemies[i].shape[3][5] = "　■　　　　■　";
        enemies[i].shape[3][6] = "　　■■■■　　";
        enemies[i].shape[3][7] = "　■　　　　■　";
        enemies[i].shape[3][8] = "■　　　　　　■";
        enemies[i].shape[3][9] = "■■　　　　■■";
        enemies[i].shape[3][10] = "　■　　　　■　";
        enemies[i].shape[3][11] = "　■　■■　■　";
        enemies[i].shape[3][12] = "　■■　　■■　";
    }
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

    SetColor(player.color);
    for (int i = 0; i < 13; i++)
    {
        SetPosition(player.x, player.y + i);
        printf(player.shape[(int)player.dir][i]);
    }


    for (int i = 0; i < ENEMY_COUNT; i++)
    {

        enemies[i].step++;

        //step이 다 되었을 경우
        if (enemies[i].step > enemies[i].maxStep)
        {
            enemies[i].step = 0;
            enemies[i].maxStep = rand() % 10 + 5;
            enemies[i].dir = (DIR)(rand() % 4);
        }

        switch (enemies[i].dir)
        {
        case LEFT:
            enemies[i].x--;
            break;
        case RIGHT:
            enemies[i].x++;
            break;
        case UP:
            enemies[i].y--;
            break;
        case DOWN:
            enemies[i].y++;
            break;
        default:
            break;
        }

        //충돌되었을 경우
        if (enemies[i].x < 0 || enemies[i].y < 0 || enemies[i].x > 142 || enemies[i].y > 82)
        {
            switch (enemies[i].dir)
            {
            case LEFT:
                enemies[i].x++;
                break;
            case RIGHT:
                enemies[i].x--;
                break;
            case UP:
                enemies[i].y++;
                break;
            case DOWN:
                enemies[i].y--;
                break;
            default:
                break;
            }

            enemies[i].step = 0;
            enemies[i].maxStep = rand() % 10 + 5;
            enemies[i].dir = (DIR)(rand() % 4);
        }

        
    }


    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        SetColor(enemies[i].color);
        for (int j = 0; j < 13; j++)
        {
            SetPosition(enemies[i].x, enemies[i].y + j);
            printf(enemies[i].shape[(int)enemies[i].dir][j]);
        }


    }
}




void SetColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void SetPosition(int x, int y)
{
    COORD pos{ x * 2, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void HideCursor()
{
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}