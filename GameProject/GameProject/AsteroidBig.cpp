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
	// Initialization specific to BigAsteroid
	Asteroid::Initialize();

	size = 50; // Example size for a big asteroid
	// Set big asteroid sprite and other properties
}

void AsteroidBig::Update()
{
	// Update logic specific to BigAsteroid
	
	Transform& tran = owner->GetTransform();
	tran.position += velocity * Time::Instance().DeltaTime();

	if (tran.position.y > screenHeight) {
		tran.position.y = -size;
		tran.position.x = static_cast<float>(rand() % screenWidth - 1);
	}
}
