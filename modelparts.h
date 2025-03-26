//==========================
// 
// モデルのパーツの処理[modelparts.h]
// Author Yuki Goto
//
//==========================
#ifndef _MODELPARTS_H_
#define _MODELPARTS_H_

//クラスの定義
class CModelParts
{
public:

	//メンバ関数
	CModelParts();//コンストラクタ
	~CModelParts();//デストラクタ
	HRESULT Init();//初期化処理
	void Uninit();//終了処理
	void Update();//更新処理
	void Draw();//描画処理
	static CModelParts* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModelParts* Parent,int ModelPartsNum, D3DXVECTOR3 scale);//生成
	void SetParents(CModelParts* Parent);//親モデルの設定
	void SetPos(D3DXVECTOR3 pos);//位置の設定
	void SetRot(D3DXVECTOR3 rot);//向きの設定
	D3DXVECTOR3& GetPos();//位置の取得
	D3DXVECTOR3& GetRot();//向きの取得
	bool GetParent();//親パーツがあるかの取得
	D3DXMATRIX& GetMtxWorld();//マトリックス取得
	void SetSize();//サイズの設定
	D3DXVECTOR3& GetVtxMin();//頂点の最小の場所を取得
	D3DXVECTOR3& GetVtxMax();//頂点の最大の場所を取得
	void SetCor();//色の設定
	int GetModelNum();//モデルの番号を取得
private:

	//メンバ変数
	D3DXVECTOR3 m_pos;//オフセット位置
	D3DXVECTOR3 m_rot;//オフセット向き
	D3DXVECTOR3 m_motionpos;//オフセット位置
	D3DXVECTOR3 m_motionrot;//オフセット向き

	D3DXMATRIX m_mtxWorld;//ワールドマトリックス
	LPD3DXMESH m_pMesh;//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER m_pBuffMat;//マテリアルへのポインタ
	DWORD m_dwNumMat;//マテリアルの数
	D3DCOLORVALUE m_Diffuse[100];//色の数
	D3DXVECTOR3 m_vtxMin;//頂点の最小
	D3DXVECTOR3 m_vtxMax;//頂点の最大
	D3DXVECTOR3 m_Size;//モデルの大きさ
	CModelParts* m_ParentParts;//親モデルのポインタ
	bool m_corDamage;//被弾したときの色に変更するか判定
	int m_modelIdx;//モデルの番号
	D3DXVECTOR3 m_scale;//スケール
};
#endif