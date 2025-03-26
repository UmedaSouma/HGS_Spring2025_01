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
CBlockEnemy::CBlockEnemy(int nPriority) :
	CBlock(nPriority),
	m_nModelIdx(0),
	m_ball(nullptr)
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
	//�{�[���̏����擾
	GetBallInfo();

	//�T�C�Y�ݒ�
	SetSize();

	//�����ݒ�
	CObjectX::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CBlockEnemy::Uninit()
{
	if (m_ball != nullptr)
	{
		m_ball = nullptr;
	}

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
	
	Hit();
}

//==========================
//�`�揈��
//==========================
void CBlockEnemy::Draw()
{
	//�`�揈��
	CObjectX::Draw();
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

//===========================================================================================================
// �����������̏���
//===========================================================================================================
void CBlockEnemy::Hit()
{
	//�����蔻��̏����擾
	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	//�����̔���
	bool collision = pCollision->RectangleLeft(m_ball->GetPosOld(), m_ball->GetPos(), GetPos(),
		m_ball->GetVtxMax(), m_ball->GetVtxMin(), GetVtxMax(), GetVtxMin());

	if (collision)
	{
		m_ball->Uninit();
	}
}

//===========================================================================================================
//�{�[���̏����擾
//===========================================================================================================
void CBlockEnemy::GetBallInfo()
{
	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CBall::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CBall::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::BALL)
		{//�I�u�W�F�N�g���G�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CBall::PRIORITY);
			continue;
		}

		//�{�[���̏����擾
		m_ball = dynamic_cast<CBall*>(pObj);

		break;
	}
}