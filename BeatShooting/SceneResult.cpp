#include "SceneResult.h"
#include "CApplication.h"
#include "ScenePlay.h"

#include <windows.h>

// 결과 화면 업데이트
int SceneResultUpdate()
{
    // Enter 키를 누르면 재시작
    if (GetAsyncKeyState(VK_RETURN) & 0x0001)
    {
        // 게임 데이터 초기화
        ScenePlayReset();

        // 플레이 상태로 변경
        g_GameState = GAME_PLAY;
    }

    return 0;
}

// 결과 화면 출력
int SceneResultRender()
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

    // 결과 문구 출력
    if (g_Font >= 0)
    {
        VEC2i resultPos = { 330, 230 };

        // 클리어 결과
        if (g_GameState == GAME_CLEAR)
        {
            g2_FontDrawText(
                g_Font,
                resultPos,
                0xFF00FF00,
                "GAME CLEAR!"
            );
        }
        // 게임 오버 결과
        else
        {
            g2_FontDrawText(
                g_Font,
                resultPos,
                0xFFFF0000,
                "GAME OVER"
            );
        }

        // 재시작 안내
        VEC2i restartPos = { 260, 380 };

        g2_FontDrawText(
            g_Font,
            restartPos,
            0xFFFFFFFF,
            "PRESS ENTER TO RESTART"
        );
    }

    return 0;
}
