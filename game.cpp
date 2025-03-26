//==========================
// 
// ゲーム画面の処理[game.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"game.h"
#include"manager.h"
#include"block.h"
#include "wall.h"
//==========================
// コンストラクタ
//==========================
CGame::CGame()
{

}

//==========================
// デストラクタ
//==========================
CGame::~CGame()
{

}

//==========================
// 初期設定
//==========================
HRESULT CGame::Init()
{
	CBlock::Create({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f });

	{// 壁配置
		CWall::Create({ -100.0f,-100.0f,0.0f }, { 1.0f,13.0f,1.0f });	// 左壁
		CWall::Create({ 100.0f,-100.0f,0.0f }, { 1.0f,13.0f,1.0f });	// 右壁
		CWall::Create({ 0.0f,150.0f,0.0f }, { 11.0f,1.0f,1.0f });	// 上壁
		CWall::Create({ 0.0f,-150.0f,0.0f }, { 11.0f,1.0f,1.0f });	// 下壁
	}
	

	return S_OK;
}

//==========================
// 終了処理
//==========================
void CGame::Uninit()
{
	CObject::ReleaseAll();
}

//==========================
// 更新処理
//==========================
void CGame::Update()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{//ゲーム画面に遷移
		CManager::GetInstance()->GetFade()->SetFade(RESULT);
	}
}

//==========================
// 描画処理
//==========================
void CGame::Draw()
{

}