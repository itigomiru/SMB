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

    int coinFrame;
    int coinTimer;

    static const int COIN_FRAME_W = 8;
    static const int COIN_FRAME_H = 8;
    static const int COIN_FRAME_MAX = 3;
    static const int COIN_ANIME_INTERVAL = 10;


public:
	static UI& GetInstance() {
		static UI instance;
		return instance;
	}
    
    void Render();
    void SetTileManager(TileManager* tm);

};