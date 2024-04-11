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
	

	size = 50; // Example size for a big asteroid
	// Set big asteroid sprite and other properties
}

void AsteroidBig::Update()
{
	// Update logic specific to BigAsteroid
	
	Transform& transform = owner->GetTransform();
	transform.position += velocity * Time::Instance().DeltaTime();

	if (transform.position.y > screenHeight) {
		transform.position.y = -size;
		transform.position.x = static_cast<float>(rand() % screenWidth);
	}
}
