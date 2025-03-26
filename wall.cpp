//==========================
// 
// ��[wall.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "wall.h"
#include "manager.h"
#include "model.h"

//�ÓI�����o������
const int CWall::PRIORITY = 1;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CWall::CWall(int nPriority) :
	CObjectX(nPriority),//���R���X�g���N�^
	m_nModelIdx(0),//���f���̔ԍ�
	m_ball(nullptr)
{

}

//==========================
//�f�X�g���N�^
//==========================
CWall::~CWall()
{

}

//==========================
//����������
//==========================
HRESULT CWall::Init()
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
void  CWall::Uninit()
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
void CWall::Update()
{
	//�X�V����
	CObjectX::Update();

	Hit();
}

//==========================
//�`�揈��
//==========================
void CWall::Draw()
{
	//�`�揈��
	CObjectX::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CWall* CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CWall* pWall = DBG_NEW CWall;

	//�ʒu�̐ݒ�
	pWall->SetPos(pos);

	//�X�P�[���̐ݒ�
	pWall->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pWall->m_nModelIdx = pModel->Regist("data\\MODEL\\wall.x");
	pWall->BindModel(pModel->GetMeshAdress(pWall->m_nModelIdx),
		pModel->GetBuffMatAdress(pWall->m_nModelIdx),
		pModel->GetNumMatAdress(pWall->m_nModelIdx),
		pModel->GetTexIdx(pWall->m_nModelIdx));

	//����������
	pWall->Init();

	return pWall;
}

//==========================
//�����蔻��
//==========================
void CWall::Hit()
{
	//�����蔻��̏����擾
	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	//�����̔���
	bool collision = pCollision->RectangleLeft(m_ball->GetPosOld(), m_ball->GetPos(), GetPos(),
		m_ball->GetVtxMax(), m_ball->GetVtxMin(), GetVtxMax(), GetVtxMin());

	if (collision)
	{
		m_ball->SetMove({ -m_ball->GetMove().x, m_ball->GetMove().y, m_ball->GetMove().z });
		return;
	}

	//�E���̔���
	collision = pCollision->RectangleRight(m_ball->GetPosOld(), m_ball->GetPos(), GetPos(),
		m_ball->GetVtxMax(), m_ball->GetVtxMin(), GetVtxMax(), GetVtxMin());

	if (collision)
	{
		m_ball->SetMove({ -m_ball->GetMove().x, m_ball->GetMove().y, m_ball->GetMove().z });
		return;
	}

	//��̔���
	collision = pCollision->RectangleFront(m_ball->GetPosOld(), m_ball->GetPos(), GetPos(),
		m_ball->GetVtxMax(), m_ball->GetVtxMin(), GetVtxMax(), GetVtxMin());

	if (collision)
	{
		m_ball->SetMove({ m_ball->GetMove().x, -m_ball->GetMove().y, m_ball->GetMove().z });
		return;
	}

	//���̔���
	collision = pCollision->RectangletBack(m_ball->GetPosOld(), m_ball->GetPos(), GetPos(),
		m_ball->GetVtxMax(), m_ball->GetVtxMin(), GetVtxMax(), GetVtxMin());

	if (collision)
	{
		m_ball->SetMove({ m_ball->GetMove().x, -m_ball->GetMove().y, m_ball->GetMove().z });
		return;
	}
}

//==========================
//�{�[���̏����擾
//==========================
void CWall::GetBallInfo()
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