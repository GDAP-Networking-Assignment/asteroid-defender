#include "GameCore.h"
#include "AsteroidSpawner.h"


#define DEBUG_AsteroidSpawner


IMPLEMENT_DYNAMIC_CLASS(AsteroidSpawner)

AsteroidSpawner::AsteroidSpawner() : spawnRate(3.0f), lastSpawnTime(0.0f) {
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
    collider = (BoxCollider*)owner->GetComponent("BoxCollider");
    collider->SetSize(100, 100);
    collider->SetName("Asteroid");
    for (const auto& other : collider->OnCollisionEnter()) {
        if (other->GetOwner()->GetName() != "Asteroid") {
            // Mark both the asteroid and the player for removal
            this->owner->ownerScene->RemoveEntity(this->owner->GetUid());
            this->owner->ownerScene->RemoveEntity(other->GetOwner()->GetUid());

            LOG("HIT SOMETHING");
            break;
        }
    }
   

    // Additional update logic, such as moving asteroids, could be here
}

void AsteroidSpawner::SpawnAsteroid() {
   
   

    
    // Decide on the type of the asteroid to spawn.
    AsteroidFactory::AsteroidType type = (rand() % 2 == 0) ? AsteroidFactory::AsteroidType::Big : AsteroidFactory::AsteroidType::Small;

    // Create a new asteroid entity in the scene.
    Entity* newAsteroid = owner->GetParentScene()->CreateEntity();

    // Set the name based on the type.
    newAsteroid->SetName(type == AsteroidFactory::AsteroidType::Small ? "AsteroidSmall" : "AsteroidBig");

    // Create an AsteroidFactory component on the new asteroid entity, not on the owner of the spawner.
    AsteroidFactory* factory = (AsteroidFactory*)newAsteroid->CreateComponent("AsteroidFactory");

    // Use the factory to create the appropriate type of asteroid on the new entity.
    Asteroid* asteroid = factory->CreateAsteroid(newAsteroid, type);

    // Initialize the new asteroid's transform and other components as needed.
    Transform& transform = newAsteroid->GetTransform();
    transform.position.x = static_cast<float>(rand() % 1280);
    transform.position.y = 0;
    // Set up the sprite for the asteroid based on its type.
    Sprite* sprite = (Sprite*)newAsteroid->CreateComponent("Sprite");
    TextureAsset* texture = nullptr;
    if (type == AsteroidFactory::AsteroidType::Small) {
        sprite->SetTextureAsset(
            (TextureAsset*)AssetManager::Instance().GetAsset("MeteorSmall_48526c0d-ca5d-4681-8fe5-93726d5906fa")
        );
    }
    else {
        sprite->SetTextureAsset(
        (TextureAsset*)AssetManager::Instance().GetAsset("MeteorBig_a7319cea-2d19-4515-b910-7d10f6df0ec3")
            );
   
    }

 
}
