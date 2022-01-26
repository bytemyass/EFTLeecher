#pragma once


#define PAGE_SIZE 0x1000
#define BELOW_PAGE_SIZE (PAGE_SIZE - 1)
#define PAGE_ADDRESS(x) (x & 0xfffffffffffff000)
#define PAGE_OFFSET(x) (x & BELOW_PAGE_SIZE)

#define PAGE_SHIFT 12
#define PAGE_ALIGN(Va) ((QWORD)((ULONG_PTR)(Va) & ~(PAGE_SIZE - 1)))
#define ADDRESS_AND_SIZE_TO_SPAN_PAGES(Va,Size) ((ULONG)((((ULONG_PTR)(Va) & (PAGE_SIZE -1)) + (Size) + (PAGE_SIZE - 1)) >> PAGE_SHIFT))

typedef struct _SYSTEM_HANDLE
{
	ULONG ProcessId;
	BYTE ObjectTypeNumber;
	BYTE Flags;
	USHORT Handle;
	PVOID Object;
	ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE, *PSYSTEM_HANDLE;

typedef struct _SYSTEM_HANDLE_INFORMATION2
{
	ULONG HandleCount;
	SYSTEM_HANDLE Handles[1];
} SYSTEM_HANDLE_INFORMATION2, *PSYSTEM_HANDLE_INFORMATION2;


//name spaces are like a container so its like saying ANYTHING inside a namespace belongs to the name X
//so to use anything in the namespace you just use the namespace name and then the variable or function!
namespace DMADevice
{
	//extern is just declaring that we have a variable by this name but its else where!
	//when declaring extern MAKE sure you declare it else where
	extern bool bConnected;
	extern DWORD dwAttachedProcessId;
	extern ULONG64 dwUnityPlayerBaseAddress;

	//declare the functions so we can use it all over!
	//i have added arguments so i dont need to worry about reading the status of the "check boxes" inside the function
	//and the equals just means this is the default value IF you dont use the arguments! so if you call Connect(); the 2 arguements will just be Connect(false,false);
	extern bool Connect(bool bMMapFile = false, bool bStealth = false, bool bRemoveOtherDMAConnections = false);

	extern void Disconnect();

	//make a function to just attach to a process so we can return an error if the process is not found or if you want to change process for another project? idk? dont need this but meh!
	extern bool AttachToProcessId(LPSTR szProcessName = REMOTE_PROCESS);

	extern bool CheckForModuleInsideProcessId(DWORD dwProcessId, LPCWSTR wszModuleName = L"vmm.dll");
	extern bool CloseHandleInProcess(DWORD dwProcessId, HANDLE hHandle);
	extern bool CloseDMAConnections(DWORD dwProcessId);
	extern bool DisconnectOtherConnections();

	template<typename U, typename P>DWORD MemRead(U lpAddress, P lpOutput, size_t uiSize, bool bFullReadRequired = true)
	{
		if (!dwAttachedProcessId || !bConnected || !lpAddress)
			return 0;

		DWORD dwBytesRead = 0;
		BOOL bRetn = (VMMDLL_MemReadEx(dwAttachedProcessId, (ULONG64)lpAddress, (PBYTE)lpOutput, uiSize, &dwBytesRead, VMMDLL_FLAG_NOCACHE | VMMDLL_FLAG_NOPAGING | VMMDLL_FLAG_NOCACHEPUT | VMMDLL_FLAG_ZEROPAD_ON_FAIL | VMMDLL_FLAG_NOPAGING_IO) && dwBytesRead != 0);
		if (!bRetn || (bFullReadRequired && dwBytesRead != uiSize))
			return dwBytesRead;

		return dwBytesRead;
	}
	template<typename Var, typename U>Var MemReadPtr(U lpAddress)
	{
		Var lpPtr = 0;
		if (MemRead(lpAddress, &lpPtr, sizeof(Var)))
			return lpPtr;
		return 0;
	}
	template<typename U, typename P>BOOL MemWrite(U lpAddress, P lpInput, size_t uiSize)
	{
		if (!dwAttachedProcessId || !bConnected || !lpAddress)
			return FALSE;

		return VMMDLL_MemWrite(dwAttachedProcessId, (ULONG64)lpAddress, (PBYTE)lpInput, uiSize);
	}
	template<typename U, typename P>BOOL MemWritePtr(U lpAddress, P lpInput)
	{
		if (!dwAttachedProcessId || !bConnected || !lpAddress)
			return FALSE;

		return VMMDLL_MemWrite(dwAttachedProcessId, (ULONG64)lpAddress, (PBYTE)&lpInput, sizeof(P));
	}

	bool MemReadUnityString(CUnityString *lpStringPtr, CUnityString* us);
}