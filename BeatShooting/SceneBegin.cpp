#include "SceneBegin.h"
#include "CApplication.h"
#include "ScenePlay.h"

#include <windows.h>

// 시작 화면 업데이트
int SceneBeginUpdate()
{
    // Enter 키를 누르면 게임 시작
    if (GetAsyncKeyState(VK_RETURN) & 0x0001)
    {
        // 게임 데이터 초기화
        ScenePlayReset();

        // 플레이 상태로 변경
        g_GameState = GAME_PLAY;
    }

    return 0;
}

// 시작 화면 출력
int SceneBeginRender()
{
    // 배경 이미지 크기 확인
    if (g_GameBackground >= 0)
    {
        float bgWidth =
            (float)g2_TextureWidth(g_GameBackground);

        float bgHeight =
            (float)g2_TextureHeight(g_GameBackground);

        if (bgWidth > 0 && bgHeight > 0)
        {
            // 화면 중앙에 배경 출력
            VEC2 bgPos = { 400.0f, 300.0f };

            // 800 x 600 화면에 맞게 크기 조절
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

    // 게임 제목 및 시작 안내
    if (g_Font >= 0)
    {
        VEC2i titlePos = { 280, 220 };

        g2_FontDrawText(
            g_Font,
            titlePos,
            0xFFFFFFFF,
            "BEAT SHOOTING"
        );

        VEC2i startPos = { 260, 400 };

        g2_FontDrawText(
            g_Font,
            startPos,
            0xFFFFFFFF,
            "PRESS ENTER TO START"
        );
    }

    return 0;
}
