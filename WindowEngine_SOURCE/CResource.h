#pragma once
#include "CEntity.h"
#include "Enums.h"

namespace Framework//::Resource
{
	namespace Resource
	{
		class CResource : public CEntity
		{
		public:
			virtual HRESULT Load(const std::wstring& wstrPath) = 0;
			const std::wstring& GetPath() const { return m_wstrPath; }
			void SetPath(const std::wstring& wstrPath) { m_wstrPath = wstrPath; }

			friend class CResourceManager;
		protected:
			CResource(Enums::eResourceType e_type);
			virtual ~CResource();

		private:
			Enums::eResourceType m_eResourceType;
			std::wstring m_wstrPath;
		};

	}
	
	
}