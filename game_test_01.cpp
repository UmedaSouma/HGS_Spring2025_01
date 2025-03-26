//==========================
// 
// �Q�[����ʂ̏���[game.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"game_test_01.h"
#include"manager.h"
#include"block.h"
#include "wall.h"
#include"ball.h"
#include "player.h"
#include "block_enemy.h"


CCreateBlock* CGameTest01::m_pCreteBlock = nullptr;
//==========================
// �R���X�g���N�^
//==========================
CGameTest01::CGameTest01()
{

}

//==========================
// �f�X�g���N�^
//==========================
CGameTest01::~CGameTest01()
{

}

//==========================
// �����ݒ�
//==========================
HRESULT CGameTest01::Init()
{


	float UnderOrigin = 180.0f;
	float SideOrigin = 300.0f;
	float VarticalScale = 17.0f;

	CPlayer::Create({ 0.0f,0.0f,0.0f });

	CBlockEnemy::Create({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f });

	CBall::Create({ 0.0f,-50.0f,0.0f }, { 1.0f,1.0f,1.0f });

	if (m_pCreteBlock == nullptr)
	{
		m_pCreteBlock = DBG_NEW CCreateBlock;
		m_pCreteBlock->Init();
	}

	{// �ǔz�u
		CWall::Create({ -SideOrigin,-UnderOrigin,0.0f }, { 1.0f,VarticalScale,1.0f });	// ����
		CWall::Create({ SideOrigin,-UnderOrigin,0.0f }, { 1.0f,VarticalScale,1.0f });	// �E��

		CWall::Create({ 0.0f,150,0.0f }, { 31.0f,1.0f,1.0f });		// ���
		CWall::Create({ 0.0f,-UnderOrigin,0.0f }, { 31.0f,1.0f,1.0f });		// ����
	}


	return S_OK;
}

//==========================
// �I������
//==========================
void CGameTest01::Uninit()
{
	if (m_pCreteBlock != nullptr)
	{
		delete m_pCreteBlock;
		m_pCreteBlock = nullptr;
	}

	CObject::ReleaseAll();
}

//==========================
// �X�V����
//==========================
void CGameTest01::Update()
{
	if (m_pCreteBlock != nullptr)
	{
		m_pCreteBlock->Update();
	}

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{//�Q�[����ʂɑJ��
		CManager::GetInstance()->GetFade()->SetFade(RESULT);
	}
}

//==========================
// �`�揈��
//==========================
void CGameTest01::Draw()
{

}