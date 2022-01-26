#pragma once

//a struct data of what we want to save!
struct CSkillData
{
	bool m_bLvlEnabled;
	int m_iLevel;
};

extern CSkillData sSkillData[];

extern wchar_t* GetConfigSettingsFile();

//we use a header file to tell C++ that we have declared function callbacks in a CPP file but you cant include a CPP file without errors
extern INT_PTR CALLBACK Serial_Dialog_Callback(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
extern INT_PTR CALLBACK Main_Dialog_Callback(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
extern INT_PTR CALLBACK Skills_Dialog_Callback(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);