//==========================
// 
// ブロックを壊す弾[bullet.h]
// Author Yuki Goto
//
//==========================
#ifndef _BULLET_H_
#define _BULLET_H_

//include
#include "objectX.h"

//クラスの定義
class CBullet :public CObjectX
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CBullet(int nPriority = PRIORITY);//コンストラクタ
	~CBullet() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
	void HitBlock();//当たり判定
private:
	int m_nModelIdx;//モデルの番号
};
#endif