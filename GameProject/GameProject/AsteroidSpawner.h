#pragma once

#include "EngineCore.h"
#include "Scene.h"
#include "Transform.h"
#include "NetworkEngine.h"
#include "Component.h"
#include "Asteroid.h"
#include <cstdlib>
#include <ctime>
#include <vector>
class AsteroidSpawner : public Component {
	DECLARE_DYNAMIC_DERIVED_CLASS(AsteroidSpawner, Component)
public:
    AsteroidSpawner();
    virtual ~AsteroidSpawner() override;

    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Serialize(RakNet::BitStream& bitStream) const override;
    virtual void Deserialize(RakNet::BitStream& bitStream) override;

private:
    void SpawnAsteroid();
    float spawnRate; // Seconds between spawns
    float lastSpawnTime; // Timestamp of the last spawn
    Sprite* sprite = nullptr;
    Sprite* sprite2 = nullptr;

};
