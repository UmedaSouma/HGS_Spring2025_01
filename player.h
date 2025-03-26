//==========================
// 
// �v���C���[����[player.h]
// Author Yuki Goto
//
//==========================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "objectgame.h"

//�N���X�̒�`
class CPlayer :public CObjectgame
{
public:
	//�����o�֐�
	CPlayer(int nPriority = PRIORITY);//�R���X�g���N�^
	~CPlayer() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	void Operation();	// ����
	void OpeMove();		// �ړ�����
	void OpeBullet();
	static CPlayer* Create(D3DXVECTOR3 pos);//�I�u�W�F�N�g����
private:
};
#endif