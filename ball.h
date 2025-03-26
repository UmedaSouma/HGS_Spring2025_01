//==========================
// 
// �{�[��[ball.h]
// Author Yuki Goto
//
//==========================
#ifndef _BALL_H_
#define _BALL_H_

//include
#include "objectX.h"

//�N���X�̒�`
class CBall :public CObjectX
{
public:
	//�萔
	static const int PRIORITY;//�`�揇
	static const int MAXLIFE = 3;//���C�t

	//�����o�֐�
	CBall(int nPriority = PRIORITY);//�R���X�g���N�^
	~CBall() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CBall* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
	void SubLife();//���������炷
private:

	void Reset();//�ʒu������
	
	int m_nModelIdx;//���f���̔ԍ�
	int m_Life;//���C�t
};
#endif