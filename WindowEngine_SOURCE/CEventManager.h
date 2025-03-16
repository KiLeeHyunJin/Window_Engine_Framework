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

		class EventJob
		{
		public :
			EventJob()	{}
			virtual ~EventJob()	{}
			virtual void operator () () = 0;
		};

		class EventAddGameObject : public EventJob
		{
		public :
			EventAddGameObject(CGameObject* _pObj, CScene* _pScene, bool _bDontDestroy) :
				pObj(_pObj), pScene(_pScene), bDontDestroy(_bDontDestroy)
			{}
			virtual ~EventAddGameObject()
			{}
			virtual void operator () ();
			
		private :
			CGameObject* pObj;
			CScene* pScene;
			bool bDontDestroy;
		};

		class EventDeleteGameObject : public EventJob
		{
		public:
			EventDeleteGameObject(CGameObject* _pObj) :	
				pObj(_pObj)
			{}
			virtual ~EventDeleteGameObject()
			{}
			virtual void operator () ();
		private:
			CGameObject* pObj;
		};

		class EventChangeLayerGameObject : public EventJob
		{
		public:
			EventChangeLayerGameObject(CGameObject* _pObj, CScene* _pScene, UINT _layer) :
				pObj(_pObj), pScene(_pScene), layer(_layer)
			{}
			virtual ~EventChangeLayerGameObject()
			{}
			virtual void operator () ();
		private:
			CGameObject* pObj;
			CScene* pScene;
			const UINT layer;
		};

		class EventSetDontDestoryGameObject : public EventJob
		{
		public :
			EventSetDontDestoryGameObject(CGameObject* _pObj, CScene* _pCurrentScene, bool _bChangeState) :
				pObj(_pObj), pCurrentScene(_pCurrentScene), bChangeState(_bChangeState)
			{ }
			virtual ~EventSetDontDestoryGameObject()
			{ }
			virtual void operator() ();
			
		private:
			CGameObject* pObj;
			CScene* pCurrentScene;
			const bool bChangeState;
		};

		/// <summary>
		/// LastTick에서 처리
		/// </summary>
		/// <param name="loadSceneID">Enum값으로 지정하는것을 추천</param>
		/// <param name="changeTime">전환 예약 시간</param>
		static void LoadScene(UINT loadSceneID, float changeTime = 0);

		/// <summary>
		/// LastTick에서 처리
		/// </summary>
		static void ChangeLayer(CGameObject* pObj, UINT layerType);

		/// <summary>
		/// LastTick에서 처리
		/// </summary>
		/// <param name="pObj"></param>
		static void SetDontDestroyGameObject(CGameObject* pObj, bool state);

		/// <summary>
		/// Tick에서 처리
		/// </summary>
		static void AddGameObject(CScene* pTargetScene, CGameObject* pObj, bool dontDestroy);
		
		/// <summary>
		/// Tick에서 처리
		/// </summary>
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

		static void Job();
		
		static void ChangeScene();

		static std::queue<EventJob*> m_quequeEventJob;
		static std::pair<const UINT, float>* m_pChangeScene;

	};

	using EVENT = CEventManager;


}

