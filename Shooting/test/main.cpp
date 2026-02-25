// 各必要なヘッダーファイルをインクルード
#include "DxLib.h"
#include "Input.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "Camera.h"
#include"Player.h"

// ゲーム内の各シーンを識別する列挙型
enum SceneType {
    SCENE_TITLE,
    SCENE_GAME,
    SCENE_RESULT
};

constexpr int SCREEN_W = 1280;
constexpr int SCREEN_H = 720;

// アプリケーションのエントリーポイント（WinMain関数）
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // 画面サイズと色深度を設定
    SetGraphMode(SCREEN_W, SCREEN_H, 32);

    // DxLibの初期化に失敗した場合は終了
    if (DxLib_Init() == -1)
        return 0;

    SetDrawScreen(DX_SCREEN_BACK);

    // 背景色を暗めに設定
    SetBackgroundColor(0, 0, 20);
    // ウィンドウモードを有効にする
    ChangeWindowMode(TRUE);
    // 裏画面に描画する設定（ダブルバッファリング）
    SetDrawScreen(DX_SCREEN_BACK);

    // タイトルシーンのインスタンスを作成
    Title title;
    // ゲームシーンのインスタンスを作成
    Game game;
    // リザルトシーンのインスタンスを作成
    Result result;

    // 最初に表示するのはタイトルシーン
    SceneType currentScene = SCENE_TITLE;

    // ゲームのメインループ（ウィンドウが閉じられるまで繰り返す）
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
    {
        // 現在のシーンに応じて、各シーンの処理を実行
        switch (currentScene)
        {
        case SCENE_TITLE:
            // タイトルシーンの更新処理
            title.Update();
            // タイトルシーンの終了条件を確認してゲームシーンへ移動
            if (title.CheckGoNext()) currentScene = SCENE_GAME;
            break;

        case SCENE_GAME:
            // ゲームシーンの更新処理
            game.Update();
            // ゲームシーンの終了条件を確認してリザルトシーンへ移動
            if (game.CheckGoNext()) currentScene = SCENE_RESULT;
            break;

        case SCENE_RESULT:
            // リザルトシーンの更新処理
            result.Update();
            // リザルトシーンの終了条件を確認してタイトルシーンへ移動
            if (result.CheckGoNext()) currentScene = SCENE_TITLE;
            break;
        }
    }

    // DxLibの終了処理
    DxLib_End();
    return 0;
}

