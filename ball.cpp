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
CBall::CBall(int nPriority) :
	CObjectX(nPriority),
m_nModelIdx(0),
m_Life(MAXLIFE)//寿命
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
	SetSize();

	//初期設定
	CObjectX::Init();
	
	SetMove({ 1.0f,1.0f,0.0f });

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

	SetPosOld(GetPos());
	SetPos(GetMove()+GetPos());
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

	//タイプ設定
	pBall->SetType(TYPE::BALL);

	return pBall;
}

//==========================
//寿命を減らす
//==========================
void CBall::SubLife()
{
	m_Life--;

	Reset();

	if (m_Life <= 0)
	{
		Uninit();
		CManager::GetInstance()->GetGameManager()->SetEnd();
	}
}

//==========================
//位置初期化
//==========================
void CBall::Reset()
{
	SetPos({ 0.0f, -50.0f, 0.0 });
}