#pragma once
#include "Include.h"

class Shape
{
public:
	int shapeNum;			// �ش� �ʵ尪���� � �޽ø� �׸� ������ ����
	D3DXVECTOR3 pos;		// ��ġ
	D3DXVECTOR3 angle;		// ȸ��
	D3DXVECTOR3 scale;		// ũ��

private:
	LPDIRECT3DTEXTURE9 texture;			// ���� �ؽ���
	LPDIRECT3DTEXTURE9 textureNormal;	// ��ָ� �ؽ���
	D3DXVECTOR3 light;					// ����

	IDirect3DVertexBuffer9* vb;			// ���ؽ� ����

	bool isPicking;			// ���� ���콺�� ����Ű�� �ִ��� (���콺�� �浹�ϰ� �ִ���)
	D3DXVECTOR3* center;	// �浹 �ڽ��� ���� ������ ��Ƶ� �迭

public:
	void Initialize();
	void Update();
	void Render();
	void Release();
	void CalculateLight();
	DWORD VectorToRGBA(D3DXVECTOR3* v);

	bool OncollisionEnter(D3DXVECTOR3* ori, D3DXVECTOR3* dir);
};

