#include "DxLib.h"
#include "Input.h"
#include "Title.h"

// タイトル画面の描画処理
void Title::Update()
{
    DrawString(100, 100, "タイトル画面 - Zキーでスタート", GetColor(255, 255, 255));
}

// 終了条件を満たしたかを判定する処理
bool Title::CheckGoNext()
{
    return GetInputState(KEY_INPUT_Z) == INPUT_PUSH;
}