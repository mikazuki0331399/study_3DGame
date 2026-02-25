#include "DxLib.h"
#include "Input.h"
#include "Result.h"

// リザルト画面の描画処理
void Result::Update()
{
    DrawString(100, 100, "リザルト画面 - Zキーでタイトルへ", GetColor(255, 255, 255));
}

// 終了条件を満たしたかを判定する処理
bool Result::CheckGoNext()
{
    return GetInputState(KEY_INPUT_Z) == INPUT_PUSH;
}
