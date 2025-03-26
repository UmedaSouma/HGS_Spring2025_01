//==========================
// 
// サウンド処理[sound.h]
// Author Yuki Goto
//
//==========================
#ifndef _SOUND_H_
#define _SOUND_H_

// サウンドクラスの定義
class CSound
{
public:
	//サウンド一覧
	typedef enum
	{
		SOUND_LABEL_INGAME = 0,		// BGM0
		SOUND_LABEL_TITLE,			// BGM1
		SOUND_LABEL_RESULT,			// BGM2
		SOUND_LABEL_SE_SHOT,		// 弾発射音
		SOUND_LABEL_SE_GRENADE,			// ヒット音
		SOUND_LABEL_SE_DEATH,	// 死亡音
		SOUND_LABEL_SE_ITEM,	// アイテム取得音
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//メンバ関数
	CSound();//コンストラクタ
	~CSound();//デストラクタ
	HRESULT Init(HWND hWnd);//初期化処理
	void Uninit();//終了処理
	HRESULT PlaySound(SOUND_LABEL label);// セグメント再生(再生中なら停止)
	void Stop(SOUND_LABEL label);// セグメント停止(ラベル指定)
	void Stop();// セグメント停止(全て)

private:
	// サウンド情報の構造体定義
	typedef struct
	{
		const char* pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDINFO;

	//メンバ関数
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);// チャンクのチェック
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);// チャンクデータの読み込み

	//メンバ変数
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ

	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX]= {				// サウンドの情報
	{"data/BGM/ingame.wav", -1},		// BGM0
	{"data/BGM/title.wav", -1},		// BGM1
	{"data/BGM/result.wav", -1},		// BGM2
	{"data/SE/bullet.wav", 0},			// 弾発射音
	{"data/SE/grenade.wav", 0},			// 爆発音
	{"data/SE/death.wav", 0},	// 死亡音
	{"data/SE/item.wav", 0},	// アイテム取得音
	};			
};

#endif 
