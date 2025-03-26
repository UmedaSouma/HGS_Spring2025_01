//==========================
// 
// �t�F�[�h����[fade.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "fade.h"
#include"manager.h"

//�ÓI�����o�ϐ�������
const int CFade::PRIORITY = 5;
//==========================
// �R���X�g���N�^
//==========================
CFade::CFade(int priority):CObject2D(priority)
{
	m_cor = 0.0f;
	m_fade = FADE_NONE;
	g_modenext = CScene::MODE::TITLE;
	
}

//==========================
// �f�X�g���N�^
//==========================
CFade::~CFade()
{

}

//==========================
// �����ݒ�
//==========================
HRESULT CFade::Init()
{
	SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	SetSize(360.0f, 640.0f);
	CObject2D::Init();

	return S_OK;
}

//==========================
// �I������
//==========================
void CFade::Uninit()
{

}

//==========================
// �X�V����
//==========================
void CFade::Update()
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{//�t�F�[�h�C�����
			m_cor -= 0.05f;

			if (m_cor <= 0.0f)
			{
				m_cor = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
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
// �`�揈��
//==========================
void CFade::Draw()
{
	CObject2D::Draw();
}

//==========================
//�t�F�[�h�̐ݒ菈��
//==========================
void CFade::SetFade(CScene::MODE modenext)
{
	g_modenext = modenext;
	m_fade = FADE_OUT;
}

//==========================
//�t�F�[�h�̏�Ԏ擾
//==========================
CFade::FADE CFade::GetFade()
{
	return m_fade;
}

//==========================
//����
//==========================
CFade* CFade::Create()
{
	CFade* pFade = DBG_NEW CFade;

	pFade->Init();

	pFade->SetType(CObject::FADE);

	return pFade;
}