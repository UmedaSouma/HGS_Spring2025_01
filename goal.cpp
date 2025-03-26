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
	m_nModelIdx(0)//���f���̔ԍ�
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
	//�T�C�Y�ݒ�
	//SetSize();

	//�����ݒ�
	CObjectX::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CGoal::Uninit()
{
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

	return pGoal;
}