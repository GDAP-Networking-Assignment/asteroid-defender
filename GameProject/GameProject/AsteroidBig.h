#pragma once
#include "GameCore.h"
#include "Asteroid.h"

class AsteroidBig : public Asteroid
{
	DECLARE_DYNAMIC_DERIVED_CLASS(AsteroidBig, Asteroid)
	public:
		AsteroidBig();
		virtual ~AsteroidBig() override;

		virtual void Initialize() override;
		virtual void Update() override;
		

};

