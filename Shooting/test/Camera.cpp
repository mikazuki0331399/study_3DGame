#include "Camera.h"
#include "Player.h"
#include <cmath>

void Camera::InitializeOnce(int scrW, int scrH, float fovDeg, float nearClip, float farClip)
{
    if (m_Inited) return;
    m_Inited = true;

    m_ScrW = scrW; m_ScrH = scrH;
    m_CenterX = m_ScrW / 2; m_CenterY = m_ScrH / 2;

    // 3D設定
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);
    SetCameraNearFar(nearClip, farClip);
    SetupCamera_Perspective(fovDeg * DX_PI_F / 180.0f);

    // 照明（任意）
    SetUseLighting(TRUE);
    ChangeLightTypeDir(VGet(-0.5f, -1.0f, -0.3f));
    SetLightEnable(TRUE);

    // マウス相対化（センタリング）
    SetMouseDispFlag(FALSE);
    SetMousePoint(m_CenterX, m_CenterY);
    // 既存の初期化方針に準拠。[1](https://jikeigroupcom-my.sharepoint.com/personal/fca2506010016_edu_fca_ac_jp/Documents/Microsoft%20Copilot%20Chat%20%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB/Camra.cpp)
}

void Camera::SetYawPitch(float yaw, float pitch)
{
    m_Yaw = yaw;
    m_Pitch = clampf(pitch, -DX_PI_F / 2.2f, DX_PI_F / 2.2f);
    // 角度のClampは既存と同じレンジを踏襲。[1](https://jikeigroupcom-my.sharepoint.com/personal/fca2506010016_edu_fca_ac_jp/Documents/Microsoft%20Copilot%20Chat%20%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB/Camra.cpp)
}

void Camera::Update()
{
    // --- マウスでYaw/Pitch ---
    int mx, my; GetMousePoint(&mx, &my);
    int dx = mx - m_CenterX;
    int dy = my - m_CenterY;
    m_Yaw -= dx * m_SensX;
    m_Pitch -= dy * m_SensY;
    m_Pitch = clampf(m_Pitch, -DX_PI_F / 2.2f, DX_PI_F / 2.2f);
    SetMousePoint(m_CenterX, m_CenterY);

    // --- ホイールで距離（ズーム） ---
    int wheel = GetMouseWheelRotVol();
    
        // ※符号は好みで調整（環境差に注意）
    m_OrbitDist = clampf(m_OrbitDist - wheel * 0.35f, 1.2f, 15.0f);

    // --- 視線方向（Yaw/Pitch から算出）---
    float cosP = cosf(m_Pitch), sinP = sinf(m_Pitch);
    float sinY = sinf(m_Yaw), cosY = cosf(m_Yaw);
    VECTOR dirF = VGet(sinY * cosP, sinP, -cosY * cosP);

    VECTOR center = m_CenterPlayer ? m_CenterPlayer->GetPosition() : m_Eye; // ←理想は常にプレイヤー
    VECTOR upLook = VGet(0.0f, m_LookUp, 0.0f);
    m_Eye = VAdd(VSub(center, VScale(dirF, m_OrbitDist)), upLook);
    // ※ m_OrbitDist==0 なら Eye = center + upLook → FPS 位置になる

    // --- プレイヤー中心へ追従（中心が無ければ位置は変えない）---
    if (m_CenterPlayer) {
        VECTOR center = m_CenterPlayer->GetPosition();
        VECTOR upLook = VGet(0.0f, m_LookUp, 0.0f);
        // TPS：プレイヤーの後方へ m_OrbitDist だけ下がり、少し上から覗く
        VECTOR desired = VAdd(VSub(center, VScale(dirF, m_OrbitDist)), upLook);

        // スムーズ追従（酔い防止）：0.0〜1.0。速くしたければ値↑
        float t = 0.2f;
        m_Eye = VGet(
            m_Eye.x + (desired.x - m_Eye.x) * t,
            m_Eye.y + (desired.y - m_Eye.y) * t,
            m_Eye.z + (desired.z - m_Eye.z) * t
        );
    }
    // m_CenterPlayer が未設定なら何もしない（流れ防止）

    if (m_OrbitDist <= 0.001f) {
        // Eye をほんの少しだけ前へ（めり込み/ちらつき対策）
        m_Eye = VAdd(m_Eye, VScale(dirF, 0.02f));
    }

}

void Camera::Apply()
{
    // 視線ベクトルを使って注視点を作り、DxLibへ適用
    float cosP = cosf(m_Pitch), sinP = sinf(m_Pitch);
    float sinY = sinf(m_Yaw), cosY = cosf(m_Yaw);
    VECTOR dirF = VGet(sinY * cosP, sinP, -cosY * cosP);
    VECTOR target = VAdd(m_Eye, VScale(dirF, 10.0f)); // 10m先を見る

    SetCameraPositionAndTarget_UpVecY(m_Eye, target);
    // 既存のApply方針を踏襲。[1](https://jikeigroupcom-my.sharepoint.com/personal/fca2506010016_edu_fca_ac_jp/Documents/Microsoft%20Copilot%20Chat%20%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB/Camra.cpp)
}
