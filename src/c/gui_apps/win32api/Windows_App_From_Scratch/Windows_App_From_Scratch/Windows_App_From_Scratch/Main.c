#include <windows.h>
#include <shellscalingapi.h>
#include <commdlg.h>  // For GetOpenFileName

#define MENU_EDIT_UNDO_ACTION_ID 2
#define MENU_EDIT_REDO_ACTION_ID 3
#define MENU_BEEP_ACTION_ID 1

#define MY_TEXTBOX_ID 105

#define ID_FILE_SELECT 12345

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
    AppendMenu(myHEditMenu, MF_STRING, ID_FILE_SELECT, L"Создать");

    AppendMenu(myHMenu, MF_POPUP, myHEditMenu, L"Правка");

    SetMenu(hWnd, myHMenu);
}

HWND hEdit;

void DrawUI(HWND hWnd) {
    
    //UINT dpi = GetDpiForWindow(hWnd);

    //int x = ScaleByDPI(10, dpi);
    //int y = ScaleByDPI(10, dpi);
    //int w = ScaleByDPI(200, dpi);
    //int h = ScaleByDPI(20, dpi);

    //hEdit = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
    //    x, y, w, h, hWnd, MY_TEXTBOX_ID, NULL, NULL);
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
        DrawUI(hWnd);
        break;
    case WM_COMMAND:

        // 8. Process nessage if Beep sound
        switch (wParam) {
        case MENU_BEEP_ACTION_ID:
            MessageBeep(MB_OK);
            break;
        }

        if (LOWORD(wParam) == MY_TEXTBOX_ID && HIWORD(wParam) == EN_CHANGE) {
            char buffer[256];
            GetWindowText(hEdit, buffer, sizeof(buffer));
            SetWindowText(hWnd, buffer);  // Set window title to textbox content
        }

        if (LOWORD(wParam) == ID_FILE_SELECT) {
            // Button clicked - open file dialog
            char filePath[123] = "";

            OPENFILENAME ofn = { 0 };
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFile = filePath;
            ofn.nMaxFile = MAX_PATH;
            ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.txt\0";
            ofn.nFilterIndex = 1;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetOpenFileName(&ofn)) {
                MessageBoxA(hWnd, ofn.lpstrFile, "Selected File", MB_OK);
            }
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
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

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