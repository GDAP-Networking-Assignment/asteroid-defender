#pragma once
#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "GameCore.h"

class GameManager : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(GameManager, Component);

private:
	std::vector<Player*> players;
	bool isStart = false;
	bool isSpawned = false;

public:
	void Initialize() override;
	void Update() override;

	void SendRPCSpawnPlayer();
	void RPCSpawnPlayer(RakNet::BitStream& bitStream);
};

#endif

