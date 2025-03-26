//==========================
// 
// モーションするモデルの描画処理[motionmodel.h]
// Author Yuki Goto
//
//==========================
#ifndef _MOTIONMODEL_H_
#define _MOTIONMODEL_H_

//include
#include "objectgame.h"
#include "modelparts.h"

//クラスの定義
class CMotionModel :public CObjectgame
{
public:

	//定数
	static const int PRIORITY;//描画順
	static const int MAX_PARTS = 20;//パーツ数
	static const int MAX_KEYSET = 20;//キーセットの数
	static const int MAX_MOTION = 10;//モーションの数

	//キーデータ
	struct KEY
	{
		D3DXVECTOR3 pos;//位置
		D3DXVECTOR3 rot;//向き
	};

	//キー情報
	struct KEYSET
	{
		int nFrame;//フレーム
		KEY aKey[MAX_PARTS];
	};

	//モーション情報
	struct MOTION
	{
		int Loop;//ループするか
		int nKeyNum;//キーの総数
		KEYSET aKeySet[MAX_KEYSET];
	};

	//モーションの種類
	typedef enum
	{
		NEUTRAL = 0,//待機
		MOVE,//移動
		ATTACK,//攻撃
	}MOTION_TYPE;

	//メンバ関数
	CMotionModel(int nPriority = PRIORITY);//コンストラクタ
	~CMotionModel() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CMotionModel* Create();//モデル生成
	void LoadFile(const char name[256],D3DXVECTOR3 scale);//ファイルを読み込む
	void SetMotion(MOTION_TYPE MotionType);//モーションを設定
private:

	//メンバ関数
	void Motion();//モーション処理

	//メンバ変数
	CModelParts* m_PartsList[MAX_PARTS];//パーツの情報
	MOTION m_MotionInfo[MAX_MOTION];//モーションの情報
	KEY m_FirstMotion[MAX_PARTS];//最初の位置と向き
	MOTION_TYPE m_MotionType;//現在のモーションの種類
	int m_nCurKey;//現在のキー番号
	int m_nCntMotion;//モーションカウンター
	int m_CurMotion;//現在のモーション番号
};
#endif 