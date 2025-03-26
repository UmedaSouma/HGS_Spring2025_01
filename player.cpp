//==========================
// 
// �v���C���[����[player.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "player.h"
#include"manager.h"
#include "input.h"
#include "bullet.h"
#include "block_ally.h"

//
CPlayerposUI* CPlayer::PUI = nullptr;
const int CPlayer::PRIORITY = 0;
//==========================
//�R���X�g���N�^
//==========================
CPlayer::CPlayer(int nPriority):
	CObjectgame(nPriority)//���R���X�g���N�^
{

}

//==========================
//�f�X�g���N�^
//==========================
CPlayer::~CPlayer()
{

}

//==========================
//����������
//==========================
HRESULT CPlayer::Init()
{
	CountBlock = 0;
	nBlock = 0;

	//�����ݒ�
	CObjectgame::Init();

	PUI = CPlayerposUI::Create({ 0.0f,0.0f,0.0f }, { 10.0f,10.0f,1.0f });

	return S_OK;
}

//==========================
//�I������
//==========================
void  CPlayer::Uninit()
{
	if (PUI != nullptr)
	{
		PUI = nullptr;
	}

	//�I������
	CObjectgame::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CPlayer::Update()
{

	if (!CManager::GetInstance()->GetGameManager()->GetStart())
	{//�J�n���Ă���
		return;
	}

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();

	if (PUI != nullptr)
	{
		PUI->SetPos({ pos.x,pos.y,-50.0f });
	}

	Operation();

	pos += move;
	SetPos(pos);

	//�X�V����
	CObjectgame::Update();
}

//==========================
//�`�揈��
//==========================
void CPlayer::Draw()
{
	//�`�揈��
	CObjectgame::Draw();
}

//===========================================================================================================
// ����
//===========================================================================================================
void CPlayer::Operation()
{
	OpeMove();

	OpeBullet();
}

//===========================================================================================================
// �ړ�����
//===========================================================================================================
void CPlayer::OpeMove()
{
	CInputKeyboard* keyboard = CManager::GetInstance()->GetKeyboard();
	CInputJoypad* joypad = CManager::GetInstance()->GetJoypad();
	float MOVE_PLAYER = 2.0f;
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };

	// �ړ�����
	if (keyboard->GetPress(DIK_A) == true || joypad->GetPress(CInputJoypad::JOYKEY_LEFT) == true)
	{// A�L�[�������ꂽ

		if (keyboard->GetPress(DIK_S) == true || joypad->GetPress(CInputJoypad::JOYKEY_UP) == true)
		{
			move.x += sinf(-D3DX_PI * 0.75f) * MOVE_PLAYER;
			move.y += cosf(-D3DX_PI * 0.75f) * MOVE_PLAYER;
		}
		else if (keyboard->GetPress(DIK_W) == true || joypad->GetPress(CInputJoypad::JOYKEY_DOWN) == true)
		{
			move.x += sinf(-D3DX_PI * 0.25f) * MOVE_PLAYER;
			move.y += cosf(D3DX_PI * 0.25f) * MOVE_PLAYER;
		}
		else if (keyboard->GetPress(DIK_A) == true || joypad->GetPress(CInputJoypad::JOYKEY_LEFT) == true)
		{
			move.x += sinf(-D3DX_PI * 0.5f) * MOVE_PLAYER;
			move.y += cosf(-D3DX_PI * 0.5f) * MOVE_PLAYER;
		}


	}
	else if (keyboard->GetPress(DIK_D) == true || joypad->GetPress(CInputJoypad::JOYKEY_RIGHT) == true)
	{// D�L�[�������ꂽ

		if (keyboard->GetPress(DIK_W) == true || joypad->GetPress(CInputJoypad::JOYKEY_DOWN) == true)
		{// S�L�[�������ꂽ
			// �E���ړ�
			move.x += sinf(D3DX_PI * 0.25f) * MOVE_PLAYER;
			move.y += cosf(D3DX_PI * 0.25f) * MOVE_PLAYER;

		}
		else if (keyboard->GetPress(DIK_S) == true || joypad->GetPress(CInputJoypad::JOYKEY_UP) == true)
		{// W�L�[�������ꂽ

			move.x += sinf(D3DX_PI * 0.75f) * MOVE_PLAYER;
			move.y += cosf(-D3DX_PI * 0.75f) * MOVE_PLAYER;

		}
		else if (keyboard->GetPress(DIK_D) == true || joypad->GetPress(CInputJoypad::JOYKEY_RIGHT) == true)
		{
			move.x += sinf(D3DX_PI * 0.5f) * MOVE_PLAYER;
			move.y += cosf(D3DX_PI * 0.5f) * MOVE_PLAYER;

		}
	}
	else if (keyboard->GetPress(DIK_S) == true || joypad->GetPress(CInputJoypad::JOYKEY_UP) == true)
	{// W�L�[�������ꂽ
		move.x += sinf(D3DX_PI * 1) * MOVE_PLAYER;
		move.y += cosf(D3DX_PI * 1) * MOVE_PLAYER;
	}
	else if (keyboard->GetPress(DIK_W) == true || joypad->GetPress(CInputJoypad::JOYKEY_DOWN) == true)
	{// S�L�[�������ꂽ
		move.x += sinf(D3DX_PI * 0) * MOVE_PLAYER;
		move.y += cosf(D3DX_PI * 0) * MOVE_PLAYER;

	}

	SetMove(move);
}

//===========================================================================================================
// �T����
//===========================================================================================================
void CPlayer::OpeBullet()
{
	CInputKeyboard* keyboard = CManager::GetInstance()->GetKeyboard();
	CInputJoypad* joypad = CManager::GetInstance()->GetJoypad();

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 BMove = { 0.0f,0.0f,15.0f };

	if (keyboard->GetTrigger(DIK_SPACE) || joypad->GetTrigger(CInputJoypad::JOYKEY_X))
	{
		CBullet::Create(pos, { 1.0f,1.0f,1.0f }, BMove);
	}

	if (keyboard->GetTrigger(DIK_N) || joypad->GetTrigger(CInputJoypad::JOYKEY_Y))
	{
		if (nBlock > 0)
		{
			D3DXVECTOR3 posA = pos;
			posA.y -= 20;
			CBlockAlly::Create(posA, { 2.0f,2.0f,1.0f }, BMove);
			nBlock--;
		}
	}
}

void CPlayer::CountBreak()
{
	CountBlock++;

	if (CountBlock >= 3)
	{
		nBlock++;
		CountBlock = 0;
	}
}

//==========================
//�I�u�W�F�N�g����
//==========================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	//�C���X�^���X����
	CPlayer* pPlayer = DBG_NEW CPlayer;

	pos.z -= 500.0f;

	//�ʒu�̐ݒ�
	pPlayer->SetPos(pos);

	pPlayer->SetType(CObject::PLAYER);

	//����������
	pPlayer->Init();

	return pPlayer;
}