switch(currentStage)
{
	case 0:
		map[9][16].itemType = ITEM_COIN;
		map[9][21].itemType = ITEM_POWERUP;
		map[5][22].itemType = ITEM_COIN;
		map[9][23].itemType = ITEM_COIN;
		map[8][64].itemType = ITEM_1UPMASHROOM;
		map[9][78].itemType = ITEM_POWERUP;
		map[5][94].itemType = ITEM_COIN;
		map[9][94].itemType = ITEM_TENCOIN;
		map[9][94].itemCount = 10;
		map[9][101].itemType = ITEM_STAR;
		map[9][106].itemType = ITEM_COIN;
		map[9][109].itemType = ITEM_COIN;
		map[5][109].itemType = ITEM_POWERUP;
		map[9][112].itemType = ITEM_COIN;
		map[5][129].itemType = ITEM_COIN;
		map[5][130].itemType = ITEM_COIN;
		map[9][170].itemType = ITEM_COIN;
	break;
	case 1:
		map[6][30].itemType = ITEM_POWERUP;
		map[9][106].itemType = ITEM_COIN;
		map[5][107].itemType = ITEM_COIN;
		map[9][109].itemType = ITEM_COIN;
		map[5][110].itemType = ITEM_COIN;
		map[9][112].itemType = ITEM_COIN;
		map[5][113].itemType = ITEM_COIN;
	break;
}