#pragma once
//==========================
// 
// 味方ブロック[block_ally.h]
// Author Soma Umeda
//
//==========================
#ifndef _BLOCK_ALLY_H_
#define _BLOCK_ALLY_H_

//include
#include "block.h"

//クラスの定義
class CBlockAlly :public CBlock
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CBlockAlly(int nPriority = PRIORITY);//コンストラクタ
	~CBlockAlly() override;		//デストラクタ
	HRESULT Init() override;	//初期化処理
	void Uninit() override;		//終了処理
	void Update() override;		//更新処理
	void Draw() override;		//描画処理
	void Hit() override;		//当たった時
	static CBlockAlly* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
private:
	int m_nModelIdx;//テクスチャの番号
};
#endif