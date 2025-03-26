//==========================
// 
// 壁[wall.h]
// Author Yuki Goto
//
//==========================
#ifndef _WALL_H_
#define _WALL_H_

//include
#include "objectX.h"
#include"ball.h"

//クラスの定義
class CWall :public CObjectX
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CWall(int nPriority = PRIORITY);//コンストラクタ
	~CWall() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CWall* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
	void Hit();//当たり判定
private:

	void GetBallInfo();//ボールの情報を取得

	CBall* m_ball;//ボールの情報
	int m_nModelIdx;//モデルの番号
};
#endif