#pragma once
#ifndef ASTEROID_FACTORY_H
#define ASTEROID_FACTORY_H

#include "GameCore.h"

class AsteroidFactory : public Object {
    DECLARE_DYNAMIC_DERIVED_CLASS(AsteroidFactory, Object)

public:
    enum class AsteroidType {
        Big,
        Small
    };

    static Asteroid* CreateAsteroid(AsteroidType type)
    {
        Entity* entity = SceneManager::Instance().CreateEntity();
        Asteroid* asteroid = nullptr;

        switch (type) {
        case AsteroidType::Big:
            asteroid = (AsteroidBig*)entity->CreateComponent("AsteroidBig");
            break;
        case AsteroidType::Small:
            asteroid = (AsteroidSmall*)entity->CreateComponent("AsteroidSmall");
            break;
        default:
            throw std::invalid_argument("Invalid Asteroid Type");
        }

        if (asteroid != nullptr) {
            asteroid->RandomizeSpawn();
        }

        return asteroid;
    }

};

#endif