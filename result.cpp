//==========================
// 
// ���U���g��ʂ̏���[result.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"result.h"
#include"manager.h"
#include"bg.h"
//==========================
// �R���X�g���N�^
//==========================
CResult::CResult()
{
	
}

//==========================
// �f�X�g���N�^
//==========================
CResult::~CResult()
{

}

//==========================
// �����ݒ�
//==========================
HRESULT CResult::Init()
{
	CBg::Create("data\\TEXTURE\\Resurt.png");

	return S_OK;
}

//==========================
// �I������
//==========================
void CResult::Uninit()
{
	CObject::ReleaseAll();
}

//==========================
// �X�V����
//==========================
void CResult::Update()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{//�^�C�g����ʂɑJ��
		CManager::GetInstance()->GetFade()->SetFade(TITLE);
	}
}

//==========================
// �`�揈��
//==========================
void CResult::Draw()
{

}