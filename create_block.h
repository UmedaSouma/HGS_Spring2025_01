#pragma once
//===========================================================================================================================================================
// 
// create_block.cpp�̃w�b�_�[ [create_block.h]
// Author : souma umeda
// 
//===========================================================================================================================================================
#ifndef _CREATE_BLOCK_H_
#define _CREATE_BLOCK_H_
#include "main.h"

class CCreateBlock
{
public:
	CCreateBlock();
	~CCreateBlock();
	void Init();	// �����ݒ�
	void Uninit();	// �I������
	void Update();
private:
	unsigned int m_nTimer;
	const int MAX_V = 7;
	const int MAX_H = 7;
};

#endif // !CREATE_BLOCK_H_