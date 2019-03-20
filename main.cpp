#include <windows.h>
#define ID_CLOSE 1
#define ID_NEW 2

LONG WINAPI WndProc(HWND, UINT, WPARAM,LPARAM);
HINSTANCE hInstance;
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine,
                   int       nCmdShow)
{
    int x = 500;
    int y = 400;
    HWND hwnd;
    MSG msg;
    WNDCLASS w;
    memset(&w,0,sizeof(WNDCLASS));
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.lpfnWndProc = WndProc;
    w.hInstance = hInstance;
    w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    w.lpszClassName = "My Class";
    RegisterClass(&w);
    hwnd = CreateWindow("My Class", "My title", WS_OVERLAPPEDWINDOW, 300, 200, x, y, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd,nCmdShow);
    UpdateWindow(hwnd);
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LONG WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam)
{
    static HWND hEdit;
    static HWND hEdit1;
    static HWND hButtNew;
    static HWND hButtClose;
    switch (Message){
    case WM_CREATE:
        hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | ES_MULTILINE, 40, 40, 400, 300, hwnd, (HMENU)10000, hInstance, NULL);
        hButtClose = CreateWindow("button", "Close", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 0, 40, 20, hwnd, (HMENU)1, hInstance, NULL);
        hButtNew = CreateWindow("button", "New", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 70, 0, 40, 20, hwnd, (HMENU)2, hInstance, NULL);
        return 0;
    case WM_COMMAND:
		switch (wparam)
		{
        case ID_CLOSE:
            DestroyWindow(hEdit1);
            break;

        case ID_NEW:
            hEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL, 40, 40, 400, 50, hwnd, (HMENU)10000, hInstance, NULL);
            ShowWindow(hEdit1, SW_NORMAL);
            UpdateWindow(hEdit1);
            break;
        }
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, Message, wparam, lparam);
    }
    return 0;
}

