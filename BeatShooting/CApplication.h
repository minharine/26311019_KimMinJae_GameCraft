#pragma once

#include "glc2d.h"

// 게임 상태
enum GAME_STATE
{
    GAME_START,
    GAME_PLAY,
    GAME_CLEAR,
    GAME_OVER
};

// 현재 게임 상태
extern GAME_STATE g_GameState;

// 화면 크기
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

// 이미지 리소스
extern int g_GameBackground;

extern int g_PlayerIdle;
extern int g_PlayerLeft;
extern int g_PlayerRight;

extern int g_Laser;

// 폰트
extern int g_Font;

// 게임 실행 클래스
class CApplication
{
public:
    void Run();

private:
    void LoadResource();
    void ReleaseResource();
};

// 게임 업데이트 및 화면 출력
int FrameMove();
int Render();
