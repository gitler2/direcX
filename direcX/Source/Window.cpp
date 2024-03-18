#include "../include/Window.h" 
#include <stdexcept>

LRESULT CALLBACK WindowProcess(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_CREATE:
	{
		Window* window = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		SetWindowLongPtr(hWindow, GWLP_USERDATA, (LONG_PTR)window);
		window->OnCreate();
		break;
	}
	case WM_DESTROY:
	{
		Window* window = (Window*)GetWindowLongPtr(hWindow, GWLP_USERDATA);
		window->OnDestroy();
		::PostQuitMessage(0);
		break;
	}
	case WM_SIZE:
	{
		INT widht = LOWORD(lParam);
		INT height = HIWORD(lParam);
	}
	default:
	{
		return ::DefWindowProcW(hWindow, uMessage, wParam, lParam);
	}
	}
	return NULL;
}

bool Window::Init()
{
	WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_BYTEALIGNCLIENT;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = L"WindowClass";
	wc.lpfnWndProc = &WindowProcess;

	if (!::RegisterClassEx(&wc))
		return false;

	hWnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"WindowClass", L"Engine", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		WEIGHT, HEIGHT, NULL, NULL, NULL, this);

	if (!hWnd)
		throw std::runtime_error("Window.cpp -> Window:Init() failed");

	::ShowWindow(hWnd, SW_SHOW);
	::UpdateWindow(hWnd);

	isRunning = true;

	return true;
}

bool Window::BroadCast()
{
	MSG message;
	while (::PeekMessage(&message, NULL, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&message);
		DispatchMessageW(&message);
	}
	this->OnUpdate();
	Sleep(1);

	return true;
}

bool Window::Release()
{
	if (!::DestroyWindow(hWnd))
		return false;

	return true;
}

bool Window::isWindowRunning()
{
	return this->isRunning;
}

void Window::OnCreate()
{
}

void Window::OnUpdate()
{
}

void Window::OnDestroy()
{
	isRunning = false;
}
