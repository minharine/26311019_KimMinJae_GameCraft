
#include "glc2d.h"
#include <windows.h>
#include <stdint.h>

// 화면 크기
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// 이미지 리소스
int g_Background = -1;
int g_Player = -1;

// 플레이어 위치
float g_PlayerX = 400.0f;
float g_PlayerY = 450.0f;

// 플레이어 이동 속도
float g_MoveSpeed = 5.0f;

// 키보드 입력 및 플레이어 이동
int FrameMove()
{
    // 왼쪽 이동
    if (GetAsyncKeyState(VK_LEFT) & 0x8000 ||
        GetAsyncKeyState('A') & 0x8000)
    {
        g_PlayerX -= g_MoveSpeed;
    }

    // 오른쪽 이동
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000 ||
        GetAsyncKeyState('D') & 0x8000)
    {
        g_PlayerX += g_MoveSpeed;
    }

    // 화면 밖으로 나가지 않도록 제한
    if (g_PlayerX < 20.0f)
    {
        g_PlayerX = 20.0f;
    }

    if (g_PlayerX > 780.0f)
    {
        g_PlayerX = 780.0f;
    }

    return 0;
}

// 게임 화면 출력
int Render()
{
    // 배경 이미지 크기 계산
    float bgWidth = (float)g2_TextureWidth(g_Background);
    float bgHeight = (float)g2_TextureHeight(g_Background);

    // 화면 크기에 맞는 배율
    VEC2 bgPos = { 400.0f, 300.0f };
    VEC2 bgScale = {
        SCREEN_WIDTH / bgWidth,
        SCREEN_HEIGHT / bgHeight
    };

    // 배경 이미지 출력
    g2_Draw2D(
        g_Background,
        NULL,
        &bgPos,
        &bgScale
    );

    // 플레이어 이미지 출력
    VEC2 playerPos = { g_PlayerX, g_PlayerY };

    g2_Draw2D(
        g_Player,
        NULL,
        &playerPos
    );

    return 0;
}

// 게임 실행
int main()
{
    // SDK 초기화
    g2_InitSdk();

    // 게임 창 생성
    g2_CreateWin(
        100, 100,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        "BeatShooting",
        true
    );

    // 배경색 설정
    g2_SetClearColor(0x00101020);

    // 이미지 불러오기
    g_Background = g2_TextureLoad(
        "resource/image/background/bg_game.png"
    );

    g_Player = g2_TextureLoad(
        "resource/image/player/player_idle.png"
    );

    // 입력 및 화면 출력 함수 등록
    g2_SetFrameMove(FrameMove);
    g2_SetRender(Render);

    // 게임 실행
    g2_Run();

    // 이미지 리소스 해제
    if (g_Player >= 0)
    {
        g2_TextureRelease(g_Player);
    }

    if (g_Background >= 0)
    {
        g2_TextureRelease(g_Background);
    }

    // 게임 종료
    g2_DestroyWin();

    return 0;
}
