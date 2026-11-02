#include <stdio.h>
#include <Windows.h>

enum SCENE_ID
{
    LOGO,
    MENU,
    STAGE,
};

SCENE_ID sceneID = LOGO;
int aniIndex = 0;
const char* logoImg[6][13] = {};

void SetPosition(int x, int y)
{
    COORD pos{ x * 2, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void LogoInit();
void LogoUpdate();

void MenuInit();
void MenuUpdate();

void StageInit();
void StageUpdate();

void GameInit();
void GameUpdate();


int main()
{
    GameInit();

    while (true)
    {
        system("cls");

        GameUpdate();

        Sleep(50);
    }

    return 0;
}



void LogoInit()
{
    logoImg[0][0] = "  ^                      *                                      ^  ";
    logoImg[0][1] = " /|\\                    ---====[<>]====---                     /|\\ ";
    logoImg[0][2] = " |*|                                     .                     ||| ";
    logoImg[0][3] = " |||                 --[ THE LOST KINGDOM ]--                  ||| ";
    logoImg[0][4] = " ||| @@@@  @   @ @   @ @@@@@     @@@@  @      @@@  @@@@  @@@@@ ||| ";
    logoImg[0][5] = " ||| @   @ @   @ @@  @ @         @   @ @     @   @ @   @ @     ||| ";
    logoImg[0][6] = " ||| @@@@  @   @ @ @ @ @@@@      @@@@  @     @@@@@ @   @ @@@@  |*| ";
    logoImg[0][7] = " ||| @  @  @   @ @  @@ @         @   @ @     @   @ @   @ @     ||| ";
    logoImg[0][8] = " ||| @   @  @@@  @   @ @@@@@     @@@@  @@@@@ @   @ @@@@  @@@@@ ||| ";
    logoImg[0][9] = "=|O|=      =============================================      =|O|=";
    logoImg[0][10] = "  |                                                             |  ";
    logoImg[0][11] = "  o             O A T H   O F   T H E   F A L L E N             o  ";
    logoImg[0][12] = "                ----------<====[ * ]====>----------                ";

    logoImg[1][0] = "  ^                              *                              ^  ";
    logoImg[1][1] = " /|\\                    ---====[<>]====---                     /|\\ ";
    logoImg[1][2] = " |||                             .                             ||| ";
    logoImg[1][3] = " |*|                 --[ THE LOST KINGDOM ]--                  ||| ";
    logoImg[1][4] = " ||| @@@@  @   @ @   @ @@@@@     @@@@  @      @@@  @@@@  @@@@@ ||| ";
    logoImg[1][5] = " ||| @   @ @   @ @@  @ @         @   @ @     @   @ @   @ @     |*| ";
    logoImg[1][6] = " ||| @@@@  @   @ @ @ @ @@@@      @@@@  @     @@@@@ @   @ @@@@  ||| ";
    logoImg[1][7] = " ||| @  @  @   @ @  @@ @         @   @ @     @   @ @   @ @     ||| ";
    logoImg[1][8] = " ||| @   @  @@@  @   @ @@@@@     @@@@  @@@@@ @   @ @@@@  @@@@@ ||| ";
    logoImg[1][9] = "=|O|=      =============================================      =|O|=";
    logoImg[1][10] = "  |                                                             |  ";
    logoImg[1][11] = "  o             O A T H   O F   T H E   F A L L E N             o  ";
    logoImg[1][12] = "                ----------<====[ * ]====>----------                ";

    logoImg[2][0] = "  ^                                      *                      ^  ";
    logoImg[2][1] = " /|\\                    ---====[<>]====---                     /|\\ ";
    logoImg[2][2] = " |||                     .                                     ||| ";
    logoImg[2][3] = " |||                 --[ THE LOST KINGDOM ]--                  ||| ";
    logoImg[2][4] = " |*| @@@@  @   @ @   @ @@@@@     @@@@  @      @@@  @@@@  @@@@@ |*| ";
    logoImg[2][5] = " ||| @   @ @   @ @@  @ @         @   @ @     @   @ @   @ @     ||| ";
    logoImg[2][6] = " ||| @@@@  @   @ @ @ @ @@@@      @@@@  @     @@@@@ @   @ @@@@  ||| ";
    logoImg[2][7] = " ||| @  @  @   @ @  @@ @         @   @ @     @   @ @   @ @     ||| ";
    logoImg[2][8] = " ||| @   @  @@@  @   @ @@@@@     @@@@  @@@@@ @   @ @@@@  @@@@@ ||| ";
    logoImg[2][9] = "=|O|=      =============================================      =|O|=";
    logoImg[2][10] = "  |                                                             |  ";
    logoImg[2][11] = "  o             O A T H   O F   T H E   F A L L E N             o  ";
    logoImg[2][12] = "                ----------<====[ * ]====>----------                ";

    logoImg[3][0] = "  ^                                                             ^  ";
    logoImg[3][1] = " /|\\                  . ---====[<>]====---  *                  /|\\ ";
    logoImg[3][2] = " |||                                                           ||| ";
    logoImg[3][3] = " |||                 --[ THE LOST KINGDOM ]--                  |*| ";
    logoImg[3][4] = " ||| @@@@  @   @ @   @ @@@@@     @@@@  @      @@@  @@@@  @@@@@ ||| ";
    logoImg[3][5] = " |*| @   @ @   @ @@  @ @         @   @ @     @   @ @   @ @     ||| ";
    logoImg[3][6] = " ||| @@@@  @   @ @ @ @ @@@@      @@@@  @     @@@@@ @   @ @@@@  ||| ";
    logoImg[3][7] = " ||| @  @  @   @ @  @@ @         @   @ @     @   @ @   @ @     ||| ";
    logoImg[3][8] = " ||| @   @  @@@  @   @ @@@@@     @@@@  @@@@@ @   @ @@@@  @@@@@ ||| ";
    logoImg[3][9] = "=|O|=      =============================================      =|O|=";
    logoImg[3][10] = "  |                                                             |  ";
    logoImg[3][11] = "  o             O A T H   O F   T H E   F A L L E N             o  ";
    logoImg[3][12] = "                ----------<====[ * ]====>----------                ";

    logoImg[4][0] = "  ^                      .                                      ^  ";
    logoImg[4][1] = " /|\\                    ---====[<>]====---                     /|\\ ";
    logoImg[4][2] = " |||                                     *                     |*| ";
    logoImg[4][3] = " |||                 --[ THE LOST KINGDOM ]--                  ||| ";
    logoImg[4][4] = " ||| @@@@  @   @ @   @ @@@@@     @@@@  @      @@@  @@@@  @@@@@ ||| ";
    logoImg[4][5] = " ||| @   @ @   @ @@  @ @         @   @ @     @   @ @   @ @     ||| ";
    logoImg[4][6] = " |*| @@@@  @   @ @ @ @ @@@@      @@@@  @     @@@@@ @   @ @@@@  ||| ";
    logoImg[4][7] = " ||| @  @  @   @ @  @@ @         @   @ @     @   @ @   @ @     ||| ";
    logoImg[4][8] = " ||| @   @  @@@  @   @ @@@@@     @@@@  @@@@@ @   @ @@@@  @@@@@ ||| ";
    logoImg[4][9] = "=|O|=      =============================================      =|O|=";
    logoImg[4][10] = "  |                                                             |  ";
    logoImg[4][11] = "  o             O A T H   O F   T H E   F A L L E N             o  ";
    logoImg[4][12] = "                ----------<====[ * ]====>----------                ";

    logoImg[5][0] = "  ^                              .                              ^  ";
    logoImg[5][1] = " /|\\                    ---====[<>]====---                     /|\\ ";
    logoImg[5][2] = " |||                             *                             ||| ";
    logoImg[5][3] = " |||                 --[ THE LOST KINGDOM ]--                  |*| ";
    logoImg[5][4] = " ||| @@@@  @   @ @   @ @@@@@     @@@@  @      @@@  @@@@  @@@@@ ||| ";
    logoImg[5][5] = " |*| @   @ @   @ @@  @ @         @   @ @     @   @ @   @ @     ||| ";
    logoImg[5][6] = " ||| @@@@  @   @ @ @ @ @@@@      @@@@  @     @@@@@ @   @ @@@@  ||| ";
    logoImg[5][7] = " ||| @  @  @   @ @  @@ @         @   @ @     @   @ @   @ @     ||| ";
    logoImg[5][8] = " ||| @   @  @@@  @   @ @@@@@     @@@@  @@@@@ @   @ @@@@  @@@@@ ||| ";
    logoImg[5][9] = "=|O|=      =============================================      =|O|=";
    logoImg[5][10] = "  |                                                             |  ";
    logoImg[5][11] = "  o             O A T H   O F   T H E   F A L L E N             o  ";
    logoImg[5][12] = "                ----------<====[ * ]====>----------                ";

    logoImg[6][0] = "  ^                                      .                      ^  ";
    logoImg[6][1] = " /|\\                    ---====[<>]====---                     /|\\ ";
    logoImg[6][2] = " |||                     *                                     ||| ";
    logoImg[6][3] = " |||                 --[ THE LOST KINGDOM ]--                  ||| ";
    logoImg[6][4] = " |*| @@@@  @   @ @   @ @@@@@     @@@@  @      @@@  @@@@  @@@@@ |*| ";
    logoImg[6][5] = " ||| @   @ @   @ @@  @ @         @   @ @     @   @ @   @ @     ||| ";
    logoImg[6][6] = " ||| @@@@  @   @ @ @ @ @@@@      @@@@  @     @@@@@ @   @ @@@@  ||| ";
    logoImg[6][7] = " ||| @  @  @   @ @  @@ @         @   @ @     @   @ @   @ @     ||| ";
    logoImg[6][8] = " ||| @   @  @@@  @   @ @@@@@     @@@@  @@@@@ @   @ @@@@  @@@@@ ||| ";
    logoImg[6][9] = "=|O|=      =============================================      =|O|=";
    logoImg[6][10] = "  |                                                             |  ";
    logoImg[6][11] = "  o             O A T H   O F   T H E   F A L L E N             o  ";
    logoImg[6][12] = "                ----------<====[ * ]====>----------                ";

    logoImg[7][0] = "  ^                                                             ^  ";
    logoImg[7][1] = " /|\\                  * ---====[<>]====---  .                  /|\\ ";
    logoImg[7][2] = " |||                                                           ||| ";
    logoImg[7][3] = " |*|                 --[ THE LOST KINGDOM ]--                  ||| ";
    logoImg[7][4] = " ||| @@@@  @   @ @   @ @@@@@     @@@@  @      @@@  @@@@  @@@@@ ||| ";
    logoImg[7][5] = " ||| @   @ @   @ @@  @ @         @   @ @     @   @ @   @ @     |*| ";
    logoImg[7][6] = " ||| @@@@  @   @ @ @ @ @@@@      @@@@  @     @@@@@ @   @ @@@@  ||| ";
    logoImg[7][7] = " ||| @  @  @   @ @  @@ @         @   @ @     @   @ @   @ @     ||| ";
    logoImg[7][8] = " ||| @   @  @@@  @   @ @@@@@     @@@@  @@@@@ @   @ @@@@  @@@@@ ||| ";
    logoImg[7][9] = "=|O|=      =============================================      =|O|=";
    logoImg[7][10] = "  |                                                             |  ";
    logoImg[7][11] = "  o             O A T H   O F   T H E   F A L L E N             o  ";
    logoImg[7][12] = "                ----------<====[ * ]====>----------                ";

}

void LogoUpdate()
{
    aniIndex++;

    if (aniIndex > 5)
    {
        aniIndex = 0;
    }
    
    for (int i = 0; i < 13; i++)
    {
        SetPosition(3, 4 + i);
        printf(logoImg[aniIndex][i]);
    }

    if (GetAsyncKeyState(VK_RETURN))
    {
        sceneID = MENU;
        MenuInit();
    }
}

void MenuInit()
{

}

void MenuUpdate()
{
    printf("MENU");
    if (GetAsyncKeyState(VK_RETURN))
    {
        sceneID = STAGE;
        StageInit();
    }
}

void StageInit()
{

}

void StageUpdate()
{
    printf("STAGE");
}

void GameInit()
{
    LogoInit();
}

void GameUpdate()
{
    switch (sceneID)
    {
    case LOGO:
        LogoUpdate();
        break;
    case MENU:
        MenuUpdate();
        break;
    case STAGE:
        StageUpdate();
        break;
    default:
        break;
    }
}