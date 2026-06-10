#pragma once
#include <vector>
#include <memory>
#include "Effect.h"

class EffectManager {
private:
	std::vector<std::unique_ptr<Effect>> effects;
	std::vector<std::unique_ptr<Effect>> pendingEffects;

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
	void Render(float cameraX);

	// エフェクトの登録関数
	void AddEffect(std::unique_ptr<Effect> effect);

	// リセット用
	void ClearAll();
};
