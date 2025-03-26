//==========================
// 
// プレイヤー処理[player.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "player.h"
#include"manager.h"
#include "input.h"
#include "bullet.h"

//
CPlayerposUI* CPlayer::PUI = nullptr;

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

	PUI = CPlayerposUI::Create({ 0.0f,0.0f,0.0f }, { 10.0f,10.0f,1.0f });

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
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();

	PUI->SetPos({ pos.x,pos.y,-50.0f });

	Operation();

	pos += move;
	SetPos(pos);

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

//===========================================================================================================
// 操作
//===========================================================================================================
void CPlayer::Operation()
{
	OpeMove();

	OpeBullet();
}

//===========================================================================================================
// 移動操作
//===========================================================================================================
void CPlayer::OpeMove()
{
	CInputKeyboard* keyboard = CManager::GetInstance()->GetKeyboard();
	CInputJoypad* joypad = CManager::GetInstance()->GetJoypad();
	float MOVE_PLAYER = 2.0f;
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };

	// 移動処理
	if (keyboard->GetPress(DIK_A) == true || joypad->GetPress(CInputJoypad::JOYKEY_LEFT) == true)
	{// Aキーが押された

		if (keyboard->GetPress(DIK_S) == true || joypad->GetPress(CInputJoypad::JOYKEY_UP) == true)
		{
			move.x += sinf(-D3DX_PI * 0.75f) * MOVE_PLAYER;
			move.y += cosf(-D3DX_PI * 0.75f) * MOVE_PLAYER;
		}
		else if (keyboard->GetPress(DIK_W) == true || joypad->GetPress(CInputJoypad::JOYKEY_DOWN) == true)
		{
			move.x += sinf(-D3DX_PI * 0.25f) * MOVE_PLAYER;
			move.y += cosf(D3DX_PI * 0.25f) * MOVE_PLAYER;
		}
		else if (keyboard->GetPress(DIK_A) == true || joypad->GetPress(CInputJoypad::JOYKEY_LEFT) == true)
		{
			move.x += sinf(-D3DX_PI * 0.5f) * MOVE_PLAYER;
			move.y += cosf(-D3DX_PI * 0.5f) * MOVE_PLAYER;
		}


	}
	else if (keyboard->GetPress(DIK_D) == true || joypad->GetPress(CInputJoypad::JOYKEY_RIGHT) == true)
	{// Dキーが押された

		if (keyboard->GetPress(DIK_W) == true || joypad->GetPress(CInputJoypad::JOYKEY_DOWN) == true)
		{// Sキーが押された
			// 右下移動
			move.x += sinf(D3DX_PI * 0.25f) * MOVE_PLAYER;
			move.y += cosf(D3DX_PI * 0.25f) * MOVE_PLAYER;

		}
		else if (keyboard->GetPress(DIK_S) == true || joypad->GetPress(CInputJoypad::JOYKEY_UP) == true)
		{// Wキーが押された

			move.x += sinf(D3DX_PI * 0.75f) * MOVE_PLAYER;
			move.y += cosf(-D3DX_PI * 0.75f) * MOVE_PLAYER;

		}
		else if (keyboard->GetPress(DIK_D) == true || joypad->GetPress(CInputJoypad::JOYKEY_RIGHT) == true)
		{
			move.x += sinf(D3DX_PI * 0.5f) * MOVE_PLAYER;
			move.y += cosf(D3DX_PI * 0.5f) * MOVE_PLAYER;

		}
	}
	else if (keyboard->GetPress(DIK_S) == true || joypad->GetPress(CInputJoypad::JOYKEY_UP) == true)
	{// Wキーが押された
		move.x += sinf(D3DX_PI * 1) * MOVE_PLAYER;
		move.y += cosf(D3DX_PI * 1) * MOVE_PLAYER;
	}
	else if (keyboard->GetPress(DIK_W) == true || joypad->GetPress(CInputJoypad::JOYKEY_DOWN) == true)
	{// Sキーが押された
		move.x += sinf(D3DX_PI * 0) * MOVE_PLAYER;
		move.y += cosf(D3DX_PI * 0) * MOVE_PLAYER;

	}

	SetMove(move);
}

//===========================================================================================================
// 鬱操作
//===========================================================================================================
void CPlayer::OpeBullet()
{
	CInputKeyboard* keyboard = CManager::GetInstance()->GetKeyboard();
	CInputJoypad* joypad = CManager::GetInstance()->GetJoypad();

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 BMove = { 0.0f,0.0f,3.0f };

	if (keyboard->GetTrigger(DIK_SPACE) || joypad->GetTrigger(CInputJoypad::JOYKEY_X))
	{
		CBullet::Create(pos, { 1.0f,1.0f,1.0f }, BMove);
	}
}

//==========================
//オブジェクト生成
//==========================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	//インスタンス生成
	CPlayer* pPlayer = DBG_NEW CPlayer;

	pos.z -= 500.0f;

	//位置の設定
	pPlayer->SetPos(pos);

	//初期化処理
	pPlayer->Init();

	return pPlayer;
}