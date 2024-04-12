#include "GameCore.h"
#include "Asteroid.h"
#include "BoxCollider.h"

#define NDEBUG_PLAYER

IMPLEMENT_DYNAMIC_CLASS(Asteroid)

void Asteroid::Initialize() {
	Component::Initialize();
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
		 //LOG(owner->GetName() << ":" << other->GetOwner()->GetName());
		 if (other->GetOwner()->GetName() == "Player") {
			 // Mark both the asteroid and the player for removal
			 SceneManager::Instance().RemoveEntity(owner->GetUid());
			 SceneManager::Instance().RemoveEntity(other->GetOwner()->GetUid());
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
	 ownerTransform.velocity.y = speed;
 }
