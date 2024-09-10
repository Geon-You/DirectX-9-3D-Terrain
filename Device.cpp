#include "Device.h"

Device::Device()
	: direct(nullptr), 
	device(nullptr), 
	sprite(nullptr),
	font(nullptr)
{
}

Device::~Device()
{
	Release();
}

HRESULT Device::InitDevice(WinMode mode)
{
	// 1. ���̷�Ʈ ��ü ����
	// 2. ���̷�Ʈ ��ü�� ���� ��ġ ���� ����
	// 3. ������ ��ġ ������ ���� ���� ó���� ���� ���� ����
	// 4. �������� ���� �������� ����̽� ��ġ ����

	// ���̷�Ʈ ��ü ����
	direct = Direct3DCreate9(D3D_SDK_VERSION);

	// ��ġ ���ɿ� ���� ������ ���� ����ü
	D3DCAPS9 deviceCaps;
	ZeroMemory(&deviceCaps, sizeof(deviceCaps));

	// ��ġ ���� ����
	if (FAILED(direct->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &deviceCaps)))
	{
		ERR_MSG(g_hWnd, L"��ġ ���� ������ ����");
		return E_FAIL;
	}

	DWORD behaivorFlag = 0;
	// �ϵ���� ���ؽ� ���μ��� ���� ���� Ȯ��
	if (deviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		// �����ϴٸ� �ϵ���� ���ؽ� ���μ��� ���
		behaivorFlag = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		// �ƴ϶�� ����Ʈ���� ���ؽ� ���μ��� ���
		behaivorFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	// ���ǽ� (Surface)
	// 1. ������Ʈ�� or �̹��� ó���� ���� ������ �ȼ� (�÷����� -> ����/�ĸ�)
	// 2. ����/���ٽ� ���� (����/���ٽ� ����)

	// ����Ʈ(����) ����
	// ���� ���� ��ġ�� ��µǰ� �ִ� �޸� ���� (�÷� ����)
	// 
	// ��(�ĸ�) ����
	// ��� �ӵ� ����� ����Ʈ ���ۿ� ������ ���� ������ �����ϰ� �ִ� ����
	// �÷� ����->  �ȼ� ����
	// ���� ����->  ���ο� �ȼ��� �÷� ���ۿ� ��� ���ΰ��� ���� �Ǻ� ��
	//				(���� z ��,)
	// ���ٽ� ����-> ���� ���ۿ� ���, Ư�� ������ �׸����� ���� ���� (���� masking ��)

	// ������ ����� ����/�ĸ� �� ����/���ٽ� ���ۿ� ���� ���� ���� ���� ����ü
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	// �ĸ� ���� ����
	d3dpp.BackBufferWidth = WIN_SIZE_X;
	d3dpp.BackBufferHeight = WIN_SIZE_Y;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	// ���� �� ���ٽ� ���� ����
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.EnableAutoDepthStencil = true;

	// ���������� ������ �������� �ڵ��� ����
	d3dpp.hDeviceWindow = g_hWnd;
	// ������ ��� (â, Ǯ���)
	d3dpp.Windowed = mode;

	// ���� ü�� -> ������ ���ǽ��� �ϳ��� �÷������� ����
	
	// �������� ��      �� ���̴� ��
	// ���ǽ�1			���ǽ�2
	// ���� ����        �ĸ� ����
	// ���ǽ�2          ���ǽ�1
	// ���� ����        �ĸ� ����

	// ���� ü�� (���� ���۸�) ��ȯ ����� ����
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	
	// ȭ�� ����� ���� (ȭ���� ���� ��ġ�� �ӵ�)
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	// �ĸ� ���۸� ���� ���ۿ� ǥ���� �� �ִ� �ִ�ӵ� ����
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	// ��ġ ����
	if (FAILED(direct->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		g_hWnd, behaivorFlag, &d3dpp, &device)))
	{
		ERR_MSG(g_hWnd, L"��ġ ���� ����");
		return E_FAIL;
	}

	// ��Ʈ ���� ����
	D3DXFONT_DESC fontInfo;
	ZeroMemory(&fontInfo, sizeof(fontInfo));

	fontInfo.Height = 20;
	fontInfo.Width = 10;
	fontInfo.Weight = FW_HEAVY;
	fontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(fontInfo.FaceName, L"�ü�");

	// ��Ʈ ��ü ����
	if (FAILED(D3DXCreateFontIndirect(device, &fontInfo, &font)))
	{
		ERR_MSG(g_hWnd, L"��Ʈ ���� ����");
		return E_FAIL;
	}

	return S_OK;
}

// 1. ȭ���� Clear() �Լ��� �ʱ�ȭ
// 2. ����� �ĸ� ���ۿ� �׸��� ���� device�� BeginScene() �� ȣ��
// 3. ����� �׸���. (���� ���ϴ� ���� �׸���)
// 4. �� �׷����� EndScene() �Լ��� ȣ��
// 5. Present() �Լ��� �����̶� �ĸ��� ��ü
// 6. 1~5 �ݺ�

// ����̽� �׸��� ����
// �� ����
// ����̽� �׸��� ��


void Device::RenderBegin()
{
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	device->BeginScene();
}

void Device::RenderEnd()
{
	device->EndScene();
	device->Present(NULL, NULL, NULL, NULL);
}

void Device::Release()
{
	if (sprite)
		sprite->Release();
	
	if (device)
		device->Release();
	
	if (direct)
		direct->Release();
}
