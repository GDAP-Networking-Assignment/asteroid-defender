#include "GameCore.h"
#include "Asteroid.h"
#define NDEBUG_PLAYER

 IMPLEMENT_ABSTRACT_CLASS(Asteroid)

Asteroid::Asteroid() : velocity(0.0f, 250.0f), size(1.0f), screenWidth(800), screenHeight(600) {
	// Constructor content
}

void Asteroid::Initialize() {
	Component::Initialize();

	//collider = (BoxCollider*)owner->CreateComponent("BoxCollider");

	AsteroidFactory* factory = (AsteroidFactory*)owner->CreateComponent("AsteroidFactory");
	AsteroidFactory::AsteroidType type = (rand() % 2 == 0) ? AsteroidFactory::AsteroidType::Big : AsteroidFactory::AsteroidType::Small;
	Asteroid* asteroid = factory->CreateAsteroid(owner, type);
	if (type == AsteroidFactory::AsteroidType::Big) {
		owner->SetName("Asteroid");
		sprite = (Sprite*)owner->CreateComponent("Sprite");
		sprite->SetTextureAsset(

			(TextureAsset*)AssetManager::Instance().GetAsset("MeteorSmall_48526c0d-ca5d-4681-8fe5-93726d5906fa")
		);
	}else {
		sprite = (Sprite*)owner->CreateComponent("Sprite");
		sprite->SetTextureAsset(

			(TextureAsset*)AssetManager::Instance().GetAsset("MeteorBig_a7319cea-2d19-4515-b910-7d10f6df0ec3")

		);
	}
	Transform& transform = owner->GetTransform();
	transform.position.x = rand() % screenWidth;
	transform.position.y = -size;

	size = 10; // Adjust the size of the asteroid as needed

}

void Asteroid::Update() {

	
		
		


	
	Transform& transform = owner->GetTransform();
	transform.position += velocity * Time::Instance().DeltaTime();

	if (transform.position.y > screenHeight) {
		transform.position.y = -size;
		transform.position.x = static_cast<float>(rand() % screenWidth);
	}
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