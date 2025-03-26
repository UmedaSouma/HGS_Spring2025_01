//==========================
// 
// プレイヤー処理[player.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "player.h"
#include"manager.h"

//==========================
//コンストラクタ
//==========================
CPlayer::CPlayer(int nPriority):
	CObjectgame(nPriority)//基底コンストラクタ
{

}

//==========================
//デストラクタ
//==========================
CPlayer::~CPlayer()
{

}

//==========================
//初期化処理
//==========================
HRESULT CPlayer::Init()
{
	//初期設定
	CObjectgame::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CPlayer::Uninit()
{
	//終了処理
	CObjectgame::Uninit();
}

//==========================
//更新処理
//==========================
void CPlayer::Update()
{
	//更新処理
	CObjectgame::Update();
}

//==========================
//描画処理
//==========================
void CPlayer::Draw()
{
	//描画処理
	CObjectgame::Draw();
}

void CPlayer::Operation()
{

}

//==========================
//オブジェクト生成
//==========================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	//インスタンス生成
	CPlayer* pPlayer = DBG_NEW CPlayer;

	//位置の設定
	pPlayer->SetPos(pos);

	//初期化処理
	pPlayer->Init();

	return pPlayer;
}