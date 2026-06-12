#pragma once
	switch (tileManager->GetCurrentStage())
	{
	case 0:
		spawnDataList = {
			{ GOOMBA,          320.0f, 190.0f, false, true },
			{ GOOMBA,          640.0f, 190.0f, false, true },
			{ GOOMBA,          800.0f, 190.0f, false, true },
			{ GOOMBA,          832.0f, 190.0f, false, true },
			{ GOOMBA,         1280.0f,  62.0f, false, true },
			{ GOOMBA,         1312.0f,  62.0f, false, true },
			{ GOOMBA,         1552.0f, 190.0f, false, true },
			{ GOOMBA,         1584.0f, 190.0f, false, true },
			{ KOOPA_TROOPA,   1696.0f, 182.0f, false, true },
			{ GOOMBA,         1840.0f, 190.0f, false, true },
			{ GOOMBA,         1872.0f, 190.0f, false, true },
			{ GOOMBA,         2016.0f, 190.0f, false, true },
			{ GOOMBA,         2048.0f, 190.0f, false, true },
			{ GOOMBA,         2096.0f, 190.0f, false, true },
			{ GOOMBA,         2784.0f, 190.0f, false, true },
			{ GOOMBA,         2816.0f, 190.0f, false, true }
		};
		break;
	case 1:
		spawnDataList = {
			{ FIREBAR,480.0f, 160.0f, false, true },  //ファイア
			{ FIREBAR,784.0f, 96.0f, false, true },
			{ FIREBAR,960.0f, 96.0f, false, true },
			{ FIREBAR,1072.0f, 96.0f, false, true },
			{ FIREBAR,1216.0f, 144.0f, false, true },
			{ FIREBAR,1344.0f, 144.0f, false, true },
			{ FIREBAR,1408.0f, 64.0f, false, true },
			{ BOWSER,2176.0f, 144.0f, false, true },  //クッパ
		};
		break;
	}
