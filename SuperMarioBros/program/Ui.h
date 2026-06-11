#pragma once

class UI
{
private:
    int nextStage;
    int timer = 0;
    const int DISPLAY_TIME = 90;
    TileManager* tileManager = nullptr;


public:
    UI(int stageNum = 0);
    void Init();
    void Update();
    void Render();
    ~UI();
    void SetTileManager(TileManager* tm);

};