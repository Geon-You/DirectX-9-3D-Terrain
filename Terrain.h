#pragma once
#include "Define.h"

typedef class TerrainVertex
{
public:
	D3DXVECTOR3 p; // ����Ʈ
	D3DXVECTOR3 n; // ��� (����)
	D3DXVECTOR3 t; // ź��Ʈ
}TV;

class MyIndex
{
public:
	WORD _0, _1, _2;
};

class Terrain
{
private:
	LPDIRECT3DVERTEXBUFFER9 vb = 0; // ������ ������ ����
	LPDIRECT3DINDEXBUFFER9 ib = 0; // �ε����� ������ ����
	LPDIRECT3DTEXTURE9 texDiffuse = 0; // �ؽ��� �����
	LPDIRECT3DTEXTURE9 texHeight = 0; // �ؽ��� ���̸�

	DWORD cxHeight; // �ؽ��� ���� ũ��
	DWORD czHeight; // �ؽ��� ���� ũ��

	D3DXMATRIXA16 matRot; // �ͷ��� ȸ���� ����� ���

public:
	void Initialize();
	void Update();
	void Render();
	void Release();

	HRESULT InitTexture(); // �ؽ��� �ε� �� �ʱ�ȭ
	HRESULT InitVB(); // ���� ���� �ʱ�ȭ
	HRESULT InitIB(); // �ε��� ���� �ʱ�ȭ

	void DrawMesh();
	void Animate(); // ȸ�� �ִϸ��̼�
};

