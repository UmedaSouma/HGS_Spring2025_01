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
CBlockAlly::CBlockAlly(int nPriority) :
	CBlock(nPriority),
	m_nModelIdx(0),
	m_ball(nullptr)
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
void  CBlockAlly::Uninit()
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
void CBlockAlly::Update()
{
	SetPosOld(GetPos());
	SetPos(GetMove() + GetPos());

	if (GetPos().z > 0)
	{
		SetMove({ 0.0f,0.0f,0.0f });
	}

	//更新処理
	CObjectX::Update();

	//当たり判定
	Hit();
}

//==========================
//描画処理
//==========================
void CBlockAlly::Draw()
{
	//描画処理
	CObjectX::Draw();
}

//==========================
//オブジェクト生成
//==========================
CBlockAlly* CBlockAlly::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move)
{
	//インスタンス生成
	CBlockAlly* pBlockAlly = DBG_NEW CBlockAlly;

	//位置の設定
	pBlockAlly->SetPos(pos);

	//スケールの設定
	pBlockAlly->SetScale(scale);

	pBlockAlly->SetMove(move);

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

//===========================================================================================================
// 当たった時の処理
//===========================================================================================================
void CBlockAlly::Hit()
{
	//当たり判定の情報を取得
	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	//左側の判定
	bool collision = pCollision->RectangleLeft(m_ball->GetPosOld(), m_ball->GetPos(), GetPos(),
		m_ball->GetVtxMax(), m_ball->GetVtxMin(), GetVtxMax(), GetVtxMin());

	if (collision)
	{
		m_ball->SetMove({ -m_ball->GetMove().x, m_ball->GetMove().y, m_ball->GetMove().z });
		Uninit();
		return;
	}

	//右側の判定
	collision = pCollision->RectangleRight(m_ball->GetPosOld(), m_ball->GetPos(), GetPos(),
		m_ball->GetVtxMax(), m_ball->GetVtxMin(), GetVtxMax(), GetVtxMin());

	if (collision)
	{
		m_ball->SetMove({ -m_ball->GetMove().x, m_ball->GetMove().y, m_ball->GetMove().z });
		Uninit();
		return;
	}

	//上の判定
	collision = pCollision->RectangleFront(m_ball->GetPosOld(), m_ball->GetPos(), GetPos(),
		m_ball->GetVtxMax(), m_ball->GetVtxMin(), GetVtxMax(), GetVtxMin());

	if (collision)
	{
		m_ball->SetMove({ m_ball->GetMove().x, -m_ball->GetMove().y, m_ball->GetMove().z });
		Uninit();
		return;
	}

	//下の判定
	collision = pCollision->RectangletBack(m_ball->GetPosOld(), m_ball->GetPos(), GetPos(),
		m_ball->GetVtxMax(), m_ball->GetVtxMin(), GetVtxMax(), GetVtxMin());

	if (collision)
	{
		m_ball->SetMove({ m_ball->GetMove().x, -m_ball->GetMove().y, m_ball->GetMove().z });
		Uninit();
		return;
	}
}

//===========================================================================================================
// ボールの情報を取得
//===========================================================================================================
void CBlockAlly::GetBallInfo()
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