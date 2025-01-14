#include "CInputManager.h"
#include "CApplication.h"

extern Framework::CApplication application;

namespace Framework
{
	std::vector<CInputManager::Key> CInputManager::m_vecKeys = {};
	Maths::Vector2 CInputManager::m_vecMousePos = Maths::Vector2::One;
	int ASCII[] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, //���콺
		VK_BACK, VK_ESCAPE, VK_TAB, VK_RETURN, //�齺���̽�, ESC, ��, ����
		VK_CAPITAL, VK_SPACE,  //ĸ����
		VK_PRIOR, VK_NEXT, VK_END, VK_HOME, VK_INSERT, VK_DELETE, //����Ű �� Ű
		VK_LEFT, VK_UP, VK_RIGHT, VK_DOWN, //ȭ��ǥ
		VK_LWIN, VK_RWIN,	//������
		VK_LSHIFT, VK_RSHIFT, //����Ʈ
		VK_LCONTROL, VK_RCONTROL, //��Ʈ��
		VK_LMENU, VK_RMENU, //��Ʈ
		VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5,
		VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9,
		VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10, VK_F11, VK_F12,
		//VK_MULTIPLY, VK_ADD, VK_SEPARATOR,//����, ���ϱ�, ���� ��ȣ Ű
		//VK_DECIMAL, VK_DIVIDE, //�Ҽ���, ������
		VK_NUMLOCK, 
		VK_OEM_7, // '
		VK_OEM_6, //]
		VK_OEM_4, //[
		VK_OEM_5, //\|
		VK_OEM_3, //~`
		VK_OEM_2, // /?
		VK_OEM_1, // ;:
		VK_OEM_PERIOD, // .
		VK_OEM_MINUS, // -
		VK_OEM_COMMA, //,
		VK_OEM_PLUS, //+
	};

	void CInputManager::Initialize()
	{
		m_vecKeys.resize((UINT)eKeyCode::END);

		for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
		{
			m_vecKeys[i].state = eKeyState::None;
			m_vecKeys[i].keyCode = (eKeyCode)i;
		}
	}


	void CInputManager::Tick()
	{
		if(GetFocus())
		{
			UpdateKey();
		}
		else
		{
			ClearKey();
		}
	}

	bool CInputManager::IsKeyDown(eKeyCode key)
	{
		return GetAsyncKeyState(ASCII[(UINT)key]) & 0x8000;
	}

	void CInputManager::UpdateKeyDown(Key& key)
	{
		if (key.bPressed)
		{
			key.state = eKeyState::Pressed;
		}
		else
		{
			key.state = eKeyState::Down;
			key.bPressed = true;
		}
	}

	void CInputManager::UpdateKeyUp(Key& key)
	{
		if (key.bPressed)
		{
			key.state = eKeyState::Up;
			key.bPressed = false;
		}
		else
		{
			key.state = eKeyState::None;
		}
	}

	void CInputManager::UpdateCursorPosition()
	{
		POINT point = {};
		GetCursorPos(&point);
		ScreenToClient(application.GetHWND(), &point);
		m_vecMousePos = Maths::Vector2(point.x, point.y);
	}

	void CInputManager::UpdateKey()
	{
		for (Key& key : m_vecKeys)
		{
			if (IsKeyDown(key.keyCode))
			{
				UpdateKeyDown(key);
			}
			else
			{
				UpdateKeyUp(key);
			}
		}
		UpdateCursorPosition();
	}

	void CInputManager::ClearKey()
	{
		for (Key& key : m_vecKeys)
		{
			if (key.state == eKeyState::Down || key.state == eKeyState::Pressed)
			{
				key.state = eKeyState::Up;
				key.bPressed = false;
			}
			else if (key.state == eKeyState::Up)
			{
				key.state = eKeyState::None;
				key.bPressed = false;
			}
		}
	}

}