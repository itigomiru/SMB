#pragma once

class PlayerData
{
private:
	PlayerData();
	PlayerData(const PlayerData&) = delete;
	PlayerData& operator=(const PlayerData&) = delete;
public:
	const int BASE_STOCK = 3;
	const int STOCK_MAX = 99;
	static PlayerData& GetInstance();
	int stock;
	int score;
	int coin;
	void AddStock(int num);
	void AddScore(int num);
	void AddCoin(int num);
	int GetStock() const;
};