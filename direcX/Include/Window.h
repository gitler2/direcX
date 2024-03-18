#pragma once 

#include <Windows.h>

#define WEIGHT 1000
#define HEIGHT 600

class Window
{
public:
	Window() = default;
	~Window() = default;
	bool Init();
	bool BroadCast();
	bool Release();
	bool isWindowRunning();

	virtual void OnCreate();
	virtual void OnUpdate();
	virtual void OnDestroy();
protected:
	HWND hWnd;
	bool isRunning;
};