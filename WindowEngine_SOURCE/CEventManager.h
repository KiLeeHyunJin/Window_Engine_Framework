#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CApplication;
	class CActor;
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

		class EventAddActor : public EventJob
		{
		public :
			EventAddActor(CActor* _pObj, CScene* _pScene, bool _bDontDestroy) :
				pObj(_pObj), pScene(_pScene), bDontDestroy(_bDontDestroy)
			{}
			virtual ~EventAddActor()
			{}
			virtual void operator () ();
			
		private :
			CActor* pObj;
			CScene* pScene;
			bool bDontDestroy;
		};

		class EventDeleteActor : public EventJob
		{
		public:
			EventDeleteActor(CActor* _pObj) :	
				pObj(_pObj)
			{}
			virtual ~EventDeleteActor()
			{}
			virtual void operator () ();
		private:
			CActor* pObj;
		};

		class EventChangeLayerActor : public EventJob
		{
		public:
			EventChangeLayerActor(CActor* _pObj, CScene* _pScene, UINT _layer) :
				pObj(_pObj), pScene(_pScene), layer(_layer)
			{}
			virtual ~EventChangeLayerActor()
			{}
			virtual void operator () ();
		private:
			CActor* pObj;
			CScene* pScene;
			const UINT layer;
		};

		class EventSetDontDestoryActor : public EventJob
		{
		public :
			EventSetDontDestoryActor(CActor* _pObj, CScene* _pCurrentScene, bool _bChangeState) :
				pObj(_pObj), pCurrentScene(_pCurrentScene), bChangeState(_bChangeState)
			{ }
			virtual ~EventSetDontDestoryActor()
			{ }
			virtual void operator() ();
			
		private:
			CActor* pObj;
			CScene* pCurrentScene;
			const bool bChangeState;
		};

		/// <summary>
		/// LastTickComponent에서 처리
		/// </summary>
		/// <param name="loadSceneID">Enum값으로 지정하는것을 추천</param>
		/// <param name="changeTime">전환 예약 시간</param>
		static void LoadScene(UINT loadSceneID, float changeTime = 0);

		/// <summary>
		/// LastTickComponent에서 처리
		/// </summary>
		static void ChangeLayer(CActor* pObj, UINT layerType);

		/// <summary>
		/// LastTickComponent에서 처리
		/// </summary>
		/// <param name="pObj"></param>
		static void SetDontDestroyActor(CActor* pObj, bool state);

		/// <summary>
		/// TickComponent에서 처리
		/// </summary>
		static void AddActor(CScene* pTargetScene, CActor* pObj, bool dontDestroy);
		
		/// <summary>
		/// TickComponent에서 처리
		/// </summary>
		static void DeleteActor(CActor* pObj);
		
		static void Clear();

		friend CApplication;
	private:
		CEventManager();
		~CEventManager();

		static void Initialize();
		static void Release();

		static void TickComponent();
		static void LastTickComponent();

		static void Job();
		
		static void ChangeScene();

		static std::queue<EventJob*> m_quequeEventJob;
		static std::pair<const UINT, float>* m_pChangeScene;

	};

	using EVENT = CEventManager;


}

