#include "EffectManager.h"

void EffectManager::Update() 
{
    for (auto it = effects.begin(); it != effects.end();) {
        (*it)->Update();
        
        if ((*it)->IsDead()) {
            it = effects.erase(it); // 寿命が来たらリストから削除
        } else {
            ++it;
        }
    }
}

void EffectManager::Render(float cameraX) 
{
    for (const auto& effect : effects) {
        effect->Render(cameraX);
    }
}

// エフェクトの登録関数
void EffectManager::AddEffect(std::unique_ptr<Effect> effect) {
    effects.push_back(std::move(effect));
}


void EffectManager::ClearAll() {
    effects.clear();
}
