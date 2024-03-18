#include "../Include/AppWindow.h"
#include <memory>

int main()
{
	auto app = std::make_shared<Application>(Application());
	if (app->Init()) {
		while (app->isWindowRunning()) {
			app->BroadCast();
		}
	}

	return 0;
}