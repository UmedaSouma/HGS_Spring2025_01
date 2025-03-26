//==========================
// 
// ゲーム画面の処理[game.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"game_test_01.h"
#include"manager.h"
#include"block.h"
#include "wall.h"
#include"ball.h"
#include "player.h"
#include "block_enemy.h"

//==========================
// コンストラクタ
//==========================
CGameTest01::CGameTest01()
{

}

//==========================
// デストラクタ
//==========================
CGameTest01::~CGameTest01()
{

}

//==========================
// 初期設定
//==========================
HRESULT CGameTest01::Init()
{
	float UnderOrigin = 180.0f;
	float SideOrigin = 300.0f;
	float VarticalScale = 17.0f;

	CPlayer::Create({ 0.0f,0.0f,0.0f });

	CBlockEnemy::Create({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f });

	CBall::Create({ 0.0f,-50.0f,0.0f }, { 1.0f,1.0f,1.0f });

	{// 壁配置
		CWall::Create({ -SideOrigin,-UnderOrigin,0.0f }, { 1.0f,VarticalScale,1.0f });	// 左壁
		CWall::Create({ SideOrigin,-UnderOrigin,0.0f }, { 1.0f,VarticalScale,1.0f });	// 右壁

		CWall::Create({ 0.0f,150,0.0f }, { 31.0f,1.0f,1.0f });		// 上壁
		CWall::Create({ 0.0f,-UnderOrigin,0.0f }, { 31.0f,1.0f,1.0f });		// 下壁
	}


	return S_OK;
}

//==========================
// 終了処理
//==========================
void CGameTest01::Uninit()
{
	CObject::ReleaseAll();
}

//==========================
// 更新処理
//==========================
void CGameTest01::Update()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{//ゲーム画面に遷移
		CManager::GetInstance()->GetFade()->SetFade(RESULT);
	}
}

//==========================
// 描画処理
//==========================
void CGameTest01::Draw()
{

}