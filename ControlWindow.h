// ControlWindow.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#define CONTROL_WINDOW_CLASS_NAME												WC_LISTBOX

#define CONTROL_WINDOW_EXTENDED_STYLE											0
#define CONTROL_WINDOW_STYLE													( WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_BORDER | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY )
#define CONTROL_WINDOW_TEXT														NULL

BOOL IsControlWindow( HWND hWnd );

BOOL ControlWindowCreate( HWND hWndParent, HINSTANCE hInstance );

BOOL ControlWindowGetRect( LPRECT lpRect );

BOOL ControlWindowHandleCommandMessage( WPARAM wParam, LPARAM lParam );

BOOL ControlWindowHandleNotifyMessage( WPARAM wParam, LPARAM lParam );

BOOL ControlWindowMove( DWORD dwX, DWORD dwY, DWORD dwWidth, DWORD dwHeight, BOOL bRepaint = TRUE );

int ControlWindowLoad( LPCTSTR lpszFileName );

int ControlWindowSave( LPCTSTR lpszFileName );

HWND ControlWindowSetFocus();
