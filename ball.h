//==========================
// 
// ボール[ball.h]
// Author Yuki Goto
//
//==========================
#ifndef _BALL_H_
#define _BALL_H_

//include
#include "objectX.h"

//クラスの定義
class CBall :public CObjectX
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CBall(int nPriority = PRIORITY);//コンストラクタ
	~CBall() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CBall* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
private:
	int m_nModelIdx;//モデルの番号
};
#endif