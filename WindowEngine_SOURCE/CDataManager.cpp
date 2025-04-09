#include "CDataManager.h"

namespace Framework
{

	namespace Manager
	{
		//std::unordered_map<std::wstring, CData*> CDataManager::_unData = {};
		CDataManager* CDataManager::s_instance = nullptr;

		void CDataManager::Load(const std::wstring& key, const std::wstring& path)
		{

		}

		CData* CDataManager::GetData(const std::wstring& key)
		{
			return nullptr;
		}

		void CDataManager::Initialize()
		{
		}

		void CDataManager::Release()
		{
			for (auto& data : _unData)
			{

			}
			_unData.clear();
		}

		CDataManager::~CDataManager()
		{
		}
	}

	
}
