// RegistryKeyClass.h

#pragma once

#include <windows.h>

#include "Ascii.h"
#include "Common.h"

#define REGISTRY_KEY_LEFT_VALUE_NAME											"left"
#define REGISTRY_KEY_TOP_VALUE_NAME												"top"
#define REGISTRY_KEY_WIDTH_VALUE_NAME											"width"
#define REGISTRY_KEY_HEIGHT_VALUE_NAME											"height"

class RegistryKey
{
public:
	RegistryKey();
	~RegistryKey();

	RegistryKey& operator = ( HKEY hKey );

	BOOL operator == ( HKEY hKey );

	BOOL operator != ( HKEY hKey );

	operator HKEY();

	BOOL Close();

	BOOL Create( HKEY hKeyTopLevel, LPCTSTR lpszSubKey );

	DWORD GetValue( LPCTSTR lpszValueName, DWORD dwDefaultValue );

	BOOL Open( HKEY hKeyTopLevel, LPCTSTR lpszSubKey );

	BOOL SetValue( LPCTSTR lpszValueName, DWORD dwValue );

	BOOL StoreWindowPosition( HWND hWnd );

protected:
	HKEY m_hKey;

}; // End of class RegistryKey
