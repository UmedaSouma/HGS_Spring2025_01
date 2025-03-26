//==========================
// 
// �Q�[����ʂ̏���[game.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"game.h"
#include"manager.h"
#include"block.h"
//==========================
// �R���X�g���N�^
//==========================
CGame::CGame()
{

}

//==========================
// �f�X�g���N�^
//==========================
CGame::~CGame()
{

}

//==========================
// �����ݒ�
//==========================
HRESULT CGame::Init()
{
	CBlock::Create({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f });

	return S_OK;
}

//==========================
// �I������
//==========================
void CGame::Uninit()
{
	CObject::ReleaseAll();
}

//==========================
// �X�V����
//==========================
void CGame::Update()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{//�Q�[����ʂɑJ��
		CManager::GetInstance()->GetFade()->SetFade(RESULT);
	}
}

//==========================
// �`�揈��
//==========================
void CGame::Draw()
{

}