//==========================
// 
// ���[�V�������郂�f���̕`�揈��[motionmodel.h]
// Author Yuki Goto
//
//==========================
#ifndef _MOTIONMODEL_H_
#define _MOTIONMODEL_H_

//include
#include "objectgame.h"
#include "modelparts.h"

//�N���X�̒�`
class CMotionModel :public CObjectgame
{
public:

	//�萔
	static const int PRIORITY;//�`�揇
	static const int MAX_PARTS = 20;//�p�[�c��
	static const int MAX_KEYSET = 20;//�L�[�Z�b�g�̐�
	static const int MAX_MOTION = 10;//���[�V�����̐�

	//�L�[�f�[�^
	struct KEY
	{
		D3DXVECTOR3 pos;//�ʒu
		D3DXVECTOR3 rot;//����
	};

	//�L�[���
	struct KEYSET
	{
		int nFrame;//�t���[��
		KEY aKey[MAX_PARTS];
	};

	//���[�V�������
	struct MOTION
	{
		int Loop;//���[�v���邩
		int nKeyNum;//�L�[�̑���
		KEYSET aKeySet[MAX_KEYSET];
	};

	//���[�V�����̎��
	typedef enum
	{
		NEUTRAL = 0,//�ҋ@
		MOVE,//�ړ�
		ATTACK,//�U��
	}MOTION_TYPE;

	//�����o�֐�
	CMotionModel(int nPriority = PRIORITY);//�R���X�g���N�^
	~CMotionModel() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CMotionModel* Create();//���f������
	void LoadFile(const char name[256],D3DXVECTOR3 scale);//�t�@�C����ǂݍ���
	void SetMotion(MOTION_TYPE MotionType);//���[�V������ݒ�
private:

	//�����o�֐�
	void Motion();//���[�V��������

	//�����o�ϐ�
	CModelParts* m_PartsList[MAX_PARTS];//�p�[�c�̏��
	MOTION m_MotionInfo[MAX_MOTION];//���[�V�����̏��
	KEY m_FirstMotion[MAX_PARTS];//�ŏ��̈ʒu�ƌ���
	MOTION_TYPE m_MotionType;//���݂̃��[�V�����̎��
	int m_nCurKey;//���݂̃L�[�ԍ�
	int m_nCntMotion;//���[�V�����J�E���^�[
	int m_CurMotion;//���݂̃��[�V�����ԍ�
};
#endif 