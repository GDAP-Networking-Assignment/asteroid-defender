#include "GameCore.h"
#include "AsteroidSpawner.h"

IMPLEMENT_DYNAMIC_CLASS(AsteroidSpawner)

AsteroidSpawner::AsteroidSpawner() : spawnRate(5.0f), lastSpawnTime(0.0f) {
    // Constructor
}

AsteroidSpawner::~AsteroidSpawner() {
    // Destructor
}

void AsteroidSpawner::Initialize() {
}

void AsteroidSpawner::Update() {
    if (NetworkEngine::Instance().IsClient()) return;
    float deltaTime = Time::Instance().DeltaTime();
    lastSpawnTime += deltaTime;
    if (lastSpawnTime >= spawnRate) {
    
        // Reset the timer
        SpawnAsteroid();
		lastSpawnTime = 0.0f;
		
    }
    // Additional update logic, such as moving asteroids, could be here
}

void AsteroidSpawner::SpawnAsteroid() {
 
	AsteroidFactory* factory = (AsteroidFactory*)owner->CreateComponent("AsteroidFactory");
	AsteroidFactory::AsteroidType type = (rand() % 2 == 0) ? AsteroidFactory::AsteroidType::Big : AsteroidFactory::AsteroidType::Small;
	Asteroid* asteroid = factory->CreateAsteroid(owner, type);

	if (type == AsteroidFactory::AsteroidType::Small) {
		owner->SetName("Asteroid");
		sprite = (Sprite*)owner->CreateComponent("Sprite");
		sprite->SetTextureAsset(
			(TextureAsset*)AssetManager::Instance().GetAsset("MeteorSmall_48526c0d-ca5d-4681-8fe5-93726d5906fa")
		);
	}
	else if (type == AsteroidFactory::AsteroidType::Big) {
		sprite = (Sprite*)owner->CreateComponent("Sprite");
		sprite->SetTextureAsset(
			(TextureAsset*)AssetManager::Instance().GetAsset("MeteorBig_a7319cea-2d19-4515-b910-7d10f6df0ec3")
		);
	}

}
