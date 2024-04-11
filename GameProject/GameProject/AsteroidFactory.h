#pragma once
#include "Asteroid.h"
#include "AsteroidBig.h"
#include "AsteroidSmall.h"

class AsteroidFactory : public Component {
public:
    AsteroidSmall* snails = new AsteroidSmall();
    AsteroidBig* big = new AsteroidBig();
    DECLARE_DYNAMIC_DERIVED_CLASS(AsteroidFactory, Component)

    AsteroidFactory();

    enum class AsteroidType {
        Big,
        Small
    };

    Asteroid* CreateAsteroid(Entity* parent, AsteroidType type) {
       

        switch (type) {
        case AsteroidType::Big:
           parent->GetComponent("AsteroidBig");
           
           big->Initialize();

            return big;
        case AsteroidType::Small:
            parent->GetComponent("AsteroidSmall");
			
            snails->Initialize();
			return snails;
        default:
            throw std::invalid_argument("Invalid Asteroid Type");
        }
    }
};
