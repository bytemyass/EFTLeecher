#include "globals.h"



CUnityKeyCodes unityKC[] =
{
	{ KC_None,L"" },
	{ KC_Mouse0,L"L.M.Button" },
	{ KC_Mouse1,L"R.M.Button" },
	{ KC_Break,L"Break" },
	{ KC_Mouse2,L"M.M.Button" },
	{ KC_Mouse3,L"X1.Button" },
	{ KC_Mouse4,L"X2.Button" },
	{ KC_None,L"" },
	{ KC_Backspace,L"Backspace" },
	{ KC_Tab,L"Tab" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_Clear,L"Clear" },
	{ KC_Return,L"Enter" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_Shift,L"Shift" },//0x10
	{ KC_Control,L"Control" },
	{ KC_Menu,L"Menu" },
	{ KC_Pause,L"Pause" },
	{ KC_CapsLock,L"Caps Lock" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_Escape,L"Escape" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_Space,L"Space" },//0x20
	{ KC_PageUp,L"Page Up" },
	{ KC_PageDown,L"Page Down" },
	{ KC_End,L"End" },
	{ KC_Home,L"Home" },
	{ KC_LeftArrow,L"Left" },
	{ KC_UpArrow,L"Up" },
	{ KC_RightArrow,L"Right" },
	{ KC_DownArrow,L"Down" },
	{ KC_None,L"" },//Select
	{ KC_Print,L"Print" },
	{ KC_None,L"" },//Execute
	{ KC_None,L"" },//Print screen -- cant use unity dont support it
	{ KC_Insert,L"Insert" },
	{ KC_Delete,L"Delete" },
	{ KC_Help,L"Help" },
	{ KC_Alpha0,L"0" },//0x30
	{ KC_Alpha1,L"1" },
	{ KC_Alpha2,L"2" },
	{ KC_Alpha3,L"3" },
	{ KC_Alpha4,L"4" },
	{ KC_Alpha5,L"5" },
	{ KC_Alpha6,L"6" },
	{ KC_Alpha7,L"7" },
	{ KC_Alpha8,L"8" },
	{ KC_Alpha9,L"9" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },//0x40
	{ KC_A,L"A" },
	{ KC_B,L"B" },
	{ KC_C,L"C" },
	{ KC_D,L"D" },
	{ KC_E,L"E" },
	{ KC_F,L"F" },
	{ KC_G,L"G" },
	{ KC_H,L"H" },
	{ KC_I,L"I" },
	{ KC_J,L"J" },
	{ KC_K,L"K" },
	{ KC_L,L"L" },
	{ KC_M,L"M" },
	{ KC_N,L"N" },
	{ KC_O,L"O" },
	{ KC_P,L"P" },//0x50
	{ KC_Q,L"Q" },
	{ KC_R,L"R" },
	{ KC_S,L"S" },
	{ KC_T,L"T" },
	{ KC_U,L"U" },
	{ KC_V,L"V" },
	{ KC_W,L"W" },
	{ KC_X,L"X" },
	{ KC_Y,L"Y" },
	{ KC_Z,L"Z" },
	{ KC_LeftWindows,L"L.Windows" },
	{ KC_RightWindows,L"R.Windows" },
	{ KC_None,L"" },//Applications 
	{ KC_None,L"" },
	{ KC_None,L"" },//Sleep
	{ KC_Keypad0,L"Numpad 0" },//0x60
	{ KC_Keypad1,L"Numpad 1" },
	{ KC_Keypad2,L"Numpad 2" },
	{ KC_Keypad3,L"Numpad 3" },
	{ KC_Keypad4,L"Numpad 4" },
	{ KC_Keypad5,L"Numpad 5" },
	{ KC_Keypad6,L"Numpad 6" },
	{ KC_Keypad7,L"Numpad 7" },
	{ KC_Keypad8,L"Numpad 8" },
	{ KC_Keypad9,L"Numpad 9" },
	{ KC_KeypadMultiply,L"*" },
	{ KC_KeypadPlus,L"+" },
	{ KC_None,L"" },//Separator
	{ KC_KeypadMinus,L"-" },
	{ KC_KeypadPeriod,L"." },
	{ KC_KeypadDivide,L"/" },
	{ KC_F1,L"F1" },//0x70
	{ KC_F2,L"F2" },
	{ KC_F3,L"F3" },
	{ KC_F4,L"F4" },
	{ KC_F5,L"F5" },
	{ KC_F6,L"F6" },
	{ KC_F7,L"F7" },
	{ KC_F8,L"F8" },
	{ KC_F9,L"F9" },
	{ KC_F10,L"F10" },
	{ KC_F11,L"F11" },
	{ KC_F12,L"F12" },
	{ KC_None,L"" },//F13
	{ KC_None,L"" },//F14
	{ KC_None,L"" },//F15
	{ KC_None,L"" },//F16
	{ KC_None,L"" },//0x80
	{ KC_None,L"" },//F18
	{ KC_None,L"" },//F19
	{ KC_None,L"" },//F20
	{ KC_None,L"" },//F21
	{ KC_None,L"" },//F22
	{ KC_None,L"" },//F23
	{ KC_None,L"" },//F24
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_Numlock,L"Num Lock" },//0x90
	{ KC_ScrollLock,L"Scroll Lock" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_LeftShift,L"L.Shift" },//0xA0
	{ KC_RightShift,L"R.Shift" },
	{ KC_LeftControl,L"L.Control" },
	{ KC_RightControl,L"R.Control" },
	{ KC_LeftAlt,L"L.Alt" },
	{ KC_RightAlt,L"R.Alt" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_Semicolon,L";" },
	{ KC_Equals,L"=" },
	{ KC_Comma,L"," },
	{ KC_Minus,L"-" },
	{ KC_Period,L"." },
	{ KC_Slash,L"/" },
	{ KC_Quote,L"'" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_None,L"" },
	{ KC_LeftBracket,L"[" },
	{ KC_Pipe,L"|" },
	{ KC_RightBracket,L"]" },
	{ KC_Hash,L"#" },
	{ KC_BackQuote,L"`" },
};

//list of skill names
wchar_t *szSkillNames[Skills_Max] =
{
	L"Endurance",
	L"Strength",
	L"Vitality",
	L"Health",
	L"Stress Resistance",
	L"Metabolism",
	L"Immunity",
	L"Perception",
	L"Intellect",
	L"Attention",
	L"Charisma",
	L"Memory",
	L"Mag Drills",
	L"Pistol",
	L"Revolver",
	L"SMG",
	L"Assault",
	L"Shotgun",
	L"Sniper",
	L"LMG",
	L"HMG",
	L"Launcher",
	L"Attached Launcher",
	L"Throwing",
	L"Misc",
	L"Melee",
	L"DMR",
	L"Draw Master",
	L"Aim Master",
	L"Recoil Control",
	L"Trouble Shooting",
	L"Sniping",
	L"Covert Movement",
	L"Prone Movement",
	L"First Aid",
	L"Field Medicine",
	L"Surgery",
	L"Light Vests",
	L"Heavy Vests",
	L"Weapon Modding",
	L"Advanced Modding",
	L"NightOps",
	L"SilentOps",
	L"Lock Picking",
	L"Search",
	L"Weapon Treatment",
	L"Free Trading",
	L"Auctions",
	L"Clean Operations",
	L"Barter",
	L"Shadow Connections",
	L"Task Performance",
	L"Bear Assault Operations",
	L"Bear Authority",
	L"Bear AK Systems",
	L"Bear Heavy Caliber",
	L"Bear Raw Power",
	L"USEC AR Systems",
	L"USEC Deep Weapon Modding",
	L"USEC Long Range Optics",
	L"USEC Negotiations",
	L"USEC Tactics",
	L"Bot Reload",
	L"Bot Sound",
	L"Aim Drills",
	L"Hideout Management",
	L"Crafting"
};
class Matrix34
{
public:
	FVec4 vec0;
	FVec4 vec1;
	FVec4 vec2;

	Matrix34()
	{
	}
};
struct TransformAccessReadOnly
{
	ULONGLONG	pTransformData;
	int			index;
};
struct TransformData
{
	char _0x0000[0x18];			//0x0000
	ULONGLONG pTransformArray;	//0x0018
	ULONGLONG pTransformIndices;//0x0020
};//0x0028
const char *CUnityGameObject::GetObjectName(char *szOutput, size_t nSize)
{
	return (DMADevice::MemRead((DWORD64)((DWORD64)this + 0x60), szOutput, nSize)) ? szOutput : 0;
}
bool CUnityGameObject::IsObject(char *szObjectName)
{
	char szOutput[65] = { 0 };
	return (GetObjectName(szOutput) && strcmp(szOutput, szObjectName) == 0);
}
CUnityGameObject *CCamera::GetGameObject()
{
	return DMADevice::MemReadPtr<CUnityGameObject*>((DWORD_PTR)this + 0x30);
}
void *CUnityMonoBehaviourScript::GetComonent(char* szName)
{
	if (!this->m_lpComponent)
		return 0;

	CUnityMonoBehaviour lpMonoBehaviour = {};
	if (!DMADevice::MemRead(this->m_lpComponent, &lpMonoBehaviour, sizeof(CUnityMonoBehaviour)) || !lpMonoBehaviour.m_lpKlass)
		return 0;

	CUnityGameObject lpUnityGameObject = {};
	if (!DMADevice::MemRead(lpMonoBehaviour.m_lpKlass, &lpUnityGameObject, sizeof(CUnityGameObject)))
		return 0;

	return lpUnityGameObject.m_aComponents.GetByName(szName);
}
bool CMonoTransform::GetPosition(FVec3* vOutput)
{
	TransformData tfd = {};
	TransformAccessReadOnly tro = {};
	CMonoTransform lpTransformData = {};
	if (!DMADevice::MemRead(this, &lpTransformData, sizeof(CMonoTransform)) || !DMADevice::MemRead(lpTransformData.dwKlass + offsetof(CMonoTransform, dwMain), &tro, sizeof(TransformAccessReadOnly)) || !DMADevice::MemRead(tro.pTransformData, &tfd, sizeof(TransformData)))
		return false;

	int iIndex = tro.index;
	int* dwIndex = new int[iIndex + 1];
	Matrix34* matrix34 = new Matrix34[iIndex + 1];
	if (!dwIndex || !matrix34 || !DMADevice::MemRead(tfd.pTransformArray, matrix34, sizeof(Matrix34) * (iIndex + 1)) || !DMADevice::MemRead(tfd.pTransformIndices, dwIndex, sizeof(int) * (iIndex + 1)))
	{
		SAFE_DELETE_ARRAY(dwIndex);
		SAFE_DELETE_ARRAY(matrix34);
		return false;
	}

	const __m128 mulVec1 = { -2.000, -2.000, 2.000, 0.000 };
	const __m128 mulVec2 = { -2.000, 2.000, -2.000, 0.000 };
	const __m128 mulVec3 = { 2.000, -2.000, -2.000, 0.000 };
	int iCurrentIndex = dwIndex[iIndex];
	__m128 result = *(__m128*) & matrix34[iIndex].vec0;
	while (iCurrentIndex >= 0)
	{
		__m128 v10 = _mm_mul_ps(*(__m128*) & matrix34[iCurrentIndex].vec2, result);
		__m128 v11 = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34[iCurrentIndex].vec1), 0x00));
		__m128 v12 = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34[iCurrentIndex].vec1), 0x71));
		__m128 v13 = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34[iCurrentIndex].vec1), 0x8E));
		__m128 v14 = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34[iCurrentIndex].vec1), 0x55));
		__m128 v15 = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34[iCurrentIndex].vec1), 0xAA));
		__m128 v16 = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34[iCurrentIndex].vec1), 0xDB));
		__m128 var1 = _mm_mul_ps(_mm_sub_ps(_mm_mul_ps(_mm_mul_ps(v11, (__m128)mulVec3), v13), _mm_mul_ps(_mm_mul_ps(v14, (__m128)mulVec1), v16)), _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), -86)));
		__m128 var2 = _mm_mul_ps(_mm_sub_ps(_mm_mul_ps(_mm_mul_ps(v15, (__m128)mulVec1), v16), _mm_mul_ps(_mm_mul_ps(v11, (__m128)mulVec2), v12)), _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), 85)));
		__m128 var3 = _mm_mul_ps(_mm_sub_ps(_mm_mul_ps(_mm_mul_ps(v14, (__m128)mulVec2), v12), _mm_mul_ps(_mm_mul_ps(v15, (__m128)mulVec3), v13)), _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), 0)));
		result = _mm_add_ps(_mm_add_ps(_mm_add_ps(var1, var2), _mm_add_ps(var3, v10)), *(__m128*)(&matrix34[iCurrentIndex].vec0));
		iCurrentIndex = dwIndex[iCurrentIndex];
	}
	SAFE_DELETE_ARRAY(dwIndex);
	SAFE_DELETE_ARRAY(matrix34);
	*vOutput = FVec3(result.m128_f32[0], result.m128_f32[1], result.m128_f32[2]);
	return true;
}
bool CBifacialTransform::GetPosition(FVec3 *vOutput)
{
	if (_accumulatePositionAndRotation)
	{
		if (vOutput)
			*vOutput = _accumulatedPosition;
		return true;
	}
	if (__useImitation && uFunc__positionImitator)
	{
		//we cant use this :(
		return false;
	}

	if (_Transform)
	{
		CMonoTransform lpTransform = {};
		if (DMADevice::MemRead(this->_Transform, &lpTransform, sizeof(CMonoTransform), false))
			return this->_Transform->GetPosition(vOutput);
		return false;
	}
	return false;
}
CMonoTransform* CUnityMonoBehaviourScript::GetTransform()
{
	CUnityMonoBehaviour lpMonoBehaviour = {};
	CUnityGameObject lpUnityGameObject = {};
	if (!DMADevice::MemRead(this->m_lpComponent, &lpMonoBehaviour, sizeof(CUnityMonoBehaviour)) || !DMADevice::MemRead(lpMonoBehaviour.m_lpKlass, &lpUnityGameObject, sizeof(CUnityGameObject)))
		return 0;

	return lpUnityGameObject.m_aComponents.GetTransform();
}
bool CUnityMonoBehaviourScript::GetPosition(FVec3* vOutput)
{
	CMonoTransform* lpTransform = (CMonoTransform*)this->GetTransform();
	if (lpTransform == 0)
		return false;

	return lpTransform->GetPosition(vOutput);
}