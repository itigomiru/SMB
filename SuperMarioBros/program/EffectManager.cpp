#include "EffectManager.h"

void EffectManager::Update() {
    for (auto it = effects.begin(); it != effects.end();) {
        (*it)->Update();
        
        if ((*it)->IsDead()) {
            it = effects.erase(it); // 寿命が来たらリストから削除
        } else {
            ++it;
        }
    }
}

void EffectManager::Render() {
    for (const auto& effect : effects) {
        effect->Render();
    }
}


void EffectManager::ClearAll() {
    effects.clear();
}
