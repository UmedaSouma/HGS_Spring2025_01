//===========================================================================================================================================================
// 
// �u���b�N���� [create_block.cpp]
// Author : souma umeda
// 
//===========================================================================================================================================================
#include "create_block.h"
#include "block_enemy.h"
#include "manager.h"

//===========================================================================================================
// �R���X�g���N�^
//===========================================================================================================
CCreateBlock::CCreateBlock()
{
}

//===========================================================================================================
// �f�X�g���N�^
//===========================================================================================================
CCreateBlock::~CCreateBlock()
{
}

//===========================================================================================================
// �����ݒ�
//===========================================================================================================
void CCreateBlock::Init()
{
	m_nTimer = 0;
	// srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����
	
	for (int i = 0; i < MAX_V; i++)
	{
		for (int t = 0; t < MAX_H; t++)
		{
			// int r = rand() % MAX_V + 1;
			D3DXVECTOR3 pos = { 0.0f + (i * 45),-140.0f+(t * 45),0.0f };
			D3DXVECTOR3 scale = { SCALE,SCALE,1.0f };
			CBlockEnemy::Create(pos, scale);
		}
	}
}

//===========================================================================================================
// �I������
//===========================================================================================================
void CCreateBlock::Uninit()
{
}

//===========================================================================================================
// �X�V����
//===========================================================================================================
void CCreateBlock::Update()
{
	if (!CManager::GetInstance()->GetGameManager()->GetStart())
	{//�J�n���Ă���
		return;
	}

	if (m_nTimer % 600 == 0 && m_nTimer != 0)
	{
		for (int i = 0; i < MAX_V; i++)
		{
			D3DXVECTOR3 pos = { 315.0f,-140.0f + (i * 45),0.0f };

			if (i == 6)
			{
				pos.x -= 40;
			}

			D3DXVECTOR3 scale = { SCALE,SCALE,1.0f };
			CBlockEnemy::Create(pos, scale);
		}

		//�I�u�W�F�N�g���擾
		CObject* pObj = CObject::GetObj(nullptr, CBlockEnemy::PRIORITY);

		while (pObj != nullptr)
		{
			if (pObj->GetNextObj() == nullptr)
			{
				break;
			}


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

			//�{�[���̏����擾
			CBlockEnemy* pBenemy = dynamic_cast<CBlockEnemy*>(pObj);

			D3DXVECTOR3 pBEpos = pBenemy->GetPos();
			pBEpos.x -= 40.0f;
			pBenemy->SetPos(pBEpos);

			pObj = CObject::GetObj(pObj, CBlockEnemy::PRIORITY);
			// break;
		}
	}

	m_nTimer++;
}
