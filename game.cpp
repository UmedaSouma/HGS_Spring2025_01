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
#include"wall.h"
#include"ball.h"
#include"block_ally.h"
#include"clear.h"
#include"GameOver.h"
#include"goal.h"
#include "player.h"

CCreateBlock* CGame::m_pCreteBlock = nullptr;
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
	CManager::GetInstance()->GetGameManager()->reset();

	float UnderOrigin = 180.0f;
	float SideOrigin = 300.0f;
	float VarticalScale = 17.0f;

	CPlayer::Create({ 0.0f,0.0f,0.0f });

	CBall::Create({ -150.0f,-50.0f,0.0f }, { 1.0f,1.0f,1.0f });

	CBlockAlly::Create({ 0.0f,0.0f,0.0f }, { 5.0f,5.0f,5.0f });

	if (m_pCreteBlock == nullptr)
	{
		m_pCreteBlock = DBG_NEW CCreateBlock;
		m_pCreteBlock->Init();
	}

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
void CGame::Uninit()
{
	if (m_pCreteBlock != nullptr)
	{
		delete m_pCreteBlock;
		m_pCreteBlock = nullptr;
	}

	CObject::ReleaseAll();
}

//==========================
// 更新処理
//==========================
void CGame::Update()
{
	Start();

	if (!CManager::GetInstance()->GetGameManager()->GetEnd())
	{
		return;
	}

	if (m_pCreteBlock != nullptr)
	{
		m_pCreteBlock->Update();
	}

	if (CManager::GetInstance()->GetGameManager()->GetGame())
	{//クリアしてるとき
		CClear::Create({ 640.0f, 300.0f, 0.0f });
	}
	else if (!CManager::GetInstance()->GetGameManager()->GetGame())
	{//クリアしていない
		COver::Create({ 640.0f, 300.0f, 0.0f });
	}

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{//ゲーム画面に遷移
		CManager::GetInstance()->GetFade()->SetFade(TITLE);
	}
}

//==========================
// 描画処理
//==========================
void CGame::Draw()
{

}

//==========================
// 描画処理
//==========================
void CGame::Start()
{
	if (CManager::GetInstance()->GetGameManager()->GetStart())
	{//開始している
		return;
	}

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{//エンターキーがおされた
		CManager::GetInstance()->GetGameManager()->SetStart();
	}
}