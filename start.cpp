//==========================
// 
// �^�C�g�����S[Start.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"start.h"
#include"manager.h"

//�ÓI�����o�̏�����
const int CStart::PRIORITY = 4;//�`��D��x
int  CStart::m_nTexIdx = 0;//�e�N�X�`��ID
//========================
//�R���X�g���N�^
//========================
CStart::CStart(int nPriority) :CObject2D(nPriority)
{

}

//========================
//�f�X�g���N�^
//========================
CStart::~CStart()
{

}

//========================
//�����ݒ�
//========================
HRESULT CStart::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//�I������
//========================
void CStart::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//�X�V����
//========================
void CStart::Update()
{
	CObject2D::Update();
}

//========================
//�`�揈��
//========================
void CStart::Draw()
{
	if (CManager::GetInstance()->GetGameManager()->GetStart())
	{//�J�n���Ă���
		return;
	}

	CObject2D::Draw();
}

//========================
//�I�u�W�F�N�g2D����
//========================
CStart* CStart::Create(D3DXVECTOR3 pos)
{
	//�C���X�^���X����
	CStart* pStart = DBG_NEW CStart;

	//�e�N�X�`���ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pStart->m_nTexIdx = pTex->Regist("data\\TEXTURE\\ui.png");
	pStart->BindTexture(pTex->GetAdress(pStart->m_nTexIdx));

	//�ʒu�̐ݒ�
	pStart->SetPos(pos);

	//�T�C�Y�ݒ�
	pStart->SetSize(100.0f, 350.0f);

	//�F��ݒ�
	//pStart->SetCor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�����ݒ�
	pStart->Init();

	return pStart;
}