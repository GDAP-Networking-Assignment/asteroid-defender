#include "GameCore.h"
#include "Bullet.h"
#include "NetworkEngine.h"

#define NDEBUG_BULLET

IMPLEMENT_DYNAMIC_CLASS(Bullet)

#include "AnimatedSprite.h"

void Bullet::Initialize()
{
    Component::Initialize();
    collider = (BoxCollider*)owner->CreateComponent("BoxCollider");
    owner->SetName("Bullet");

    sprite = (Sprite*)owner->CreateComponent("Sprite");
    sprite->SetTextureAsset(
        (TextureAsset*)AssetManager::Instance().GetAsset("Laser_2ffefe30-b2b5-4cfa-98d1-2cf6a6f7930e")
    );

    Transform& entityTransform = owner->GetTransform();
    entityTransform.RotateToVelocity(90.0f);
}
void Bullet::Update() {
    Component::Update();
    // Client side movement for sync testing
    if (NetworkEngine::Instance().IsClient() && InputSystem::Instance().IsKeyPressed(SDLK_SPACE)) {
        owner->GetTransform().position.y += 400*Time::Instance().DeltaTime();
    }

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

void Bullet::SetTarget(Vec2 target) {
    Vec2 direction = target - owner->GetTransform().position;
    if (direction != Vec2::Zero) {
        direction.Normalize();
    }
    owner->GetTransform().velocity = direction * speed;
}
