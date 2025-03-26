//==========================
// 
// [gamemanager.h]
// Author Yuki Goto
//
//==========================
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

//クラスの定義
class CGameManager
{
public:
	//定数
	static const int PRIORITY;

	//メンバ関数
	CGameManager();//コンストラクタ
	~CGameManager();//デストラクタ
	bool GetGame();//クリア判定を取得
	void SetGame();//クリア判定を設定
	bool GetEnd();//終了判定を取得
	void SetEnd();//終了判定を設定
	void reset();//情報リセット
private:
	bool m_Game;//クリア判定
	bool m_End;//終了判定
};

#endif 
