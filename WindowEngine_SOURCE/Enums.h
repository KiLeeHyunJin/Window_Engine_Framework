#pragma once

namespace Framework//::Enums
{
	namespace Enums
	{

#pragma region  Component

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
#pragma endregion


#pragma region Layer
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
#pragma endregion


#pragma region  Resource

		enum class eResourceType
		{
			Texture,
			AudioClip,
			Prefab,
			Animation,

			Size,
		};
#pragma endregion


#pragma region  UI
		enum class eUILayer
		{
			None,
			HUD,
			Popup,
		};


		enum class eUIType
		{
			None,
			Button,
			Popup,

			Size,
		};
#pragma endregion

	}


}