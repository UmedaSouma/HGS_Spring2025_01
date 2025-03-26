//==========================
// 
// 壁[wall.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "wall.h"
#include "manager.h"
#include "model.h"

//静的メンバ初期化
const int CWall::PRIORITY = 1;//描画順

//==========================
//コンストラクタ
//==========================
CWall::CWall(int nPriority) :
	CObjectX(nPriority),//基底コンストラクタ
	m_nModelIdx(0),//モデルの番号
	m_ball(nullptr)
{

}

//==========================
//デストラクタ
//==========================
CWall::~CWall()
{

}

//==========================
//初期化処理
//==========================
HRESULT CWall::Init()
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
void  CWall::Uninit()
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
void CWall::Update()
{
	//更新処理
	CObjectX::Update();

	Hit();
}

//==========================
//描画処理
//==========================
void CWall::Draw()
{
	//描画処理
	CObjectX::Draw();
}

//==========================
//オブジェクト生成
//==========================
CWall* CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CWall* pWall = DBG_NEW CWall;

	//位置の設定
	pWall->SetPos(pos);

	//スケールの設定
	pWall->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pWall->m_nModelIdx = pModel->Regist("data\\MODEL\\wall.x");
	pWall->BindModel(pModel->GetMeshAdress(pWall->m_nModelIdx),
		pModel->GetBuffMatAdress(pWall->m_nModelIdx),
		pModel->GetNumMatAdress(pWall->m_nModelIdx),
		pModel->GetTexIdx(pWall->m_nModelIdx));

	//初期化処理
	pWall->Init();

	return pWall;
}

//==========================
//当たり判定
//==========================
void CWall::Hit()
{
	//当たり判定の情報を取得
	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	//左側の判定
	bool collision = pCollision->RectangleLeft(m_ball->GetPosOld(), m_ball->GetPos(), GetPos(),
		m_ball->GetVtxMax(), m_ball->GetVtxMin(), GetVtxMax(), GetVtxMin());

	if (collision)
	{
		m_ball->SetMove({ -m_ball->GetMove().x, m_ball->GetMove().y, m_ball->GetMove().z });
		return;
	}

	//右側の判定
	collision = pCollision->RectangleRight(m_ball->GetPosOld(), m_ball->GetPos(), GetPos(),
		m_ball->GetVtxMax(), m_ball->GetVtxMin(), GetVtxMax(), GetVtxMin());

	if (collision)
	{
		m_ball->SetMove({ -m_ball->GetMove().x, m_ball->GetMove().y, m_ball->GetMove().z });
		return;
	}

	//上の判定
	collision = pCollision->RectangleFront(m_ball->GetPosOld(), m_ball->GetPos(), GetPos(),
		m_ball->GetVtxMax(), m_ball->GetVtxMin(), GetVtxMax(), GetVtxMin());

	if (collision)
	{
		m_ball->SetMove({ m_ball->GetMove().x, -m_ball->GetMove().y, m_ball->GetMove().z });
		return;
	}

	//下の判定
	collision = pCollision->RectangletBack(m_ball->GetPosOld(), m_ball->GetPos(), GetPos(),
		m_ball->GetVtxMax(), m_ball->GetVtxMin(), GetVtxMax(), GetVtxMin());

	if (collision)
	{
		m_ball->SetMove({ m_ball->GetMove().x, -m_ball->GetMove().y, m_ball->GetMove().z });
		return;
	}
}

//==========================
//ボールの情報を取得
//==========================
void CWall::GetBallInfo()
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