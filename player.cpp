//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "player.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define	BODY_PLAYER			"data/MODEL/mere god/body.x"	// 読み込むモデル名
#define	HEAD_PLAYER			"data/MODEL/mere god/head.x"	// 読み込むモデル名
#define	HAND_L_PLAYER		"data/MODEL/mere god/hand_L.x"	// 読み込むモデル名
#define	HAND_R_PLAYER		"data/MODEL/mere god/hand_R.x"	// 読み込むモデル名
#define	LEG_L_PLAYER		"data/MODEL/mere god/leg_L.x"	// 読み込むモデル名
#define	LEG_R_PLAYER		"data/MODEL/mere god/leg_R.x"	// 読み込むモデル名
#define	SWORD_PLAYER		"data/MODEL/mere god/sword.x"		// 読み込むモデル名

#define	TEXTURE_PLAYER		"data/MODEL/mere god/knight.png"		// 読み込むモデル名
#define	TEXTURE_SWORD		"data/MODEL/mere god/kenn.png"		// 読み込むモデル名

#define	PLAYER_RADIUS		(15.0f)						// 半径

#define	VALUE_MOVE_PLAYER	(0.195f)					// 移動速度
#define	RATE_MOVE_PLAYER	(0.025f)					// 移動慣性係数

#define	UNIT_S_PLAYER	(0.1f)						// 拡大単位
#define	UNIT_R_PLAYER	(D3DXToRadian(5))			// 回転単位　5度
#define UNIT_T_PLAYER	(1.0f)						// 移動単位

#define	RATE_ROTATE_PLAYER	(0.10f)						// 回転慣性係数



extern HWND hWnd;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void WriteAnime();
void AnimeWalk(KEY g_anime[]);
void AnimeKen(KEY g_anime[]);
void AnimeKen3(KEY g_anime[]);
void AnimeTemp(KEY g_anime[]);
void CreateAnimeTemp(int flameNum = 60);
void DebugUI();
void controller();

void LoadAnime(KEY *g_anime);	//外部のデータを読む

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer;		// テクスチャ読み込み場所
LPDIRECT3DTEXTURE9	g_pD3DTextureSword;		// テクスチャ読み込み場所
PLAYER				g_player;					// プレイヤーワーク

int g_mode = MODE_EDIT;//編輯モードかどうか

int SRTMode = 0;
int XYZMode = 0;

int g_conId = 0;	//デフォルトのコントロールID

bool manual = 1;//操作説明

float g_motionTime = 0.0f;	// アニメーション全体時間　歩く
float g_motionTime2 = 0.0f;	// アニメーション全体時間　剣投げ
float g_motionTime3 = 0.0f;	// アニメーション全体時間　ジャンプ斬り
float g_motionTimeTemp = 0.0f;	// アニメーション全体時間　臨時

float g_motionTimeSR = 0.0f;	// アニメーション全体時間　臨時




int g_keyMax;				//キーフレームの数

bool g_animeState = 0;		//運動状態かどうか　歩く
bool g_animeStateKen = 0;
bool g_animeStateKen3= 0;

float g_cancelTime = 0.0f;// 最初状態に戻る時間 歩く

D3DXMATRIX mtxBuff;
D3DXMATRIX mtxBuff3;

D3DXVECTOR3 vctBuff3;
float rotY;	//ジャンプ斬りを発動時の方向を記録する

D3DXMATRIX rotYMtx;

bool partsShine;

//走るキー情報
KEY g_animeWalk[] =
{
	{
		15,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S この拡大は全部のパーツに反映する
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T　地面との距離（この数値は自分でテストして得るもの）
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0f, -7.18f, -0.79f),//T
			},


		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S
				D3DXVECTOR3(-0.0385f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(1.4923f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-0.7069f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0854f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.9425f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0f, -7.18f, -0.79f),//T
			},


		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S
				D3DXVECTOR3(-0.0385f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-0.8639f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(1.0996f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.9425f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0854f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0f, -7.18f, -0.79f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S
				D3DXVECTOR3(-0.0385f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(1.4923f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-0.7069f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0854f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.9425f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0f, -7.18f, -0.79f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

};

//剣投げ
KEY g_animeKen[] =
{
	{
		30,
		{
			{// part 0
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-0.7900f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(12.5664f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-65.1650f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(25.1326f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-55.1650f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(37.7775f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-65.1650f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(50.2655f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-55.1650f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(62.9106f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-65.1650f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////


};

//ジャンプ斬り
KEY g_animeKen3[] =
{
		{
		30,
		{
			{// パーツ番号:0 
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// パーツ番号:1 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// パーツ番号:2 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// パーツ番号:3 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// パーツ番号:4 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// パーツ番号:5 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// パーツ番号:6 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-0.7900f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////キーフレーム番号:0 

	{
		40,
		{
			{// パーツ番号:0 
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.5498f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,85.7199f,-137.4752f),//T
			},

			{// パーツ番号:1 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-0.1571f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// パーツ番号:2 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(3.5517f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// パーツ番号:3 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(2.7489f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// パーツ番号:4 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-0.8639f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// パーツ番号:5 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-0.3927f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// パーツ番号:6 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-0.7900f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////キーフレーム番号:1 

	{
		15,
		{
			{// パーツ番号:0 
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(-0.2356f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,-316.4919f),//T
			},

			{// パーツ番号:1 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-0.1571f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// パーツ番号:2 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.7069f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// パーツ番号:3 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.4451f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// パーツ番号:4 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.7069f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// パーツ番号:5 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-0.7069f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// パーツ番号:6 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0472f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-0.7900f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////キーフレーム番号:2 

	{
		1000,
		{
			{// パーツ番号:0 
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,-316.4919f),//T
			},

			{// パーツ番号:1 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// パーツ番号:2 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// パーツ番号:3 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// パーツ番号:4 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// パーツ番号:5 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// パーツ番号:6 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-0.7900f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////キーフレーム番号:3 

};


//外部のファイルをロード用
KEY g_animeMemoy[] =
{
	{
		20,
		{
			{// part 0
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-0.7900f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(12.5664f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-105.1650f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(25.1326f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-95.1650f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(37.7775f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-105.1650f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(50.2655f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-95.1650f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(62.9106f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-105.1650f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////


};


//エディター用
KEY *pAnimeTemp;

int keyFrameNum;//保存するキーフレームの総数

int keyFrameSaveNo;//次に保存するキーフレームの番号

int functionMode;

int reviewNo;//個別リビューするキーフレームの番号

int reviewFrameNo1;//区間リビューする始点キーフレームの番号
int reviewFrameNo2;//区間リビューする終点キーフレームの番号

int diyFrame = 60;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	pAnimeTemp = (KEY *)malloc(sizeof(KEY) * 256);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_player.part[0].partFile = (char *)BODY_PLAYER;//親は一番先にしなければならない
	g_player.part[1].partFile = (char *)HEAD_PLAYER;//(const char *)から(char *)に変換
	g_player.part[2].partFile = (char *)HAND_L_PLAYER;//左手
	g_player.part[3].partFile = (char *)HAND_R_PLAYER;//右手
	g_player.part[4].partFile = (char *)LEG_L_PLAYER;//左足
	g_player.part[5].partFile = (char *)LEG_R_PLAYER;//右足

	g_player.part[6].partFile = (char *)SWORD_PLAYER;//右手の剣

	for (int i = 0; i < PART_MAX; i++)//パーツ番号
	{
		// Xファイルの読み込み
		if(FAILED(D3DXLoadMeshFromX(g_player.part[i].partFile,
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_player.part[i].pMatBuff,
									NULL,
									&g_player.part[i].nNumMat,
									&g_player.part[i].pMesh)))
		{
			MessageBox(hWnd, _T("Xファイルの読み込みに失敗しました"), _T("error"), MB_OK | MB_ICONERROR);
			return E_FAIL;
		}

		switch (i)
		{//初期値
		case 0:
		{//体
			g_player.part[i].srt.scl = D3DXVECTOR3(2.0f, 2.0f, 2.0f);//xyz必ず同じように
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(0.0f, 28.0f, 0.0f);// pos.yは足が地面に触れるような数値

			g_player.part[i].parent = NULL;//体の親はNULLにする
			break;
		}
		case 1:
		{//頭
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(0.0f, 7.06f,  0.09f);

			g_player.part[i].parent = &g_player.part[0];//体を親にする
			break;
		}
		case 2:
		{//左手
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(7.01f, 4.82f, -0.49f);

			g_player.part[i].parent = &g_player.part[0];//体を親にする
			break;
		}
		case 3:
		{//右手
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(-7.01f, 4.82f, -0.49f);

			g_player.part[i].parent = &g_player.part[0];//体を親にする
			break;
		}
		case 4:
		{//左足
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(2.0f, -4.00f, 0.0f);

			g_player.part[i].parent = &g_player.part[0];//体を親にする
			break;
		}
		case 5:
		{//右足
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(-2.0f, -4.00f, 0.0f);

			g_player.part[i].parent = &g_player.part[0];//体を親にする
			break;
		}
		case 6:
		{//右手の剣
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
			g_player.part[i].srt.pos = D3DXVECTOR3(-0.92f, -7.19f, -0.79f);	//ここの数値要注意、特にｚの符号

			g_player.part[i].parent = &g_player.part[3];//右手を親にする！！
			break;
		}

		}

		g_player.part[i].use = true;

	}

	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.fRadius = PLAYER_RADIUS;	//影のサイズ用、当たり判定用　

	g_player.state = NORMAL;
	

#if 1
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_PLAYER,			// ファイルの名前
								&g_pD3DTexturePlayer);	// 読み込むメモリー

		// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_SWORD,				// ファイルの名前
								&g_pD3DTextureSword);	// 読み込むメモリー


#endif

	CreateAnimeTemp(diyFrame);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	//運動情報を書き出す
	WriteAnime();

	for (int i = 0; i < PART_MAX; i++)//パーツ番号
	{
		if (g_player.part[i].pMesh != NULL)
		{// メッシュの開放
			g_player.part[i].pMesh->Release();
			g_player.part[i].pMesh = NULL;
		}

		if (g_player.part[i].pMatBuff != NULL)
		{// マテリアルの開放
			g_player.part[i].pMatBuff->Release();
			g_player.part[i].pMatBuff = NULL;
		}
	}

	if (g_pD3DTexturePlayer != NULL)
	{// テクスチャの開放
		g_pD3DTexturePlayer->Release();
		g_pD3DTexturePlayer = NULL;
	}

	SAFE_RELEASE(g_pD3DTextureSword);

	if (pAnimeTemp != g_animeMemoy)
	{
		free(pAnimeTemp);
	}
	
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	partsShine = 0;

	controller();




	switch (g_mode)
	{
	case MODE_PLAY:
	{
#ifdef _DEBUG
		//AnimeKen(g_animeKen);
		AnimeWalk(g_animeWalk);
#endif
		break;
	}

	case MODE_EDIT:
	{
#ifdef _DEBUG
		AnimeTemp(pAnimeTemp);
#endif		
		break;
	}

	case MODE_INGAME:
	{
		D3DXVECTOR3 rotCamera;
		float fDiffRotY;

		// カメラの向き取得
		rotCamera = GetRotCamera();

		g_animeState = 0;//運動状態をリセット

		//移動
		if (GetKeyboardPress(DIK_A) || IsButtonPress(0, BUTTON_LEFT) || IsButtonPress(0, BUTTON_LSTICK_LEFT))
		{
			g_animeState = 1;//動く状態にする

			if (GetKeyboardPress(DIK_W) || IsButtonPress(0, BUTTON_UP) || IsButtonPress(0, BUTTON_LSTICK_UP))
			{// 左前移動
				g_player.move.x -= sinf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.75f;
			}
			else if (GetKeyboardPress(DIK_S) || IsButtonPress(0, BUTTON_DOWN) || IsButtonPress(0, BUTTON_LSTICK_DOWN))
			{// 左後移動
				g_player.move.x -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.25f;
			}
			else
			{// 左移動
				g_player.move.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.50f;
			}
		}
		else if (GetKeyboardPress(DIK_D) || IsButtonPress(0, BUTTON_RIGHT) || IsButtonPress(0, BUTTON_LSTICK_RIGHT))
		{
			g_animeState = 1;//動く状態にする

			if (GetKeyboardPress(DIK_W) || IsButtonPress(0, BUTTON_UP) || IsButtonPress(0, BUTTON_LSTICK_UP))
			{// 右前移動
				g_player.move.x -= sinf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.75f;
			}
			else if (GetKeyboardPress(DIK_S) || IsButtonPress(0, BUTTON_DOWN) || IsButtonPress(0, BUTTON_LSTICK_DOWN))
			{// 右後移動
				g_player.move.x -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.25f;
			}
			else
			{// 右移動
				g_player.move.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.50f;
			}
		}
		else if (GetKeyboardPress(DIK_W) || IsButtonPress(0, BUTTON_UP) || IsButtonPress(0, BUTTON_LSTICK_UP))
		{
			g_animeState = 1;//動く状態にする

			// 前移動
			g_player.move.x -= sinf(D3DX_PI + rotCamera.y) * VALUE_MOVE_PLAYER;
			g_player.move.z -= cosf(D3DX_PI + rotCamera.y) * VALUE_MOVE_PLAYER;

			g_player.rotDest.y = D3DX_PI + rotCamera.y;
		}
		else if (GetKeyboardPress(DIK_S) || IsButtonPress(0, BUTTON_DOWN) || IsButtonPress(0, BUTTON_LSTICK_DOWN))
		{
			g_animeState = 1;//動く状態にする

			// 後移動
			g_player.move.x -= sinf(rotCamera.y) * VALUE_MOVE_PLAYER;
			g_player.move.z -= cosf(rotCamera.y) * VALUE_MOVE_PLAYER;

			g_player.rotDest.y = rotCamera.y;
		}

		if (g_animeStateKen3 == 0)
		{
			AnimeWalk(g_animeWalk);
		}
		AnimeKen3(g_animeKen3);

		AnimeKen(g_animeKen);

		

		// 目的の角度までの差分
		fDiffRotY = g_player.rotDest.y - g_player.part[0].srt.rot.y;//体を基準に
		if (fDiffRotY > D3DX_PI)
		{
			fDiffRotY -= D3DX_PI * 2.0f;
		}
		if (fDiffRotY < -D3DX_PI)
		{
			fDiffRotY += D3DX_PI * 2.0f;
		}

		// 目的の角度まで慣性をかける　段々目的の角度に変化する
		g_player.part[0].srt.rot.y += fDiffRotY * RATE_ROTATE_PLAYER;//体に反映
		if (g_player.part[0].srt.rot.y > D3DX_PI)
		{
			g_player.part[0].srt.rot.y -= D3DX_PI * 2.0f;
		}
		if (g_player.part[0].srt.rot.y < -D3DX_PI)
		{
			g_player.part[0].srt.rot.y += D3DX_PI * 2.0f;
		}

		// 位置移動を反映
		g_player.part[0].srt.pos.x += g_player.move.x;//体に反映
		g_player.part[0].srt.pos.y += g_player.move.y;
		g_player.part[0].srt.pos.z += g_player.move.z;

		//移動範囲　//体を基準に
		{
			if (g_player.part[0].srt.pos.x < -630.0f)
			{
				g_player.part[0].srt.pos.x = -630.0f;
			}
			if (g_player.part[0].srt.pos.x > 630.0f)
			{
				g_player.part[0].srt.pos.x = 630.0f;
			}
			if (g_player.part[0].srt.pos.y < 10.0f)
			{
				g_player.part[0].srt.pos.y = 10.0f;
			}
			if (g_player.part[0].srt.pos.y > 150.0f)
			{
				g_player.part[0].srt.pos.y = 150.0f;
			}
			if (g_player.part[0].srt.pos.z > 630.0f)
			{
				g_player.part[0].srt.pos.z = 630.0f;
			}
			if (g_player.part[0].srt.pos.z < -630.0f)
			{
				g_player.part[0].srt.pos.z = -630.0f;
			}
		}

		// 移動量に慣性をかける　運動エネルギーを一部損して保存する、次のフレームに使う
		//損の部分イコール次のフレームに獲得の運動エネルギーの場合、速度が最大(6.05f)になって、等速直線運動になる
		g_player.move.x += (0.0f - g_player.move.x) * RATE_MOVE_PLAYER;//即ち、g_player.move.x = g_player.move.x * (1 - RATE_MOVE_PLAYER;)
		g_player.move.y += (0.0f - g_player.move.y) * RATE_MOVE_PLAYER;
		g_player.move.z += (0.0f - g_player.move.z) * RATE_MOVE_PLAYER;

		break;
	}



	}//switch end


	DebugUI();


	//運動情報を書き出す
	if (GetKeyboardTrigger(DIK_F2))
	{
		WriteAnime();
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;
	D3DXMATERIAL *pD3DXMat;

	D3DMATERIAL9 matDef;
	pDevice->GetMaterial(&matDef);// デフォルトのマテリアルを取得

	for (int i = 0; i < PART_MAX; i++)//パーツ番号
	{
		if (g_player.part[i].use)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, g_player.part[i].srt.scl.x,
				g_player.part[i].srt.scl.y,
				g_player.part[i].srt.scl.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);
			
			g_player.part[i].mtxS = mtxScl;

			//if ((g_animeStateKen3) && (i == BODY))
			//{
			//	// 移動を反映
			//	D3DXMatrixTranslation(&mtxTranslate, g_player.part[i].srt.pos.x,
			//		g_player.part[i].srt.pos.y,
			//		g_player.part[i].srt.pos.z);
			//	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

			//	g_player.part[i].mtxT = mtxTranslate;

			//	// 回転を反映
			//	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.part[i].srt.rot.y,
			//		g_player.part[i].srt.rot.x,
			//		g_player.part[i].srt.rot.z);
			//	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

			//	g_player.part[i].mtxR = mtxRot;


			//}
			//else
			
			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.part[i].srt.rot.y,
				g_player.part[i].srt.rot.x,
				g_player.part[i].srt.rot.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

			g_player.part[i].mtxR = mtxRot;

			// 移動を反映



			D3DXMatrixTranslation(&mtxTranslate, g_player.part[i].srt.pos.x,
				g_player.part[i].srt.pos.y,
				g_player.part[i].srt.pos.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

			g_player.part[i].mtxT = mtxTranslate;
			

			



			//親が存在する場合は親のワールドマトリクスを合成
			if (g_player.part[i].parent)
			{
				if ((i == SWORD_R)&&(g_animeStateKen))
				{
					D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxBuff);
					
				}
				else
				{
					D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &g_player.part[i].parent->mtxWorld);
				}


			}



			g_player.part[i].mtxWorld = mtxWorld;//ワールドマトリクスを保存

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)g_player.part[i].pMatBuff->GetBufferPointer();

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTexturePlayer);

			if (i == SWORD_R)
			{
				pDevice->SetTexture(0, g_pD3DTextureSword);

			}

			//選択されたパーツが光る
			if (i == g_conId)
			{
				if (partsShine == 1)
				{
					pDevice->SetTexture(0, NULL);
				}
				
			}


			for (int nCntMat = 0; nCntMat < (int)g_player.part[i].nNumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// 描画
				g_player.part[i].pMesh->DrawSubset(nCntMat);
			}
			
		}
	}
	pDevice->SetMaterial(&matDef);// マテリアルをデフォルトに戻す
}

//=============================================================================
// プレイヤーを取得
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_player;
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionPlayer(void)
{
	return g_player.part[0].srt.pos;//体を基準に
}

//=============================================================================
// 向き取得
//=============================================================================
D3DXVECTOR3 GetRotationPlayer(void)
{
	return g_player.part[0].srt.rot;//体を基準に
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestPlayer(void)
{
	return g_player.rotDest;
}

//=============================================================================
// 移動量取得
//=============================================================================
D3DXVECTOR3 GetMovePlayer(void)
{
	return g_player.move;
}

// アニメ書き出し
void WriteAnime()
{
#ifdef _DEBUG

	FILE *fp;
	fp = fopen("animeTemp.txt", "a+");//"a+"は書き込みのモード。ファイルがないと、自動に作成
	if (fp == NULL)
	{
		return;
	}

	fprintf(fp, "★★★★★★★★★★★★★★★★★★★★★★★★★★★NEW★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");

	for (int i = 0; i < keyFrameNum; i++)
	{
		//\t　水平タブ
		fprintf(fp, "\t{\n");
		fprintf(fp, "\t\t%d,\n", pAnimeTemp[i].frame);//フレーム数
		fprintf(fp, "\t\t{\n");

		for (int j = 0; j < PART_MAX; j++)
		{
			fprintf(fp, "\t\t\t{// パーツ番号:%d \n", j);
			fprintf(fp, "\t\t\t\tD3DXVECTOR3(%.4ff,%.4ff,%.4ff),//S\n", pAnimeTemp[i].key[j].scl.x,
																		pAnimeTemp[i].key[j].scl.y,
																		pAnimeTemp[i].key[j].scl.z);

			fprintf(fp, "\t\t\t\tD3DXVECTOR3(%.4ff,%.4ff,%.4ff),//R\n", pAnimeTemp[i].key[j].rot.x,
																		pAnimeTemp[i].key[j].rot.y,
																		pAnimeTemp[i].key[j].rot.z);

			fprintf(fp, "\t\t\t\tD3DXVECTOR3(%.4ff,%.4ff,%.4ff),//T\n", pAnimeTemp[i].key[j].pos.x,
																		pAnimeTemp[i].key[j].pos.y,
																		pAnimeTemp[i].key[j].pos.z);

			fprintf(fp, "\t\t\t},\n");
			fprintf(fp, "\n");
		}
		fprintf(fp, "\t\t}\n");
		fprintf(fp, "\t},///////////////////////////////////////////////////////////////////////////////////キーフレーム番号:%d \n",i);
		fprintf(fp, "\n");

	}

	fclose(fp);

#endif

}


void AnimeWalk(KEY g_anime[])
{
	g_keyMax = sizeof(g_animeWalk) / sizeof(KEY);//sizeof(g_anime)ではダメ

	switch (g_mode)
	{
	case MODE_PLAY:
	{
		//アニメーション 
		int i = (int)g_motionTime;  //現在のキーフレームナンバー

		//if (i > g_keyMax - 2)//最大キーフレームナンバーを超えたら
		//{
		//	i = g_keyMax - 2;//最大キーフレームナンバーにする
		//}

		//loopできるように
		if (i > g_keyMax - 2)//最大キーフレームナンバーを超えたら
		{
			i = 1;
			g_motionTime = 1.0f;
		}

		float dt = 1.0f / g_anime[i].frame;//補間の間隔時間

		g_motionTime += dt;

		if (g_motionTime > g_keyMax - 1.0f)//最大時間を超えたら
		{
			g_motionTime = g_keyMax - 1.0f;//最大最大時間にする
		}

		if (g_motionTime - i > 1.0f) //誤差を修正　想定の1.0を超えたら
		{
			i++;//次のキーフレームに入る
		}

		//if (GetKeyboardPress(DIK_SPACE))
		//{
		//	g_motionTime = 0.0f;	//リセット
		//	i = (int)g_motionTime;	//重要
		//}

		if (1)
		{
			//接続の補間は　[i] * 1.0です、[i + 1] * 0.0ではない
			for (int j = 0; j < PART_MAX; j++)//パーツ番号
			{
				// Scale
				//g_player.part[j].srt.scl.x = g_anime[i].key[j].scl.x +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].scl.x - g_anime[i].key[j].scl.x)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				//g_player.part[j].srt.scl.y = g_anime[i].key[j].scl.y +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].scl.y - g_anime[i].key[j].scl.y)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				//g_player.part[j].srt.scl.z = g_anime[i].key[j].scl.z +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].scl.z - g_anime[i].key[j].scl.z)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				// Rotation
				g_player.part[j].srt.rot.x = g_anime[i].key[j].rot.x +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].rot.x - g_anime[i].key[j].rot.x)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.rot.y = g_anime[i].key[j].rot.y +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].rot.y - g_anime[i].key[j].rot.y)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.rot.z = g_anime[i].key[j].rot.z +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].rot.z - g_anime[i].key[j].rot.z)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				// Position
				//g_player.part[j].srt.pos.x = g_anime[i].key[j].pos.x +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].pos.x - g_anime[i].key[j].pos.x)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				//g_player.part[j].srt.pos.y = g_anime[i].key[j].pos.y +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].pos.y - g_anime[i].key[j].pos.y)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				//g_player.part[j].srt.pos.z = g_anime[i].key[j].pos.z +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].pos.z - g_anime[i].key[j].pos.z)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける
			}
		}

		break;
	}

	case MODE_INGAME:
	{
		//アニメーション 
		int i = (int)g_motionTime;  //現在のキーフレームナンバー

		//loopできるように
		if (i > g_keyMax - 2)//最大キーフレームナンバーを超えたら
		{
			i = 1;
			g_motionTime = 1.0f;
		}

		float dt = 1.0f / g_anime[i].frame;//補間の間隔時間

		g_motionTime += dt;

		if (g_motionTime > g_keyMax - 1.0f)//最大時間を超えたら
		{
			g_motionTime = g_keyMax - 1.0f;//最大時間にする
		}

		if (g_motionTime - i > 1.0f) //誤差を修正　想定の1.0を超えたら
		{
			i++;//次のキーフレームに入る
		}

		if (g_animeState == 0)
		{
			g_motionTime = 0.0f;	//リセット
			i = (int)g_motionTime;	//重要

			if (g_player.state != FROZEN)
			{
				g_cancelTime += dt;//0番キーフレームのtimeを使う
			}

			if (g_cancelTime > 1.0f)//最大時間を超えたら
			{
				g_cancelTime = 1.0f;//最大最大時間にする
			}

			//接続の補間は　[i] * 1.0です、[i + 1] * 0.0ではない
			for (int j = 0; j < PART_MAX; j++)//パーツ番号
			{//最初のキーの状態に戻る
				// Scale
				//g_player.part[j].srt.scl.x = g_player.part[j].srt.scl.x +	
				//	(g_anime[0].key[j].scl.x - g_player.part[j].srt.scl.x)	
				//	* g_cancelTime;											

				//g_player.part[j].srt.scl.y = g_player.part[j].srt.scl.y +	
				//	(g_anime[0].key[j].scl.y - g_player.part[j].srt.scl.y)	
				//	* g_cancelTime;											

				//g_player.part[j].srt.scl.z = g_player.part[j].srt.scl.z +	
				//	(g_anime[0].key[j].scl.z - g_player.part[j].srt.scl.z)	
				//	* g_cancelTime;											

				// Rotation
				g_player.part[j].srt.rot.x = g_player.part[j].srt.rot.x +
					(g_anime[0].key[j].rot.x - g_player.part[j].srt.rot.x)
					* g_cancelTime;

				//g_player.part[j].srt.rot.y = g_player.part[j].srt.rot.y +	
				//	(g_anime[0].key[j].rot.y - g_player.part[j].srt.rot.y)	
				//	* g_cancelTime;											

				g_player.part[j].srt.rot.z = g_player.part[j].srt.rot.z +
					(g_anime[0].key[j].rot.z - g_player.part[j].srt.rot.z)
					* g_cancelTime;

				// Position
				//g_player.part[j].srt.pos.x = g_player.part[j].srt.pos.x +	
				//	(g_anime[0].key[j].pos.x - g_player.part[j].srt.pos.x)	
				//	* g_cancelTime;											

				//g_player.part[j].srt.pos.y = g_player.part[j].srt.pos.y +	
				//	(g_anime[0].key[j].pos.y - g_player.part[j].srt.pos.y)	
				//	* g_cancelTime;											

				//g_player.part[j].srt.pos.z = g_player.part[j].srt.pos.z +	
				//	(g_anime[0].key[j].pos.z - g_player.part[j].srt.pos.z)	
				//	* g_cancelTime;											
			}

		}
		else
		{
			g_cancelTime = 0.0f;	//リセット

			//接続の補間は　[i] * 1.0です、[i + 1] * 0.0ではない
			for (int j = 0; j < PART_MAX; j++)//パーツ番号
			{
				// Scale
				//g_player.part[j].srt.scl.x = g_anime[i].key[j].scl.x +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].scl.x - g_anime[i].key[j].scl.x)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				//g_player.part[j].srt.scl.y = g_anime[i].key[j].scl.y +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].scl.y - g_anime[i].key[j].scl.y)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				//g_player.part[j].srt.scl.z = g_anime[i].key[j].scl.z +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].scl.z - g_anime[i].key[j].scl.z)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				// Rotation
				g_player.part[j].srt.rot.x = g_anime[i].key[j].rot.x +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].rot.x - g_anime[i].key[j].rot.x)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				//g_player.part[j].srt.rot.y = g_anime[i].key[j].rot.y +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].rot.y - g_anime[i].key[j].rot.y)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.rot.z = g_anime[i].key[j].rot.z +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].rot.z - g_anime[i].key[j].rot.z)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				// Position
				//g_player.part[j].srt.pos.x = g_anime[i].key[j].pos.x +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].pos.x - g_anime[i].key[j].pos.x)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				//g_player.part[j].srt.pos.y = g_anime[i].key[j].pos.y +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].pos.y - g_anime[i].key[j].pos.y)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				//g_player.part[j].srt.pos.z = g_anime[i].key[j].pos.z +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].pos.z - g_anime[i].key[j].pos.z)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける
			}

		}

		break;
	}

	}//end switch


}

void AnimeKen(KEY g_anime[])
{
	if (g_animeStateKen == 0)
	{
		if (GetKeyboardPress(DIK_J))
		{
			g_animeStateKen = 1;//動く状態にする	
			
			D3DXMatrixIdentity(&mtxBuff);
			D3DXMatrixMultiply(&mtxBuff, &mtxBuff, &g_player.part[SWORD_R].parent->mtxS);
			D3DXMatrixMultiply(&mtxBuff, &mtxBuff, &g_player.part[SWORD_R].parent->mtxT);			
			D3DXMatrixMultiply(&mtxBuff, &mtxBuff, &g_player.part[SWORD_R].parent->parent->mtxWorld);//剣を投げる時の、親の行列情報を保存
		}

	}

	if (g_animeStateKen)
	{
		g_keyMax = sizeof(g_animeKen) / sizeof(KEY);//sizeof(g_anime)ではダメ

		//アニメーション 
		int i = (int)g_motionTime2;  //i:現在のキーフレームナンバー

		float dt = 1.0f / g_anime[i].frame;//補間の間隔時間

		//完成したら、元の状態に戻る
		if (i > g_keyMax - 2)//最大キーフレームナンバーを超えたら
		{
			i = 0;
			g_motionTime2 = 0.0f;

			g_animeStateKen = 0;
			dt = 0;
		}

		g_motionTime2 += dt;

		if (g_motionTime2 > g_keyMax - 1.0f)//最大時間を超えたら
		{
			g_motionTime2 = g_keyMax - 1.0f;//最大最大時間にする

		}

		if (g_motionTime2 - i > 1.0f) //誤差を修正　想定の1.0を超えたら
		{
			i++;//次のキーフレームに入る
		}




		//接続の補間は　[i] * 1.0です、[i + 1] * 0.0ではない

		int j = SWORD_R;

		// Rotation
		g_player.part[j].srt.rot.x = g_anime[i].key[j].rot.x +				// 前のキーフレーム位置
			(g_anime[i + 1].key[j].rot.x - g_anime[i].key[j].rot.x)			// 前のキーフレームと次のキーフレームの差分
			* (g_motionTime2 - i);											// に　全体アニメ時間の小数点以下の割合をかける

		g_player.part[j].srt.rot.y = g_anime[i].key[j].rot.y +				// 前のキーフレーム位置
			(g_anime[i + 1].key[j].rot.y - g_anime[i].key[j].rot.y)			// 前のキーフレームと次のキーフレームの差分
			* (g_motionTime2 - i);											// に　全体アニメ時間の小数点以下の割合をかける

		g_player.part[j].srt.rot.z = g_anime[i].key[j].rot.z +				// 前のキーフレーム位置
			(g_anime[i + 1].key[j].rot.z - g_anime[i].key[j].rot.z)			// 前のキーフレームと次のキーフレームの差分
			* (g_motionTime2 - i);											// に　全体アニメ時間の小数点以下の割合をかける


		// Position
		g_player.part[j].srt.pos.x = g_anime[i].key[j].pos.x +				// 前のキーフレーム位置
			(g_anime[i + 1].key[j].pos.x - g_anime[i].key[j].pos.x)			// 前のキーフレームと次のキーフレームの差分
			* (g_motionTime2 - i);											// に　全体アニメ時間の小数点以下の割合をかける

		g_player.part[j].srt.pos.y = g_anime[i].key[j].pos.y +				// 前のキーフレーム位置
			(g_anime[i + 1].key[j].pos.y - g_anime[i].key[j].pos.y)			// 前のキーフレームと次のキーフレームの差分
			* (g_motionTime2 - i);											// に　全体アニメ時間の小数点以下の割合をかける

		g_player.part[j].srt.pos.z = g_anime[i].key[j].pos.z +				// 前のキーフレーム位置
			(g_anime[i + 1].key[j].pos.z - g_anime[i].key[j].pos.z)			// 前のキーフレームと次のキーフレームの差分
			* (g_motionTime2 - i);											// に　全体アニメ時間の小数点以下の割合をかける


	}

}


void AnimeKen3(KEY g_anime[])
{
	if (g_animeStateKen3 == 0)
	{
		if (GetKeyboardPress(DIK_K))
		{
			g_animeStateKen3 = 1;//動く状態にする	
			g_motionTime3 = 0.0f;
	
			vctBuff3 = D3DXVECTOR3( g_player.part[0].srt.pos.x,
									0.0f,
									g_player.part[0].srt.pos.z);

			rotY = g_player.part[0].srt.rot.y;


		}

	}

	if (g_animeStateKen3)
	{
		g_keyMax = sizeof(g_animeKen3) / sizeof(KEY);//sizeof(g_anime)ではダメ

		//アニメーション 
		int i = (int)g_motionTime3;  //i:現在のキーフレームナンバー

		float dt = 1.0f / g_anime[i].frame;//補間の間隔時間

		//完成したら、元の状態に戻る
		if (i > g_keyMax - 2)//最大キーフレームナンバーを超えたら
		{
			i = g_keyMax - 2;//最大キーフレームナンバーにする

			g_animeStateKen3 = 0;
			g_motionTime = 0.0f;		//着地時、走る時間リセット	ジャンプと走るモーションがスムーズにつながるポイント！
		}

		g_motionTime3 += dt;

		if (g_motionTime3 > g_keyMax - 1.0f)//最大時間を超えたら
		{
			g_motionTime3 = g_keyMax - 1.0f;//最大最大時間にする

		}

		if (g_motionTime3 - i > 1.0f) //誤差を修正　想定の1.0を超えたら
		{
			i++;//次のキーフレームに入る
		}

		//接続の補間は　[i] * 1.0です、[i + 1] * 0.0ではない
		for (int j = 0; j < PART_MAX; j++)//パーツ番号
		{
			// Rotation
			g_player.part[j].srt.rot.x = g_anime[i].key[j].rot.x +				// 前のキーフレーム位置
				(g_anime[i + 1].key[j].rot.x - g_anime[i].key[j].rot.x)			// 前のキーフレームと次のキーフレームの差分
				* (g_motionTime3 - i);											// に　全体アニメ時間の小数点以下の割合をかける

			//g_player.part[j].srt.rot.y = g_anime[i].key[j].rot.y +				// 前のキーフレーム位置
			//	(g_anime[i + 1].key[j].rot.y - g_anime[i].key[j].rot.y)			// 前のキーフレームと次のキーフレームの差分
			//	* (g_motionTime3 - i);											// に　全体アニメ時間の小数点以下の割合をかける

			g_player.part[j].srt.rot.z = g_anime[i].key[j].rot.z +				// 前のキーフレーム位置
				(g_anime[i + 1].key[j].rot.z - g_anime[i].key[j].rot.z)			// 前のキーフレームと次のキーフレームの差分
				* (g_motionTime3 - i);											// に　全体アニメ時間の小数点以下の割合をかける

			 //Position
			g_player.part[j].srt.pos.x = g_anime[i].key[j].pos.x +				// 前のキーフレーム位置
				(g_anime[i + 1].key[j].pos.x - g_anime[i].key[j].pos.x)			// 前のキーフレームと次のキーフレームの差分
				* (g_motionTime3 - i);											// に　全体アニメ時間の小数点以下の割合をかける

			g_player.part[j].srt.pos.y = g_anime[i].key[j].pos.y +				// 前のキーフレーム位置
				(g_anime[i + 1].key[j].pos.y - g_anime[i].key[j].pos.y)			// 前のキーフレームと次のキーフレームの差分
				* (g_motionTime3 - i);											// に　全体アニメ時間の小数点以下の割合をかける

			g_player.part[j].srt.pos.z = g_anime[i].key[j].pos.z +				// 前のキーフレーム位置
				(g_anime[i + 1].key[j].pos.z - g_anime[i].key[j].pos.z)			// 前のキーフレームと次のキーフレームの差分
				* (g_motionTime3 - i);											// に　全体アニメ時間の小数点以下の割合をかける
		}

		//目の前の方向にモーションするように
		D3DXMatrixIdentity(&rotYMtx);
		D3DXMatrixRotationY(&rotYMtx,rotY);
		D3DXVec3TransformCoord(&g_player.part[BODY].srt.pos,
									&g_player.part[BODY].srt.pos,
									&rotYMtx);

		g_player.part[BODY].srt.pos.x = g_player.part[BODY].srt.pos.x + vctBuff3.x;		//原点ではなく、立っている場所で発動
		g_player.part[BODY].srt.pos.z = g_player.part[BODY].srt.pos.z + vctBuff3.z;

		g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	}

	PrintDebugProc("今のフレームパターン：%d \n\n", (int)g_motionTime3);

}

void AnimeTemp(KEY g_anime[])
{
	if (GetKeyboardRepeat(DIK_L))
	{
		if (keyFrameNum > 1)
		{
			g_keyMax = keyFrameNum;

			//アニメーション 
			int i = (int)g_motionTimeTemp;  //現在のキーフレームナンバー

			float dt = 1.0f / g_anime[i].frame;//補間の間隔時間

			//loopできるように
			if (i > g_keyMax - 2)//最大キーフレームナンバーを超えたら
			{
				i = 0;
				g_motionTimeTemp = 0.0f;

				dt = 0.0f;
			}

			g_motionTimeTemp += dt;

			if (g_motionTimeTemp > g_keyMax - 1.0f)//最大時間を超えたら
			{
				g_motionTimeTemp = g_keyMax - 1.0f;//最大最大時間にする
			}

			if (g_motionTimeTemp - i > 1.0f) //誤差を修正　想定の1.0を超えたら
			{
				i++;//次のキーフレームに入る
			}

			//if (GetKeyboardPress(DIK_SPACE))
			//{
			//	g_motionTimeTemp = 0.0f;	//リセット
			//	i = (int)g_motionTimeTemp;	//重要
			//}

				//接続の補間は　[i] * 1.0です、[i + 1] * 0.0ではない
			for (int j = 0; j < PART_MAX; j++)//パーツ番号
			{
				// Scale
				g_player.part[j].srt.scl.x = g_anime[i].key[j].scl.x +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].scl.x - g_anime[i].key[j].scl.x)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTimeTemp - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.scl.y = g_anime[i].key[j].scl.y +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].scl.y - g_anime[i].key[j].scl.y)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTimeTemp - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.scl.z = g_anime[i].key[j].scl.z +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].scl.z - g_anime[i].key[j].scl.z)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTimeTemp - i);											// に　全体アニメ時間の小数点以下の割合をかける

				// Rotation
				g_player.part[j].srt.rot.x = g_anime[i].key[j].rot.x +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].rot.x - g_anime[i].key[j].rot.x)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTimeTemp - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.rot.y = g_anime[i].key[j].rot.y +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].rot.y - g_anime[i].key[j].rot.y)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTimeTemp - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.rot.z = g_anime[i].key[j].rot.z +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].rot.z - g_anime[i].key[j].rot.z)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTimeTemp - i);											// に　全体アニメ時間の小数点以下の割合をかける

				// Position
				g_player.part[j].srt.pos.x = g_anime[i].key[j].pos.x +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].pos.x - g_anime[i].key[j].pos.x)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTimeTemp - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.pos.y = g_anime[i].key[j].pos.y +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].pos.y - g_anime[i].key[j].pos.y)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTimeTemp - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.pos.z = g_anime[i].key[j].pos.z +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].pos.z - g_anime[i].key[j].pos.z)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTimeTemp - i);											// に　全体アニメ時間の小数点以下の割合をかける
			}

			PrintDebugProc(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>{全体レビュー中}経過時間:%f  現在のキーフレーム番号:%d  フレーム数:%d \n\n", g_motionTimeTemp,i, pAnimeTemp[i].frame);
		}
	}

	else if(GetKeyboardRepeat(DIK_I))
	{
		if (reviewFrameNo2 > reviewFrameNo1)
		{
			g_keyMax = reviewFrameNo2 - reviewFrameNo1 +1;

			//アニメーション 
			int i = (int)g_motionTimeSR;  //現在のキーフレームナンバー

			float dt = 1.0f / g_anime[i].frame;//補間の間隔時間

			//reviewFrameNo1番号状態にリセット
			if ((i < reviewFrameNo1) || (i > reviewFrameNo2))
			{
				g_motionTimeSR = (float)reviewFrameNo1;
				i = reviewFrameNo1;

				dt = 0.0f;

				for (int j = 0; j < PART_MAX; j++)
				{
					g_player.part[j].srt.scl = pAnimeTemp[reviewFrameNo1].key[j].scl;
					g_player.part[j].srt.rot = pAnimeTemp[reviewFrameNo1].key[j].rot;
					g_player.part[j].srt.pos = pAnimeTemp[reviewFrameNo1].key[j].pos;
				}
			}

			

			//loopできるように
			if (i > reviewFrameNo2 - 1)//最大キーフレームナンバーを超えたら
			{
				g_motionTimeSR = (float)reviewFrameNo1;
				i = reviewFrameNo1;

				dt = 0.0f;
			}

			
			g_motionTimeSR += dt;

			if (g_motionTimeSR > (float)reviewFrameNo2)//最大時間を超えたら
			{
				g_motionTimeSR = (float)reviewFrameNo2;//最大最大時間にする
			}

			if (g_motionTimeSR - i > 1.0f) //誤差を修正　想定の1.0を超えたら
			{
				i++;//次のキーフレームに入る
			}

			//接続の補間は　[i] * 1.0です、[i + 1] * 0.0ではない
			for (int j = 0; j < PART_MAX; j++)//パーツ番号
			{
				// Scale
				g_player.part[j].srt.scl.x = g_anime[i].key[j].scl.x +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].scl.x - g_anime[i].key[j].scl.x)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTimeSR - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.scl.y = g_anime[i].key[j].scl.y +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].scl.y - g_anime[i].key[j].scl.y)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTimeSR - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.scl.z = g_anime[i].key[j].scl.z +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].scl.z - g_anime[i].key[j].scl.z)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTimeSR - i);											// に　全体アニメ時間の小数点以下の割合をかける

				// Rotation
				g_player.part[j].srt.rot.x = g_anime[i].key[j].rot.x +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].rot.x - g_anime[i].key[j].rot.x)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTimeSR - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.rot.y = g_anime[i].key[j].rot.y +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].rot.y - g_anime[i].key[j].rot.y)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTimeSR - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.rot.z = g_anime[i].key[j].rot.z +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].rot.z - g_anime[i].key[j].rot.z)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTimeSR - i);											// に　全体アニメ時間の小数点以下の割合をかける

				// Position
				g_player.part[j].srt.pos.x = g_anime[i].key[j].pos.x +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].pos.x - g_anime[i].key[j].pos.x)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTimeSR - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.pos.y = g_anime[i].key[j].pos.y +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].pos.y - g_anime[i].key[j].pos.y)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTimeSR - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.pos.z = g_anime[i].key[j].pos.z +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].pos.z - g_anime[i].key[j].pos.z)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTimeSR - i);											// に　全体アニメ時間の小数点以下の割合をかける
			}

			PrintDebugProc(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>{指定区間レビュー中}経過時間:%f  現在のキーフレーム番号:%d  フレーム数:%d \n\n", g_motionTimeSR, i, pAnimeTemp[i].frame);
		}

	}
}

void CreateAnimeTemp(int flameNum)
{

	pAnimeTemp[keyFrameSaveNo].frame = flameNum;

	for (int i = 0;i < PART_MAX;i++)
	{
		pAnimeTemp[keyFrameSaveNo].key[i].scl = g_player.part[i].srt.scl;
		pAnimeTemp[keyFrameSaveNo].key[i].rot = g_player.part[i].srt.rot;
		pAnimeTemp[keyFrameSaveNo].key[i].pos = g_player.part[i].srt.pos;
	}

	if (keyFrameSaveNo == keyFrameNum)
	{
		keyFrameNum++;
		keyFrameSaveNo++;
	}
	

};


void controller()
{

#ifdef _DEBUG
	//モードの入力
	if (GetKeyboardPress(DIK_F5))
	{
		g_mode = MODE_PLAY;
	}
	if (GetKeyboardPress(DIK_F6))
	{
		g_mode = MODE_EDIT;
	}
	if (GetKeyboardPress(DIK_F7))
	{
		g_mode = MODE_INGAME;
	}

	//コントロールIDの入力
	if (GetKeyboardPress(DIK_NUMPAD0))
	{
		g_conId = 0;
		partsShine = 1;
	}
	else if (GetKeyboardPress(DIK_NUMPAD1))
	{
		g_conId = 1;
		partsShine = 1;
	}
	else if (GetKeyboardPress(DIK_NUMPAD2))
	{
		g_conId = 2;
		partsShine = 1;
	}
	else if (GetKeyboardPress(DIK_NUMPAD3))
	{
		g_conId = 3;
		partsShine = 1;
	}
	else if (GetKeyboardPress(DIK_NUMPAD4))
	{
		g_conId = 4;
		partsShine = 1;
	}
	else if (GetKeyboardPress(DIK_NUMPAD5))
	{
		g_conId = 5;
		partsShine = 1;
	}
	else if (GetKeyboardPress(DIK_NUMPAD6))
	{
		g_conId = 6;
		partsShine = 1;
	}

	if (GetKeyboardTrigger(DIK_F9))
	{
		manual = !manual;
	}

	if (g_mode == MODE_EDIT)
	{

		if (GetKeyboardTrigger(DIK_F4))
		{
			LoadAnime(g_animeMemoy);
		}


		if (GetKeyboardPress(DIK_Q))
		{
			SRTMode = 0;//S
		}
		if (GetKeyboardPress(DIK_A))
		{
			SRTMode = 1;//R
		}
		if (GetKeyboardPress(DIK_Z))
		{
			SRTMode = 2;//T
		}

		if (GetKeyboardPress(DIK_S))
		{
			XYZMode = 0;//X
		}
		if (GetKeyboardPress(DIK_D))
		{
			XYZMode = 1;//Y
		}
		if (GetKeyboardPress(DIK_F))
		{
			XYZMode = 2;//Z
		}

		//モデルパーツのコントローラー
		switch (SRTMode)
		{
		case 0://縮小拡大					
			if (GetKeyboardRepeat(DIK_LEFT))
			{
				g_player.part[g_conId].srt.scl.x -= UNIT_S_PLAYER;
				g_player.part[g_conId].srt.scl.y -= UNIT_S_PLAYER;
				g_player.part[g_conId].srt.scl.z -= UNIT_S_PLAYER;
			}
			else if (GetKeyboardRepeat(DIK_RIGHT))
			{
				g_player.part[g_conId].srt.scl.x += UNIT_S_PLAYER;
				g_player.part[g_conId].srt.scl.y += UNIT_S_PLAYER;
				g_player.part[g_conId].srt.scl.z += UNIT_S_PLAYER;
			}
			break;

		case 1://回転
			switch (XYZMode)
			{
			case 0:
				//x軸回転
				if (GetKeyboardRepeat(DIK_LEFT))
				{
					g_player.part[g_conId].srt.rot.x += UNIT_R_PLAYER;

				}
				else if (GetKeyboardRepeat(DIK_RIGHT))
				{
					g_player.part[g_conId].srt.rot.x -= UNIT_R_PLAYER;

				}
				break;
			case 1:
				//y軸回転
				if (GetKeyboardRepeat(DIK_LEFT))
				{
					g_player.part[g_conId].srt.rot.y += UNIT_R_PLAYER;
					//if (g_player.part[g_conId].srt.rot.y > D3DX_PI)
					//{
					//	g_player.part[g_conId].srt.rot.y -= D3DX_PI * 2.0f;
					//}
				}
				else if (GetKeyboardRepeat(DIK_RIGHT))
				{
					g_player.part[g_conId].srt.rot.y -= UNIT_R_PLAYER;
					//if (g_player.part[g_conId].srt.rot.y < -D3DX_PI)
					//{
					//	g_player.part[g_conId].srt.rot.y += D3DX_PI * 2.0f;
					//}
				}
				break;
			case 2:
				//z軸回転
				if (GetKeyboardRepeat(DIK_LEFT))
				{
					g_player.part[g_conId].srt.rot.z += UNIT_R_PLAYER;
					//if (g_player.part[g_conId].srt.rot.z > D3DX_PI)
					//{
					//	g_player.part[g_conId].srt.rot.z -= D3DX_PI * 2.0f;
					//}
				}
				else if (GetKeyboardRepeat(DIK_RIGHT))
				{
					g_player.part[g_conId].srt.rot.z -= UNIT_R_PLAYER;
					//if (g_player.part[g_conId].srt.rot.z < -D3DX_PI)
					//{
					//	g_player.part[g_conId].srt.rot.z += D3DX_PI * 2.0f;
					//}
				}
				break;
			}
			break;

		case 2://移動
			switch (XYZMode)
			{
			case 0:
				//x軸移動
				if (GetKeyboardRepeat(DIK_LEFT))
				{
					g_player.part[g_conId].srt.pos.x -= UNIT_T_PLAYER;
				}
				else if (GetKeyboardRepeat(DIK_RIGHT))
				{
					g_player.part[g_conId].srt.pos.x += UNIT_T_PLAYER;
				}
				break;
			case 1:
				//y軸移動
				if (GetKeyboardRepeat(DIK_LEFT))
				{
					g_player.part[g_conId].srt.pos.y -= UNIT_T_PLAYER;
				}
				else if (GetKeyboardRepeat(DIK_RIGHT))
				{
					g_player.part[g_conId].srt.pos.y += UNIT_T_PLAYER;
				}
				break;
			case 2:
				//z軸移動
				if (GetKeyboardRepeat(DIK_LEFT))
				{
					g_player.part[g_conId].srt.pos.z -= UNIT_T_PLAYER;
				}
				else if (GetKeyboardRepeat(DIK_RIGHT))
				{
					g_player.part[g_conId].srt.pos.z += UNIT_T_PLAYER;
				}
				break;
			}
			break;

		}

		//今の運動状態を保存
		if (GetKeyboardTrigger(DIK_NUMPADENTER))
		{
			CreateAnimeTemp(diyFrame);
		}

		//デフォルト状態になる
		if (GetKeyboardTrigger(DIK_SPACE))
		{
			for (int j = 0; j < PART_MAX; j++)
			{
				g_player.part[j].srt.scl = pAnimeTemp[0].key[j].scl;
				g_player.part[j].srt.rot = pAnimeTemp[0].key[j].rot;
				//g_player.part[j].srt.pos = pAnimeTemp[0].key[j].pos;
			}
		}


		if (GetKeyboardPress(DIK_1))
		{
			functionMode = 1;

		}
		if (GetKeyboardPress(DIK_2))
		{
			functionMode = 2;

		}
		if (GetKeyboardPress(DIK_3))
		{
			functionMode = 3;

		}
		if (GetKeyboardPress(DIK_4))
		{
			functionMode = 4;

		}
		if (GetKeyboardPress(DIK_5))
		{
			functionMode = 5;

		}


		if (functionMode == 1)
		{
			if (GetKeyboardRepeat(DIK_MINUS))
			{
				if (keyFrameSaveNo > 0)
				{
					keyFrameSaveNo--;
				}
			}

			if (GetKeyboardRepeat(DIK_EQUALS))
			{
				if ((keyFrameSaveNo + 1) <= keyFrameNum)
				{
					keyFrameSaveNo++;
				}
			}
		}

		if (functionMode == 2)
		{
			if (GetKeyboardRepeat(DIK_MINUS))
			{
				if (diyFrame > 0)
				{
					diyFrame--;
				}
			}

			if (GetKeyboardRepeat(DIK_EQUALS))
			{
				diyFrame++;
			}
		}

		if (functionMode == 3)
		{
			if (GetKeyboardRepeat(DIK_MINUS))
			{
				if (reviewNo > 0)
				{
					reviewNo--;
				}
			}

			if (GetKeyboardRepeat(DIK_EQUALS))
			{
				if ((reviewNo + 1) < keyFrameNum)
				{
					reviewNo++;
				}
			}
		}

		if (functionMode == 4)
		{
			if (GetKeyboardRepeat(DIK_MINUS))
			{
				if (reviewFrameNo1 > 0)
				{
					reviewFrameNo1--;
				}
			}

			if (GetKeyboardRepeat(DIK_EQUALS))
			{
				if ((reviewFrameNo1 + 1) < keyFrameNum)
				{
					reviewFrameNo1++;
				}
			}
		}

		if (functionMode == 5)
		{
			if (GetKeyboardRepeat(DIK_MINUS))
			{
				if (reviewFrameNo2 > 0)
				{
					reviewFrameNo2--;
				}
			}

			if (GetKeyboardRepeat(DIK_EQUALS))
			{
				if ((reviewFrameNo2 + 1) < keyFrameNum)
				{
					reviewFrameNo2++;
				}
			}
		}


		if (GetKeyboardTrigger(DIK_P))
		{

			for (int j = 0; j < PART_MAX; j++)
			{
				g_player.part[j].srt.scl = pAnimeTemp[reviewNo].key[j].scl;
				g_player.part[j].srt.rot = pAnimeTemp[reviewNo].key[j].rot;
				g_player.part[j].srt.pos = pAnimeTemp[reviewNo].key[j].pos;
			}
		}

	}


#endif


}

void DebugUI()
{
#ifdef _DEBUG

	PrintDebugProc("モード：[");
	switch (g_mode)
	{
	case 0:
		PrintDebugProc("プレイ");
		break;
	case 1:
		PrintDebugProc("エディター");
		break;
	case 2:
		PrintDebugProc("インゲーム");
		break;

	}
	PrintDebugProc("]\n\n");

	if (g_mode == MODE_EDIT)
	{
		PrintDebugProc("パーツ操作方法[F9]：\n");
		if (manual)
		{
			PrintDebugProc("テンキーの[0]～[6]:パーツ切換\n");
			PrintDebugProc("[Q][A][Z]:SRT切換 \n");
			PrintDebugProc("[S][D][F]:XYZ切換 \n");
			PrintDebugProc("[<-][->](Repeat):SRT値を加減する \n");
			PrintDebugProc("[SPACE]:デフォルト状態に復元\n");
			PrintDebugProc("[F2]:外部ファイルへの出力(閉じると自動実行)\n");
			PrintDebugProc("[F4]:外部データをロード\n");
		}
		PrintDebugProc("\n");

		PrintDebugProc(">>>>>>>>>>>>現在の操作：[");
		switch (g_conId)
		{
		case 0:
			PrintDebugProc("体");
			break;
		case 1:
			PrintDebugProc("頭");
			break;
		case 2:
			PrintDebugProc("左手");
			break;
		case 3:
			PrintDebugProc("右手");
			break;
		case 4:
			PrintDebugProc("左足");
			break;
		case 5:
			PrintDebugProc("右足");
			break;
		case 6:
			PrintDebugProc("剣");
			break;
		}
		PrintDebugProc("]");


		PrintDebugProc("[");
		switch (SRTMode)
		{
		case 0:
			PrintDebugProc("拡大");
			break;
		case 1:
			PrintDebugProc("回転");
			break;
		case 2:
			PrintDebugProc("移動");
			break;

		}
		PrintDebugProc("]");

		if (SRTMode != 0)
		{
			PrintDebugProc("[");
			switch (XYZMode)
			{
			case 0:
				PrintDebugProc("X軸");
				break;
			case 1:
				PrintDebugProc("Y軸");
				break;
			case 2:
				PrintDebugProc("Z軸");
				break;

			}
			PrintDebugProc("]");
		}
		else
		{
			PrintDebugProc("[3軸]");
		}


		PrintDebugProc("\n\n");

	}

	PrintDebugProc("[");
	switch (g_conId)
	{
	case 0:
		PrintDebugProc("体");
		break;
	case 1:
		PrintDebugProc("頭");
		break;
	case 2:
		PrintDebugProc("左手");
		break;
	case 3:
		PrintDebugProc("右手");
		break;
	case 4:
		PrintDebugProc("左足");
		break;
	case 5:
		PrintDebugProc("右足");
		break;
	case 6:
		PrintDebugProc("剣");
		break;
	}

	PrintDebugProc("]のSRT値:\n");


	if (SRTMode == 0)
	{
		PrintDebugProc("●●●●●●");

		PrintDebugProc("[S：(★%f : %f : %f★)]", g_player.part[g_conId].srt.scl.x,
			g_player.part[g_conId].srt.scl.y,
			g_player.part[g_conId].srt.scl.z);


	}
	else
	{
		PrintDebugProc("[S：(%f : %f : %f)]", g_player.part[g_conId].srt.scl.x,
			g_player.part[g_conId].srt.scl.y,
			g_player.part[g_conId].srt.scl.z);

	}

	if (SRTMode == 0)
	{
		PrintDebugProc("●");
	}
	PrintDebugProc("\n");



	if (SRTMode == 1)
	{
		PrintDebugProc("●●●●●●");

		switch (XYZMode)
		{
		case 0:
			PrintDebugProc("[R：(★%f★ : %f : %f)]", g_player.part[g_conId].srt.rot.x,
				g_player.part[g_conId].srt.rot.y,
				g_player.part[g_conId].srt.rot.z);


			break;
		case 1:
			PrintDebugProc("[R：(%f : ★%f★ : %f)]", g_player.part[g_conId].srt.rot.x,
				g_player.part[g_conId].srt.rot.y,
				g_player.part[g_conId].srt.rot.z);


			break;
		case 2:
			PrintDebugProc("[R：(%f : %f : ★%f★)]", g_player.part[g_conId].srt.rot.x,
				g_player.part[g_conId].srt.rot.y,
				g_player.part[g_conId].srt.rot.z);


			break;

		}
	}
	else
	{
		PrintDebugProc("[R：(%f : %f : %f)]", g_player.part[g_conId].srt.rot.x,
			g_player.part[g_conId].srt.rot.y,
			g_player.part[g_conId].srt.rot.z);
	}

	if (SRTMode == 1)
	{
		PrintDebugProc("●●");
	}
	PrintDebugProc("\n");




	if (SRTMode == 2)
	{
		PrintDebugProc("●●●●●●");

		switch (XYZMode)
		{
		case 0:
			PrintDebugProc("[T：(★%f★ : %f : %f)]", g_player.part[g_conId].srt.pos.x,
				g_player.part[g_conId].srt.pos.y,
				g_player.part[g_conId].srt.pos.z);


			break;
		case 1:
			PrintDebugProc("[T：(%f : ★%f★ : %f)]", g_player.part[g_conId].srt.pos.x,
				g_player.part[g_conId].srt.pos.y,
				g_player.part[g_conId].srt.pos.z);


			break;
		case 2:
			PrintDebugProc("[T：(%f : %f : ★%f★)]", g_player.part[g_conId].srt.pos.x,
				g_player.part[g_conId].srt.pos.y,
				g_player.part[g_conId].srt.pos.z);


			break;

		}

	}
	else
	{
		PrintDebugProc("[T：(%f : %f : %f)]", g_player.part[g_conId].srt.pos.x,
			g_player.part[g_conId].srt.pos.y,
			g_player.part[g_conId].srt.pos.z);

	}

	if (SRTMode == 2)
	{
		PrintDebugProc("●●●");
	}
	PrintDebugProc("\n\n");
	
	if (g_mode == MODE_EDIT)
	{
		PrintDebugProc("現在保存されたキーフレームの総数:%d \n", keyFrameNum);

		if ((functionMode == 1) || (functionMode == 2))
		{
			PrintDebugProc("■■■■■■");
		}
		
		if (functionMode == 1)
		{
			PrintDebugProc("次に保存するキーフレーム番号:★%d★  保存フレーム数:%d ", keyFrameSaveNo, diyFrame);
		}
		else if (functionMode == 2)
		{
			PrintDebugProc("次に保存するキーフレーム番号:%d  保存フレーム数:★%d★ ", keyFrameSaveNo, diyFrame);
		}
		else
		{
			PrintDebugProc("次に保存するキーフレーム番号:%d  保存フレーム数:%d ", keyFrameSaveNo, diyFrame);
		}

		if (functionMode == 1)
		{
			PrintDebugProc("■\n");
		}
		else if(functionMode == 2)
		{
			PrintDebugProc("■■\n");
		}
		else
		{
			PrintDebugProc("\n");
		}

		PrintDebugProc("変更:[1] [2][-][+]  [NUMPADENTER]:今の運動状態を保存\n\n");


		if (functionMode == 3)
		{
			PrintDebugProc("■■■■■■");
		}

		if (functionMode == 3)
		{
			PrintDebugProc("個別レビューのキーフレーム番号:★%d★(フレーム数:%d) ", reviewNo, pAnimeTemp[reviewNo].frame);
		}
		else
		{
			PrintDebugProc("個別レビューのキーフレーム番号:%d(フレーム数:%d) ", reviewNo, pAnimeTemp[reviewNo].frame);
		}
		

		if (functionMode == 3)
		{
			PrintDebugProc("■■■\n");
		}
		else
		{
			PrintDebugProc("\n");
		}


		PrintDebugProc("変更:[3][-][+]  [P]:個別レビュー  [L]:全体レビュー\n\n");


		if ((functionMode == 4) || (functionMode == 5))
		{
			PrintDebugProc("■■■■■■");
		}


		if (functionMode == 4)
		{
			PrintDebugProc("指定区間レビューのキーフレーム番号:★%d★～%d ", reviewFrameNo1, reviewFrameNo2);
		}
		else if (functionMode == 5)
		{
			PrintDebugProc("指定区間レビューのキーフレーム番号:%d～★%d★ ", reviewFrameNo1, reviewFrameNo2);
		}
		else
		{
			PrintDebugProc("指定区間レビューのキーフレーム番号:%d～%d ", reviewFrameNo1, reviewFrameNo2);
		}

		if (functionMode == 4)
		{
			PrintDebugProc("■■■■\n");
		}
		else if (functionMode == 5)
		{
			PrintDebugProc("■■■■■\n");
		}
		else
		{
			PrintDebugProc("\n");
		}

		PrintDebugProc("変更:[4]～[5][-][+]  [I]:区間レビュー\n\n");


	}

	if (g_mode == MODE_INGAME)
	{
		PrintDebugProc("目的向き：%f \n", g_player.rotDest.y);
		PrintDebugProc("プレイヤーの運動量：%f,%f,%f \n", g_player.move.x, g_player.move.y, g_player.move.z);
	}

#endif


}


void LoadAnime(KEY *g_anime)
{
	if (pAnimeTemp != g_animeMemoy) 
	{
		free(pAnimeTemp);	//ヒープ領域の解放
	}
	

	pAnimeTemp = g_anime;

	keyFrameNum = sizeof(g_animeMemoy) / sizeof(KEY);

	keyFrameSaveNo = keyFrameNum;

	reviewNo = reviewFrameNo1 = reviewFrameNo2 = 0;

	diyFrame = 60;
}






