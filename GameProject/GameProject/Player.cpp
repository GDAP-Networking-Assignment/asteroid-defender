#include "GameCore.h"
#include "Player.h"
#include "Sprite.h"
#include "TextureAsset.h"
#include "BoxCollider.h"
#include "NetworkEngine.h"
#include "Bullet.h"

#define NDEBUG_PLAYER

IMPLEMENT_DYNAMIC_CLASS(Player)

void Player::Initialize()
{
	Component::Initialize();
	collider = (BoxCollider*)owner->GetComponent("BoxCollider");
	RegisterRPC(GetHashCode("RPCSpawnBullet"), std::bind(&Player::RPCSpawnBullet, this, std::placeholders::_1));
}

void Player::Update() 
{
	if (NetworkEngine::Instance().IsClient()) {
		HandleFire();
		return;
	}

	if (collider == nullptr)
	{
		LOG("No collider");
		return;
	}
	for (const auto& other : collider->OnCollisionEnter())
	{
		if (other->GetOwner()->GetName() != "Enemy")
		{
			continue;
		}

		// Take Damage
	}
}

void Player::Load(json::JSON& node)
{
	Component::Load(node);
	if (node.hasKey("Speed"))
	{
		speed = static_cast<float>(node.at("Speed").ToFloat());
	}

	if (node.hasKey("DeathScene"))
	{
		game_over_scene = GetHashCode(node.at("DeathScene").ToString().c_str());
	}
}

void Player::HandleFire() {
	if (fired) {
		fireCounter += Time::Instance().DeltaTime();
	}

	if (fireCounter > fireCooldown) {
		fired = false;
		fireCounter = 0;
	}

	const InputSystem& input = InputSystem::Instance();
	if (input.IsMouseButtonPressed(SDL_BUTTON_LEFT) && !fired) {
		fired = true;
		fireCounter = 0;

		int mouseX, mouseY;
		const Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
		Vec2 mousePos = { (float)mouseX, (float)mouseY };

		Entity* newBullet = owner->GetParentScene()->CreateEntity();
		Bullet* bullet = (Bullet*)newBullet->CreateComponent("Bullet");
		newBullet->GetTransform().position = owner->GetTransform().position;
		bullet->SetTarget(mousePos);

		SendRPCSpawnBullet(bullet);
	}
}

void Player::SendRPCSpawnBullet(Bullet* bullet)
{
	RakNet::BitStream bitStream;
	bitStream.Write((unsigned char)MSG_SCENE_MANAGER);
	bitStream.Write((unsigned char)MSG_RPC);
	bitStream.Write(owner->GetParentScene()->GetUid());
	bitStream.Write(owner->GetUid());
	bitStream.Write(GetUid());
	bitStream.Write(GetHashCode("RPCSpawnBullet"));

	// Serialize bullet position and velocity
	Transform& bulletTransform = bullet->GetOwner()->GetTransform();
	bitStream.Write(bulletTransform.position.x);
	bitStream.Write(bulletTransform.position.y);
	bitStream.Write(bulletTransform.velocity.x);
	bitStream.Write(bulletTransform.velocity.y);

	NetworkEngine::Instance().SendPacket(bitStream);
}

void Player::RPCSpawnBullet(RakNet::BitStream& bitStream)
{
	Entity* entityBullet = SceneManager::Instance().CreateEntity();
	Bullet* bullet = (Bullet*)entityBullet->CreateComponent("Bullet");

	Transform& entityTransform = entityBullet->GetTransform();
	bitStream.Read(entityTransform.position.x);
	bitStream.Read(entityTransform.position.y);
	bitStream.Read(entityTransform.velocity.x);
	bitStream.Read(entityTransform.velocity.y);
}
