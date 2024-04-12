#include "GameCore.h"
#include "AsteroidBig.h"
#include "CircleCollider.h"

IMPLEMENT_DYNAMIC_CLASS(AsteroidBig);

void AsteroidBig::Initialize()
{
	Asteroid::Initialize();
	sprite->SetTextureAsset(
		(TextureAsset*)AssetManager::Instance().GetAsset("MeteorBig_a7319cea-2d19-4515-b910-7d10f6df0ec3")
	);
}
