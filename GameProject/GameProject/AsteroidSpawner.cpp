#include "GameCore.h"
#include "AsteroidSpawner.h"


IMPLEMENT_DYNAMIC_CLASS(AsteroidSpawner)

AsteroidSpawner::AsteroidSpawner() : spawnRate(2.0f), lastSpawnTime(0.0f) {
    // Constructor
}

AsteroidSpawner::~AsteroidSpawner() {
    // Destructor
}

void AsteroidSpawner::Initialize() {
    Component::Initialize();
    srand(static_cast<unsigned int>(time(nullptr))); // Seed for asteroid spawn position
  
    //sprite2 = (Sprite*)owner->GetComponent("Sprite");
    
   
   
    /*sprite2->SetTextureAsset(

        (TextureAsset*)AssetManager::Instance().GetAsset("MeteorSmall_48526c0d-ca5d-4681-8fe5-93726d5906fa")
    );*/
}

void AsteroidSpawner::Update() {
    
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
    // Create a new asteroid entity at a random x position at the top of the screen
    Entity* asteroidEntity = owner->GetParentScene()->CreateEntity();
    Asteroid* asteroid = (Asteroid*)asteroidEntity->GetComponent("Asteroid");
    asteroidEntity->GetTransform().position = owner->GetTransform().position;
  


}

void AsteroidSpawner::Serialize(RakNet::BitStream& bitStream) const {
    // Implement serialization logic for any necessary asteroid state
}

void AsteroidSpawner::Deserialize(RakNet::BitStream& bitStream) {
    // Implement deserialization logic for any necessary asteroid state
}