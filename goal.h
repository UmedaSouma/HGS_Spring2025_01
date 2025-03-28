//==========================
// 
// ゴール[goal.h]
// Author Yuki Goto
//
//==========================
#ifndef _GOAL_H_
#define _GOAL_H_

//include
#include "objectX.h"
#include "ball.h"

//クラスの定義
class CGoal :public CObjectX
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CGoal(int nPriority = PRIORITY);//コンストラクタ
	~CGoal() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CGoal* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
	void hit();//当たり判定
private:
	
	void GetBallInfo();//ボールの情報を取得

	int m_nModelIdx;//モデルの番号
	CBall* m_ball;//ボールの情報
};
#endif