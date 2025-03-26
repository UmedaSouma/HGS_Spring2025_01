//==========================
// 
// シーン管理[scene.cpp]
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
// コンストラクタ
//==========================
CScene::CScene()
{
	m_mode = TITLE;
}

//==========================
// デストラクタ
//==========================
CScene::~CScene()
{
	
}

//==========================
// 初期設定
//==========================
HRESULT CScene::Init()
{
	return S_OK;

}

//==========================
// 終了処理
//==========================
void CScene::Uninit()
{

}

//==========================
// 更新処理
//==========================
void CScene::Update()
{

}

//==========================
// 描画処理
//==========================
void CScene::Draw()
{

}

//==========================
// 生成処理
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
//現在のシーンを取得
//==========================
CScene::MODE CScene::GetScene()
{
	return m_mode;
}