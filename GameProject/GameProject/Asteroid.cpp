#include "GameCore.h"
#include "Asteroid.h"

#define NDEBUG_PLAYER

 IMPLEMENT_ABSTRACT_CLASS(Asteroid)

Asteroid::Asteroid() : velocity(0.0f, 50.0f), size(1.0f), screenWidth(800), screenHeight(600) {
	 screenWidth = RenderSystem::Instance().GetWindowSize().x;
	 screenHeight = RenderSystem::Instance().GetWindowSize().y;

}

void Asteroid::Initialize() {
	Component::Initialize();

	//collider = (BoxCollider*)owner->CreateComponent("BoxCollider");

	

	size = 10; // Adjust the size of the asteroid as needed

}

void Asteroid::Update() {


	
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