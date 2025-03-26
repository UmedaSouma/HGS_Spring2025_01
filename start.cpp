//==========================
// 
// タイトルロゴ[Start.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"start.h"
#include"manager.h"

//静的メンバの初期化
const int CStart::PRIORITY = 4;//描画優先度
int  CStart::m_nTexIdx = 0;//テクスチャID
//========================
//コンストラクタ
//========================
CStart::CStart(int nPriority) :CObject2D(nPriority)
{

}

//========================
//デストラクタ
//========================
CStart::~CStart()
{

}

//========================
//初期設定
//========================
HRESULT CStart::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//終了処理
//========================
void CStart::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//更新処理
//========================
void CStart::Update()
{
	CObject2D::Update();
}

//========================
//描画処理
//========================
void CStart::Draw()
{
	if (CManager::GetInstance()->GetGameManager()->GetStart())
	{//開始している
		return;
	}

	CObject2D::Draw();
}

//========================
//オブジェクト2D生成
//========================
CStart* CStart::Create(D3DXVECTOR3 pos)
{
	//インスタンス生成
	CStart* pStart = DBG_NEW CStart;

	//テクスチャ設定
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pStart->m_nTexIdx = pTex->Regist("data\\TEXTURE\\ui.png");
	pStart->BindTexture(pTex->GetAdress(pStart->m_nTexIdx));

	//位置の設定
	pStart->SetPos(pos);

	//サイズ設定
	pStart->SetSize(100.0f, 350.0f);

	//色を設定
	//pStart->SetCor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//初期設定
	pStart->Init();

	return pStart;
}