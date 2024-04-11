#include "GameCore.h"
#include "AsteroidSmall.h"

IMPLEMENT_DYNAMIC_CLASS(AsteroidSmall);

void AsteroidSmall::Initialize() {
    // Initialization specific to SmallAsteroid
    Asteroid::Initialize();
    //collider = (BoxCollider*)owner->CreateComponent("BoxCollider");
    
    size = 10; // Example size for a small asteroid
    // Set small asteroid sprite and other properties
}

void AsteroidSmall::Update() {
    // Update logic specific to SmallAsteroid
    Asteroid::Update();
    Transform& transform = owner->GetTransform();
    transform.position += velocity * Time::Instance().DeltaTime();

    if (transform.position.y > screenHeight) {
        transform.position.y = -size;
        transform.position.x = static_cast<float>(rand() % screenWidth);
    }
}