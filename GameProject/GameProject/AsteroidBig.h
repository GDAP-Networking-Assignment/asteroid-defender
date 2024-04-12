#pragma once
#ifndef _ASTEROID_BIG_H_
#define _ASTEROID_BIG_H_

#include "GameCore.h"
#include "Asteroid.h"

class AsteroidBig : public Asteroid
{
	DECLARE_DYNAMIC_DERIVED_CLASS(AsteroidBig, Asteroid)

	public:
		void Initialize() override;
		void TakeDamage(int damage);
};

#endif

