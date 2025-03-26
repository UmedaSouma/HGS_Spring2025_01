//==========================
// 
// �^�C�g����ʂ̏���[taitle.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"title.h"
#include"manager.h"
#include"bg.h"
//==========================
// �R���X�g���N�^
//==========================
CTitle::CTitle()
{

}

//==========================
// �f�X�g���N�^
//==========================
CTitle::~CTitle()
{

}

//==========================
// �����ݒ�
//==========================
HRESULT CTitle::Init()
{
	CBg::Create("data\\TEXTURE\\title.png");

	return S_OK;

}

//==========================
// �I������
//==========================
void CTitle::Uninit()
{
	CObject::ReleaseAll();
}

//==========================
// �X�V����
//==========================
void CTitle::Update()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{//�Q�[����ʂɑJ��
		CManager::GetInstance()->GetFade()->SetFade(GAME);
	}
}

//==========================
// �`�揈��
//==========================
void CTitle::Draw()
{

}