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
			DECLARE_SINGLE(CDataManager)
			RELEASE_SINGLE(CDataManager)
		public:
			void Load(const std::wstring& key, const std::wstring& path);
			CData* GetData(const std::wstring& key);


			friend CApplication;
		private:
			void Initialize();
			void Release();

			//CDataManager();
			~CDataManager();

			std::unordered_map<std::wstring, CData*> _unData = {};

		};
	}

	
	using DATA = Manager::CDataManager;
}


