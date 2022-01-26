//pragma once tells C++ compiler if you include this file more then once it will only ever be included more then once so you dont get include errors
#pragma once
//this is a C++ trick / hack that tells dialogs to use the better looking dialogs :)
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#define _CRT_SECURE_NO_WARNINGS
//include any EXTRA files
#include <windows.h>
#include <stdio.h>
#include "leechcore.h"
#include "vmmdll.h"
#include <utility>
#include <TlHelp32.h>
#include <CommCtrl.h>
#include <emmintrin.h>
#include <xmmintrin.h>
#pragma comment(lib,"leechcore.lib")
#pragma comment(lib,"vmm.lib")
#include "resource.h"
#include "Dialog Callbacks.h"

//defines this is where you define anything defines are just basically "static globals/variables" but with #define its telling the compiler you are defining it for compiling

#define REMOTE_PROCESS "EscapeFromTarkov.exe"

#define DEBUG_CONSOLE
//#define ENABLE_AIMBOT

#define INPUT_MANAGER		0x0156C448
#define UNITY_OBJECT_LIST	0x0156C698
#define UNITY_CAMERA_LIST	0x0150EA00

#define SAFE_DELETE_ARRAY(x) if(x) { delete [] x; x = 0; }
#define SAFE_FREE_ALLOC(x) if(x) { LocalFree(x); x = 0; }





typedef enum _OBJECT_INFORMATION_CLASS
{
	ObjectBasicInformation, // OBJECT_BASIC_INFORMATION
	ObjectNameInformation, // OBJECT_NAME_INFORMATION
	ObjectTypeInformation, // OBJECT_TYPE_INFORMATION
	ObjectTypesInformation, // OBJECT_TYPES_INFORMATION
	ObjectHandleFlagInformation, // OBJECT_HANDLE_FLAG_INFORMATION
	ObjectSessionInformation,
	ObjectSessionObjectInformation,
	MaxObjectInfoClass
} OBJECT_INFORMATION_CLASS;

typedef struct _UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;

typedef struct _OBJECT_NAME_INFORMATION
{
	UNICODE_STRING Name;
} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;

typedef struct _OBJECT_TYPE_INFORMATION
{
	UNICODE_STRING TypeName;
	ULONG TotalNumberOfObjects;
	ULONG TotalNumberOfHandles;
	ULONG TotalPagedPoolUsage;
	ULONG TotalNonPagedPoolUsage;
	ULONG TotalNamePoolUsage;
	ULONG TotalHandleTableUsage;
	ULONG HighWaterNumberOfObjects;
	ULONG HighWaterNumberOfHandles;
	ULONG HighWaterPagedPoolUsage;
	ULONG HighWaterNonPagedPoolUsage;
	ULONG HighWaterNamePoolUsage;
	ULONG HighWaterHandleTableUsage;
	ULONG InvalidAttributes;
	GENERIC_MAPPING GenericMapping;
	ULONG ValidAccessMask;
	BOOLEAN SecurityRequired;
	BOOLEAN MaintainHandleCount;
	UCHAR TypeIndex; // since WINBLUE
	CHAR ReservedByte;
	ULONG PoolType;
	ULONG DefaultPagedPoolCharge;
	ULONG DefaultNonPagedPoolCharge;
} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;

#ifndef NT_SUCCESS
#define NT_SUCCESS(x) ((x) >= 0)
#endif //!NT_SUCCESS

#ifndef STATUS_NOT_FOUND
#define STATUS_NOT_FOUND               ((NTSTATUS)0xC0000225L)
#endif //!STATUS_NOT_FOUND

#ifndef STATUS_INFO_LENGTH_MISMATCH
#define STATUS_INFO_LENGTH_MISMATCH    ((NTSTATUS)0xC0000004L)
#endif //!STATUS_INFO_LENGTH_MISMATCH

//extern is just declaring that we have a variable by this name but its else where!
//when declaring extern MAKE sure you declare it else where
extern char szSettingsFile[];
extern DWORD dwConnectionStatusColor;
extern float fMaxStamina;
extern bool bLocalPlayerFound;
extern bool bWorldPointerFound;
extern bool bAutoDisconnectAfterRaidEnds;
extern bool bRemoveVisorEffects;
extern bool bNightVisionEffect;
extern bool bThermalVisionEffect;
extern bool bNoWeight;
extern bool bNoRecoil;
extern bool bNoStamina;
extern bool bUnlockEverything;
extern int iJumpMultiplier;
extern int iThrowMultiplier;
extern int iHearingMultiplier;

#ifdef ENABLE_AIMBOT
extern bool bAimbotEnabled;
extern int iAimbotBone;
extern int iAimbotHotkey;
#endif
#define D3DX_PI                        ((FLOAT)  3.141592654f)
#define D3DXToRadian(degree)        ((degree) * (D3DX_PI / 180.0f))
#define D3DXToDegree(radian)        ((radian) * (180.0f / D3DX_PI))

//we include OTHER files here due to the fact we have defines and static globals above that the header files MIGHT use so just incase lets include files here so the files CAN access what they require!
#include "MonoClasses.h"
#include "DMADevice.h"
#include "MainThread.h"