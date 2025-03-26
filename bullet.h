//==========================
// 
// �u���b�N���󂷒e[bullet.h]
// Author Yuki Goto
//
//==========================
#ifndef _BULLET_H_
#define _BULLET_H_

//include
#include "objectX.h"

//�N���X�̒�`
class CBullet :public CObjectX
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CBullet(int nPriority = PRIORITY);//�R���X�g���N�^
	~CBullet() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
	void HitBlock();//�����蔻��
private:
	int m_nModelIdx;//���f���̔ԍ�
};
#endif