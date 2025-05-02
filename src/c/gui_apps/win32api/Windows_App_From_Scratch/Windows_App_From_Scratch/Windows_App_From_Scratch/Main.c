#include <windows.h>

const LPCWSTR MY_WINDOW_CLASS = L"myAmazingWindowClass";

HMENU myHMenu;

// 7. Menus:
void AddMenus(HWND hWnd) {
    myHMenu = CreateMenu();

    AppendMenu(myHMenu, MF_STRING, NULL, L"Файл");

    SetMenu(hWnd, myHMenu);
}

// 1. Basic signature
// int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {}

// 3.2. - Window procedure signature:
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lparam) {
    
    // 6. Processing messages in switch
    switch (message) {
        // (7
    case WM_CREATE:
        AddMenus(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0); // makes GetMessage return false;
        break;
    default:
        return DefWindowProcW(hWnd, message, wParam, lparam);
    }
}

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
) {
    // 2. Dialog
	//MessageBox(NULL, L"Добро Пожаловать!", L"Привет", MB_OK);

    // 3.1 Widnow Class
    WNDCLASSW windowClass = { 0 };
    //
    windowClass.hbrBackground = COLOR_WINDOW;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = MY_WINDOW_CLASS;
    windowClass.lpfnWndProc = WindowProcedure;
    //
    if (!RegisterClassW(&windowClass)) {
        return -1;
    }
    
    // 4. Creating a window
    CreateWindow(MY_WINDOW_CLASS, L"Добро Пожаловать в мое Окно", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);

    // 5. Message Loop (otherwise exits immediately)
    MSG message = { 0 };
    while (GetMessage(&message, NULL, NULL, NULL)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

	return 0;
}