//==========================
// 
// �S�[��[goal.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "goal.h"
#include "manager.h"
#include "model.h"

//�ÓI�����o������
const int CGoal::PRIORITY = 1;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CGoal::CGoal(int nPriority) :
	CObjectX(nPriority),//���R���X�g���N�^
	m_nModelIdx(0),//���f���̔ԍ�
	m_ball(nullptr)//�{�[���̏��
{

}

//==========================
//�f�X�g���N�^
//==========================
CGoal::~CGoal()
{

}

//==========================
//����������
//==========================
HRESULT CGoal::Init()
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
void  CGoal::Uninit()
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
void CGoal::Update()
{
	//�X�V����
	CObjectX::Update();

	hit();
}

//==========================
//�`�揈��
//==========================
void CGoal::Draw()
{
	//�`�揈��
	CObjectX::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CGoal* CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CGoal* pGoal = DBG_NEW CGoal;

	//�ʒu�̐ݒ�
	pGoal->SetPos(pos);

	//�X�P�[���̐ݒ�
	pGoal->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pGoal->m_nModelIdx = pModel->Regist("data\\MODEL\\goal.x");
	pGoal->BindModel(pModel->GetMeshAdress(pGoal->m_nModelIdx),
		pModel->GetBuffMatAdress(pGoal->m_nModelIdx),
		pModel->GetNumMatAdress(pGoal->m_nModelIdx),
		pModel->GetTexIdx(pGoal->m_nModelIdx));

	//����������
	pGoal->Init();

	//�^�C�v�ݒ�
	pGoal->SetType(TYPE::GOAL);

	return pGoal;
}

//==========================
//�����蔻��
//==========================
void CGoal::hit()
{
	if (m_ball->GetPos().x <= GetPos().x + GetVtxMax().x
		&& m_ball->GetPos().x > GetPos().x + GetVtxMin().x
		&& m_ball->GetPos().y  < GetPos().y + GetVtxMax().y
		&& m_ball->GetPos().y  > GetPos().y + GetVtxMin().y)
	{
		m_ball->Uninit();//�{�[��������

		CManager::GetInstance()->GetGameManager()->SetEnd();
		CManager::GetInstance()->GetGameManager()->SetGame();

	}
}

//==========================
//�{�[���̏����擾
//==========================
void CGoal::GetBallInfo()
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