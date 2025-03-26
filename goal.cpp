//==========================
// 
// ゴール[goal.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "goal.h"
#include "manager.h"
#include "model.h"

//静的メンバ初期化
const int CGoal::PRIORITY = 1;//描画順

//==========================
//コンストラクタ
//==========================
CGoal::CGoal(int nPriority) :
	CObjectX(nPriority),//基底コンストラクタ
	m_nModelIdx(0),//モデルの番号
	m_ball(nullptr)//ボールの情報
{

}

//==========================
//デストラクタ
//==========================
CGoal::~CGoal()
{

}

//==========================
//初期化処理
//==========================
HRESULT CGoal::Init()
{
	//ボールの情報を取得
	GetBallInfo();

	//サイズ設定
	SetSize();

	//初期設定
	CObjectX::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CGoal::Uninit()
{
	if (m_ball != nullptr)
	{
		m_ball = nullptr;
	}

	//終了処理
	CObjectX::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CGoal::Update()
{
	//更新処理
	CObjectX::Update();

	hit();
}

//==========================
//描画処理
//==========================
void CGoal::Draw()
{
	//描画処理
	CObjectX::Draw();
}

//==========================
//オブジェクト生成
//==========================
CGoal* CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CGoal* pGoal = DBG_NEW CGoal;

	//位置の設定
	pGoal->SetPos(pos);

	//スケールの設定
	pGoal->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pGoal->m_nModelIdx = pModel->Regist("data\\MODEL\\goal.x");
	pGoal->BindModel(pModel->GetMeshAdress(pGoal->m_nModelIdx),
		pModel->GetBuffMatAdress(pGoal->m_nModelIdx),
		pModel->GetNumMatAdress(pGoal->m_nModelIdx),
		pModel->GetTexIdx(pGoal->m_nModelIdx));

	//初期化処理
	pGoal->Init();

	//タイプ設定
	pGoal->SetType(TYPE::GOAL);

	return pGoal;
}

//==========================
//当たり判定
//==========================
void CGoal::hit()
{
	if (m_ball->GetPos().x <= GetPos().x + GetVtxMax().x
		&& m_ball->GetPos().x > GetPos().x + GetVtxMin().x
		&& m_ball->GetPos().y  < GetPos().y + GetVtxMax().y
		&& m_ball->GetPos().y  > GetPos().y + GetVtxMin().y)
	{
		m_ball->Uninit();//ボールを消す

		CManager::GetInstance()->GetGameManager()->SetEnd();
		CManager::GetInstance()->GetGameManager()->SetGame();

	}
}

//==========================
//ボールの情報を取得
//==========================
void CGoal::GetBallInfo()
{
	//オブジェクトを取得
	CObject* pObj = CObject::GetObj(nullptr, CBall::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CBall::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::BALL)
		{//オブジェクトが敵ではない
			pObj = CObject::GetObj(pObj, CBall::PRIORITY);
			continue;
		}

		//ボールの情報を取得
		m_ball = dynamic_cast<CBall*>(pObj);

		break;
	}
}