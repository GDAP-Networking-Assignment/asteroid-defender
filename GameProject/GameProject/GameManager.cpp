#include "GameCore.h"
#include "GameManager.h"
#include "Globals.h"

IMPLEMENT_DYNAMIC_CLASS(GameManager);

void GameManager::Initialize()
{
	RegisterRPC(GetHashCode("RPCSpawnPlayer"), std::bind(&GameManager::RPCSpawnPlayer, this, std::placeholders::_1));
	Globals::Instance().gm = this;
}

void GameManager::Update()
{
	if (NetworkEngine::Instance().serverReady && ! isSpawned) {
		SendRPCSpawnPlayer();
		isSpawned = true;
	}

	if (NetworkEngine::Instance().IsServer() && NetworkEngine::Instance().GetConnections().size() > 1 && !isStart)
	{
		Entity* spawnerEntity = SceneManager::Instance().CreateEntity();
		AsteroidSpawner* spawnerComponent = (AsteroidSpawner*)spawnerEntity->CreateComponent("AsteroidSpawner");
		isStart = true;
	}
}

void GameManager::SendRPCSpawnPlayer()
{
	RakNet::BitStream bitStream;
	bitStream.Write((unsigned char)MSG_SCENE_MANAGER);
	bitStream.Write((unsigned char)MSG_RPC);

	bitStream.Write(SceneManager::Instance().GetActiveSceneId());
	bitStream.Write(owner->GetUid());
	bitStream.Write(GetUid());
	bitStream.Write(GetHashCode("RPCSpawnPlayer"));
	bitStream.Write(NetworkEngine::Instance().rakInterface->GetMyGUID().g);
	NetworkEngine::Instance().SendPacket(bitStream);
}

void GameManager::RPCSpawnPlayer(RakNet::BitStream& bitStream)
{
	Entity* playerEntity = SceneManager::Instance().CreateEntity();
	Player* playerComponent = (Player* )playerEntity->CreateComponent("Player");
	bitStream.Read(playerComponent->networkGuid);
	playerEntity->GetTransform().position.y = RenderSystem::Instance().GetWindowSize().y - 24;
	playerEntity->GetTransform().position.x = rand() % RenderSystem::Instance().GetWindowSize().x;
}
