#pragma once

namespace Framework::Enums
{
	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		Custom,

		Camera,
		Size,
	};

	enum class eLayerType
	{
		None,
		BackGround,

		Size = 16,
	};

	enum class eResourceType
	{
		Texture,
		AudioClip,
		Prefab,

		Size,
	};
}