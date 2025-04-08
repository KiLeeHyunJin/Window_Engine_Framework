#pragma once
#include "CommonInclude.h"

namespace Framework
{

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


	namespace Manager
	{
		//class CApplication;
		class CRenderManager;

		class CInputManager
		{
		public:
			__forceinline static bool GetKeyDown(eKeyCode key) { return m_vecKeys[static_cast<UINT>(key)].state == eKeyState::Down; }
			__forceinline static bool GetKeyUp(eKeyCode key) { return m_vecKeys[static_cast<UINT>(key)].state == eKeyState::Up; }
			__forceinline static bool GetKeyPressed(eKeyCode key) { return m_vecKeys[static_cast<UINT>(key)].state == eKeyState::Pressed; }
			__forceinline static const Maths::Vector2& GetMousePosition() { return m_vecMousePos; }

			friend class CApplication;
			friend CRenderManager;
		private:
			struct Key
			{
				eKeyCode	keyCode;
				eKeyState	state;
				bool		bPressed;
			};

			CInputManager();
			~CInputManager();

			static void Initialize(HWND hwnd);
			static void Tick();
			static void Render(HDC hdc, int posX, int posY);

			static bool IsKeyDown(eKeyCode key);
			static void UpdateKeyDown(Key& key);
			static void UpdateKeyUp(Key& key);
			static void UpdateCursorPosition();

			static void UpdateKey();
			static void ClearKey();
			//static void SetResolution(const Maths::Vector2& resolution) { m_vecWinResolution = resolution; }

			//static Maths::Vector2 m_vecWinResolution;
			static Maths::Vector2 m_vecMousePos;
			static std::vector<Key> m_vecKeys;

			static HWND m_hwnd;
		};
	}

	
	using INPUT = Manager::CInputManager;
//#define INPUT CInputManager


}


