#include "Player.h"
#include <cmath>

void Player::Initialize(const VECTOR& startPos, float height, float radius, int seg)
{
    m_Pos = startPos;
    m_Height = height;
    m_Radius = radius;
    m_Seg = seg;
    m_Yaw = 0.0f;
}

VECTOR Player::GetForwardXZ() const
{
    // yaw=0 で 前 = -Z（あなたの既存実装に合わせる）
    float s = sinf(m_Yaw), c = cosf(m_Yaw);
    return VGet(s, 0.0f, -c); // x=sin, z=-cos
    // 既存の式と同じです。[2](https://jikeigroupcom-my.sharepoint.com/personal/fca2506010016_edu_fca_ac_jp/Documents/Microsoft%20Copilot%20Chat%20%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB/Player.cpp)
}


void Player::UpdateCameraAligned(float camYaw)
{
    float forward = 0.0f;
    float strafe = 0.0f;

    // --- 入力（WASD） ---
    if (CheckHitKey(KEY_INPUT_W)) forward += 1.0f;
    if (CheckHitKey(KEY_INPUT_S)) forward -= 1.0f;
    if (CheckHitKey(KEY_INPUT_A)) strafe += 1.0f; // 左へ
    if (CheckHitKey(KEY_INPUT_D)) strafe -= 1.0f; // 右へ

    // 速度（Shiftダッシュ／Ctrl低速）
    float spd = m_MoveSpeed;
    if (CheckHitKey(KEY_INPUT_LSHIFT))   spd *= 1.8f;
    if (CheckHitKey(KEY_INPUT_LCONTROL)) spd *= 0.5f;

    // --- カメラの前/右ベクトル（XZ） ---
    // yaw=0 で前は -Z というあなたの座標系に合わせた式
    float sY = sinf(camYaw), cY = cosf(camYaw);
    VECTOR camF = VGet(sY, 0.0f, -cY);           // Front
    VECTOR camR = VGet(-camF.z, 0.0f, camF.x);   // Right = (-fz,0,fx)

    // --- 入力から移動ベクトルを合成 ---
    VECTOR move = VGet(
        camF.x * forward + camR.x * strafe,
        0.0f,
        camF.z * forward + camR.z * strafe
    );

    // 斜めで速くならないよう正規化
    float len2 = move.x * move.x + move.z * move.z;
    if (len2 > 1e-6f) {
        float invLen = 1.0f / sqrtf(len2);
        move.x *= invLen;
        move.z *= invLen;

        // 位置更新
        m_Pos.x += move.x * spd;
        m_Pos.z += move.z * spd;

        // ★進行方向に向きを合わせる（yaw=0 で -Z 系なので atan2(move.x, -move.z)）
        m_Yaw = atan2f(move.x, -move.z);
    }

    m_Pos.y = 0.0f; // 地面想定
}
    


void Player::Draw() const
{
    if (m_Alpha <= 0) return; // 完全に透明なら描画しない

    // αブレンド開始
    if (m_Alpha < 255) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Alpha);
    }

    // カプセル本体
    VECTOR p1 = VAdd(m_Pos, VGet(0.0f, m_Radius, 0.0f));
    VECTOR p2 = VAdd(m_Pos, VGet(0.0f, m_Height - m_Radius, 0.0f));
    DrawCapsule3D(p1, p2, m_Radius, m_Seg, m_Dif, m_Spc, TRUE);

    // FPSに近い時は矢印が邪魔になりがちなので、半透明以下なら描かない等の配慮
    if (m_Alpha > 160) {
        VECTOR chest = VAdd(m_Pos, VGet(0.0f, m_Height * 0.75f, 0.0f));
        VECTOR tip = VAdd(chest, VScale(GetForwardXZ(), 0.8f));
        DrawLine3D(chest, tip, GetColor(255, 230, 120));
    }

    // ブレンド終了
    if (m_Alpha < 255) {
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}



