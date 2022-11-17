#pragma once
#include <iostream>
#include "InputListener.h"
#include <unordered_set>
#include "Point.h"
#include <Windows.h>

typedef std::vector<InputListener*> List;

class InputSystem
{
private:
	InputSystem();
	~InputSystem();
	InputSystem(InputSystem const&) {};

public:
	InputSystem& operator=(InputSystem const&) {};

	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	void setCursorPosition(const Point& pos);
	void showCursor(bool show);

	bool isKeyDown(int key);
	bool isKeyUp(int key);

	void callOnKeyDown(int key);
	void callOnKeyUp(int key);

	void onMouseMove(Point deltaPt);
	void onLeftMouseDown(Point deltaPt);
	void onLeftMouseUp(Point deltaPt);
	void onRightMouseDown(Point deltaPt);
	void onRightMouseUp(Point deltaPt);

	static InputSystem* sharedInstance;
	List inputListenersList;

public:
	static InputSystem* get();
	static void initialize();
	static void destroy();

private:
	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};
	Point m_old_mouse_pos;
	bool m_first_time = true;
};

