#pragma once

#include "EngineCore.h"
#include "Scene.h"
#include "Transform.h"
#include "NetworkEngine.h"
#include "Component.h"
#include "Asteroid.h"
#include "AsteroidFactory.h"
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


private:
    void SpawnAsteroid();
    float spawnRate; // Seconds between spawns
    float lastSpawnTime; // Timestamp of the last spawn
    Sprite* sprite = nullptr;
    BoxCollider* collider = nullptr;
    

};
