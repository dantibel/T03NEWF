/* File: t03newf.cpp
 * Coder: DB6
 * Last change date: 21.07.2022
 */
#include <windows.h>

#include "cmpl.h"
#include "frame.h"

// Window class name
#define WND_CLASS_NAME "My window class"

// Frame
frame Frm;

/* Dispatch window messsages function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 *   - number of message:
 *       UINT Message;
 *   - message param (word):
 *       WPARAM wParam;
 *   - message param (long): 
 *       LPARAM lParam;
 * RETURNS:
 *   (LRESULT) - in depend of messge.
 */
INT CALLBACK MyWindowFunc( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam );

/* Main program function.
 * ARGUMENTS:
 *  - handle of application:
 *      HINSTANCE hInstance;
 *  - handle of previous application:
 *    (doesnt use so must be NULL)
 *      HINSTANCE hPrevInstance;
 *  - command string
 *      CHAR *Cmdline;
 *  - window showing flag:
 *      INT ShowCmd;
 * RETURNS:
 *   (INT) code of return in to operation system 
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *Cmdline, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = (WNDPROC)MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }

  hWnd =
    CreateWindow(WND_CLASS_NAME,
    "DB6's window",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    Frm.W, Frm.H,
    NULL,
    NULL,
    hInstance,
    NULL);

  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return (INT)msg.wParam;
} /* End of 'WinMain' function */

/* Dispatch window messsages function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 *   - number of message:
 *       UINT Message;
 *   - message param (word):
 *       WPARAM wParam;
 *   - message param (long): 
 *       LPARAM lParam;
 * RETURNS:
 *   (LRESULT) - in depend of messge.
 */
INT CALLBACK MyWindowFunc( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  static HDC hMemDC;
  static HBITMAP hBm;
  MINMAXINFO *minmax;

  switch (Message)
  {
  case WM_GETMINMAXINFO:
    minmax = (MINMAXINFO *)lParam;
    minmax->ptMinTrackSize.x = minmax->ptMinTrackSize.y = 300;
    minmax->ptMaxTrackSize.y = GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYBORDER) * 2;
    return 0;

  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    SetTimer(hWnd, 47, 0, NULL);
    return 0;

  case WM_SIZE:
    //ScreenH = HIWORD(lParam);
    //ScreenW = LOWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    //Frm.Draw(hDC);
    Frm.Draw(hDC);
    ReleaseDC(hWnd, hDC);
    //SelectObject(hMemDC, hBm);
    return 0;

  case WM_TIMER:
    hDC = GetDC(hWnd);
    InvalidateRect(hWnd, NULL, false);
    ReleaseDC(hWnd, hDC);
    return 0;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, Frm.W, Frm.H, hMemDC, 0, 0, SRCCOPY);
    //StretchBlt(hDC, 0, 0, Frm.W, Frm.H, hMemDC, 0, 0, Frm.W, Frm.H, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;

  case WM_ERASEBKGND:
    return 0;

  case WM_KEYDOWN:
    switch (wParam)
    {
    case VK_ESCAPE:
      DestroyWindow(hWnd);
    case 'S':
      Frm.Save();
      break;
    }
    return 0;

  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 47);
    PostQuitMessage(47);
    return 0;
  }
  return (int)DefWindowProc(hWnd, Message, wParam, lParam);
} /* End of 'MyWindowFunc' function */

/* END OF 't03newf.cpp' FILE */
