#include "Item.h"


bool Item::SpawnUpdate()
{
	if (spawnWait > 0)
	{
		spawnWait--;
		return false;
	}
	pos.y -= SPAWN_SPEED;
	if (pos.y <= spawnPos.y - size.h)
	{
		pos.y = spawnPos.y - size.h;
		speed.y = 0;
		return true;
	}
	return false;
}

void Item::SetTileManager(TileManager* tm)
{
	tileManager = tm;
}
