#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CApplication;

	enum class eKeyState	{	Up, Down, Pressed, None		};
	enum class eKeyCode		
	{	
		Q, W, E, R, T, Y, U, I, O, P, 
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		LBUTTON, RBUTTON, MIDDLEBUTTON,
		BackSpace, ESC, Tab, Enter,
		CapsLock, Space,
		PageUp, PageDown, End, Home, Insert, Delete,
		Left, Up, Right, Down,
		LeftWindow, RightWindow,
		LeftShift, RightShift,
		LeftControl, RightControl,
		LeftAlt, RightAlt,
		Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
		F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		//Multiply, Add, Separator, 
		NumLock, Quotes, CloseBracket, OpenBracket, Or, Tilde,
		Question, Colon, Dot, Minus, COMMA, PLUS,
		
		END
	};



	class CInputManager
	{
	public:
		struct Key
		{
			eKeyCode	keyCode;
			eKeyState	state;
			bool		bPressed;
		};


		__forceinline static bool GetKeyDown(eKeyCode key)		{ return m_vecKeys[(UINT)key].state == eKeyState::Down;		}
		__forceinline static bool GetKeyUp(eKeyCode key)		{ return m_vecKeys[(UINT)key].state == eKeyState::Up;		}
		__forceinline static bool GetKeyPressed(eKeyCode key)	{ return m_vecKeys[(UINT)key].state == eKeyState::Pressed;	}
		__forceinline static Maths::Vector2 GetMousePosition()	{ return m_vecMousePos; }

		friend CApplication;
	private:
		static void Initialize();
		static void Tick();

		static bool IsKeyDown(eKeyCode key);
		static void UpdateKeyDown(Key& key);
		static void UpdateKeyUp(Key& key);
		static void UpdateCursorPosition();

		static void UpdateKey();
		static void ClearKey();

		static Maths::Vector2 m_vecMousePos;

		static std::vector<Key> m_vecKeys;
	};

#define INPUT CInputManager


}


