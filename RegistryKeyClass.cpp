// RegistryKeyClass.cpp

#include "RegistryKeyClass.h"

RegistryKey::RegistryKey()
{
	// Initialise member variables
	::ZeroMemory( &m_hKey, sizeof( m_hKey ) );

} // End of function RegistryKey::RegistryKey

RegistryKey::~RegistryKey()
{
	// Clear member variables
	::ZeroMemory( &m_hKey, sizeof( m_hKey ) );

} // End of function RegistryKey::~RegistryKey

RegistryKey& RegistryKey::operator = ( HKEY hKey )
{
	// Update member variables
	m_hKey = hKey;

	return *this;

} // End of function RegistryKey::operator =

BOOL RegistryKey::operator == ( HKEY hKey )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( hKey == m_hKey )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function RegistryKey::operator ==

BOOL RegistryKey::operator != ( HKEY hKey )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( hKey != m_hKey )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function RegistryKey::operator !=

RegistryKey::operator HKEY()
{
	return m_hKey;

} // End of function RegistryKey::operator HKEY()

BOOL RegistryKey::Close()
{
	BOOL bResult = FALSE;

	// Close registry key
	if( RegCloseKey( m_hKey ) == ERROR_SUCCESS )
	{
		// Successfully closed registry key

		// Update return value
		bResult = TRUE;

	} // End of successfully closed registry key

	return bResult;

} // End of function RegistryKey::Close

BOOL RegistryKey::Create( HKEY hKeyTopLevel, LPCTSTR lpszSubKey )
{
	BOOL bResult = FALSE;

	// Create registry key
	if( RegCreateKeyEx( hKeyTopLevel, lpszSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &m_hKey, NULL ) == ERROR_SUCCESS )
	{
		// Successfully created registry key

		// Update return value
		bResult = TRUE;

	} // End of successfully created registry key

	return bResult;

} // End of function RegistryKey::Create

DWORD RegistryKey::GetValue( LPCTSTR lpszValueName, DWORD dwDefaultValue )
{
	DWORD dwResult;

	DWORD dwType = REG_DWORD;
	DWORD dwSize = sizeof( DWORD );

	// Get registry value
	if( RegQueryValueEx( m_hKey, lpszValueName, 0, &dwType, ( LPBYTE )&dwResult, &dwSize ) != ERROR_SUCCESS )
	{
		// Unable to get registry value

		// Use default value
		dwResult = dwDefaultValue;

	} // End of unable to get registry value

	return dwResult;

} // End of function RegistryKey::GetValue

BOOL RegistryKey::Open( HKEY hKeyTopLevel, LPCTSTR lpszSubKey )
{
	BOOL bResult = FALSE;

	// Open registry key
	if( RegOpenKeyEx( hKeyTopLevel, lpszSubKey, 0, KEY_READ, &m_hKey ) == ERROR_SUCCESS )
	{
		// Successfully opened registry key

		// Update return value
		bResult = TRUE;

	} // End of successfully opened registry key
	return bResult;

} // End of function RegistryKey::Open

BOOL RegistryKey::SetValue( LPCTSTR lpszValueName, DWORD dwValue )
{
	BOOL bResult = FALSE;

	DWORD dwSize = sizeof( DWORD );

	// Set registry value
	if( RegSetValueEx( m_hKey, lpszValueName, 0, REG_DWORD, ( LPBYTE )&dwValue, dwSize ) == ERROR_SUCCESS )
	{
		// Successfully set registry value

		// Update return value
		bResult = TRUE;

	} // End of successfully set registry value

	return bResult;

} // End of function RegistryKey::SetValue

BOOL RegistryKey::StoreWindowPosition( HWND hWnd )
{
	BOOL bResult = FALSE;

	RECT rcWindow;

	// Get window rect
	if( GetWindowRect( hWnd, &rcWindow ) )
	{
		// Successfully got window rect
		DWORD dwWindowWidth;
		DWORD dwWindowHeight;

		// Store window size
		dwWindowWidth	= ( rcWindow.right - rcWindow.left );
		dwWindowHeight	= ( rcWindow.bottom - rcWindow.top );

		// Write window position to registry
		bResult = SetValue( REGISTRY_KEY_LEFT_VALUE_NAME,	rcWindow.left );
		bResult &= SetValue( REGISTRY_KEY_TOP_VALUE_NAME,		rcWindow.top );
		bResult &= SetValue( REGISTRY_KEY_WIDTH_VALUE_NAME,	dwWindowWidth );
		bResult &= SetValue( REGISTRY_KEY_HEIGHT_VALUE_NAME,	dwWindowHeight );

	} // End of successfully got window rect

	return bResult;

} // End of function RegistryKey::StoreWindowPosition

/*
RegistryKey::
{
} // End of function RegistryKey::
*/
