#pragma once
//==========================
// 
// 味方ブロック[block_ally.h]
// Author Soma Umeda
//
//==========================
#ifndef _BLOCK_ENEMY_H_
#define _BLOCK_ENEMY_H_

//include
#include "block.h"
#include "ball.h"

//クラスの定義
class CBlockEnemy :public CBlock
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CBlockEnemy(int nPriority = PRIORITY);//コンストラクタ
	~CBlockEnemy() override;	//デストラクタ
	HRESULT Init() override;	//初期化処理
	void Uninit() override;		//終了処理
	void Update() override;		//更新処理
	void Draw() override;		//描画処理
	void Hit() override;		//当たった時
	static CBlockEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
private:
	void GetBallInfo();//ボールの情報を取得

	//メンバ変数
	int m_nModelIdx;//テクスチャの番号
	CBall* m_ball;//ボールの情報
};
#endif