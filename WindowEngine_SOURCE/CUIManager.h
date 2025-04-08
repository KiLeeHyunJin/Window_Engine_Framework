#pragma once
#include "CommonInclude.h"

namespace Framework
{
	//class CScene;
	class CUIBase;
	class CApplication;

	namespace Manager
	{
		class CRenderManager;

		class CUIManager
		{
		public:
			static void LoadUI(Enums::eUIType type, CUIBase* pUI, bool bChangeHierarchy = false, bool bDrag = false);
			static void Push(Enums::eUIType type);

			static void Pop(Enums::eUIType type);
			static void Pop(CUIBase* closeUI);

			static void PopPopup();

			static void OnLoad(Enums::eUIType type);

			static void OnComplete(CUIBase* uiBase);
			static void OnFail();

			static void Clear();

			static void SetLastSibling(CUIBase* pFrontUI);
			//static CUIBase* GetCollisionUI();

			friend CApplication;
			friend CRenderManager;
		private:
			CUIManager();
			~CUIManager();

			static void Initialize();
			static void Release();

			static void Tick();
			static void LastTick();

			static void Render(HDC hdc);

			static void	CloseUI(INT closeUIIdx);

			static void MouseEvent(CUIBase* pUI, CUIBase* pChild);
			static CUIBase* GetTopUI();
			static CUIBase* GetParentUI(CUIBase* pChild);
			static CUIBase* GetFocusUI();
			static INT FindUIIdex(const CUIBase* pTarget);

			static std::queue<Enums::eUIType> m_queUIType; //대기열
			static std::vector<CUIBase*> m_vecCurrentUIs; //현재 UI 목록
			/// <summary>
			/// vector를 사용하는 이유는 캐시 적중률, 참조 연산등을 고려해 선택
			/// </summary>

			static std::unordered_map<Enums::eUIType, CUIBase*> m_unmapUI; //캐싱
			static CUIBase* m_pCurrentUI; //현재 UI
		};
	}


	using UI = Manager::CUIManager;
//	#define UI CUIManager
}

