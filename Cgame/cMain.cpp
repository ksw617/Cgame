#include <stdio.h>
#include <Windows.h>

enum SCENE_ID
{
    LOGO,
    MENU, 
    STAGE,
    UTILL,
};

enum MENU_ID
{
    CONTINUE,
    NEWGAME,
    UTILITY,
    EXIT,
};

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

struct Obj
{
    int x;
    int y;
    Color color;
    const char* shape;
};

void SetPosition(int x, int y)
{
    COORD pos{ x * 2, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}     

void ChangeColor(Color color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

SCENE_ID sceneID = LOGO;

void LogoInit();
void LogoUpdate();

#define MENU_COUNT 4

Obj arrow;
Obj menus[MENU_COUNT];

MENU_ID menuID = CONTINUE;

void MenuInit();
void MenuUpdate();

void StageInit();
void StageUpdate();

void UtillUpdate();

int main()
{
    LogoInit();

    while (true)
    {
        system("cls");
       
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
        case UTILL:
            UtillUpdate();
        default:
            break;
        }

        Sleep(50);
    }

    return 0;
}

void LogoInit() {}

void LogoUpdate()
{
    SetPosition(10, 10);
    printf("LOGO");

    if (GetAsyncKeyState(VK_RETURN))
    {
        sceneID = MENU;
        MenuInit();
    }
}

void MenuInit()
{
    arrow.x = 15;
    arrow.y = 25;
    arrow.color = LIGHT_RED;
    arrow.shape = "▶";

    for (int i = 0; i < MENU_COUNT; i++)
    {
        menus[i].x = 18;
        menus[i].y = 25 + 2 * i;
        menus[i].color = LIGHT_WHITE;
    }

    menus[0].color = LIGHT_RED;

    menus[0].shape = "Continue";
    menus[1].shape = "NewGame";
    menus[2].shape = "Setting";
    menus[3].shape = "Exit";
}

void MenuUpdate()
{
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        if (arrow.y > 25)
        {
            arrow.y -= 2;
            int id = menuID;     //id 이전
            menus[id].color = LIGHT_WHITE; 
            id--;                //id 지금
            menus[id].color = LIGHT_RED;
            menuID = (MENU_ID)id;
        }
    }


    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        if (arrow.y < 31)
        {
            arrow.y += 2;
            int id = menuID;   //id 이전 //0
            menus[id].color = LIGHT_WHITE;  //menus[0] = 흰색
            id++;              //id 지금     //id == 1
            menus[id].color = LIGHT_RED;    //menus[1] = 빨간색;
            menuID = (MENU_ID)id;       //menuID = (MENU_ID) id(1);
        }
            
    }

    if (GetAsyncKeyState(VK_RETURN))
    {
        switch (menuID)
        {
        case CONTINUE:
            sceneID = STAGE;
            break;
        case NEWGAME:
            StageInit();
            sceneID = STAGE;
            break;
        case UTILITY:
            sceneID = UTILL;
            break;
        case EXIT:
            exit(true);
            break;
        default:
            break;
        }
    }

    SetPosition(arrow.x, arrow.y);
    ChangeColor(arrow.color);
    printf(arrow.shape);


    for (int i = 0; i < MENU_COUNT; i++)
    {
        SetPosition(menus[i].x, menus[i].y);
        ChangeColor(menus[i].color);
        printf(menus[i].shape);
    }

}


void StageInit() {}
void StageUpdate()
{
    SetPosition(10, 10);
    printf("STAGE");
}

void UtillUpdate()
{
    SetPosition(10, 10);
    printf("UTILL");
}

