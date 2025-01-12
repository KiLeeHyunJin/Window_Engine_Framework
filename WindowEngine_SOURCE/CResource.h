#pragma once
#include "CEntity.h"
#include "Enums.h"

namespace Framework::Resource
{
	class CResourceManager;

	class CResource : public CEntity
	{
	public:
		virtual HRESULT Load(const std::wstring& wstrPath)	 = 0;
		const std::wstring& GetPath() { return m_wstrPath; }
		void SetPath(const std::wstring& wstrPath) { m_wstrPath = wstrPath; }
		virtual ~CResource();

		friend CResourceManager;
	protected:
		CResource(Enums::eResourceType e_type);
		

	private:

		Enums::eResourceType m_eResourceType;
		std::wstring m_wstrPath;
	};

	
}