// Window_Engine_Framework.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Window_Engine_Framework.h"

#include "..\\WindowEngine_SOURCE\\CApplication.h"
#include "..\\WindowEngine\\LoadScene.h"

#pragma comment (lib,"..\\x64\\Debug\\WindowEngine.lib" )

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

Framework::CApplication application;

ULONG_PTR g_pToken;
Gdiplus::GdiplusStartupInput gpsi;
bool processState;  // 게임 진행 중이면 true 종료면 false
bool scaleMaximum;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#pragma region  Window_Process_Init
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);         //메모리 누수 체크
    setlocale(LC_ALL, "Korean");                                    //지역 설정

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWENGINEFRAMEWORK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

#pragma endregion Window_Process_Init

    //app.Test();
    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))    {   return FALSE;   }

    // TODO: 여기에 코드를 입력합니다.

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWENGINEFRAMEWORK));
    MSG msg;
    processState = true;
    while (processState)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))// 단축키 처리 하지만, 단축키가 아닐 경우
            {
                TranslateMessage(&msg); // 입력 메시지 번역
                DispatchMessage(&msg); // 입력 메시지 처리, WinProc에서 전달된 메시지 처리
            }
        }
        else
        {
            application.Run();
        }
    }
    Gdiplus::GdiplusShutdown(g_pToken);

    return (int) msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWENGINEFRAMEWORK));
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;//MAKEINTRESOURCEW(IDC_WINDOWENGINEFRAMEWORK);
    wcex.lpszClassName  = szWindowClass;

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   DWORD myStyle = WS_OVERLAPPED
       | WS_CAPTION
       | WS_SYSMENU
       | WS_THICKFRAME
       | WS_MINIMIZEBOX
       //|WS_MAXIMIZEBOX
       ;

   int screenScaleX = GetSystemMetrics(SM_CXSCREEN);
   int screenScaleY = GetSystemMetrics(SM_CYSCREEN);

   HWND hWnd = CreateWindowW(
       szWindowClass,
       szTitle,
       myStyle,

       0, 
       0,               //Start Pos Y //CW_DEFAULT

       0,   //Size X
       0,   //Size Y

       nullptr,
       nullptr,
       hInstance,
       nullptr);

   scaleMaximum = false;

   if (!hWnd)   {    return FALSE;   }
   Gdiplus::GdiplusStartup(&g_pToken, &gpsi, NULL);

   Framework::LoadScenes();

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   application.Initialize(
       hWnd, 
       WINSIZEX , WINSIZEY, 
       (screenScaleX - WINSIZEX) >> 1,
       (screenScaleY - WINSIZEY) >> 1,
       myStyle, false
   );

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                processState = false;
                break;
            case ID_CHANGESCALE:
            {
                scaleMaximum = !scaleMaximum;
                application.ChangeScreenSize(scaleMaximum);
            }
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
   
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_CLOSE:
        DestroyWindow(hWnd);
        processState = false;
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
