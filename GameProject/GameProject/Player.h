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
private:
    float speed = 5.0f;
    BoxCollider* collider = nullptr;
    STRCODE game_over_scene = -1;
    Entity* networkedEntity = nullptr;

    float fireCooldown = 0.5;
    float fireCounter = 0;
    bool fired = false;

private:
    void HandleInput();
    void HandleFire();

    void RPCMove(RakNet::BitStream& bitStream);

    void SendRPCSpawnBullet(Bullet* bullet);
    void RPCSpawnBullet(RakNet::BitStream& bitStream);

private:
    Vec2 movement;
};

#endif // PLAYER_H


