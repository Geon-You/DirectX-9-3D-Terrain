#pragma once
#include "Include.h"

class Scene;

class MainGame
{
private:
	Scene* scene;

public:
	void Initialize(); // �ʱ�ȭ
	void Update(); // ���� �� ���� ����
	void Render(); // ���� �� �׸���
	void Release(); // �޸� ����
	void OnMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	MainGame();
	~MainGame();
};

