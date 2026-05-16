#pragma once
#include <vector>
#include <memory>
#include "Effect.h"

class EffectManager {
private:
    std::vector<std::unique_ptr<Effect>> effects;

    // シングルトン化 (ImageManager等に合わせる)
    EffectManager() {}
    ~EffectManager() {}

public:
    // コピー禁止
    EffectManager(const EffectManager&) = delete;
    EffectManager& operator=(const EffectManager&) = delete;

    static EffectManager& GetInstance() {
        static EffectManager instance;
        return instance;
    }

    void Update();
    void Render();

    // エフェクトの登録関数

    // リセット用
    void ClearAll(); 
};
