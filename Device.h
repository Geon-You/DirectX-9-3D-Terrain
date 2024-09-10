#pragma once
#include "Include.h"

class Device
{
public:
	DECLARE_SINGLETON(Device);

private:
	Device();
public:
	~Device();

private:
	// ��ġ ���� ���縦 ���� ���̷�Ʈ ��ü�� ���� �ʵ�
	LPDIRECT3D9 direct;
	// ��ġ�� ��ǥ�ϴ� ��ü
	LPDIRECT3DDEVICE9 device;
	// �̹��� ������ ��ǥ�ϴ� ��ü
	LPD3DXSPRITE sprite;
	// ��Ʈ
	LPD3DXFONT font;

public:
	HRESULT InitDevice(WinMode mode); // ��ġ�ʱ�ȭ
	void RenderBegin(); // �׸��� ���� ��, ȣ��
	void RenderEnd();   // �׸��� ���� ��, ȣ��
	void Release();

public:
	LPDIRECT3DDEVICE9 GetDevice() { return device; }
	LPD3DXSPRITE GetSprite() { return sprite; }
	LPD3DXFONT GetFont() { return font; }
};

