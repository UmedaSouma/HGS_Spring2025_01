//==========================
// 
// ゲーム画面の処理[game.h]
// Author Yuki Goto
//
//==========================
#ifndef _GAME_TEST_01_H_
#define _GAME_TEST_01_H_

//include
#include"scene.h"

//ゲームクラスの定義
class CGameTest01 :public CScene
{
public:

	//メンバ関数
	CGameTest01();//コンストラクタ
	~CGameTest01() override;//デストラクタ
	HRESULT Init()override;//初期化処理
	void Uninit()override;//終了処理
	void Update()override;//更新処理
	void Draw()override;//描画処理
private:
};

#endif 