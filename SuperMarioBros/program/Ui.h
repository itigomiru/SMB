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


public:
	static UI& GetInstance() {
		static UI instance;
		return instance;
	}
    
    void Render();
    void SetTileManager(TileManager* tm);

};