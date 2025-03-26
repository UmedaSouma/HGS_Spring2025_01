//==========================
// 
// �S�[��[goal.h]
// Author Yuki Goto
//
//==========================
#ifndef _GOAL_H_
#define _GOAL_H_

//include
#include "objectX.h"

//�N���X�̒�`
class CGoal :public CObjectX
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CGoal(int nPriority = PRIORITY);//�R���X�g���N�^
	~CGoal() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CGoal* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
private:
	int m_nModelIdx;//���f���̔ԍ�
};
#endif