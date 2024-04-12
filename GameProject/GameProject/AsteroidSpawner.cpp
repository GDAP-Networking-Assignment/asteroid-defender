#include "GameCore.h"
#include "AsteroidSpawner.h"

#define DEBUG_AsteroidSpawner

IMPLEMENT_DYNAMIC_CLASS(AsteroidSpawner)

void AsteroidSpawner::Initialize() {

}

void AsteroidSpawner::Update() {
    if (NetworkEngine::Instance().IsClient()) return;
    lastSpawnTime += Time::Instance().DeltaTime();
    if (lastSpawnTime >= spawnRate) {
        // Reset the timer
        SpawnAsteroid();
		lastSpawnTime = 0.0f;
		
    }
}

void AsteroidSpawner::Load(json::JSON& node)
{
    Component::Load(node);
    if (node.hasKey("SpawnRate"))
    {
        spawnRate = static_cast<float>(node.at("SpawnRate").ToFloat());
    }
}

void AsteroidSpawner::SpawnAsteroid() {
    // Decide on the type of the asteroid to spawn.
    AsteroidFactory::AsteroidType type = (rand() % 2 == 0) ? 
        AsteroidFactory::AsteroidType::Big : AsteroidFactory::AsteroidType::Small;

    AsteroidFactory::CreateAsteroid(type);
}
