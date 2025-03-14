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
		enum class eEventType
		{
			Delete,
			Add,

			Layer,
			Scene,

			Size
		};

		struct LayerData
		{
			LayerData(eEventType _eEventType, CScene* _scene, Enums::eLayerType _targetLayer = Enums::eLayerType::None) :
				eEventType(_eEventType), pScene(_scene), eTargetLayer(_targetLayer)
			{}
			CScene* pScene;
			eEventType eEventType;
			Enums::eLayerType eTargetLayer;
		};

		static void LoadScene(UINT loadSceneID, float changeTime = 0);

		static void ChangeLayer(CGameObject* pObj, Enums::eLayerType layerType);

		static void SetDontDestroyGameObject(CGameObject* pObj);
		static void AddGameObject(CScene* pTargetScene, CGameObject* pObj, bool dontDestroy);

		static void DeleteGameObject(CGameObject* pObj);
		
		static void Clear();

		friend CApplication;
	private:
		CEventManager();
		~CEventManager();

		static void Initialize();
		static void Release();

		static void Tick();
		static void LastTick();

		static void ProgressLifeObject();
		static void ProgressChangeObject();

		static void ProgressAddGameObject(CGameObject* pObj, LayerData& data);
		static void ProgressDeleteGameObject(CGameObject* pObj, LayerData& data);
		
		static void ProgressChangeLayer(CGameObject* pObj, LayerData& data);
		static void ProgressDontDestroy(CGameObject* pObj, LayerData& data);
		
		static void ProgressChangeScene();

		static std::queue<std::pair<CGameObject*, LayerData>> m_quequeObject;
		static std::queue<std::pair<CGameObject*, LayerData>> m_quequeChange;
		//static std::queue<CGameObject*> m_quequeDeleteObject;
		static std::pair<const UINT, float>* m_pChangeScene;

		//using Progress = ;
		using EventFuncPtr = void (*)(CGameObject*, CEventManager::LayerData&);

		static EventFuncPtr ProgressFunc[static_cast<int>(eEventType::Size)];
	};

	using EVENT = CEventManager;
	using DeleteFunc = void(*)(CGameObject*); // �Լ� ������ - ���� ��� �Լ��̹Ƿ�, ��ü �ν��Ͻ� ���� ȣ�� 

	constexpr DeleteFunc Delete = &CEventManager::DeleteGameObject; //��� �Լ� ������ - constexpr�� �ٿ����Ƿ� ������ Ÿ�� ����� ���
}

