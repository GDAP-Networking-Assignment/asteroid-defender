#include "GameCore.h"
#include "AsteroidSmall.h"

IMPLEMENT_DYNAMIC_CLASS(AsteroidSmall);

void AsteroidSmall::Initialize() {
    // Initialization specific to SmallAsteroid
    Component::Initialize();
    //collider = (BoxCollider*)owner->CreateComponent("BoxCollider");
    sprite = (Sprite*)owner->GetComponent("Sprite");
    sprite->SetTextureAsset(

        (TextureAsset*)AssetManager::Instance().GetAsset("MeteorSmall_48526c0d-ca5d-4681-8fe5-93726d5906fa")
    );
    Asteroid::Initialize();
    size = 10; // Example size for a small asteroid
    // Set small asteroid sprite and other properties
}

void AsteroidSmall::Update() {
    // Update logic specific to SmallAsteroid
    Asteroid::Update();
}