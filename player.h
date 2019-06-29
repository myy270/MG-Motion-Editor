//=============================================================================
//
// �v���C���[���� [player.h]
// Author : ���p�j
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "item.h"

#define PART_MAX	(7)		// �p�[�c�̐��@�́A���A����A�E��A�����A�E���A�E��̌�

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
struct SRT
{
	D3DXVECTOR3 scl;		// �g��k��	
	D3DXVECTOR3 rot;		// ���݂̌���
	D3DXVECTOR3 pos;		// ���݂̈ʒu
};

//�L�[�t���[���̒�`
struct KEY
{
	int			frame;			//���̃L�[�t���[���̑��t���[����
	SRT			key[PART_MAX];	//�L�[�t���[���̃f�[�^
};

struct PART
{
	char *partFile;
	//x�t�@�C�����
	LPD3DXBUFFER		pMatBuff;			// ���b�V���̃}�e���A�������i�[
	DWORD				nNumMat;			// �}�e���A�����̑���
	LPD3DXMESH			pMesh;				// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^

	SRT			srt;		//Scaling Rotation Translation
	D3DXMATRIX	mtxS;
	D3DXMATRIX	mtxR;
	D3DXMATRIX	mtxT;
	D3DXMATRIX	mtxWorld;
	PART		*parent;
	bool		use;
};

enum STATE
{
	NORMAL,
	FROZEN,
	STATE_MAX
};


struct PLAYER
{
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 rotDest;	// �ړI�̌���
	float fRadius;			// ���a
	int nIdxShadow;			// �eID
	PART part[PART_MAX];

	ITEMTYPE holdItem;	//�������Ă���A�C�e��

	STATE state;	//�ُ��Ԃ��ǂ���
	int stateTime;	//�ُ��Ԃ̎c�莞��
};

enum PART_ID
{
	BODY,
	HEAD,
	HAND_L,
	HAND_R,
	LEG_L,
	LEG_R,
	SWORD_R,
	PART_ID_MAX
};

enum APPLIMODE
{
	MODE_PLAY,//��������[�V�������Đ����郂�[�h
	MODE_EDIT,//���[�V��������郂�[�h
	MODE_INGAME,//���ۃv���C����Ƃ��̃��[�h
	APPLIMODE_MAX
};



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);

D3DXVECTOR3 GetPositionPlayer(void);
D3DXVECTOR3 GetRotationPlayer(void);
D3DXVECTOR3 GetRotationDestPlayer(void);
D3DXVECTOR3 GetMovePlayer(void);



#endif