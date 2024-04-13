#pragma once

#include "GameCore.h"

class AsteroidSpawner : public Component {
	DECLARE_DYNAMIC_DERIVED_CLASS(AsteroidSpawner, Component)
public:
    void Initialize() override;
    void Update() override;
    void Load(json::JSON& node) override;

private:
    void SpawnAsteroid();

private:
    float spawnRate = 0.7f; // Seconds between spawns
    float lastSpawnTime = 0.0f; // Timestamp of the last spawn
};
