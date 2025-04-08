#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CApplication;
	class CActor;
	class CScene;

	namespace Manager
	{
		class CEventManager
		{
		public:

			class EventJob
			{
			public:
				EventJob() {}
				virtual ~EventJob() {}
				virtual void operator () () = 0;
			};

			class EventAddActor : public EventJob
			{
			public:
				EventAddActor(CActor* _pObj, bool _bDontDestroy) :
					pObj(_pObj), bDontDestroy(_bDontDestroy)
				{
				}
				virtual ~EventAddActor() {}
				virtual void operator () ();

			private:
				CActor* pObj;
				bool bDontDestroy;
			};

			class EventDeleteActor : public EventJob
			{
			public:
				EventDeleteActor(CActor* _pObj) :
					pObj(_pObj)
				{
				}
				virtual ~EventDeleteActor() {}
				virtual void operator () ();
			private:
				CActor* pObj;
			};

			class EventChangeLayerActor : public EventJob
			{
			public:
				EventChangeLayerActor(CActor* _pObj, UINT _layer) :
					pObj(_pObj), layer(_layer)
				{
				}
				virtual ~EventChangeLayerActor() {}
				virtual void operator () ();
			private:
				CActor* pObj;
				const UINT layer;
			};

			class EventSetDontDestoryActor : public EventJob
			{
			public:
				EventSetDontDestoryActor(CActor* _pObj, bool _bChangeState) :
					pObj(_pObj), bChangeState(_bChangeState)
				{
				}
				virtual ~EventSetDontDestoryActor() {}
				virtual void operator() ();

			private:
				CActor* pObj;
				const bool bChangeState;
			};

			/// <summary>
			/// LastTick���� ó��
			/// </summary>
			/// <param name="loadSceneID">Enum������ �����ϴ°��� ��õ</param>
			/// <param name="changeTime">��ȯ ���� �ð�</param>
			static void LoadScene(UINT loadSceneID, float changeTime = 0);

			/// <summary>
			/// LastTick���� ó��
			/// </summary>
			static void ChangeLayer(CActor* pObj, UINT layerType);

			/// <summary>
			/// LastTick���� ó��
			/// </summary>
			/// <param name="pObj"></param>
			static void SetDontDestroyActor(CActor* pObj, bool state);

			/// <summary>
			/// Tick���� ó��
			/// </summary>
			static void AddActor(CActor* pObj, bool dontDestroy);

			/// <summary>
			/// Tick���� ó��
			/// </summary>
			static void DeleteActor(CActor* pObj);

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
	}

	using EVENT = Manager::CEventManager;


}

