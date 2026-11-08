#include "ScenePlay.h"
#include "CApplication.h"

#include <windows.h>

// 플레이어 위치
float g_PlayerX = 400.0f;
float g_PlayerY = 520.0f;

// 플레이어 이동 속도
float g_MoveSpeed = 6.0f;

// 현재 플레이어 이미지
int g_CurrentPlayer = -1;

// 빔 위치
float g_LaserX = 400.0f;
float g_LaserY = -100.0f;

// 빔 이동 속도
float g_LaserSpeed = 4.0f;

// 빔 크기
float g_LaserWidth = 32.0f;
float g_LaserHeight = 192.0f;

// 게임 초기화
void ScenePlayReset()
{
    // 플레이어 위치 초기화
    g_PlayerX = 400.0f;
    g_PlayerY = 520.0f;

    // 플레이어 이미지 초기화
    g_CurrentPlayer = g_PlayerIdle;

    // 빔 위치 초기화
    g_LaserX = 400.0f;
    g_LaserY = -100.0f;
}

// 게임 플레이 업데이트
int ScenePlayUpdate()
{
    // 기본 플레이어 이미지
    g_CurrentPlayer = g_PlayerIdle;

    // 왼쪽 이동
    if (GetAsyncKeyState(VK_LEFT) & 0x8000 ||
        GetAsyncKeyState('A') & 0x8000)
    {
        g_PlayerX -= g_MoveSpeed;

        // 왼쪽 이동 이미지
        g_CurrentPlayer = g_PlayerLeft;
    }

    // 오른쪽 이동
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000 ||
        GetAsyncKeyState('D') & 0x8000)
    {
        g_PlayerX += g_MoveSpeed;

        // 오른쪽 이동 이미지
        g_CurrentPlayer = g_PlayerRight;
    }

    // 화면 밖으로 나가지 않도록 제한
    if (g_PlayerX < 16.0f)
    {
        g_PlayerX = 16.0f;
    }

    if (g_PlayerX > 784.0f)
    {
        g_PlayerX = 784.0f;
    }

    // 빔 아래로 이동
    g_LaserY += g_LaserSpeed;

    // 플레이어 충돌 범위
    float playerLeft = g_PlayerX - 16.0f;
    float playerRight = g_PlayerX + 16.0f;
    float playerTop = g_PlayerY - 16.0f;
    float playerBottom = g_PlayerY + 16.0f;

    // 빔 충돌 범위
    float laserLeft = g_LaserX - g_LaserWidth / 2.0f;
    float laserRight = g_LaserX + g_LaserWidth / 2.0f;
    float laserTop = g_LaserY - g_LaserHeight / 2.0f;
    float laserBottom = g_LaserY + g_LaserHeight / 2.0f;

    // 가로 방향 충돌 확인
    bool hitX =
        playerRight > laserLeft &&
        playerLeft < laserRight;

    // 세로 방향 충돌 확인
    bool hitY =
        playerBottom > laserTop &&
        playerTop < laserBottom;

    // 플레이어가 빔에 맞았는지 확인
    if (hitX && hitY)
    {
        g_GameState = GAME_OVER;
    }

    // 빔이 플레이어를 완전히 지나가면 클리어
    if (laserTop > playerBottom)
    {
        g_GameState = GAME_CLEAR;
    }

    return 0;
}

// 게임 화면 출력
int ScenePlayRender()
{
    // 배경 이미지 출력
    if (g_GameBackground >= 0)
    {
        float bgWidth =
            (float)g2_TextureWidth(g_GameBackground);

        float bgHeight =
            (float)g2_TextureHeight(g_GameBackground);

        if (bgWidth > 0 && bgHeight > 0)
        {
            VEC2 bgPos = { 400.0f, 300.0f };

            VEC2 bgScale = {
                800.0f / bgWidth,
                600.0f / bgHeight
            };

            g2_Draw2D(
                g_GameBackground,
                NULL,
                &bgPos,
                &bgScale
            );
        }
    }

    // 빔 이미지 출력
    if (g_Laser >= 0)
    {
        float laserTextureWidth =
            (float)g2_TextureWidth(g_Laser);

        float laserTextureHeight =
            (float)g2_TextureHeight(g_Laser);

        if (laserTextureWidth > 0 &&
            laserTextureHeight > 0)
        {
            VEC2 laserPos = {
                g_LaserX,
                g_LaserY
            };

            // 세로로 길게 출력
            VEC2 laserScale = {
                g_LaserWidth / laserTextureWidth,
                g_LaserHeight / laserTextureHeight
            };

            g2_Draw2D(
                g_Laser,
                NULL,
                &laserPos,
                &laserScale
            );
        }
    }

    // 플레이어 이미지 출력
    if (g_CurrentPlayer >= 0)
    {
        VEC2 playerPos = {
            g_PlayerX,
            g_PlayerY
        };

        g2_Draw2D(
            g_CurrentPlayer,
            NULL,
            &playerPos
        );
    }

    // 조작 안내
    if (g_Font >= 0)
    {
        VEC2i guidePos = { 20, 20 };

        g2_FontDrawText(
            g_Font,
            guidePos,
            0xFFFFFFFF,
            "MOVE : A / D OR LEFT / RIGHT"
        );
    }

    return 0;
}
