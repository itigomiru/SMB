#pragma once

class UI
{
private:
    int nextStage;
    int timer = 0;
    const int DISPLAY_TIME = 90;
    TileManager* tileManager = nullptr;
	UI();
    ~UI();
	UI(const UI&) = delete;
	UI& operator=(const UI&) = delete;

    int coinAnimationCounter;
    int coinAnimWaitCounter;

    static const int COIN_FRAME_W = 8;
    static const int COIN_FRAME_H = 8;
    static const int COIN_ANIM_SPEED = 8;
    static const int COIN_ANIM_FRAMES = 3;
    static const int COIN_ANIM_WAIT_TIME = 25;


public:
	static UI& GetInstance() {
		static UI instance;
		return instance;
	}
    
    void Render();
    void SetTileManager(TileManager* tm);

};