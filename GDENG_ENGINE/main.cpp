#include "AppWindow.h"
#include "InputSystem.h"


int main()
{
	try
	{
		GraphicsEngine::create();
		InputSystem::initialize();
	}
	catch (...) { return -1; }
	

	

	
	{
		try
		{
			AppWindow app;
			while (app.isRun());
		}
		catch(...)
		{
			GraphicsEngine::release();
			InputSystem::destroy();

			return -1;
		}
		
	}

	GraphicsEngine::release();
	InputSystem::destroy();

	return 0;
}