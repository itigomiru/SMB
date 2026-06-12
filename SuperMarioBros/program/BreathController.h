#pragma once
#include "Object.h"
#include "Float2.h"

class Breath : public Object
{
public:
	Breath(
		bool isRight, bool isUp, float riseWidth, Float2 position, float moveSpeed
	);

	void Update(float cameraX) override;
	void Render(float cameraX) override;

private:
	bool isRight; // å¸Ç´
	bool isUp; // è„è∏Ç∑ÇÈÇ©Ç«Ç§Ç©

	float startY; // è„è∏äJénà íu
	float riseWidth; // è„è∏ïù

	static const int BREATH_W = 32; 
	static const int BREATH_H = 16;
};