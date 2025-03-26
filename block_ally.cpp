//==========================
// 
// �����u���b�N[block_ally.cpp]
// Author Soma Umeda
//
//==========================

//include
#include "block_ally.h"
#include "manager.h"
#include "model.h"

//�ÓI�����o������
const int CBlockAlly::PRIORITY = 1;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CBlockAlly::CBlockAlly(int nPriority) :CBlock(nPriority), m_nModelIdx(0)
{

}

//==========================
//�f�X�g���N�^
//==========================
CBlockAlly::~CBlockAlly()
{

}

//==========================
//����������
//==========================
HRESULT CBlockAlly::Init()
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
void  CBlockAlly::Uninit()
{
	//�I������
	CObjectX::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CBlockAlly::Update()
{
	//�X�V����
	CObjectX::Update();
}

//==========================
//�`�揈��
//==========================
void CBlockAlly::Draw()
{
	//�`�揈��
	CObjectX::Draw();
}

//===========================================================================================================
// �����������̏���
//===========================================================================================================
void CBlockAlly::Hit()
{
}

//==========================
//�I�u�W�F�N�g����
//==========================
CBlockAlly* CBlockAlly::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CBlockAlly* pBlockAlly = DBG_NEW CBlockAlly;

	//�ʒu�̐ݒ�
	pBlockAlly->SetPos(pos);

	//�X�P�[���̐ݒ�
	pBlockAlly->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBlockAlly->m_nModelIdx = pModel->Regist("data\\MODEL\\soil.x");
	pBlockAlly->BindModel(pModel->GetMeshAdress(pBlockAlly->m_nModelIdx),
		pModel->GetBuffMatAdress(pBlockAlly->m_nModelIdx),
		pModel->GetNumMatAdress(pBlockAlly->m_nModelIdx),
		pModel->GetTexIdx(pBlockAlly->m_nModelIdx));

	//����������
	pBlockAlly->Init();

	return pBlockAlly;
}