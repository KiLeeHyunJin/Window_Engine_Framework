#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CApplication;
	class CGameObject;
	class CScene;

	class CEventManager
	{
	public:
		struct LayerData
		{
			LayerData(CScene* _scene, Enums::eLayerType _targetLayer) : scene(_scene), targetLayer(_targetLayer)
			{}
			CScene* scene;
			Enums::eLayerType targetLayer;
		};

		static void ChangeLayer(CGameObject* pObj, Enums::eLayerType layerType);

		static void SetDontDestroyGameObject(CGameObject* pObj);
		static void AddGameObject(CScene* pTargetScene, CGameObject* pObj, bool dontDestroy);

		__forceinline static void DeleteGameObject(CGameObject* pObj)	{ m_quequeDeleteObject.push(pObj); }


		static void Clear();

		friend CApplication;
	private:
		CEventManager();
		~CEventManager();

		static void Initialize();
		static void Release();

		static void Tick();
		static void LastTick();

		static void ProgressAddGameObject();
		static void ProgressDeleteGameObject();
		static void ProgressChangeLayer();

		static std::queue<std::pair<CGameObject*, CScene*>> m_quequeAddObject;
		static std::queue<std::pair<CGameObject*, LayerData>> m_quequeChangeLayerObject;
		static std::queue<CGameObject*> m_quequeDeleteObject;
		static std::pair<CScene, float>* m_pChangeScene;
	};

	using EVENT = CEventManager;
	using DeleteFunc = void(*)(CGameObject*); // 함수 포인터 - 정적 멤버 함수이므로, 객체 인스턴스 없이 호출 

	constexpr DeleteFunc Delete = &CEventManager::DeleteGameObject; //상수 함수 포인터 - constexpr을 붙였으므로 컴파일 타임 상수로 사용
}

