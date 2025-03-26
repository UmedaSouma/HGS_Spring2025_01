//==========================
// 
// �v���C���[�̈ʒu[playerposui.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "playerposui.h"
#include "manager.h"
#include "texture.h"

//�ÓI�����o������
const int CPlayerposUI::PRIORITY = 0;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CPlayerposUI::CPlayerposUI(int nPriority) :CObject3D(nPriority), m_nTexIdx(0)
{

}

//==========================
//�f�X�g���N�^
//==========================
CPlayerposUI::~CPlayerposUI()
{

}

//==========================
//����������
//==========================
HRESULT CPlayerposUI::Init()
{
	//�����ݒ�
	CObject3D::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void CPlayerposUI::Uninit()
{
	//�I������
	CObject3D::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CPlayerposUI::Update()
{
	//�X�V����
	CObject3D::Update();
}

//==========================
//�`�揈��
//==========================
void CPlayerposUI::Draw()
{
	//�`�揈��
	CObject3D::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CPlayerposUI* CPlayerposUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X����
	CPlayerposUI* pPlayerposUI = DBG_NEW CPlayerposUI;

	//�ʒu�̐ݒ�
	pPlayerposUI->SetPos(pos);

	//�傫���̐ݒ�
	pPlayerposUI->SetSize(size);

	pPlayerposUI->SetRot({ D3DX_PI,0.0f,0.0f });

	//����������
	pPlayerposUI->Init();

	//�e�N�X�`���ݒ�
	/*CTexture* pTex = CManager::GetInstance()->GetTexture();
	pPlayerposUI->m_nTexIdx = pTex->Regist("data\\TEXTURE\\blood.png");
	pPlayerposUI->BindTexture(pTex->GetAdress(pPlayerposUI->m_nTexIdx));*/

	return pPlayerposUI;
}