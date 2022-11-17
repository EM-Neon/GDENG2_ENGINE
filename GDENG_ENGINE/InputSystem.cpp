#include "InputSystem.h"

InputSystem* InputSystem::sharedInstance = nullptr;

InputSystem::InputSystem()
{
	this->m_old_mouse_pos = Point(0, 0);
}

InputSystem::~InputSystem()
{
	this->inputListenersList.clear();
	InputSystem::sharedInstance = nullptr;
}

void InputSystem::update()
{
	POINT currentPt = {};
	GetCursorPos(&currentPt);

	if(this->m_first_time)
	{
		this->m_first_time = false;
		this->m_old_mouse_pos = Point(currentPt.x, currentPt.y);
	}

	if(this->m_old_mouse_pos.m_x != currentPt.x || this->m_old_mouse_pos.m_y != currentPt.y)
	{
		Point deltaPt = Point(currentPt.x - this->m_old_mouse_pos.m_x, currentPt.y - this->m_old_mouse_pos.m_y);
		this->onMouseMove(deltaPt);
	}

	this->m_old_mouse_pos = Point(currentPt.x, currentPt.y);

	if (GetKeyboardState(this->m_keys_state))
	{
		for(int i = 0; i < ARRAYSIZE(this->m_keys_state); i++)
		{
			if(this->m_keys_state[i] & 0x80 && this->m_keys_state[i] != this->m_old_keys_state[i])
			{
				if(i == VK_LBUTTON && this->m_keys_state[i] != this->m_old_keys_state[i])
				{
					Point deltaPt = Point(currentPt.x - this->m_old_mouse_pos.m_x, currentPt.y - this->m_old_mouse_pos.m_y);
					this->onLeftMouseDown(deltaPt);
				}
				else if(i == VK_RBUTTON && this->m_keys_state[i] != this->m_old_keys_state[i])
				{
					Point deltaPt = Point(currentPt.x - this->m_old_mouse_pos.m_x, currentPt.y - this->m_old_mouse_pos.m_y);
					this->onRightMouseDown(deltaPt);
				}
				else
				{
					this->callOnKeyDown(i);
				}
			}
			else if(this->m_keys_state[i] != this->m_old_keys_state[i])
			{
				if(i == VK_LBUTTON && this->m_keys_state[i] != this->m_old_keys_state[i])
				{
					Point deltaPt = Point(currentPt.x - this->m_old_mouse_pos.m_x, currentPt.y - this->m_old_mouse_pos.m_y);
					this->onLeftMouseUp(deltaPt);
				}
				else if(i == VK_RBUTTON && this->m_keys_state[i] != this->m_old_keys_state[i])
				{
					Point deltaPt = Point(currentPt.x - this->m_old_mouse_pos.m_x, currentPt.y - this->m_old_mouse_pos.m_y);
					this->onRightMouseUp(deltaPt);
				}
				else
				{
					this->callOnKeyUp(i);
				}
			}
		}

		::memcpy(this->m_old_keys_state, this->m_keys_state, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	this->inputListenersList.push_back(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	int index = -1;
	for(int i = 0; i < this->inputListenersList.size(); i++)
	{
		if(this->inputListenersList[i] == listener)
		{
			index = i;
			break;
		}
	}
	if(index > -1)
	{
		this->inputListenersList.erase(this->inputListenersList.begin() + index);
	}
}

void InputSystem::setCursorPosition(const Point& pos)
{
	::SetCursorPos(pos.m_x, pos.m_y);
}

void InputSystem::showCursor(bool show)
{
	::ShowCursor(show);
}

bool InputSystem::isKeyDown(int key)
{
	for(int i = 0; i < ARRAYSIZE(this->m_keys_state); i++)
	{
		if(this->m_keys_state[i] & 0x80 && i == key)
		{
			return true;
		}
		else if(i == key)
		{
			return false;
		}
	}

	return false;
}

bool InputSystem::isKeyUp(int key)
{
	for(int i = 0; i < ARRAYSIZE(this->m_keys_state); i++)
	{
		if (!(this->m_keys_state[i] & 0x80) && i == key)
		{
			return true;
		}
		else if (i == key)
		{
			return false;
		}
	}

	return false;
}

void InputSystem::callOnKeyDown(int key)
{
	for(int i = 0; i < this->inputListenersList.size();i++)
	{
		this->inputListenersList[i]->onKeyDown(key);
	}
}

void InputSystem::callOnKeyUp(int key)
{
	for(int i = 0; i < this->inputListenersList.size(); i++)
	{
		this->inputListenersList[i]->onKeyUp(key);
	}
}

void InputSystem::onMouseMove(Point deltaPt)
{
	for(int i = 0; i < this->inputListenersList.size(); i++)
	{
		this->inputListenersList[i]->onMouseMove(deltaPt);
	}
}

void InputSystem::onLeftMouseDown(Point deltaPt)
{
	for(int i = 0; i < this->inputListenersList.size(); i++)
	{
		this->inputListenersList[i]->onLeftMouseDown(deltaPt);
	}
}

void InputSystem::onLeftMouseUp(Point deltaPt)
{
	for (int i = 0; i < this->inputListenersList.size(); i++) {
		this->inputListenersList[i]->onLeftMouseUp(deltaPt);
	}
}

void InputSystem::onRightMouseDown(Point deltaPt)
{
	for (int i = 0; i < this->inputListenersList.size(); i++) {
		this->inputListenersList[i]->onRightMouseDown(deltaPt);
	}
}

void InputSystem::onRightMouseUp(Point deltaPt)
{
	for (int i = 0; i < this->inputListenersList.size(); i++) {
		this->inputListenersList[i]->onRightMouseUp(deltaPt);
	}
}

void InputSystem::initialize()
{
	if (InputSystem::sharedInstance) throw std::exception("InputSystem already created");
	InputSystem::sharedInstance = new InputSystem();
}

void InputSystem::destroy()
{
	if (!InputSystem::sharedInstance) return;
	delete InputSystem::sharedInstance;
}

InputSystem* InputSystem::get()
{
	return sharedInstance;
}
