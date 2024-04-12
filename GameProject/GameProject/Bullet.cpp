#include "GameCore.h"
#include "Bullet.h"
#include "BoxCollider.h"

#define NDEBUG_BULLET

IMPLEMENT_DYNAMIC_CLASS(Bullet)

void Bullet::Initialize()
{
    Component::Initialize();
    owner->SetName("Bullet");
    sprite = (Sprite*)owner->CreateComponent("Sprite");
    sprite->SetTextureAsset(
        (TextureAsset*)AssetManager::Instance().GetAsset("Laser_2ffefe30-b2b5-4cfa-98d1-2cf6a6f7930e")
    );
    collider = (BoxCollider*)owner->CreateComponent("BoxCollider");
    owner->GetTransform().RotateToVelocity(90.0f);
}
void Bullet::Update() {
    Component::Update();

    // SERVER Collision Detection and removal
    if (NetworkEngine::Instance().IsClient()) return;
    // Offscreen removal
    Vec2& ownerPosition = owner->GetTransform().position;
    IVec2 windowSize = RenderSystem::Instance().GetWindowSize();
    if (ownerPosition.y < 0 || ownerPosition.y > windowSize.y ||
        ownerPosition.x < 0 || ownerPosition.x > windowSize.x) {
        SceneManager::Instance().RemoveEntity(owner->GetUid());
    }
    // Collision
    for (const auto& other : collider->OnCollisionEnter())
    {
        if (other->GetOwner()->GetName() == "Asteroid") {
            LOG(owner->GetName() << ":" << other->GetOwner()->GetName());
            SceneManager::Instance().RemoveEntity(other->GetOwner()->GetUid()); // Remove asteroid
            SceneManager::Instance().RemoveEntity(owner->GetUid()); // Remove bullet
            break; // Since bullet is destroyed, no need to check for more collisions
        }
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
