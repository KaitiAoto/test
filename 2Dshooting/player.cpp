//===================================
//
//  プレイヤー表示処理[player.cpp]
//  Author:kaiti
//
//===================================
#include "main.h"
#include "player.h"
#include "background.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "fade.h"
#include "game.h"
#include "result.h"
#include "effect.h"
//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;
Player g_player;
//========================
//プレイヤーの初期化処理
//========================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	//1つ目
	//テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\runningman100.png",&g_pTexturePlayer);

	D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\2006960.png",&g_pTexturePlayer);

	g_player.nCounterAnimPlayer = 0;
	g_player.nPatternAnimPlayer = 0;

	g_player.pos = D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.state = PLAYERSTATE_NORMAL;
	//対角線の長さを算出
	g_player.fLengthPlayer = sqrtf(PLAYER_WIDTH * PLAYER_WIDTH + PLAYER_HEIGTH * PLAYER_HEIGTH) / 2.0f;
	//対角線の角度を算出
	g_player.fAnglePlayer = atan2f(PLAYER_WIDTH, PLAYER_HEIGTH);
	g_player.nLife = 3;
	g_player.bUse = true;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffPlayer,
		                        NULL);
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	//pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - 50.0f, g_player.pos.y - 50.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + 50.0f, g_player.pos.y - 50.0f, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - 50.0f, g_player.pos.y + 50.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + 50.0f, g_player.pos.y + 50.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	//pVtx[3].tex = D3DXVECTOR2(0.2f, 0.5f);
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffPlayer->Unlock();

	g_player.rot.z -= D3DX_PI/2;
}
//======================
//プレイヤーの終了処理
//======================
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}
//======================
//プレイヤーの更新処理
//======================
void UpdatePlayer(void)
{
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//SetEffect(g_player.pos, D3DCOLOR_RGBA(255, 255, 255, 255), 30, 30.0);

	if (g_player.bUse == true)
	{
		//キー入力による移動＆コントローラー
		//左
		if (GetKeyboardPress(DIK_A) == true|| GetJoypadPress(JOYKEY_LEFT) == true)
		{// A
			if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true)
			{//左上
				g_player.move.x -= sinf(D3DX_PI * 0.75f) * 0.3f;
				g_player.move.y += cosf(D3DX_PI * 0.75f) * 0.3f;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN) == true)
			{//左下
				g_player.move.x -= sinf(D3DX_PI * 0.25f) * 0.3f;
				g_player.move.y += cosf(D3DX_PI * 0.25f) * 0.3f;
			}
			else
			{//左
				g_player.move.x -= 0.3f;
			}
		}
		//右
		else if (GetKeyboardPress(DIK_D) == true|| GetJoypadPress(JOYKEY_RIGET) == true)
		{// D
			if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true)
			{//右上
				g_player.move.x += sinf(D3DX_PI * 0.75f) * 0.3f;
				g_player.move.y += cosf(D3DX_PI * 0.75f) * 0.3f;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN) == true)
			{//右下
				g_player.move.x += sinf(D3DX_PI * 0.75f) * 0.3f;
				g_player.move.y -= cosf(D3DX_PI * 0.75f) * 0.3f;
			}
			else
			{//右
				g_player.move.x += 0.3f;
			}
		}
		//上
		else if (GetKeyboardPress(DIK_W) == true|| GetJoypadPress(JOYKEY_UP) == true)
		{// W
			if (GetKeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT) == true)
			{//左上
				g_player.move.x -= sinf(D3DX_PI * 0.75f) * 0.3f;
				g_player.move.y += cosf(D3DX_PI * 0.75f) * 0.3f;
			}
			else if (GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGET) == true)
			{//右上
				g_player.move.x += sinf(D3DX_PI * 0.75f) * 0.3f;
				g_player.move.y += cosf(D3DX_PI * 0.75f) * 0.3f;
			}
			else
			{//上
				g_player.move.y -= 0.3f;
			}
		}
		//下
		else if (GetKeyboardPress(DIK_S) == true|| GetJoypadPress(JOYKEY_DOWN) == true)
		{// S

			if (GetKeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT) == true)
			{//左下
				g_player.move.x -= sinf(D3DX_PI * 0.25f) * 0.3f;
				g_player.move.y += cosf(D3DX_PI * 0.25f) * 0.3f;
			}
			else if (GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGET) == true)
			{//右下
				g_player.move.x += sinf(D3DX_PI * 0.25f) * 0.3f;
				g_player.move.y -= cosf(D3DX_PI * 0.25f) * 0.3f;
			}
			else
			{//下
				g_player.move.y += 0.3f;
			}
		}
		////回転
		//else if (GetKeyboardPress(DIK_Q) == true|| GetJoypadPress(JOYKEY_L1) == true)
		//{
		//	g_player.rot.z += 0.1;
		//	if (g_player.rot.z >= D3DX_PI)
		//	{
		//		g_player.rot.z = -D3DX_PI;
		//	}
		//}
		////回転
		//else if (GetKeyboardPress(DIK_E) == true|| GetJoypadPress(JOYKEY_R1) == true)
		//{
		//	g_player.rot.z -= 0.1;
		//	if (g_player.rot.z <= -D3DX_PI)
		//	{
		//		g_player.rot.z = D3DX_PI;
		//	}
		//}
		//弾発射
		if (KeyboardTrigger(DIK_SPACE) == true|| GetJoypadPress(JOYKEY_A) == true)
		{
			//弾の設定
			SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI) * 10.0f, cosf(g_player.rot.z + D3DX_PI) * 10.0f, 0.0f), 100, BULLETTYPE_PLAYER);

			////複数同時
			//int nCnt,nData=-25;
			//for (nCnt = 0; nCnt < 3; nCnt++)
			//{
			//	SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y + nData, 0.0f), D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI) * 10.0f, cosf(g_player.rot.z + D3DX_PI) * 10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
			//	SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y + nData, 0.0f), D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI + 0.5) * 10.0f, cosf(g_player.rot.z + D3DX_PI + 0.5) * 10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
			//	SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y + nData, 0.0f), D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI - 0.5) * 10.0f, cosf(g_player.rot.z + D3DX_PI - 0.5) * 10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
			//	nData += 25;
			//}

			////後ろ
			//SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI) * -10.0f, cosf(g_player.rot.z + D3DX_PI) * -10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
			////斜め
			//SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI + 0.5) * 10.0f, cosf(g_player.rot.z + D3DX_PI + 0.5) * 10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
			//SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI - 0.5) * 10.0f, cosf(g_player.rot.z + D3DX_PI - 0.5) * 10.0f, 0.0f), 100, BULLETTYPE_PLAYER);

			////斜め後ろ
			//SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI + 0.5) * -10.0f, cosf(g_player.rot.z + D3DX_PI + 0.5) * -10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
			//SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI - 0.5) * -10.0f, cosf(g_player.rot.z + D3DX_PI - 0.5) * -10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
			////上下 
			//SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI/2) * 10.0f, cosf(g_player.rot.z + D3DX_PI/2) * 10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
			//SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI/2) * -10.0f, cosf(g_player.rot.z + D3DX_PI/2) * -10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
		}

		//START
		else if (GetKeyboardPress(DIK_0) == true||GetJoypadPress(JOYKEY_START) == true)
		{
			SetResult(RESULT_GAMEOVER);
			SetFade(MODE_RESULT);
		}
		//BACK
		else if (GetKeyboardPress(DIK_9) == true || GetJoypadPress(JOYKEY_BACK) == true)
		{
			SetFade(MODE_TITLE);
		}


		//移動制限
		if (g_player.pos.x <= 25)
		{
			g_player.move.x = 0.3;
		}
		else if(g_player.pos.x >= SCREEN_WIDTH - 25)
		{
			g_player.move.x = -0.3;
		}
		if (g_player.pos.y <= 40)
		{
			g_player.move.y = 0.3;
		}
		else if (g_player.pos.y >= SCREEN_HEIGHT - 40)
		{
			g_player.move.y = -0.3;
		}

		//位置を更新
		g_player.pos.x += g_player.move.x;
		g_player.pos.y += g_player.move.y;
		//移動量を更新
		g_player.move.x += (0.0f - g_player.move.x) * 0.02f;
		g_player.move.y += (0.0f - g_player.move.y) * 0.02f;

		pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.fAnglePlayer)) * g_player.fLengthPlayer;
		pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.fAnglePlayer)) * g_player.fLengthPlayer;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAnglePlayer)) * g_player.fLengthPlayer;
		pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAnglePlayer)) * g_player.fLengthPlayer;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z - g_player.fAnglePlayer) * g_player.fLengthPlayer;
		pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z - g_player.fAnglePlayer) * g_player.fLengthPlayer;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + g_player.fAnglePlayer) * g_player.fLengthPlayer;
		pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + g_player.fAnglePlayer) * g_player.fLengthPlayer;
		pVtx[3].pos.z = 0.0f;

		//アニメーション
		//g_player.nCounterAnimPlayer++;
		//if ((g_player.nCounterAnimPlayer % 5) == 0)
		//{//一定時間経過
		//	//パターンNoを更新
		//	g_player.nPatternAnimPlayer = (g_player.nPatternAnimPlayer + 1) % 10;

		//	//テクスチャ座標の設定
		//	//U座標は５で割ったあまりが１か0かででる
		//	//V座標は５で割った結果が0.?か1.?かでわかる
		//	if (GetKeyboardPress(DIK_D) == true)
		//	{
		//		pVtx[1].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f);
		//		pVtx[0].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f + 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f);
		//		pVtx[3].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f + 0.5f);
		//		pVtx[2].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f + 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f + 0.5f);
		//	}
		//	else if (GetKeyboardPress(DIK_A) == true)
		//	{
		//		pVtx[0].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f);
		//		pVtx[1].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f + 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f);
		//		pVtx[2].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f + 0.5f);
		//		pVtx[3].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f + 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f + 0.5f);
		//	}
		//	else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_W) == true)
		//	{
		//		pVtx[0].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f);
		//		pVtx[1].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f + 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f);
		//		pVtx[2].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f + 0.5f);
		//		pVtx[3].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f + 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f + 0.5f);
		//	}
		//}

		switch (g_player.state)
		{
		case PLAYERSTATE_NORMAL:
			break;
		case PLAYERSTATE_DAMAGE:
			g_player.nCounterState--;
			if (g_player.nCounterState <= 0)
			{
				g_player.state = PLAYERSTATE_NORMAL;
				//ポリゴンを通常色に戻す
				VERTEX_2D* pVtx;
				//頂点バッファをロックし、頂点情報へのポインタを取得
				g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				//頂点バッファをアンロック
				g_pVtxBuffPlayer->Unlock();
			}
			break;
		case PLAYERSTATE_DEATH:
			g_player.nCounterState--;
			if (g_player.nCounterState <= 0)
			{

				return;
			}
			break;
		}
	}
	//頂点バッファをアンロック
	g_pVtxBuffPlayer->Unlock();
}
//======================
//プレイヤーの描画処理
//======================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	if (g_player.bUse == true)
	{
		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));
		//1つ目
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer);
		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//================
//プレイヤー取得
//================
Player* GetPlayer(void)
{
	return &g_player;
}
//===================
//プレイヤーの状態
//===================
void HitPlayer(int nDamage)
{
	g_player.nLife -= nDamage;
	if (g_player.nLife <= 0)
	{
		//爆発の設定
		SetExplosion(g_player.pos, 1.0f);
		g_player.bUse = false;
		g_player.state = PLAYERSTATE_DEATH;
		g_player.nCounterState = 60;

		//モード設定をリザルトにする
		SetGameState(GAMESTATE_GAMEOVER);
	}
	else
	{
		g_player.state = PLAYERSTATE_DAMAGE;
		g_player.nCounterState = 5;
		VERTEX_2D* pVtx;
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		//頂点バッファをアンロック
		g_pVtxBuffPlayer->Unlock();
	}
}