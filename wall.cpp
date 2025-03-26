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
	m_nModelIdx(0)//���f���̔ԍ�
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
	//�T�C�Y�ݒ�
	//SetSize();

	//�����ݒ�
	CObjectX::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CWall::Uninit()
{
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