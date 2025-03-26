//==========================
// 
// �V�[���Ǘ�[scene.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"scene.h"
#include"title.h"
#include"game.h"
#include "game_test_01.h"
#include"result.h"

//==========================
// �R���X�g���N�^
//==========================
CScene::CScene()
{
	m_mode = TITLE;
}

//==========================
// �f�X�g���N�^
//==========================
CScene::~CScene()
{
	
}

//==========================
// �����ݒ�
//==========================
HRESULT CScene::Init()
{
	return S_OK;

}

//==========================
// �I������
//==========================
void CScene::Uninit()
{

}

//==========================
// �X�V����
//==========================
void CScene::Update()
{

}

//==========================
// �`�揈��
//==========================
void CScene::Draw()
{

}

//==========================
// ��������
//==========================
CScene* CScene::Create(MODE mode)
{
	CScene* pScene = nullptr;

	switch (mode)
	{
	case TITLE:
		pScene = DBG_NEW CTitle;
		break;

	case GAME:
		pScene = DBG_NEW CGame;
		break;

	case GAME_TEST_01:
		pScene = DBG_NEW CGameTest01;
		break;

	case RESULT:
		pScene = DBG_NEW CResult;
		break;

	default:
		break;
	}

	pScene->m_mode = mode;

	return pScene;
}

//==========================
//���݂̃V�[�����擾
//==========================
CScene::MODE CScene::GetScene()
{
	return m_mode;
}