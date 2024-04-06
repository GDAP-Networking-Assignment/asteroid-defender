#include "EngineCore.h"
#include "Transform.h"
#include "Scene.h"

IMPLEMENT_DYNAMIC_CLASS(Transform);

void Transform::Update()
{
	if (owner != nullptr && owner->GetParentScene() != nullptr) {
		PredictTransform(owner->GetParentScene()->timerTransformSync);
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

void Transform::Scale(const Vec2& delta)
{
	scale *= delta;
}

void Transform::PredictTransform(float _time)
{
	Vec2 nextPos;
	int nextRotation = 0;
	Vec2 nextScale;

	position = Vec2::Lerp(position, nextPos, _time);
	scale = nextScale;
}

void Transform::Serialize(RakNet::BitStream& bitStream) const
{
	if (owner == nullptr || owner->GetParentScene() == nullptr) return;

	if (owner->GetParentScene()->shouldTransformSync) {
		bitStream.Write(position.x);
		bitStream.Write(position.y);
		bitStream.Write(rotation);
		bitStream.Write(scale.x);
		bitStream.Write(scale.y);
		owner->GetParentScene()->shouldTransformSync = false;
	}
}

void Transform::Deserialize(RakNet::BitStream& bitStream)
{
	bitStream.Read(nextPos.x);
	bitStream.Read(nextPos.y);
	bitStream.Read(nextRotation);
	bitStream.Read(nextScale.x);
	bitStream.Read(nextScale.y);
}
