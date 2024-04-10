#include "EngineCore.h"
#include "Engine.h"
#include "EngineTime.h"
#include "RenderSystem.h"
#include "SceneManager.h"
#include "Entity.h"
#include "InputSystem.h"

#include <thread>

#include "AssetManager.h"
#include "AudioSystem.h"
#include "CollisionSystem.h"
#include "Component.h"

#include "NetworkEngine.h"

extern void Engine_Register();

void Engine::Initialize(int _ServerOrClient)
{
	Engine_Register();
	NetworkEngine::Instance().Initialize(_ServerOrClient == 0);

	// Load the managers
	AudioSystem::Instance().Load("../Assets/AudioSystem.json");
	AssetManager::Instance().Load("../Assets/AssetManager.json");

	AudioSystem::Instance().Initialize();
	AssetManager::Instance().Initialize();

	RenderSystem::Instance().Initialize(NetworkEngine::Instance().IsClient());
	SceneManager::Instance().Load();

	SceneManager::Instance().Initialize();
	InputSystem::Instance().RegisterQuitEventHandler([this] {isRunning = false; });
}

void Engine::Destroy()
{
	Time::Instance().Destroy();
	CollisionSystem::Instance().Destroy();
	SceneManager::Instance().Destroy();
	AssetManager::Instance().Destroy();
	AudioSystem::Instance().Destroy();
	RenderSystem::Instance().Destroy();
}

void Engine::GameLoop()
{
	while (isRunning)
	{
		Time::Instance().Update();

		// --------------------- Pre-update Phase ---------------------
		NetworkEngine::Instance().PreUpdate();
		SceneManager::Instance().PreUpdate();

		// --------------------- Update Phase ---------------------
		InputSystem::Instance().Update();
		SceneManager::Instance().Update();
		RenderSystem::Instance().Update();
		CollisionSystem::Instance().Update();

		// --------------------- Post-update Phase ---------------------
		SceneManager::Instance().PostUpdate();
		NetworkEngine::Instance().PostUpdate();
	}
}
