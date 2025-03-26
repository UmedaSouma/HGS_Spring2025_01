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
#include "block_enemy.h"
#include "player.h"

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

	SetPosOld(GetPos());
	SetPos(GetMove() + GetPos());

	HitBlock();

	if (GetPos().z > 50.0f)
	{
		Uninit();
	}
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
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move)
{
	//インスタンス生成
	CBullet* pBullet = DBG_NEW CBullet;

	//位置の設定
	pBullet->SetPos(pos);

	//スケールの設定
	pBullet->SetScale(scale);

	// 移動量の設定
	pBullet->SetMove(move);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBullet->m_nModelIdx = pModel->Regist("data\\MODEL\\ball.x");
	pBullet->BindModel(pModel->GetMeshAdress(pBullet->m_nModelIdx),
		pModel->GetBuffMatAdress(pBullet->m_nModelIdx),
		pModel->GetNumMatAdress(pBullet->m_nModelIdx),
		pModel->GetTexIdx(pBullet->m_nModelIdx));

	//初期化処理
	pBullet->Init();

	return pBullet;
}

//==========================
//当たり判定
//==========================
void CBullet::HitBlock()
{
	//オブジェクトを取得
	CObject* pObj = CObject::GetObj(nullptr, CBlockEnemy::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CBlockEnemy::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMYBLOCK)
		{//オブジェクトが敵ではない
			pObj = CObject::GetObj(pObj, CBlockEnemy::PRIORITY);
			continue;
		}

		//敵ブロックの情報を取得
		CBlockEnemy* pBlockEnemy = dynamic_cast<CBlockEnemy*>(pObj);

		if (GetPos().x  <= pBlockEnemy->GetPos().x + pBlockEnemy->GetVtxMax().x
			&& GetPos().x  > pBlockEnemy->GetPos().x + pBlockEnemy->GetVtxMin().x
			&& GetPos().y  < pBlockEnemy->GetPos().y + pBlockEnemy->GetVtxMax().y
			&& GetPos().y  > pBlockEnemy->GetPos().y + pBlockEnemy->GetVtxMin().y
			&& GetPos().z  < pBlockEnemy->GetPos().z + pBlockEnemy->GetVtxMax().z
			&& GetPos().z  > pBlockEnemy->GetPos().z + pBlockEnemy->GetVtxMin().z)
		{
			pBlockEnemy->Uninit();
			Uninit();

			//オブジェクトを取得
			CObject* pObj2 = CObject::GetObj(nullptr, CPlayer::PRIORITY);
			CPlayer* pplayer = nullptr;

			while (pObj2 != nullptr)
			{
				if (pObj2 == nullptr)
				{//オブジェクトがない
					pObj2 = CObject::GetObj(pObj2, CPlayer::PRIORITY);
					continue;
				}

				//種類の取得
				CObject::TYPE type = pObj2->GetType();

				if (type != CObject::TYPE::PLAYER)
				{//オブジェクトが敵ではない
					pObj2 = CObject::GetObj(pObj2, CPlayer::PRIORITY);
					continue;
				}

				//ボールの情報を取得
				pplayer = dynamic_cast<CPlayer*>(pObj2);
				pplayer->CountBreak();
				break;
			}

		}

		pObj = CObject::GetObj(pObj, CBlockEnemy::PRIORITY);
	}
}

//===========================================================================================================
// ボールの情報を取得
//===========================================================================================================
void CBullet::GetPlayerInfo()
{
	//オブジェクトを取得
	CObject* pObj2 = CObject::GetObj(nullptr, CPlayer::PRIORITY);
	CPlayer* pplayer = nullptr;

	while (pObj2 != nullptr)
	{
		if (pObj2 == nullptr)
		{//オブジェクトがない
			pObj2 = CObject::GetObj(pObj2, CPlayer::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj2->GetType();

		if (type != CObject::TYPE::BALL)
		{//オブジェクトが敵ではない
			pObj2 = CObject::GetObj(pObj2, CPlayer::PRIORITY);
			continue;
		}

		//ボールの情報を取得
		pplayer = dynamic_cast<CPlayer*>(pObj2);

		break;
	}
}