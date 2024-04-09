#pragma once
#include "GameCore.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "NetworkEngine.h"

class Asteroid : public Component {
public:
    DECLARE_DYNAMIC_DERIVED_CLASS(Asteroid, Component)
    Asteroid();
    virtual void Initialize() override;
    virtual void Update() override;

    // Networking
    void SerializeProperties(RakNet::BitStream& bs) const;
    void DeserializeProperties(RakNet::BitStream& bs);
    int screenWidth;
    int screenHeight;

private:
    Vec2 velocity;
    float size; // Example property, adjust as needed
    BoxCollider* collider = nullptr;
    Sprite* sprite = nullptr;
};
