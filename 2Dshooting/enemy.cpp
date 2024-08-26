//===========================
//
//  敵表示処理[enemy.cpp]
//  Author:kaiti
//
//===========================
#include "main.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "fade.h"
#include "score.h"
#include "input.h"
#include "game.h"
#include "effect.h"
//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;
Enemy g_aEnemy[NUM_ENEMY];
int g_nNumEnemy = NUM_ENEMY;
//===============
//敵の初期化処理
//===============
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntENEMY;
	//デバイスの取得
	pDevice = GetDevice();

    //テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\figure_running.png", &g_apTextureEnemy[0]); //1
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\2037014.png", &g_apTextureEnemy[1]); //2 バインダー
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\2143503.png", &g_apTextureEnemy[2]);//3 消しゴム
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\figure_running.png", &g_apTextureEnemy[3]);//4 

	for (nCntENEMY = 0; nCntENEMY < NUM_ENEMY; nCntENEMY++)
	{
		//敵START
		g_aEnemy[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT/2, 0.0f);
		g_aEnemy[1].pos = D3DXVECTOR3(SCREEN_WIDTH/2, 0.0f, 0.0f);
		g_aEnemy[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0.0f);
		g_aEnemy[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT / 2, 0.0f);

		g_aEnemy[nCntENEMY].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntENEMY].nType = nCntENEMY;
		g_aEnemy[nCntENEMY].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntENEMY].nCounterState = 0;
		//弾発射間隔
		g_aEnemy[0].nCounterBullet = 60;
		g_aEnemy[1].nCounterBullet = 45;
		g_aEnemy[2].nCounterBullet = 88;
		g_aEnemy[3].nCounterBullet = 120;

		g_aEnemy[nCntENEMY].nLife = 3;
		g_aEnemy[nCntENEMY].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//対角線の長さを算出
		g_aEnemy[nCntENEMY].fLengthEnemy = sqrtf(ENEMY_WIDTH * ENEMY_WIDTH + ENEMY_HEIGTH * ENEMY_HEIGTH) / 2.0f;
		//対角線の角度を算出
		g_aEnemy[nCntENEMY].fAngleEnemy = atan2f(ENEMY_WIDTH, ENEMY_HEIGTH);
		g_aEnemy[nCntENEMY].bUse = true;
	}
	g_nNumEnemy = NUM_ENEMY;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 *NUM_ENEMY,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffEnemy,
		                        NULL);
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntENEMY = 0; nCntENEMY < NUM_ENEMY; nCntENEMY++)
	{
		//頂点座標の設定
	    pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
        pVtx[1].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
        pVtx[3].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
        pVtx[2].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		//pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntENEMY].pos.x - 50.0f, g_aEnemy[nCntENEMY].pos.y - 50.0f, 0.0f);
		//pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntENEMY].pos.x + 50.0f, g_aEnemy[nCntENEMY].pos.y - 50.0f, 0.0f);
		//pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntENEMY].pos.x - 50.0f, g_aEnemy[nCntENEMY].pos.y + 50.0f, 0.0f);
		//pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntENEMY].pos.x + 50.0f, g_aEnemy[nCntENEMY].pos.y + 50.0f, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffEnemy->Unlock();
}
//==============
//敵の終了処理
//==============
void UninitEnemy(void)
{
	int nCntENEMY;
	//テクスチャの破棄
	for (nCntENEMY = 0; nCntENEMY < NUM_ENEMY; nCntENEMY++)
	{
		if (g_apTextureEnemy[nCntENEMY] != NULL)
		{
			g_apTextureEnemy[nCntENEMY]->Release();
			g_apTextureEnemy[nCntENEMY] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}
//==========
//更新処理
//==========
void UpdateEnemy(void)
{
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	Player* pPlayer;
	pPlayer = GetPlayer();
	//使用されている敵が弾を発射する
	int nCntEnemy;
	int nCnt1 = 0;
	for (nCntEnemy=0;nCntEnemy<NUM_ENEMY;nCntEnemy++)
	{
		//SetEffect(g_aEnemy[nCntEnemy].pos, D3DCOLOR_RGBA(255, 255, 255, 255), 30, 30.0);

		if (g_aEnemy[nCntEnemy].bUse == true)
		{//敵使用時
			if (pPlayer->bUse == true)
			{//プレイヤー使用時
				//敵とプレイヤーの接触
				if (pPlayer->pos.x + 30 >= g_aEnemy[nCntEnemy].pos.x - 30.0f //左端
					&& pPlayer->pos.x - 30 <= g_aEnemy[nCntEnemy].pos.x + 30.0f //右端
					&& pPlayer->pos.y + 30 >= g_aEnemy[nCntEnemy].pos.y - 30.0f //上端
					&& pPlayer->pos.y - 30 <= g_aEnemy[nCntEnemy].pos.y + 30.0f)//下端
				{
					//敵のヒット処理
					HitEnemy(nCntEnemy, 1);
					HitPlayer(1);
				}
			}

			//位置を更新
			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
			g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;
			//移動量を更新
			//g_aEnemy[nCntEnemy].move.x += (0.0f - g_aEnemy[nCntEnemy].move.x) * 0.02f;
			//g_aEnemy[nCntEnemy].move.y += (0.0f - g_aEnemy[nCntEnemy].move.y) * 0.02f;

			pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].rot.z + (-D3DX_PI + g_aEnemy[nCntEnemy].fAngleEnemy)) * g_aEnemy[nCntEnemy].fLengthEnemy;
			pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].rot.z + (-D3DX_PI + g_aEnemy[nCntEnemy].fAngleEnemy)) * g_aEnemy[nCntEnemy].fLengthEnemy;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].rot.z + (D3DX_PI - g_aEnemy[nCntEnemy].fAngleEnemy)) * g_aEnemy[nCntEnemy].fLengthEnemy;
			pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].rot.z + (D3DX_PI - g_aEnemy[nCntEnemy].fAngleEnemy)) * g_aEnemy[nCntEnemy].fLengthEnemy;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].rot.z - g_aEnemy[nCntEnemy].fAngleEnemy) * g_aEnemy[nCntEnemy].fLengthEnemy;
			pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].rot.z - g_aEnemy[nCntEnemy].fAngleEnemy) * g_aEnemy[nCntEnemy].fLengthEnemy;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + sinf(g_aEnemy[nCntEnemy].rot.z + g_aEnemy[nCntEnemy].fAngleEnemy) * g_aEnemy[nCntEnemy].fLengthEnemy;
			pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y + cosf(g_aEnemy[nCntEnemy].rot.z + g_aEnemy[nCntEnemy].fAngleEnemy) * g_aEnemy[nCntEnemy].fLengthEnemy;
			pVtx[3].pos.z = 0.0f;


			//回転
			g_aEnemy[nCntEnemy].rot.z += 0.1;
			if (g_aEnemy[nCntEnemy].rot.z >= D3DX_PI)
			{
				g_aEnemy[nCntEnemy].rot.z = -D3DX_PI;
			}

			//敵が画面枠に当たった
			int nCnt;
			// X軸移動
			if (g_aEnemy[nCntEnemy].pos.x >= SCREEN_WIDTH)
			{
				for (nCnt = 0; nCnt < SCREEN_WIDTH; nCnt++)
				{
					g_aEnemy[nCntEnemy].move.x -= 0.005;
				}
			}
			else if (g_aEnemy[nCntEnemy].pos.x <= 0)
			{
				for (nCnt = 0; nCnt < SCREEN_WIDTH; nCnt++)
				{
					g_aEnemy[nCntEnemy].move.x += 0.005;
				}
			}
			else
			{
				g_aEnemy[nCntEnemy].move.x += 0.005;
			}
			// Y軸移動
			if (g_aEnemy[nCntEnemy].pos.y >= SCREEN_HEIGHT)
			{
				for (nCnt = 0; nCnt < SCREEN_HEIGHT; nCnt++)
				{
					g_aEnemy[nCntEnemy].move.y -= 0.005;
				}
			}
			else if (g_aEnemy[nCntEnemy].pos.y <= 0)
			{
				for (nCnt = 0; nCnt < SCREEN_HEIGHT; nCnt++)
				{
					g_aEnemy[nCntEnemy].move.y += 0.005;
				}
			}
			else
			{
				g_aEnemy[nCntEnemy].move.y += 0.005;
			}

			//弾発射
			g_aEnemy[nCntEnemy].nCounterBullet--;
			if (g_aEnemy[nCntEnemy].nCounterBullet <=0)
			{
				SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(g_aEnemy[nCntEnemy].rot.z + D3DX_PI) * 10.0f, cosf(g_aEnemy[nCntEnemy].rot.z + D3DX_PI) * 10.0f, 0.0f), 100, BULLETTYPE_ENEMY1);
				g_aEnemy[nCntEnemy].nCounterBullet = 60;
			}
			else
			{
			}

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
				break;
			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
					//ポリゴンを通常色に戻す
					VERTEX_2D* pVtx;
					//頂点バッファをロックし、頂点情報へのポインタを取得
					g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
					pVtx += 4 * nCntEnemy;
					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					//頂点バッファをアンロック
					g_pVtxBuffEnemy->Unlock();
				}
				break;
			}
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffEnemy->Unlock();
}
//==============
//敵の描画処理
//==============
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	int nCntENEMY;
	for (nCntENEMY = 0; nCntENEMY < NUM_ENEMY; nCntENEMY++)
	{
		if (g_aEnemy[nCntENEMY].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy[nCntENEMY]);
			//敵の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntENEMY * 4, 2);
		}
	}
}
//==========
//敵の設定
//==========
void SetEnemy(D3DXVECTOR3 pos, int Type)
{
	int nCntENEMY;
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntENEMY = 0; nCntENEMY < NUM_ENEMY; nCntENEMY++)
	{
		if (g_aEnemy[nCntENEMY].bUse == false)
		{
			g_aEnemy[nCntENEMY].pos = pos;

			//頂点座標の設定
			//pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntENEMY].pos.x - 50.0f, g_aEnemy[nCntENEMY].pos.y - 50.0f, 0.0f);
			//pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntENEMY].pos.x + 50.0f, g_aEnemy[nCntENEMY].pos.y - 50.0f, 0.0f);
			//pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntENEMY].pos.x - 50.0f, g_aEnemy[nCntENEMY].pos.y + 50.0f, 0.0f);
			//pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntENEMY].pos.x + 50.0f, g_aEnemy[nCntENEMY].pos.y + 50.0f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			g_aEnemy[nCntENEMY].nType = Type;
			g_aEnemy[nCntENEMY].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntENEMY].nCounterState = 0;
			g_aEnemy[nCntENEMY].nCounterBullet = 60;
			g_aEnemy[nCntENEMY].nLife = 3;
			g_aEnemy[nCntENEMY].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//対角線の長さを算出
			g_aEnemy[nCntENEMY].fLengthEnemy = sqrtf(ENEMY_WIDTH * ENEMY_WIDTH + ENEMY_HEIGTH * ENEMY_HEIGTH) / 2.0f;
			//対角線の角度を算出
			g_aEnemy[nCntENEMY].fAngleEnemy = atan2f(ENEMY_WIDTH, ENEMY_HEIGTH);

			g_aEnemy[nCntENEMY].bUse = true;

			g_nNumEnemy++;

			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffEnemy->Unlock();
}
//=========
//敵取得
//=========
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];
}
//==========
//敵の状態
//==========
void HitEnemy(int nCntEnemy, int nDamage)
{
	g_aEnemy[nCntEnemy].nLife -= nDamage;
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		//爆発の設定
		SetExplosion(g_aEnemy[nCntEnemy].pos, 1.0f);
		g_aEnemy[nCntEnemy].bUse = false;

		AddScore(111);

		g_nNumEnemy--;  //敵の総数を減らす
		if (g_nNumEnemy <= 0)
		{
			//モード設定をリザルトにする
			SetGameState(GAMESTATE_CLEAR);
		}
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;

    	VERTEX_2D* pVtx;
    	//頂点バッファをロックし、頂点情報へのポインタを取得
    	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
    	pVtx += 4 * nCntEnemy;
    
    	//頂点カラーの設定
    	pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
    	pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
    	pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
    	pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
    	//頂点バッファをアンロック
    	g_pVtxBuffEnemy->Unlock();
	}
}