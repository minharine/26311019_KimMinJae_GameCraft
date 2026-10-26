
#include "glc2d.h"
#include <windows.h>
#include <stdint.h>

// 화면 크기
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// 레인 번호
#define LANE_LEFT 0
#define LANE_CENTER 1
#define LANE_RIGHT 2

// 게임 상태 변수
int g_PlayerLane = LANE_CENTER;
int g_PlayerHP = 3;
int g_Score = 0;

int g_ObstacleLane = LANE_LEFT;
int g_ObstacleY = 0;

int g_Font = -1;
bool g_GameOver = false;

// 키 입력 확인용
bool g_PrevLeft = false;
bool g_PrevRight = false;

// 시간 확인용
long long g_LastTime = 0;
long long g_LastMoveTime = 0;

// 레인별 X 좌표
int GetLaneX(int lane)
{
    if (lane == LANE_LEFT)
    {
        return 200;
    }
    else if (lane == LANE_CENTER)
    {
        return 400;
    }
    else
    {
        return 600;
    }
}

// 게임 업데이트
int FrameMove()
{
    long long currentTime = g2_TimeGetTime();

    if (g_LastTime == 0)
    {
        g_LastTime = currentTime;
        g_LastMoveTime = currentTime;
    }

    // 키 입력 상태 확인
    const KEYCODE* key = g2_GetKeyboard();

    if (key != NULL && !g_GameOver)
    {
        bool leftPressed =
            key[VK_LEFT] || key['A'];

        bool rightPressed =
            key[VK_RIGHT] || key['D'];

        // 키를 새로 눌렀을 때만 이동
        if (leftPressed && !g_PrevLeft)
        {
            if (g_PlayerLane > LANE_LEFT)
            {
                g_PlayerLane--;
            }
        }

        if (rightPressed && !g_PrevRight)
        {
            if (g_PlayerLane < LANE_RIGHT)
            {
                g_PlayerLane++;
            }
        }

        g_PrevLeft = leftPressed;
        g_PrevRight = rightPressed;
    }

    // 장애물 이동
    if (!g_GameOver &&
        currentTime - g_LastMoveTime >= 20)
    {
        g_ObstacleY += 5;
        g_LastMoveTime = currentTime;

        // 장애물이 플레이어 위치에 도착
        if (g_ObstacleY >= 480)
        {
            if (g_ObstacleLane == g_PlayerLane)
            {
                g_PlayerHP--;

                if (g_PlayerHP <= 0)
                {
                    g_PlayerHP = 0;
                    g_GameOver = true;
                }
            }
            else
            {
                g_Score += 10;
            }

            // 다음 장애물 생성
            if (!g_GameOver)
            {
                g_ObstacleY = 0;
                g_ObstacleLane++;

                if (g_ObstacleLane > LANE_RIGHT)
                {
                    g_ObstacleLane = LANE_LEFT;
                }
            }
        }
    }

    return 0;
}

// 화면 출력
int Render()
{
    // 화면 배경색 설정은 초기화 단계에서 지정
    // 세 개의 레인 표시
    g2_FontDrawText(
        g_Font, { 150, 80 }, 0xFF888888,
        "--------------------------------");

    g2_FontDrawText(
        g_Font, { 150, 150 }, 0xFFFFFFFF,
        "|              |              |");

    g2_FontDrawText(
        g_Font, { 150, 220 }, 0xFFFFFFFF,
        "|              |              |");

    g2_FontDrawText(
        g_Font, { 150, 290 }, 0xFFFFFFFF,
        "|              |              |");

    g2_FontDrawText(
        g_Font, { 150, 360 }, 0xFFFFFFFF,
        "|              |              |");

    g2_FontDrawText(
        g_Font, { 150, 430 }, 0xFFFFFFFF,
        "|              |              |");

    g2_FontDrawText(
        g_Font, { 150, 500 }, 0xFF888888,
        "--------------------------------");

    // 레인 이름
    g2_FontDrawText(
        g_Font, { 165, 45 }, 0xFFFFFFFF, "LEFT");

    g2_FontDrawText(
        g_Font, { 365, 45 }, 0xFFFFFFFF, "CENTER");

    g2_FontDrawText(
        g_Font, { 565, 45 }, 0xFFFFFFFF, "RIGHT");

    // 플레이어 출력
    int playerX = GetLaneX(g_PlayerLane);

    g2_FontDrawText(
        g_Font, { playerX - 20, 470 },
        0xFF00FFFF, "[P]");

    // 장애물 출력
    int obstacleX = GetLaneX(g_ObstacleLane);

    if (!g_GameOver)
    {
        g2_FontDrawText(
            g_Font, { obstacleX - 20, g_ObstacleY },
            0xFFFF5555, "[X]");
    }

    // HP와 점수
    g2_FontDrawText(
        g_Font, { 20, 20 }, 0xFFFFFFFF,
        "HP: %d", g_PlayerHP);

    g2_FontDrawText(
        g_Font, { 20, 50 }, 0xFFFFFFFF,
        "SCORE: %d", g_Score);

    // 조작 방법
    g2_FontDrawText(
        g_Font, { 20, 550 }, 0xFFCCCCCC,
        "MOVE: A / D or LEFT / RIGHT");

    // 게임 오버
    if (g_GameOver)
    {
        g2_FontDrawText(
            g_Font, { 300, 250 }, 0xFFFF5555,
            "GAME OVER");

        g2_FontDrawText(
            g_Font, { 270, 290 }, 0xFFFFFFFF,
            "Please restart the game.");
    }

    return 0;
}

int main()
{
    // SDK 초기화
    if (g2_InitSdk() < 0)
    {
        return 0;
    }

    // 게임 창 생성
    if (g2_CreateWin(
        100, 100,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        "BeatShooting", true, 1.0f) < 0)
    {
        return 0;
    }

    // 배경색 설정
    g2_SetClearColor(0x00101020);

    // 폰트 생성
    g_Font = g2_FontCreate("Arial", 24);

    // 게임 함수 등록
    g2_SetFrameMove(FrameMove);
    g2_SetRender(Render);

    // 게임 실행
    g2_Run();

    // 종료
    g2_DestroyWin();

    return 0;
}
