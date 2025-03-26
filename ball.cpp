//==========================
// 
// �{�[��[ball.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "ball.h"
#include "manager.h"
#include "model.h"

//�ÓI�����o������
const int CBall::PRIORITY = 1;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CBall::CBall(int nPriority) :
	CObjectX(nPriority),
m_nModelIdx(0),
m_Life(MAXLIFE)//����
{

}

//==========================
//�f�X�g���N�^
//==========================
CBall::~CBall()
{

}

//==========================
//����������
//==========================
HRESULT CBall::Init()
{
	//�T�C�Y�ݒ�
	SetSize();

	//�����ݒ�
	CObjectX::Init();
	
	SetMove({ 1.0f,1.0f,0.0f });

	return S_OK;
}

//==========================
//�I������
//==========================
void  CBall::Uninit()
{
	//�I������
	CObjectX::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CBall::Update()
{
	//�X�V����
	CObjectX::Update();

	SetPosOld(GetPos());
	SetPos(GetMove()+GetPos());
}

//==========================
//�`�揈��
//==========================
void CBall::Draw()
{
	//�`�揈��
	CObjectX::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CBall* CBall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CBall* pBall = DBG_NEW CBall;

	//�ʒu�̐ݒ�
	pBall->SetPos(pos);

	//�X�P�[���̐ݒ�
	pBall->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBall->m_nModelIdx = pModel->Regist("data\\MODEL\\ball.x");
	pBall->BindModel(pModel->GetMeshAdress(pBall->m_nModelIdx),
		pModel->GetBuffMatAdress(pBall->m_nModelIdx),
		pModel->GetNumMatAdress(pBall->m_nModelIdx),
		pModel->GetTexIdx(pBall->m_nModelIdx));

	//����������
	pBall->Init();

	//�^�C�v�ݒ�
	pBall->SetType(TYPE::BALL);

	return pBall;
}

//==========================
//���������炷
//==========================
void CBall::SubLife()
{
	m_Life--;

	Reset();

	if (m_Life <= 0)
	{
		Uninit();
		CManager::GetInstance()->GetGameManager()->SetEnd();
	}
}

//==========================
//�ʒu������
//==========================
void CBall::Reset()
{
	SetPos({ 0.0f, -50.0f, 0.0 });
}