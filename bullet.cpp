//==========================
// 
// �u���b�N���󂷒e[bullet.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "bullet.h"
#include "manager.h"
#include "model.h"

//�ÓI�����o������
const int CBullet::PRIORITY = 1;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CBullet::CBullet(int nPriority) :
	CObjectX(nPriority),//���R���X�g���N�^
	m_nModelIdx(0)//���f���̔ԍ�
{

}

//==========================
//�f�X�g���N�^
//==========================
CBullet::~CBullet()
{

}

//==========================
//����������
//==========================
HRESULT CBullet::Init()
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
void  CBullet::Uninit()
{
	//�I������
	CObjectX::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CBullet::Update()
{
	//�X�V����
	CObjectX::Update();
}

//==========================
//�`�揈��
//==========================
void CBullet::Draw()
{
	//�`�揈��
	CObjectX::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�C���X�^���X����
	CBullet* pBullet = DBG_NEW CBullet;

	//�ʒu�̐ݒ�
	pBullet->SetPos(pos);

	//�X�P�[���̐ݒ�
	pBullet->SetScale(scale);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBullet->m_nModelIdx = pModel->Regist("data\\MODEL\\soil.x");
	pBullet->BindModel(pModel->GetMeshAdress(pBullet->m_nModelIdx),
		pModel->GetBuffMatAdress(pBullet->m_nModelIdx),
		pModel->GetNumMatAdress(pBullet->m_nModelIdx),
		pModel->GetTexIdx(pBullet->m_nModelIdx));

	//����������
	pBullet->Init();

	return pBullet;
}