#include "GameCore.h"

void GameRegisterClasses()
{
	REGISTER_TYPECLASS(Player);
	REGISTER_TYPECLASS(GameOver);
	REGISTER_TYPECLASS(Bullet);
	REGISTER_TYPECLASS(AsteroidSpawner);
	REGISTER_TYPECLASS(AsteroidBig);
	REGISTER_TYPECLASS(AsteroidSmall);
	REGISTER_TYPECLASS(AsteroidFactory);
	REGISTER_TYPECLASS(Asteroid);
}