//==========================
// 
// �v���C���[�̈ʒu[palyerposui.h]
// Author Yuki Goto
//
//==========================
#ifndef _PLAYERPOSUI_H_
#define _PLAYERPOSUI_H_

//include
#include "object3D.h"

//�N���X�̒�`
class CPlayerposUI :public CObject3D
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CPlayerposUI(int nPriority = PRIORITY);//�R���X�g���N�^
	~CPlayerposUI() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CPlayerposUI* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//�I�u�W�F�N�g����
private:
	int m_nTexIdx;//�e�N�X�`���̔ԍ�
};
#endif