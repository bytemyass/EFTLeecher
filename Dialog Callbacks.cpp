#include "globals.h"
#include <Wininet.h>
#include <time.h>
#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "wininet.lib")

//this is a dialog call back what a callback is, is a function that gets called when and if something happens in the dialog
//the iMsg argument allows you to filter which one you want to ACT on or what todo when something happens


//keep a record of skill setting's we dont need to keep reading and writing memory from EFT it takes LONGER!
DWORD iLastPressed = 0;
CSkillData sSkillData[Skills_Max] = {};

//i made a function just so its quicker and easy then defining loads of thingss inside the switch cases below!
VOID SetDialogItemsStatus(HWND hDlg, bool bDisabled)
{
	//we dont want to disable the connect button if we are enabled the others we want to do the opposite so we use ! which is the opposite of true!
	EnableWindow(GetDlgItem(hDlg, ID_BTN_DMA_CONNECT), !bDisabled);
	EnableWindow(GetDlgItem(hDlg, IDC_AUTO_DISCONNECT), !bDisabled);
	EnableWindow(GetDlgItem(hDlg, IDC_USE_MMAP_FILE), !bDisabled);
	EnableWindow(GetDlgItem(hDlg, IDC_USE_STEALTH_CONNECTION), !bDisabled);
	EnableWindow(GetDlgItem(hDlg, IDC_REMOVE_CONNECTIONS), !bDisabled);	

	//now do normal shit? enable if we want to or disable!
	EnableWindow(GetDlgItem(hDlg, ID_BTN_DMA_SHUTDOWN), bDisabled);
	//EnableWindow(GetDlgItem(hDlg, IDC_NOWEIGHT), bDisabled);
	//EnableWindow(GetDlgItem(hDlg, IDC_DOORS), bDisabled);
	//EnableWindow(GetDlgItem(hDlg, IDC_DOORS_KEYCARD), bDisabled);
	EnableWindow(GetDlgItem(hDlg, IDC_NORECOIL), bDisabled);
	EnableWindow(GetDlgItem(hDlg, IDC_ENDURANCE), bDisabled);
	EnableWindow(GetDlgItem(hDlg, IDC_SKILLS_MAX), bDisabled);
	EnableWindow(GetDlgItem(hDlg, ID_BTN_VISOR_EFFECT), bDisabled);
	EnableWindow(GetDlgItem(hDlg, ID_BTN_NIGHTVISION), bDisabled);
	EnableWindow(GetDlgItem(hDlg, ID_BTN_THERMAL), bDisabled);
#ifdef ENABLE_AIMBOT
	EnableWindow(GetDlgItem(hDlg, IDC_AIMBOT_ENABLE), bDisabled);
	EnableWindow(GetDlgItem(hDlg, IDC_AIMBOT_HEAD), bDisabled);
	EnableWindow(GetDlgItem(hDlg, IDC_AIMBOT_CHEST), bDisabled);
	EnableWindow(GetDlgItem(hDlg, IDC_AIMBOT_PELVIS), bDisabled);
	EnableWindow(GetDlgItem(hDlg, IDC_AIMBOT_LFOOT), bDisabled);
	EnableWindow(GetDlgItem(hDlg, IDC_AIMBOT_RFOOT), bDisabled);
	EnableWindow(GetDlgItem(hDlg, IDC_AIMBOT_RANDOM), bDisabled);
	EnableWindow(GetDlgItem(hDlg, IDC_AIMBOT_HOTKEY), bDisabled);
#endif
}

//from https://docs.microsoft.com/en-us/windows/win32/controls/create-a-tooltip-for-a-control

// Description:
//   Creates a tooltip for an item in a dialog box. 

// Parameters:
//   idTool - identifier of an dialog box item.
//   nDlg - window handle of the dialog box.
//   pszText - string to use as the tooltip text.

// Returns:
//   The handle to the tooltip.
//
HWND CreateToolTip(int toolID, HWND hDlg, PTSTR pszText)
{
	if (!toolID || !hDlg || !pszText)
		return NULL;

	// Get the window of the tool.
	HWND hwndTool = GetDlgItem(hDlg, toolID);

	// Create the tooltip. g_hInst is the global instance handle.
	HWND hwndTip = CreateWindowEx(NULL, TOOLTIPS_CLASS, NULL, WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hDlg, NULL, GetModuleHandle(0), NULL);
	if (!hwndTool || !hwndTip)
		return NULL;

	// Associate the tooltip with the tool.
	TOOLINFO toolInfo = { 0 };
	toolInfo.cbSize = sizeof(toolInfo);
	toolInfo.hwnd = hDlg;
	toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
	toolInfo.uId = (UINT_PTR)hwndTool;
	toolInfo.lpszText = pszText;
	SendMessage(hwndTip, TTM_ADDTOOL, 0, (LPARAM)&toolInfo);
	return hwndTip;
}
//write our own version i mean microsoft thanks so much!
BOOL WINAPI WritePrivateProfileIntA(LPCSTR szKey, int iValue)
{
	char szValue[64] = {};
	sprintf_s(szValue, "%d", iValue);
	return WritePrivateProfileStringA("ToolBox", szKey, szValue, szSettingsFile);
}

//this is for the serial dialog box
INT_PTR CALLBACK Serial_Dialog_Callback(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//switch is just a simple load of if's statment's
	switch (iMsg)
	{
		//init dialog is the first thing that is called put your start up code here
		case WM_INITDIALOG:
		{


			//declare a buffer for the HWID
			char szHWID[512] = { 0 };
			//the ifdef will check ALL included header files for the #define X and if #define X is found the compiler will auto add the code

			strcpy_s(szHWID, "DEV_HWID");

			//SetWindowText just does what it says on the tin lol it sets text inside a dialog item
			//GetDlgItem is a simple function it grabs ANY dialog item within or declared on or in a dialog
			SetWindowTextA(GetDlgItem(hWnd, IDC_HWID), szHWID);

			//the ifdef will check ALL included header files for the #define X and if #define X is found the compiler will auto add the code


			//to save the user time we call a simple windows api called postmessage which basically is saying SEND this message to the dialog telling them we have clicked OK
			PostMessage(hWnd, WM_COMMAND, MAKEWPARAM(IDOK, NULL), NULL);

			//the ifdef will check ALL included header files for the #define X and if #define X is found the compiler will auto add the code

			
		}break;

		//command is passed when you click or you do a command
		case WM_COMMAND:
		{
			//grab which dialog item passed the command AKA button's etc
			switch (LOWORD(wParam))
			{
				//IDOK is a normal OK dialog button (just to explain i renamed the OK button to verity)
				case IDOK:
				{
//the ifdef will check ALL included header files for the #define X and if #define X is found the compiler will auto add the code


					//keep a buffer for the serial
					char szSerial[512] = { 0 };
//read above about this.....^^

					


			
					//grab the dialog entered text or text that we have set
					UINT iLen = GetDlgItemTextA(hWnd, IDC_SERIAL, szSerial, 512);

					strcpy_s(szSerial, "DEV_HWID");
	

					//WritePrivateProfileStringA writes a string to a file with the key given!
					//we write it here because the HWID has been checked and has passed so CAN write and it will be valid next time!
					for (int s = 0; s < iLen; s++)
					{
						if (szSerial[s] == '\r' && szSerial[s + 1] == '\n')
						{
							memmove(&szSerial[s], &szSerial[s + 2], iLen - s);
						}
					}

					WritePrivateProfileStringA("ToolBox", "HWID", szSerial, szSettingsFile);

					//we can pass ANYTHING to quit message so we can check if its valid!
					PostQuitMessage(1337);
					
				
					return S_OK;
				
				}break;

				//IDCANCEL is a normal Cancel dialog button
				case IDCANCEL:
				{
					//post quit message forces the WM_QUIT message which in the main app loop you should be looking for then to break and after that message is processed the app will then fetch the destory etc message's
					PostQuitMessage(0);
				}break;
			}

		}break;

		//destroy is called when the dialog is DESTORYED put your clean up code here
		case WM_DESTROY:
		{
			
		}break;
	}
	return S_OK;
}

//this is for the main dialog box
INT_PTR CALLBACK Main_Dialog_Callback(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//switch is just a simple load of if's statment's
	switch (iMsg)
	{
		//init dialog is the first thing that is called put your start up code here
		case WM_INITDIALOG:
		{
			//load setting's here
			if(GetPrivateProfileIntA("ToolBox", "UseMapFile", 0, szSettingsFile))
				CheckDlgButton(hWnd, IDC_USE_MMAP_FILE, BST_CHECKED);

			if (GetPrivateProfileIntA("ToolBox", "StealthInjection", 0, szSettingsFile))
				CheckDlgButton(hWnd, IDC_USE_STEALTH_CONNECTION, BST_CHECKED);

			if (GetPrivateProfileIntA("ToolBox", "RemoveConnections", 0, szSettingsFile))
				CheckDlgButton(hWnd, IDC_REMOVE_CONNECTIONS, BST_CHECKED);

			if (GetPrivateProfileIntA("ToolBox", "AutoDisconnect", 0, szSettingsFile))
			{
				bAutoDisconnectAfterRaidEnds = true;
				CheckDlgButton(hWnd, IDC_AUTO_DISCONNECT, BST_CHECKED);
			}
			else
			{
				bAutoDisconnectAfterRaidEnds = false;
			}

			if (GetPrivateProfileIntA("ToolBox", "RemoveVisorEffects", 0, szSettingsFile))
			{
				SendMessageA(hWnd, WM_COMMAND, MAKEWPARAM(ID_BTN_VISOR_EFFECT, 0), 0);
			}

			if (GetPrivateProfileIntA("ToolBox", "NightVisionEffect", 0, szSettingsFile))
			{
				SendMessageA(hWnd, WM_COMMAND, MAKEWPARAM(ID_BTN_NIGHTVISION, 0), 0);
			}

			if (GetPrivateProfileIntA("ToolBox", "ThermalVisionEffect", 0, szSettingsFile))
			{
				SendMessageA(hWnd, WM_COMMAND, MAKEWPARAM(ID_BTN_THERMAL, 0), 0);
			}
			bNoWeight = (GetPrivateProfileIntA("ToolBox", "NoWeight", 0, szSettingsFile));
			bUnlockEverything = (GetPrivateProfileIntA("ToolBox", "UnlockEverything", 0, szSettingsFile));
			bNoStamina = (GetPrivateProfileIntA("ToolBox", "NoStamina", 0, szSettingsFile));
			bNoRecoil = (GetPrivateProfileIntA("ToolBox", "NoRecoil", 0, szSettingsFile));
			bRemoveVisorEffects = (GetPrivateProfileIntA("ToolBox", "RemoveVisorEffects", 0, szSettingsFile));
			bNightVisionEffect = (GetPrivateProfileIntA("ToolBox", "NightVisionEffect", 0, szSettingsFile));
			bThermalVisionEffect = (GetPrivateProfileIntA("ToolBox", "ThermalVisionEffect", 0, szSettingsFile));
			CheckDlgButton(hWnd, IDC_NORECOIL, bNoRecoil ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hWnd, IDC_ENDURANCE, bNoStamina ? BST_CHECKED : BST_UNCHECKED);


			SetDlgItemTextA(hWnd, ID_BTN_VISOR_EFFECT, !bRemoveVisorEffects ? "Enable Visor Effects" : "Remove Visor Effects");
			SetDlgItemTextA(hWnd, ID_BTN_THERMAL, (!bThermalVisionEffect) ? "Enable Thermal Vision" : "Disable Thermal Vision");
			SetDlgItemTextA(hWnd, ID_BTN_NIGHTVISION, !bNightVisionEffect ? "Enable Night Vision" : "Disable Night Vision");

			iJumpMultiplier = (GetPrivateProfileIntA("ToolBox", "JumpMultiplier", 1, szSettingsFile));
			iThrowMultiplier = (GetPrivateProfileIntA("ToolBox", "ThrowMultiplier", 1, szSettingsFile));
			iHearingMultiplier = (GetPrivateProfileIntA("ToolBox", "HearingMultiplier", 1, szSettingsFile));

			SendDlgItemMessageW(hWnd, IDC_JUMP_SLIDER, TBM_SETRANGE, TRUE, MAKELPARAM(1, 6));
			SendDlgItemMessageW(hWnd, IDC_THROW_SLIDER, TBM_SETRANGE, TRUE, MAKELPARAM(1, 6));
			SendDlgItemMessageW(hWnd, IDC_HEARING_SLIDER, TBM_SETRANGE, TRUE, MAKELPARAM(1, 10));

			SendDlgItemMessageW(hWnd, IDC_JUMP_SLIDER, TBM_SETPOS, TRUE, iJumpMultiplier);
			SendDlgItemMessageW(hWnd, IDC_THROW_SLIDER, TBM_SETPOS, TRUE, iThrowMultiplier);
			SendDlgItemMessageW(hWnd, IDC_HEARING_SLIDER, TBM_SETPOS, TRUE, iHearingMultiplier);

			wchar_t szTextBuffer[32] = {};
			swprintf_s(szTextBuffer, L"%dx", iJumpMultiplier);
			SetWindowTextW(GetDlgItem(hWnd, IDC_JUMP_TEXT), szTextBuffer);
			swprintf_s(szTextBuffer, L"%dx", iThrowMultiplier);
			SetWindowTextW(GetDlgItem(hWnd, IDC_THROW_TEXT), szTextBuffer);
			swprintf_s(szTextBuffer, L"%dx", iHearingMultiplier);
			SetWindowTextW(GetDlgItem(hWnd, IDC_HEARING_TEXT), szTextBuffer);

#ifdef ENABLE_AIMBOT
		
			iAimbotBone = GetPrivateProfileIntA("ToolBox", "Aimbot_Bone", EHumanBones::HumanHead, szSettingsFile);
			if (iAimbotBone == EHumanBones::HumanHead)
				CheckDlgButton(hWnd, IDC_AIMBOT_HEAD, BST_CHECKED);
			if (iAimbotBone == EHumanBones::HumanSpine1)
				CheckDlgButton(hWnd, IDC_AIMBOT_CHEST, BST_CHECKED);
			if (iAimbotBone == EHumanBones::HumanPelvis)
				CheckDlgButton(hWnd, IDC_AIMBOT_PELVIS, BST_CHECKED);
			if (iAimbotBone == EHumanBones::HumanLFoot)
				CheckDlgButton(hWnd, IDC_AIMBOT_LFOOT, BST_CHECKED);
			if (iAimbotBone == EHumanBones::HumanRFoot)
				CheckDlgButton(hWnd, IDC_AIMBOT_RFOOT, BST_CHECKED);
			if (iAimbotBone == EHumanBones::BONE_MAX)
				CheckDlgButton(hWnd, IDC_AIMBOT_RANDOM, BST_CHECKED);

			bAimbotEnabled = (GetPrivateProfileIntA("ToolBox", "Aimbot_Enable", 0, szSettingsFile) == 1);
			CheckDlgButton(hWnd, IDC_AIMBOT_ENABLE, bAimbotEnabled);

			iAimbotHotkey = (GetPrivateProfileIntA("ToolBox", "Aimbot_Hotkey", KC_Mouse0, szSettingsFile));
			for (int i = 1; i < 0xA6; i++)
			{
				if (iAimbotHotkey == unityKC[i].kc && unityKC[i].kc != KC_None)
					SetDlgItemTextW(hWnd, IDC_AIMBOT_HOTKEY, unityKC[i].KeyName);
			}
#endif
		}break;

		//command is passed when you click or you do a command
		case WM_COMMAND:
		{
			//grab which dialog item passed the command AKA button's etc
			switch (LOWORD(wParam))
			{
				//lets check which button we have clicked or dialog item we have clicked
				case ID_BTN_DMA_CONNECT:
				{
					//now lets call the function to see if we can connect

					//we dont have to use variables BUT easyer for you to understand
					bool bUseMapFile = (IsDlgButtonChecked(hWnd, IDC_USE_MMAP_FILE) == BST_CHECKED);
					bool bUseStealth = (IsDlgButtonChecked(hWnd, IDC_USE_STEALTH_CONNECTION) == BST_CHECKED);
					bool bRemoveDMA = (IsDlgButtonChecked(hWnd, IDC_REMOVE_CONNECTIONS) == BST_CHECKED);

					//call our function to connect to the dma device!
					if (DMADevice::Connect(bUseMapFile, bUseStealth, bRemoveDMA) == false)
					{
						//DO NOT continue! return so the code dont continue!
						return S_OK;
					}

					//we want a new color so lets make it green? i like green its nice!
					dwConnectionStatusColor = RGB(0, 255, 0);

					//change the connection status to connected aka green(lime)!
					SetDlgItemTextA(hWnd, IDC_CONNECTION_STATUS, "Connected!");

					//now we attach to the process id we want
					if (DMADevice::AttachToProcessId() == false)
					{
						//display an error
						MessageBoxA(0, "Remote process " REMOTE_PROCESS " was not found please make sure the process is running! and click connect again.", 0, 0);
						
						//we dont disconnect there no point? its just easier to find the process again
						return S_OK;
					}
					//create a buffer to store the results of sprintf
					char szProcessIdBufferText[32] = { 0 };

					//sprintf converts a format to string
					sprintf_s(szProcessIdBufferText, "%d[0x%X]", DMADevice::dwAttachedProcessId, DMADevice::dwAttachedProcessId);

					//set the dlgitem text
					SetDlgItemTextA(hWnd, IDC_PROCESS_ID, szProcessIdBufferText);

					//set all the dlgitems to enabled
					SetDialogItemsStatus(hWnd, true);
				}break;

				case ID_BTN_DMA_SHUTDOWN:
				{
					//disconnect the device
					DMADevice::Disconnect();

					//change the connection status to disconnected AKA red!
					dwConnectionStatusColor = RGB(255, 0, 0);

					//set the connection status text to disconnected
					SetDlgItemTextA(hWnd, IDC_CONNECTION_STATUS, "Disconnected!");

					//set the dlgitem text
					SetDlgItemTextA(hWnd, IDC_PROCESS_ID, "N/A");
					
					//set all the dlgitems to disabled
					SetDialogItemsStatus(hWnd, false);
				}break;

				case IDC_AUTO_DISCONNECT:
				{
					//set the global variable to what ever the user has set it to
					bAutoDisconnectAfterRaidEnds = (IsDlgButtonChecked(hWnd, IDC_AUTO_DISCONNECT) == BST_CHECKED);
				}break;


				case ID_BTN_VISOR_EFFECT:
				{
					//let me explain this this is just making the variable equal the opposite of the current value so its as simple as writing this!
					//if(bRemoveVisorEffects) bRemoveVisorEffects = false;
					//if(!bRemoveVisorEffects) bRemoveVisorEffects = true;
					bRemoveVisorEffects = !bRemoveVisorEffects;

					//right let me explain the ? : the ? means if that value is TRUE so bRemoveVisorEffects == true the FIRST or after the ? will be the value or text and : will be the opposite of what value!
					SetDlgItemTextA(hWnd, ID_BTN_VISOR_EFFECT, !bRemoveVisorEffects ? "Enable Visor Effects" : "Remove Visor Effects");
				}break;

				case ID_BTN_NIGHTVISION:
				{
					//read above for information about this!
					bNightVisionEffect = !bNightVisionEffect;

					//set some lovly text(read above for this information)
					SetDlgItemTextA(hWnd, ID_BTN_NIGHTVISION, !bNightVisionEffect ? "Enable Night Vision" : "Disable Night Vision");
				}break;

				case ID_BTN_THERMAL:
				{
					//read above for information about this!
					bThermalVisionEffect = !bThermalVisionEffect;

					//set some lovly text(read above for this information)
					SetDlgItemTextA(hWnd, ID_BTN_THERMAL, !bThermalVisionEffect ? "Enable Thermal Vision" : "Disable Thermal Vision");
				}break;

				case IDC_NORECOIL:
				{
					//just check the status of the checkbox and set a "global variable" of the status
					bNoRecoil = (IsDlgButtonChecked(hWnd, IDC_NORECOIL) == BST_CHECKED);
				}break;

				case IDC_ENDURANCE:
				{
					//just check the status of the checkbox and set a "global variable" of the status
					bNoStamina = (IsDlgButtonChecked(hWnd, IDC_ENDURANCE) == BST_CHECKED);
				}break;

				case IDC_DOORS:
				{
					//just check the status of the checkbox and set a "global variable" of the status
					bUnlockEverything = (IsDlgButtonChecked(hWnd, IDC_DOORS) == BST_CHECKED);
				}break;

				//case IDC_SKILLSMAX:
				//{
				//	//create a new dialog box for the skills
				//	bSkillsUpdate = (IsDlgButtonChecked(hWnd, IDC_SKILLSMAX) == BST_CHECKED);;

				case IDC_BTN_SKILLS:
				{
					//create a new dialog box for the skills
					DialogBoxW(GetModuleHandle(0), MAKEINTRESOURCE(IDD_SKILL_BUF_DIALOG), NULL, Skills_Dialog_Callback);
				}break;

#ifdef ENABLE_AIMBOT
				case IDC_AIMBOT_ENABLE:
				{
					bAimbotEnabled = (IsDlgButtonChecked(hWnd, IDC_AIMBOT_ENABLE) == BST_CHECKED);
				}break;

				case IDC_AIMBOT_HEAD:
				case IDC_AIMBOT_CHEST:
				case IDC_AIMBOT_PELVIS:
				case IDC_AIMBOT_LFOOT:
				case IDC_AIMBOT_RFOOT:
				case IDC_AIMBOT_RANDOM:
				{
					if (IsDlgButtonChecked(hWnd, IDC_AIMBOT_HEAD))
						iAimbotBone = EHumanBones::HumanHead;
					if (IsDlgButtonChecked(hWnd, IDC_AIMBOT_PELVIS))
						iAimbotBone = EHumanBones::HumanPelvis;
					if (IsDlgButtonChecked(hWnd, IDC_AIMBOT_CHEST))
						iAimbotBone = EHumanBones::HumanSpine1;//no idea if this is correct but try different values
					if (IsDlgButtonChecked(hWnd, IDC_AIMBOT_LFOOT))
						iAimbotBone = EHumanBones::HumanLFoot;
					if (IsDlgButtonChecked(hWnd, IDC_AIMBOT_RFOOT))
						iAimbotBone = EHumanBones::HumanRFoot;
					if (IsDlgButtonChecked(hWnd, IDC_AIMBOT_RANDOM))
						iAimbotBone = EHumanBones::BONE_MAX;

				}break;

				//shit part :@
				case IDC_AIMBOT_HOTKEY:
				{
					//need this because when you click on the button and try set LButton the dlg wants to past the button press AGAIN! so you in an endless loop!
					if (iLastPressed > 0)
					{
						int dwTmp = (int)(iLastPressed - GetTickCount());
						if (dwTmp > 0 && !(dwTmp < 0))
							return 0;
					}

					SetFocus(NULL);

					int iKey = -1;
					SetDlgItemTextW(hWnd, IDC_AIMBOT_HOTKEY, L"Press Any Key");
					while (iKey == -1)
					{
						for (int i = 0; i < 0xE0; i++)
						{
							if (GetAsyncKeyState(i) < 0 && unityKC[i].kc != KC_None)
							{
								iKey = i;
								break;
							}
						}
					}
					iAimbotHotkey = unityKC[iKey].kc;
					SetDlgItemTextW(hWnd, IDC_AIMBOT_HOTKEY, unityKC[iKey].KeyName);
					if(iKey == VK_LBUTTON)
						iLastPressed = (GetTickCount() + 200);

				}break;
#endif
			
				
				case ID_EXIT:
				{
					//save settings why not?
					WritePrivateProfileIntA("RemoveVisorEffects", bRemoveVisorEffects);
					WritePrivateProfileIntA("NightVisionEffect", bNightVisionEffect);
					WritePrivateProfileIntA("ThermalVisionEffect", bThermalVisionEffect);
					WritePrivateProfileIntA("NoRecoil", bNoRecoil);
					WritePrivateProfileIntA("NoStamina", bNoStamina);
					WritePrivateProfileIntA("UnlockEverything", bUnlockEverything);
					WritePrivateProfileIntA("NoWeight", bNoWeight);
					WritePrivateProfileIntA("UseMapFile", (IsDlgButtonChecked(hWnd, IDC_USE_MMAP_FILE) == BST_CHECKED));
					WritePrivateProfileIntA("StealthInjection", (IsDlgButtonChecked(hWnd, IDC_USE_STEALTH_CONNECTION) == BST_CHECKED));
					WritePrivateProfileIntA("RemoveConnections", (IsDlgButtonChecked(hWnd, IDC_REMOVE_CONNECTIONS) == BST_CHECKED));
					WritePrivateProfileIntA("AutoDisconnect", (IsDlgButtonChecked(hWnd, IDC_AUTO_DISCONNECT) == BST_CHECKED));
					WritePrivateProfileIntA("JumpMultiplier", iJumpMultiplier);
					WritePrivateProfileIntA("ThrowMultiplier", iThrowMultiplier);
					WritePrivateProfileIntA("HearingMultiplier", iHearingMultiplier);
#ifdef ENABLE_AIMBOT
					WritePrivateProfileIntA("Aimbot_Bone", iAimbotBone);
					WritePrivateProfileIntA("Aimbot_Hotkey", iAimbotHotkey);
					WritePrivateProfileIntA("Aimbot_Enable", bAimbotEnabled);
#endif
					PostQuitMessage(0);
				}break;
			}
		}break;

		//this is sent as a message WHEN you move the slider etc
		case WM_HSCROLL:
		{
			if ((HWND)lParam == GetDlgItem(hWnd, IDC_JUMP_SLIDER))
			{
				//grab the slider value
				int iPos = SendDlgItemMessageW(hWnd, IDC_JUMP_SLIDER, TBM_GETPOS, 0, 0);

				//set the "text" for the value of the level
				wchar_t szTextBuffer[32] = {};
				swprintf_s(szTextBuffer, L"%dx", iPos);
				SetWindowTextW(GetDlgItem(hWnd, IDC_JUMP_TEXT), szTextBuffer);

				//set the data
				iJumpMultiplier = iPos;
			}
			if ((HWND)lParam == GetDlgItem(hWnd, IDC_THROW_SLIDER))
			{
				//grab the slider value
				int iPos = SendDlgItemMessageW(hWnd, IDC_THROW_SLIDER, TBM_GETPOS, 0, 0);

				//set the "text" for the value of the level
				wchar_t szTextBuffer[32] = {};
				swprintf_s(szTextBuffer, L"%dx", iPos);
				SetWindowTextW(GetDlgItem(hWnd, IDC_THROW_TEXT), szTextBuffer);

				//set the data
				iThrowMultiplier = iPos;
			}
			if ((HWND)lParam == GetDlgItem(hWnd, IDC_HEARING_SLIDER))
			{
				//grab the slider value
				int iPos = SendDlgItemMessageW(hWnd, IDC_HEARING_SLIDER, TBM_GETPOS, 0, 0);

				//set the "text" for the value of the level
				wchar_t szTextBuffer[32] = {};
				swprintf_s(szTextBuffer, L"%dx", iPos);
				SetWindowTextW(GetDlgItem(hWnd, IDC_HEARING_TEXT), szTextBuffer);

				//set the data
				iHearingMultiplier = iPos;
			}

		}break;

		//this is sent or called BEFORE the static text is drawn so we can make it really fancy if we want only did this so it can show you you can do many things!
		case WM_CTLCOLORSTATIC:
		{
			if (((HWND)lParam) == GetDlgItem(hWnd, IDC_CONNECTION_STATUS))
			{
				//set the background mode so we want it transparent
				SetBkMode((HDC)wParam, TRANSPARENT);

				//set the text color
				SetTextColor((HDC)wParam, dwConnectionStatusColor);

				//WM_CTLCOLORSTATIC REQUIRES YOU TO RETURN A SYSCOLORBRUSH!!!
				//Return value
				//If an application processes this message, the return value is a handle to a brush that the system uses to paint the background of the static control.
				//so we return the color menu which is default menu color of any dialog
				return (BOOL)GetSysColorBrush(COLOR_MENU);
			}
			if (((HWND)lParam) == GetDlgItem(hWnd, IDC_PLAYER_STATUS))
			{
				//set the background mode so we want it transparent
				SetBkMode((HDC)wParam, TRANSPARENT);

				//set the text color
				SetTextColor((HDC)wParam, bLocalPlayerFound ? RGB(0,255,0) : RGB(255,0,0));

				//WM_CTLCOLORSTATIC REQUIRES YOU TO RETURN A SYSCOLORBRUSH!!!
				//Return value
				//If an application processes this message, the return value is a handle to a brush that the system uses to paint the background of the static control.
				//so we return the color menu which is default menu color of any dialog
				return (BOOL)GetSysColorBrush(COLOR_MENU);
			}
			if (((HWND)lParam) == GetDlgItem(hWnd, IDC_WORLD_STATUS))
			{
				//set the background mode so we want it transparent
				SetBkMode((HDC)wParam, TRANSPARENT);

				//set the text color
				SetTextColor((HDC)wParam, bWorldPointerFound ? RGB(0, 255, 0) : RGB(255, 0, 0));

				//WM_CTLCOLORSTATIC REQUIRES YOU TO RETURN A SYSCOLORBRUSH!!!
				//Return value
				//If an application processes this message, the return value is a handle to a brush that the system uses to paint the background of the static control.
				//so we return the color menu which is default menu color of any dialog
				return (BOOL)GetSysColorBrush(COLOR_MENU);
			}

			
		}break;

		//did we click the nice BIG recross at the top right? then process it?
		case WM_CLOSE:
		{
			//save settings why not?
			WritePrivateProfileIntA("RemoveVisorEffects", bRemoveVisorEffects);
			WritePrivateProfileIntA("NightVisionEffect", bNightVisionEffect);
			WritePrivateProfileIntA("ThermalVisionEffect", bThermalVisionEffect);
			WritePrivateProfileIntA("NoRecoil", bNoRecoil);
			WritePrivateProfileIntA("NoStamina", bNoStamina);
			WritePrivateProfileIntA("UnlockEverything", bUnlockEverything);
			WritePrivateProfileIntA("NoWeight", bNoWeight);
			WritePrivateProfileIntA("UseMapFile", (IsDlgButtonChecked(hWnd, IDC_USE_MMAP_FILE) == BST_CHECKED));
			WritePrivateProfileIntA("StealthInjection", (IsDlgButtonChecked(hWnd, IDC_USE_STEALTH_CONNECTION) == BST_CHECKED));
			WritePrivateProfileIntA("RemoveConnections", (IsDlgButtonChecked(hWnd, IDC_REMOVE_CONNECTIONS) == BST_CHECKED));
			WritePrivateProfileIntA("AutoDisconnect", (IsDlgButtonChecked(hWnd, IDC_AUTO_DISCONNECT) == BST_CHECKED));
			WritePrivateProfileIntA("JumpMultiplier", iJumpMultiplier);
			WritePrivateProfileIntA("ThrowMultiplier", iThrowMultiplier);
			WritePrivateProfileIntA("HearingMultiplier", iHearingMultiplier);
#ifdef ENABLE_AIMBOT
			WritePrivateProfileIntA("Aimbot_Bone", iAimbotBone);
			WritePrivateProfileIntA("Aimbot_Hotkey", iAimbotHotkey);
			WritePrivateProfileIntA("Aimbot_Enable", bAimbotEnabled);
#endif
			//disconnect the device
			DMADevice::Disconnect();

			//lets just quit!
			PostQuitMessage(0);
		}break;

		//destroy is called when the dialog is DESTORYED put your clean up code here
		case WM_DESTROY:
		{
			//disconnect the device
			DMADevice::Disconnect();

			//save settings why not?
			WritePrivateProfileIntA("RemoveVisorEffects", bRemoveVisorEffects);
			WritePrivateProfileIntA("NightVisionEffect", bNightVisionEffect);
			WritePrivateProfileIntA("ThermalVisionEffect", bThermalVisionEffect);
			WritePrivateProfileIntA("NoRecoil", bNoRecoil);
			WritePrivateProfileIntA("NoStamina", bNoStamina);
			WritePrivateProfileIntA("UnlockEverything", bUnlockEverything);
			WritePrivateProfileIntA("NoWeight", bNoWeight);
			WritePrivateProfileIntA("UseMapFile", (IsDlgButtonChecked(hWnd, IDC_USE_MMAP_FILE) == BST_CHECKED));
			WritePrivateProfileIntA("StealthInjection", (IsDlgButtonChecked(hWnd, IDC_USE_STEALTH_CONNECTION) == BST_CHECKED));
			WritePrivateProfileIntA("RemoveConnections", (IsDlgButtonChecked(hWnd, IDC_REMOVE_CONNECTIONS) == BST_CHECKED));
			WritePrivateProfileIntA("AutoDisconnect", (IsDlgButtonChecked(hWnd, IDC_AUTO_DISCONNECT) == BST_CHECKED));
			WritePrivateProfileIntA("JumpMultiplier", iJumpMultiplier);
			WritePrivateProfileIntA("ThrowMultiplier", iThrowMultiplier);
			WritePrivateProfileIntA("HearingMultiplier", iHearingMultiplier);
			#ifdef ENABLE_AIMBOT
			WritePrivateProfileIntA("Aimbot_Bone", iAimbotBone);
			WritePrivateProfileIntA("Aimbot_Hotkey", iAimbotHotkey);
			WritePrivateProfileIntA("Aimbot_Enable", bAimbotEnabled);
			#endif

		}break;
	}
	return S_OK;
}

//this is for the skills dialog box
INT_PTR CALLBACK Skills_Dialog_Callback(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//switch is just a simple load of if's statment's
	switch (iMsg)
	{
		//init dialog is the first thing that is called put your start up code here
		case WM_INITDIALOG:
		{
			//load setting's here
			for (int i = 0; i < Skills_Max; i++)
			{
				//add the skill name to the list
				SendDlgItemMessageW(hWnd, IDC_SKILLS_LIST, LB_ADDSTRING, NULL, (LPARAM)szSkillNames[i]);

				//declare a buffer for the key
				char szKey[64] = {};

				//now make a string with the buffer and add a unique key
				sprintf_s(szKey, "Level_Enabled_%d", i);

				//set the data from the settings file
				sSkillData[i].m_bLvlEnabled = GetPrivateProfileIntA("ToolBox", szKey, 0, szSettingsFile);

				//clear the buffer for new data
				ZeroMemory(szKey, 64);

				//now make a string with the buffer and add a unique key
				sprintf_s(szKey, "Level_%d", i);

				//set the data from the settings file
				sSkillData[i].m_iLevel = GetPrivateProfileIntA("ToolBox", szKey, 0, szSettingsFile);
			}

			//set the values for the slider min and max!
			SendDlgItemMessageW(hWnd, IDC_LEVEL_SLIDER, TBM_SETRANGE, TRUE, MAKELPARAM(0, 51));
		}break;

		//this is sent as a message WHEN you move the slider etc
		case WM_HSCROLL:
		{
			if ((HWND)lParam == GetDlgItem(hWnd, IDC_LEVEL_SLIDER))
			{
				//we have changed selection so lets grab the new selected one!
				INT iSelected = SendDlgItemMessageA(hWnd, IDC_SKILLS_LIST, LB_GETCURSEL, NULL, NULL);

				//check if we have selected something make sure we are not going over board!
				if (iSelected == LB_ERR || iSelected >= Skills_Max)
					return S_OK;

				//grab the slider value
				int iPos = SendDlgItemMessageW(hWnd, IDC_LEVEL_SLIDER, TBM_GETPOS, 0, 0);

				//set the "text" for the value of the level
				wchar_t szTextBuffer[32] = {};
				swprintf_s(szTextBuffer, L"%d", iPos);

				//after 50 its MAX level!
				if (iPos > 50)
					wcscpy(szTextBuffer, L"MAX");

				//set the dlg item text
				SetWindowTextW(GetDlgItem(hWnd, IDC_LEVEL_TEXT), szTextBuffer);

				//set the data
				sSkillData[iSelected].m_iLevel = iPos;
			}
		}break;

		//command is passed when you click or you do a command
		case WM_COMMAND:
		{
			//grab which dialog item passed the command AKA button's etc
			switch (LOWORD(wParam))
			{
				//did we click enable?
				case IDC_ENABLE_LEVEL:
				{
					//we have changed selection so lets grab the new selected one!
					INT iSelected = SendDlgItemMessageA(hWnd, IDC_SKILLS_LIST, LB_GETCURSEL, NULL, NULL);

					//check if we have selected something make sure we are not going over board!
					if (iSelected == LB_ERR || iSelected >= Skills_Max)
						return S_OK;

					//save the results
					sSkillData[iSelected].m_bLvlEnabled = IsDlgButtonChecked(hWnd, IDC_ENABLE_LEVEL);

					//enable or disbale the skill slider
					EnableWindow(GetDlgItem(hWnd, IDC_LEVEL_SLIDER), sSkillData[iSelected].m_bLvlEnabled); 
					EnableWindow(GetDlgItem(hWnd, IDC_LEVEL_TEXT), sSkillData[iSelected].m_bLvlEnabled);
				}break;

				////did we click enable?
				//case IDC_SKILL_BUFFER:
				//{
				//	//we have changed selection so lets grab the new selected one!
				//	INT iSelected = SendDlgItemMessageA(hWnd, IDC_SKILLS_LIST, LB_GETCURSEL, NULL, NULL);

				//	//check if we have selected something make sure we are not going over board!
				//	if (iSelected == LB_ERR || iSelected >= Skills_Max)
				//		return S_OK;

				//	//save the results
				//	sSkillData[iSelected].m_bBuffsEnabled = IsDlgButtonChecked(hWnd, IDC_ENABLE_LEVEL);

				//	//we tell the main thread we have updated skills
				//	bSkillsUpdate = true;
				//}break;


				//check if its a list we have clicked!
				case IDC_SKILLS_LIST:
				{
					//check why we clicked or what we have done?
					if (HIWORD(wParam) == LBN_SELCHANGE)
					{
						//we have changed selection so lets grab the new selected one!
						INT iSelected = SendDlgItemMessageA(hWnd, IDC_SKILLS_LIST, LB_GETCURSEL, NULL, NULL);
						
						//check if we have selected something make sure we are not going over board!
						if (iSelected == LB_ERR || iSelected >= Skills_Max)
							return S_OK;

						//grab the selected from the array we dont require it as a pointer (pointer allows changes done to it but keep it as an array so we can READ only)
						CSkillData lpSkillData = sSkillData[iSelected];

						//check the dlg button on the status of the saved results
						CheckDlgButton(hWnd, IDC_ENABLE_LEVEL, lpSkillData.m_bLvlEnabled ? BST_CHECKED : BST_UNCHECKED);

						//enable the window IF skill check box is enabled or disable if not ticked etc
						EnableWindow(GetDlgItem(hWnd, IDC_LEVEL_SLIDER), lpSkillData.m_bLvlEnabled);
						EnableWindow(GetDlgItem(hWnd, IDC_LEVEL_TEXT), lpSkillData.m_bLvlEnabled);

						//set the dlg item text 
						wchar_t szTextBuffer[64] = {};
						swprintf_s(szTextBuffer, L"%d", lpSkillData.m_iLevel);

						//after 50 its MAX level!
						if (lpSkillData.m_iLevel > 50)
							wcscpy(szTextBuffer, L"MAX");
						SetDlgItemTextW(hWnd, IDC_LEVEL_TEXT, szTextBuffer);

						//set the track bar / slider position
						SendDlgItemMessageW(hWnd, IDC_LEVEL_SLIDER, TBM_SETPOS, TRUE, lpSkillData.m_iLevel);
						////check the dlg button on the status of the saved results
						//CheckDlgButton(hWnd, IDC_SKILL_BUFFER, lpSkillData.m_bBuffsEnabled);
					}
				}break;
			}
		}
		break;
		
		//destroy is called when the dialog is DESTORYED put your clean up code here
		case WM_DESTROY:
		{
			//save setting's here
			for (int i = 0; i < Skills_Max; i++)
			{
				//declare a buffer for the key
				char szKey[64] = {};

				//now make a string with the buffer and add a unique key
				sprintf_s(szKey, "Level_Enabled_%d", i);

				//write the data from the global array
				WritePrivateProfileIntA(szKey, sSkillData[i].m_bLvlEnabled);

				//clear the buffer for new data
				ZeroMemory(szKey, 64);

				//now make a string with the buffer and add a unique key
				sprintf_s(szKey, "Level_%d", i);
				
				//write the data from the global array
				WritePrivateProfileIntA(szKey, sSkillData[i].m_iLevel);
			}
		}break;

		case WM_CLOSE:
		{
			EndDialog(hWnd, 0);
		}break;
	}
	return S_OK;
}