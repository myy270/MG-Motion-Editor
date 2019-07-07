//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : ���p�j
//
//=============================================================================
#include "player.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define	BODY_PLAYER			"data/MODEL/mere god/body.x"	// �ǂݍ��ރ��f����
#define	HEAD_PLAYER			"data/MODEL/mere god/head.x"	// �ǂݍ��ރ��f����
#define	HAND_L_PLAYER		"data/MODEL/mere god/hand_L.x"	// �ǂݍ��ރ��f����
#define	HAND_R_PLAYER		"data/MODEL/mere god/hand_R.x"	// �ǂݍ��ރ��f����
#define	LEG_L_PLAYER		"data/MODEL/mere god/leg_L.x"	// �ǂݍ��ރ��f����
#define	LEG_R_PLAYER		"data/MODEL/mere god/leg_R.x"	// �ǂݍ��ރ��f����
#define	SWORD_PLAYER		"data/MODEL/mere god/sword.x"		// �ǂݍ��ރ��f����

#define	TEXTURE_PLAYER		"data/MODEL/mere god/knight.png"		// �ǂݍ��ރ��f����
#define	TEXTURE_SWORD		"data/MODEL/mere god/kenn.png"		// �ǂݍ��ރ��f����

#define	PLAYER_RADIUS		(15.0f)						// ���a

#define	VALUE_MOVE_PLAYER	(0.195f)					// �ړ����x
#define	RATE_MOVE_PLAYER	(0.025f)					// �ړ������W��

#define	UNIT_S_PLAYER	(0.1f)						// �g��P��
#define	UNIT_R_PLAYER	(D3DXToRadian(5))			// ��]�P�ʁ@5�x
#define UNIT_T_PLAYER	(1.0f)						// �ړ��P��

#define	RATE_ROTATE_PLAYER	(0.10f)						// ��]�����W��



extern HWND hWnd;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void WriteAnime();
void AnimeWalk(KEY g_anime[]);
void AnimeKen(KEY g_anime[]);
void AnimeKen3(KEY g_anime[]);
void AnimeTemp(KEY g_anime[]);
void CreateAnimeTemp(int flameNum = 60);
void DebugUI();
void controller();

void LoadAnime(KEY *g_anime);	//�O���̃f�[�^��ǂ�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer;		// �e�N�X�`���ǂݍ��ݏꏊ
LPDIRECT3DTEXTURE9	g_pD3DTextureSword;		// �e�N�X�`���ǂݍ��ݏꏊ
PLAYER				g_player;					// �v���C���[���[�N

int g_mode = MODE_EDIT;//�ҏS���[�h���ǂ���

int SRTMode = 0;
int XYZMode = 0;

int g_conId = 0;	//�f�t�H���g�̃R���g���[��ID

bool manual = 1;//�������

float g_motionTime = 0.0f;	// �A�j���[�V�����S�̎��ԁ@����
float g_motionTime2 = 0.0f;	// �A�j���[�V�����S�̎��ԁ@������
float g_motionTime3 = 0.0f;	// �A�j���[�V�����S�̎��ԁ@�W�����v�a��
float g_motionTimeTemp = 0.0f;	// �A�j���[�V�����S�̎��ԁ@�Վ�

float g_motionTimeSR = 0.0f;	// �A�j���[�V�����S�̎��ԁ@�Վ�




int g_keyMax;				//�L�[�t���[���̐�

bool g_animeState = 0;		//�^����Ԃ��ǂ����@����
bool g_animeStateKen = 0;
bool g_animeStateKen3= 0;

float g_cancelTime = 0.0f;// �ŏ���Ԃɖ߂鎞�� ����

D3DXMATRIX mtxBuff;
D3DXMATRIX mtxBuff3;

D3DXVECTOR3 vctBuff3;
float rotY;	//�W�����v�a��𔭓����̕������L�^����

D3DXMATRIX rotYMtx;

bool partsShine;

//����L�[���
KEY g_animeWalk[] =
{
	{
		15,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S ���̊g��͑S���̃p�[�c�ɔ��f����
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T�@�n�ʂƂ̋����i���̐��l�͎����Ńe�X�g���ē�����́j
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

//������
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

//�W�����v�a��
KEY g_animeKen3[] =
{
		{
		30,
		{
			{// �p�[�c�ԍ�:0 
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// �p�[�c�ԍ�:1 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// �p�[�c�ԍ�:2 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// �p�[�c�ԍ�:3 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// �p�[�c�ԍ�:4 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// �p�[�c�ԍ�:5 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// �p�[�c�ԍ�:6 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-0.7900f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////�L�[�t���[���ԍ�:0 

	{
		40,
		{
			{// �p�[�c�ԍ�:0 
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.5498f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,85.7199f,-137.4752f),//T
			},

			{// �p�[�c�ԍ�:1 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-0.1571f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// �p�[�c�ԍ�:2 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(3.5517f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// �p�[�c�ԍ�:3 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(2.7489f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// �p�[�c�ԍ�:4 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-0.8639f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// �p�[�c�ԍ�:5 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-0.3927f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// �p�[�c�ԍ�:6 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-0.7900f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////�L�[�t���[���ԍ�:1 

	{
		15,
		{
			{// �p�[�c�ԍ�:0 
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(-0.2356f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,-316.4919f),//T
			},

			{// �p�[�c�ԍ�:1 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-0.1571f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// �p�[�c�ԍ�:2 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.7069f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// �p�[�c�ԍ�:3 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.4451f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// �p�[�c�ԍ�:4 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.7069f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// �p�[�c�ԍ�:5 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-0.7069f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// �p�[�c�ԍ�:6 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0472f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-0.7900f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////�L�[�t���[���ԍ�:2 

	{
		1000,
		{
			{// �p�[�c�ԍ�:0 
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,-316.4919f),//T
			},

			{// �p�[�c�ԍ�:1 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// �p�[�c�ԍ�:2 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// �p�[�c�ԍ�:3 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// �p�[�c�ԍ�:4 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// �p�[�c�ԍ�:5 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// �p�[�c�ԍ�:6 
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-0.7900f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////�L�[�t���[���ԍ�:3 

};


//�O���̃t�@�C�������[�h�p
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


//�G�f�B�^�[�p
KEY *pAnimeTemp;

int keyFrameNum;//�ۑ�����L�[�t���[���̑���

int keyFrameSaveNo;//���ɕۑ�����L�[�t���[���̔ԍ�

int functionMode;

int reviewNo;//�ʃ��r���[����L�[�t���[���̔ԍ�

int reviewFrameNo1;//��ԃ��r���[����n�_�L�[�t���[���̔ԍ�
int reviewFrameNo2;//��ԃ��r���[����I�_�L�[�t���[���̔ԍ�

int diyFrame = 60;


//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	pAnimeTemp = (KEY *)malloc(sizeof(KEY) * 256);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_player.part[0].partFile = (char *)BODY_PLAYER;//�e�͈�Ԑ�ɂ��Ȃ���΂Ȃ�Ȃ�
	g_player.part[1].partFile = (char *)HEAD_PLAYER;//(const char *)����(char *)�ɕϊ�
	g_player.part[2].partFile = (char *)HAND_L_PLAYER;//����
	g_player.part[3].partFile = (char *)HAND_R_PLAYER;//�E��
	g_player.part[4].partFile = (char *)LEG_L_PLAYER;//����
	g_player.part[5].partFile = (char *)LEG_R_PLAYER;//�E��

	g_player.part[6].partFile = (char *)SWORD_PLAYER;//�E��̌�

	for (int i = 0; i < PART_MAX; i++)//�p�[�c�ԍ�
	{
		// X�t�@�C���̓ǂݍ���
		if(FAILED(D3DXLoadMeshFromX(g_player.part[i].partFile,
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_player.part[i].pMatBuff,
									NULL,
									&g_player.part[i].nNumMat,
									&g_player.part[i].pMesh)))
		{
			MessageBox(hWnd, _T("X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���"), _T("error"), MB_OK | MB_ICONERROR);
			return E_FAIL;
		}

		switch (i)
		{//�����l
		case 0:
		{//��
			g_player.part[i].srt.scl = D3DXVECTOR3(2.0f, 2.0f, 2.0f);//xyz�K�������悤��
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(0.0f, 28.0f, 0.0f);// pos.y�͑����n�ʂɐG���悤�Ȑ��l

			g_player.part[i].parent = NULL;//�̂̐e��NULL�ɂ���
			break;
		}
		case 1:
		{//��
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(0.0f, 7.06f,  0.09f);

			g_player.part[i].parent = &g_player.part[0];//�̂�e�ɂ���
			break;
		}
		case 2:
		{//����
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(7.01f, 4.82f, -0.49f);

			g_player.part[i].parent = &g_player.part[0];//�̂�e�ɂ���
			break;
		}
		case 3:
		{//�E��
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(-7.01f, 4.82f, -0.49f);

			g_player.part[i].parent = &g_player.part[0];//�̂�e�ɂ���
			break;
		}
		case 4:
		{//����
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(2.0f, -4.00f, 0.0f);

			g_player.part[i].parent = &g_player.part[0];//�̂�e�ɂ���
			break;
		}
		case 5:
		{//�E��
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(-2.0f, -4.00f, 0.0f);

			g_player.part[i].parent = &g_player.part[0];//�̂�e�ɂ���
			break;
		}
		case 6:
		{//�E��̌�
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
			g_player.part[i].srt.pos = D3DXVECTOR3(-0.92f, -7.19f, -0.79f);	//�����̐��l�v���ӁA���ɂ��̕���

			g_player.part[i].parent = &g_player.part[3];//�E���e�ɂ���I�I
			break;
		}

		}

		g_player.part[i].use = true;

	}

	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.fRadius = PLAYER_RADIUS;	//�e�̃T�C�Y�p�A�����蔻��p�@

	g_player.state = NORMAL;
	

#if 1
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PLAYER,			// �t�@�C���̖��O
								&g_pD3DTexturePlayer);	// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SWORD,				// �t�@�C���̖��O
								&g_pD3DTextureSword);	// �ǂݍ��ރ������[


#endif

	CreateAnimeTemp(diyFrame);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	//�^�����������o��
	WriteAnime();

	for (int i = 0; i < PART_MAX; i++)//�p�[�c�ԍ�
	{
		if (g_player.part[i].pMesh != NULL)
		{// ���b�V���̊J��
			g_player.part[i].pMesh->Release();
			g_player.part[i].pMesh = NULL;
		}

		if (g_player.part[i].pMatBuff != NULL)
		{// �}�e���A���̊J��
			g_player.part[i].pMatBuff->Release();
			g_player.part[i].pMatBuff = NULL;
		}
	}

	if (g_pD3DTexturePlayer != NULL)
	{// �e�N�X�`���̊J��
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
// �X�V����
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

		// �J�����̌����擾
		rotCamera = GetRotCamera();

		g_animeState = 0;//�^����Ԃ����Z�b�g

		//�ړ�
		if (GetKeyboardPress(DIK_A) || IsButtonPress(0, BUTTON_LEFT) || IsButtonPress(0, BUTTON_LSTICK_LEFT))
		{
			g_animeState = 1;//������Ԃɂ���

			if (GetKeyboardPress(DIK_W) || IsButtonPress(0, BUTTON_UP) || IsButtonPress(0, BUTTON_LSTICK_UP))
			{// ���O�ړ�
				g_player.move.x -= sinf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.75f;
			}
			else if (GetKeyboardPress(DIK_S) || IsButtonPress(0, BUTTON_DOWN) || IsButtonPress(0, BUTTON_LSTICK_DOWN))
			{// ����ړ�
				g_player.move.x -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.25f;
			}
			else
			{// ���ړ�
				g_player.move.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.50f;
			}
		}
		else if (GetKeyboardPress(DIK_D) || IsButtonPress(0, BUTTON_RIGHT) || IsButtonPress(0, BUTTON_LSTICK_RIGHT))
		{
			g_animeState = 1;//������Ԃɂ���

			if (GetKeyboardPress(DIK_W) || IsButtonPress(0, BUTTON_UP) || IsButtonPress(0, BUTTON_LSTICK_UP))
			{// �E�O�ړ�
				g_player.move.x -= sinf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.75f;
			}
			else if (GetKeyboardPress(DIK_S) || IsButtonPress(0, BUTTON_DOWN) || IsButtonPress(0, BUTTON_LSTICK_DOWN))
			{// �E��ړ�
				g_player.move.x -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.25f;
			}
			else
			{// �E�ړ�
				g_player.move.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.50f;
			}
		}
		else if (GetKeyboardPress(DIK_W) || IsButtonPress(0, BUTTON_UP) || IsButtonPress(0, BUTTON_LSTICK_UP))
		{
			g_animeState = 1;//������Ԃɂ���

			// �O�ړ�
			g_player.move.x -= sinf(D3DX_PI + rotCamera.y) * VALUE_MOVE_PLAYER;
			g_player.move.z -= cosf(D3DX_PI + rotCamera.y) * VALUE_MOVE_PLAYER;

			g_player.rotDest.y = D3DX_PI + rotCamera.y;
		}
		else if (GetKeyboardPress(DIK_S) || IsButtonPress(0, BUTTON_DOWN) || IsButtonPress(0, BUTTON_LSTICK_DOWN))
		{
			g_animeState = 1;//������Ԃɂ���

			// ��ړ�
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

		

		// �ړI�̊p�x�܂ł̍���
		fDiffRotY = g_player.rotDest.y - g_player.part[0].srt.rot.y;//�̂����
		if (fDiffRotY > D3DX_PI)
		{
			fDiffRotY -= D3DX_PI * 2.0f;
		}
		if (fDiffRotY < -D3DX_PI)
		{
			fDiffRotY += D3DX_PI * 2.0f;
		}

		// �ړI�̊p�x�܂Ŋ�����������@�i�X�ړI�̊p�x�ɕω�����
		g_player.part[0].srt.rot.y += fDiffRotY * RATE_ROTATE_PLAYER;//�̂ɔ��f
		if (g_player.part[0].srt.rot.y > D3DX_PI)
		{
			g_player.part[0].srt.rot.y -= D3DX_PI * 2.0f;
		}
		if (g_player.part[0].srt.rot.y < -D3DX_PI)
		{
			g_player.part[0].srt.rot.y += D3DX_PI * 2.0f;
		}

		// �ʒu�ړ��𔽉f
		g_player.part[0].srt.pos.x += g_player.move.x;//�̂ɔ��f
		g_player.part[0].srt.pos.y += g_player.move.y;
		g_player.part[0].srt.pos.z += g_player.move.z;

		//�ړ��͈́@//�̂����
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

		// �ړ��ʂɊ�����������@�^���G�l���M�[���ꕔ�����ĕۑ�����A���̃t���[���Ɏg��
		//���̕����C�R�[�����̃t���[���Ɋl���̉^���G�l���M�[�̏ꍇ�A���x���ő�(6.05f)�ɂȂ��āA���������^���ɂȂ�
		g_player.move.x += (0.0f - g_player.move.x) * RATE_MOVE_PLAYER;//�����Ag_player.move.x = g_player.move.x * (1 - RATE_MOVE_PLAYER;)
		g_player.move.y += (0.0f - g_player.move.y) * RATE_MOVE_PLAYER;
		g_player.move.z += (0.0f - g_player.move.z) * RATE_MOVE_PLAYER;

		break;
	}



	}//switch end


	DebugUI();


	//�^�����������o��
	if (GetKeyboardTrigger(DIK_F2))
	{
		WriteAnime();
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;
	D3DXMATERIAL *pD3DXMat;

	D3DMATERIAL9 matDef;
	pDevice->GetMaterial(&matDef);// �f�t�H���g�̃}�e���A�����擾

	for (int i = 0; i < PART_MAX; i++)//�p�[�c�ԍ�
	{
		if (g_player.part[i].use)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, g_player.part[i].srt.scl.x,
				g_player.part[i].srt.scl.y,
				g_player.part[i].srt.scl.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);
			
			g_player.part[i].mtxS = mtxScl;

			//if ((g_animeStateKen3) && (i == BODY))
			//{
			//	// �ړ��𔽉f
			//	D3DXMatrixTranslation(&mtxTranslate, g_player.part[i].srt.pos.x,
			//		g_player.part[i].srt.pos.y,
			//		g_player.part[i].srt.pos.z);
			//	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

			//	g_player.part[i].mtxT = mtxTranslate;

			//	// ��]�𔽉f
			//	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.part[i].srt.rot.y,
			//		g_player.part[i].srt.rot.x,
			//		g_player.part[i].srt.rot.z);
			//	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

			//	g_player.part[i].mtxR = mtxRot;


			//}
			//else
			
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.part[i].srt.rot.y,
				g_player.part[i].srt.rot.x,
				g_player.part[i].srt.rot.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

			g_player.part[i].mtxR = mtxRot;

			// �ړ��𔽉f



			D3DXMatrixTranslation(&mtxTranslate, g_player.part[i].srt.pos.x,
				g_player.part[i].srt.pos.y,
				g_player.part[i].srt.pos.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

			g_player.part[i].mtxT = mtxTranslate;
			

			



			//�e�����݂���ꍇ�͐e�̃��[���h�}�g���N�X������
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



			g_player.part[i].mtxWorld = mtxWorld;//���[���h�}�g���N�X��ۑ�

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)g_player.part[i].pMatBuff->GetBufferPointer();

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTexturePlayer);

			if (i == SWORD_R)
			{
				pDevice->SetTexture(0, g_pD3DTextureSword);

			}

			//�I�����ꂽ�p�[�c������
			if (i == g_conId)
			{
				if (partsShine == 1)
				{
					pDevice->SetTexture(0, NULL);
				}
				
			}


			for (int nCntMat = 0; nCntMat < (int)g_player.part[i].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �`��
				g_player.part[i].pMesh->DrawSubset(nCntMat);
			}
			
		}
	}
	pDevice->SetMaterial(&matDef);// �}�e���A�����f�t�H���g�ɖ߂�
}

//=============================================================================
// �v���C���[���擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_player;
}

//=============================================================================
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionPlayer(void)
{
	return g_player.part[0].srt.pos;//�̂����
}

//=============================================================================
// �����擾
//=============================================================================
D3DXVECTOR3 GetRotationPlayer(void)
{
	return g_player.part[0].srt.rot;//�̂����
}

//=============================================================================
// �ړI�̌����擾
//=============================================================================
D3DXVECTOR3 GetRotationDestPlayer(void)
{
	return g_player.rotDest;
}

//=============================================================================
// �ړ��ʎ擾
//=============================================================================
D3DXVECTOR3 GetMovePlayer(void)
{
	return g_player.move;
}

// �A�j�������o��
void WriteAnime()
{
#ifdef _DEBUG

	FILE *fp;
	fp = fopen("animeTemp.txt", "a+");//"a+"�͏������݂̃��[�h�B�t�@�C�����Ȃ��ƁA�����ɍ쐬
	if (fp == NULL)
	{
		return;
	}

	fprintf(fp, "������������������������������������������������������NEW������������������������������������������������������\n");

	for (int i = 0; i < keyFrameNum; i++)
	{
		//\t�@�����^�u
		fprintf(fp, "\t{\n");
		fprintf(fp, "\t\t%d,\n", pAnimeTemp[i].frame);//�t���[����
		fprintf(fp, "\t\t{\n");

		for (int j = 0; j < PART_MAX; j++)
		{
			fprintf(fp, "\t\t\t{// �p�[�c�ԍ�:%d \n", j);
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
		fprintf(fp, "\t},///////////////////////////////////////////////////////////////////////////////////�L�[�t���[���ԍ�:%d \n",i);
		fprintf(fp, "\n");

	}

	fclose(fp);

#endif

}


void AnimeWalk(KEY g_anime[])
{
	g_keyMax = sizeof(g_animeWalk) / sizeof(KEY);//sizeof(g_anime)�ł̓_��

	switch (g_mode)
	{
	case MODE_PLAY:
	{
		//�A�j���[�V���� 
		int i = (int)g_motionTime;  //���݂̃L�[�t���[���i���o�[

		//if (i > g_keyMax - 2)//�ő�L�[�t���[���i���o�[�𒴂�����
		//{
		//	i = g_keyMax - 2;//�ő�L�[�t���[���i���o�[�ɂ���
		//}

		//loop�ł���悤��
		if (i > g_keyMax - 2)//�ő�L�[�t���[���i���o�[�𒴂�����
		{
			i = 1;
			g_motionTime = 1.0f;
		}

		float dt = 1.0f / g_anime[i].frame;//��Ԃ̊Ԋu����

		g_motionTime += dt;

		if (g_motionTime > g_keyMax - 1.0f)//�ő厞�Ԃ𒴂�����
		{
			g_motionTime = g_keyMax - 1.0f;//�ő�ő厞�Ԃɂ���
		}

		if (g_motionTime - i > 1.0f) //�덷���C���@�z���1.0�𒴂�����
		{
			i++;//���̃L�[�t���[���ɓ���
		}

		//if (GetKeyboardPress(DIK_SPACE))
		//{
		//	g_motionTime = 0.0f;	//���Z�b�g
		//	i = (int)g_motionTime;	//�d�v
		//}

		if (1)
		{
			//�ڑ��̕�Ԃ́@[i] * 1.0�ł��A[i + 1] * 0.0�ł͂Ȃ�
			for (int j = 0; j < PART_MAX; j++)//�p�[�c�ԍ�
			{
				// Scale
				//g_player.part[j].srt.scl.x = g_anime[i].key[j].scl.x +				// �O�̃L�[�t���[���ʒu
				//	(g_anime[i + 1].key[j].scl.x - g_anime[i].key[j].scl.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				//g_player.part[j].srt.scl.y = g_anime[i].key[j].scl.y +				// �O�̃L�[�t���[���ʒu
				//	(g_anime[i + 1].key[j].scl.y - g_anime[i].key[j].scl.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				//g_player.part[j].srt.scl.z = g_anime[i].key[j].scl.z +				// �O�̃L�[�t���[���ʒu
				//	(g_anime[i + 1].key[j].scl.z - g_anime[i].key[j].scl.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				// Rotation
				g_player.part[j].srt.rot.x = g_anime[i].key[j].rot.x +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].rot.x - g_anime[i].key[j].rot.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.rot.y = g_anime[i].key[j].rot.y +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].rot.y - g_anime[i].key[j].rot.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.rot.z = g_anime[i].key[j].rot.z +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].rot.z - g_anime[i].key[j].rot.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				// Position
				//g_player.part[j].srt.pos.x = g_anime[i].key[j].pos.x +				// �O�̃L�[�t���[���ʒu
				//	(g_anime[i + 1].key[j].pos.x - g_anime[i].key[j].pos.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				//g_player.part[j].srt.pos.y = g_anime[i].key[j].pos.y +				// �O�̃L�[�t���[���ʒu
				//	(g_anime[i + 1].key[j].pos.y - g_anime[i].key[j].pos.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				//g_player.part[j].srt.pos.z = g_anime[i].key[j].pos.z +				// �O�̃L�[�t���[���ʒu
				//	(g_anime[i + 1].key[j].pos.z - g_anime[i].key[j].pos.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������
			}
		}

		break;
	}

	case MODE_INGAME:
	{
		//�A�j���[�V���� 
		int i = (int)g_motionTime;  //���݂̃L�[�t���[���i���o�[

		//loop�ł���悤��
		if (i > g_keyMax - 2)//�ő�L�[�t���[���i���o�[�𒴂�����
		{
			i = 1;
			g_motionTime = 1.0f;
		}

		float dt = 1.0f / g_anime[i].frame;//��Ԃ̊Ԋu����

		g_motionTime += dt;

		if (g_motionTime > g_keyMax - 1.0f)//�ő厞�Ԃ𒴂�����
		{
			g_motionTime = g_keyMax - 1.0f;//�ő厞�Ԃɂ���
		}

		if (g_motionTime - i > 1.0f) //�덷���C���@�z���1.0�𒴂�����
		{
			i++;//���̃L�[�t���[���ɓ���
		}

		if (g_animeState == 0)
		{
			g_motionTime = 0.0f;	//���Z�b�g
			i = (int)g_motionTime;	//�d�v

			if (g_player.state != FROZEN)
			{
				g_cancelTime += dt;//0�ԃL�[�t���[����time���g��
			}

			if (g_cancelTime > 1.0f)//�ő厞�Ԃ𒴂�����
			{
				g_cancelTime = 1.0f;//�ő�ő厞�Ԃɂ���
			}

			//�ڑ��̕�Ԃ́@[i] * 1.0�ł��A[i + 1] * 0.0�ł͂Ȃ�
			for (int j = 0; j < PART_MAX; j++)//�p�[�c�ԍ�
			{//�ŏ��̃L�[�̏�Ԃɖ߂�
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
			g_cancelTime = 0.0f;	//���Z�b�g

			//�ڑ��̕�Ԃ́@[i] * 1.0�ł��A[i + 1] * 0.0�ł͂Ȃ�
			for (int j = 0; j < PART_MAX; j++)//�p�[�c�ԍ�
			{
				// Scale
				//g_player.part[j].srt.scl.x = g_anime[i].key[j].scl.x +				// �O�̃L�[�t���[���ʒu
				//	(g_anime[i + 1].key[j].scl.x - g_anime[i].key[j].scl.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				//g_player.part[j].srt.scl.y = g_anime[i].key[j].scl.y +				// �O�̃L�[�t���[���ʒu
				//	(g_anime[i + 1].key[j].scl.y - g_anime[i].key[j].scl.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				//g_player.part[j].srt.scl.z = g_anime[i].key[j].scl.z +				// �O�̃L�[�t���[���ʒu
				//	(g_anime[i + 1].key[j].scl.z - g_anime[i].key[j].scl.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				// Rotation
				g_player.part[j].srt.rot.x = g_anime[i].key[j].rot.x +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].rot.x - g_anime[i].key[j].rot.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				//g_player.part[j].srt.rot.y = g_anime[i].key[j].rot.y +				// �O�̃L�[�t���[���ʒu
				//	(g_anime[i + 1].key[j].rot.y - g_anime[i].key[j].rot.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.rot.z = g_anime[i].key[j].rot.z +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].rot.z - g_anime[i].key[j].rot.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				// Position
				//g_player.part[j].srt.pos.x = g_anime[i].key[j].pos.x +				// �O�̃L�[�t���[���ʒu
				//	(g_anime[i + 1].key[j].pos.x - g_anime[i].key[j].pos.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				//g_player.part[j].srt.pos.y = g_anime[i].key[j].pos.y +				// �O�̃L�[�t���[���ʒu
				//	(g_anime[i + 1].key[j].pos.y - g_anime[i].key[j].pos.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				//g_player.part[j].srt.pos.z = g_anime[i].key[j].pos.z +				// �O�̃L�[�t���[���ʒu
				//	(g_anime[i + 1].key[j].pos.z - g_anime[i].key[j].pos.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������
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
			g_animeStateKen = 1;//������Ԃɂ���	
			
			D3DXMatrixIdentity(&mtxBuff);
			D3DXMatrixMultiply(&mtxBuff, &mtxBuff, &g_player.part[SWORD_R].parent->mtxS);
			D3DXMatrixMultiply(&mtxBuff, &mtxBuff, &g_player.part[SWORD_R].parent->mtxT);			
			D3DXMatrixMultiply(&mtxBuff, &mtxBuff, &g_player.part[SWORD_R].parent->parent->mtxWorld);//���𓊂��鎞�́A�e�̍s�����ۑ�
		}

	}

	if (g_animeStateKen)
	{
		g_keyMax = sizeof(g_animeKen) / sizeof(KEY);//sizeof(g_anime)�ł̓_��

		//�A�j���[�V���� 
		int i = (int)g_motionTime2;  //i:���݂̃L�[�t���[���i���o�[

		float dt = 1.0f / g_anime[i].frame;//��Ԃ̊Ԋu����

		//����������A���̏�Ԃɖ߂�
		if (i > g_keyMax - 2)//�ő�L�[�t���[���i���o�[�𒴂�����
		{
			i = 0;
			g_motionTime2 = 0.0f;

			g_animeStateKen = 0;
			dt = 0;
		}

		g_motionTime2 += dt;

		if (g_motionTime2 > g_keyMax - 1.0f)//�ő厞�Ԃ𒴂�����
		{
			g_motionTime2 = g_keyMax - 1.0f;//�ő�ő厞�Ԃɂ���

		}

		if (g_motionTime2 - i > 1.0f) //�덷���C���@�z���1.0�𒴂�����
		{
			i++;//���̃L�[�t���[���ɓ���
		}




		//�ڑ��̕�Ԃ́@[i] * 1.0�ł��A[i + 1] * 0.0�ł͂Ȃ�

		int j = SWORD_R;

		// Rotation
		g_player.part[j].srt.rot.x = g_anime[i].key[j].rot.x +				// �O�̃L�[�t���[���ʒu
			(g_anime[i + 1].key[j].rot.x - g_anime[i].key[j].rot.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
			* (g_motionTime2 - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

		g_player.part[j].srt.rot.y = g_anime[i].key[j].rot.y +				// �O�̃L�[�t���[���ʒu
			(g_anime[i + 1].key[j].rot.y - g_anime[i].key[j].rot.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
			* (g_motionTime2 - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

		g_player.part[j].srt.rot.z = g_anime[i].key[j].rot.z +				// �O�̃L�[�t���[���ʒu
			(g_anime[i + 1].key[j].rot.z - g_anime[i].key[j].rot.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
			* (g_motionTime2 - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������


		// Position
		g_player.part[j].srt.pos.x = g_anime[i].key[j].pos.x +				// �O�̃L�[�t���[���ʒu
			(g_anime[i + 1].key[j].pos.x - g_anime[i].key[j].pos.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
			* (g_motionTime2 - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

		g_player.part[j].srt.pos.y = g_anime[i].key[j].pos.y +				// �O�̃L�[�t���[���ʒu
			(g_anime[i + 1].key[j].pos.y - g_anime[i].key[j].pos.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
			* (g_motionTime2 - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

		g_player.part[j].srt.pos.z = g_anime[i].key[j].pos.z +				// �O�̃L�[�t���[���ʒu
			(g_anime[i + 1].key[j].pos.z - g_anime[i].key[j].pos.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
			* (g_motionTime2 - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������


	}

}


void AnimeKen3(KEY g_anime[])
{
	if (g_animeStateKen3 == 0)
	{
		if (GetKeyboardPress(DIK_K))
		{
			g_animeStateKen3 = 1;//������Ԃɂ���	
			g_motionTime3 = 0.0f;
	
			vctBuff3 = D3DXVECTOR3( g_player.part[0].srt.pos.x,
									0.0f,
									g_player.part[0].srt.pos.z);

			rotY = g_player.part[0].srt.rot.y;


		}

	}

	if (g_animeStateKen3)
	{
		g_keyMax = sizeof(g_animeKen3) / sizeof(KEY);//sizeof(g_anime)�ł̓_��

		//�A�j���[�V���� 
		int i = (int)g_motionTime3;  //i:���݂̃L�[�t���[���i���o�[

		float dt = 1.0f / g_anime[i].frame;//��Ԃ̊Ԋu����

		//����������A���̏�Ԃɖ߂�
		if (i > g_keyMax - 2)//�ő�L�[�t���[���i���o�[�𒴂�����
		{
			i = g_keyMax - 2;//�ő�L�[�t���[���i���o�[�ɂ���

			g_animeStateKen3 = 0;
			g_motionTime = 0.0f;		//���n���A���鎞�ԃ��Z�b�g	�W�����v�Ƒ��郂�[�V�������X���[�Y�ɂȂ���|�C���g�I
		}

		g_motionTime3 += dt;

		if (g_motionTime3 > g_keyMax - 1.0f)//�ő厞�Ԃ𒴂�����
		{
			g_motionTime3 = g_keyMax - 1.0f;//�ő�ő厞�Ԃɂ���

		}

		if (g_motionTime3 - i > 1.0f) //�덷���C���@�z���1.0�𒴂�����
		{
			i++;//���̃L�[�t���[���ɓ���
		}

		//�ڑ��̕�Ԃ́@[i] * 1.0�ł��A[i + 1] * 0.0�ł͂Ȃ�
		for (int j = 0; j < PART_MAX; j++)//�p�[�c�ԍ�
		{
			// Rotation
			g_player.part[j].srt.rot.x = g_anime[i].key[j].rot.x +				// �O�̃L�[�t���[���ʒu
				(g_anime[i + 1].key[j].rot.x - g_anime[i].key[j].rot.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				* (g_motionTime3 - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			//g_player.part[j].srt.rot.y = g_anime[i].key[j].rot.y +				// �O�̃L�[�t���[���ʒu
			//	(g_anime[i + 1].key[j].rot.y - g_anime[i].key[j].rot.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
			//	* (g_motionTime3 - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			g_player.part[j].srt.rot.z = g_anime[i].key[j].rot.z +				// �O�̃L�[�t���[���ʒu
				(g_anime[i + 1].key[j].rot.z - g_anime[i].key[j].rot.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				* (g_motionTime3 - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			 //Position
			g_player.part[j].srt.pos.x = g_anime[i].key[j].pos.x +				// �O�̃L�[�t���[���ʒu
				(g_anime[i + 1].key[j].pos.x - g_anime[i].key[j].pos.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				* (g_motionTime3 - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			g_player.part[j].srt.pos.y = g_anime[i].key[j].pos.y +				// �O�̃L�[�t���[���ʒu
				(g_anime[i + 1].key[j].pos.y - g_anime[i].key[j].pos.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				* (g_motionTime3 - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			g_player.part[j].srt.pos.z = g_anime[i].key[j].pos.z +				// �O�̃L�[�t���[���ʒu
				(g_anime[i + 1].key[j].pos.z - g_anime[i].key[j].pos.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				* (g_motionTime3 - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������
		}

		//�ڂ̑O�̕����Ƀ��[�V��������悤��
		D3DXMatrixIdentity(&rotYMtx);
		D3DXMatrixRotationY(&rotYMtx,rotY);
		D3DXVec3TransformCoord(&g_player.part[BODY].srt.pos,
									&g_player.part[BODY].srt.pos,
									&rotYMtx);

		g_player.part[BODY].srt.pos.x = g_player.part[BODY].srt.pos.x + vctBuff3.x;		//���_�ł͂Ȃ��A�����Ă���ꏊ�Ŕ���
		g_player.part[BODY].srt.pos.z = g_player.part[BODY].srt.pos.z + vctBuff3.z;

		g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	}

	PrintDebugProc("���̃t���[���p�^�[���F%d \n\n", (int)g_motionTime3);

}

void AnimeTemp(KEY g_anime[])
{
	if (GetKeyboardRepeat(DIK_L))
	{
		if (keyFrameNum > 1)
		{
			g_keyMax = keyFrameNum;

			//�A�j���[�V���� 
			int i = (int)g_motionTimeTemp;  //���݂̃L�[�t���[���i���o�[

			float dt = 1.0f / g_anime[i].frame;//��Ԃ̊Ԋu����

			//loop�ł���悤��
			if (i > g_keyMax - 2)//�ő�L�[�t���[���i���o�[�𒴂�����
			{
				i = 0;
				g_motionTimeTemp = 0.0f;

				dt = 0.0f;
			}

			g_motionTimeTemp += dt;

			if (g_motionTimeTemp > g_keyMax - 1.0f)//�ő厞�Ԃ𒴂�����
			{
				g_motionTimeTemp = g_keyMax - 1.0f;//�ő�ő厞�Ԃɂ���
			}

			if (g_motionTimeTemp - i > 1.0f) //�덷���C���@�z���1.0�𒴂�����
			{
				i++;//���̃L�[�t���[���ɓ���
			}

			//if (GetKeyboardPress(DIK_SPACE))
			//{
			//	g_motionTimeTemp = 0.0f;	//���Z�b�g
			//	i = (int)g_motionTimeTemp;	//�d�v
			//}

				//�ڑ��̕�Ԃ́@[i] * 1.0�ł��A[i + 1] * 0.0�ł͂Ȃ�
			for (int j = 0; j < PART_MAX; j++)//�p�[�c�ԍ�
			{
				// Scale
				g_player.part[j].srt.scl.x = g_anime[i].key[j].scl.x +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].scl.x - g_anime[i].key[j].scl.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTimeTemp - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.scl.y = g_anime[i].key[j].scl.y +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].scl.y - g_anime[i].key[j].scl.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTimeTemp - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.scl.z = g_anime[i].key[j].scl.z +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].scl.z - g_anime[i].key[j].scl.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTimeTemp - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				// Rotation
				g_player.part[j].srt.rot.x = g_anime[i].key[j].rot.x +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].rot.x - g_anime[i].key[j].rot.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTimeTemp - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.rot.y = g_anime[i].key[j].rot.y +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].rot.y - g_anime[i].key[j].rot.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTimeTemp - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.rot.z = g_anime[i].key[j].rot.z +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].rot.z - g_anime[i].key[j].rot.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTimeTemp - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				// Position
				g_player.part[j].srt.pos.x = g_anime[i].key[j].pos.x +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].pos.x - g_anime[i].key[j].pos.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTimeTemp - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.pos.y = g_anime[i].key[j].pos.y +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].pos.y - g_anime[i].key[j].pos.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTimeTemp - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.pos.z = g_anime[i].key[j].pos.z +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].pos.z - g_anime[i].key[j].pos.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTimeTemp - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������
			}

			PrintDebugProc(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>{�S�̃��r���[��}�o�ߎ���:%f  ���݂̃L�[�t���[���ԍ�:%d  �t���[����:%d \n\n", g_motionTimeTemp,i, pAnimeTemp[i].frame);
		}
	}

	else if(GetKeyboardRepeat(DIK_I))
	{
		if (reviewFrameNo2 > reviewFrameNo1)
		{
			g_keyMax = reviewFrameNo2 - reviewFrameNo1 +1;

			//�A�j���[�V���� 
			int i = (int)g_motionTimeSR;  //���݂̃L�[�t���[���i���o�[

			float dt = 1.0f / g_anime[i].frame;//��Ԃ̊Ԋu����

			//reviewFrameNo1�ԍ���ԂɃ��Z�b�g
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

			

			//loop�ł���悤��
			if (i > reviewFrameNo2 - 1)//�ő�L�[�t���[���i���o�[�𒴂�����
			{
				g_motionTimeSR = (float)reviewFrameNo1;
				i = reviewFrameNo1;

				dt = 0.0f;
			}

			
			g_motionTimeSR += dt;

			if (g_motionTimeSR > (float)reviewFrameNo2)//�ő厞�Ԃ𒴂�����
			{
				g_motionTimeSR = (float)reviewFrameNo2;//�ő�ő厞�Ԃɂ���
			}

			if (g_motionTimeSR - i > 1.0f) //�덷���C���@�z���1.0�𒴂�����
			{
				i++;//���̃L�[�t���[���ɓ���
			}

			//�ڑ��̕�Ԃ́@[i] * 1.0�ł��A[i + 1] * 0.0�ł͂Ȃ�
			for (int j = 0; j < PART_MAX; j++)//�p�[�c�ԍ�
			{
				// Scale
				g_player.part[j].srt.scl.x = g_anime[i].key[j].scl.x +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].scl.x - g_anime[i].key[j].scl.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTimeSR - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.scl.y = g_anime[i].key[j].scl.y +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].scl.y - g_anime[i].key[j].scl.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTimeSR - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.scl.z = g_anime[i].key[j].scl.z +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].scl.z - g_anime[i].key[j].scl.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTimeSR - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				// Rotation
				g_player.part[j].srt.rot.x = g_anime[i].key[j].rot.x +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].rot.x - g_anime[i].key[j].rot.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTimeSR - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.rot.y = g_anime[i].key[j].rot.y +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].rot.y - g_anime[i].key[j].rot.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTimeSR - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.rot.z = g_anime[i].key[j].rot.z +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].rot.z - g_anime[i].key[j].rot.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTimeSR - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				// Position
				g_player.part[j].srt.pos.x = g_anime[i].key[j].pos.x +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].pos.x - g_anime[i].key[j].pos.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTimeSR - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.pos.y = g_anime[i].key[j].pos.y +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].pos.y - g_anime[i].key[j].pos.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTimeSR - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.pos.z = g_anime[i].key[j].pos.z +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].pos.z - g_anime[i].key[j].pos.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTimeSR - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������
			}

			PrintDebugProc(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>{�w���ԃ��r���[��}�o�ߎ���:%f  ���݂̃L�[�t���[���ԍ�:%d  �t���[����:%d \n\n", g_motionTimeSR, i, pAnimeTemp[i].frame);
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
	//���[�h�̓���
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

	//�R���g���[��ID�̓���
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

		//���f���p�[�c�̃R���g���[���[
		switch (SRTMode)
		{
		case 0://�k���g��					
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

		case 1://��]
			switch (XYZMode)
			{
			case 0:
				//x����]
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
				//y����]
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
				//z����]
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

		case 2://�ړ�
			switch (XYZMode)
			{
			case 0:
				//x���ړ�
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
				//y���ړ�
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
				//z���ړ�
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

		//���̉^����Ԃ�ۑ�
		if (GetKeyboardTrigger(DIK_NUMPADENTER))
		{
			CreateAnimeTemp(diyFrame);
		}

		//�f�t�H���g��ԂɂȂ�
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

	PrintDebugProc("���[�h�F[");
	switch (g_mode)
	{
	case 0:
		PrintDebugProc("�v���C");
		break;
	case 1:
		PrintDebugProc("�G�f�B�^�[");
		break;
	case 2:
		PrintDebugProc("�C���Q�[��");
		break;

	}
	PrintDebugProc("]\n\n");

	if (g_mode == MODE_EDIT)
	{
		PrintDebugProc("�p�[�c������@[F9]�F\n");
		if (manual)
		{
			PrintDebugProc("�e���L�[��[0]�`[6]:�p�[�c�؊�\n");
			PrintDebugProc("[Q][A][Z]:SRT�؊� \n");
			PrintDebugProc("[S][D][F]:XYZ�؊� \n");
			PrintDebugProc("[<-][->](Repeat):SRT�l���������� \n");
			PrintDebugProc("[SPACE]:�f�t�H���g��Ԃɕ���\n");
			PrintDebugProc("[F2]:�O���t�@�C���ւ̏o��(����Ǝ������s)\n");
			PrintDebugProc("[F4]:�O���f�[�^�����[�h\n");
		}
		PrintDebugProc("\n");

		PrintDebugProc(">>>>>>>>>>>>���݂̑���F[");
		switch (g_conId)
		{
		case 0:
			PrintDebugProc("��");
			break;
		case 1:
			PrintDebugProc("��");
			break;
		case 2:
			PrintDebugProc("����");
			break;
		case 3:
			PrintDebugProc("�E��");
			break;
		case 4:
			PrintDebugProc("����");
			break;
		case 5:
			PrintDebugProc("�E��");
			break;
		case 6:
			PrintDebugProc("��");
			break;
		}
		PrintDebugProc("]");


		PrintDebugProc("[");
		switch (SRTMode)
		{
		case 0:
			PrintDebugProc("�g��");
			break;
		case 1:
			PrintDebugProc("��]");
			break;
		case 2:
			PrintDebugProc("�ړ�");
			break;

		}
		PrintDebugProc("]");

		if (SRTMode != 0)
		{
			PrintDebugProc("[");
			switch (XYZMode)
			{
			case 0:
				PrintDebugProc("X��");
				break;
			case 1:
				PrintDebugProc("Y��");
				break;
			case 2:
				PrintDebugProc("Z��");
				break;

			}
			PrintDebugProc("]");
		}
		else
		{
			PrintDebugProc("[3��]");
		}


		PrintDebugProc("\n\n");

	}

	PrintDebugProc("[");
	switch (g_conId)
	{
	case 0:
		PrintDebugProc("��");
		break;
	case 1:
		PrintDebugProc("��");
		break;
	case 2:
		PrintDebugProc("����");
		break;
	case 3:
		PrintDebugProc("�E��");
		break;
	case 4:
		PrintDebugProc("����");
		break;
	case 5:
		PrintDebugProc("�E��");
		break;
	case 6:
		PrintDebugProc("��");
		break;
	}

	PrintDebugProc("]��SRT�l:\n");


	if (SRTMode == 0)
	{
		PrintDebugProc("������������");

		PrintDebugProc("[S�F(��%f : %f : %f��)]", g_player.part[g_conId].srt.scl.x,
			g_player.part[g_conId].srt.scl.y,
			g_player.part[g_conId].srt.scl.z);


	}
	else
	{
		PrintDebugProc("[S�F(%f : %f : %f)]", g_player.part[g_conId].srt.scl.x,
			g_player.part[g_conId].srt.scl.y,
			g_player.part[g_conId].srt.scl.z);

	}

	if (SRTMode == 0)
	{
		PrintDebugProc("��");
	}
	PrintDebugProc("\n");



	if (SRTMode == 1)
	{
		PrintDebugProc("������������");

		switch (XYZMode)
		{
		case 0:
			PrintDebugProc("[R�F(��%f�� : %f : %f)]", g_player.part[g_conId].srt.rot.x,
				g_player.part[g_conId].srt.rot.y,
				g_player.part[g_conId].srt.rot.z);


			break;
		case 1:
			PrintDebugProc("[R�F(%f : ��%f�� : %f)]", g_player.part[g_conId].srt.rot.x,
				g_player.part[g_conId].srt.rot.y,
				g_player.part[g_conId].srt.rot.z);


			break;
		case 2:
			PrintDebugProc("[R�F(%f : %f : ��%f��)]", g_player.part[g_conId].srt.rot.x,
				g_player.part[g_conId].srt.rot.y,
				g_player.part[g_conId].srt.rot.z);


			break;

		}
	}
	else
	{
		PrintDebugProc("[R�F(%f : %f : %f)]", g_player.part[g_conId].srt.rot.x,
			g_player.part[g_conId].srt.rot.y,
			g_player.part[g_conId].srt.rot.z);
	}

	if (SRTMode == 1)
	{
		PrintDebugProc("����");
	}
	PrintDebugProc("\n");




	if (SRTMode == 2)
	{
		PrintDebugProc("������������");

		switch (XYZMode)
		{
		case 0:
			PrintDebugProc("[T�F(��%f�� : %f : %f)]", g_player.part[g_conId].srt.pos.x,
				g_player.part[g_conId].srt.pos.y,
				g_player.part[g_conId].srt.pos.z);


			break;
		case 1:
			PrintDebugProc("[T�F(%f : ��%f�� : %f)]", g_player.part[g_conId].srt.pos.x,
				g_player.part[g_conId].srt.pos.y,
				g_player.part[g_conId].srt.pos.z);


			break;
		case 2:
			PrintDebugProc("[T�F(%f : %f : ��%f��)]", g_player.part[g_conId].srt.pos.x,
				g_player.part[g_conId].srt.pos.y,
				g_player.part[g_conId].srt.pos.z);


			break;

		}

	}
	else
	{
		PrintDebugProc("[T�F(%f : %f : %f)]", g_player.part[g_conId].srt.pos.x,
			g_player.part[g_conId].srt.pos.y,
			g_player.part[g_conId].srt.pos.z);

	}

	if (SRTMode == 2)
	{
		PrintDebugProc("������");
	}
	PrintDebugProc("\n\n");
	
	if (g_mode == MODE_EDIT)
	{
		PrintDebugProc("���ݕۑ����ꂽ�L�[�t���[���̑���:%d \n", keyFrameNum);

		if ((functionMode == 1) || (functionMode == 2))
		{
			PrintDebugProc("������������");
		}
		
		if (functionMode == 1)
		{
			PrintDebugProc("���ɕۑ�����L�[�t���[���ԍ�:��%d��  �ۑ��t���[����:%d ", keyFrameSaveNo, diyFrame);
		}
		else if (functionMode == 2)
		{
			PrintDebugProc("���ɕۑ�����L�[�t���[���ԍ�:%d  �ۑ��t���[����:��%d�� ", keyFrameSaveNo, diyFrame);
		}
		else
		{
			PrintDebugProc("���ɕۑ�����L�[�t���[���ԍ�:%d  �ۑ��t���[����:%d ", keyFrameSaveNo, diyFrame);
		}

		if (functionMode == 1)
		{
			PrintDebugProc("��\n");
		}
		else if(functionMode == 2)
		{
			PrintDebugProc("����\n");
		}
		else
		{
			PrintDebugProc("\n");
		}

		PrintDebugProc("�ύX:[1] [2][-][+]  [NUMPADENTER]:���̉^����Ԃ�ۑ�\n\n");


		if (functionMode == 3)
		{
			PrintDebugProc("������������");
		}

		if (functionMode == 3)
		{
			PrintDebugProc("�ʃ��r���[�̃L�[�t���[���ԍ�:��%d��(�t���[����:%d) ", reviewNo, pAnimeTemp[reviewNo].frame);
		}
		else
		{
			PrintDebugProc("�ʃ��r���[�̃L�[�t���[���ԍ�:%d(�t���[����:%d) ", reviewNo, pAnimeTemp[reviewNo].frame);
		}
		

		if (functionMode == 3)
		{
			PrintDebugProc("������\n");
		}
		else
		{
			PrintDebugProc("\n");
		}


		PrintDebugProc("�ύX:[3][-][+]  [P]:�ʃ��r���[  [L]:�S�̃��r���[\n\n");


		if ((functionMode == 4) || (functionMode == 5))
		{
			PrintDebugProc("������������");
		}


		if (functionMode == 4)
		{
			PrintDebugProc("�w���ԃ��r���[�̃L�[�t���[���ԍ�:��%d���`%d ", reviewFrameNo1, reviewFrameNo2);
		}
		else if (functionMode == 5)
		{
			PrintDebugProc("�w���ԃ��r���[�̃L�[�t���[���ԍ�:%d�`��%d�� ", reviewFrameNo1, reviewFrameNo2);
		}
		else
		{
			PrintDebugProc("�w���ԃ��r���[�̃L�[�t���[���ԍ�:%d�`%d ", reviewFrameNo1, reviewFrameNo2);
		}

		if (functionMode == 4)
		{
			PrintDebugProc("��������\n");
		}
		else if (functionMode == 5)
		{
			PrintDebugProc("����������\n");
		}
		else
		{
			PrintDebugProc("\n");
		}

		PrintDebugProc("�ύX:[4]�`[5][-][+]  [I]:��ԃ��r���[\n\n");


	}

	if (g_mode == MODE_INGAME)
	{
		PrintDebugProc("�ړI�����F%f \n", g_player.rotDest.y);
		PrintDebugProc("�v���C���[�̉^���ʁF%f,%f,%f \n", g_player.move.x, g_player.move.y, g_player.move.z);
	}

#endif


}


void LoadAnime(KEY *g_anime)
{
	if (pAnimeTemp != g_animeMemoy) 
	{
		free(pAnimeTemp);	//�q�[�v�̈�̉��
	}
	

	pAnimeTemp = g_anime;

	keyFrameNum = sizeof(g_animeMemoy) / sizeof(KEY);

	keyFrameSaveNo = keyFrameNum;

	reviewNo = reviewFrameNo1 = reviewFrameNo2 = 0;

	diyFrame = 60;
}






