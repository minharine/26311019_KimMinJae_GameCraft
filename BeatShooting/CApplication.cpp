#include "CApplication.h"

#include "SceneBegin.h"
#include "ScenePlay.h"
#include "SceneResult.h"

// 게임 상태
GAME_STATE g_GameState = GAME_START;

// 이미지 리소스
int g_GameBackground = -1;

int g_PlayerIdle = -1;
int g_PlayerLeft = -1;
int g_PlayerRight = -1;

int g_Laser = -1;

// 폰트
int g_Font = -1;

// 리소스 불러오기
void CApplication::LoadResource()
{
    // 게임 배경
    g_GameBackground = g2_TextureLoad(
        "resource/image/background/bg_game.png"
    );

    // 플레이어 이미지
    g_PlayerIdle = g2_TextureLoad(
        "resource/image/player/player_idle.png"
    );

    g_PlayerLeft = g2_TextureLoad(
        "resource/image/player/player_move_left.png"
    );

    g_PlayerRight = g2_TextureLoad(
        "resource/image/player/player_move_right.png"
    );

    // 빔 이미지
    g_Laser = g2_TextureLoad(
        "resource/image/obstacle/obstacle_laser.png"
    );

    // 폰트 생성
    g_Font = g2_FontCreate("Arial", 30);
}

// 리소스 해제
void CApplication::ReleaseResource()
{
    if (g_GameBackground >= 0)
        g2_TextureRelease(g_GameBackground);

    if (g_PlayerIdle >= 0)
        g2_TextureRelease(g_PlayerIdle);

    if (g_PlayerLeft >= 0)
        g2_TextureRelease(g_PlayerLeft);

    if (g_PlayerRight >= 0)
        g2_TextureRelease(g_PlayerRight);

    if (g_Laser >= 0)
        g2_TextureRelease(g_Laser);
}

// 게임 데이터 업데이트
int FrameMove()
{
    if (g_GameState == GAME_START)
    {
        SceneBeginUpdate();
    }
    else if (g_GameState == GAME_PLAY)
    {
        ScenePlayUpdate();
    }
    else
    {
        SceneResultUpdate();
    }

    return 0;
}

// 게임 화면 출력
int Render()
{
    if (g_GameState == GAME_START)
    {
        SceneBeginRender();
    }
    else if (g_GameState == GAME_PLAY)
    {
        ScenePlayRender();
    }
    else
    {
        SceneResultRender();
    }

    return 0;
}

// 게임 실행
void CApplication::Run()
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

    // 기본 배경색
    g2_SetClearColor(0x00101020);

    // 리소스 불러오기
    LoadResource();

    // 게임 시작 상태
    g_GameState = GAME_START;

    // 업데이트 및 출력 함수 등록
    g2_SetFrameMove(FrameMove);
    g2_SetRender(Render);

    // 게임 실행
    g2_Run();

    // 리소스 해제
    ReleaseResource();

    // 게임 종료
    g2_DestroyWin();
}
