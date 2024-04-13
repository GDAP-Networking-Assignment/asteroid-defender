#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "GameCore.h"

class BoxCollider;
class Bullet;

class Player : public Component
{
    DECLARE_DYNAMIC_DERIVED_CLASS(Player, Component)

public:
    void Initialize() override;
    void Update() override;
    void Load(json::JSON&) override;

    void SerializeCreate(RakNet::BitStream& bitStream) const override;
    void DeserializeCreate(RakNet::BitStream& bitStream) override;

private:
    float speed = 5.0f;
    Sprite* sprite = nullptr;
    BoxCollider* collider = nullptr;
    STRCODE game_over_scene = -1;
    Entity* networkedEntity = nullptr;
    float fireCooldown = 0.5;
    float fireCounter = 0;
    bool fired = false;

private:
    void HandleFire();

    void SendRPCSpawnBullet(Bullet* bullet);
    void RPCSpawnBullet(RakNet::BitStream& bitStream);

public:
    uint64_t networkGuid;
};

#endif // PLAYER_H


