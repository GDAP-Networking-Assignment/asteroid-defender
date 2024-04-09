#include "GameCore.h"
#include "Asteroid.h"

IMPLEMENT_DYNAMIC_CLASS(Asteroid);
Asteroid::Asteroid() : velocity(0.0f, 0.0f), size(1.0f), screenWidth(800), screenHeight(600) {
    // Constructor content
}

void Asteroid::Initialize() {
    Component::Initialize();
    collider = (BoxCollider*)owner->CreateComponent("BoxCollider");


    // Randomize properties
    velocity.x = static_cast<float>(rand() % 100 - 50); // Example velocity, adjust as needed
    velocity.y = static_cast<float>(rand() % 100 - 50);
    size = static_cast<float>((rand() % 5) + 1); // Random size for demonstration
    // Additional initialization logic as needed

    // If server, setup to send these properties
    //if (NetworkEngine::Instance().IsServer()) {
    //    RakNet::BitStream bs;
    //    SerializeProperties(bs);
    //    NetworkEngine::Instance().SendPacket(bs);
    //}
}

void Asteroid::Update() {
    Transform& transform = owner->GetTransform();
    transform.position += velocity * Time::Instance().DeltaTime();
    transform.position.x = static_cast<float>(rand() % screenWidth);
    transform.position.y = 0.0f;
    // Additional logic to handle screen wrapping or destruction
}

void Asteroid::SerializeProperties(RakNet::BitStream& bs) const {
    bs.Write((RakNet::MessageID)MSG_CREATE_ASTEROID);
    bs.Write(velocity.x);
    bs.Write(velocity.y);
    bs.Write(size);
}

void Asteroid::DeserializeProperties(RakNet::BitStream& bs) {
    bs.Read(velocity.x);
    bs.Read(velocity.y);
    bs.Read(size);
    // Apply these properties as needed
}