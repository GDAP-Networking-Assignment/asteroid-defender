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
	RegisterRPC(GetHashCode("RPC"), std::bind(&Player::RPCMove, this, std::placeholders::_1));
	RegisterRPC(GetHashCode("RPCSpawnBullet"), std::bind(&Player::RPCSpawnBullet, this, std::placeholders::_1));
}

void Player::Update() 
{
	if (NetworkEngine::Instance().IsClient()) {
		HandleInput();
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

void Player::HandleInput()
{
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

void Player::RPCMove(RakNet::BitStream& bitStream)
{
	float value = 0.0f;
	bitStream.Read(value);
	movement.x += value;
	bitStream.Read(value);
	movement.y += value;
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

	bitStream.Write(bullet->GetOwner()->GetTransform().position.x);
	bitStream.Write(bullet->GetOwner()->GetTransform().position.y);

	bitStream.Write(bullet->direction.x);
	bitStream.Write(bullet->direction.y);

	NetworkEngine::Instance().SendPacket(bitStream);
}

void Player::RPCSpawnBullet(RakNet::BitStream& bitStream)
{
	Entity* entityBullet = SceneManager::Instance().CreateEntity();
	Bullet* bullet = (Bullet*)entityBullet->CreateComponent("Bullet");

	// Position
	Vec2 pos;
	bitStream.Read(pos.x);
	bitStream.Read(pos.y);
	entityBullet->GetTransform().position.x = pos.x;
	entityBullet->GetTransform().position.y = pos.y;

	// Direction
	bitStream.Read(bullet->direction.x);
	bitStream.Read(bullet->direction.y);
}
