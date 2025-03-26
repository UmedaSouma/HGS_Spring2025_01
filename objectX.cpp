//==========================
// 
// モデルの描画処理[objectX.cpp]
// Author Yuki Goto
//
//==========================

//incelude
#include"objectX.h"
#include"manager.h"

//静的メンバ変数初期化
const int CObjectX::PRIORITY = 3;//描画順
//==========================
// コンストラクタ
//==========================
CObjectX::CObjectX(int nPriority):CObjectgame(nPriority)
{
	//変数の初期化
	m_pMesh = nullptr;//メッシュ(頂点情報)へのポインタ
	m_pBuffMat = nullptr;//マテリアルへのポインタ
	m_dwNumMat = 0;//マテリアルの数
	m_pTexture = nullptr;
	m_pTexture2 = nullptr;
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//モデルの大きさ
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//頂点の最小
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//頂点の最大
}

//==========================
// デストラクタ
//==========================
CObjectX::~CObjectX(void)
{

}

//==========================
// 初期化処理
//==========================
HRESULT CObjectX::Init(void)
{

	//モデルの大きさを取得
	//SetSize();

	return S_OK;
}

//==========================
// 終了処理
//==========================
void CObjectX::Uninit(void)
{
	//メッシュの破棄
	if (m_pMesh != nullptr)
	{
		m_pMesh = nullptr;
	}

	//マテリアルの破棄
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat = nullptr;
	}

	if (m_pTexture2 != nullptr)
	{
		delete[] m_pTexture2;
		m_pTexture2 = nullptr;
	}
}

//==========================
// 更新処理
//==========================
void CObjectX::Update(void)
{

}

//==========================
// 描画処理
//==========================
void CObjectX::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算用マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	D3DXMATRIX mtxShadow;//影行列
	D3DXPLANE plane;//平面情報
	D3DXVECTOR4 vecLight;//ライト逆方向
	D3DXVECTOR3 pos, nor;//平面上の1点と法線

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&GetMtxWorld());
	D3DXMatrixIdentity(&mtxShadow);

	
	//スケール設定
	D3DXMatrixScaling(&mtxScale, GetScale().x, GetScale().y, GetScale().z);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxScale);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxRot);
	
	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);

	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &GetMtxWorld());

	//現在のマトリックスを取得
	pDevice->GetMaterial(&matDef);

	//法線の長さを1にする
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		pDevice->SetTexture(0, m_pTexture2[nCntMat]);
		//if (pMat[nCntMat].pTextureFilename != NULL)
		//{
		//	//テクスチャの設定
		//	pDevice->SetTexture(0, m_pTexture);
		//}
		//else if (pMat[nCntMat].pTextureFilename == NULL)
		//{
		//	//テクスチャの設定
		//	pDevice->SetTexture(0, NULL);
		//}

		//D3DXCreateSphere(pDevice, 30.0f, 10, 7, &m_pMesh, NULL);

		//モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat);
	}


	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
}

//==========================
// モデル生成
//==========================
CObjectX* CObjectX::Create(void)
{
	CObjectX* pModel = DBG_NEW CObjectX;

	//初期化処理
	pModel->Init();

	return pModel;
}

//==========================
//モデル割り当て
//==========================
void CObjectX::BindModel(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat, LPDIRECT3DTEXTURE9* pTexture)
{
	m_pMesh = pMesh;
	m_pBuffMat = pBuffMat;
	m_dwNumMat = dwNumMat;

	m_pTexture2 = DBG_NEW LPDIRECT3DTEXTURE9[int(dwNumMat)];

	for (int i = 0; i < int(dwNumMat); i++)
	{
		m_pTexture2[i] = pTexture[i];
	}
}

//========================
//サイズを取得
//========================
void CObjectX::SetSize(void)
{
	int nNumVtx;//頂点数
	DWORD sizeFVF;//頂点フォーマットのサイズ
	BYTE* pVtxBuff;//頂点バッファへのポインタ

	//頂点数の取得
	nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点バッファのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		vtx.x *= GetScale().x;
		vtx.y *= GetScale().y;
		vtx.z *= GetScale().z;

		//最大の頂点を取得
		if (vtx.x > m_vtxMax.x)
		{
			m_vtxMax.x = floor(vtx.x);
		}
		if (vtx.y > m_vtxMax.y)
		{
			m_vtxMax.y = floor(vtx.y);
		}
		if (vtx.z > m_vtxMax.z)
		{
			m_vtxMax.z = floor(vtx.z);
		}

		//最小の頂点を取得
		if (vtx.x < m_vtxMin.x)
		{
			m_vtxMin.x = floor(vtx.x);
		}
		if (vtx.y < m_vtxMin.y)
		{
			m_vtxMin.y = floor(vtx.y);
		}

		if (vtx.z < m_vtxMin.z)
		{
			m_vtxMin.z = floor(vtx.z);
		}

		pVtxBuff += sizeFVF;
	}

	//頂点バッファのアンロック
	m_pMesh->UnlockVertexBuffer();

	m_Size.x = m_vtxMax.x - m_vtxMin.x;
	m_Size.y = m_vtxMax.y - m_vtxMin.y;
	m_Size.z = m_vtxMax.z - m_vtxMin.z;
}

//========================
//テクスチャ割り当て
//========================
void CObjectX::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//========================
//頂点の最小の場所を取得
//========================
D3DXVECTOR3& CObjectX::GetVtxMin(void)
{
	return m_vtxMin;
}

//========================
//頂点の最大の場所を取得
//========================
D3DXVECTOR3& CObjectX::GetVtxMax(void)
{
	return m_vtxMax;
}

//========================
//サイズ取得
//========================
D3DXVECTOR3& CObjectX::GetSize(void)
{
	return m_Size;
}

//========================
//メッシュ(頂点情報)へのポインタ
//========================
LPD3DXMESH& CObjectX::GetMesh()
{
	return m_pMesh;
}

//========================
//マテリアルへのポインタ
//========================
LPD3DXBUFFER& CObjectX::GetBuffMat()
{
	return m_pBuffMat;
}

//========================
//マテリアルの数
//========================
DWORD& CObjectX::GetNumMat()
{
	return m_dwNumMat;
}