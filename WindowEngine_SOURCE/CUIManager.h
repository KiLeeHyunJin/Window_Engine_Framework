#pragma once
#include "CommonInclude.h"
namespace Framework
{
	class CRenderManager;
	class CScene;
	class CUIBase;
	class CUIManager
	{
	public:
		static void Push(Enums::eUIType type);
		static void Pop(Enums::eUIType type);

		static void OnLoad();
		
		static void OnComplete();
		static void OnFail();


	private:
		CUIManager();
		~CUIManager();

		static void Initialize();
		static void Tick();
		static void LastTick();
		static void Render(HDC hdc);

		static std::stack<CUIBase*> m_stackBase;
		static std::queue<Enums::eUIType> m_queUIType;
		static std::unordered_map<Enums::eUIType, CUIBase*> m_unmapUI;
		static CUIBase* m_pCurrentUI;

	};
}

