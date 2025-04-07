#pragma once
#include "CScene.h"

namespace Framework
{

	class CDontDestroyOnLoad : public CScene
	{
	public:
		CDontDestroyOnLoad();
		~CDontDestroyOnLoad();

	private:
		virtual void Initialize()	override;
		virtual void Release()		override;

		virtual void TickComponent()			override;
		virtual void LastTickComponent()		override;

		virtual void Render(HDC hdc) override;

		virtual void OnEnter()		override;
		virtual void OnExit()		override;


		// CScene��(��) ���� ��ӵ�
		void LastRender(HDC hdc) override;

	};
}
