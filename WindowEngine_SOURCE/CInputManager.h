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
			DECLARE_SINGLE(CInputManager)
			RELEASE_SINGLE
		public:
			__forceinline bool GetKeyDown(eKeyCode key) { return m_vecKeys[static_cast<UINT>(key)].state == eKeyState::Down; }
			__forceinline bool GetKeyUp(eKeyCode key) { return m_vecKeys[static_cast<UINT>(key)].state == eKeyState::Up; }
			__forceinline bool GetKeyPressed(eKeyCode key) { return m_vecKeys[static_cast<UINT>(key)].state == eKeyState::Pressed; }
			__forceinline const Maths::Vector2& GetMousePosition() { return m_vecMousePos; }

			friend class CApplication;
			friend CRenderManager;
		private:
			struct Key
			{
				eKeyCode	keyCode;
				eKeyState	state;
				bool		bPressed;
			};

			//CInputManager();
			~CInputManager();

			void Initialize(HWND hwnd);
			void Tick();
			void Render(HDC hdc, int posX, int posY);

			bool IsKeyDown(eKeyCode key);
			void UpdateKeyDown(Key& key);
			void UpdateKeyUp(Key& key);
			void UpdateCursorPosition();

			void UpdateKey();
			void ClearKey();

			void Release(){}
			//void SetResolution(const Maths::Vector2& resolution) { m_vecWinResolution = resolution; }

			//Maths::Vector2 m_vecWinResolution;
			Maths::Vector2 m_vecMousePos	= {};
			std::vector<Key> m_vecKeys		= {};

			HWND m_hwnd						= {};
		};
	}

	
	using INPUT = Manager::CInputManager;
//#define INPUT CInputManager


}


