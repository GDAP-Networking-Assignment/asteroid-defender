#pragma once
#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include "GameCore.h"
#include "IDamagable.h"

class BoxCollider;

class Asteroid : public Component {
  DECLARE_DYNAMIC_DERIVED_CLASS(Asteroid, Component);

public:
    virtual void Initialize() override;
    virtual void Update() override;

    void RandomizeSpawn();
    void TakeDamage(int damage);

protected:
    float speed = 100.0f;
    BoxCollider* collider = nullptr;
    Sprite* sprite = nullptr;
    int health = 100;

};
#endif