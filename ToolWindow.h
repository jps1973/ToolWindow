// ToolWindow.h

#pragma once

#include "Ascii.h"
#include "Common.h"

#include "Resource.h"

#define MAIN_WINDOW_CLASS_NAME													"Main ToolWindow Window Class"

#define MAIN_WINDOW_CLASS_STYLE													0
#define MAIN_WINDOW_CLASS_ICON_NAME												IDI_APPLICATION
#define MAIN_WINDOW_CLASS_ICON													LoadIcon( NULL, MAIN_WINDOW_CLASS_ICON_NAME )
#define MAIN_WINDOW_CLASS_CURSOR												LoadCursor( NULL, IDC_ARROW )
#define MAIN_WINDOW_CLASS_BACKGROUND											( HBRUSH )( COLOR_WINDOW + 1 )
#define MAIN_WINDOW_CLASS_ICON_SMALL											LoadIcon( NULL, MAIN_WINDOW_CLASS_ICON_NAME )

#define MAIN_WINDOW_EXTENDED_STYLE												( WS_EX_TOOLWINDOW | WS_EX_TOPMOST )
#define MAIN_WINDOW_STYLE														( WS_OVERLAPPEDWINDOW | WS_BORDER )
#define MAIN_WINDOW_TEXT														"ToolWindow"

#define MAIN_WINDOW_MINIMUM_WIDTH												320
#define MAIN_WINDOW_MINIMUM_HEIGHT												200

#define ABOUT_MESSAGE_TEXT														"ToolWindow\r\n"					\
																				"\r\n"								\
																				"Written by Jim Smith\r\n"			\
																				"\r\n"								\
																				"August 2025"

#define UNABLE_TO_REGISTER_MAIN_WINDOW_CLASS_ERROR_MESSAGE						"Unable to Register Main Window Class"
#define UNABLE_TO_CREATE_MAIN_WINDOW_ERROR_MESSAGE								"Unable to Create Main Window"
