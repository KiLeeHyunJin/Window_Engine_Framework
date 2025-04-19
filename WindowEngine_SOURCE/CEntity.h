#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CEntity
	{
	public:
		CEntity();
		virtual ~CEntity();
		const std::wstring& GetName()				const	{ return m_wsName;			}
		bool CompareName(const std::wstring& name)	const	{ return m_wsName == name;	}
		void SetName(const std::wstring& name)				{ m_wsName = name;			}
	private:
		std::wstring m_wsName;
	};


}

