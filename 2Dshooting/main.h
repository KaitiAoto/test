//==============================
//
//　ウインドウ表示処理[main.h]
//　Author:kaiti
//
//==============================
#ifndef _MAIN_H_
#define _MAIN_H_

#include<Windows.h>
#include "d3dx9.h"

#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "Xinput.h"
#include "xaudio2.h"
//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")

//マクロ定義
#define CLASS_NAME "WindowsClass"
#define WINDOW_NAME "2Dシューティングゲーム"
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//頂点情報(2D)の構造体
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;      //座標変換用係数
	D3DCOLOR col;   //頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標
}VERTEX_2D;

//
typedef enum
{
	MODE_TITLE=0,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX
}MODE;

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
MODE GetMode(void);

LPDIRECT3DDEVICE9 GetDevice(void);

#endif