#include <stdio.h>
#include <windows.h>


void getWindow()
{
	LPSTR window_title = calloc(1024, sizeof(LPSTR));
	// get a handle of currently active window
	HWND hwnd = GetForegroundWindow(); 

	// GetWindowTextA needs @window_title to not be null. If we perform this check, we can 
	// know this to be true, and the warnings will go away :)
	if (NULL == window_title) {
		printf("window_title is NULL before going into GetWindowTextA(). That's not good.\n");
		exit(1);
	}
	int len = 0;
	// actually get the window title
	len = GetWindowTextA(hwnd, window_title, 1024);
	if (len < 1) {
		printf("failed to get window title\n");
		exit(2);
	}
	printf("Window title: %s\n", window_title);
}


/*
	This function rotates the screen.
*/
void rotateScreen()
{
	DEVMODE mode = { 0 };
	//first get setting for "current" screen
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &mode);

	if (mode.dmFields | DM_DISPLAYORIENTATION)
	{
		// choose a rotation setting. Options are:
		// #define DMDO_DEFAULT    0
		// #define DMDO_90         1
		// #define DMDO_180        2
		// #define DMDO_270        3
		mode.dmDisplayOrientation = DMDO_DEFAULT;
		LONG r;
		r = ChangeDisplaySettings(&mode, 0);
	}
}

/*
	This function changes the location at which the current screen exists using coordinates.
	Think of the following scenario:
	You have two monitors, extending the display for the second one. Running this function will take 
	the focused screen and move it's alignment relative to the other display.
*/
void changeScreenLocation()
{
	DEVMODE mode = { 0 };
	//first get setting for "current" screen
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &mode);

	if (mode.dmFields | DM_DISPLAYORIENTATION)
	{
		// pick a location for the screen to be moved to
		POINTL loc = { 3000, 1000 };
		mode.dmPosition = loc;
		LONG r;
		r = ChangeDisplaySettings(&mode, 0);
	}
}

int main(int argc, char* argv[])
{
	printf("Switch to the window you want the title for\n");
	Sleep(5000);
	getWindow();
	return 0;
}

