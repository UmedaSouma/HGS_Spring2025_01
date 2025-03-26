//==========================
// 
// �u���b�N���󂷒e[bullet.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "bullet.h"
#include "manager.h"
#include "model.h"
#include "block_enemy.h"
#include "player.h"

//�ÓI�����o������
const int CBullet::PRIORITY = 1;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CBullet::CBullet(int nPriority) :
	CObjectX(nPriority),//���R���X�g���N�^
	m_nModelIdx(0)//���f���̔ԍ�
{

}

//==========================
//�f�X�g���N�^
//==========================
CBullet::~CBullet()
{

}

//==========================
//����������
//==========================
HRESULT CBullet::Init()
{
	//�T�C�Y�ݒ�
	//SetSize();

	//�����ݒ�
	CObjectX::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void  CBullet::Uninit()
{
	//�I������
	CObjectX::Uninit();

	Release();
}

//==========================
//�X�V����
//==========================
void CBullet::Update()
{
	//�X�V����
	CObjectX::Update();

	SetPosOld(GetPos());
	SetPos(GetMove() + GetPos());

	HitBlock();

	if (GetPos().z > 50.0f)
	{
		Uninit();
	}
}

//==========================
//�`�揈��
//==========================
void CBullet::Draw()
{
	//�`�揈��
	CObjectX::Draw();
}

//==========================
//�I�u�W�F�N�g����
//==========================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move)
{
	//�C���X�^���X����
	CBullet* pBullet = DBG_NEW CBullet;

	//�ʒu�̐ݒ�
	pBullet->SetPos(pos);

	//�X�P�[���̐ݒ�
	pBullet->SetScale(scale);

	// �ړ��ʂ̐ݒ�
	pBullet->SetMove(move);

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBullet->m_nModelIdx = pModel->Regist("data\\MODEL\\ball.x");
	pBullet->BindModel(pModel->GetMeshAdress(pBullet->m_nModelIdx),
		pModel->GetBuffMatAdress(pBullet->m_nModelIdx),
		pModel->GetNumMatAdress(pBullet->m_nModelIdx),
		pModel->GetTexIdx(pBullet->m_nModelIdx));

	//����������
	pBullet->Init();

	return pBullet;
}

//==========================
//�����蔻��
//==========================
void CBullet::HitBlock()
{
	//�I�u�W�F�N�g���擾
	CObject* pObj = CObject::GetObj(nullptr, CBlockEnemy::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj = CObject::GetObj(pObj, CBlockEnemy::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMYBLOCK)
		{//�I�u�W�F�N�g���G�ł͂Ȃ�
			pObj = CObject::GetObj(pObj, CBlockEnemy::PRIORITY);
			continue;
		}

		//�G�u���b�N�̏����擾
		CBlockEnemy* pBlockEnemy = dynamic_cast<CBlockEnemy*>(pObj);

		if (GetPos().x  <= pBlockEnemy->GetPos().x + pBlockEnemy->GetVtxMax().x
			&& GetPos().x  > pBlockEnemy->GetPos().x + pBlockEnemy->GetVtxMin().x
			&& GetPos().y  < pBlockEnemy->GetPos().y + pBlockEnemy->GetVtxMax().y
			&& GetPos().y  > pBlockEnemy->GetPos().y + pBlockEnemy->GetVtxMin().y
			&& GetPos().z  < pBlockEnemy->GetPos().z + pBlockEnemy->GetVtxMax().z
			&& GetPos().z  > pBlockEnemy->GetPos().z + pBlockEnemy->GetVtxMin().z)
		{
			pBlockEnemy->Uninit();
			Uninit();

			//�I�u�W�F�N�g���擾
			CObject* pObj2 = CObject::GetObj(nullptr, CPlayer::PRIORITY);
			CPlayer* pplayer = nullptr;

			while (pObj2 != nullptr)
			{
				if (pObj2 == nullptr)
				{//�I�u�W�F�N�g���Ȃ�
					pObj2 = CObject::GetObj(pObj2, CPlayer::PRIORITY);
					continue;
				}

				//��ނ̎擾
				CObject::TYPE type = pObj2->GetType();

				if (type != CObject::TYPE::PLAYER)
				{//�I�u�W�F�N�g���G�ł͂Ȃ�
					pObj2 = CObject::GetObj(pObj2, CPlayer::PRIORITY);
					continue;
				}

				//�{�[���̏����擾
				pplayer = dynamic_cast<CPlayer*>(pObj2);
				pplayer->CountBreak();
				break;
			}

		}

		pObj = CObject::GetObj(pObj, CBlockEnemy::PRIORITY);
	}
}

//===========================================================================================================
// �{�[���̏����擾
//===========================================================================================================
void CBullet::GetPlayerInfo()
{
	//�I�u�W�F�N�g���擾
	CObject* pObj2 = CObject::GetObj(nullptr, CPlayer::PRIORITY);
	CPlayer* pplayer = nullptr;

	while (pObj2 != nullptr)
	{
		if (pObj2 == nullptr)
		{//�I�u�W�F�N�g���Ȃ�
			pObj2 = CObject::GetObj(pObj2, CPlayer::PRIORITY);
			continue;
		}

		//��ނ̎擾
		CObject::TYPE type = pObj2->GetType();

		if (type != CObject::TYPE::BALL)
		{//�I�u�W�F�N�g���G�ł͂Ȃ�
			pObj2 = CObject::GetObj(pObj2, CPlayer::PRIORITY);
			continue;
		}

		//�{�[���̏����擾
		pplayer = dynamic_cast<CPlayer*>(pObj2);

		break;
	}
}