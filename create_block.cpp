//===========================================================================================================================================================
// 
// ブロック生成 [create_block.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "create_block.h"
#include "block_enemy.h"
#include "manager.h"

//===========================================================================================================
// コンストラクタ
//===========================================================================================================
CCreateBlock::CCreateBlock()
{
}

//===========================================================================================================
// デストラクタ
//===========================================================================================================
CCreateBlock::~CCreateBlock()
{
}

//===========================================================================================================
// 初期設定
//===========================================================================================================
void CCreateBlock::Init()
{
	m_nTimer = 0;
	// srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化
	
	for (int i = 0; i < MAX_V; i++)
	{
		for (int t = 0; t < MAX_H; t++)
		{
			// int r = rand() % MAX_V + 1;
			D3DXVECTOR3 pos = { 0.0f + (i * 45),-140.0f+(t * 45),0.0f };
			D3DXVECTOR3 scale = { SCALE,SCALE,1.0f };
			CBlockEnemy::Create(pos, scale);
		}
	}
}

//===========================================================================================================
// 終了処理
//===========================================================================================================
void CCreateBlock::Uninit()
{
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void CCreateBlock::Update()
{
	if (!CManager::GetInstance()->GetGameManager()->GetStart())
	{//開始している
		return;
	}

	if (m_nTimer % 600 == 0 && m_nTimer != 0)
	{
		for (int i = 0; i < MAX_V; i++)
		{
			D3DXVECTOR3 pos = { 315.0f,-140.0f + (i * 45),0.0f };

			if (i == 6)
			{
				pos.x -= 40;
			}

			D3DXVECTOR3 scale = { SCALE,SCALE,1.0f };
			CBlockEnemy::Create(pos, scale);
		}

		//オブジェクトを取得
		CObject* pObj = CObject::GetObj(nullptr, CBlockEnemy::PRIORITY);

		while (pObj != nullptr)
		{
			if (pObj->GetNextObj() == nullptr)
			{
				break;
			}


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

			//ボールの情報を取得
			CBlockEnemy* pBenemy = dynamic_cast<CBlockEnemy*>(pObj);

			D3DXVECTOR3 pBEpos = pBenemy->GetPos();
			pBEpos.x -= 40.0f;
			pBenemy->SetPos(pBEpos);

			pObj = CObject::GetObj(pObj, CBlockEnemy::PRIORITY);
			// break;
		}
	}

	m_nTimer++;
}
