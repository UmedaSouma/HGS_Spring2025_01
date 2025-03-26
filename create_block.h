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

class CreateBlock
{
public:
	CreateBlock();
	~CreateBlock();
	void Init();	// 初期設定
	void Uninit();	// 終了処理
	void Update();
private:

};

#endif // !CREATE_BLOCK_H_