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
CBlockAlly::CBlockAlly(int nPriority) :
	CBlock(nPriority),
	m_nModelIdx(0),
	m_ball(nullptr)
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
void  CBlockAlly::Uninit()
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
void CBlockAlly::Update()
{
	SetPosOld(GetPos());
	SetPos(GetMove() + GetPos());

	if (GetPos().z > 0)
	{
		SetMove({ 0.0f,0.0f,0.0f });
	}

	//�X�V����
	CObjectX::Update();

	//�����蔻��
	Hit();
}

//==========================
//�`�揈��
//==========================
void CBlockAlly::Draw()
{
	//�`�揈��
	CObjectX::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CBlockAlly* CBlockAlly::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move)
{
	//�C���X�^���X����
	CBlockAlly* pBlockAlly = DBG_NEW CBlockAlly;

	//�ʒu�̐ݒ�
	pBlockAlly->SetPos(pos);

	//�X�P�[���̐ݒ�
	pBlockAlly->SetScale(scale);

	pBlockAlly->SetMove(move);

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

//===========================================================================================================
// �����������̏���
//===========================================================================================================
void CBlockAlly::Hit()
{
	//�����蔻��̏����擾
	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	//�����̔���
	bool collision = pCollision->RectangleLeft(m_ball->GetPosOld(), m_ball->GetPos(), GetPos(),
		m_ball->GetVtxMax(), m_ball->GetVtxMin(), GetVtxMax(), GetVtxMin());

	if (collision)
	{
		m_ball->SetMove({ -m_ball->GetMove().x, m_ball->GetMove().y, m_ball->GetMove().z });
		Uninit();
		return;
	}

	//�E���̔���
	collision = pCollision->RectangleRight(m_ball->GetPosOld(), m_ball->GetPos(), GetPos(),
		m_ball->GetVtxMax(), m_ball->GetVtxMin(), GetVtxMax(), GetVtxMin());

	if (collision)
	{
		m_ball->SetMove({ -m_ball->GetMove().x, m_ball->GetMove().y, m_ball->GetMove().z });
		Uninit();
		return;
	}

	//��̔���
	collision = pCollision->RectangleFront(m_ball->GetPosOld(), m_ball->GetPos(), GetPos(),
		m_ball->GetVtxMax(), m_ball->GetVtxMin(), GetVtxMax(), GetVtxMin());

	if (collision)
	{
		m_ball->SetMove({ m_ball->GetMove().x, -m_ball->GetMove().y, m_ball->GetMove().z });
		Uninit();
		return;
	}

	//���̔���
	collision = pCollision->RectangletBack(m_ball->GetPosOld(), m_ball->GetPos(), GetPos(),
		m_ball->GetVtxMax(), m_ball->GetVtxMin(), GetVtxMax(), GetVtxMin());

	if (collision)
	{
		m_ball->SetMove({ m_ball->GetMove().x, -m_ball->GetMove().y, m_ball->GetMove().z });
		Uninit();
		return;
	}
}

//===========================================================================================================
// �{�[���̏����擾
//===========================================================================================================
void CBlockAlly::GetBallInfo()
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