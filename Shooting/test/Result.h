#pragma once

/// <summary>
/// リザルト画面の処理を行うクラス
/// </summary>
class Result
{
public:
    /// <summary>
    /// リザルト画面を描画する処理
    /// </summary>
    void Update();

    /// <summary>
    /// Zキーが押されたかを判定する処理
    /// </summary>
    /// <returns>押された場合は true</returns>
    bool CheckGoNext();
};
