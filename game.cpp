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
#include "wall.h"
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

	{// �ǔz�u
		CWall::Create({ -100.0f,-100.0f,0.0f }, { 1.0f,13.0f,1.0f });	// ����
		CWall::Create({ 100.0f,-100.0f,0.0f }, { 1.0f,13.0f,1.0f });	// �E��
		CWall::Create({ 0.0f,150.0f,0.0f }, { 11.0f,1.0f,1.0f });	// ���
		CWall::Create({ 0.0f,-150.0f,0.0f }, { 11.0f,1.0f,1.0f });	// ����
	}
	

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