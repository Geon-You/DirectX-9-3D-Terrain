#include "Terrain.h"
#include "Device.h"

void Terrain::Initialize()
{
    if (FAILED(InitTexture()))
        return;

    if (FAILED(InitVB()))
        return;

    if (FAILED(InitIB()))
        return;
}

void Terrain::Update()
{
    Animate();
}

void Terrain::Render()
{
    auto device = GET_SINGLE(Device)->GetDevice();

    device->SetRenderState(D3DRS_LIGHTING, FALSE);

    // 0�� �ؽ��� ���������� ����� �ؽ��� ����
    device->SetTexture(0, texDiffuse);
    // 0�� �ؽ��Ŀ� Ȯ�� ���� ����
    device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    // 0�� �ؽ��� �ε��� ���
    device->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);

    DrawMesh();
}

void Terrain::Release()
{
    if (texDiffuse != nullptr)
    {
        texDiffuse->Release();
        texDiffuse = nullptr;
    }

    if (texHeight != nullptr)
    {
        texHeight->Release();
        texHeight = nullptr;
    }

    if (vb != nullptr)
    {
        vb->Release();
        vb = nullptr;
    }

    if (ib != nullptr)
    {
        ib->Release();
        ib = nullptr;
    }
}

HRESULT Terrain::InitTexture()
{
    auto device = GET_SINGLE(Device)->GetDevice();

    // ���̸� �ؽ��� �ε�
    if (FAILED(D3DXCreateTextureFromFileEx(device, L"height.bmp", D3DX_DEFAULT,
        D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED,
        D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &texHeight)))
    {
        return E_FAIL;
    }

    // ����� �ؽ��� �ε�
    if (FAILED(D3DXCreateTextureFromFile(device, L"tile.bmp", &texDiffuse)))
    {
        return E_FAIL;
    }

    return S_OK;
}

HRESULT Terrain::InitVB()
{
    D3DSURFACE_DESC sd;
    D3DLOCKED_RECT rc;

    // �ؽ��� ���� ��������
    texHeight->GetLevelDesc(0, &sd);
    cxHeight = sd.Width; // �ؽ��� ���� ũ��
    czHeight = sd.Height; // �ؽ��� ���� ũ��

    auto device = GET_SINGLE(Device)->GetDevice();

    // ���ؽ� ���� ����
    if (FAILED(device->CreateVertexBuffer(cxHeight * czHeight * sizeof(TV),
        0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &vb, NULL)))
    {
        return E_FAIL;
    }

    // �ؽ��� �޸� ���� �ϸ鼭 �ؽ��� ������ ������
    texHeight->LockRect(0, &rc, NULL, D3DLOCK_READONLY);

    // ���ؽ� ���� ��
    void* vertice;
    if (FAILED(vb->Lock(0, cxHeight * czHeight * sizeof(TV), (void**)&vertice, NULL)))
    {
        return E_FAIL;
    }

    // �ͷ��� ���ؽ� ����
    // �޾ƿ� ���ؽ� ������ ���� �ּҸ� �ͷ��� ���ؽ� ���·� ĳ����
    // -> ��� - ������ ������ �ͷ��� ���ؽ� ���·� ��� ����
    TV* pv = (TV*)vertice;
    TV v;

    // �ؽ��� ���� ũ�⸸ŭ �ݺ�
    for (DWORD z = 0; z < czHeight; ++z)
    {
        // �ؽ��� ���� ũ�⸸ŭ �ݺ�
        for (DWORD x = 0; x < cxHeight; ++x)
        {
            // �޽� �����͸� ������ �����Ͽ� x, z ��ǥ ���� (y�� ��ǥ�� ���̸ʿ��� �о��)
            v.p.x = (float)x - cxHeight / 2.f;
            // �޼� ��ǥ��� z�� ���� ������ ����� �����̹Ƿ� -�� ����
            v.p.z = -((float)z - czHeight / 2.f);

            // ���ؽ��� y (����) ���� ���̸� �ؽ����� ������ ���� ����
            // Bits -> ��� �ؽ��Ŀ� ���� ��ü ��Ʈ (��ü ��Ʈ�� ���� �ּ�)
            // Pitch -> �� �࿡ �ִ� ����Ʈ ��
            v.p.y = (*((LPDWORD)rc.pBits + x + z * (rc.Pitch / 4)) & 0x000000ff) / 5.f;

            // ��� ���� ����
            v.n = v.p;
            D3DXVec3Normalize(&v.n, &v.n);

            // t�� �ؽ��� ������ ���� u, v ��ǥ
            v.t.x = (float)x / (cxHeight - 1);
            v.t.y = (float)z / (czHeight - 1);

            // pv�� ���� ���� ���ؽ��� ���� ���ؽ� �迭 ���� ����
            // �������� ���� ��� ������ �ϳ��� ���ؽ� ������ ���ؽ� �迭�� ���ҿ� ������ ��
            // ���� ���ҷ� �Ѿ�� ���� �ּҸ� ��ó���� ++ ��Ŵ
            *pv++ = v;
        }
    }

    // ���ؽ� ����, �ؽ��� �� ����
    vb->Unlock();
    texHeight->UnlockRect(0);

    return S_OK;
}

HRESULT Terrain::InitIB()
{
    auto device = GET_SINGLE(Device)->GetDevice();

    // �ε��� ���� ����
    if (FAILED(device->CreateIndexBuffer(
        (cxHeight - 1) * (czHeight - 1) * 2 * sizeof(MyIndex),
        NULL, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &ib, NULL)))
    {
        return E_FAIL;
    }

    MyIndex* pi = NULL;

    // �ε��� ���� ��
    if (FAILED(ib->Lock(0, (cxHeight - 1) * (czHeight - 1) * 2 * sizeof(MyIndex),
        (void**)&pi, NULL)))
    {
        return E_FAIL;
    }

    MyIndex i;
    for (DWORD z = 0; z < czHeight - 1; ++z)
    {
        for (DWORD x = 0; x < cxHeight - 1; ++x)
        {
            // CW(�ð�) �������� Ʈ���̾ޱ��� ����
            // -> �ø��� CCW(�ݽð�)�� ���� �Ǿ��ֱ� ������
            i._0 = z * cxHeight + x;
            i._1 = z * cxHeight + x + 1;
            i._2 = (z + 1) * cxHeight + x;
            *pi++ = i;

            i._0 = (z + 1) * cxHeight + x;
            i._1 = z * cxHeight + x + 1;
            i._2 = (z + 1) * cxHeight + x + 1;
            *pi++ = i;
        }
    }

    ib->Unlock();

    return S_OK;
}

void Terrain::DrawMesh()
{
    auto device = GET_SINGLE(Device)->GetDevice();

    // ���� ��� ����
    device->SetTransform(D3DTS_WORLD, &matRot);
    // ���ؽ� ���� ���� �ҽ� ����
    device->SetStreamSource(0, vb, 0, sizeof(TV));
    // FVF ����
    device->SetFVF(D3DFVF_CUSTOMVERTEX);
    // �ε��� ���� ����
    device->SetIndices(ib);

    device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,
        cxHeight * czHeight, 0, (cxHeight - 1) * (czHeight - 1) * 2);
}

void Terrain::Animate()
{
    // static ���� ���� ���� ��, �� ó�� �� ���� �ʱ�ȭ�ǰ� ���� ������
    static ULONGLONG t = 0;
    static bool flag = false;

    // 0 ~ 2pi ������ ���� ���
    ULONGLONG d = GetTickCount64() % (int)(D3DX_PI * 2 * 1000);

    // y�� ȸ�� ���
    D3DXMatrixRotationY(&matRot, d / 1000.f);

    // 360�� ȸ���� �� �� �� ������ �÷��װ� �����
    if (d < t) flag = !flag;

    GET_SINGLE(Device)->GetDevice()->SetRenderState(D3DRS_FILLMODE,
        flag ? D3DFILL_WIREFRAME : D3DFILL_SOLID);

    t = d;
}
