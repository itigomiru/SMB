#pragma once
#include "Effect.h"

class FireballEffect : public Effect {
private:
    int animTimer = 0;          // アニメーション用のカウンター
    int currentFrame = 0;       // 現在のフレーム（0〜2）

    // 定数（画像のサイズに合わせて調整してください）
    static const int FRAME_COUNT = 3;  // 全3コマ
    static const int ANIM_SPEED = 3;   // コマの切り替え速度
    static const int FRAME_WIDTH = 16; // 1コマの横幅 (16x16の場合)
    static const int FRAME_HEIGHT = 16;// 1コマの縦幅

public:
    // 親クラスのコンストラクタを呼び出す
    FireballEffect(float startX, float startY) : Effect(startX, startY) {}

    void Update() override;
    void Render(float cameraX) override; 
};