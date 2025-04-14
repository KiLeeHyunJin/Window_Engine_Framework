#include "CUIManager.h"
#include "CUIBase.h"
#include "CButton.h"
#include "CInputManager.h"

namespace Framework
{

	namespace Manager
	{
		CUIManager* CUIManager::s_instance = nullptr;

		CUIManager::~CUIManager()
		{
		}

		void CUIManager::Initialize()
		{

		}

		void CUIManager::LoadUI(Enums::eUIType type, CUIBase* pUI, bool bChangeHierarchy, bool bDrag)
		{
			pUI->SetDraggable(bDrag);
			pUI->SetChangeHierarchy(bChangeHierarchy);
			pUI->SetType(type);
			m_unmapUI.insert(std::make_pair(type, pUI));
		}

		void CUIManager::Push(Enums::eUIType type)
		{
			m_queUIType.push(type);
		}

		void CUIManager::Pop(Enums::eUIType type)
		{
			const INT size = (INT)m_vecCurrentUIs.size();
			if (size == 0) { return; }

			const auto& findIter	= m_unmapUI.find(type);
			const CUIBase* findUI	= findIter->second;

			INT closeUIIdx = findIter->second->GetIndex();
			Enums::eUIType closeUIType = m_vecCurrentUIs[closeUIIdx]->GetType();
			if (closeUIIdx < 0 ||
				closeUIType != type)
			{
				closeUIIdx = FindUIIdex(findUI);
			}

			if (closeUIIdx <= -1) { return; } //이미 닫혀있는 UI

			CloseUI(closeUIIdx);
		}

		void CUIManager::Pop(CUIBase* closeUI)
		{
			const UINT size = (UINT)m_vecCurrentUIs.size();
			if (size == 0) { return; }

			INT closeUIIdx = closeUI->GetIndex();
			const Enums::eUIType type = closeUI->GetType();

			if (closeUIIdx < 0 ||
				m_vecCurrentUIs[closeUIIdx]->GetType() != type)
			{
				closeUIIdx = FindUIIdex(closeUI);
			}
			if (closeUIIdx < 0) { return; }

			CloseUI(closeUIIdx);
		}

		void CUIManager::PopPopup()
		{
			const INT size = static_cast<INT>(m_vecCurrentUIs.size());

			if (size == 0)
			{
				return;
			}

			for (INT i = size - 1; i >= 0; i--)
			{
				if (m_vecCurrentUIs[i]->GetType() == Enums::eUIType::Popup)
				{
					CloseUI(i);
					return;  // 만약 하나만 닫고 싶다면 유지
				}
			}
		}

		INT CUIManager::FindUIIdex(const CUIBase* pTarget)
		{
			const INT size = static_cast<INT>(m_vecCurrentUIs.size());

			for (INT i = 0; i < size; i++)
			{
				if (pTarget == m_vecCurrentUIs[i])
				{
					return i;
				}
			}
			return -1;
		}

		void CUIManager::CloseUI(INT closeUIIdx)
		{
			const auto iter = m_vecCurrentUIs.cbegin() + closeUIIdx;
			if (iter != m_vecCurrentUIs.cend())
			{
				(*iter)->SetIndex(-1);
				m_vecCurrentUIs.erase(iter);
			}

			const INT size = static_cast<INT>(m_vecCurrentUIs.size());
			for (INT i = closeUIIdx; i < size; i++)
			{
				m_vecCurrentUIs[i]->SetIndex(i);
			}
		}

		void CUIManager::OnLoad(Enums::eUIType type)
		{
			std::unordered_map<Enums::eUIType, CUIBase*>::iterator iter = m_unmapUI.find(type);
			if (iter == m_unmapUI.end())
			{
				OnFail();
			}
			else
			{
				OnComplete(iter->second);
			}
		}

		void CUIManager::OnComplete(CUIBase* uiBase)
		{
			if (uiBase == nullptr) { return; }

			uiBase->Initialize();
			uiBase->Active();
			uiBase->Tick();
			uiBase->LastTick();

			if (uiBase->GetFullScreen())
			{
				for (const auto& pUI : m_vecCurrentUIs)
				{
					pUI->InActive();
				}
			}

			const UINT uiIdx = (UINT)m_vecCurrentUIs.size();
			uiBase->SetIndex(uiIdx);

			m_vecCurrentUIs.push_back(uiBase);
			m_pCurrentUI = nullptr;
		}

		void CUIManager::OnFail()
		{
			m_pCurrentUI = nullptr;
		}

		void CUIManager::Release()
		{
			Clear();
			for (auto& ui : m_unmapUI)
			{
				ui.second->Clear();
				ui.second->Release();
				delete ui.second;
			}
		}

		void CUIManager::Clear()
		{
			m_pCurrentUI = nullptr;
			for (const auto pUI : m_vecCurrentUIs)
			{
				pUI->SetIndex(-1);
			}
			m_vecCurrentUIs.clear();
			while (m_queUIType.empty() == false)
			{
				m_queUIType.pop();
			}
		}

		void CUIManager::SetLastSibling(CUIBase* pUI)
		{
			CUIBase* pParentUI = GetParentUI(pUI);
			if (pParentUI == nullptr) { return; }
			if (pParentUI->GetChangeHierarchy() == false) { return; }

			const UINT size = (UINT)m_vecCurrentUIs.size();
			const UINT currentIdx = pParentUI->GetIndex();

			if (size <= 1 ||
				(size - 1) == currentIdx) {
				return;
			} // 마지막 요소면 이동 불필요


			auto iter = m_vecCurrentUIs.cbegin() + currentIdx;
			if (iter != m_vecCurrentUIs.cend())
			{
				CUIBase* save = *iter;
				m_vecCurrentUIs.erase(iter);               // 요소 삭제 (O(N))
				m_vecCurrentUIs.push_back(save);          // 뒤에 추가 (O(1))

				for (UINT i = currentIdx; i < size; i++) //번호 다시 기입
				{
					m_vecCurrentUIs[i]->SetIndex(i);
				}
			}
		}


		void CUIManager::Tick()
		{
			for (auto& pUI : m_vecCurrentUIs)
			{
				pUI->Tick();
			}

			if (m_queUIType.size() > 0)
			{
				Enums::eUIType requestUI = m_queUIType.front();
				m_queUIType.pop();
				OnLoad(requestUI);
			}

			CUIBase* pTargetUI = GetFocusUI();
			if (m_pCurrentUI == nullptr)
			{
				m_pCurrentUI = pTargetUI;
			}
			else
			{
				if (m_pCurrentUI->GetCurrOn() == false)
				{
					m_pCurrentUI = pTargetUI;
				}
				else
				{
					if (pTargetUI != nullptr &&
						pTargetUI != m_pCurrentUI)
					{
						const CUIBase* pPrevParent = GetParentUI(m_pCurrentUI);
						const CUIBase* pNewParent = GetParentUI(pTargetUI);

						if (pPrevParent->GetIndex() <= pNewParent->GetIndex())
						{
							m_pCurrentUI = pTargetUI;
						}
					}
				}
			}

			for (auto& pUI : m_vecCurrentUIs)
			{
				MouseEvent(pUI, m_pCurrentUI);
			}
		}

		void CUIManager::LastTick()
		{
			for (auto& pUI : m_vecCurrentUIs)
			{
				pUI->LastTick();
			}
		}

		void CUIManager::Render(HDC hdc)
		{
			for (const auto& pUI : m_vecCurrentUIs)
			{
				pUI->Render(hdc);
			}
		}

		void CUIManager::MouseEvent(CUIBase* pUI, CUIBase* pfocusUI)
		{
			if (pUI == nullptr)
			{	return;		}

			if (pUI == pfocusUI)
			{
				pUI->Enter();
				if (GET_SINGLE(INPUT).GetKeyDown(eKeyCode::LBUTTON))
				{
					pUI->Down();
				}
				else if (GET_SINGLE(INPUT).GetKeyUp(eKeyCode::LBUTTON))
				{
					pUI->Up();
				}
			}
			else
			{
				pUI->Exit();
			}


			const std::vector<CUIBase*>& childs = pUI->GetChilds();
			for (CUIBase* pChildUI : childs)
			{
				MouseEvent(pChildUI, pfocusUI);
			}
		}

		CUIBase* CUIManager::GetTopUI()
		{
			if (m_vecCurrentUIs.empty() == false)
			{
				for (auto it = m_vecCurrentUIs.rbegin(); it != m_vecCurrentUIs.rend(); ++it)
				{
					if ((*it)->GetCurrOn())
					{
						return *it;
					}
				}
			}
			return nullptr;
		}

		CUIBase* CUIManager::GetParentUI(CUIBase* pChild)
		{
			if (pChild == nullptr) { return nullptr; }

			CUIBase* pParent = pChild;
			CUIBase* pParentParent = pParent->GetParent();
			while (pParentParent != nullptr)
			{
				pParent = pParentParent;
				pParentParent = pParent->GetParent();
			}
			return pParent;
		}

		CUIBase* CUIManager::GetFocusUI()
		{
			CUIBase* pTopUI = GetTopUI();
			if (pTopUI == nullptr) { return nullptr; }
			if (m_vecCurrentUIs.size() == 0) { return nullptr; }

			std::queue<CUIBase*> queUIs;
			queUIs.push(pTopUI);

			CUIBase* targetUI = nullptr;
			while (queUIs.empty() == false)
			{
				CUIBase* pUI = queUIs.front();
				queUIs.pop();

				if (pUI->GetCurrOn())
				{
					targetUI = pUI;
					const std::vector<CUIBase*>& targetChilds = pUI->GetChilds();

					for (const auto ui : targetChilds)
					{
						queUIs.push(ui);
					}
				}
			}
			return targetUI;
		}
	}

	





}