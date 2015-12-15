
/*
    Author:     Tu Vu
    Professor:  Gerald Doutt
    Class:      CS431
*/
#include "Prgm3.h"

// Global Function Declarations
LRESULT CALLBACK  WndProc(HWND, UINT, WPARAM, LPARAM);
void startPainting();

// Main program code
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR szCmdLine, int iCmdShow)
{
    static TCHAR  szAppName[] = TEXT("Blue Blizzard");
    WNDCLASSEX    wndclass;
    HWND          hWindow;
    MSG           msg;

    // Create the window class for the main window
    wndclass.cbSize = sizeof(wndclass);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GEAR));
    wndclass.hIconSm = NULL;
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    // Register the window class
    if (!RegisterClassEx(&wndclass))
        return 0;

    // Create the window
    hWindow = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);

    // Show and update the window
    ShowWindow(hWindow, iCmdShow);
    UpdateWindow(hWindow);

    // Enter the main message loop
    while (GetMessage(&msg, NULL, 0, 0))
    {
        // Process the message
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static int cxClient, cyClient;
    HDC         hdc;
    PAINTSTRUCT ps;
    // RECT { LONG left; LONG top; LONG right; LONG bottom;}
    RECT smallrect = { 150, 150, 550, 350 };
    RECT bigrect = { 100, 100, 600, 400 };
    HPEN hredpen, hbluepen, hgreenpen;
    HBRUSH hYellowBrush, hVerticalBrush, hGreenBrush;

    TCHAR szBuffer[50];
    static int iLength;

    switch (msg)
    {
    case WM_CREATE:
        PlaySound(TEXT("CHIMES.WAV"), NULL, SND_FILENAME | SND_ASYNC);
        return 0;

    case WM_PAINT:
        // Update window display
        hdc = BeginPaint(hWindow, &ps);

        hbluepen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
        hredpen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
        hgreenpen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
        hYellowBrush = CreateSolidBrush(RGB(255, 255, 0));
        hGreenBrush = CreateSolidBrush(RGB(0, 204,0));
        hVerticalBrush = CreateHatchBrush(HS_VERTICAL, RGB(0, 150, 150));

        FillRect(hdc, &bigrect, hGreenBrush);
        FillRect(hdc, &smallrect, hVerticalBrush);

        SetBkColor(hdc, RGB(204, 255, 204));

        SelectObject(hdc, hbluepen);
        iLength = wsprintf(szBuffer, TEXT("What is this?"));
        TextOut(hdc, 250, 250, szBuffer, iLength);

        SelectObject(hdc, hbluepen);
        iLength = wsprintf(szBuffer, TEXT("A window, of course"));
        TextOut(hdc, 320, 310, szBuffer, iLength);

        ReleaseDC(hWindow, hdc);

        DeleteObject(hYellowBrush);
        DeleteObject(hGreenBrush);
        DeleteObject(hVerticalBrush);
        DeleteObject(hbluepen);
        DeleteObject(hredpen);
        DeleteObject(hgreenpen);

        EndPaint(hWindow, &ps);
        return 0;

    case WM_DESTROY:
        // Exit the application
        PlaySound(TEXT("APPLAUSE.WAV"), NULL, SND_FILENAME | SND_ASYNC);
        MessageBox(NULL, TEXT("Thanks for using the program. Bye!"), TEXT("Good Bye"), MB_ICONEXCLAMATION);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWindow, msg, wParam, lParam);
}
