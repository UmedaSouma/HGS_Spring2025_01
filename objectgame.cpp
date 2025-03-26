//==========================
// 
// ゲームオブジェクト[objectgame.h]
// Author Yuki Goto
//
//==========================

//include
#include"objectgame.h"

//==========================
// コンストラクタ
//==========================
CObjectgame::CObjectgame(int nPriority):CObject(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_mtxWorld);
	m_radius = 0.0f;
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

//==========================
// デストラクタ
//==========================
CObjectgame::~CObjectgame()
{

}

//==========================
// 初期設定
//==========================
HRESULT CObjectgame::Init(void)
{
	return S_OK;
}

//==========================
// 終了処理
//==========================
void CObjectgame::Uninit(void)
{

}

//==========================
// 更新処理
//==========================
void CObjectgame::Update(void)
{

}

//==========================
// 描画処理
//==========================
void CObjectgame::Draw(void)
{

}

//==========================
//位置取得
//==========================
D3DXVECTOR3& CObjectgame::GetPos(void)
{
	return m_pos;
}

//==========================
//位置設定
//==========================
void CObjectgame::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==========================
//位置取得
//==========================
D3DXVECTOR3& CObjectgame::GetRot(void)
{
	return m_rot;
}

//==========================
//位置設定
//==========================
void CObjectgame::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//==========================
//昔の位置取得
//==========================
D3DXVECTOR3& CObjectgame::GetPosOld(void)
{
	return m_posold;
}

//==========================
//昔の位置設定
//==========================
void CObjectgame::SetPosOld(D3DXVECTOR3 posord)
{
	m_posold = posord;
}

//==========================
//移動値取得
//==========================
D3DXVECTOR3& CObjectgame::GetMove(void)
{
	return m_move;
}

//==========================
//移動値設定
//==========================
void CObjectgame::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//==========================
//マトリックス取得
//==========================
D3DXMATRIX& CObjectgame::GetMtxWorld()
{
	return m_mtxWorld;
}

//==========================
//マトリックスの設定
//==========================
void CObjectgame::SetMtxWorld(D3DXMATRIX mtxWorld)
{
	m_mtxWorld = mtxWorld;
}

//==========================
//球の判定
//==========================
bool CObjectgame::ColisionSphere(D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, float myradius, float partnerradius)
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
//半径の設定
//==========================
void CObjectgame::SetRadius(float radius)
{
	m_radius = radius;
}

//==========================
//半径の取得
//==========================
float CObjectgame::GetRadius()
{
	return m_radius;
}

//==========================
//拡大率の設定
//==========================
void CObjectgame::SetScale(D3DXVECTOR3 scale)
{
	m_scale = scale;
}

//==========================
//拡大率の設定
//==========================
D3DXVECTOR3& CObjectgame::GetScale()
{
	return m_scale;
}