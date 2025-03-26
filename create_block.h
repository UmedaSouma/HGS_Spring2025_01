#pragma once
//===========================================================================================================================================================
// 
// create_block.cppのヘッダー [create_block.h]
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
	void Init();	// 初期設定
	void Uninit();	// 終了処理
	void Update();
private:
	unsigned int m_nTimer;
	const int MAX_V = 7;
	const int MAX_H = 7;
};

#endif // !CREATE_BLOCK_H_