
#pragma once
#include "DxLib.h"

// ゲームシーン専用のシンプルなキューブ描画ユーティリティ
// 使い方：
//   Cube cube;
//   cube.Initialize(VGet(0,1,0), VGet(2,2,2), GetColor(180,60,60));
//   （ゲームループ内）cube.Update(); cube.Draw();
//   終了時 cube.Finalize();

class Cube
{
public:
    // pos: 中心座標（ワールド）
    // size: 幅(x)・高さ(y)・奥行き(z)
    // difColor: 拡散色
    // spcColor: 鏡面色（未指定なら白）
    // fill: TRUE=塗りつぶし / FALSE=ワイヤー
    void Initialize(
        const VECTOR& pos,
        const VECTOR& size,
        unsigned int difColor,
        unsigned int spcColor = 0xFFFFFFFF,
        bool fill = true
    );

    void Update();   // いまは何もしない（将来アニメ等のフック用）
    void Draw() const;
    void Finalize(); // いまは何もしない（将来リソース破棄用）

    // セッター／ゲッター（軽く）
    void         SetPosition(const VECTOR& p) { m_Pos = p; }
    void         SetSize(const VECTOR& s) { m_Size = s; }
    const VECTOR& GetPosition() const { return m_Pos; }
    const VECTOR& GetSize() const { return m_Size; }
    void         SetColor(unsigned int dif, unsigned int spc) { m_Dif = dif; m_Spc = spc; }
    void         SetFill(bool f) { m_Fill = f; }

private:
    // AABB（中心＋サイズ）→ DrawCube3D に渡す min/max へ変換
    void computeMinMax(VECTOR& outMin, VECTOR& outMax) const;

    VECTOR       m_Pos{ 0.0f, 0.0f, 0.0f };
    VECTOR       m_Size{ 1.0f, 1.0f, 1.0f };
    unsigned int m_Dif = 0xFFAAAAAA; // 拡散色
    unsigned int m_Spc = 0xFFFFFFFF; // 鏡面色
    bool         m_Fill = true;
};

