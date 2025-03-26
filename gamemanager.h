//==========================
// 
// [gamemanager.h]
// Author Yuki Goto
//
//==========================
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

//�N���X�̒�`
class CGameManager
{
public:
	//�萔
	static const int PRIORITY;

	//�����o�֐�
	CGameManager();//�R���X�g���N�^
	~CGameManager();//�f�X�g���N�^
	bool GetGame();//�N���A������擾
	void SetGame();//�N���A�����ݒ�
	bool GetEnd();//�I��������擾
	void SetEnd();//�I�������ݒ�
	void reset();//��񃊃Z�b�g
private:
	bool m_Game;//�N���A����
	bool m_End;//�I������
};

#endif 
