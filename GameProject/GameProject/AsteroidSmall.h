#pragma once

#ifndef _ASTEROID_SMALL_H_
#define _ASTEROID_SMALL_H_

#include "GameCore.h"
#include "Asteroid.h"

class AsteroidSmall : public Asteroid {

   DECLARE_DYNAMIC_DERIVED_CLASS(AsteroidSmall, Asteroid)

public:
    void Initialize() override;
    void TakeDamage(int damage);
};

#endif