#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "GameCore.h"
#include "TextureAsset.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "Sprite.h"

class Bullet : public Component
{
    DECLARE_DYNAMIC_DERIVED_CLASS(Bullet, Component)

public:
    void Initialize() override;
    void Update() override;
    void Load(json::JSON&) override;
    void SetTarget(Vec2 target);

    void SerializeCreate(RakNet::BitStream& bitStream) const override;
    void DeserializeCreate(RakNet::BitStream& bitStream) override;

private:
    BoxCollider* collider = nullptr;
    Sprite* sprite = nullptr;

    STRCODE game_over_scene = -1;

public:
    float speed = 100.0f;
    Vec2 direction;
};

#endif // Bullet_H