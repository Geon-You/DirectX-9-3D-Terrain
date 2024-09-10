#include "Shape.h"
#include "Device.h"

void Shape::Initialize()
{
	auto device = GET_SINGLE(Device)->GetDevice();

	// ���� �ʱ�ȭ
	light = D3DXVECTOR3(0, 0, 0);

	// �浹 �ڽ� ����
	// ���ؽ��� �޸�, ť�� ����� �浹ü�� ǥ���ϴµ� �ʿ��� �ּ����� �� 8���� ������ ��
	center = new D3DXVECTOR3[8]
	{
		D3DXVECTOR3(-5, 5, -5), D3DXVECTOR3(5, 5, -5), D3DXVECTOR3(-5, 5, 5),
		D3DXVECTOR3(5, 5, 5), D3DXVECTOR3(-5, -5, -5), D3DXVECTOR3(5, -5, -5),
		D3DXVECTOR3(-5, -5, 5), D3DXVECTOR3(5, -5, 5)
	};

	// �ؽ��� �ε� (���� �ؽ���)
	if (FAILED(D3DXCreateTextureFromFile(device, L"stone.bmp", &texture)))
	{
		// �ؽ��� ���� ���� ��, �޼��� �˾�
		MessageBox(NULL, L"Texture Load Failed", L"Fail", MB_OK);
		return;
	}

	// �ؽ��� �ε� (��ָ� �ؽ���)
	if (FAILED(D3DXCreateTextureFromFile(device, L"stoneNormal.bmp", &textureNormal)))
	{
		// �ؽ��� ���� ���� ��, �޼��� �˾�
		MessageBox(NULL, L"Texture Load Failed", L"Fail", MB_OK);
		return;
	}

	// �ؽ��� ���͸� ����
	// �ؽ��İ� ��� ���� ��, ���ø��� ��� ����
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	// �ؽ��İ� Ȯ�� ���� ��, ���ø��� ��� ����
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	// �ؽ��� ���͸� ����
	// �ؽ��İ� ��� ���� ��, ���ø��� ��� ����
	device->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	// �ؽ��İ� Ȯ�� ���� ��, ���ø��� ��� ����
	device->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	// 0�� �ؽ��� �ε��� ���
	device->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	// 1�� �ؽ��� �ε��� ���
	device->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);


	// ���ؽ� ���� ����
	if (FAILED(device->CreateVertexBuffer(sizeof(VERTEX) * 24, NULL,
		D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &vb, NULL)))
	{
		// ���ؽ� ���� ���� ���� ��, �޼��� �˾�
		MessageBox(NULL, L"Create VB Failed", L"Fail", MB_OK);
		return;
	}

	// ���ؽ� ���� ��� (�а� ����� ���ÿ� ����� �� �����Ƿ�)
	VERTEX* vertice;
	if (FAILED(vb->Lock(0, sizeof(VERTEX) * 24, (void**)&vertice, NULL)))
		return;

	// ����
	// 1�� ��
	vertice[0].position = D3DXVECTOR3(-5, 5, -5);
	vertice[0].color = 0xFFFFFFFF;
	vertice[0].tu = 0;
	vertice[0].tv = 0;

	vertice[1].position = D3DXVECTOR3(5, 5, -5);
	vertice[1].color = 0xFFFFFFFF;
	vertice[1].tu = .33f;
	vertice[1].tv = 0;

	vertice[2].position = D3DXVECTOR3(-5, -5, -5);
	vertice[2].color = 0xFFFFFFFF;
	vertice[2].tu = 0;
	vertice[2].tv = .5f;

	vertice[3].position = D3DXVECTOR3(5, -5, -5);
	vertice[3].color = 0xFFFFFFFF;
	vertice[3].tu = .33f;
	vertice[3].tv = .5f;

	// 2�� ��
	vertice[4].position = D3DXVECTOR3(5, 5, 5);
	vertice[4].color = 0xFFFFFFFF;
	vertice[4].tu = .66f;
	vertice[4].tv = .5f;

	vertice[5].position = D3DXVECTOR3(-5, 5, 5);
	vertice[5].color = 0xFFFFFFFF;
	vertice[5].tu = 1;
	vertice[5].tv = .5f;

	vertice[6].position = D3DXVECTOR3(5, -5, 5);
	vertice[6].color = 0xFFFFFFFF;
	vertice[6].tu = .66f;
	vertice[6].tv = 1;

	vertice[7].position = D3DXVECTOR3(-5, -5, 5);
	vertice[7].color = 0xFFFFFFFF;
	vertice[7].tu = 1;
	vertice[7].tv = 1;

	// 3�� ��
	vertice[8].position = D3DXVECTOR3(-5, 5, 5);
	vertice[8].color = 0xFFFFFFFF;
	vertice[8].tu = .33f;
	vertice[8].tv = 0;

	vertice[9].position = D3DXVECTOR3(5, 5, 5);
	vertice[9].color = 0xFFFFFFFF;
	vertice[9].tu = .66f;
	vertice[9].tv = 0;

	vertice[10].position = D3DXVECTOR3(-5, 5, -5);
	vertice[10].color = 0xFFFFFFFF;
	vertice[10].tu = .33f;
	vertice[10].tv = .5f;

	vertice[11].position = D3DXVECTOR3(5, 5, -5);
	vertice[11].color = 0xFFFFFFFF;
	vertice[11].tu = .66f;
	vertice[11].tv = .5f;

	// 4�� ��
	vertice[12].position = D3DXVECTOR3(5, 5, -5);
	vertice[12].color = 0xFFFFFFFF;
	vertice[12].tu = .66f;
	vertice[12].tv = 0;

	vertice[13].position = D3DXVECTOR3(5, 5, 5);
	vertice[13].color = 0xFFFFFFFF;
	vertice[13].tu = 1;
	vertice[13].tv = 0;

	vertice[14].position = D3DXVECTOR3(5, -5, -5);
	vertice[14].color = 0xFFFFFFFF;
	vertice[14].tu = .66f;
	vertice[14].tv = .5f;

	vertice[15].position = D3DXVECTOR3(5, -5, 5);
	vertice[15].color = 0xFFFFFFFF;
	vertice[15].tu = 1;
	vertice[15].tv = .5f;

	// 5�� ��
	vertice[16].position = D3DXVECTOR3(-5, -5, -5);
	vertice[16].color = 0xFFFFFFFF;
	vertice[16].tu = 0;
	vertice[16].tv = .5f;

	vertice[17].position = D3DXVECTOR3(5, -5, -5);
	vertice[17].color = 0xFFFFFFFF;
	vertice[17].tu = .33f;
	vertice[17].tv = .5f;

	vertice[18].position = D3DXVECTOR3(-5, -5, 5);
	vertice[18].color = 0xFFFFFFFF;
	vertice[18].tu = 0;
	vertice[18].tv = 1;

	vertice[19].position = D3DXVECTOR3(5, -5, 5);
	vertice[19].color = 0xFFFFFFFF;
	vertice[19].tu = .33f;
	vertice[19].tv = 1;

	// 6�� ��
	vertice[20].position = D3DXVECTOR3(-5, 5, 5);
	vertice[20].color = 0xFFFFFFFF;
	vertice[20].tu = .33f;
	vertice[20].tv = .5f;

	vertice[21].position = D3DXVECTOR3(-5, 5, -5);
	vertice[21].color = 0xFFFFFFFF;
	vertice[21].tu = .66f;
	vertice[21].tv = .5f;

	vertice[22].position = D3DXVECTOR3(-5, -5, 5);
	vertice[22].color = 0xFFFFFFFF;
	vertice[22].tu = .33f;
	vertice[22].tv = 1;

	vertice[23].position = D3DXVECTOR3(-5, -5, -5);
	vertice[23].color = 0xFFFFFFFF;
	vertice[23].tu = .66f;
	vertice[23].tv = 1;

	// ������ ���� ��, ���� ��� ����
	vb->Unlock();

	shapeNum = 1;
	pos = D3DXVECTOR3(0, 0, 0);
	scale = D3DXVECTOR3(1.f, 1.f, 1.f);
	angle = D3DXVECTOR3(0, 0, 0);
}

void Shape::Update()
{
	// �׸� �޽� ����
	if (GetAsyncKeyState('1')) shapeNum = 1;
	if (GetAsyncKeyState('2')) shapeNum = 2;
	if (GetAsyncKeyState('3')) shapeNum = 3;
	if (GetAsyncKeyState('4')) shapeNum = 4;

	// x�� ȸ��
	if (GetAsyncKeyState('Q')) angle.x -= 1.f;
	if (GetAsyncKeyState('W')) angle.x += 1.f;

	// y�� ȸ��
	if (GetAsyncKeyState('E')) angle.y -= 1.f;
	if (GetAsyncKeyState('R')) angle.y += 1.f;

	// z�� ȸ��
	if (GetAsyncKeyState('T')) angle.z -= 1.f;
	if (GetAsyncKeyState('Y')) angle.z += 1.f;

	// �̵�
	if (GetAsyncKeyState(VK_NUMPAD4)) pos.x -= 1.f;
	if (GetAsyncKeyState(VK_NUMPAD6)) pos.x += 1.f;

	if (GetAsyncKeyState(VK_NUMPAD8)) pos.y -= 1.f;
	if (GetAsyncKeyState(VK_NUMPAD2)) pos.y += 1.f;

	if (GetAsyncKeyState(VK_NUMPAD7)) pos.z -= 1.f;
	if (GetAsyncKeyState(VK_NUMPAD9)) pos.z += 1.f;
}

void Shape::Render()
{
	if (isPicking)
		return;

	CalculateLight();

	auto device = GET_SINGLE(Device)->GetDevice();

	// ���� ���� (�⺻���� ������ ��������) -> ������ �� ����
	// -> ���� �ɼ��� ����������, ���� ���忡 ��ġ�� ������ �����Ƿ� ������ �� ����
	// ������ �� ���, �޽��� ���ؽ��� ������ �ִ� �⺻ ������ ����
	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �׸��� ���� ����
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	// �齺���̽� �ø� (�޸� �߷�����, ����ȭ ���)
	// �齺���̽� �ø� -> �ð����(CW) or �ݽð����(CCW)
	// �ø� �⺻ ���� ���� CCW, �޸��� �׸��� �ʴ´�.
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	D3DXMATRIX matTrans; // ��ġ ���
	D3DXMATRIX matRot;	 // ȸ�� ���
	D3DXMATRIX matScale; // ũ�� ���
	D3DXMATRIX matWorld; // ���� ���

	// ��� �������� ���� ���� ȸ���� ǥ�� ��,
	// ������ ������ �߻���
	// �� ������ ������ �ذ� �� �� �ִ� ���� ���ʹϾ�
	// �׸��� ���� �࿡ ���� ȸ�� ���꿡 ���ؼ��� ���ʹϾ��� ����ӵ��� �� ���� (���� �࿡ ���� ����� ��� ������ �� ����)
	// ��Ŀ����� degree�� radian�� �̿��� ����(������)�� ������ ���ʹϾ��� �츮�� ���������� �˾ƺ� �� �ִ� ������ �ƴϴ�(�������� ������ �ʿ���).

	D3DXQUATERNION q; // ���ʹϾ�
	D3DXVECTOR3 radAngle; // �������� ��ȯ�� �ޱ� ���� ���� ����

	radAngle.x = D3DXToRadian(angle.x);
	radAngle.y = D3DXToRadian(angle.y);
	radAngle.z = D3DXToRadian(angle.z);

	// ��ġ ��� ��ȯ
	D3DXMatrixTranslation(&matTrans, pos.x, pos.y, pos.z);

	// ȸ�� ��� ��ȯ
	D3DXQuaternionRotationYawPitchRoll(&q, radAngle.y, radAngle.x, radAngle.z);
	D3DXMatrixRotationQuaternion(&matRot, &q);

	// ũ�� ��� ��ȯ
	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);

	// ���� ��� ����
	matWorld = matScale * matRot * matTrans;
	// ������ ���� ����� ����
	device->SetTransform(D3DTS_WORLD, &matWorld);

	// ���� ���͸� RGBA�� ��ȯ
	DWORD dwFactor = VectorToRGBA(&light);
	// RGBA�� ��ȯ�� ���͸� TextureFactor ������ ���
	device->SetRenderState(D3DRS_TEXTUREFACTOR, dwFactor);

	// ��ָ� �ؽ����� RGBA�� ���� ���͸� ����
	device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
	device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DOTPRODUCT3);

	// ��ָ� �ؽ��Ŀ� ������ �ؽ��ĸ� ��� ���
	device->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
	device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	

	// �ؽ��� ���� (�ؽ��� ����)
	device->SetTexture(0, textureNormal);
	device->SetTexture(1, texture);

	// ����� ���ؽ� ���� ����
	device->SetStreamSource(0, vb, 0, sizeof(VERTEX));
	// FVF ����
	device->SetFVF(D3DFVF_CUSTOMVERTEX);

	// �ﰢ�� 2���� �̿��Ͽ� �� ���� �׸�
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 8, 2);
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 12, 2);
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 16, 2);
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 20, 2);
}

void Shape::Release()
{
	if (texture)
	{
		texture->Release();
		texture = nullptr;
	}

	if (textureNormal)
	{
		textureNormal->Release();
		textureNormal = nullptr;
	}

	if (vb)
	{
		vb->Release();
		vb = nullptr;
	}

	if (center)
	{
		delete center;
		center = nullptr;
	}
}

void Shape::CalculateLight()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	light.x = -(((2.f * pt.x) / WIN_SIZE_X) - 1);
	light.y = -(((2.f * pt.y) / WIN_SIZE_Y) - 1);
	light.z = 0;

	if (D3DXVec3Length(&light) > 1.f)
	{
		D3DXVec3Normalize(&light, &light);
	}
	else
	{
		light.z = sqrt(1.f - light.x * light.x - light.y * light.y);
	}
}

DWORD Shape::VectorToRGBA(D3DXVECTOR3* v)
{
	DWORD r = (DWORD)(127.f * v->x + 128.f);
	DWORD g = (DWORD)(127.f * v->y + 128.f);
	DWORD b = (DWORD)(127.f * v->z + 128.f);
	DWORD a = (DWORD)255.f;

	return (a << 24) + (r << 16) + (g << 8) + b;
}

bool Shape::OncollisionEnter(D3DXVECTOR3* ori, D3DXVECTOR3* dir)
{
	// �ֻ����� ������ �浹 ������ �Ǻ�
	// ���̿� �޽��� �ﰢ�� �浹 ��, �浹 ������ x, y, �Ÿ� t(z��)
	float u, v, t;
	isPicking = false;

	// �ﰢ���� �� ���ؽ� ��ġ�� ���� ����
	D3DXVECTOR3 v1, v2, v3;
	v1 = center[0] + pos;
	v2 = center[1] + pos;
	v3 = center[2] + pos;

	// ������ �ﰢ���� �浹 üũ -> D3DXIntersectTri();
	if (D3DXIntersectTri(&v1, &v2, &v3, ori, dir, &u, &v, &t))
	{
		isPicking = true;
		return true;
	}

	v1 = center[1] + pos;
	v2 = center[2] + pos;
	v3 = center[3] + pos;

	if (D3DXIntersectTri(&v1, &v2, &v3, ori, dir, &u, &v, &t))
	{
		isPicking = true;
		return true;
	}

	v1 = center[0] + pos;
	v2 = center[1] + pos;
	v3 = center[4] + pos;

	if (D3DXIntersectTri(&v1, &v2, &v3, ori, dir, &u, &v, &t))
	{
		isPicking = true;
		return true;
	}

	v1 = center[0] + pos;
	v2 = center[1] + pos;
	v3 = center[5] + pos;

	if (D3DXIntersectTri(&v1, &v2, &v3, ori, dir, &u, &v, &t))
	{
		isPicking = true;
		return true;
	}

	v1 = center[1] + pos;
	v2 = center[5] + pos;
	v3 = center[7] + pos;

	if (D3DXIntersectTri(&v1, &v2, &v3, ori, dir, &u, &v, &t))
	{
		isPicking = true;
		return true;
	}

	v1 = center[1] + pos;
	v2 = center[7] + pos;
	v3 = center[3] + pos;

	if (D3DXIntersectTri(&v1, &v2, &v3, ori, dir, &u, &v, &t))
	{
		isPicking = true;
		return true;
	}

	v1 = center[0] + pos;
	v2 = center[2] + pos;
	v3 = center[6] + pos;

	if (D3DXIntersectTri(&v1, &v2, &v3, ori, dir, &u, &v, &t))
	{
		isPicking = true;
		return true;
	}

	v1 = center[0] + pos;
	v2 = center[4] + pos;
	v3 = center[6] + pos;

	if (D3DXIntersectTri(&v1, &v2, &v3, ori, dir, &u, &v, &t))
	{
		isPicking = true;
		return true;
	}

	v1 = center[2] + pos;
	v2 = center[6] + pos;
	v3 = center[3] + pos;

	if (D3DXIntersectTri(&v1, &v2, &v3, ori, dir, &u, &v, &t))
	{
		isPicking = true;
		return true;
	}

	v1 = center[7] + pos;
	v2 = center[6] + pos;
	v3 = center[3] + pos;

	if (D3DXIntersectTri(&v1, &v2, &v3, ori, dir, &u, &v, &t))
	{
		isPicking = true;
		return true;
	}

	v1 = center[6] + pos;
	v2 = center[4] + pos;
	v3 = center[5] + pos;

	if (D3DXIntersectTri(&v1, &v2, &v3, ori, dir, &u, &v, &t))
	{
		isPicking = true;
		return true;
	}

	v1 = center[6] + pos;
	v2 = center[5] + pos;
	v3 = center[7] + pos;

	if (D3DXIntersectTri(&v1, &v2, &v3, ori, dir, &u, &v, &t))
	{
		isPicking = true;
		return true;
	}

	return false;
}
