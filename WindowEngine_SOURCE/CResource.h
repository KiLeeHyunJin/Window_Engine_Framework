#include "CEntity.h"

namespace Framework
{
	class CResource
	{
	public:
		CResource(Enum::eResourceType e_type);
		virtual ~CResource();

		virtual HRESULT Load(const std::wstring& wstrPath)	 = 0;
		const std::wstring& GetPath() { return m_wstrPath; }
	private:
		Enum::eResourceType m_eResourceType;
		std::wstring m_wstrPath;
	};

	
}