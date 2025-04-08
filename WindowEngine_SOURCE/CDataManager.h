#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CApplication;
	class CData;

	namespace Manager
	{
		class CDataManager
		{
		public:
			static void Load(const std::wstring& key, const std::wstring& path);
			static CData* GetData(const std::wstring& key);


			friend CApplication;
		private:
			static void Initialize();
			static void Release();

			CDataManager();
			~CDataManager();

			static std::unordered_map<std::wstring, CData*> _unData;
		};
	}

	
	using DATA = Manager::CDataManager;
}


