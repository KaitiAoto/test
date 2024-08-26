//==========================
//
//  弾発射処理[bullet.cpp]
//  Author:kaiti
//
//==========================
#include "main.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "effect.h"
//マクロ定義
#define MAX_BULLET (256)
//弾構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	int nLife;
	BULLETTYPE type;
	bool bUse;
}Bullet;
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBullet[2] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;
Bullet g_aBullet[MAX_BULLET];
//================
//弾の初期化処理
//================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sodapdf-converted.png",&g_pTextureBullet[0]);//プレイヤーの弾
	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_pTextureBullet[0]);//プレイヤーの弾

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\2143503.png", &g_pTextureBullet[1]);//敵の弾1

	//弾情報の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 100;
		g_aBullet[nCntBullet].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffBullet,
		                        NULL);
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}
//==============
//弾の終了処理
//==============
void UninitBullet(void)
{
	int nCnt;
	//テクスチャの破棄
	for (nCnt = 0; nCnt < 2; nCnt++)
	{
		if (g_pTextureBullet[nCnt] != NULL)
		{
			g_pTextureBullet[nCnt]->Release();
			g_pTextureBullet[nCnt] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
//===============
//弾の更新処理
//===============
void UpdateBullet(void)
{
	int nCntBullet;
	//頂点座標を更新
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			SetEffect(g_aBullet[nCntBullet].pos, D3DCOLOR_RGBA(255, 255, 255, 255), 30, 30.0);

			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{//プレイヤーの弾
				int nCntEnemy;
				Enemy* pEnemy;
				//敵取得
				pEnemy = GetEnemy();

				for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (   g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - 50.0f //左端
							&& g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + 50.0f //右端
							&& g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - 50.0f //上端
							&& g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + 50.0f)//下端
						{
							//敵のヒット処理
							HitEnemy(nCntEnemy, 1);
							SetExplosion(pEnemy->pos, 1.0f);
							g_aBullet[nCntBullet].bUse = false;
						}
					}
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY1)
			{//敵の弾
				Player* pPlayer;
				//プレイヤー取得
				pPlayer = GetPlayer();

				if (pPlayer->bUse == true)
				{
					if (   g_aBullet[nCntBullet].pos.x >= pPlayer->pos.x - 50.0f //左端
						&& g_aBullet[nCntBullet].pos.x <= pPlayer->pos.x + 50.0f //右端
						&& g_aBullet[nCntBullet].pos.y >= pPlayer->pos.y - 50.0f //上端
						&& g_aBullet[nCntBullet].pos.y <= pPlayer->pos.y + 50.0f)//下端
					{
						//敵のヒット処理
						//pPlayer->bUse = false;
						HitPlayer(1);
						g_aBullet[nCntBullet].bUse = false;
					}
				}
			}

			//弾の位置を更新
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30, g_aBullet[nCntBullet].pos.y - 20, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30, g_aBullet[nCntBullet].pos.y - 20, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30, g_aBullet[nCntBullet].pos.y + 20, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30, g_aBullet[nCntBullet].pos.y + 20, 0.0f);

			//弾が画面外にいった
			if (g_aBullet[nCntBullet].pos.x >= SCREEN_WIDTH || g_aBullet[nCntBullet].pos.y >= SCREEN_HEIGHT || g_aBullet[nCntBullet].pos.x <= 0 || g_aBullet[nCntBullet].pos.y <= 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}

			g_aBullet[nCntBullet].nLife -= 0.1;
			//弾の寿命
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				SetExplosion(g_aBullet[nCntBullet].pos, 1.0);
				g_aBullet[nCntBullet].bUse = false;
			}
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}
//==============
//弾の描画処理
//==============
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//テクスチャの設定
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				pDevice->SetTexture(0, g_pTextureBullet[0]);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY1)
			{
				pDevice->SetTexture(0, g_pTextureBullet[1]);
			}
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				                   nCntBullet*4,
				                   2);
		}
	}
}
//===============
//弾の設定処理
//===============
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
{
	int nCntBullet;
	//頂点座標を更新
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//弾を使用していない
			g_aBullet[nCntBullet].pos = pos;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);
			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = nLife;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].bUse = true;
			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}