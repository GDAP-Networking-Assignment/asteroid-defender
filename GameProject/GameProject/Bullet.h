#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#include "GameCore.h"

class Sprite;

class Bullet : public Component
{
    DECLARE_DYNAMIC_DERIVED_CLASS(Bullet, Component)

public:
    void Initialize() override;
    void Update() override;
    void Load(json::JSON&) override;
    void SetTarget(Vec2 target);

private:
    BoxCollider* collider = nullptr;
    Sprite* sprite = nullptr;

    STRCODE game_over_scene = -1;

public:
    float speed = 300.0f;
};

#endif // _Bullet_H_