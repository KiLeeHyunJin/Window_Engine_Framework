#include "CDataManager.h"

namespace Framework
{
	std::unordered_map<std::wstring, std::wstring> CDataManager::_unData = {};

	void CDataManager::Load(const std::wstring& key, const std::wstring& path)
	{

	}

	void CDataManager::GetData(const std::wstring& key)
	{

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
