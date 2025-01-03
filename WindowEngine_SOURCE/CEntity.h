#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CEntity
	{
	public:
		CEntity();
		virtual ~CEntity();
		std::wstring& GetName() { return m_wsName; }
		void SetName(const std::wstring& name) { m_wsName = name; }
	private:
		std::wstring m_wsName;
	};


}

