#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CEntity
	{
	public:
		CEntity();
		virtual ~CEntity();
		wstring& GetName() { return m_wsName; }
		void SetName(const wstring& name) { m_wsName = name; }
	private:
		wstring m_wsName;
	};


}

