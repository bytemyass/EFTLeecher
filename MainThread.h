#pragma once
#include <atomic>

struct CPlayerData
{
	bool m_bSameGroup : 1;
	bool m_bBasePositionVaild : 1;
	bool m_bBoneIsVaild : 1;

	CPlayer* m_lpPointer;

	FVec3 m_vBonePosition;
	FVec3 m_vBasePosition;
};

struct CThreadData
{
	BOOL m_bGameRunnning;

	HWND m_hDlg;

	std::atomic<int> m_iBone;

	CPlayer* m_lpLocalPlayerPointer;
	CGameWorld *m_lpMainWorldPointer;
	CUnityGameObject* m_lpMainCameraGameObject;

	int m_iPlayerObjectCount;
	CPlayerData** m_lpPlayerObjects;

	DWORD64 m_dwInputManager;
};

extern DWORD WINAPI MainThread(LPVOID lpParam);
extern DWORD WINAPI PlayerThread(LPVOID lpParam);
extern DWORD WINAPI AimbotThread(LPVOID lpParam);