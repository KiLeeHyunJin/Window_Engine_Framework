#include "CDataManager.h"

namespace Framework
{
	std::unordered_map<std::wstring, CData*> CDataManager::_unData = {};

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

	CDataManager::CDataManager()
	{
	}
	CDataManager::~CDataManager()
	{
	}
}
