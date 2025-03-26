//==========================
// 
// [result.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"gamemanager.h"

//==========================
//コンストラクタ
//==========================
CGameManager::CGameManager() :
	m_End(false),
	m_Game(false),
	m_start(false)
{

}

//==========================
//デストラクタ
//==========================
CGameManager::~CGameManager()
{

}

//==========================
//クリア判定を取得
//==========================
bool CGameManager::GetGame()
{
	return m_Game;
}

//==========================
//クリア判定を設定
//==========================
void CGameManager::SetGame()
{
	m_Game = true;
}

//==========================
//終了判定を取得
//==========================
bool CGameManager::GetEnd()
{
	return m_End;
}

//==========================
//終了判定を設定
//==========================
void CGameManager::SetEnd()
{
	m_End = true;
}

//==========================
//開始判定を取得
//==========================
bool CGameManager::GetStart()
{
	return m_start;
}

//==========================
//開始判定を設定
//==========================
void CGameManager::SetStart()
{
	m_start = true;
}

//==========================
//情報リセット
//==========================
void CGameManager::reset()
{
	m_End = false;
	m_Game = false;
	m_start = false;
}