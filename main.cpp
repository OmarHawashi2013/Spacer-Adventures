/*  
    ================================================
    =   /----\  \       /|  ------  |-----|        =
    =  |      | | \    / | /      \ |      |       =
    =  |      | |  \  /  | |------| |-----|        =
    =  |      | |   \/   | |      | |     \        =
    =  \ ____ / |        | |      | |      \       =
    =  [ --> OFFSET: 0x0000 | STATUS: OK ]         =
    =                                              =
    =  [ OMAR ENGINE - Custom Win32 Framework ]    =
    =  [ Developed by: Omar Hawash | (C) 2026 ]    =
    ================================================

*/ 


#include <windows.h>
#include <fstream>
#include <vector>
#include <math.h>
#include <chrono>
#include <random>
#include "inc/input.h"
#include "inc/debug.h"
#include "inc/global.h"
#include "inc/gameObj.h"
#include "inc/bullet.h"
#include "inc/back.h"
#include "inc/tilemap.h"
#include "inc/platform.h"
#include "inc/player.h"
#include "inc/walkingEnemy.h"
#include "inc/jumpingEnemy.h"
#include "inc/collictable.h"
#include "inc/rocketShooter.h"
#include "inc/jumppad.h"
using namespace std;

constexpr double MS_PER_FRAME = 1000.0 / 60.0;

platform p(64, 720/2, 64, 64, 3);
std::vector<platform> pv;

#define IDI_APP_ICON 101

vector<walkingEnemy> walkingEnemyV;
vector<jumpingEnemy> jumpingEnemyV;

vector<collictable> cV;
vector<jumppad> jpV;

vector<rocketShooter> rsV;

HDC backDC;
HBITMAP backBMP;

Back bck;

Map lvl(48, 23);



/*
levels
*/
#include "inc/main_menu.h"
#include "inc/level_1.h"
/*
levels
*/

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

Back bck;
    switch (uMsg) 
    {
    	case WM_DESTROY:
            DeleteObject(hFont);
            DeleteObject(hFontSmall);
            mciSendString("close bgm", NULL, 0, NULL);
            mciSendString("close sndJump", NULL, 0, NULL);
            mciSendString("close sndShoot", NULL, 0, NULL);
            mciSendString("close sndEnemyJump", NULL, 0, NULL);

            DeleteObject(backBMP);
            DeleteDC(backDC);
            for (int i = 0; i < 10; ++i)
            {
                DeleteObject(playerFrames[i]);
            }

            PostQuitMessage(0);
            return 0;
 
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam); 
    }
    return 0; 
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow){
	WNDCLASS wc = {};

	wc.lpfnWndProc   = WndProc;
	wc.hInstance     = hInstance;
	wc.lpszClassName = "Spacer Adventures";

    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP_ICON)); // big icon

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
	    0,
	    "Spacer Adventures",
	    "Spacer Adventures",
	    WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,

	    CW_USEDEFAULT, CW_USEDEFAULT, screenX, screenY,

	    NULL,
	    NULL,
	    hInstance,
	    NULL
	);

	if (hwnd == NULL){
	    return 0;
	}

	ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    HDC hdc = GetDC(hwnd);

    backDC = CreateCompatibleDC(hdc);
    backBMP = CreateCompatibleBitmap(hdc, screenX, screenY);
    SelectObject(backDC, backBMP);

    /*x
    init
    */

    mciSendString("open \"sfx/jump.wav\" type waveaudio alias sndJump", NULL, 0, NULL);
    mciSendString("open \"sfx/shoot.wav\" type waveaudio alias sndShoot", NULL, 0, NULL);
    mciSendString("open \"sfx/ejump.wav\" type waveaudio alias  sndEnemyJump", NULL, 0, NULL);
    

    mciSendString("open music/main_menu.wav type mpegvideo alias bgm", NULL, 0, NULL);
    mciSendString("play bgm repeat", NULL, 0, NULL);

    player.init(backDC, playerFrames[0], false);
    lvl.init(backDC, "tilesets/moon/tile_1.bmp", "tilesets/moon/tile_2.bmp", "tilesets/moon/tile_3.bmp", "levels/level_1.sl");
    bck.init(backDC, "tilesets/moon/back.bmp");

    InitPlayerFrames();

    p.init(backDC, "tilesets/moon/tile_1.bmp");

    pv.push_back(p);


    for(int y = 0; y < lvl.mapH; y++){
        for(int x  =0;x < lvl.mapW;x++){
            if(lvl.m[y][x] == '5'){
                float bx = (x *64), by = (y * 64);
                walkingEnemy enemyNow(bx, by, 64, 64, 5);

                enemyNow.init(backDC, "sprites/star_man1.bmp");

                walkingEnemyV.push_back(enemyNow);
            }
            if (lvl.m[y][x] == '6') {
                float bx = (x *64), by = (y * 64);
                jumpingEnemy enemyNow(bx, by, 64, 64, 5);

                enemyNow.init(backDC, "sprites/star_man1.bmp");

                jumpingEnemyV.push_back(enemyNow);
            }
            if (lvl.m[y][x] == '7') {
                float bx = (x *64), by = (y * 64);
                rocketShooter enemyNow(bx, by, 64, 64);

                enemyNow.init(backDC, "sprites/rocketLancher.bmp");

                rsV.push_back(enemyNow);
            }
            if (lvl.m[y][x] == '8') {
                float bx = (x *64), by = (y * 64);
                collictable cNow(bx, by, 32, 32);

                cNow.init(backDC, "sprites/coin.bmp");

                cV.push_back(cNow);
            }
            if (lvl.m[y][x] == '9') {
                float bx = (x *64), by = (y * 64);
                jumppad jpNow(bx, by, 64, 64);

                jpNow.init(backDC, "sprites/player1.bmp");

                jpV.push_back(jpNow);
            }
        }
    }

    AddFontResourceEx("Minecraft.ttf", FR_PRIVATE, 0);

    /*
    init
    */


    MSG msg;

    while (true){
        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
            if(msg.message == WM_QUIT) return msg.wParam;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        auto frameStart = std::chrono::high_resolution_clock::now();

        PatBlt(
            backDC, 0, 0, screenX, screenY, BLACKNESS
        );

        if (GetForegroundWindow() == hwnd)
            Input::update();

        switch (gameState) {
            case 0:
                main_menu(backDC);
                break;
            case 1:
                level_1();
                break;
        }
        


        BitBlt(hdc, 0, 0, screenX, screenY, backDC, 0, 0, SRCCOPY);

        auto frameEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> frameTime = frameEnd - frameStart;

        if (frameTime.count() < MS_PER_FRAME) {
            Sleep(static_cast<DWORD>(MS_PER_FRAME - frameTime.count()));
        }
    }
}