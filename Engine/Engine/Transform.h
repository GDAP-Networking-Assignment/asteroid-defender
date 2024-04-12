#pragma once

#include "Component.h"
#include "EngineMath.h"

struct TransformData {
    Vec2 position;
    float rotation = 0;
    Vec2 scale;
    Vec2 velocity;
};

class Transform : public Component 
{
    DECLARE_DYNAMIC_DERIVED_CLASS(Transform, Component)

public:
    void Update() override;

public:
    Transform();

    void Serialize(RakNet::BitStream& bitStream) const override;
    void Deserialize(RakNet::BitStream& bitStream) override;

    void Load(json::JSON& node) override;

    void Translate(const Vec2& delta);
    void Rotate(float delta);
    void RotateToVelocity(float deltaOffset = 0);
    void Scale(const Vec2& delta);
    void DeserializePredict(RakNet::BitStream& bitStream);

public:
    Vec2 position; ///< The position of the entity in the game world.
    float rotation; ///< The rotation of the entity, in degrees or radians.
    Vec2 scale; ///< The scale of the entity.
    Vec2 velocity;

private:
    bool runInterpolate = false;
    TransformData lastTransform;
    TransformData interpolationTarget;
    float interpolationTimer = 0.0f;
    const float interpolationDuration = 0.2f;
};