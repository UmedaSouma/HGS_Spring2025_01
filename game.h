//==========================
// 
// �Q�[����ʂ̏���[game.h]
// Author Yuki Goto
//
//==========================
#ifndef _GAME_H_
#define _GAME_H_

//include
#include"scene.h"

//�Q�[���N���X�̒�`
class CGame :public CScene
{
public:

	//�����o�֐�
	CGame();//�R���X�g���N�^
	~CGame() override;//�f�X�g���N�^
	HRESULT Init()override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
private:
};

#endif 