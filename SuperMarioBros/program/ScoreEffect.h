#pragma once
#include "Float2.h"
#include "Effect.h"

class ScoreEffect : public Effect
{
public:
    ScoreEffect(Float2 position, int score);
    ~ScoreEffect() = default;

    void Update() override;

    void Render(float cameraX) override;

    enum SCORE
    {
        SCORE_100 = 0,
        SCORE_200 = 1,
        SCORE_400 = 2,
        SCORE_500 = 3,
        SCORE_800 = 4,
        SCORE_1000 = 5,
        SCORE_2000 = 6,
        SCORE_4000 = 7,
        SCORE_5000 = 8,
        SCORE_8000 = 9,
        SCORE_1UP = 10,
    };

private:
    Float2 speed;
    int scoreValue;

    int timer;
    const int LIFE_TIME = 40;
	const int REAL_SCORE[11] = { 100, 200, 400, 500, 800, 1000, 2000, 4000, 5000, 8000, 0 };
};