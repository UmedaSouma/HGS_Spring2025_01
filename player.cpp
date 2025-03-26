//==========================
// 
// �v���C���[����[player.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "player.h"
#include"manager.h"

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

void CPlayer::Operation()
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