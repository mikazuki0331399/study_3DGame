#pragma once
#include "DxLib.h"

class Player;

class Camera
{
public:
    void InitializeOnce(int scrW, int scrH, float fovDeg = 60.0f,
        float nearClip = 0.1f, float farClip = 5000.0f);
    void Update();
    void Apply();

    // 設定
    void SetCenterPlayer(const Player* p) { m_CenterPlayer = p; }
    void SetSensitivity(float sx, float sy) { m_SensX = sx; m_SensY = sy; }
    void SetOrbit(float dist, float lookUp) { m_OrbitDist = dist; m_LookUp = lookUp; }

    // 角度
    void SetYawPitch(float yaw, float pitch);
    float GetYaw() const { return m_Yaw; }
    float GetPitch() const { return m_Pitch; }

    // 位置（必要なら）
    VECTOR GetPosition() const { return m_Eye; }
    float GetOrbitDist() const { return m_OrbitDist; }

private:
    static float clampf(float v, float lo, float hi) {
        return (v < lo) ? lo : ((v > hi) ? hi : v);
    }

    bool   m_Inited = false;
    int    m_ScrW = 1280, m_ScrH = 720;
    int    m_CenterX = 640, m_CenterY = 360;

    VECTOR m_Eye = VGet(0.0f, 1.6f, 5.0f);
    float  m_Yaw = 0.0f;
    float  m_Pitch = 0.0f;
    float  m_SensX = 0.0008f;
    float  m_SensY = 0.0006f;

    float  m_OrbitDist = 5.0f;  // プレイヤーからの距離（ホイールで可変）
    float  m_LookUp = 1.6f;  // 見下ろしの高さ

    const Player* m_CenterPlayer = nullptr;
};
