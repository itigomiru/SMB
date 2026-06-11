#include"PlayerData.h"
#include"Player.h"

PlayerData& PlayerData::GetInstance()
{
	static PlayerData instance;
	return instance;
}

void PlayerData::AddTime(int num)
{
	time += num;
	if (time < 0)time = 0;
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
	//sound
	if (coin > COIN_MAX)
	{
		coin -= COIN_MAX;
		AddStock(1);
	}
}

int PlayerData::GetStock() const { return stock; }
int PlayerData::GetTime() const { return time; }
int PlayerData::GetScore() const { return score; }
int PlayerData::GetCoin() const { return coin; }

PlayerData::PlayerData()
{
	Reset();
}
void PlayerData::Reset()
{
	playerState = 0;
	time = BASE_TIME;
	stock = BASE_STOCK;
	score = 0;
	coin = 0;
}