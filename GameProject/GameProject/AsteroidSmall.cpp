#include "GameCore.h"
#include "AsteroidSmall.h"
#include "CircleCollider.h"

IMPLEMENT_DYNAMIC_CLASS(AsteroidSmall);

void AsteroidSmall::Initialize() {
    Asteroid::Initialize();
    sprite->SetTextureAsset(
        (TextureAsset*)AssetManager::Instance().GetAsset("MeteorSmall_48526c0d-ca5d-4681-8fe5-93726d5906fa")
    );
}