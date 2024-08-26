//==============================
//
//  スコア処理[score.cpp]
//  Author:kaiti
//
//==============================
#include "score.h"
//マクロ定義
#define MAX_SCORE (8)
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;
D3DXVECTOR3 g_posScore;
int g_nScore;
//=============
//初期化処理
//=============
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number000.png", &g_pTextureScore); //1

	g_posScore = D3DXVECTOR3(850.0f,0.0f,0.0f);
	g_nScore = 0;

	//頂点バッファの生成・頂点情報の設定
	VERTEX_2D* pVtx;
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffScore,
		                        NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	int nCnt;
	for (nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x + (50 * nCnt), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + (50 * (nCnt + 1)), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x + (50 * nCnt), 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + (50 * (nCnt + 1)), 100.0f, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();
}
//==========
//終了処理
//==========
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}

}
//==========
//更新処理
//==========
void UpdateScore(void)
{

}
//===========
//描画処理
//===========
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));
	
	int nCnt;
	for (nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureScore);
		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt*4, 2);
	}
}
//=================
//スコアの設定
//=================
void SetScore(int nScore)
{
	int aPosTexU[MAX_SCORE]; //桁数分
	g_nScore = nScore;

	int nData = 100000000;
	int nData2 = 10000000;
	int nCnt;
	for (nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		aPosTexU[nCnt] = g_nScore % nData / nData2;
		nData /= 10;
		nData2 /= 10;
	}

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] / 10), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] / 10) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] / 10), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] / 10) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();
}
//==================
//スコアの加算処理
//==================
void AddScore(int nValue)
{
	int aPosTexU[MAX_SCORE];
	g_nScore += nValue;

	int nData = 100000000;
	int nData2 = 10000000;
	int nCnt;
	for (nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		aPosTexU[nCnt] = g_nScore % nData / nData2;
		nData /= 10;
		nData2 /= 10;
	}

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((aPosTexU[nCnt] / 10), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCnt] / 10) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aPosTexU[nCnt] / 10), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCnt] / 10) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();
 }