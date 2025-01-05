#include "CEntity.h"

namespace Framework
{
	class CResource
	{
	public:
		CResource(Enums::eResourceType e_type);
		virtual ~CResource();

		virtual HRESULT Load(const std::wstring& wstrPath)	 = 0;
		const std::wstring& GetPath() { return m_wstrPath; }
	private:
		Enums::eResourceType m_eResourceType;
		std::wstring m_wstrPath;
	};

	
}