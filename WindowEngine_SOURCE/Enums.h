#pragma once

namespace Framework::Enums
{
	enum class eComponentType
	{
		Transform,
		Collider,
		Rigidbody,

		Custom,

		SpriteRenderer,
		Animator,
		Camera,

		Size,
	};

	enum class eLayerType
	{
		None,
		BackGround,
		Character,

		Particle,

		Size = 16,
	};

	enum class eResourceType
	{
		Texture,
		AudioClip,
		Prefab,
		Animation,

		Size,
	};
}