#include "CRenderer.h"

namespace Framework//::Renderer
{
	namespace Renderer
	{
		//extern CCameraComponent* mainCamera = nullptr;
		CCameraComponent* CRenderer::m_mainCam = nullptr;
		Maths::Vector2 CRenderer::m_vecResolution = {};
	}
	
}