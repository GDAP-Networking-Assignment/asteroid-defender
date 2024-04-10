#include "GameCore.h"
#include "Asteroid.h"

IMPLEMENT_DYNAMIC_CLASS(Asteroid);
Asteroid::Asteroid() : velocity(0.0f, 1.0f), size(1.0f), screenWidth(800), screenHeight(600) {
    // Constructor content
}

void Asteroid::Initialize() {
    Component::Initialize();
    collider = (BoxCollider*)owner->CreateComponent("BoxCollider");
    owner->SetName("Asteroid");
    sprite = (Sprite*)owner->CreateComponent("Sprite");
    sprite->SetTextureAsset(

        (TextureAsset*)AssetManager::Instance().GetAsset("MeteorBig_a7319cea-2d19-4515-b910-7d10f6df0ec3")

    );
    Transform& transform = owner->GetTransform();
    transform.position.x = rand() % screenWidth;
    transform.position.y = -size;
    // Set the velocity to move downwards
    velocity.x = 0; // No horizontal movement
    velocity.y = 1; // Adjust the speed of downward movement as needed
    size = 1; // Adjust the size of the asteroid as needed

    // If server, setup to send these properties
    //if (NetworkEngine::Instance().IsServer()) {
    //    RakNet::BitStream bs;
    //    SerializeProperties(bs);
    //    NetworkEngine::Instance().SendPacket(bs);
    //}
}

void Asteroid::Update() {
    Transform& transform = owner->GetTransform();

    // Move the asteroid downwards by updating its y position based on velocity
    transform.position += velocity;

    // Additional logic for handling screen wrapping or destruction
    // For example, reset the position to the top of the screen when it goes off the bottom
    if (transform.position.y > screenHeight) {
        transform.position.y = -size; // Reset to just above the screen
        transform.position.x = static_cast<float>(rand() % screenWidth); // Optional: Randomize x again if desired
    }
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