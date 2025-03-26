//==========================
// 
// モーションするモデルの描画処理[motionmodel.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "motionmodel.h"
#include "manager.h"

//静的メンバ初期化
const int CMotionModel::PRIORITY = 1;//描画順

//==========================
//コンストラクタ
//==========================
CMotionModel::CMotionModel(int nPriority) :CObjectgame(nPriority)
{
	for (int i = 0; i < MAX_PARTS; i++)
	{
		m_PartsList[i] = nullptr;
		m_FirstMotion[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_FirstMotion[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	for (int i = 0; i < MAX_MOTION; i++)
	{
		m_MotionInfo[i].Loop = 0;
		m_MotionInfo[i].nKeyNum = 0;
		for (int n = 0; n < MAX_PARTS; n++)
		{
			m_MotionInfo[i].aKeySet[n].nFrame = 0;
			for (int j = 0; j < MAX_PARTS; j++)
			{
				m_MotionInfo[i].aKeySet[n].aKey[j].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_MotionInfo[i].aKeySet[n].aKey[j].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}

	m_nCurKey = 0;//現在のキー番号
	m_nCntMotion = 0;//モーションカウンター
	
}
//==========================
//デストラクタ
//==========================
CMotionModel::~CMotionModel()
{

}

//==========================
//初期化処理
//==========================
HRESULT CMotionModel::Init()
{
	SetMotion(NEUTRAL);

	return S_OK;
}

//==========================
//終了処理
//==========================
void CMotionModel::Uninit()
{
	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (m_PartsList[i] != nullptr)
		{
			m_PartsList[i]->Uninit();
			m_PartsList[i] = nullptr;
		}
	}

	Release();
}

//==========================
//更新処理
//==========================
void CMotionModel::Update()
{
	Motion();

	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (m_PartsList[i] != nullptr)
		{
			m_PartsList[i]->Update();
		}
	}

}

//==========================
//描画処理
//==========================
void CMotionModel::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	D3DXMATRIX mtxShadow;//影行列
	D3DXPLANE plane;//平面情報
	D3DXVECTOR4 vecLight;//ライト逆方向
	D3DXVECTOR3 pos, nor;//平面上の1点と法線

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&GetMtxWorld());
	D3DXMatrixIdentity(&mtxShadow);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &GetMtxWorld());

	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (m_PartsList[i] != nullptr)
		{
			m_PartsList[i]->Draw();
		}
	}
}

//==========================
//モデル生成
//==========================
CMotionModel* CMotionModel::Create()
{
	CMotionModel* pMotionModel = DBG_NEW CMotionModel;

	return pMotionModel;
}

//==========================
//モーションを設定
//==========================
void CMotionModel::SetMotion(MOTION_TYPE MotionType)
{
	if (m_MotionType == MotionType)
	{
		return;
	}

	m_MotionType = MotionType;

	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (m_PartsList[i] != nullptr)
		{
			m_FirstMotion[i].pos = m_PartsList[i]->GetPos();
			m_FirstMotion[i].rot = m_PartsList[i]->GetRot();
		}
	}

	m_nCurKey = 0;//現在のキー番号
	m_nCntMotion = 0;//モーションカウンター
}

//==========================
//モーション処理
//==========================
void CMotionModel::Motion()
{
	for (int nCntModel = 0; nCntModel < MAX_PARTS; nCntModel++)
	{
		if (m_PartsList[nCntModel] != nullptr)
		{

			//位置と向きの差分を求める
			D3DXVECTOR3 diffrot = m_MotionInfo[(int)m_MotionType].aKeySet[m_nCurKey].aKey[nCntModel].rot - m_FirstMotion[nCntModel].rot;
			D3DXVECTOR3 diffpos = m_MotionInfo[(int)m_MotionType].aKeySet[m_nCurKey].aKey[nCntModel].pos - m_FirstMotion[nCntModel].pos;

			//相対値を求める
			float Cur = (float)m_nCntMotion / m_MotionInfo[(int)m_MotionType].aKeySet[m_nCurKey].nFrame;

			//現在値を求める
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			rot.x = m_FirstMotion[nCntModel].rot.x + (diffrot.x * Cur);
			rot.y = m_FirstMotion[nCntModel].rot.y + (diffrot.y * Cur);
			rot.z = m_FirstMotion[nCntModel].rot.z + (diffrot.z * Cur);

			//向きの設定
			m_PartsList[nCntModel]->SetRot(D3DXVECTOR3(rot.x, rot.y, rot.z));

			if (!m_PartsList[nCntModel]->GetParent())
			{//親のパーツがないとき

				//現在値を求める
				pos.x = m_FirstMotion[nCntModel].pos.x + (diffpos.x * Cur);
				pos.y = m_FirstMotion[nCntModel].pos.y + (diffpos.y * Cur);
				pos.z = m_FirstMotion[nCntModel].pos.z + (diffpos.z * Cur);

				//位置の設定
				m_PartsList[nCntModel]->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
			}

		}
	}

	m_nCntMotion++;//モーションカウンターを進める

	if (m_nCntMotion == m_MotionInfo[(int)m_MotionType].aKeySet[m_nCurKey].nFrame)
	{//モーションカウンターが再生フレーム数に達した

		for (int i = 0; i < MAX_PARTS; i++)
		{
			if (m_PartsList[i] != nullptr)
			{
				m_FirstMotion[i].pos = m_PartsList[i]->GetPos();
				m_FirstMotion[i].rot = m_PartsList[i]->GetRot();
			}
		}

		m_nCurKey++;//現在のキー番号を進める
		m_nCntMotion = 0;//カウンターを初期化
		if (m_nCurKey == m_MotionInfo[(int)m_MotionType].nKeyNum)
		{//現在のキー番号がキーの総数になった
			m_nCurKey = 0;//現在のキー番号を0に戻す

			if (m_MotionInfo[(int)m_MotionType].Loop == 0)
			{//現在のモーションがループしないとき
				SetMotion(NEUTRAL);
			}
		}
	}
}

//==========================
//ファイルを読み込む
//==========================
void CMotionModel::LoadFile(const char name[256], D3DXVECTOR3 scale)
{
	ifstream inputfile(name);//テキストファイルを開く

	string Data;
	char FileName[256];//モデルのファイルパス
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向き
	int Index = 0;//モデルの番号
	int Parent = 0;//親の番号
	int ModelNum = 0;//モデルの数
	int ModelPartsNum[20];//モデルパーツの番号
	int CountParts = 0;//パーツの情報を読み込んだ回数
	int motionCount = 0;//モーションの数
	int KeySetCount = 0;//キーセットの数
	int KeyCount = 0;//キーの数
	float Radius = 0.0f;//当たり判定の半径

	if (!inputfile)
	{
		return;
	}

	while (1)
	{
		getline(inputfile, Data);

		//モデル数
		if (Data.find("モデル数") != string::npos)
		{
			getline(inputfile, Data);
			inputfile >> Data;
			inputfile >> Data;
			inputfile >> ModelNum;
		}

		//モデルファイル
		if (Data.find("モデルファイル名") != string::npos)
		{
			CModel* pModel = CManager::GetInstance()->GetModel();
			for (int i = 0; i < ModelNum; i++)
			{
				getline(inputfile, Data, '=');
				inputfile >> FileName;
				ModelPartsNum[i] = pModel->Regist(FileName);
			}
		}

		//キャラクター情報
		if (Data.find("PARTSSET") != string::npos)
		{
			while (getline(inputfile, Data, '='))//情報を読み込む
			{
				if (Data.find("INDEX") != string::npos)
				{
					inputfile >> Index;
				}
				if (Data.find("PARENT") != string::npos)
				{
					inputfile >> Parent;
				}
				if (Data.find("POS") != string::npos)
				{
					inputfile >> pos.x;
					inputfile >> pos.y;
					inputfile >> pos.z;
				}
				if (Data.find("ROT") != string::npos)
				{
					inputfile >> rot.x;
					inputfile >> rot.y;
					inputfile >> rot.z;
					inputfile >> Data;

					if (Data.find("END_PARTSSET") != string::npos)
					{
						if (Parent == -1)
						{
							m_PartsList[CountParts] = CModelParts::Create(pos, rot, nullptr, ModelPartsNum[CountParts], scale);
						}
						else
						{
							m_PartsList[CountParts] = CModelParts::Create(pos, rot, m_PartsList[Parent], ModelPartsNum[CountParts], scale);
						}

						CountParts++;
						Data.clear();
						break;
					}
				}
			}
		}

		////当たり判定の情報
		//if (Data.find("COLLISIONSET") != string::npos)
		//{
		//	while (getline(inputfile, Data, '='))//情報を読み込む
		//	{
		//		if (Data.find("INDEX") != string::npos)
		//		{
		//			inputfile >> Index;
		//		}
		//		if (Data.find("PARENT") != string::npos)
		//		{
		//			inputfile >> Parent;
		//		}
		//		if (Data.find("POS") != string::npos)
		//		{
		//			inputfile >> pos.x;
		//			inputfile >> pos.y;
		//			inputfile >> pos.z;
		//		}
		//		if (Data.find("RADIUS") != string::npos)
		//		{
		//			inputfile >> Radius;
		//			break;
		//		}
		//	}
		//	getline(inputfile, Data);
		//	if (Data.find("END_COLLISIONSET") != string::npos)
		//	{
		//		m_PartsList[Index]->CreateVisual(pos, Radius);
		//	}
		//}

		//モーション情報
		if (Data.find("MOTIONSET") != string::npos)
		{
			while (getline(inputfile, Data, '='))//情報を読み込む
			{
				if (Data.find("LOOP") != string::npos)
				{
					inputfile >> m_MotionInfo[motionCount].Loop;
				}
				if (Data.find("NUM_KEY") != string::npos)
				{
					inputfile >> m_MotionInfo[motionCount].nKeyNum;
					break;
				}
			}
			while (getline(inputfile, Data))//情報を読み込む
			{
				if (Data.find("KEYSET") != string::npos)
				{
					while (getline(inputfile, Data, '='))//情報を読み込む
					{
						if (Data.find("FRAME") != string::npos)
						{
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].nFrame;
							break;
						}
					}
				}

				if (Data.find("KEY") != string::npos)
				{
					while (getline(inputfile, Data, '='))//情報を読み込む
					{
						if (Data.find("POS") != string::npos)
						{
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].aKey[KeyCount].pos.x;
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].aKey[KeyCount].pos.y;
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].aKey[KeyCount].pos.z;
						}
						if (Data.find("ROT") != string::npos)
						{
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].aKey[KeyCount].rot.x;
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].aKey[KeyCount].rot.y;
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].aKey[KeyCount].rot.z;
							KeyCount++;
							getline(inputfile, Data);
							getline(inputfile, Data);
							getline(inputfile, Data);
							if (Data.find("END_KEYSET") != string::npos)
							{
								KeySetCount++;
								KeyCount = 0;
							}
							break;
						}
					}
				}
				if (Data.find("END_MOTIONSET") != string::npos)
				{
					KeySetCount = 0;
					motionCount++;
					break;
				}
			}
		}

		if (Data.find("END_SCRIPT") != string::npos)
		{
			break;
		}
	}

	inputfile.close();//ファイルを閉じる

}