//we include header files you dont have to use any OTHER Files but its cleaner
#include "globals.h"

//the location of the settings file
char szSettingsFile[MAX_PATH] = {};

//the console call back it will fire when an event happens AKA closing the console
#ifdef DEBUG_CONSOLE
BOOL WINAPI ConsoleHandle(DWORD CtrlType)
{
	if (CtrlType == CTRL_CLOSE_EVENT)
	{
		return TRUE;
	}
	return FALSE;
}
#endif

//
// This is the MAIN entry point this is what your application will run before anything else
//
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//
	// hInstance - the current application address space
	// hPrevInstance - the prev application address space
	// lpCmdLine - the command line that is passed IF passed
	// nShowCmd - the show command this is normally SW_SHOWNORMAL meaning user clicked on the EXE
	//
	//UNREFERENCED_PARAMETER - allows you to tell C++ you WILL NOT USE this parameter you dont need to use it, but if you use it it causes your app NOT to compile unneeded code
	//
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef DEBUG_CONSOLE
	//creates a new console for this app
	AllocConsole();

	//this tells the app to redirect ANY writes AKA printf to the console
	freopen("CONOUT$", "w", stdout);

	//set a console callback
	SetConsoleCtrlHandler(ConsoleHandle, TRUE);

	//print some debug data
	printf("DMA toolbox loaded\n\n");
#endif
	//get the settings file
	GetCurrentDirectoryA(MAX_PATH, szSettingsFile);
	strcat(szSettingsFile, "//Settings.ini");

	//this "CreateDialogParamA" will create a dialog from a resource file AKA IDD_MAIN_DIALOG and sets a callback function to the dialog
	HWND hDlgBox = CreateDialogParamA(hInstance, MAKEINTRESOURCEA(IDD_SERIAL_DIALOG), NULL, Serial_Dialog_Callback, NULL);
	if (hDlgBox == 0)
	{
		MessageBox(0, L"Failed to create dialog box\n", 0, 0);
		return 0;
	}
	//we tell the dialog that we want to show it
	ShowWindow(hDlgBox, SW_SHOWNORMAL);

	//we tell "windows" to update the dialog
	UpdateWindow(hDlgBox);

#ifdef DEBUG_CONSOLE
	//more debug data
	printf("Toolbox loaded!\n");
#endif

	//declare a variable
	MSG msg = { 0 };

	//make a loop till you get the quit message
	while (msg.message != WM_QUIT)
	{
		//peek message checks if there are any message AKA things that have happen on the dialog
		while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE) > 0)
		{
			//check if this message is a dialog message if this is NOT a dialog message then translate it and send it to the callback function
			if (!IsDialogMessage(hDlgBox, &msg))
			{
				//translate message before sending it to the dialog
				TranslateMessage(&msg);

				//send it to the dialog callback function
				DispatchMessage(&msg);
			}

			//check if the message is quitting
			if (msg.message == WM_QUIT)
			{
				//break the loop when you get the quit message then it will do an if statement and break the endless loop!
				break;
			}
		}
	}

	//destroy the window FULLY! you dont need to because the quit message will do it but LETS make sure destory is called for clean up?
	DestroyWindow(hDlgBox);

	//set it to NULL so we dont get wrong value when making a new dialog box!
	hDlgBox = NULL;

	//the ifdef will check ALL included header files for the #define X and if #define X is found the compiler will auto add the code

	//check the value if its valid return from the HWID check dialog box!
	if (msg.wParam == 1337)
	{
		//create a new dialog box because we have checked the HWID!
		hDlgBox = CreateDialogParamA(hInstance, MAKEINTRESOURCEA(IDD_MAIN_DIALOG), NULL, Main_Dialog_Callback, NULL);

		//clear the WHOLE message buffer so that way we dont get wrong data
		ZeroMemory(&msg, sizeof(MSG));

		//we tell the dialog that we want to show it
		ShowWindow(hDlgBox, SW_SHOWNORMAL);

		//we tell "windows" to update the dialog
		UpdateWindow(hDlgBox);

		CThreadData hThreadData = {};
		hThreadData.m_hDlg = hDlgBox;
		hThreadData.m_bGameRunnning = TRUE;
		hThreadData.m_lpMainWorldPointer = 0;
		hThreadData.m_lpLocalPlayerPointer = 0;
		hThreadData.m_dwInputManager = 0;
		hThreadData.m_lpMainCameraGameObject = 0;
		hThreadData.m_iPlayerObjectCount = 0;
		hThreadData.m_iBone = 0;
		hThreadData.m_lpPlayerObjects = (CPlayerData**)calloc(200, sizeof(DWORD64));
		for (int i = 0; i < 200; i++)
			hThreadData.m_lpPlayerObjects[i] = (CPlayerData*)calloc(1, sizeof(CPlayerData));

		//create a thread for the main processing or main shit or hack function what ever you please just so we can do shit in the background with no issues of crap!
		HANDLE hMainThread = CreateThread(NULL, NULL, MainThread, &hThreadData, NULL, NULL);
#ifdef ENABLE_AIMBOT
		HANDLE hPlayerThread = CreateThread(NULL, NULL, PlayerThread, &hThreadData, NULL, NULL);
		HANDLE hAimbotThread = CreateThread(NULL, NULL, AimbotThread, &hThreadData, NULL, NULL);
#endif
		//wait we couldnt create a thread? WTF is this guy running win95?
		if (hMainThread == INVALID_HANDLE_VALUE)
		{
			MessageBoxA(0, "Error Creating MainThread Try Again?", 0, 0);

			//destroy the window FULLY! you dont need to because the quit message will do it but LETS make sure destory is called for clean up?
			DestroyWindow(hDlgBox);

			//set it to NULL so we dont get wrong value when making a new dialog box!
			hDlgBox = NULL;

			return nShowCmd;
		}
#ifdef ENABLE_AIMBOT
		if (hPlayerThread == INVALID_HANDLE_VALUE)
		{
			MessageBoxA(0, "Error Creating MainThread Try Again?", 0, 0);

			//destroy the window FULLY! you dont need to because the quit message will do it but LETS make sure destory is called for clean up?
			DestroyWindow(hDlgBox);

			//set it to NULL so we dont get wrong value when making a new dialog box!
			hDlgBox = NULL;

			return nShowCmd;
		}
		if (hAimbotThread == INVALID_HANDLE_VALUE)
		{
			MessageBoxA(0, "Error Creating MainThread Try Again?", 0, 0);

			//destroy the window FULLY! you dont need to because the quit message will do it but LETS make sure destory is called for clean up?
			DestroyWindow(hDlgBox);

			//set it to NULL so we dont get wrong value when making a new dialog box!
			hDlgBox = NULL;

			return nShowCmd;
		}
#endif
		//make a loop till you get the quit message
		while (msg.message != WM_QUIT)
		{
			//peek message checks if there are any message AKA things that have happen on the dialog
			while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE) > 0)
			{
				//check if this message is a dialog message if this is NOT a dialog message then translate it and send it to the callback function
				if (!IsDialogMessage(hDlgBox, &msg))
				{
					//translate message before sending it to the dialog
					TranslateMessage(&msg);

					//send it to the dialog callback function
					DispatchMessage(&msg);
				}

				//check if the message is quitting
				if (msg.message == WM_QUIT)
				{
					//break the loop when you get the quit message then it will do an if statement and break the endless loop!
					break;
				}
			}
		}

		//destroy the window FULLY! you dont need to because the quit message will do it but LETS make sure destory is called for clean up?
		DestroyWindow(hDlgBox);

		//set it to NULL so we dont get wrong value when making a new dialog box!
		hDlgBox = NULL;

		//tell thread to piss off!
		hThreadData.m_bGameRunnning = FALSE;

		////close the main thread it should close but we need to FORCE it to close because we no longer need it but meh lets just force it 
		//TerminateThread(hMainThread, TRUE);
		//TerminateThread(hAimbotThread, TRUE);

		//wait for the thread to exit!
		WaitForSingleObject(hMainThread, INFINITE);
#ifdef ENABLE_AIMBOT
		WaitForSingleObject(hPlayerThread, INFINITE);
		WaitForSingleObject(hAimbotThread, INFINITE);
		CloseHandle(hPlayerThread);
#endif		
		CloseHandle(hMainThread);
		//exit the handle! always clean up :)

#ifdef ENABLE_AIMBOT
		CloseHandle(hAimbotThread);
#endif
	}

//the ifdef will check ALL included header files for the #define X and if #define X is found the compiler will auto add the code



	//now we just return because everything has been cleaned up etc via the callbacks!
	return nShowCmd;
}