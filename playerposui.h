//==========================
// 
// プレイヤーの位置[palyerposui.h]
// Author Yuki Goto
//
//==========================
#ifndef _PLAYERPOSUI_H_
#define _PLAYERPOSUI_H_

//include
#include "object3D.h"

//クラスの定義
class CPlayerposUI :public CObject3D
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CPlayerposUI(int nPriority = PRIORITY);//コンストラクタ
	~CPlayerposUI() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CPlayerposUI* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//オブジェクト生成
private:
	int m_nTexIdx;//テクスチャの番号
};
#endif