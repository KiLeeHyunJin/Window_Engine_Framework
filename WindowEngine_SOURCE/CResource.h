#pragma once
#include "CEntity.h"


namespace Framework//::Resource
{
	namespace Manager
	{
		class CResourceManager;
	}

	namespace Resource
	{
		class CResource : public CEntity
		{
		public:
			CResource(Enums::eResourceType e_type);
			virtual ~CResource();

			virtual HRESULT Load(const std::wstring& wstrPath) = 0;
			const std::wstring& GetPath() const { return m_wstrPath; }
			void SetPath(const std::wstring& wstrPath) { m_wstrPath = wstrPath; }

			//friend Manager::CResourceManager;
		protected:


		private:
			Enums::eResourceType m_eResourceType;
			std::wstring m_wstrPath;
		};

	}
	
	
}