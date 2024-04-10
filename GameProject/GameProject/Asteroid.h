#pragma once
#include "GameCore.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "NetworkEngine.h"


class Asteroid : public Component {

    DECLARE_ABSTRACT_DERIVED_CLASS(Asteroid, Component);

public:



    Asteroid(); // Constructor declaration

    virtual void Initialize() override = 0;
    virtual void Update() override = 0;

    void SerializeProperties(RakNet::BitStream& bs) const;

    void DeserializeProperties(RakNet::BitStream& bs);

protected:
    Vec2 velocity;
    float size;
    int screenWidth, screenHeight;
    BoxCollider* collider = nullptr;
    Sprite* sprite = nullptr;
    
};
