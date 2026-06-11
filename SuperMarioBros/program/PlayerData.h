#pragma once

class PlayerData
{
private:
	PlayerData();
	PlayerData(const PlayerData&) = delete;
	PlayerData& operator=(const PlayerData&) = delete;
	int stock;
	int score;
	int coin;
	int time;
public:
	const int BASE_STOCK = 3;
	const int STOCK_MAX = 99;
	const int SCORE_MAX = 999999;
	const int COIN_MAX = 99;
	const int TIME_MAX = 999;
	static PlayerData& GetInstance();
	void AddStock(int num);
	void AddScore(int num);
	void AddCoin(int num);
	void AddTime(int num);
	void Reset();
	int GetStock() const;
	int GetTime() const;
	int GetScore() const;
	int GetCoin() const;
};