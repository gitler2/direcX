#pragma once 
#include "../include/Window.h"

class Application : public Window
{
public:
	Application() = default;
	~Application() = default;

	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnDestroy() override;
};