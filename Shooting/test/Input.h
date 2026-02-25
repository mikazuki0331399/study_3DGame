#pragma once

enum InputState
{
    INPUT_OFF,     // キーが押されていない状態
    INPUT_PUSH,    // キーが押された（押した瞬間）
    INPUT_ON,      // キーが押されている（押し続けている状態）
    INPUT_RELEASE  // キーが離された（離した瞬間）
};

/// <summary>
/// 指定されたキーの状態を取得する関数
/// </summary>
/// <param name="keyCode">対象のキーコード（例：KEY_INPUT_Z）</param>
/// <returns>キーの状態（INPUT_OFF, INPUT_PUSH, INPUT_ON, INPUT_RELEASE）</returns>
InputState GetInputState(int keyCode);
