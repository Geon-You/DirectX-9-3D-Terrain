#pragma once
#include "Include.h"

// ���̽��� Texture Ŭ������ �ְ�
// �Ļ� Ŭ������ SingleTexture, MultiTexture
// Single - �ؽ�ó �� ���� �����ϰ� ����
// Multi - ������ �ؽ�ó ���� ���� �����ϰ� ����

class Texture abstract
{
public:
	Texture();
	virtual ~Texture();

public:
	virtual const TEXINFO* GetTexture(const TCHAR* key = nullptr, const int& cnt = 0) abstract;
	virtual HRESULT InsertTexture(const TCHAR* path, 
		const TCHAR* key = nullptr, const int& cnt = 0) abstract;
	virtual void Release() abstract;
};

