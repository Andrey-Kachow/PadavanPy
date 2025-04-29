#include <windows.h>

// 1. Basic signature
// int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lparam) {

}

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
) {
    // 2. Dialog
	MessageBox(NULL, L"Welcome to my app", L"Hello", MB_OK);

    WNDCLASSW windowClass = {0};
    //
    windowClass.hbrBackground = COLOR_WINDOW;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = L"myAmazingWindowClass";
    windowClass.lpfnWndProc = WindowProcedure;

    if (!RegisterClassW(&windowClass)) {

    }

	return 0;
}