//==========================
// 
// フェード処理[fade.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "fade.h"
#include"manager.h"

//静的メンバ変数初期化
const int CFade::PRIORITY = 5;
//==========================
// コンストラクタ
//==========================
CFade::CFade(int priority):CObject2D(priority)
{
	m_cor = 0.0f;
	m_fade = FADE_NONE;
	g_modenext = CScene::MODE::TITLE;
	
}

//==========================
// デストラクタ
//==========================
CFade::~CFade()
{

}

//==========================
// 初期設定
//==========================
HRESULT CFade::Init()
{
	SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	SetSize(360.0f, 640.0f);
	CObject2D::Init();

	return S_OK;
}

//==========================
// 終了処理
//==========================
void CFade::Uninit()
{

}

//==========================
// 更新処理
//==========================
void CFade::Update()
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{//フェードイン状態
			m_cor -= 0.05f;

			if (m_cor <= 0.0f)
			{
				m_cor = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{//フェードアウト状態
			m_cor += 0.05f;

			if (m_cor >= 1.0f)
			{
				m_cor = 1.0f;
				m_fade = FADE_IN;

				CManager::GetInstance()->SetMode(g_modenext);
			}
		}
	}

	SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_cor));
	CObject2D::Update();

}

//==========================
// 描画処理
//==========================
void CFade::Draw()
{
	CObject2D::Draw();
}

//==========================
//フェードの設定処理
//==========================
void CFade::SetFade(CScene::MODE modenext)
{
	g_modenext = modenext;
	m_fade = FADE_OUT;
}

//==========================
//フェードの状態取得
//==========================
CFade::FADE CFade::GetFade()
{
	return m_fade;
}

//==========================
//生成
//==========================
CFade* CFade::Create()
{
	CFade* pFade = DBG_NEW CFade;

	pFade->Init();

	pFade->SetType(CObject::FADE);

	return pFade;
}