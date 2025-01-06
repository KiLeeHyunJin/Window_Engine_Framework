#include "CEntity.h"

namespace Framework
{
	class CResourceManager;
	class CResource
	{
	public:
		virtual HRESULT Load(const std::wstring& wstrPath)	 = 0;
		const std::wstring& GetPath() { return m_wstrPath; }

		friend CResourceManager;
	private:
		CResource(Enums::eResourceType e_type);
		virtual ~CResource();
		Enums::eResourceType m_eResourceType;
		std::wstring m_wstrPath;
	};

	
}