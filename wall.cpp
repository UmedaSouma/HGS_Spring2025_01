//==========================
// 
// 壁[wall.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "wall.h"
#include "manager.h"
#include "model.h"

//静的メンバ初期化
const int CWall::PRIORITY = 1;//描画順

//==========================
//コンストラクタ
//==========================
CWall::CWall(int nPriority) :
	CObjectX(nPriority),//基底コンストラクタ
	m_nModelIdx(0)//モデルの番号
{

}

//==========================
//デストラクタ
//==========================
CWall::~CWall()
{

}

//==========================
//初期化処理
//==========================
HRESULT CWall::Init()
{
	//サイズ設定
	//SetSize();

	//初期設定
	CObjectX::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CWall::Uninit()
{
	//終了処理
	CObjectX::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CWall::Update()
{
	//更新処理
	CObjectX::Update();
}

//==========================
//描画処理
//==========================
void CWall::Draw()
{
	//描画処理
	CObjectX::Draw();
}

//==========================
//オブジェクト生成
//==========================
CWall* CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CWall* pWall = DBG_NEW CWall;

	//位置の設定
	pWall->SetPos(pos);

	//スケールの設定
	pWall->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pWall->m_nModelIdx = pModel->Regist("data\\MODEL\\wall.x");
	pWall->BindModel(pModel->GetMeshAdress(pWall->m_nModelIdx),
		pModel->GetBuffMatAdress(pWall->m_nModelIdx),
		pModel->GetNumMatAdress(pWall->m_nModelIdx),
		pModel->GetTexIdx(pWall->m_nModelIdx));

	//初期化処理
	pWall->Init();

	return pWall;
}