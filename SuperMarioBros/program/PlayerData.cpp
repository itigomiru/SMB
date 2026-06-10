#include"PlayerData.h"
#include"Player.h"

PlayerData& PlayerData::GetInstance()
{
	static PlayerData instance;
	return instance;
}

void PlayerData::AddStock(int num)
{
	stock += num;
	if (stock > STOCK_MAX)stock = STOCK_MAX;
}

void PlayerData::AddScore(int num)
{
	score += num; 
}

void PlayerData::AddCoin(int num)
{
	coin += num; 
	if (coin >= 100)
	{
		coin -= 100;
		AddStock(1);
	}
}

int PlayerData::GetStock() const { return stock; }

PlayerData::PlayerData()
{
	Reset();
}
void PlayerData::Reset()
{
	stock = BASE_STOCK;
	score = 0;
	coin = 0;
}
