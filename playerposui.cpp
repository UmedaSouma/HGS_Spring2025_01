//==========================
// 
// プレイヤーの位置[playerposui.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "playerposui.h"
#include "manager.h"
#include "texture.h"

//静的メンバ初期化
const int CPlayerposUI::PRIORITY = 0;//描画順

//==========================
//コンストラクタ
//==========================
CPlayerposUI::CPlayerposUI(int nPriority) :CObject3D(nPriority), m_nTexIdx(0)
{

}

//==========================
//デストラクタ
//==========================
CPlayerposUI::~CPlayerposUI()
{

}

//==========================
//初期化処理
//==========================
HRESULT CPlayerposUI::Init()
{
	//初期設定
	CObject3D::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void CPlayerposUI::Uninit()
{
	//終了処理
	CObject3D::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CPlayerposUI::Update()
{
	//更新処理
	CObject3D::Update();
}

//==========================
//描画処理
//==========================
void CPlayerposUI::Draw()
{
	//描画処理
	CObject3D::Draw();
}

//==========================
//オブジェクト生成
//==========================
CPlayerposUI* CPlayerposUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンス生成
	CPlayerposUI* pPlayerposUI = DBG_NEW CPlayerposUI;

	//位置の設定
	pPlayerposUI->SetPos(pos);

	//大きさの設定
	pPlayerposUI->SetSize(size);

	pPlayerposUI->SetRot({ D3DX_PI,0.0f,0.0f });

	//初期化処理
	pPlayerposUI->Init();

	//テクスチャ設定
	/*CTexture* pTex = CManager::GetInstance()->GetTexture();
	pPlayerposUI->m_nTexIdx = pTex->Regist("data\\TEXTURE\\blood.png");
	pPlayerposUI->BindTexture(pTex->GetAdress(pPlayerposUI->m_nTexIdx));*/

	return pPlayerposUI;
}