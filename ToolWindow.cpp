// ToolWindow.cpp

#include "ToolWindow.h"

LRESULT CALLBACK MainWindowProcedure( HWND hWndMain, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	LRESULT lr = 0;

	// Select message
	switch( uMessage )
	{
		case WM_CREATE:
		{
			// A create message
			HINSTANCE hInstance;

			// Get instance handle
			hInstance = ( ( ( LPCREATESTRUCT )lParam )->hInstance );

			// Create control window
			if( ControlWindowCreate( hWndMain, hInstance ) )
			{
				// Successfully created control window
			} // End of successfully created control window

			// Break out of switch
			break;

		} // End of a create message
		case WM_ACTIVATE:
		{
			// An activate message

			// Focus on control window
			ControlWindowSetFocus();

			// Break out of switch
			break;

		} // End of an activate message
		case WM_SIZE:
		{
			// A size message
			RegistryKey registryKey;
			DWORD dwClientWidth;
			DWORD dwClientHeight;

			// Store client size
			dwClientWidth	= LOWORD( lParam );
			dwClientHeight	= HIWORD( lParam );

			// Move control window to fit client
			ControlWindowMove( 0, 0, dwClientWidth, dwClientHeight, TRUE );

			// Create registry key
			if( registryKey.Create( REGISTRY_KEY, REGISTRY_SUB_KEY ) )
			{
				// Successfully created registry key

				// Store window position
				registryKey.StoreWindowPosition( hWndMain );

				// Close registry key
				registryKey.Close();

			} // End of successfully created registry key

			// Break out of switch
			break;

		} // End of a size message
		case WM_MOVE:
		{
			// A move message
			RegistryKey registryKey;

			// Create registry key
			if( registryKey.Create( REGISTRY_KEY, REGISTRY_SUB_KEY ) )
			{
				// Successfully created registry key

				// Store window position
				registryKey.StoreWindowPosition( hWndMain );

				// Close registry key
				registryKey.Close();

			} // End of successfully created registry key

			// Break out of switch
			break;

		} // End of a move message
		case WM_GETMINMAXINFO:
		{
			// A get min max info message
			MINMAXINFO FAR *lpMinMaxInfo;

			// Get min max info structure
			lpMinMaxInfo = ( MINMAXINFO FAR * )lParam;

			// Update min max info structure
			lpMinMaxInfo->ptMinTrackSize.x = MAIN_WINDOW_MINIMUM_WIDTH;
			lpMinMaxInfo->ptMinTrackSize.y = MAIN_WINDOW_MINIMUM_HEIGHT;

			// Break out of switch
			break;

		} // End of a get min max info message
		case WM_COMMAND:
		{
			// A command message

			// Select command
			switch( LOWORD( wParam ) )
			{
				case IDM_HELP_ABOUT:
				{
					// A help about command

					// Show about message
					MessageBox( hWndMain, ABOUT_MESSAGE_TEXT, ABOUT_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );

					// Break out of switch
					break;

				} // End of a help about command
				default:
				{
					// Default command

					// See if command message is from control window
					if( IsControlWindow( ( HWND )lParam ) )
					{
						// Command message is from control window

						// Handle command message from control window
						if( !( ControlWindowHandleCommandMessage( wParam, lParam ) ) )
						{
							// Command message was not handled from control window

							// Call default procedure
							lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

						} // End of command message was not handled from control window

					} // End of command message is from control window
					else
					{
						// Command message is not from control window

						// Call default procedure
						lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

					} // End of command message is not from control window

					// Break out of switch
					break;

				} // End of default command

			}; // End of selection for command

			// Break out of switch
			break;

		} // End of a command message
		case WM_NOTIFY:
		{
			// A notify message
			LPNMHDR lpNmHdr;

			// Get notify message handler
			lpNmHdr = ( LPNMHDR )lParam;

			// See if notify message is from control window
			if( IsControlWindow( lpNmHdr->hwndFrom ) )
			{
				// Notify message is from control window

				// Handle notify message from control window
				if( !( ControlWindowHandleNotifyMessage( wParam, lParam ) ) )
				{
					// Notify message was not handled from control window

					// Call default procedure
					lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

				} // End of notify message was not handled from control window

			} // End of notify message is from control window
			else
			{
				// Notify message is not from control window

				// Call default procedure
				lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

			} // End of notify message is not from control window


			// Break out of switch
			break;

		} // End of a notify message
		case WM_CONTEXTMENU:
		{
			// A context menu message
			HMENU hMenu;

			// Load context menu
			hMenu = LoadMenu( NULL, MAKEINTRESOURCE( IDR_CONTEXT_MENU ) );

			// Show context menu
			TrackPopupMenu( GetSubMenu( hMenu, 0 ), ( TPM_LEFTALIGN | TPM_LEFTBUTTON ), LOWORD( lParam ), HIWORD( lParam ), 0, hWndMain, NULL );

			// Break out of switch
			break;

		} // End of a context menu message
		case WM_CLOSE:
		{
			// A close message

			// Destroy main window
			DestroyWindow( hWndMain );

			// Break out of switch
			break;

		} // End of a close message
		case WM_DESTROY:
		{
			// A destroy message

			// Terminate thread
			PostQuitMessage( 0 );

			// Break out of switch
			break;

		} // End of a destroy message
		default:
		{
			// Default message

			// Call default window procedure
			lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

			// Break out of switch
			break;

		} // End of default message

	}; // End of selection for message

	return lr;

} // End of function MainWindowProcedure

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow )
{
	MSG msg;

	HWND hWndExisting;

	// Attempt to find existing instance of window
	hWndExisting = FindWindow( MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_TEXT );

	// See if existing instance of window was found
	if( hWndExisting )
	{
		// Successfully found existing instance of window

		// Activate existing instance of window
		SetForegroundWindow( hWndExisting );

	} // End of successfully found existing instance of window
	else
	{
		// Unable to find existing instance of window

		// Clear message structure
		ZeroMemory( &msg, sizeof( msg ) );

		WNDCLASSEX wcMain;

		// Clear main window class structure structure
		ZeroMemory( &wcMain, sizeof( wcMain ) );

		// Initialise main window class structure structure
		wcMain.cbSize			= sizeof( WNDCLASSEX );
		wcMain.lpfnWndProc		= MainWindowProcedure;
		wcMain.hInstance		= hInstance;
		wcMain.style			= MAIN_WINDOW_CLASS_STYLE;
		wcMain.hIcon			= MAIN_WINDOW_CLASS_ICON;
		wcMain.hCursor			= MAIN_WINDOW_CLASS_CURSOR;
		wcMain.hbrBackground	= MAIN_WINDOW_CLASS_BACKGROUND;
		wcMain.lpszClassName	= MAIN_WINDOW_CLASS_NAME;
		wcMain.hIconSm			= MAIN_WINDOW_CLASS_ICON;

		// Register main window class
		if( RegisterClassEx( &wcMain ) )
		{
			// Successfully registered main window class
			HWND hWndMain;
			DWORD dwWindowLeft;
			DWORD dwWindowTop;
			DWORD dwWindowWidth;
			DWORD dwWindowHeight;
			RegistryKey registryKey;

			// Open registry key
			if( registryKey.Open( REGISTRY_KEY, REGISTRY_SUB_KEY ) )
			{
				// Successfully opened registry key

				// Get window position
				dwWindowLeft	= registryKey.GetValue( REGISTRY_KEY_LEFT_VALUE_NAME,	CW_USEDEFAULT );
				dwWindowTop		= registryKey.GetValue( REGISTRY_KEY_TOP_VALUE_NAME,	CW_USEDEFAULT );
				dwWindowWidth	= registryKey.GetValue( REGISTRY_KEY_WIDTH_VALUE_NAME,	CW_USEDEFAULT );
				dwWindowHeight	= registryKey.GetValue( REGISTRY_KEY_HEIGHT_VALUE_NAME,	CW_USEDEFAULT );

				// Close registry key
				registryKey.Close();

			} // End of successfully opened registry key
			else
			{
				// Unable to open registry key

				// Use default window positions
				dwWindowLeft	= CW_USEDEFAULT;
				dwWindowTop		= CW_USEDEFAULT;
				dwWindowWidth	= CW_USEDEFAULT;
				dwWindowHeight	= CW_USEDEFAULT;

			} // End of unable to open registry key

			// Create main window
			hWndMain = CreateWindowEx( MAIN_WINDOW_EXTENDED_STYLE, MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_TEXT, MAIN_WINDOW_STYLE, dwWindowLeft, dwWindowTop, dwWindowWidth, dwWindowHeight, NULL, NULL, hInstance, NULL );

			// Ensure that main window was created
			if( hWndMain )
			{
				// Successfully created main window

				// Show main window
				ShowWindow( hWndMain, nCmdShow );

				// Update main window
				UpdateWindow( hWndMain );

				// Message loop
				while( GetMessage( &msg, NULL, 0, 0 ) > 0 )
				{
					// Translate message
					TranslateMessage( &msg );

					// Dispatch message
					DispatchMessage( &msg );

				}; // End of message loop

			} // End of successfully created main window
			else
			{
				// Unable to create main window

				// Display error message
				MessageBox( NULL, UNABLE_TO_CREATE_MAIN_WINDOW_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

			} // End of unable to create main window

		} // End of successfully registered main window class
		else
		{
			// Unable to register main window class

			// Display error message
			MessageBox( NULL, UNABLE_TO_REGISTER_MAIN_WINDOW_CLASS_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

		} // End of unable to register main window class

	} // End of unable to find existing instance of window

	return msg.wParam;

} // End of function WinMain
