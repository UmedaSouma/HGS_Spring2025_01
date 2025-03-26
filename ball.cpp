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
CBall::CBall(int nPriority) :CObjectX(nPriority), m_nModelIdx(0)
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
	//SetSize();

	//�����ݒ�
	CObjectX::Init();

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

	return pBall;
}