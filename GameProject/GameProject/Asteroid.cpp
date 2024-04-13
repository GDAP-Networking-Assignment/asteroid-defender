#include "GameCore.h"
#include "Asteroid.h"
#include "BoxCollider.h"

#define NDEBUG_PLAYER

IMPLEMENT_DYNAMIC_CLASS(Asteroid)

void Asteroid::Initialize() {
	Component::Initialize();
	this->owner->SetName("Asteroid");
	owner->SetName("Asteroid");
	sprite = (Sprite*)owner->CreateComponent("Sprite");
	collider = (BoxCollider*)owner->CreateComponent("BoxCollider");
}

 void Asteroid::Update()
 {
	 Component::Update();
	 Vec2& ownerPosition = owner->GetTransform().position;

	 // SERVER Collision Detection and removal
	 if (NetworkEngine::Instance().IsClient()) return;
	 for (const auto& other : collider->OnCollisionEnter()) {
		 if (other->GetOwner()->HasComponent("Player")) {
			 RakNet::BitStream bitStream;
			 bitStream.Write((unsigned char)NetworkPacketIds::MSG_SCENE_MANAGER);
			 bitStream.Write((unsigned char)NetworkPacketIds::MSG_GAME_OVER);
			 NetworkEngine::Instance().SendPacket(bitStream);
			 break;
		 }
	 }
	 int screenHeight = RenderSystem::Instance().GetWindowSize().y;
	 if (ownerPosition.y > screenHeight) {
		 SceneManager::Instance().RemoveEntity(owner->GetUid());
	 }
 }

 void Asteroid::RandomizeSpawn()
 {
	 int screenWidth = RenderSystem::Instance().GetWindowSize().x;
	 Transform& ownerTransform = owner->GetTransform();
	 ownerTransform.position.x = static_cast<float>(rand() % screenWidth);
	 ownerTransform.position.y = 0;

	 float randomAngle = static_cast<float>(std::rand())*M_PI / RAND_MAX;
	 Vec2 downVector = Vec2(cos(randomAngle), sin(randomAngle));
	 downVector.Normalize();
	 ownerTransform.velocity = downVector*speed;
 }

 void Asteroid::TakeDamage(int damage)
 {
	health -= damage;
    if (health <= 0) {
        SceneManager::Instance().RemoveEntity(owner->GetUid()); // Destroy asteroid
    }
 }
