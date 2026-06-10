#include "EffectManager.h"
#include <algorithm>

void EffectManager::Update()
{
    // エフェクト更新
    for (auto& effect : effects)
    {
        if (effect)
        {
            effect->Update();
        }
    }

    // 死亡したエフェクトを削除
    effects.erase(
        std::remove_if(
            effects.begin(),
            effects.end(),
            [](const std::unique_ptr<Effect>& effect)
            {
                return !effect || effect->IsDead();
            }),
        effects.end());

    // Update中に追加されたエフェクトを反映
    for (auto& effect : pendingEffects)
    {
        effects.push_back(std::move(effect));
    }

    pendingEffects.clear();
}

void EffectManager::Render(float cameraX)
{
    for (const auto& effect : effects)
    {
        if (!effect) continue;

        effect->Render(cameraX);
    }
}

void EffectManager::AddEffect(std::unique_ptr<Effect> effect)
{
    pendingEffects.push_back(std::move(effect));
}

void EffectManager::ClearAll()
{
    effects.clear();
    pendingEffects.clear();
}