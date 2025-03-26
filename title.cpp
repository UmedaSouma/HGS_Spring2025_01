//==========================
// 
// タイトル画面の処理[taitle.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"title.h"
#include"manager.h"
#include"bg.h"
//==========================
// コンストラクタ
//==========================
CTitle::CTitle()
{

}

//==========================
// デストラクタ
//==========================
CTitle::~CTitle()
{

}

//==========================
// 初期設定
//==========================
HRESULT CTitle::Init()
{
	CBg::Create("data\\TEXTURE\\title.png");

	return S_OK;

}

//==========================
// 終了処理
//==========================
void CTitle::Uninit()
{
	CObject::ReleaseAll();
}

//==========================
// 更新処理
//==========================
void CTitle::Update()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{//ゲーム画面に遷移
		CManager::GetInstance()->GetFade()->SetFade(GAME);
	}
}

//==========================
// 描画処理
//==========================
void CTitle::Draw()
{

}