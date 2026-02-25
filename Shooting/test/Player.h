#pragma once
#include "DxLib.h"
#include <cmath>

class Player
{
public:
    void Initialize(const VECTOR& startPos, float height, float radius, int seg);
    void UpdateCameraAligned(float camYaw);
    void Update();
    void Draw() const;

    void SetAlpha(int a) { m_Alpha = (a < 0) ? 0 : (a > 255 ? 255 : a); }

    // 取得系
    VECTOR GetPosition() const { return m_Pos; }
    float  GetYaw() const { return m_Yaw; }
    VECTOR GetForwardXZ() const; // yaw=0 で前方は -Z
    void SetYaw(float yaw) { m_Yaw = yaw; }
   
private:
    VECTOR m_Pos = VGet(0.0f, 0.0f, 0.0f);
    float  m_Height = 1.7f;
    float  m_Radius = 0.35f;
    int    m_Seg = 12;

    float  m_Yaw = 0.0f;       // 左右回転（ラジアン）
    float  m_MoveSpeed = 0.08f;
    float  m_TurnSpeed = 0.04f;

    // 描画色など（必要なら）
    int    m_Dif = GetColor(180, 220, 255);
    int    m_Spc = GetColor(80, 140, 255);

    int m_Alpha = 255; // 0=完全透明, 255=不透明
    void SetGraviti
};
