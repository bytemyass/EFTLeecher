#include "globals.h"

//we set the variable inside the namespace X to what ever we want so that the compiler CAN set the value before executed
bool DMADevice::bConnected = false;
DWORD DMADevice::dwAttachedProcessId = NULL;
ULONG64 DMADevice::dwUnityPlayerBaseAddress = NULL;


bool DMADevice::Connect(bool bMMapFile, bool bStealth, bool bRemoveOtherDMAConnections)
{
	//check if we already connected to the dma device?
	if (bConnected)
		return true;

	//we declare the return value here so we can return any status we want if something fail's!
	bool bReturnStatus = true;

	//the default argument count is 3 which is ["", "-device", "fpga"]
	unsigned int iArgumentCount = 3;

	//set the arguments!
	LPSTR args[7] = { "", "-device", "fpga", "-max", 0, "-memmap", "mmap.txt" };

	//lets remove ALL other connections first?
	if(bRemoveOtherDMAConnections)
	{
		//check the status and see if we DID close DMA connection's
		if (DisconnectOtherConnections() == false)
		{
			MessageBoxA(0, "Could not close other DMA connection's are you sure there is one open?", 0, 0);

			//now i dont know if we should return false to say NOT to connect because what if they HAVNT got a connection open?
			return false;
		}
	}

	//see if we want to use the map file
	if (bMMapFile)
	{
		//we set to false because we will set to true if ALL checks passed so its much easyer to keep track!
		bReturnStatus = false;

		//create a buffer for the memory size from map
		char szMapMemory[64] = { 0 };

		//CreateFile ether creates a file or opens an existing file that depends on the flags given with dwCreationDisposition
		HANDLE hFile = CreateFileA("mmap.txt", FILE_GENERIC_READ, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		
		//we check if we have a handle for this file
		if (hFile != INVALID_HANDLE_VALUE)
		{
			//we grab the file size
			DWORD dwFileSize = GetFileSize(hFile, NULL);

			//check if the file size is BIGGER then 0
			if (dwFileSize > 0)
			{
				//create a file buffer to store the file into memory so we can read the file or copy the file into the buffer this can be BYTE or char but byte is better because BYTE allows -256 to 256 char only allow 0 to 255
				//we do plus 1 because we want file buffer + a null terminated char (WE DONT NEED IT because we know the file size but meh memory can be a dangerous thing if fucked up!)
				BYTE* lpFileBuffer = new BYTE[dwFileSize + 1];

				//we check if the system has the memory for this file size i mean ALL systems should have atleast 10mb memory but we ALWAYS check when dealing with memory!
				if (lpFileBuffer != NULL)
				{
					//create a variable to store how many bytes / char's we have read from the file
					DWORD dwNumberBytesRead = 0;
					if (ReadFile(hFile, lpFileBuffer, dwFileSize, &dwNumberBytesRead, NULL))
					{
						//strrchr reads the whole buffer AKA file buffer and finds the LAST "needle AKA -" in the file and returns the string + - in the file!
						char *szLastMemoryLine = strrchr((char*)lpFileBuffer, '-');
						if (szLastMemoryLine != NULL)
						{
							//szLastMemoryLine should now contain - "- MEMORY_ADDRESS"

							//so we change the minus and the space to 0 and x so it should now be 0xMEMORY_ADDRESS which we can now use? or should be able to!
							szLastMemoryLine[0] = '0';
							szLastMemoryLine[1] = 'x';

							//now copy the LAST memory map so we can use it
							strcpy_s(szMapMemory, szLastMemoryLine);

							//we set our return status to true because we set the first argument to true meaning we want to use the map file and we can use it because we have everything we need?
							bReturnStatus = true;

							//we now change the argument count because we are using ALOT more!
							iArgumentCount = 7;
						}
					}
					//right ill take a min to explain this part because SOME are ALWAYS confused about delete [] and delete and free
					//delete [] DELETES an ARRAY that was allocated so any memory made with NEW [SIZE] you are ALWAYS required to delete it as an ARRAY!
					//delete DELETES a memory that is created with just NEW you should never delete NEW memory with delete [] because that memory is not an array its just MEMORY pointer
					//so any time you create memory or create memory AKA "new VARIABLE_TYPE[]" you should do "delete []" but if you do "new VARABLE_TYPE" you should just delete
					delete[] lpFileBuffer;
				}
			}

			//we have to close a handle to the file we have opened so the system can take control of it!
			CloseHandle(hFile);
		}
		else
		{
			//we couldnt get a handle to the file so we check if the file is found!
			if (GetLastError() == ERROR_FILE_NOT_FOUND)
			{
				//the file is NOT found!
				MessageBoxA(0, "mmap.txt is not found please make sure mmap.txt is valid and has valid memory map", 0, 0);

				//return false so we DONT connect to the dma device with the wrong arguments and give the wrong idea!
				return false;
			}
		}
		//we now set the argument to the memory map file found?
		args[4] = { szMapMemory };
	}

	//we check if the results are in and they are false because if false then we cant connect because something is wrong?
	if (bReturnStatus == false)
	{
		//i dont know what to say? maybe tell them run as admin make sure the file is valid? idk? LOL!
		MessageBoxA(0, "mmap.txt is not found please make sure mmap.txt is valid and has valid memory map", 0, 0);

		//do i need to explain this?
		return false;
	}

	//now make a connection <3
	if (!VMMDLL_Initialize(iArgumentCount, args))
	{
		//give them a message i mean we have to tell them about the cable length i mean whos stupid to have a cable length of like 4meters?(LOL!)
		MessageBoxA(0, "Failed to connect to the DMA Device make sure your cable is NOT to long and is able to connect to the DMA Device", 0, 0);

		//do i need to explain this?
		return false;
	}

	//do we want to force clear the "master abort flags?" meaning stealth? so there NO CHANCE for the flags to be set?
	if (bStealth)
	{
		//we need variables to save the values
		ULONG64 qwID = 0, qwVersionMajor = 0, qwVersionMinor = 0;

		//we ask nicely for the results of EACH request AKA ID, Major version, Minor version
		if (!VMMDLL_ConfigGet(LC_OPT_FPGA_FPGA_ID, &qwID) ||
			!VMMDLL_ConfigGet(LC_OPT_FPGA_VERSION_MAJOR, &qwVersionMajor) ||
			!VMMDLL_ConfigGet(LC_OPT_FPGA_VERSION_MINOR, &qwVersionMinor))
		{
			//display an error?
			MessageBoxA(0, "Failed to get your FPGA Version are you connected?", 0, 0);

			//because a connection was made we need to now close it :(
			VMMDLL_Close();

			//do i need to explain this?
			return false;
		}
		if (!((qwVersionMajor >= 4) && ((qwVersionMajor >= 5) || (qwVersionMinor >= 7))))
		{
			//display an error?
			MessageBoxA(0, "Your version of the FPGA can not use the stealth function please disable or update your FPGA board to the lastest version", 0, 0);

			//because a connection was made we need to now close it :(
			VMMDLL_Close();

			//do i need to explain this?
			return false;
		}
		//create a variable to store data
		LC_CONFIG LcConfig = {};

		//set our leech core config version
		LcConfig.dwVersion = LC_CONFIG_VERSION;

		//and the device name the device name is existing because we have already set up a connection but if you want to be anal just use FPGA or there device
		strcpy_s(LcConfig.szDevice, "existing");

		//now create a standalone version of leech core ourself
		HANDLE hLeechCore = LcCreate(&LcConfig);

		//check the return value LcCreate will return NULL if failed to "create" and a handle or "memory" to the created leech core
		if (hLeechCore == NULL)
		{
			//display an error?
			MessageBoxA(0, "Could not create or open an existing device to leech core please retry if this problem keeps happening disable stealth option", 0, 0);

			//because a connection was made we need to now close it :(
			VMMDLL_Close();

			//do i need to explain this?
			return false;
		}
		//please dont ask me why or what this shit is because its what ufrisk wants you to send to the config to reset the "pci config space flags"
		BYTE bBytes[4] = { 0x10, 0x00, 0x10, 0x00 };

		//now we send a command to the device to tell it todo a command which is cleaning the PCI config space flags remember i dont know how all this shit works all i know is this works and he shown it in his code want more info on how this works ask ufrisk lol
		//https://github.com/ufrisk/MemProcFS/blob/master/vmm_example/vmmdll_example.c#L184 link to how he is doing it!
		LcCommand(hLeechCore, LC_CMD_FPGA_CFGREGPCIE_MARKWR | 0x002, 4, bBytes, NULL, NULL);

		//close the handle to the leech core we have opened this will NOT close the connection as they have a counter on how many times a connection has been made so we have made 2 but only closing 1? so meaning they will keep it open for us!
		LcClose(hLeechCore);
	}

	//copy the return status to tell us if connection was complete!
	bConnected = bReturnStatus;

	//everything is complete we have a connection and we have set up everything we need :)
	return bReturnStatus;
}
bool DMADevice::AttachToProcessId(LPSTR szProcessName)
{
	//wait we trying to look for a process without a connection this is not a good thing this is bad! but shouldnt ever happen but always good to check?
	if (bConnected == false)
		return false;

	//we grab a process id from the name some games use 2 process id's or processes like pubg it runs 2 of the same exe names so you have to filter them
	if (VMMDLL_PidGetFromName(szProcessName, &dwAttachedProcessId) == FALSE)
		return false;

	//grab unityplayer.dll it should ALWAYS be found if the process is unity player game!
	dwUnityPlayerBaseAddress = VMMDLL_ProcessGetModuleBase(dwAttachedProcessId, L"UnityPlayer.dll");

	//check if found!
	if (dwUnityPlayerBaseAddress == 0)
	{
		//set it to null because we no longer want to be attached lol!
		dwAttachedProcessId = NULL;
		return false;
	}
	//we return true if dwAttachedProcessId is ANYTHING but NULL and false if its NULL same with unityplayer.dll address
	return (dwAttachedProcessId != NULL && dwUnityPlayerBaseAddress != NULL);
}
void DMADevice::Disconnect()
{
	//we have no connection!
	bConnected = false;

	//reset the attached process id
	dwAttachedProcessId = NULL;

	//tell the DMA to close the device
	VMMDLL_Close();
}
bool DMADevice::CheckForModuleInsideProcessId(DWORD dwProcessId, LPCWSTR wszModuleName)
{
	//create a snapshot list of the modules inside the process from process id
	HANDLE hProcessList = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);

	//we couldnt get the list?
	if (hProcessList == INVALID_HANDLE_VALUE)
		return false;

	//make a variable for storing the results
	MODULEENTRY32 me32 = {};

	//tell windows the size
	me32.dwSize = sizeof(MODULEENTRY32);

	//grab the first module inside the list!
	if (!Module32First(hProcessList, &me32))
	{
		//ALWAYS clean up system handles
		CloseHandle(hProcessList);
		return false;
	}


	do{
		//compare the module name to the module we want
		if (_wcsicmp(me32.szModule, wszModuleName) == 0)
		{
			//ALWAYS clean up system handles
			CloseHandle(hProcessList);

			//success!
			return true;
		}

		//grab the next module in the list! if there is one!
	} while (Module32Next(hProcessList, &me32));

	//ALWAYS clean up system handles
	CloseHandle(hProcessList);
	return false;
}
using fnFreeCall = DWORD_PTR(__fastcall*)(...);
template<typename ...Params>NTSTATUS NtRoutine(const char* szName, Params &&... params)
{
	HMODULE hNtDll = GetModuleHandleA("ntdll.dll");
	if (hNtDll == 0)
		return STATUS_NOT_FOUND;

	auto fn = (fnFreeCall)GetProcAddress(hNtDll, szName);
	if (fn == 0)
		return STATUS_NOT_FOUND;

	return (NTSTATUS)fn(std::forward<Params>(params) ...);
}
//simple API calls to ntdll for some reason ntdll is different on MOST version of windows so we use a simple API to just grab the "function" and forward the arguments to it really simple nothing much to explain
#define NtQuerySystemInformation(...) NtRoutine("NtQuerySystemInformation", __VA_ARGS__)
#define NtDuplicateObject(...) NtRoutine("NtDuplicateObject", __VA_ARGS__)
#define NtQueryObject(...) NtRoutine("NtQueryObject", __VA_ARGS__)

bool DMADevice::CloseHandleInProcess(DWORD dwProcessId, HANDLE hHandle)
{
	//we open the process that we require access to we want all access creating threads,memory read/write query process etc etc
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);

	//for some reason we couldnt open this process? is it system did they run as admin? wtf going on?
	if (hProcess == NULL)
		return false;

	//now grab the close handle address thanks to windows for the shared address space of system modules we dont need to worry about this being wrong when found locally(this process)
	LPTHREAD_START_ROUTINE Address_CloseHandle = (LPTHREAD_START_ROUTINE)GetProcAddress(LoadLibrary(L"Kernel32.dll"), "CloseHandle");

	//WAIT A SEC? closehandle is not found WTF we running on shitty mac?
	if (Address_CloseHandle == NULL)
	{
		//ALWAYS clean up system handles
		CloseHandle(hProcess);
		return false;
	}

	//we create a remote thread on the process when executing code you are ALWAYS required to have it in a thread ether main thread or a newly created thread but since they dont have anticheat protection we just use normal create thread <3
	HANDLE hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, Address_CloseHandle, hHandle, 0, 0);

	//ermm? couldnt create a thread on there process? wtf?
	if (hRemoteThread == NULL)
	{
		//ALWAYS clean up system handles
		CloseHandle(hProcess);
		return false;
	}
	//WAIT for the thread to finish executing or running and we wait for infinite you can wait for X ammount of time but its best to wait for it to finish fully before we give the status!
	WaitForSingleObject(hRemoteThread, INFINITE);

	//ALWAYS clean up system handles
	CloseHandle(hRemoteThread);
	CloseHandle(hProcess);

	//success!
	return true;
}
bool DMADevice::CloseDMAConnections(DWORD dwProcessId)
{
	//use 2mb for default size we can use more if required!
	DWORD dwSize = 0x2000;

	//variable for the size if we need more! (everyone always need's more!)
	DWORD dwRequired = 0;

	//make some memory because we cant use a variable well we can but it could be like 50mb in size which would then require the exe to be 50mb lol but make memory its simple easy and quick!
	SYSTEM_HANDLE_INFORMATION2* lpSysHandleInformation = (SYSTEM_HANDLE_INFORMATION2*)malloc(dwSize);

	//wait we cant get enough memory? FML fail then?
	if (lpSysHandleInformation == NULL)
		return false;

	//grab all handle objects on the system
	NTSTATUS ntStatus = NtQuerySystemInformation(16/*SystemHandleInformation*/, lpSysHandleInformation, dwSize, &dwRequired);

	//we failed? todo this?
	if (!NT_SUCCESS(ntStatus))
	{
		//oh we dont have enough buffer size thats not an issue lets make more room! we also check to make sure the API returned the required size
		if (ntStatus != STATUS_INFO_LENGTH_MISMATCH || !dwRequired)
		{
			//ALWAYS clean up memory!
			free(lpSysHandleInformation);
			return false;
		}
		// The size was not enough so clean up the old stuff!
		free(lpSysHandleInformation);

		//lets change the size now much bigger plus added room!
		dwSize = dwRequired + 1024;

		//make more memory more room!
		lpSysHandleInformation = (SYSTEM_HANDLE_INFORMATION2*)malloc(dwSize);

		//always check to make sure they have made the memory before accessing it :)
		if (lpSysHandleInformation == 0)
		{
			return false;
		}

		//now lets call it again with a bigger size! this should not fail anymore!
		ntStatus = NtQuerySystemInformation(16/*SystemHandleInformation*/, lpSysHandleInformation, dwSize, &dwRequired);

		//am i seeing bullshit again?! just fail this time!
		if (!NT_SUCCESS(ntStatus))
		{
			//ALWAYS clean up memory!
			free(lpSysHandleInformation);

			return false;
		}
	}

	//we memory enough to get the type info so make it here so we dont have to keep making it per object and we can just reuse the buffer
	POBJECT_TYPE_INFORMATION lpObjectTypeInfo = (POBJECT_TYPE_INFORMATION)malloc(0x5000);
	if (lpObjectTypeInfo == 0)
	{
		//ALWAYS clean up memory!
		free(lpSysHandleInformation);

		//we dont have enough memory? so tell them its not working :(
		return false;
	}

	//now create a loop for all the system handles and do some checks!
	for (int i = 0; i < lpSysHandleInformation->HandleCount; i++)
	{
		//get the handle from the index i
		SYSTEM_HANDLE handle = lpSysHandleInformation->Handles[i];

		//check the object type the process id and the process id!
		if (handle.ObjectTypeNumber != 10 && handle.ProcessId > 4 && handle.ProcessId == dwProcessId)
		{
			//we open the process that has the handle so we can duplate it
			HANDLE hProcessHandle = OpenProcess(PROCESS_DUP_HANDLE, FALSE, handle.ProcessId);

			//we could not do this SHIT then continue and hope that we find what we look for!
			if (hProcessHandle == 0)
				continue;

			//make a variable to hold the handle data
			HANDLE hDupHandle = INVALID_HANDLE_VALUE;

			//duplicate the object aka copy the handle, handles are process based so you CANT use another processes handles UNLESS you ask for it and duplicate it!
			if (!NT_SUCCESS(NtDuplicateObject(hProcessHandle, handle.Handle, GetCurrentProcess(), &hDupHandle, 0, 0, DUPLICATE_SAME_ACCESS)))
			{
				//always close and clean up handles!
				CloseHandle(hProcessHandle);
				continue;
			}

			//clear the buffer we reuse so it has nothing from the old!
			ZeroMemory(lpObjectTypeInfo, 0x5000);

			//just set this to null we dont need it or want to use it but some arguments are required!
			dwRequired = 0;

			//now query the handle object
			if (!NT_SUCCESS(NtQueryObject(hDupHandle, ObjectTypeInformation, lpObjectTypeInfo, 0x5000, &dwRequired)))
			{
				//always close and clean up handles!
				CloseHandle(hProcessHandle);
				CloseHandle(hDupHandle);
				continue;
			}

			//we check to see if this object type is a FILE because when opening a device or a folder or anything todo with file system its ALWAYS a file type!
			if (wcscmp(lpObjectTypeInfo->TypeName.Buffer, L"File") != 0)
			{
				//always close and clean up handles!
				CloseHandle(hProcessHandle);
				CloseHandle(hDupHandle);
				continue;
			}

			//clear the buffer we reuse so it has nothing from the old!
			ZeroMemory(lpObjectTypeInfo, 0x5000);

			//convert the object type info to name information
			POBJECT_NAME_INFORMATION lpObjectNameInfo = (POBJECT_NAME_INFORMATION)lpObjectTypeInfo;

			//again query the object info but this time we are after the NAME now the type name
			if (!NT_SUCCESS(NtQueryObject(hDupHandle, ObjectNameInformation, lpObjectTypeInfo, 0x5000, &dwRequired)))
			{
				//always close and clean up handles!
				CloseHandle(hProcessHandle);
				CloseHandle(hDupHandle);
				continue;
			}

			//now we compare the object name info to device DMA device connects with Device\\000X X = an id of the device and sometimes WDeviceW000 as well no idea why but windows converts \\ to W? confused maybe api bug?
			if (wcsncmp(lpObjectNameInfo->Name.Buffer, L"\\Device\\000", wcslen(L"\\Device\\000")) == 0 || 
				wcsncmp(lpObjectNameInfo->Name.Buffer, L"WDeviceW000", wcslen(L"WDeviceW000")) == 0)
			{
				//keep a backup of what we found
				DWORD dwDMAProcessId = (DWORD)handle.ProcessId;
				HANDLE hDeviceHandle = (HANDLE)handle.Handle;

				//clean up everything because surely they should not be any other connections but one.....?

				//ALWAYS clean up memory!
				free(lpSysHandleInformation);
				free(lpObjectTypeInfo);

				//always close and clean up handles!
				CloseHandle(hProcessHandle);
				CloseHandle(hDupHandle);

				//now process the "disconnection request or force disconnection"
				return CloseHandleInProcess(dwDMAProcessId, hDeviceHandle);
			}

			//always close and clean up handles!
			CloseHandle(hProcessHandle);
			CloseHandle(hDupHandle);
		}
	}
	//ALWAYS clean up memory!
	free(lpObjectTypeInfo);
	free(lpSysHandleInformation);
	return false;
}
bool DMADevice::DisconnectOtherConnections()
{
	//we create a list handle to grab ALL current processes on the current system
	HANDLE hProcessList = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (hProcessList == INVALID_HANDLE_VALUE)
		return false;

	//we have a variable to hold the current "process"
	PROCESSENTRY32 pe32 = {};

	//we set the size
	pe32.dwSize = sizeof(PROCESSENTRY32);

	//we grab the FIRST process in the list!
	if (!Process32First(hProcessList, &pe32))
	{
		CloseHandle(hProcessList);
		return false;
	}

	//save our current process id
	DWORD dwCurrentProcessId = GetCurrentProcessId();

	do {
		//we first check to make sure the process id is bigger then 5 any process lower then 5 is a system process and we shouldnt mess with system processes!
		//then we compare to make sure the process is NOT ours!
		//then we check for the required module inside the process which is vmm.dll
		if (pe32.th32ProcessID > 5 && pe32.th32ProcessID != dwCurrentProcessId && CheckForModuleInsideProcessId(pe32.th32ProcessID))
		{
			//always close handles when done with it allows the system to be clean!
			CloseHandle(hProcessList);

			//close the dma connection and return the status
			return CloseDMAConnections(pe32.th32ProcessID);
		}
		//grab the next process in the list
	} while (Process32Next(hProcessList, &pe32));

	//always close handles when done with it allows the system to be clean!
	CloseHandle(hProcessList);

	//no process found with a DMA connection (well one we can find) so lets just say we closed them DMA will fail to connect if there is one open!
	return true;
}

bool DMADevice::MemReadUnityString(CUnityString *lpStringPtr, CUnityString* us)
{
	if (!dwAttachedProcessId || !bConnected || !lpStringPtr)
		return false;

	//because unity strings can be REALLY long or REALLY short we use mem read scatter ufrisk says its faster?
	DWORD dwNumPages = ADDRESS_AND_SIZE_TO_SPAN_PAGES((QWORD)lpStringPtr, sizeof(CUnityString));

	//get the page address PAGE ADDRESS is inline with 0x1000 normally all systems are set like this but some change it which they shouldnt
	QWORD qwPageAddress = PAGE_ALIGN((QWORD)lpStringPtr);

	//now get the offset, the offset is the last 3 char numbers hex on the address so 0x1337 offset will be 0x0337
	DWORD dwPageOffset = PAGE_OFFSET((QWORD)lpStringPtr);

	//make 3 scatter memory requests
	PPMEM_SCATTER ppMEMs;

	//create memory and init the scatters
	if (!LcAllocScatter1(3, &ppMEMs))
		return false;

	//EACH scatter address needs to be inline with 0x1000 + (i * 0x1000)
	for (int i = 0; i < dwNumPages; i++)
		ppMEMs[i]->qwA = (qwPageAddress + (i << PAGE_SHIFT));

	//send the request to the device
	DWORD dwProcessedCount = VMMDLL_MemReadScatter(dwAttachedProcessId, ppMEMs, dwNumPages, VMMDLL_FLAG_NOCACHE | VMMDLL_FLAG_NOPAGING | VMMDLL_FLAG_NOCACHEPUT | VMMDLL_FLAG_ZEROPAD_ON_FAIL);

	//check how many pages we have processed
	if (dwProcessedCount > 0)
	{
		//get the current buffer size
		DWORD cb = min(sizeof(CUnityString), PAGE_SIZE - dwPageOffset);

		//convert the buffer to BYTES because bytes is 1 and pointer is 8
		LPBYTE lpBuffer = (LPBYTE)us;

		//loop the processed requests the pages we have got
		for (int i = 0; i < dwProcessedCount; i++)
		{
			//is this request finished or valid?
			if (!ppMEMs[i]->f)
				continue;

			//copy the buffer to our output buffer
			memcpy(lpBuffer, (ppMEMs[i]->pb + dwPageOffset), cb);

			//move the buffer up!
			lpBuffer += cb;

			//change the current buffer size to PAGE SIZE
			cb = PAGE_SIZE;

			//check IF we are below PAGE SIZE
			if (((dwPageOffset + sizeof(CUnityString)) & 0xfff))
			{
				//set the current buffer size to the len size left
				cb = ((dwPageOffset + sizeof(CUnityString)) & 0xfff);
			}
			//reset the page offset because we reading now from the start of a page..
			dwPageOffset = 0;
		}
		//clean up the memory and scatter required
		LcMemFree(ppMEMs);

		//set to null we dont need to but lets!
		ppMEMs = 0;

		//check the buffer for validation so the string size should be extactly the same as whats in the buffer no more no less!
		return (wcslen(us->szString) == us->dwStringSize);
	}
	//clean up the memory and scatter required
	LcMemFree(ppMEMs);

	//set to null we dont need to but lets!
	ppMEMs = 0;

	//didnt do as what we needed?
	return false;
}