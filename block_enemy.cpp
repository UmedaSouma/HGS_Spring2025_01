//==========================
// 
// 味方ブロック[block_ally.cpp]
// Author Soma Umeda
//
//==========================

//include
#include "block_enemy.h"
#include "manager.h"
#include "model.h"

//静的メンバ初期化
const int CBlockEnemy::PRIORITY = 1;//描画順

//==========================
//コンストラクタ
//==========================
CBlockEnemy::CBlockEnemy(int nPriority) :
	CBlock(nPriority),
	m_nModelIdx(0),
	m_ball(nullptr)
{

}

//==========================
//デストラクタ
//==========================
CBlockEnemy::~CBlockEnemy()
{

}

//==========================
//初期化処理
//==========================
HRESULT CBlockEnemy::Init()
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
void  CBlockEnemy::Uninit()
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
void CBlockEnemy::Update()
{
	//更新処理
	CObjectX::Update();
	
	Hit();
}

//==========================
//描画処理
//==========================
void CBlockEnemy::Draw()
{
	//描画処理
	CObjectX::Draw();
}

//==========================
//オブジェクト生成
//==========================
CBlockEnemy* CBlockEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CBlockEnemy* pBlockEnemy = DBG_NEW CBlockEnemy;

	//位置の設定
	pBlockEnemy->SetPos(pos);

	//スケールの設定
	pBlockEnemy->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBlockEnemy->m_nModelIdx = pModel->Regist("data\\MODEL\\soil.x");
	pBlockEnemy->BindModel(pModel->GetMeshAdress(pBlockEnemy->m_nModelIdx),
		pModel->GetBuffMatAdress(pBlockEnemy->m_nModelIdx),
		pModel->GetNumMatAdress(pBlockEnemy->m_nModelIdx),
		pModel->GetTexIdx(pBlockEnemy->m_nModelIdx));

	//初期化処理
	pBlockEnemy->Init();

	return pBlockEnemy;
}

//===========================================================================================================
// 当たった時の処理
//===========================================================================================================
void CBlockEnemy::Hit()
{
	//当たり判定の情報を取得
	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	//左側の判定
	bool collision = pCollision->RectangleLeft(m_ball->GetPosOld(), m_ball->GetPos(), GetPos(),
		m_ball->GetVtxMax(), m_ball->GetVtxMin(), GetVtxMax(), GetVtxMin());

	if (collision)
	{
		m_ball->Uninit();
	}
}

//===========================================================================================================
//ボールの情報を取得
//===========================================================================================================
void CBlockEnemy::GetBallInfo()
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