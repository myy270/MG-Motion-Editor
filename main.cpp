//=============================================================================
//
// ���C������ [main.cpp]
// Author : ���p�j
//
//=============================================================================
#include "main.h"
#include "input.h"
//#include "title.h"
#include "game.h"
//#include "result.h"
#include "fade.h"
//#include "sound.h"
#include "player.h"
#include "debugproc.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"			// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"MG_Battle"		// �E�C���h�E�̃L���v�V������


//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D �I�u�W�F�N�g
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)
#ifdef _DEBUG
int					g_nCountFPS;			// FPS�J�E���^
#endif
MODE				g_mode = MODE_GAME;	// ���[�h

int rest;			//�|�[�Y�̃X�C�b�`

HWND hWnd;
//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	
	MSG msg;
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						100,
						0,
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
						NULL,
						NULL,
						hInstance,
						NULL);

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	//�t���[���J�E���g������
	timeBeginPeriod(1);				// ����\��ݒ�
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// ���b�Z�[�W���[�v
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`(���o)
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif

				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / F_P_S))
			{
#ifdef _DEBUG
				PrintDebugProc("FPS:%d\n", g_nCountFPS);
#endif

				dwExecLastTime = dwCurrentTime;

				// ���͍X�V
				UpdateInput();


				//�|�[�Y����
				if (g_mode == MODE_GAME)
				{
					if (GetKeyboardTrigger(DIK_F3) || ((IsButtonPress(0, BUTTON_SHARE)) && (IsButtonTrigger(0, BUTTON_OPTIONS))) || ((IsButtonTrigger(0, BUTTON_SHARE)) && (IsButtonPress(0, BUTTON_OPTIONS))))
					{
						rest = !rest;
					}
				}

				if (rest == 0)
				{
					// �X�V����
					Update();

					// �`�揈��
					Draw();
				}
				

				dwFrameCount++;
			}
		}
	}
	
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

	timeEndPeriod(1);				// ����\��߂�

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:					// [ESC]�L�[�������ꂽ
			DestroyWindow(hWnd);		// �E�B���h�E��j������悤�w������
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
    if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory( &d3dpp, sizeof(d3dpp) );						// ���[�N���[���N���A
	d3dpp.BackBufferCount			= 1;
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat			= d3ddm.Format;				// �J���[���[�h�̎w��
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed					= bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil	= TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	if(bWindow)
	{// �E�B���h�E���[�h
		d3dpp.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
									D3DDEVTYPE_HAL, 
									hWnd, 
									D3DCREATE_HARDWARE_VERTEXPROCESSING, 
									&d3dpp, &g_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp, &g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp, &g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
    g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);//�g���A�|���S�����Â��Ȃ���������ł���

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);		// �A���t�@�u�����f�B���O����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		// �ŏ��̃A���t�@����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);		// �Q�Ԗڂ̃A���t�@����

	// ���͏����̏�����
	InitInput(hInstance, hWnd);

	// �f�o�b�O�\�������̏�����
	InitDebugProc();

	// �t�F�[�h�̏�����
	InitFade();

	//// �T�E���h�̏�����
	//InitSound(hWnd);

	// �ŏ��̓^�C�g����ʂ�
	SetMode(g_mode);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	if(g_pD3DDevice != NULL)
	{// �f�o�C�X�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if(g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	//UninitTitle();
	UninitGame();
	//UninitResult();

	// �t�F�[�h�̏I������
	UninitFade();

	// �T�E���h�̏I������
	//UninitSound();

	// ���͏����̏I������
	UninitInput();

	// �f�o�b�O�\�������̏I������
	UninitDebugProc();

}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	//�����I�Ƀ^�C�g����ʂɖ߂�
	if (GetKeyboardTrigger(DIK_F4) || (IsButtonPress(0, BUTTON_L3) && IsButtonTrigger(0, BUTTON_R3)) || (IsButtonTrigger(0, BUTTON_L3) && IsButtonPress(0, BUTTON_R3)))
	{		
		SetMode(MODE_TITLE);
	}

	UpdateDebugProc();

	switch(g_mode)
	{
	case MODE_TITLE:		// �^�C�g����ʂ̍X�V
		//UpdateTitle();
		break;

	case MODE_GAME:			// �Q�[����ʂ̍X�V
		UpdateGame();
		break;

	case MODE_RESULT:		// ���U���g��ʂ̍X�V

		//UpdateGame();		//�Q�[����ʂ�ێ�����

		//UpdateResult();	
		break;
	}

	// �t�F�[�h�����̍X�V
	UpdateFade();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(200, 200, 200, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch(g_mode)
		{
		case MODE_TITLE:		// �^�C�g����ʂ̕`��
			//DrawTitle();
			break;

		case MODE_GAME:			// �Q�[����ʂ̕`��
			DrawGame();
			break;

		case MODE_RESULT:		// ���U���g��ʂ̕`��

			//DrawGame();			//�Q�[����ʂ�ێ�����

			//DrawResult();
			break;
		}

		// �t�F�[�h�`��
		DrawFade();

		// �f�o�b�O�\�������̕`��
		DrawDebugProc();
		
		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=============================================================================
// ���[�h�̐ݒ�@�ď���������K�v����!!!
//=============================================================================
void SetMode(MODE mode)
{
	g_mode = mode;

	switch(g_mode)
	{
	case MODE_TITLE:
		// ���U���g��ʂ̏I������
		//UninitResult();

		// �^�C�g����ʂ̏�����
		//InitTitle();

		// �Q�[����ʂ̏I������
		//UninitGame();

		break;

	case MODE_GAME:
		// �^�C�g����ʂ̏I������
		//UninitTitle();

		// �Q�[����ʂ̏�����
		InitGame();

		break;

	case MODE_RESULT:
		// �Q�[����ʂ̏I������
		//UninitGame();

		// ���U���g��ʂ̏�����
		//InitResult();

		break;
	}
}

//=============================================================================
// ���[�h�̎擾
//=============================================================================
MODE GetMode(void)
{
	return g_mode;
}