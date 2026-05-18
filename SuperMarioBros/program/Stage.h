#pragma once
#include "Scene.h"
#include "ObjectManager.h"

class Stage : public Scene
{
private :
	//	ステージに必要な変数を宣言
	ObjectManager objectManager;
public:
	void Init() override;
	void Update() override;
	void Render() override;
	~Stage() override;
};
