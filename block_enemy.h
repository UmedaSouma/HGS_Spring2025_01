#pragma once
//==========================
// 
// �����u���b�N[block_ally.h]
// Author Soma Umeda
//
//==========================
#ifndef _BLOCK_ENEMY_H_
#define _BLOCK_ENEMY_H_

//include
#include "block.h"
#include "ball.h"

//�N���X�̒�`
class CBlockEnemy :public CBlock
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CBlockEnemy(int nPriority = PRIORITY);//�R���X�g���N�^
	~CBlockEnemy() override;	//�f�X�g���N�^
	HRESULT Init() override;	//����������
	void Uninit() override;		//�I������
	void Update() override;		//�X�V����
	void Draw() override;		//�`�揈��
	void Hit() override;		//����������
	static CBlockEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
private:
	void GetBallInfo();//�{�[���̏����擾

	//�����o�ϐ�
	int m_nModelIdx;//�e�N�X�`���̔ԍ�
	CBall* m_ball;//�{�[���̏��
};
#endif