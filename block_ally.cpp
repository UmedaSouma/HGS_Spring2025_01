//==========================
// 
// 味方ブロック[block_ally.cpp]
// Author Soma Umeda
//
//==========================

//include
#include "block_ally.h"
#include "manager.h"
#include "model.h"

//静的メンバ初期化
const int CBlockAlly::PRIORITY = 1;//描画順

//==========================
//コンストラクタ
//==========================
CBlockAlly::CBlockAlly(int nPriority) :CBlock(nPriority), m_nModelIdx(0)
{

}

//==========================
//デストラクタ
//==========================
CBlockAlly::~CBlockAlly()
{

}

//==========================
//初期化処理
//==========================
HRESULT CBlockAlly::Init()
{
	//サイズ設定
	//SetSize();

	//初期設定
	CObjectX::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CBlockAlly::Uninit()
{
	//終了処理
	CObjectX::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CBlockAlly::Update()
{
	//更新処理
	CObjectX::Update();
}

//==========================
//描画処理
//==========================
void CBlockAlly::Draw()
{
	//描画処理
	CObjectX::Draw();
}

//===========================================================================================================
// 当たった時の処理
//===========================================================================================================
void CBlockAlly::Hit()
{
}

//==========================
//オブジェクト生成
//==========================
CBlockAlly* CBlockAlly::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CBlockAlly* pBlockAlly = DBG_NEW CBlockAlly;

	//位置の設定
	pBlockAlly->SetPos(pos);

	//スケールの設定
	pBlockAlly->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBlockAlly->m_nModelIdx = pModel->Regist("data\\MODEL\\soil.x");
	pBlockAlly->BindModel(pModel->GetMeshAdress(pBlockAlly->m_nModelIdx),
		pModel->GetBuffMatAdress(pBlockAlly->m_nModelIdx),
		pModel->GetNumMatAdress(pBlockAlly->m_nModelIdx),
		pModel->GetTexIdx(pBlockAlly->m_nModelIdx));

	//初期化処理
	pBlockAlly->Init();

	return pBlockAlly;
}