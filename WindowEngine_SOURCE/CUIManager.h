#pragma once
#include "CommonInclude.h"

namespace Framework
{
	//class CScene;
	class CUIBase;
	class CApplication;

	namespace Manager
	{
		//class CRenderManager;

		class CUIManager 
		{
			DECLARE_SINGLE(CUIManager)
			RELEASE_SINGLE(CUIManager)

		public:
			void LoadUI(Enums::eUIType type, CUIBase* pUI, bool bChangeHierarchy = false, bool bDrag = false);
			void Push(Enums::eUIType type);
			void Render(HDC hdc);

			void Pop(Enums::eUIType type);
			void Pop(CUIBase* closeUI);

			void PopPopup();

			void OnLoad(Enums::eUIType type);

			void OnComplete(CUIBase* uiBase);
			void OnFail();

			void Clear();

			void SetLastSibling(CUIBase* pFrontUI);
			//CUIBase* GetCollisionUI();

			friend CApplication;
		private:
			//CUIManager();
			~CUIManager();

			void Initialize();
			void Release();

			void Tick();
			void LastTick();


			void	CloseUI(INT closeUIIdx);

			void MouseEvent(CUIBase* pUI, CUIBase* pChild);
			CUIBase* GetTopUI();
			CUIBase* GetParentUI(CUIBase* pChild);
			CUIBase* GetFocusUI();
			INT FindUIIdex(const CUIBase* pTarget);

			std::queue<Enums::eUIType> m_queUIType					= {};
			/// <summary>
			/// vector를 사용하는 이유는 캐시 적중률, 참조 연산등을 고려해 선택
			/// </summary>
			std::vector<CUIBase*> m_vecCurrentUIs					= {};
			std::unordered_map<Enums::eUIType, CUIBase*> m_unmapUI	= {};
			CUIBase* m_pCurrentUI									= {};
		};
	}


	using UI = Manager::CUIManager;
//	#define UI CUIManager
}

