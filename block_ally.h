#pragma once
//==========================
// 
// �����u���b�N[block_ally.h]
// Author Soma Umeda
//
//==========================
#ifndef _BLOCK_ALLY_H_
#define _BLOCK_ALLY_H_

//include
#include "block.h"

//�N���X�̒�`
class CBlockAlly :public CBlock
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CBlockAlly(int nPriority = PRIORITY);//�R���X�g���N�^
	~CBlockAlly() override;		//�f�X�g���N�^
	HRESULT Init() override;	//����������
	void Uninit() override;		//�I������
	void Update() override;		//�X�V����
	void Draw() override;		//�`�揈��
	void Hit() override;		//����������
	static CBlockAlly* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
private:
	int m_nModelIdx;//�e�N�X�`���̔ԍ�
};
#endif