//==========================
// 
// リザルト画面の処理[result.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"result.h"
#include"manager.h"
#include"bg.h"
//==========================
// コンストラクタ
//==========================
CResult::CResult()
{
	
}

//==========================
// デストラクタ
//==========================
CResult::~CResult()
{

}

//==========================
// 初期設定
//==========================
HRESULT CResult::Init()
{
	CBg::Create("data\\TEXTURE\\Resurt.png");

	return S_OK;
}

//==========================
// 終了処理
//==========================
void CResult::Uninit()
{
	CObject::ReleaseAll();
}

//==========================
// 更新処理
//==========================
void CResult::Update()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{//タイトル画面に遷移
		CManager::GetInstance()->GetFade()->SetFade(TITLE);
	}
}

//==========================
// 描画処理
//==========================
void CResult::Draw()
{

}