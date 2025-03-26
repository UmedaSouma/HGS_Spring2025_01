//==========================
// 
// ブロックを壊す弾[bullet.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "bullet.h"
#include "manager.h"
#include "model.h"

//静的メンバ初期化
const int CBullet::PRIORITY = 1;//描画順

//==========================
//コンストラクタ
//==========================
CBullet::CBullet(int nPriority) :
	CObjectX(nPriority),//基底コンストラクタ
	m_nModelIdx(0)//モデルの番号
{

}

//==========================
//デストラクタ
//==========================
CBullet::~CBullet()
{

}

//==========================
//初期化処理
//==========================
HRESULT CBullet::Init()
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
void  CBullet::Uninit()
{
	//終了処理
	CObjectX::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CBullet::Update()
{
	//更新処理
	CObjectX::Update();
}

//==========================
//描画処理
//==========================
void CBullet::Draw()
{
	//描画処理
	CObjectX::Draw();
}

//==========================
//オブジェクト生成
//==========================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CBullet* pBullet = DBG_NEW CBullet;

	//位置の設定
	pBullet->SetPos(pos);

	//スケールの設定
	pBullet->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBullet->m_nModelIdx = pModel->Regist("data\\MODEL\\soil.x");
	pBullet->BindModel(pModel->GetMeshAdress(pBullet->m_nModelIdx),
		pModel->GetBuffMatAdress(pBullet->m_nModelIdx),
		pModel->GetNumMatAdress(pBullet->m_nModelIdx),
		pModel->GetTexIdx(pBullet->m_nModelIdx));

	//初期化処理
	pBullet->Init();

	return pBullet;
}