#pragma once
void EnemySpawner::SetSpawner()
{

	SpawnData data1 = { FIERBAR,480.0f, 160.0f, false, true };  //ファイア
	SpawnData data2 = { FIERBAR,784.0f, 96.0f, false, true }; 
	SpawnData data3 = { FIERBAR,960.0f, 96.0f, false, true }; 
	SpawnData data4 = { FIERBAR,1072.0f, 96.0f, false, true }; 
	SpawnData data5 = { FIERBAR,1216.0f, 144.0f, false, true }; 
	SpawnData data6 = { FIERBAR,1344.0f, 144.0f, false, true }; 
	SpawnData data7 = { FIERBAR,1408.0f, 64.0f, false, true }; 
	SpawnData data8 = { BOWSER,2176.0f, 144.0f, false, true };  //クッパ
	
	spawnDataList.push_back(data1);
	spawnDataList.push_back(data2);
	spawnDataList.push_back(data3);
	spawnDataList.push_back(data4);
	spawnDataList.push_back(data5);
	spawnDataList.push_back(data6);
	spawnDataList.push_back(data7);
	spawnDataList.push_back(data8);
	
}