#include <windows.h>

#define MENU_EDIT_UNDO_ACTION_ID 2
#define MENU_EDIT_REDO_ACTION_ID 3
#define MENU_BEEP_ACTION_ID 1

const LPCWSTR MY_WINDOW_CLASS = L"myAmazingWindowClass";

HMENU myHMenu;

// 7. Menus:
void AddMenus(HWND hWnd) {
    myHMenu = CreateMenu();

    AppendMenu(myHMenu, MF_STRING, MENU_BEEP_ACTION_ID, L"Файл");
    AppendMenu(myHMenu, MF_STRING, NULL, L"Помощь");

    // 9. Menu with extra options
    HMENU myHEditMenu = CreateMenu();
    AppendMenu(myHEditMenu, MF_STRING, MENU_EDIT_UNDO_ACTION_ID, L"Отменить");
    AppendMenu(myHEditMenu, MF_STRING, MENU_EDIT_REDO_ACTION_ID, L"Применить");

    // 10. Separator
    AppendMenu(myHEditMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(myHEditMenu, MF_STRING, NULL, L"Создать");

    AppendMenu(myHMenu, MF_POPUP, myHEditMenu, L"Правка");

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
    case WM_COMMAND:

        // 8. Process nessage if Beep sound
        switch (wParam) {
        case MENU_BEEP_ACTION_ID:
            MessageBeep(MB_OK);
            break;
        }

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
	int welcomeDialogResult = MessageBox(NULL, L"Добро Пожаловать!", L"Привет", MB_OKCANCEL);
    // 2.5 dialog actions response
    if (welcomeDialogResult == IDOK) {
        MessageBox(NULL, L"Вы нажали ОК!", L"Уведомление", MB_OK);
    }
    else if (welcomeDialogResult == IDCANCEL) {
        MessageBox(NULL, L"Вы нажали Отмена", L"Уведомление", MB_OK);
    }

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