//==========================
// 
// [result.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"gamemanager.h"

//==========================
//�R���X�g���N�^
//==========================
CGameManager::CGameManager() :
	m_End(false),
	m_Game(false),
	m_start(false)
{

}

//==========================
//�f�X�g���N�^
//==========================
CGameManager::~CGameManager()
{

}

//==========================
//�N���A������擾
//==========================
bool CGameManager::GetGame()
{
	return m_Game;
}

//==========================
//�N���A�����ݒ�
//==========================
void CGameManager::SetGame()
{
	m_Game = true;
}

//==========================
//�I��������擾
//==========================
bool CGameManager::GetEnd()
{
	return m_End;
}

//==========================
//�I�������ݒ�
//==========================
void CGameManager::SetEnd()
{
	m_End = true;
}

//==========================
//�J�n������擾
//==========================
bool CGameManager::GetStart()
{
	return m_start;
}

//==========================
//�J�n�����ݒ�
//==========================
void CGameManager::SetStart()
{
	m_start = true;
}

//==========================
//��񃊃Z�b�g
//==========================
void CGameManager::reset()
{
	m_End = false;
	m_Game = false;
	m_start = false;
}