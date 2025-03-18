#pragma once
#include "CCameraComponent.h"

namespace Framework//::Renderer
{
	namespace Renderer
	{
		//extern CCameraComponent* mainCamera;
	//extern Vector2 resolution;

		class CRenderer
		{
		public:
			static void SetMainCamera(CCameraComponent* cam)
			{
				m_mainCam = cam;
				m_mainCam->SetResolution(m_vecResolution);
			}
			static CCameraComponent* GetMainCamera() { return m_mainCam; }
			static void SetResolution(Vector2 resolution) { m_vecResolution = resolution; }

		private:
			static CCameraComponent* m_mainCam;
			static Maths::Vector2 m_vecResolution;
		};
	}
	
}
