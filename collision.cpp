//==========================
// 
// 当たり判定[collision.cpp]
// Author Yuki Goto
//
//==========================

//inlude
#include"collision.h"

//==========================
//コンストラクタ
//==========================
CCollision::CCollision()
{

}

//==========================
//デストラクタ
//==========================
CCollision::~CCollision()
{

}

//==========================
//球の判定
//==========================
bool CCollision::Sphere(D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, float myradius, float partnerradius)
{
	D3DXVECTOR3 DisPos = D3DXVECTOR3(mypos.x - partnerpos.x, mypos.y - partnerpos.y, mypos.z - partnerpos.z);
	float Distance = sqrtf((DisPos.x * DisPos.x) + (DisPos.y * DisPos.y) + (DisPos.z * DisPos.z));

	if (Distance < myradius + partnerradius)
	{
		return true;
	}

	return false;
}

//==========================
//矩形の左
//==========================
bool CCollision::RectangleLeft(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin)
{
	if (posold.x + myvtxmax.x <= partnerpos.x + partnervtxmin.x
		&& mypos.x + myvtxmax.x > partnerpos.x + partnervtxmin.x
		&& mypos.y + myvtxmin.y < partnerpos.y + partnervtxmax.y
		&& mypos.y + myvtxmax.y > partnerpos.y + partnervtxmin.y)
	{
		return true;
	}

	return false;
}

//==========================
//矩形の右
//==========================
bool CCollision::RectangleRight(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin)
{
	if (posold.x - myvtxmax.x >= partnerpos.x + partnervtxmax.x
		&& mypos.x - myvtxmax.x < partnerpos.x + partnervtxmax.x
		&& mypos.z - myvtxmin.z < partnerpos.z + partnervtxmax.z
		&& mypos.z + myvtxmax.z > partnerpos.z + partnervtxmin.z)
	{//右
		return true;
	}

	return false;
}

//==========================
//矩形の奥
//==========================
bool CCollision::RectangletBack(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin)
{

	if (posold.z - myvtxmin.z >= partnerpos.z + partnervtxmax.z
		&& mypos.z - myvtxmin.z < partnerpos.z + partnervtxmax.z
		&& mypos.x - myvtxmin.x < partnerpos.x + partnervtxmax.x
		&& mypos.x + myvtxmax.x > partnerpos.x + partnervtxmin.x)
	{//奥
		return true;
	}

	return false;
}

//==========================
//矩形の正面
//==========================
bool CCollision::RectangleFront(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin)
{
	if (posold.z + myvtxmax.z <= partnerpos.z + partnervtxmin.z
		&& mypos.z + myvtxmax.z > partnerpos.z + partnervtxmin.z
		&& mypos.x - myvtxmin.x < partnerpos.x + partnervtxmax.x
		&& mypos.x + myvtxmax.x > partnerpos.x + partnervtxmin.x)
	{//手前
		return true;
	}

	return false;

}