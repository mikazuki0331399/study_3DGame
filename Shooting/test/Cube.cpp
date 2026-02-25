
#include "Cube.h"

void Cube::Initialize(const VECTOR& pos, const VECTOR& size,
    unsigned int difColor, unsigned int spcColor, bool fill)
{
    m_Pos = pos;
    m_Size = size;
    m_Dif = difColor;
    m_Spc = spcColor;
    m_Fill = fill;

    // ※Zバッファやライトは「ゲームシーンの初期化」で一度だけ有効化しておく想定
    //   SetUseZBuffer3D(TRUE); SetWriteZBuffer3D(TRUE);
    //   SetUseLighting(TRUE); ChangeLightTypeDir(...); など
}

void Cube::Update()
{
    // いまは特になし（将来的に点滅・移動・拡縮など入れやすいフック）
}

void Cube::computeMinMax(VECTOR& outMin, VECTOR& outMax) const
{
    // 中心 m_Pos とサイズ m_Size（幅・高さ・奥行き）から AABB の min/max を算出
    outMin = VGet(m_Pos.x - m_Size.x * 0.5f,
        m_Pos.y - m_Size.y * 0.5f,
        m_Pos.z - m_Size.z * 0.5f);

    outMax = VGet(m_Pos.x + m_Size.x * 0.5f,
        m_Pos.y + m_Size.y * 0.5f,
        m_Pos.z + m_Size.z * 0.5f);
}

void Cube::Draw() const
{
    VECTOR mn, mx;
    computeMinMax(mn, mx);

    // DrawCube3D は軸に平行な直方体（AABB）を描く
    DrawCube3D(
        mn, mx,
        m_Dif,  // 拡散色
        m_Spc,  // 鏡面色
        m_Fill ? TRUE : FALSE
    );
}

void Cube::Finalize()
{
    // いまは GPU リソースなし（MV1 等に差し替えたらここで破棄）
}
