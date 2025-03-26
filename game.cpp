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