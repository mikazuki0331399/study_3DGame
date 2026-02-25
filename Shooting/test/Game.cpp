
#include "Game.h"

Game::Game() {}

static float NormalizeAngle(float a) {
    while (a > DX_PI_F) a -= DX_PI_F * 2.0f;
    while (a < -DX_PI_F) a += DX_PI_F * 2.0f;
    return a;
}

void Game::Update()
{
    // 初回だけ初期化（画面サイズは実行中の実値を取得）
    if (!m_initialized) {
        int w = 0, h = 0, bpp = 0;
        GetScreenState(&w, &h, &bpp);              // 実スクリーンサイズで初期化
        SetUseZBuffer3D(TRUE);
        SetWriteZBuffer3D(TRUE);
        SetUseLighting(TRUE);
        ChangeLightTypeDir(VGet(0.3f, -1.0f, 0.2f));
        SetLightEnable(TRUE);
        m_player.Initialize(VGet(0, 0, 0), 1.7f, 0.35f, 12);
        m_camera.InitializeOnce(w, h);
        m_camera.SetCenterPlayer(&m_player);
        m_camera.SetSensitivity(0.0008f, 0.0006f);
        m_camera.SetOrbit(5.0f, 1.6f);
        m_initialized = true;

        {
            Cube c;
                        // 位置(0,0.5,3)、サイズ(1,1,1)、拡散=薄い青、鏡面=白、塗りつぶし=TRUE
            c.Initialize(
                    VGet(0.0f, 0.5f, 3.0f),     // 中心位置
                    VGet(1.0f, 1.0f, 1.0f),     // 幅・高さ・奥行き
                    GetColor(120, 170, 255),    // Diffuse
                    GetColor(255, 255, 255),    // Specular
                    true                         // 塗りつぶし
                     );
            m_cubes.emplace_back(c);
            
        }
        
                    // 例：複数置きたい場合は追加
        {
            Cube c2;
            c2.Initialize(VGet(2.0f, 0.5f, 5.0f), VGet(1.0f, 1.0f, 1.0f),
                GetColor(255, 180, 120), GetColor(255, 255, 255), true);
            m_cubes.emplace_back(c2);
        }
        m_initialized = true;

    }

    // 任意：Enter で次シーンへ（あなたの条件に合わせて変更OK）
    if (CheckHitKey(KEY_INPUT_RETURN)) m_goNext = true;

    // 更新
   
    m_player.UpdateCameraAligned(m_camera.GetYaw());
    m_camera.Apply();
    m_player.Draw();
    m_camera.Update();
	float camYaw = m_camera.GetYaw();
    float plyYaw = m_player.GetYaw();

    float diff = NormalizeAngle(camYaw - plyYaw);
    if (fabsf(diff) > 0.00872665f) { // 0.5°相当
        m_player.SetYaw(camYaw);
    }

    // ここから3D描画
    m_camera.Apply();

    // 簡単な床グリッド
    int gridColor = GetColor(90, 90, 90);
    for (int i = -20; i <= 20; ++i) {
        DrawLine3D(VGet((float)i, 0.0f, -20.0f), VGet((float)i, 0.0f, 20.0f), gridColor);
        DrawLine3D(VGet(-20.0f, 0.0f, (float)i), VGet(20.0f, 0.0f, (float)i), gridColor);
    }

    for (auto& c : m_cubes) 
    {
        c.Update(); // 将来のアニメ用。今は何もしない実装
        c.Draw();   // AABB（軸平行直方体）で描画
        
    }

    // プレイヤー描画
    m_player.Draw();

    // 2Dオーバレイ（デバッグ）
    DrawFormatString(20, 20, GetColor(255, 255, 255),
        "WASD/Arrow Move  |  Mouse Look  |  Wheel Zoom  |  Enter->Result");

    const float fadeStart = 1.0f;  // ここ以上は常に不透明
    const float fadeEnd = 0.2f;  // ここ以下は完全透明（FPS視点近傍）
    float d = m_camera.GetOrbitDist();

    // 0..1 に正規化（距離が近いほど 0、遠いほど 1）
    float t = (d - fadeEnd) / (fadeStart - fadeEnd);
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    int alpha = (int)(t * 255.0f);
    m_player.SetAlpha(alpha);

}
