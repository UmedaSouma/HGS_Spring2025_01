//==========================
// 
// �����u���b�N[block_ally.cpp]
// Author Soma Umeda
//
//==========================

//include
#include "block_enemy.h"
#include "manager.h"
#include "model.h"

//�ÓI�����o������
const int CBlockEnemy::PRIORITY = 1;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CBlockEnemy::CBlockEnemy(int nPriority) :CBlock(nPriority), m_nModelIdx(0)
{

}

//==========================
//�f�X�g���N�^
//==========================
CBlockEnemy::~CBlockEnemy()
{

}

//==========================
//����������
//==========================
HRESULT CBlockEnemy::Init()
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
void  CBlockEnemy::Uninit()
{
	//�I������
	CObjectX::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CBlockEnemy::Update()
{
	//�X�V����
	CObjectX::Update();
}

//==========================
//�`�揈��
//==========================
void CBlockEnemy::Draw()
{
	//�`�揈��
	CObjectX::Draw();
}

//===========================================================================================================
// �����������̏���
//===========================================================================================================
void CBlockEnemy::Hit()
{
}

//==========================
//�I�u�W�F�N�g����
//==========================
CBlockEnemy* CBlockEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CBlockEnemy* pBlockEnemy = DBG_NEW CBlockEnemy;

	//�ʒu�̐ݒ�
	pBlockEnemy->SetPos(pos);

	//�X�P�[���̐ݒ�
	pBlockEnemy->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBlockEnemy->m_nModelIdx = pModel->Regist("data\\MODEL\\soil.x");
	pBlockEnemy->BindModel(pModel->GetMeshAdress(pBlockEnemy->m_nModelIdx),
		pModel->GetBuffMatAdress(pBlockEnemy->m_nModelIdx),
		pModel->GetNumMatAdress(pBlockEnemy->m_nModelIdx),
		pModel->GetTexIdx(pBlockEnemy->m_nModelIdx));

	//����������
	pBlockEnemy->Init();

	return pBlockEnemy;
}