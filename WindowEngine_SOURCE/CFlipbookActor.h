#pragma once
#include "CActor.h"
#include "CommonInclude.h"

namespace Framework
{
    namespace Resource
    {
        class CFlipbook;
    }
    using namespace Resource;

    class CFlipbookActor :
        public CActor
    {
        DECLARE_PARENT(CActor)
    public:
        CFlipbookActor(UINT layer);
        virtual ~CFlipbookActor();

        void SetFlipbook(const CFlipbook* flipbook) 
        {  
            CFlipbook* pFlipbook = const_cast<CFlipbook*>(flipbook);
            m_pFlipbook = pFlipbook;
        }
        void Reset();

    protected:
		/// <summary>
		  /// ��ġ �� ȣ��
		  /// </summary>
		void Initialize()			override;
		/// <summary>
		/// ��ġ �� ȣ��
		/// </summary>
		void BeginPlay()			override;
		/// <summary>
		/// ���� �� ȣ��
		/// </summary>
		void Release()				override;
		/// <summary>
		/// 1�ʿ� 80�� ȣ��
		/// </summary>
		/// <returns>false�� ��ȯ �� ���� ����</returns>
		bool Tick()					override;
		/// <summary>
		/// Tick ���� �����ϴ� �Լ�
		/// </summary>
		/// <returns>false�� ��ȯ �� ���� ����</returns>
		bool LastTick()				override;
		/// <summary>
		/// �浹 ���� ȣ��
		/// </summary>
		void FixedTick()			override;
		/// <summary>
		/// FixedTick ���� ȣ��
		/// </summary>
		bool Render(HDC hdc) const	override;
    private:
        void AnimationTickComponent();

        Resource::CFlipbook* m_pFlipbook;
        float m_fSumTime;
        INT m_uiIndex;
        bool m_bCompleted;


    };


}
