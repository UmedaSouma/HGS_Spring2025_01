//==========================
// 
// �Q�[����ʂ̏���[game.h]
// Author Yuki Goto
//
//==========================
#ifndef _GAME_TEST_01_H_
#define _GAME_TEST_01_H_

//include
#include"scene.h"

//�Q�[���N���X�̒�`
class CGameTest01 :public CScene
{
public:

	//�����o�֐�
	CGameTest01();//�R���X�g���N�^
	~CGameTest01() override;//�f�X�g���N�^
	HRESULT Init()override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
private:
};

#endif 