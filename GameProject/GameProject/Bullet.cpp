#include "GameCore.h"
#include "Bullet.h"

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
    owner->GetTransform().Rotate(RAD_TO_DEG(direction.Angle())+90);
}
void Bullet::Update() {
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

void Bullet::SetTarget(Vec2 target) {
    direction = target - owner->GetTransform().position;
    if (direction != Vec2::Zero) {
        direction.Normalize();
    }
}

void Bullet::SerializeCreate(RakNet::BitStream& bitStream) const
{
    Component::SerializeCreate(bitStream);

    bitStream.Write(direction.x);
    bitStream.Write(direction.y);
}

void Bullet::DeserializeCreate(RakNet::BitStream& bitStream)
{
    Component::DeserializeCreate(bitStream);

    bitStream.Read(direction.x);
    bitStream.Read(direction.y);
}
