//==========================
// 
// ボール[ball.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "ball.h"
#include "manager.h"
#include "model.h"

//静的メンバ初期化
const int CBall::PRIORITY = 1;//描画順

//==========================
//コンストラクタ
//==========================
CBall::CBall(int nPriority) :CObjectX(nPriority), m_nModelIdx(0)
{

}

//==========================
//デストラクタ
//==========================
CBall::~CBall()
{

}

//==========================
//初期化処理
//==========================
HRESULT CBall::Init()
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
void  CBall::Uninit()
{
	//終了処理
	CObjectX::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CBall::Update()
{
	//更新処理
	CObjectX::Update();
}

//==========================
//描画処理
//==========================
void CBall::Draw()
{
	//描画処理
	CObjectX::Draw();
}

//==========================
//オブジェクト生成
//==========================
CBall* CBall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CBall* pBall = DBG_NEW CBall;

	//位置の設定
	pBall->SetPos(pos);

	//スケールの設定
	pBall->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBall->m_nModelIdx = pModel->Regist("data\\MODEL\\ball.x");
	pBall->BindModel(pModel->GetMeshAdress(pBall->m_nModelIdx),
		pModel->GetBuffMatAdress(pBall->m_nModelIdx),
		pModel->GetNumMatAdress(pBall->m_nModelIdx),
		pModel->GetTexIdx(pBall->m_nModelIdx));

	//初期化処理
	pBall->Init();

	return pBall;
}