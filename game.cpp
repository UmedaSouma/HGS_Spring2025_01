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
#include"wall.h"
#include"ball.h"
#include"block_ally.h"
#include"clear.h"
#include"GameOver.h"
#include"goal.h"
#include "player.h"

CCreateBlock* CGame::m_pCreteBlock = nullptr;
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
	CManager::GetInstance()->GetGameManager()->reset();

	float UnderOrigin = 180.0f;
	float SideOrigin = 300.0f;
	float VarticalScale = 17.0f;

	CPlayer::Create({ 0.0f,0.0f,0.0f });

	CBall::Create({ -150.0f,-50.0f,0.0f }, { 1.0f,1.0f,1.0f });

	CBlockAlly::Create({ 0.0f,0.0f,0.0f }, { 5.0f,5.0f,5.0f });

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
void CGame::Uninit()
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
void CGame::Update()
{
	Start();

	if (!CManager::GetInstance()->GetGameManager()->GetEnd())
	{
		return;
	}

	if (m_pCreteBlock != nullptr)
	{
		m_pCreteBlock->Update();
	}

	if (CManager::GetInstance()->GetGameManager()->GetGame())
	{//�N���A���Ă�Ƃ�
		CClear::Create({ 640.0f, 300.0f, 0.0f });
	}
	else if (!CManager::GetInstance()->GetGameManager()->GetGame())
	{//�N���A���Ă��Ȃ�
		COver::Create({ 640.0f, 300.0f, 0.0f });
	}

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{//�Q�[����ʂɑJ��
		CManager::GetInstance()->GetFade()->SetFade(TITLE);
	}
}

//==========================
// �`�揈��
//==========================
void CGame::Draw()
{

}

//==========================
// �`�揈��
//==========================
void CGame::Start()
{
	if (CManager::GetInstance()->GetGameManager()->GetStart())
	{//�J�n���Ă���
		return;
	}

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{//�G���^�[�L�[�������ꂽ
		CManager::GetInstance()->GetGameManager()->SetStart();
	}
}