// ControlWindow.cpp

#include "ControlWindow.h"

// Global variables
static HWND g_hWndControl;

BOOL IsControlWindow( HWND hWnd )
{
	// See if supplied window is control window
	return( hWnd == g_hWndControl );

} // End of function IsControlWindow

BOOL ControlWindowCreate( HWND hWndParent, HINSTANCE hInstance )
{
	BOOL bResult = FALSE;

	// Create control window
	g_hWndControl = CreateWindowEx( CONTROL_WINDOW_EXTENDED_STYLE, CONTROL_WINDOW_CLASS_NAME, CONTROL_WINDOW_TEXT, CONTROL_WINDOW_STYLE, 0, 0, 0, 0, hWndParent, ( HMENU )NULL, hInstance, NULL );

	// Ensure that control window was created
	if( g_hWndControl )
	{
		// Successfully created control window
		HFONT hFont;

		// Get default gui font
		hFont = ( HFONT )GetStockObject( DEFAULT_GUI_FONT );

		// Set control window font
		SendMessage( g_hWndControl, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

		// Update return value
		bResult = TRUE;

	} // End of successfully created control window
	return bResult;

} // End of function ControlWindowCreate

BOOL ControlWindowGetRect( LPRECT lpRect )
{
	// Get control window rect
	return GetWindowRect( g_hWndControl, lpRect );

} // End of function ControlWindowGetRect

BOOL ControlWindowHandleCommandMessage( WPARAM wParam, LPARAM )
{
	BOOL bResult = FALSE;

	// Select control window notification code
	switch( HIWORD( wParam ) )
	{
		default:
		{
			// Default notification code

			// No need to do anything here, just continue with default result

			// Break out of switch
			break;

		} // End of default notification code

	}; // End of selection for control window notification code

	return bResult;

} // End of function ControlWindowHandleCommandMessage

BOOL ControlWindowHandleNotifyMessage( WPARAM, LPARAM lParam )
{
	BOOL bResult = FALSE;

	LPNMHDR lpNmhdr;

	// Get notify message handler
	lpNmhdr = ( ( LPNMHDR )lParam );

	// Select control window notification code
	switch( lpNmhdr->code )
	{
		default:
		{
			// Default notification code

			// No need to do anything here, just continue with default result

			// Break out of switch
			break;

		} // End of default notification code

	}; // End of selection for control window notification code

	return bResult;

} // End of function ControlWindowHandleNotifyMessage

BOOL ControlWindowMove( DWORD dwX, DWORD dwY, DWORD dwWidth, DWORD dwHeight, BOOL bRepaint )
{
	// Move control window
	return MoveWindow( g_hWndControl, dwX, dwY, dwWidth, dwHeight, bRepaint );

} // End of function ControlWindowMove

int ControlWindowLoad( LPCTSTR lpszFileName )
{
	int nResult = 0;

	HANDLE hFile;

	// Open file
	hFile = CreateFile( lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );

	// Ensure that file was opened
	if( hFile != INVALID_HANDLE_VALUE )
	{
		// Successfully opened file
		DWORD dwFileSize;

		// Get file size
		dwFileSize = GetFileSize( hFile, NULL );

		// Ensure that file size was got
		if( dwFileSize != INVALID_FILE_SIZE )
		{
			// Successfully got file size

			// Allocate string memory
			LPTSTR lpszFileText = new char[ dwFileSize + sizeof( char ) ];

			// Read file text
			if( ReadFile( hFile, lpszFileText, dwFileSize, NULL, NULL ) )
			{
				// Successfully read file text
				LPTSTR lpszLine;

				// Terminate file text
				lpszFileText[ dwFileSize ] = ( char )NULL;

				// Get first line in file text
				lpszLine = strtok( lpszFileText, NEW_LINE_TEXT );

				// Loop through all lines in file text
				while( lpszLine )
				{
					// Add line to control window
					if( SendMessage( g_hWndControl, LB_ADDSTRING, ( WPARAM )NULL, ( LPARAM )lpszLine ) >= 0 )
					{
						// Successfully added line to control window

						// Update return value
						nResult ++;

						// Get next line in file text
						lpszLine = strtok( NULL, NEW_LINE_TEXT );

					} // End of successfully added line to control window
					else
					{
						// Unable to add line to control window

						// Force exit from loop
						lpszLine = NULL;

					} // End of unable to add line to control window

				}; // End of loop through all lines in file text

			} // End of successfully read file text

			// Free string memory
			delete [] lpszFileText;

		} // End of successfully got file size

		// Close file
		CloseHandle( hFile );

	} // End of successfully opened file

	return nResult;

} // End of function ControlWindowLoad

int ControlWindowSave( LPCTSTR lpszFileName )
{
	int nResult = 0;

	HANDLE hFile;

	// Create file
	hFile = CreateFile( lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

	// Ensure that file was created
	if( hFile != INVALID_HANDLE_VALUE )
	{
		// Successfully created file
		int nItemCount;
		int nWhichItem;

		// Allocate string memory
		LPTSTR lpszItemText = new char[ STRING_LENGTH + sizeof( char ) ];

		// Count items on control window
		nItemCount = SendMessage( g_hWndControl, LB_GETCOUNT, ( WPARAM )NULL, ( LPARAM )NULL );

		// Loop through items on control window
		for( nWhichItem = 0; nWhichItem < nItemCount; nWhichItem ++ )
		{
			// Get item text
			if( SendMessage( g_hWndControl, LB_GETTEXT, ( WPARAM )nWhichItem, ( LPARAM )lpszItemText) != LB_ERR )
			{
				// Successfully got item text

				// Write item text to file
				if( WriteFile( hFile, lpszItemText, lstrlen( lpszItemText ), NULL, NULL ) )
				{
					// Successfully wrote item text to file

					// Write new line text to file
					WriteFile( hFile, NEW_LINE_TEXT, lstrlen( NEW_LINE_TEXT ), NULL, NULL );

					// Update return value
					nResult ++;

				} // End of successfully wrote item text to file
				else
				{
					// Unable to write item text to file

					// Force exit from loop
					nWhichItem = nItemCount;

				} // End of unable to write item text to file

			} // End of successfully got item text
			else
			{
				// Unable to get item text

				// Force exit from loop
				nWhichItem = nItemCount;

			} // End of unable to get item text

		}; // End of loop through items on control window

		// Free string memory
		delete [] lpszItemText;

		// Close file
		CloseHandle( hFile );

	} // End of successfully created file

	return nResult;

} // End of function ControlWindowSave

HWND ControlWindowSetFocus()
{
	// Focus on control window
	return SetFocus( g_hWndControl );

} // End of function ControlWindowSetFocus
