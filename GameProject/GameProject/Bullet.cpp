#include "GameCore.h"
#include "Bullet.h"

#define NDEBUG_BULLET

IMPLEMENT_DYNAMIC_CLASS(Bullet)

#include "AnimatedSprite.h"

void Bullet::Initialize()
{
    Component::Initialize();
    start_pos = owner->GetTransform().position;
    collider = (BoxCollider*)owner->CreateComponent("BoxCollider");
    owner->SetName("Bullet");

    sprite = (Sprite*)owner->CreateComponent("Sprite");
    sprite->SetTextureAsset(
        (TextureAsset*)AssetManager::Instance().GetAsset("Laser_2ffefe30-b2b5-4cfa-98d1-2cf6a6f7930e")
    );
    owner->GetTransform().Rotate(RAD_TO_DEG(atan(direction.y / direction.x)) + 90);
}
void Bullet::Update() {
    // Move the player
    owner->GetTransform().position += direction * (speed * Time::Instance().DeltaTime());

    if (collider == nullptr)
    {
        return;
    }
    for (const auto& other : collider->OnCollisionEnter())
    {
        if (other->GetOwner()->GetName() != "Enemy")
        {
            continue;
        }
        owner->GetParentScene()->RemoveEntity(uid);
    }
}
void Bullet::Load(json::JSON& node)
{
    Component::Load(node);
    if (node.hasKey("Speed"))
    {
        speed = static_cast<float>(node.at("Speed").ToFloat());
    }
}

void Bullet::SetTarget(Vec2 dir) {
    direction = dir - owner->GetTransform().position;
    if (direction != Vec2::Zero) {
        direction.Normalize();
    }
}