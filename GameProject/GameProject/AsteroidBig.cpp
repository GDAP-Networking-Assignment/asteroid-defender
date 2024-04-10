#include "GameCore.h"
#include "AsteroidBig.h"

IMPLEMENT_DYNAMIC_CLASS(AsteroidBig);

AsteroidBig::AsteroidBig()
{
}

AsteroidBig::~AsteroidBig()
{
}

void AsteroidBig::Initialize()
{
	Component::Initialize();
	// Initialization specific to BigAsteroid
	collider = (BoxCollider*)owner->CreateComponent("BoxCollider");
	owner->SetName("Asteroid");

	sprite = (Sprite*)owner->CreateComponent("Sprite");
	sprite->SetTextureAsset(

		(TextureAsset*)AssetManager::Instance().GetAsset("MeteorBig_a7319cea-2d19-4515-b910-7d10f6df0ec3")

	);
	size = 50; // Example size for a big asteroid
	// Set big asteroid sprite and other properties
}

void AsteroidBig::Update()
{
	// Update logic specific to BigAsteroid
	Asteroid::Update();
}
