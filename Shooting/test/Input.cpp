#include "DxLib.h"
#include "Input.h"

// 指定されたキーの状態を取得する関数
InputState GetInputState(int keyCode)
{
    // 前のフレームのキー入力状態を記録するバッファ
    static char prevKeyBuf[256] = {};

    // 現在のフレームのキー入力状態を取得
    char keyBuf[256];
    GetHitKeyStateAll(keyBuf);

    InputState state;

    // 前のフレームでは押されておらず、今フレームで押された → 押された瞬間
    if (prevKeyBuf[keyCode] == 0 && keyBuf[keyCode] != 0)
        state = INPUT_PUSH;
    // 前のフレームでも今フレームでも押されている → 押し続けている
    else if (prevKeyBuf[keyCode] != 0 && keyBuf[keyCode] != 0)
        state = INPUT_ON;
    // 前のフレームでは押されていたが、今フレームで離された → 離した瞬間
    else if (prevKeyBuf[keyCode] != 0 && keyBuf[keyCode] == 0)
        state = INPUT_RELEASE;
    // 押されていない状態
    else
        state = INPUT_OFF;

    // 現在の状態を次フレームの比較用に保存
    prevKeyBuf[keyCode] = keyBuf[keyCode];
    return state;
}
