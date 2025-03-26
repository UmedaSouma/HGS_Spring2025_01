//==========================
// 
// プレイヤー処理[player.h]
// Author Yuki Goto
//
//==========================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "objectgame.h"

//クラスの定義
class CPlayer :public CObjectgame
{
public:
	//メンバ関数
	CPlayer(int nPriority = PRIORITY);//コンストラクタ
	~CPlayer() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	void Operation();	// 操作
	void OpeMove();		// 移動操作
	void OpeBullet();
	static CPlayer* Create(D3DXVECTOR3 pos);//オブジェクト生成
private:
};
#endif