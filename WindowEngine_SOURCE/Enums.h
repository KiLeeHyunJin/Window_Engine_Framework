#pragma once

namespace Framework::Enums
{
	enum class eComponentType
	{
		Transform,
		
		Custom,

		SpriteRenderer,
		Animator,
		Camera,
		Collider,
		Rigidbody,

		Size,
	};

	enum class eLayerType
	{
		None,
		BackGround,
		Ground,
		Character,

		Particle,
		UI,
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

	enum class eUIType
	{
		Button,


		Size,
	};
}