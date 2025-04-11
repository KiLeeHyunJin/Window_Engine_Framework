#pragma once
#include "CResource.h"
#include "CommonInclude.h"

namespace Framework//::Resource
{

	namespace Resource
	{
		class CTexture;
		class CSprite;
		class CFlipbook;
	}

	namespace Manager
	{
		using namespace Maths;
		using namespace Resource;

		class CResourceManager 
		{
			DECLARE_SINGLE(CResourceManager)
			RELEASE_SINGLE(CResourceManager)
		public:

			CTexture* LoadTexture(const std::wstring& key, const std::wstring& path);
			void		 LoadSound(const std::wstring& key);

			const bool CreateSprite(const CTexture* texture, const std::wstring& key, const Vector2Int& leftTop, const Vector2Int& size, const Vector2Int& pivot = Maths::Vector2Int::Zero);
			const bool CreateFlipbook(const std::wstring& key, bool loop);

			void InsertSprite(const CFlipbook* flipbook, const CSprite* sprite, float duration = 1);

			const CTexture* FindTexture(const std::wstring& key);
			const CSprite* FindSprite(const std::wstring& key);
			const CFlipbook* FindFlipbook(const std::wstring& key);
			void FindSound(const std::wstring& key);

			void Tick()				{};
			void LastTick()			{};
			void Render(HDC hdc)	{};
			void Initialize()		{};

			friend class CApplication;
		private:
			//CResourceManager();
			~CResourceManager();

			CResource* LoadResource(CResource* pResource, const std::wstring& key, const std::wstring& path)
			{
				if (FAILED(pResource->Load(path)))
				{
					assert(true);
					SAFE_DELETE(pResource);
					return nullptr;
				}
				pResource->SetName(key);
				pResource->SetPath(path);
				return pResource;
			}

			void Release();

			std::map<const std::wstring, CResource*> m_mapResoucres = {};

			std::map<const std::wstring, CTexture*> m_mapTextures	= {};
			std::map<const std::wstring, CSprite*> m_mapSprites		= {};
			std::map<const std::wstring, CFlipbook*> m_mapFlipbooks = {};

		};

	}
	using RESOURCE = Manager::CResourceManager;


	

}


