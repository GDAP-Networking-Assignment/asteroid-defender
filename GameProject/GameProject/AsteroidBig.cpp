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
	Asteroid::Update();
}
