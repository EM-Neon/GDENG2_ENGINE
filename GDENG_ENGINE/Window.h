#pragma once
#define NOMINMAX //avoid conflict with Windows.h MIN and MAX declarations
#include <Windows.h>


class Window
{
public:
	//Initialize the window
	Window();
	//Release the window
	~Window();

	bool isRun();

	RECT getClientWindowRect();

	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();

private:
	bool broadcast();

protected:
	HWND m_hwnd;
	bool m_is_run;
	bool m_is_init = false;
};

