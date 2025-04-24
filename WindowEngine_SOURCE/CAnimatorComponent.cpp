#pragma once
#include "CAnimatorComponent.h"
#include "CResourceManager.h"

#include <windows.h>

#include <fcntl.h>
#include <io.h>

namespace Framework
{

	CAnimatorComponent::CAnimatorComponent() :
		CComponent(Enums::eComponentType::Animator),
		m_pCurrentAnimation(nullptr),
		m_bLoop(false),
		m_mapAnimations{}
	{
	}

	CAnimatorComponent::~CAnimatorComponent()
	{

	}

	void CAnimatorComponent::BeginPlay()
	{	}

	bool CAnimatorComponent::TickComponent()
	{
		if (m_pCurrentAnimation != nullptr)
		{
			m_pCurrentAnimation->TickComponent();
			Events* events = FindEvents(m_pCurrentAnimation->GetName());
			if (m_pCurrentAnimation->IsCompleted())
			{
				if (events)
				{
					events->m_CompleteEvent();
				}
				if (m_bLoop)
				{
					m_pCurrentAnimation->Reset();
				}
			}
		}
		return true;
	}

	bool CAnimatorComponent::LastTickComponent()
	{	return true;	}

	void CAnimatorComponent::Render(HDC hdc)
	{
		if (m_pCurrentAnimation != nullptr)
		{
			m_pCurrentAnimation->Render(hdc);
		}
	}

	void CAnimatorComponent::CreateAnimation(const std::wstring& name,const CTexture* spriteSheet, const Vector2& leftTop, UINT spriteLength, float duration)
	{
		CAnimation* pAnim = FindAnimation(name);
		if (pAnim != nullptr)
		{	return;		}
		pAnim = new CAnimation();
		pAnim->CreateAnimation(name, true);
		pAnim->SetOwner(this);
		m_mapAnimations.insert(std::make_pair(name,pAnim));
	}


	void CAnimatorComponent::CreateAnimationByFolder(const std::wstring& name, const std::wstring& path, const float duration)
	{
		const CAnimation* pAnim = FindAnimation(name);
		if (pAnim != nullptr)
		{	return;	}
		UINT size = 0;
		const CTexture* spriteSheet = GET_SINGLE(RESOURCE).FindTexture(name);

		if (spriteSheet == nullptr)
		{
			std::vector<const Resource::CTexture*> vecImgs = {};

#pragma region  LoadImg
			const std::wstring searchPath = path + L"\\*";

			WIN32_FIND_DATAW findFileData;
			HANDLE hFind = FindFirstFileW(searchPath.c_str(), &findFileData);

			if (hFind != INVALID_HANDLE_VALUE)
			{
				do
				{
					const std::wstring wstrName = findFileData.cFileName;
					if (wstrName == L"." || wstrName == L"..")
					{
						continue;
					}

					if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
					{
						const std::wstring fileName = wstrName;
						const std::wstring fullName = path + wstrName;
						const Resource::CTexture* pTexture = GET_SINGLE(RESOURCE).LoadTexture(fileName, fullName);
						if (pTexture != nullptr)
						{
							vecImgs.push_back(pTexture);
						}
					}
				} while (FindNextFileW(hFind, &findFileData) != 0);
				FindClose(hFind);
			}
			else
			{
				assert(false);
			}
#pragma endregion

			size = (UINT)vecImgs.size();
			if (size == 0)
			{	assert(false);	}

			UINT imgWidth = 0;
			UINT imgHeigth = 0;
			std::vector<Maths::Vector2> sizes = {};
			for (const auto& img : vecImgs)
			{
				sizes.push_back(Maths::Vector2((float)img->GetWidth(), (float)img->GetHeight()));
				imgWidth += img->GetWidth();
				if (imgHeigth < img->GetHeight())
				{	imgHeigth = img->GetHeight();	}
			}

			/*spriteSheet = CTexture::Create(name, imgWidth, imgHeigth, sizes);
			float stackWidth = 0;
			for (UINT i = 0; i < size; i++)
			{
				BitBlt(spriteSheet->GetHDC(), (UINT)stackWidth, 0,
					(UINT)sizes[i].x, (UINT)sizes[i].y, vecImgs[i]->GetHDC(), 0, 0, SRCCOPY);
				stackWidth += sizes[i].x;
			}*/
		}
		else
		{
			//size = (UINT)spriteSheet->GetSpriteSize().size();
		}

		CreateAnimation(name, spriteSheet, Vector2::Zero, size, duration);
	}

	CAnimation* CAnimatorComponent::FindAnimation(const std::wstring& name)
	{
		auto iter = m_mapAnimations.find(name);
		if (iter == m_mapAnimations.end())
		{	return nullptr;		}
		return iter->second;
	}

	void CAnimatorComponent::PlayAnimation(const std::wstring& name, bool loop)
	{
		CAnimation* pAnim = FindAnimation(name);
		if (pAnim != nullptr)
		{
			if (m_bLoop != loop)
			{	m_bLoop = loop;	}
			EndAnimation();
			StartAnimation(pAnim);
		}
	}

	std::function<void()>& CAnimatorComponent::GetStartEvent(const std::wstring& name)
	{
		Events* pEvents = FindEvents(name);
		return pEvents->m_StartEvent.mEvent;
		// TODO: 여기에 return 문을 삽입합니다.
	}

	std::function<void()>& CAnimatorComponent::GetCompleteEvent(const std::wstring& name)
	{
		Events* pEvents = FindEvents(name);
		return pEvents->m_CompleteEvent.mEvent;

		// TODO: 여기에 return 문을 삽입합니다.
	}

	std::function<void()>& CAnimatorComponent::GetEndEvent(const std::wstring& name)
	{
		Events* pEvents = FindEvents(name);
		return pEvents->m_EndEvent.mEvent;
		// TODO: 여기에 return 문을 삽입합니다.
	}

	CAnimatorComponent::Events* CAnimatorComponent::FindEvents(const std::wstring& name)
	{
		const auto& iter = m_mapEvents.find(name);
		if (iter == m_mapEvents.end())
		{
			return nullptr;
		}
		return iter->second;
	}

	void CAnimatorComponent::EndAnimation()
	{
		if (m_pCurrentAnimation != nullptr)
		{
			Events* oldEvents = FindEvents(m_pCurrentAnimation->GetName());
			if (oldEvents)
			{
				oldEvents->m_EndEvent();
			}
		}
	}

	void CAnimatorComponent::StartAnimation(CAnimation* const pAnim)
	{
		m_pCurrentAnimation = pAnim;
		m_pCurrentAnimation->Reset();
		Events* newEvents = FindEvents(m_pCurrentAnimation->GetName());
		if (newEvents)
		{
			newEvents->m_StartEvent();
		}
	}

	void CAnimatorComponent::Release()
	{
		RELEASE_MAP(m_mapAnimations);
		RELEASE_MAP(m_mapEvents);
		m_pCurrentAnimation = nullptr;
		//for (const auto& pair : m_mapAnimations)
		//{
		//	delete pair.second;
		//}
		//for (const auto& pair : m_mapEvents)
		//{
		//	delete pair.second;
		//}
		//m_mapAnimations.clear();
		//m_mapEvents.clear();
	}

}
