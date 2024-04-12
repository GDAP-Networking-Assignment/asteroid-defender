#include "EngineCore.h"
#include "Transform.h"
#include "Scene.h"
#include "NetworkEngine.h"

IMPLEMENT_DYNAMIC_CLASS(Transform);

void Transform::Update()
{ 
	position += velocity * Time::Instance().DeltaTime();

	if (runInterpolate && owner != nullptr && owner->GetName() != "Player") {
		interpolationTimer += Time::Instance().DeltaTime();

		float lerpValue = interpolationTimer / interpolationDuration;

		position = Vec2::Lerp(lastTransform.position, interpolationTarget.position, lerpValue);
		scale = Vec2::Lerp(scale, interpolationTarget.scale, lerpValue);
		velocity = Vec2::Lerp(velocity, interpolationTarget.velocity, lerpValue);

		if (interpolationTimer > interpolationDuration) {
			interpolationTimer = 0;
			runInterpolate = false;
		}
	}

}

Transform::Transform() :
	position(Vec2::Zero), rotation(0), scale(Vec2(1))
{
}

void Transform::Load(json::JSON& node)
{
	Component::Load(node);

	if (node.hasKey("Position"))
	{
		position = vec2_from_json(node["Position"]);
	}
	if (node.hasKey("Rotation"))
	{
		rotation = static_cast<float>(node["Rotation"].ToFloat());
	}
	if (node.hasKey("Scale"))
	{
		scale = vec2_from_json(node["Scale"]);
	}
}

void Transform::Translate(const Vec2& delta)
{
	position += delta;
}

void Transform::Rotate(float delta)
{
	rotation += delta;
}

void Transform::RotateToVelocity(float deltaOffset)
{
	rotation = RAD_TO_DEG(velocity.Angle()) + deltaOffset;
}

void Transform::Scale(const Vec2& delta)
{
	scale *= delta;
}

void Transform::DeserializePredict(RakNet::BitStream& bitStream)
{
	bitStream.Read(interpolationTarget.position.x);
	bitStream.Read(interpolationTarget.position.y);
	bitStream.Read(interpolationTarget.rotation);
	bitStream.Read(interpolationTarget.scale.x);
	bitStream.Read(interpolationTarget.scale.y);
	bitStream.Read(interpolationTarget.velocity.x);
	bitStream.Read(interpolationTarget.velocity.y);

	// Predict position based on time since server sent packet
	float delta = Time::Instance().currentServerTick - Time::Instance().lastServerTick;
	interpolationTarget.position += interpolationTarget.velocity * delta;
	runInterpolate = true;

	lastTransform.position = position;
	lastTransform.rotation = rotation;
	lastTransform.velocity = velocity;
}

void Transform::Serialize(RakNet::BitStream& bitStream) const
{
	/*if (owner == nullptr || owner->GetParentScene() == nullptr) return;
	if (owner->GetParentScene()->shouldTransformSync) {
		owner->GetParentScene()->shouldTransformSync = false;
	}*/

	bitStream.Write(position.x);
	bitStream.Write(position.y);
	bitStream.Write(rotation);
	bitStream.Write(scale.x);
	bitStream.Write(scale.y);
	bitStream.Write(velocity.x);
	bitStream.Write(velocity.y);
}

void Transform::Deserialize(RakNet::BitStream& bitStream)
{
	bitStream.Read(position.x);
	bitStream.Read(position.y);
	bitStream.Read(rotation);
	bitStream.Read(scale.x);
	bitStream.Read(scale.y);
	bitStream.Read(velocity.x);
	bitStream.Read(velocity.y);
}
