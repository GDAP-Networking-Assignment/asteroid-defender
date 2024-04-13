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
	sprite = (Sprite*)owner->CreateComponent("Sprite");
	sprite->SetTextureAsset(
		(TextureAsset*)AssetManager::Instance().GetAsset("Ship_c50b2792-24af-4981-bcfa-a0014762b813")
	);
	collider = (BoxCollider*)owner->CreateComponent("BoxCollider");
	RegisterRPC(GetHashCode("RPCSpawnBullet"), std::bind(&Player::RPCSpawnBullet, this, std::placeholders::_1));
}

void Player::Update() 
{
	if (NetworkEngine::Instance().IsClient() && NetworkEngine::Instance().isGameStart) {
		if (NetworkEngine::Instance().rakInterface->GetMyGUID().g == networkGuid) {
			HandleFire();
		}
	}
}

void Player::Load(json::JSON& node)
{
	Component::Load(node);
}

void Player::SerializeCreate(RakNet::BitStream& bitStream) const
{
	Component::SerializeCreate(bitStream);
	bitStream.Write(networkGuid);
}

void Player::DeserializeCreate(RakNet::BitStream& bitStream)
{
	Component::DeserializeCreate(bitStream);
	bitStream.Read(networkGuid);
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

		Entity* entityBullet = owner->GetParentScene()->CreateEntity();
		Bullet* bullet = (Bullet*)entityBullet->CreateComponent("Bullet");
		entityBullet->GetTransform().position = owner->GetTransform().position;
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

	// Serialize bullet
	bitStream.Write(bullet->GetOwner()->GetUid());
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
	//entityBullet->SetName("Bullet");

	bitStream.Read(entityBullet->networkUid);
	Transform& entityTransform = entityBullet->GetTransform();
	bitStream.Read(entityTransform.position.x);
	bitStream.Read(entityTransform.position.y);
	bitStream.Read(entityTransform.velocity.x);
	bitStream.Read(entityTransform.velocity.y);
}