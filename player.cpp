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
	//�����ݒ�
	CObjectgame::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CPlayer::Uninit()
{
	//�I������
	CObjectgame::Uninit();
}

//==========================
//�X�V����
//==========================
void CPlayer::Update()
{
	Operation();

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
	float MOVE_PLAYER = 1.0f;
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };

	// �ړ�����
	if (keyboard->GetPress(DIK_A) == true || joypad->GetPress(CInputJoypad::JOYKEY_LEFT) == true)
	{// A�L�[�������ꂽ

		if (keyboard->GetPress(DIK_W) == true || joypad->GetPress(CInputJoypad::JOYKEY_UP) == true)
		{
			move.x += sinf(-D3DX_PI * 0.75f) * MOVE_PLAYER;
			move.y += cosf(-D3DX_PI * 0.75f) * MOVE_PLAYER;
		}
		else if (keyboard->GetPress(DIK_S) == true || joypad->GetPress(CInputJoypad::JOYKEY_DOWN) == true)
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

		if (keyboard->GetPress(DIK_S) == true || joypad->GetPress(CInputJoypad::JOYKEY_DOWN) == true)
		{// S�L�[�������ꂽ
			// �E���ړ�
			move.x += sinf(D3DX_PI * 0.25f) * MOVE_PLAYER;
			move.y += cosf(D3DX_PI * 0.25f) * MOVE_PLAYER;

		}
		else if (keyboard->GetPress(DIK_W) == true || joypad->GetPress(CInputJoypad::JOYKEY_UP) == true)
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
	else if (keyboard->GetPress(DIK_W) == true || joypad->GetPress(CInputJoypad::JOYKEY_UP) == true)
	{// W�L�[�������ꂽ
		move.x += sinf(D3DX_PI * 1) * MOVE_PLAYER;
		move.y += cosf(D3DX_PI * 1) * MOVE_PLAYER;
	}
	else if (keyboard->GetPress(DIK_S) == true || joypad->GetPress(CInputJoypad::JOYKEY_DOWN) == true)
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

}

//==========================
//�I�u�W�F�N�g����
//==========================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	//�C���X�^���X����
	CPlayer* pPlayer = DBG_NEW CPlayer;

	//�ʒu�̐ݒ�
	pPlayer->SetPos(pos);

	//����������
	pPlayer->Init();

	return pPlayer;
}