//==========================
// 
// カメラ処理[camera.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"camera.h"
#include"manager.h"

//静的メンバ変数初期化
const float CCamera::Y_DISTANCE = 10.0f;//距離
const float CCamera::Z_DISTANCE = -450.0f;//距離
//==========================
// コンストラクタ
//==========================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, Y_DISTANCE, Z_DISTANCE);//視点
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//注視点
	m_targetposV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;//目的の視点
	m_targetposR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//目的の注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//上方向
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向き
	m_PosVY = 0.0f;
	m_PosRY = 0.0f;
	m_nFlame = 0;
	m_fShapeScale = 0;
}

//==========================
// デストラクタ
//==========================
CCamera::~CCamera()
{

}

//==========================
// 初期設定
//==========================
HRESULT CCamera::Init()
{
	m_posV = D3DXVECTOR3(0.0f, Y_DISTANCE, Z_DISTANCE);//視点
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//上方向
	m_targetposV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;//目的の視点
	m_targetposR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//目的の注視点
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向き
	m_PosVY = 0.0f;
	m_PosRY = 0.0f;
	m_nFlame = 0;
	m_fShapeScale = 0;

	return S_OK;
}

//==========================
// 終了処理
//==========================
void CCamera::Uninit()
{

}

//==========================
// 更新処理
//==========================
void CCamera::Update()
{
#ifdef _DEBUG
	//入力処理
	Input();
#endif

	m_posR.x += (m_targetposR.x - m_posR.x) * 0.25f;
	m_posV.x += (m_targetposV.x - m_posV.x) * 0.25f;

	/*m_posR.y += (m_targetposR.y - m_posR.y) * 0.25f;
	m_posV.y += (m_targetposV.y - m_posV.y) * 0.25f;*/

}

#define PLOJECTION (1)//シーン切り替え
//==========================
// カメラの設定
//==========================
void CCamera::SetCamera()
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

#if PLOJECTION
	//プロジェクションマトリックスを作成(遠近投影)
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),							//視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		//画面のアスペクト比
		10.0f,											//Z値の最小値
		1000.0f);										//Z値の最大値

#else

	D3DXMATRIX MatScale;

	//プロジェクションマトリックスを作成(平行投影)
	D3DXMatrixOrthoLH(&m_mtxProjection,
		(float)SCREEN_HEIGHT,
		(float)SCREEN_WIDTH,
		10.0f,
		1000.0f);
	D3DXMatrixIdentity(&MatScale);
	D3DXMatrixScaling(&MatScale, 1.0f, 5.0f, 1.0f);
	D3DXMatrixMultiply(&m_mtxProjection, &m_mtxProjection, &MatScale);
#endif



	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	D3DXVECTOR3 adjust = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_nFlame > 0)
	{
		m_nFlame--;
		random_device rnd;
		adjust.x = (float)(rnd() % m_fShapeScale);
		adjust.y = (float)(rnd() % m_fShapeScale);
	}

	D3DXVECTOR3 posV = m_posV + adjust;
	D3DXVECTOR3 posR = m_posR + adjust;

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&posV,						//視点
		&posR,						//注視点
		&m_vecU);					//上方向ベクトル

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

}

//==========================
//カメラ揺れ設定
//==========================
void CCamera::SetShape(int flame, int scale)
{
	m_nFlame = flame;
	m_fShapeScale = scale;
}

//==========================
//カメラの移動
//==========================
void CCamera::Move(D3DXVECTOR3 pos)
{
	m_targetposR.x = pos.x;
	m_targetposR.z = pos.z;

	m_targetposV.x = pos.x;
	m_targetposV.z = pos.z + Z_DISTANCE;
}

//==========================
//カメラの縦移動
//==========================
void CCamera::VerticalMove(D3DXVECTOR3 pos)
{
	m_posR.y = pos.y;
	m_posR.z = pos.z;

	m_posV.y = pos.y + Y_DISTANCE;
	m_posV.z = pos.z + Z_DISTANCE;
}

//==========================
//注視点の取得
//==========================
D3DXVECTOR3& CCamera::GetPosR()
{
	return m_posR;
}

//==========================
//インゲーム以外のカメラ
//==========================
void CCamera::OutGame(D3DXVECTOR3 pos)
{
	m_posV.y = pos.y;
	m_posR.y = pos.y;
}

//==========================
// カメラの入力処理
//==========================
void CCamera::Input(void)
{
	//カメラの平行移動
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_H))
	{
		if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_T))
		{
			m_posV.x += sinf(m_rot.y * D3DX_PI + 2.355f) * 2.0f;
			m_posV.z += cosf(m_rot.y * D3DX_PI + 2.355f) * 2.0f;
			m_posR.x += sinf(m_rot.y * D3DX_PI + 2.355f) * 2.0f;
			m_posR.z += cosf(m_rot.y * D3DX_PI + 2.355f) * 2.0f;
		}
		else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_G))
		{
			m_posV.x += sinf(m_rot.y * D3DX_PI + 0.785f) * 2.0f;
			m_posV.z += cosf(m_rot.y * D3DX_PI + 0.785f) * 2.0f;
			m_posR.x += sinf(m_rot.y * D3DX_PI + 0.785f) * 2.0f;
			m_posR.z += cosf(m_rot.y * D3DX_PI + 0.785f) * 2.0f;
		}
		else
		{
			m_posV.x += sinf(m_rot.y * D3DX_PI + 1.57f) * 2.0f;
			m_posV.z += cosf(m_rot.y * D3DX_PI + 1.57f) * 2.0f;
			m_posR.x += sinf(m_rot.y * D3DX_PI + 1.57f) * 2.0f;
			m_posR.z += cosf(m_rot.y * D3DX_PI + 1.57f) * 2.0f;
		}
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_F))
	{
		if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_T))
		{
			m_posV.x += sinf(m_rot.y * D3DX_PI - 2.355f) * 2.0f;
			m_posV.z += cosf(m_rot.y * D3DX_PI - 2.355f) * 2.0f;
			m_posR.x += sinf(m_rot.y * D3DX_PI - 2.355f) * 2.0f;
			m_posR.z += cosf(m_rot.y * D3DX_PI - 2.355f) * 2.0f;
		}
		else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_G))
		{
			m_posV.x += sinf(m_rot.y * D3DX_PI - 0.785f) * 2.0f;
			m_posV.z += cosf(m_rot.y * D3DX_PI - 0.785f) * 2.0f;
			m_posR.x += sinf(m_rot.y * D3DX_PI - 0.785f) * 2.0f;
			m_posR.z += cosf(m_rot.y * D3DX_PI - 0.785f) * 2.0f;
		}
		else
		{
			m_posV.x += sinf(m_rot.y * D3DX_PI - 1.57f) * 2.0f;
			m_posV.z += cosf(m_rot.y * D3DX_PI - 1.57f) * 2.0f;
			m_posR.x += sinf(m_rot.y * D3DX_PI - 1.57f) * 2.0f;
			m_posR.z += cosf(m_rot.y * D3DX_PI - 1.57f) * 2.0f;
		}
	}
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_T))
	{
		m_PosRY += 1.0f;
		m_posR.y = 0.0f + m_PosRY;

		m_PosVY += 1.0f;
		m_posV.y = Y_DISTANCE + m_PosVY;
	}
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_G))
	{
		m_PosRY -= 1.0f;
		m_posR.y = 0.0f + m_PosRY;

		m_PosVY -= 1.0f;
		
		m_posV.y = Y_DISTANCE + m_PosVY;
	}

	/*else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
	{
		m_posV.x += sinf(m_rot.y * D3DX_PI) * -2.0f;
		m_posV.z += cosf(m_rot.y * D3DX_PI) * -2.0f;
		m_posR.x += sinf(m_rot.y * D3DX_PI) * -2.0f;
		m_posR.z += cosf(m_rot.y * D3DX_PI) * -2.0f;
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
	{
		m_posV.x += sinf(m_rot.y * D3DX_PI) * 2.0f;
		m_posV.z += cosf(m_rot.y * D3DX_PI) * 2.0f;
		m_posR.x += sinf(m_rot.y * D3DX_PI) * 2.0f;
		m_posR.z += cosf(m_rot.y * D3DX_PI) * 2.0f;
	}*/

	////視点操作
	//if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_Z))
	//{
	//	m_rot.y += 0.02f;
	//	m_posV.x = m_posR.x + (sinf(m_rot.y * D3DX_PI) * Z_DISTANCE);
	//	m_posV.z = m_posR.z + (cosf(m_rot.y * D3DX_PI) * Z_DISTANCE);
	//}
	//else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_C))
	//{
	//	m_rot.y -= 0.02f;
	//	m_posV.x = m_posR.x + (sinf(m_rot.y * D3DX_PI) * Z_DISTANCE);
	//	m_posV.z = m_posR.z + (cosf(m_rot.y * D3DX_PI) * Z_DISTANCE);
	//}
	//else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_Y))
	//{
	//	m_PosVY += 1.0f;
	//	m_posV.x = m_posR.x + (sinf(m_rot.y * D3DX_PI) * Z_DISTANCE);
	//	m_posV.y = Y_DISTANCE + m_PosVY;
	//	m_posV.z = m_posR.z + (cosf(m_rot.y * D3DX_PI) * Z_DISTANCE);
	//}
	//else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_N))
	//{
	//	m_PosVY -= 1.0f;
	//	m_posV.x = m_posR.x + (sinf(m_rot.y * D3DX_PI) * Z_DISTANCE);
	//	m_posV.y = Y_DISTANCE + m_PosVY;
	//	m_posV.z = m_posR.z + (cosf(m_rot.y * D3DX_PI) * Z_DISTANCE);
	//}

	////注視点操作
	//if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_T))
	//{
	//	m_PosRY += 2.0f;
	//	m_posR.y = 0.0f + m_PosRY;
	//}
	//else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_B))
	//{
	//	m_PosRY -= 2.0f;
	//	m_posR.y = 0.0f + m_PosRY;
	//}
	//else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_Q))
	//{
	//	m_rot.y -= 0.02f;
	//	m_posR.x = m_posV.x - (sinf(m_rot.y * D3DX_PI) * Z_DISTANCE);
	//	m_posR.z = m_posV.z - (cosf(m_rot.y * D3DX_PI) * Z_DISTANCE);
	//}
	//else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_E))
	//{
	//	m_rot.y += 0.02f;
	//	m_posR.x = m_posV.x - (sinf(m_rot.y * D3DX_PI) * Z_DISTANCE);
	//	m_posR.z = m_posV.z - (cosf(m_rot.y * D3DX_PI) * Z_DISTANCE);
	//}

}