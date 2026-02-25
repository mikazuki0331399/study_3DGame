#pragma once

/// <summary>
/// タイトル画面の処理を行うクラス
/// </summary>
class Title
{
public:
    /// <summary>
    /// タイトル画面を描画する処理
    /// </summary>
    void Update();

    /// <summary>
    /// 終了条件を満たしたかを判定する処理
    /// </summary>
    /// <returns>押された場合は true</returns>
    bool CheckGoNext();
};
