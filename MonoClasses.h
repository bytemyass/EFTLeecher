#pragma once
#include <math.h>

#define CLASS_MonoBehaviour 68	//0x44
#define CLASS_MonoTransform 120	//0x80

extern wchar_t *szSkillNames[];

enum KeyCode
{
	KC_None,
	KC_Backspace = 8,
	KC_Delete = 127,
	KC_Tab = 9,
	KC_Clear = 12,
	KC_Return,
	KC_Pause = 19,
	KC_Escape = 27,
	KC_Space = 32,
	KC_Keypad0 = 256,
	KC_Keypad1,
	KC_Keypad2,
	KC_Keypad3,
	KC_Keypad4,
	KC_Keypad5,
	KC_Keypad6,
	KC_Keypad7,
	KC_Keypad8,
	KC_Keypad9,
	KC_KeypadPeriod,
	KC_KeypadDivide,
	KC_KeypadMultiply,
	KC_KeypadMinus,
	KC_KeypadPlus,
	KC_KeypadEnter,
	KC_KeypadEquals,
	KC_UpArrow,
	KC_DownArrow,
	KC_RightArrow,
	KC_LeftArrow,
	KC_Insert,
	KC_Home,
	KC_End,
	KC_PageUp,
	KC_PageDown,
	KC_F1,
	KC_F2,
	KC_F3,
	KC_F4,
	KC_F5,
	KC_F6,
	KC_F7,
	KC_F8,
	KC_F9,
	KC_F10,
	KC_F11,
	KC_F12,
	KC_F13,
	KC_F14,
	KC_F15,
	KC_Alpha0 = 48,
	KC_Alpha1,
	KC_Alpha2,
	KC_Alpha3,
	KC_Alpha4,
	KC_Alpha5,
	KC_Alpha6,
	KC_Alpha7,
	KC_Alpha8,
	KC_Alpha9,
	KC_Exclaim = 33,
	KC_DoubleQuote,
	KC_Hash,
	KC_Dollar,
	KC_Percent,
	KC_Ampersand,
	KC_Quote,
	KC_LeftParen,
	KC_RightParen,
	KC_Asterisk,
	KC_Plus,
	KC_Comma,
	KC_Minus,
	KC_Period,
	KC_Slash,
	KC_Colon = 58,
	KC_Semicolon,
	KC_Less,
	KC_Equals,
	KC_Greater,
	KC_Question,
	KC_At,
	KC_LeftBracket = 91,
	KC_Backslash,
	KC_RightBracket,
	KC_Caret,
	KC_Underscore,
	KC_BackQuote,
	KC_A,
	KC_B,
	KC_C,
	KC_D,
	KC_E,
	KC_F,
	KC_G,
	KC_H,
	KC_I,
	KC_J,
	KC_K,
	KC_L,
	KC_M,
	KC_N,
	KC_O,
	KC_P,
	KC_Q,
	KC_R,
	KC_S,
	KC_T,
	KC_U,
	KC_V,
	KC_W,
	KC_X,
	KC_Y,
	KC_Z,
	KC_LeftCurlyBracket,
	KC_Pipe,
	KC_RightCurlyBracket,
	KC_Tilde,
	KC_Numlock = 300,
	KC_CapsLock,
	KC_ScrollLock,
	KC_RightShift,
	KC_LeftShift,
	KC_RightControl,
	KC_LeftControl,
	KC_RightAlt,
	KC_LeftAlt,
	KC_LeftCommand = 310,
	KC_LeftApple = 310,
	KC_LeftWindows,
	KC_RightCommand = 309,
	KC_RightApple = 309,
	KC_RightWindows = 312,
	KC_AltGr,
	KC_Help = 315,
	KC_Print,
	KC_SysReq,
	KC_Break,
	KC_Menu,
	KC_Mouse0 = 323,
	KC_Mouse1,
	KC_Mouse2,
	KC_Mouse3,
	KC_Mouse4,
	KC_Mouse5,
	KC_Mouse6,
	KC_Shift = (KC_RightShift | KC_LeftShift),
	KC_Control = (KC_RightControl | KC_LeftControl)
};

struct CUnityKeyCodes
{
	KeyCode kc;
	wchar_t *KeyName;
};

extern CUnityKeyCodes unityKC[];

enum EHumanBones
{
	Empty = 0,
	IKController,
	Mesh,
	Vest_0,
	Vest_1,
	backpack,
	backpack_0,
	backpack_1,
	backpack_2,
	razgruz,
	razgruz_0,
	razgruz_1,
	razgruz_2,
	Root_Joint,
	HumanPelvis,
	HumanLThigh1,
	HumanLThigh2,
	HumanLCalf,
	HumanLFoot,
	HumanLToe,
	HumanRThigh1,
	HumanRThigh2,
	HumanRCalf,
	HumanRFoot,
	HumanRToe,
	Bear_Feet,
	USEC_Feet,
	BEAR_feet_1,
	weapon_holster_pistol,
	HumanSpine1,
	HumanGear1,
	HumanGear2,
	HumanGear3,
	HumanGear4,
	HumanGear4_1,
	HumanGear5,
	HumanSpine2,
	HumanSpine3,
	IK_S_LForearm1,
	IK_S_LForearm2,
	IK_S_LForearm3,
	IK_S_LPalm,
	IK_S_LDigit11,
	IK_S_LDigit12,
	IK_S_LDigit13,
	IK_S_LDigit21,
	IK_S_LDigit22,
	IK_S_LDigit23,
	IK_S_LDigit31,
	IK_S_LDigit32,
	IK_S_LDigit33,
	IK_S_LDigit41,
	IK_S_LDigit42,
	IK_S_LDigit43,
	IK_S_LDigit51,
	IK_S_LDigit52,
	IK_S_LDigit53,
	XYZ,
	LCollarbone_anim,
	RCollarbone_anim,
	RCollarbone_anim_XYZ,
	Weapon_root_3rd_anim,
	Weapon_root_3rd_anim_XYZ_1,
	Bend_Goal_Left,
	Bend_Goal_Right,
	Bend_Goal_Right_XYZ_1,
	HumanRibcage,
	IK_LForearm1,
	IK_LForearm2,
	IK_LForearm3,
	IK_LPalm,
	IK_LDigit11,
	IK_LDigit12,
	IK_LDigit13,
	IK_LDigit21,
	IK_LDigit22,
	IK_LDigit23,
	IK_LDigit31,
	IK_LDigit32,
	IK_LDigit33,
	IK_LDigit41,
	IK_LDigit42,
	IK_LDigit43,
	IK_LDigit51,
	IK_LDigit52,
	IK_LDigit53,
	Camera_animated,
	CameraContainer,
	Cam,
	HumanLCollarbone,
	HumanLUpperarm,
	HumanLForearm1,
	HumanLForearm2,
	HumanLForearm3,
	HumanLPalm,
	HumanLDigit11,
	HumanLDigit12,
	HumanLDigit13,
	HumanLDigit21,
	HumanLDigit22,
	HumanLDigit23,
	HumanLDigit31,
	HumanLDigit32,
	HumanLDigit33,
	HumanLDigit41,
	HumanLDigit42,
	HumanLDigit43,
	HumanLDigit51,
	HumanLDigit52,
	HumanLDigit53,
	HumanRCollarbone,
	HumanRUpperarm,
	HumanRForearm1,
	HumanRForearm2,
	HumanRForearm3,
	HumanRPalm,
	HumanRDigit11,
	HumanRDigit12,
	HumanRDigit13,
	HumanRDigit21,
	HumanRDigit22,
	HumanRDigit23,
	HumanRDigit31,
	HumanRDigit32,
	HumanRDigit33,
	HumanRDigit41,
	HumanRDigit42,
	HumanRDigit43,
	HumanRDigit51,
	HumanRDigit52,
	HumanRDigit53,
	Weapon_root,
	HumanNeck,
	HumanHead,
	HumanBackpack,
	weapon_holster,
	weapon_holster1,
	Camera_animated_3rd,
	BONE_MAX
};

enum CEProceduralAnimationMask
{
	Breathing = 1,//0x000000[0x000004]
	Walking = 2,//0x000000[0x000004]
	MotionReaction = 4,//0x000000[0x000004]
	ForceReaction = 8,//0x000000[0x000004]
	Shooting = 16,//0x000000[0x000004]
	DrawDown = 32,//0x000000[0x000004]
	Aiming = 64,//0x000000[0x000004]
};
enum CEDoorState : BYTE
{
	DS_Locked = 1,//0x000000[0x000001]
	DS_Shut = 2,//0x000000[0x000001]
	DS_Open = 4,//0x000000[0x000001]
	DS_Interacting = 8,//0x000000[0x000001]
	DS_Breaching = 16,//0x000000[0x000001]
};
enum CESkillId : BYTE
{
	Endurance = 0,//0x000000[0x000001]
	Strength = 1,//0x000000[0x000001]
	Vitality = 2,//0x000000[0x000001]
	Health = 3,//0x000000[0x000001]
	StressResistance = 4,//0x000000[0x000001]
	Metabolism = 5,//0x000000[0x000001]
	Immunity = 6,//0x000000[0x000001]
	Perception = 7,//0x000000[0x000001]
	Intellect = 8,//0x000000[0x000001]
	Attention = 9,//0x000000[0x000001]
	Charisma = 10,//0x000000[0x000001]
	Memory = 11,//0x000000[0x000001]
	MagDrills = 12,//0x000000[0x000001]
	Pistol = 13,//0x000000[0x000001]
	Revolver = 14,//0x000000[0x000001]
	SMG = 15,//0x000000[0x000001]
	Assault = 16,//0x000000[0x000001]
	Shotgun = 17,//0x000000[0x000001]
	Sniper = 18,//0x000000[0x000001]
	LMG = 19,//0x000000[0x000001]
	HMG = 20,//0x000000[0x000001]
	Launcher = 21,//0x000000[0x000001]
	AttachedLauncher = 22,//0x000000[0x000001]
	Throwing = 23,//0x000000[0x000001]
	Misc = 24,//0x000000[0x000001]
	Melee = 25,//0x000000[0x000001]
	DMR = 26,//0x000000[0x000001]
	DrawMaster = 27,//0x000000[0x000001]
	AimMaster = 28,//0x000000[0x000001]
	RecoilControl = 29,//0x000000[0x000001]
	TroubleShooting = 30,//0x000000[0x000001]
	Sniping = 31,//0x000000[0x000001]
	CovertMovement = 32,//0x000000[0x000001]
	ProneMovement = 33,//0x000000[0x000001]
	FirstAid = 34,//0x000000[0x000001]
	FieldMedicine = 35,//0x000000[0x000001]
	Surgery = 36,//0x000000[0x000001]
	LightVests = 37,//0x000000[0x000001]
	HeavyVests = 38,//0x000000[0x000001]
	WeaponModding = 39,//0x000000[0x000001]
	AdvancedModding = 40,//0x000000[0x000001]
	NightOps = 41,//0x000000[0x000001]
	SilentOps = 42,//0x000000[0x000001]
	Lockpicking = 43,//0x000000[0x000001]
	Search = 44,//0x000000[0x000001]
	WeaponTreatment = 45,//0x000000[0x000001]
	Freetrading = 46,//0x000000[0x000001]
	Auctions = 47,//0x000000[0x000001]
	Cleanoperations = 48,//0x000000[0x000001]
	Barter = 49,//0x000000[0x000001]
	Shadowconnections = 50,//0x000000[0x000001]
	Taskperformance = 51,//0x000000[0x000001]
	BearAssaultoperations = 52,//0x000000[0x000001]
	BearAuthority = 53,//0x000000[0x000001]
	BearAksystems = 54,//0x000000[0x000001]
	BearHeavycaliber = 55,//0x000000[0x000001]
	BearRawpower = 56,//0x000000[0x000001]
	UsecArsystems = 57,//0x000000[0x000001]
	UsecDeepweaponmodding = 58,//0x000000[0x000001]
	UsecLongrangeoptics = 59,//0x000000[0x000001]
	UsecNegotiations = 60,//0x000000[0x000001]
	UsecTactics = 61,//0x000000[0x000001]
	BotReload = 62,//0x000000[0x000001]
	BotSound = 63,//0x000000[0x000001]
	AimDrills = 64,//0x000000[0x000001]
	HideoutManagement = 65,//0x000000[0x000001]
	Crafting = 66,//0x000000[0x000001]
	Skills_Max = 67
};
enum CESkillClass
{
	Physical = 0,//0x000000[0x000004]
	Combat = 1,//0x000000[0x000004]
	Special = 2,//0x000000[0x000004]
	Practical = 3,//0x000000[0x000004]
	Mental = 4,//0x000000[0x000004]
};


static bool FindInCharArray(char *szClassNames, const char *szToFind)
{
	char *szFoundClass = strchr(szClassNames, ',');
	if (szFoundClass == 0)
		return _stricmp(szClassNames, (char*)szToFind) == 0;

	char *szHaystack = szClassNames;
	while (1)
	{
		char *szNeedle = strchr(szHaystack, ',');
		if (szNeedle == 0)
			return (_stricmp(szHaystack, (char*)szToFind) == 0);

		if (strncmp(szHaystack, (char*)szToFind, (size_t)(szNeedle - szHaystack)) == 0)
			return true;

		szHaystack = szNeedle + 1;
	}
	return false;
}

inline float Clamp(float value, float min, float max)
{
	if (value < min)
		value = min;
	else if (value > max)
		value = max;
	return value;
}
inline float ClampAngle(float angle, float min, float max)
{
	if (angle < -360.0f)
	{
		angle += 360.0f;
	}
	if (angle > 360.0f)
	{
		angle -= 360.0f;
	}
	return Clamp(angle, min, max);
}
inline float ClampAngle360Sensitive(float angle, float min, float max)
{
	if (angle < -360.0f)
	{
		angle += 360.0f;
	}
	if (angle > 360.0f)
	{
		angle -= 360.0f;
	}
	float num = (angle > 0.0f) ? (angle - 360.0f) : (angle + 360.0f);
	if (num > min && num < max)
	{
		return angle;
	}
	return Clamp(angle, min, max);
}


class FVec3;

class FVec2
{
public:
	float x, y;

	FVec2()
	{
		x = y = 0.0f;
	}
	FVec2(float xx, float yy)
	{
		x = xx;
		y = yy;
	}
	FVec2 operator / (float v)
	{
		return FVec2(x / v, y / v);
	}
	inline FVec2 operator-(const FVec2& v)
	{
		FVec2 res;
		res.x = x - v.x;
		res.y = y - v.y;
		return res;
	}
	inline FVec2 operator / (const FVec2& v)
	{
		FVec2 res;
		res.x = x / v.x;
		res.y = y / v.y;
		return res;
	}
	inline FVec3 ForwardVector();

	FVec2 NormalizeAngles()
	{
		while (x > 89.0f)
			x -= 180.0f;
		while (x < -89.0f)
			x += 180.0f;

		while (y > 180.0f)
			y -= 360.0f;
		while (y < -180.0f)
			y += 360.0f;
		return (*this);
	}
};

class FVec3
{
public:
	float x, y, z;

	FVec3()
	{
		x = y = z = 0.0f;
	}
	FVec3(float xx, float yy, float zz)
	{
		x = xx;
		y = yy;
		z = zz;
	}

	FVec3 operator * (float v)
	{
		return FVec3(x * v, y * v, z * v);
	}

	inline float Dot(const float v)
	{
		return (x * v + y * v + z * v);
	}
	inline float Dot(const FVec3& v)
	{
		return (x * v.x + y * v.y + z * v.z); //4 1547 ‭
	}
	inline FVec3 operator-(const FVec3& v)
	{
		FVec3 res;
		res.x = x - v.x;
		res.y = y - v.y;
		res.z = z - v.z;
		return res;
	}
	
	//static float Angle(FVec3 from, FVec3 to)
	//{
	//	float denominator = (float)sqrt(from.LengthSqt() * to.LengthSqt());
	//	if (denominator < kEpsilonNormalSqrt)
	//		return 0.0f;

	//	float dot = Clamp(from.Dot(to) / denominator, -1.0f, 1.0f);
	//	return ((float)acosf(dot)) * 57.295779513082320876798154814105f;
	//}
	inline float GetFOV(FVec3 &vDelta)
	{
		return D3DXToDegree(acosf((*this).Dot(vDelta)));
	}
	inline FVec3 Normalize()
	{
		float fMag_Inv = 1.0f / Length();
		return FVec3(x * fMag_Inv, y * fMag_Inv, z *fMag_Inv);
	}
	inline FVec2 ToRotator()
	{
		FVec2 rot;
		rot.y = (float)-D3DXToDegree(atan2f(y, (float)sqrtf(x * x + z * z)));
		rot.x = (float)D3DXToDegree(atan2f(x, z));
		if (rot.x > 180.0f)
			rot.x -= 360.0f;
		return rot;
	}
	inline float LengthSqt()
	{
		return (x * x + y * y + z * z);
	}
	float Length()
	{
		return sqrtf(LengthSqt());
	}
};
	
inline FVec3 FVec2::ForwardVector()
{
	float fCY = cosf(D3DXToRadian(x));
	float fSY = sinf(D3DXToRadian(x));
	float fCP = cosf(D3DXToRadian(y));
	float fSP = sinf(D3DXToRadian(y));

	FVec3 res;
	res.x = fSP * fCY;
	res.y = -fSY;
	res.z = fCY * fCP;
	return res;
};

class FVec4
{
public:
	float x, y, z, w;

	FVec4()
	{
		x = y = z = w = 0.0f;
	}

	FVec4(float xx, float yy, float zz, float ww)
	{
		x = xx;
		y = yy;
		z = zz;
		w = ww;
	}

	FVec3 operator *(FVec3 point)
	{
		float num = x * 2.0f;
		float num2 = y * 2.0f;
		float num3 = z * 2.0f;
		float num4 = x * num;
		float num5 = y * num2;
		float num6 = z * num3;
		float num7 = x * num2;
		float num8 = x * num3;
		float num9 = y * num3;
		float num10 = w * num;
		float num11 = w * num2;
		float num12 = w * num3;

		FVec3 result;
		result.x = (1.0f - (num5 + num6)) * point.x + (num7 - num12) * point.y + (num8 + num11) * point.z;
		result.y = (num7 + num12) * point.x + (1.0f - (num4 + num6)) * point.y + (num9 - num10) * point.z;
		result.z = (num8 - num11) * point.x + (num9 + num10) * point.y + (1.0f - (num4 + num5)) * point.z;
		return result;
	}
};

class CObject
{
public:
	char _0x0000[0x10];
};

class CMonoTransform
{
public:
	char _0x0000[0x010];				//0x0000
	DWORD_PTR dwKlass;					//0x0010
	char _0x0018[0x20];					//0x0018
	DWORD_PTR dwMain;					//0x0038

public:
	bool GetPosition(FVec3* vOutput);
};

template<typename T>class CUnityTArray
{
public:
	char _0x0000[0x18];		//0x0000
	DWORD dwSize;			//0x0018
	DWORD dwMaxSize;		//0x001C
	T lpListArray[1];		//0x0020
};
#define TARRAY_SIZE(T,xCount) sizeof(CUnityTArray<T>) + (sizeof(T) * xCount)

template<typename T, int iCounter>class CUnityTArrayCounter
{
public:
	char _0x0000[0x18];		//0x0000
	DWORD dwSize;			//0x0018
	DWORD dwMaxSize;		//0x001C
	T lpListArray[iCounter];//0x0020
};

template<typename T>class CUnityTList
{
public:
	char _0x0000[0x10];		//0x0000
	CUnityTList *lpList;	//0x0010
	DWORD dwSize;			//0x0018
	DWORD dwMaxSize;		//0x001C
	T lpListArray[1];		//0x0020
};
#define TLIST_SIZE(T,xCount) sizeof(CUnityTList<T>) + (sizeof(T) * xCount)

template<typename T, int iCounter>class CUnityTListCounter
{
public:
	char _0x0000[0x10];		//0x0000
	CUnityTList<T> *lpList;	//0x0010
	DWORD dwSize;			//0x0018
	DWORD dwMaxSize;		//0x001C
	T lpListArray[iCounter];		//0x0020
};

template<typename TKeys, typename TValues>class CUnityDictionaryValues
{
public:
	DWORD64 m_dwArrayHash;								//0x0000
	TKeys m_lpKey;										//0x0008
	TValues m_lpValue;									//0x0010
};
template<typename TKeys, typename TValues>class CUnityDictionaryList
{
public:
	char _0x0000[0x20];									//0x0000
	CUnityDictionaryValues<TKeys, TValues> m_Data[1];	//0x0020
};

template<typename TKeys, typename TValues>class CUnityDictionary
{
public:
	char _0x0000[0x18];									//0x0000
	CUnityDictionaryList<TKeys, TValues>* m_lpKeys;		//0x0018
	//CUnityDictionaryValues<TValues>* m_lpValues;		//0x0020
	char _0x0030[0x20];									//0x0028
	DWORD dwSize;										//0x0040
	DWORD dwMax;										//0x0044
	char _0x0048[0x08];									//0x0048
};

struct CUnityString
{
	DWORD64 dwVTable;													//0x0000
	DWORD64 Unknown;													//0x0008
	DWORD dwStringSize;													//0x0010
	wchar_t szString[512];												//0x0014
};
static bool operator == (CUnityString& a, CUnityString& b)
{
	return (a.dwStringSize == b.dwStringSize && wcscmp(a.szString, b.szString) == 0);
}
static bool operator == (CUnityString& a, const wchar_t* b)
{
	return (a.dwStringSize == wcslen(b) && wcscmp(a.szString, b) == 0);
}

class CUnityMonoType
{
public:
	class CMonoClass *m_lpKlass;										//0x0000
	char _0x0008[0x10];													//0x0008
	DWORD64 m_dwType;													//0x0018
};

class CUnityBaseMonoBehaviour
{
public:
	CUnityMonoType *m_lpType;											//0x0000
	char _0x0008[0x08];													//0x0008
};

template<typename T>class CUnityListElement
{
public:
	CUnityListElement<T> *m_lpPrev;
	CUnityListElement<T> *m_lpNext;
};
template<typename T>class CUnityListNode : public CUnityListElement<T>
{
public:
	T *m_lpData;
};

class CUnityObject : public CUnityListNode<class CUnityObject>
{
public:
	char _0x0018[0x10];										//0x0018
	void *m_lpScriptingObjectPointer;						//0x0028
};//Size = 0x0030

class CUnityComponent : public CUnityObject
{
public:
	class CUnityGameObject *m_lpGameObject;					//0x0030
};//Size = 0x0038

class CMonoClass
{
public:
	char _0x0000[0x30];													//0x0000
	CMonoClass *m_lpParent;												//0x0030
	char _0x0038[0x10];													//0x0038
	const char *m_szName;												//0x0048
	const char *m_szNamespace;											//0x0050
	char _0x0058[0x48];													//0x0058
	class CMethod **lpMethod;											//0x00A0
	char _0x00A8[0x54];													//0x00A8
	DWORD m_dwNumOfMethods;												//0x00FC
};

template<typename T>class CUnityPair
{
public:
	int first;
	char _0x0004[4];
	T* second;
};
template<typename T>class CUnityDynamicArray
{
public:
	CUnityPair<T> *m_lpData;			//0x0000
	int m_iLabel;						//0x0008
	char _0x000C[4];					//0x000C
	DWORD m_dwSize;						//0x0010
	char _0x0014[4];					//0x0014
	DWORD m_dwCapacity;					//0x0018
	char _0x001C[4];					//0x001C

	FORCEINLINE BOOL ReadListData(CUnityPair<T>* lpOutput)
	{
		return DMADevice::MemRead(this->m_lpData, lpOutput, sizeof(CUnityPair<T>) * m_dwSize, "List");
	}

	CMonoTransform* GetTransform()
	{
		if (m_dwSize == 0 || m_dwSize >= 100 || m_lpData == 0)
			return 0;

		CUnityPair<CMonoTransform*> lpBuffer = {};
		if (!DMADevice::MemRead(this->m_lpData, &lpBuffer, sizeof(CUnityPair<CMonoTransform*>)))
			return 0;

		CUnityMonoBehaviour monoBehaviour = {};
		if (!DMADevice::MemRead(lpBuffer.second, &monoBehaviour, sizeof(CUnityMonoBehaviour)))
			return 0;

		return (CMonoTransform*)monoBehaviour.m_lpScript;
	}

	T* operator[](int i)
	{
		if (i > m_dwSize)
			return 0;

		CUnityPair<T> lpBuffer[64] = {};
		if (!ReadListData(lpBuffer))
			return 0;

		return lpBuffer[i].second;
	}

	T* GetById(int iId)
	{
		if (m_dwSize == 0 || m_dwSize >= 1000 || m_lpData == 0)
			return 0;

		CUnityPair<T>* lpBuffer = (CUnityPair<T>*)calloc(m_dwSize, sizeof(CUnityPair<T>));
		if (!lpBuffer)
			return 0;

		if (!ReadListData(lpBuffer))
		{
			free(lpBuffer);
			return 0;
		}

		for (int i = 0; i < m_dwSize; i++)
		{
			if (lpBuffer[i].first == iId)
			{
				CUnityMonoBehaviour monoBehaviour = {};
				if (!DMADevice::MemRead(lpBuffer[i].second, &monoBehaviour, sizeof(CUnityMonoBehaviour), "List"))
					continue;

				free(lpBuffer);
				return (T*)monoBehaviour.m_lpScript;
			}
		}
		free(lpBuffer);
		return 0;
	}

	T* GetByName(char *szScriptName)
	{
		if (m_dwSize == 0 || m_dwSize >= 1000 || m_lpData == 0)
			return 0;

		CUnityPair<T>* lpBuffer = (CUnityPair<T>*)calloc(m_dwSize, sizeof(CUnityPair<T>));
		if (!lpBuffer)
			return 0;

		if (!ReadListData(lpBuffer))
		{
			free(lpBuffer);
			return 0;
		}

		for (int i = 0; i < m_dwSize; i++)
		{
			CUnityMonoBehaviour monoBehaviour = {};
			if (lpBuffer[i].first != CLASS_MonoBehaviour || !lpBuffer[i].second || !DMADevice::MemRead(lpBuffer[i].second, &monoBehaviour, sizeof(CUnityMonoBehaviour)))
				continue;

			if (!monoBehaviour.m_lpScript || !monoBehaviour.m_lpScriptCache)
				continue;

			CUnityScriptCache monoScriptCache = {};
			if (!DMADevice::MemRead(monoBehaviour.m_lpScriptCache, &monoScriptCache, sizeof(CUnityScriptCache)) || !monoScriptCache.klass)
				continue;

			char szClassName[64] = {};
			CMonoClass monoKlass = {};
			if (!DMADevice::MemRead(monoScriptCache.klass, &monoKlass, sizeof(CMonoClass)) || !monoKlass.m_szName || !DMADevice::MemRead(monoKlass.m_szName, szClassName, 64, false))
				continue;

			//printf("Name:%s\n", szClassName);
			if (FindInCharArray(szScriptName, szClassName))
			{
				free(lpBuffer);
				return (T*)monoBehaviour.m_lpScript;
			}
		}
		free(lpBuffer);
		return 0;
	}
};

class CUnityScriptCache
{
public:
	int refCount;														//0x0000
	char _0x0004[4];													//0x0004
	class CMonoClass *klass;											//0x0008
	CUnityDynamicArray<class CUnityScriptingMethodMono> methods;		//0x0010
	int scriptType;														//0x0030
};

class CUnityGameObject : public CUnityObject
{
public:
	CUnityDynamicArray<CUnityComponent> m_aComponents;		//0x0030
	char _0x0050[0x10];										//0x0050
	const char *m_szObjectName;								//0x0060
	//char _0x0068[0x10];									//0x0068

	const char *GetObjectName(char *szOutput, size_t nSize = 64);
	bool IsObject(char *szObjectName);
};

class CUnityMonoBehaviour
{
public:
	LPCVOID lpVTable;													//0x0000
	char _0x0008[0x20];													//0x0008
	CUnityMonoBehaviour *m_lpScript;									//0x0028
	CUnityGameObject *m_lpKlass;										//0x0030
	char _0x0038[0xB8];													//0x0038
	CUnityScriptCache *m_lpScriptCache;									//0x00F0
};
class CUnityMonoBehaviourScript : public CUnityBaseMonoBehaviour
{
public:
	class CUnityMonoBehaviour *m_lpComponent;			//0x0010

	void *GetComonent(char* szName);
	void *GetComonent(DWORD dwId, int *iErrorCode = 0);
	CMonoTransform* GetTransform();

	bool GetPosition(FVec3* lpOutput);
	bool GetRotation(FVec4* lpOutput);
};





class CUnityGameObjectManager
{
public:
	CUnityListElement<CUnityListNode<CUnityGameObject>> m_Tagged;
	CUnityListElement<CUnityListNode<CUnityGameObject>> m_Active;
};


template<typename T>class CGClass1103 : public CUnityBaseMonoBehaviour
{
public:
	char _0x0010[0x10];//0x0010
	DWORD Id;//0x0020
	DWORD BuffType;//0x0024
	T Value;//0x0028
};
class CGClass1097 : public CUnityBaseMonoBehaviour
{
public:
	char _0x0010[0x18];							//0x0010
	CESkillId Id;								//000028
	float Current;								//0x002C
};
class CGameWorld : public CUnityMonoBehaviourScript
{
public:
	class CGClass687* gclass687_0;//0x000018[0x000008]
	CUnityString* string_0;//0x000020[0x000008]
	class CGClass916* GameDateTime;//0x000028[0x000008]
	class CConfig* SpeedLimits;//0x000030[0x000008]
	CUnityString* CurrentProfileId;//0x000038[0x000008]
	class CGClass446* gclass446_0;//0x000040[0x000008]
	class CAudioSourceCulling* AudioSourceCulling;//0x000048[0x000008]
	class CGInterface215* ginterface215_0;//0x000050[0x000008]
	class CBallisticsCalculator* _sharedBallisticsCalculator;//0x000058[0x000008]
	CUnityTList<class CGInterface7*>* LootList;//0x000060[0x000008]
	CUnityDictionary<class CIItemOwner*, class CGStruct77>* ItemOwners;//0x000068[0x000008]
	void* LootItems;//0x000070[0x000008]
	CUnityTList<class CGClass747*>* AllLoot;//0x000078[0x000008]
	CUnityTList<class CPlayer*>* RegisteredPlayers;//0x000080[0x000008]
};

class CItem : public CObject
{
public:
	CUnityString* Id;//0x000010[0x000008]
	void* OriginalAddress;//0x000018[0x000008]
	void* Components;//0x000020[0x000008]
	CUnityString* _toStringCache;//0x000028[0x000008]
	void* CurrentAddress;//0x000030[0x000008]
	void* _template;//0x000038[0x000008]
	void* Attributes;//0x000040[0x000008]
	void* ChildrenChanged;//0x000048[0x000008]
	bool UnlimitedCount;//0x000050[0x000001]
	unsigned char _0x00000051[0x3];//0x00000051 (0x3) MISSED OFFSET
	__int32 BuyRestrictionMax;//0x000054[0x000004]
	__int32 BuyRestrictionCurrent;//0x000058[0x000004]
	__int32 StackObjectsCount;//0x00005C[0x000004]
	__int32 Version;//0x000060[0x000004]
	bool SpawnedInSession;//0x000064[0x000001]
	unsigned char _0x00000065[0x3];//0x00000065 (0x3) MISSED OFFSET
};
class CGClass1765 : public CItem
{
public:
	void* SideEffect;//0x000068[0x000008]
	void* Repairable;//0x000070[0x000008]
	void* KnifeComponent;//0x000078[0x000008]
};
class CGClass1766 : public CGClass1765
{
public:
	int Side;//0x0000D0[0x000004]
	unsigned char _0x000000D4[0x4];//0x000000D4 (0x4) MISSED OFFSET
};
template<typename T>class CGClass502 : public CObject
{
public:
	void* func_0;//0x000010[0x000008]
};
template<typename T>class CGClass503 : public CGClass502<T>
{
public:
	T gparam_0;//0x000018[0x000008]
	bool bool_0;//0x000020[0x000001]
	unsigned char _0x00000021[0x7];//0x00000021 (0x7) MISSED OFFSET
};
class CGClass1781 : public CObject
{
public:
	void* Equipment;//0x000010[0x000008]
	void* ArmorSlots;//0x000010[0x000008]
	void* Stash;//0x000018[0x000008]
	void* FastAccessSlots;//0x000018[0x000008]
	void* QuestRaidItems;//0x000020[0x000008]
	void* QuestStashItems;//0x000028[0x000008]
	void* SortingTable;//0x000030[0x000008]
	void* FastAccess;//0x000038[0x000008]
	void* TotalWeight;//0x000040[0x000008]
	void* TotalWeightEliteSkill;//0x000048[0x000008]
	void* DeserializationErrors;//0x000050[0x000008]
	void* list_0;//0x000058[0x000008]
	void* OnWeightUpdated;//0x000060[0x000008]
};



class CGClass1794 : public CObject
{
public:
	void* action_0;//0x000010[0x000008]
	void* Logger;//0x000018[0x000008]
	void* action_1;//0x000020[0x000008]
	void* action_2;//0x000028[0x000008]
	void* action_3;//0x000030[0x000008]
	void* action_4;//0x000038[0x000008]
	void* action_5;//0x000040[0x000008]
	void* action_6;//0x000048[0x000008]
	void* action_7;//0x000050[0x000008]
	void* action_8;//0x000058[0x000008]
	void* action_9;//0x000060[0x000008]
	void* action_10;//0x000068[0x000008]
	void* action_11;//0x000070[0x000008]
	void* action_12;//0x000078[0x000008]
	void* hashSet_0;//0x000080[0x000008]
	CUnityString* string_0;//0x000088[0x000008]
	void* itemFilter_0;//0x000090[0x000008]
	void* item_0;//0x000098[0x000008]
	void* item_1;//0x0000A0[0x000008]
	void* item_2;//0x0000A8[0x000008]
	CUnityString* string_1;//0x0000B0[0x000008]
	void* list_0;//0x0000B8[0x000008]
	void* coroutine_0;//0x0000C0[0x000008]
	unsigned __int16 ushort_0;//0x0000C8[0x000002]
	unsigned char _0x000000CA[0x2];//0x000000CA (0x2) MISSED OFFSET
	__int32 int_0;//0x0000CC[0x000004]
	bool bool_0;//0x0000D0[0x000001]
	bool bool_1;//0x0000D1[0x000001]
	unsigned char _0x000000D2[0x2];//0x000000D2 (0x2) MISSED OFFSET
	int eownerType_0;//0x0000D4[0x000004]
};
class CGClass1143 : public CUnityBaseMonoBehaviour
{
public:
	void* action_0;//0x000010[0x000008]
	float FactorValue;//0x000018[0x000004]
	bool SimpleCalculation;//0x00001C[0x000001]
	char _0x0001D[0x03];//0x00001D[0x000003]
	float float_0;//0x000020[0x000003]
};
class CGClass1795 : public CGClass1794
{
public:
	int Side;//0x0000D8[0x000004]
	unsigned char _0x000000DC[0x4];//0x000000DC (0x4) MISSED OFFSET
};
class CGClass1205 : public CObject
{
public:
	void* WeaponBuffs;//0x000010[0x000008]
	CGClass1103<float>* EnduranceBuffEnduranceInc;//0x000018[0x000008]
	CGClass1103<float>* EnduranceHands;//0x000020[0x000008]
	CGClass1103<float>* EnduranceBuffJumpCostRed;//0x000028[0x000008]
	CGClass1103<float>* EnduranceBuffBreathTimeInc;//0x000030[0x000008]
	CGClass1103<float>* EnduranceBuffRestoration;//0x000038[0x000008]
	CGClass1103<float>* EnduranceBreathElite;//0x000040[0x000008]
	CGClass1103<float>* StrengthBuffLiftWeightInc;//0x000048[0x000008]
	CGClass1103<float>* StrengthBuffSprintSpeedInc;//0x000050[0x000008]
	CGClass1103<float>* StrengthBuffJumpHeightInc;//0x000058[0x000008]
	CGClass1103<float>* StrengthBuffAimFatigue;//0x000060[0x000008]
	CGClass1103<float>* StrengthBuffThrowDistanceInc;//0x000068[0x000008]
	CGClass1103<float>* StrengthBuffMeleePowerInc;//0x000070[0x000008]
	CGClass1103<bool>* StrengthBuffElite;//0x000078[0x000008]
	CGClass1103<float>* StrengthBuffMeleeCrits;//0x000080[0x000008]
	CGClass1103<float>* VitalityBuffBleedChanceRed;//0x000088[0x000008]
	CGClass1103<float>* VitalityBuffSurviobilityInc;//0x000090[0x000008]
	CGClass1103<bool>* VitalityBuffRegeneration;//0x000098[0x000008]
	CGClass1103<bool>* VitalityBuffBleedStop;//0x0000A0[0x000008]
	CGClass1103<float>* HealthBreakChanceRed;//0x0000A8[0x000008]
	CGClass1103<float>* HealthOfflineRegenerationInc;//0x0000B0[0x000008]
	CGClass1103<float>* HealthEnergy;//0x0000B8[0x000008]
	CGClass1103<float>* HealthHydration;//0x0000C0[0x000008]
	CGClass1103<bool>* HealthEliteAbsorbDamage;//0x0000C8[0x000008]
	CGClass1103<float>* HealthElitePosion;//0x0000D0[0x000008]
	CGClass1103<float>* StressPain;//0x0000D8[0x000008]
	CGClass1103<float>* StressTremor;//0x0000E0[0x000008]
	CGClass1103<bool>* StressBerserk;//0x0000E8[0x000008]
	CGClass1103<float>* MetabolismRatioPlus;//0x0000F0[0x000008]
	CGClass1103<float>* MetabolismPoisonTime;//0x0000F8[0x000008]
	CGClass1103<float>* MetabolismMiscDebuffTime;//0x000100[0x000008]
	CGClass1103<bool>* MetabolismEliteBuffNoDyhydration;//0x000108[0x000008]
	CGClass1103<float>* PerceptionHearing;//0x000110[0x000008]
	CGClass1103<float>* PerceptionLootDot;//0x000118[0x000008]
	CGClass1103<bool>* PerceptionEliteNoIdea;//0x000120[0x000008]
	CGClass1103<float>* IntellectLearningSpeed;//0x000128[0x000008]
	CGClass1103<float>* IntellectWeaponMaintance;//0x000130[0x000008]
	CGClass1103<bool>* IntellectEliteNaturalLearner;//0x000138[0x000008]
	CGClass1103<bool>* IntellectEliteAmmoCounter;//0x000140[0x000008]
	CGClass1103<bool>* IntellectEliteContainerScope;//0x000148[0x000008]
	CGClass1103<float>* AttentionLootSpeed;//0x000150[0x000008]
	CGClass1103<float>* AttentionExamine;//0x000158[0x000008]
	CGClass1103<float>* AttentionEliteLuckySearch;//0x000160[0x000008]
	CGClass1103<bool>* AttentionEliteExtraLootExp;//0x000168[0x000008]
	CGClass1103<float>* MagDrillsLoadSpeed;//0x000170[0x000008]
	CGClass1103<float>* MagDrillsUnloadSpeed;//0x000178[0x000008]
	CGClass1103<float>* MagDrillsInventoryCheckSpeed;//0x000180[0x000008]
	CGClass1103<float>* MagDrillsInventoryCheckAccuracy;//0x000188[0x000008]
	CGClass1103<bool>* MagDrillsInstantCheck;//0x000190[0x000008]
	CGClass1103<bool>* MagDrillsLoadProgression;//0x000198[0x000008]
	CGClass1103<float>* CharismaBuff1;//0x0001A0[0x000008]
	CGClass1103<float>* CharismaBuff2;//0x0001A8[0x000008]
	CGClass1103<bool>* CharismaEliteBuff1;//0x0001B0[0x000008]
	CGClass1103<float>* CharismaEliteBuff2;//0x0001B8[0x000008]
	CGClass1103<float>* MemoryMentalForget1;//0x0001C0[0x000008]
	CGClass1103<float>* MemoryMentalForget2;//0x0001C8[0x000008]
	CGClass1103<bool>* MemoryEliteMentalRecoil;//0x0001D0[0x000008]
	CGClass1103<float>* ImmunityMiscEffects;//0x0001D8[0x000008]
	CGClass1103<float>* ImmunityPoisonBuff;//0x0001E0[0x000008]
	CGClass1103<float>* ImmunityPainKiller;//0x0001E8[0x000008]
	CGClass1103<float>* ImmunityAvoidPoisonChance;//0x0001F0[0x000008]
	CGClass1103<float>* ImmunityAvoidMiscEffectsChance;//0x0001F8[0x000008]
	void* Pistol;//0x000200[0x000008]
	void* Revolver;//0x000208[0x000008]
	void* SMG;//0x000210[0x000008]
	void* Assault;//0x000218[0x000008]
	void* Shotgun;//0x000220[0x000008]
	void* Sniper;//0x000228[0x000008]
	void* LMG;//0x000230[0x000008]
	void* HMG;//0x000238[0x000008]
	void* Launcher;//0x000240[0x000008]
	void* AttachedLauncher;//0x000248[0x000008]
	void* Misc;//0x000250[0x000008]
	void* Melee;//0x000258[0x000008]
	void* DMR;//0x000260[0x000008]
	void* Throwing;//0x000268[0x000008]
	void* AimDrills;//0x000270[0x000008]
	void* RecoilControl;//0x000278[0x000008]
	void* TroubleShooting;//0x000280[0x000008]
	CGClass1103<float>* AimMasterSpeed;//0x000288[0x000008]
	CGClass1103<float>* AimMasterWiggle;//0x000290[0x000008]
	CGClass1103<bool>* AimMasterElite;//0x000298[0x000008]
	CGClass1103<float>* RecoilControlImprove;//0x0002A0[0x000008]
	CGClass1103<float>* RecoilControlElite;//0x0002A8[0x000008]
	CGClass1103<float>* TroubleFixing;//0x0002B0[0x000008]
	CGClass1103<bool>* TroubleFixingDurElite;//0x0002B8[0x000008]
	CGClass1103<bool>* TroubleFixingMagElite;//0x0002C0[0x000008]
	CGClass1103<bool>* TroubleFixingAmmoElite;//0x0002C8[0x000008]
	CGClass1103<float>* ThrowingStrengthBuff;//0x0002D0[0x000008]
	CGClass1103<float>* ThrowingEnergyExpenses;//0x0002D8[0x000008]
	CGClass1103<bool>* ThrowingEliteBuff;//0x0002E0[0x000008]
	CGClass1103<float>* DrawSpeed;//0x0002E8[0x000008]
	CGClass1103<float>* DrawSound;//0x0002F0[0x000008]
	CGClass1103<bool>* DrawElite;//0x0002F8[0x000008]
	CGClass1103<bool>* DrawTremor;//0x000300[0x000008]
	void* action_0;//0x000308[0x000008]
	CUnityTArray<CGClass1097*>* Skills;//0x000310[0x000008]
	CUnityTArray<CGClass1097*>* DisplayList;//0x000318[0x000008]
	void* list_0;//0x000320[0x000008]
	void* Mastering;//0x000328[0x000008]
	void* action_1;//0x000330[0x000008]
	void* action_2;//0x000338[0x000008]
	void* action_3;//0x000340[0x000008]
	void* action_4;//0x000348[0x000008]
	void* action_5;//0x000350[0x000008]
	void* NoExpenseAimSkillTimer;//0x000358[0x000008]
	void* FastAimTimer;//0x000360[0x000008]
	void* SprintAction;//0x000368[0x000008]
	void* PushUp;//0x000370[0x000008]
	CGClass1143* ProneAction;//0x000378[0x000008]
	void* MovementAction;//0x000380[0x000008]
	void* JumpAction;//0x000388[0x000008]
	void* WeaponReloadAction;//0x000390[0x000008]
	void* WeaponShotAction;//0x000398[0x000008]
	void* WeaponChamberAction;//0x0003A0[0x000008]
	CGClass1143* WeaponFixAction;//0x0003A8[0x000008]
	CGClass1143* WeaponDrawAction;//0x0003B0[0x000008]
	CGClass1143* WeaponAimAction;//0x0003B8[0x000008]
	void* ShotAfterAim;//0x0003C0[0x000008]
	CGClass1143* RecoilAction;//0x0003C8[0x000008]
	CGClass1143* FistfightAction;//0x0003D0[0x000008]
	CGClass1143* ThrowAction;//0x0003D8[0x000008]
	CGClass1143* HoldBreathAction;//0x0003E0[0x000008]
	CGClass1143* DamageTakenAction;//0x0003E8[0x000008]
	void* HealthNegativeEffect;//0x0003F0[0x000008]
	CGClass1143* LowHPDuration;//0x0003F8[0x000008]
	CGClass1143* OnlineAction;//0x000400[0x000008]
	CGClass1143* UniqueLoot;//0x000408[0x000008]
	CGClass1143* ExamineAction;//0x000410[0x000008]
	CGClass1143* ExamineWithInstruction;//0x000418[0x000008]
	void* LockpickAction;//0x000420[0x000008]
	CGClass1143* RepairAction;//0x000428[0x000008]
	void* FindAction;//0x000430[0x000008]
	void* TradeAction;//0x000438[0x000008]
	CGClass1143* SearchAction;//0x000440[0x000008]
	CGClass1143* RaidLoadedAmmoAction;//0x000448[0x000008]
	CGClass1143* RaidUnloadedAmmoAction;//0x000450[0x000008]
	CGClass1143* MagazineCheckAction;//0x000458[0x000008]
	void* AnySkillUp;//0x000460[0x000008]
	void* SkillProgress;//0x000468[0x000008]
	void* HydrationChanged;//0x000470[0x000008]
	void* EnergyChanged;//0x000478[0x000008]
	void* KillAction;//0x000480[0x000008]
	CGClass1143* SurgeryAction;//0x000488[0x000008]
	void* HideoutCraftTimerAction;//0x000490[0x000008]
	CGClass1143* HideoutCompleteCraftAction;//0x000498[0x000008]
	CGClass1143* HideoutZoneUpgradeAction;//0x0004A0[0x000008]
	CGClass1143* UniqueCrafting;//0x0004A8[0x000008]
	CGClass1143* StimulatorNegativeBuff;//0x0004B0[0x000008]
	CGClass1143* Exhaustion;//0x0004B8[0x000008]
	CGClass1143* Dehydration;//0x0004C0[0x000008]
	CGClass1143* WeaponRepairedAction;//0x0004C8[0x000008]
	void* ConsumptionActions;//0x0004D0[0x000008]
	void* bonusController_0;//0x0004D8[0x000008]
	void* Perception;//0x0004E0[0x000008]
	void* Intellect;//0x0004E8[0x000008]
	void* Attention;//0x0004F0[0x000008]
	void* Immunity;//0x0004F8[0x000008]
	void* Charisma;//0x000500[0x000008]
	void* Memory;//0x000508[0x000008]
	void* Endurance;//0x000510[0x000008]
	void* Strength;//0x000518[0x000008]
	void* Vitality;//0x000520[0x000008]
	void* Health;//0x000528[0x000008]
	void* Metabolism;//0x000530[0x000008]
	void* StressResistance;//0x000538[0x000008]
	void* Sniping;//0x000540[0x000008]
	void* CovertMovement;//0x000548[0x000008]
	void* ProneMovement;//0x000550[0x000008]
	void* FirstAid;//0x000558[0x000008]
	void* FieldMedicine;//0x000560[0x000008]
	void* LightVests;//0x000568[0x000008]
	void* HeavyVests;//0x000570[0x000008]
	void* WeaponModding;//0x000578[0x000008]
	void* AdvancedModding;//0x000580[0x000008]
	void* NightOps;//0x000588[0x000008]
	void* SilentOps;//0x000590[0x000008]
	void* Lockpicking;//0x000598[0x000008]
	void* Surgery;//0x0005A0[0x000008]
	void* Search;//0x0005A8[0x000008]
	void* WeaponTreatment;//0x0005B0[0x000008]
	void* MagDrills;//0x0005B8[0x000008]
	void* Freetrading;//0x0005C0[0x000008]
	void* Auctions;//0x0005C8[0x000008]
	void* Cleanoperations;//0x0005D0[0x000008]
	void* Barter;//0x0005D8[0x000008]
	void* Shadowconnections;//0x0005E0[0x000008]
	void* Taskperformance;//0x0005E8[0x000008]
	void* Crafting;//0x0005F0[0x000008]
	void* HideoutManagement;//0x0005F8[0x000008]
	CGClass1103<float>* CovertMovementSoundVolume;//0x000600[0x000008]
	CGClass1103<float>* CovertMovementEquipment;//0x000608[0x000008]
	CGClass1103<float>* CovertMovementSpeed;//0x000610[0x000008]
	CGClass1103<bool>* CovertMovementElite;//0x000618[0x000008]
	CGClass1103<float>* CovertMovementLoud;//0x000620[0x000008]
	CGClass1103<float>* ProneMovementSpeed;//0x000628[0x000008]
	CGClass1103<float>* ProneMovementVolume;//0x000630[0x000008]
	CGClass1103<bool>* ProneMovementEliteSprint;//0x000638[0x000008]
	CGClass1103<float>* SearchBuffSpeed;//0x000640[0x000008]
	CGClass1103<bool>* SearchDouble;//0x000648[0x000008]
	CGClass1103<float>* SurgeryReducePenalty;//0x000650[0x000008]
	CGClass1103<float>* SurgerySpeed;//0x000658[0x000008]
	CGClass1103<float>* HideoutResourceConsumption;//0x000660[0x000008]
	CGClass1103<float>* ZoneBonusBoost;//0x000668[0x000008]
	CGClass1103<bool>* HideoutExtraSlots;//0x000670[0x000008]
	CGClass1103<float>* SingleCraftTimeReduce;//0x000678[0x000008]
	CGClass1103<float>* ContinueCraftTimeReduce;//0x000680[0x000008]
	CGClass1103<bool>* EliteCrafting;//0x000688[0x000008]
	CGClass1103<float>* WeaponDurabilityLosOnShotReduce;//0x000690[0x000008]
	CGClass1103<float>* WeaponDeteriorationChanceOnRepairReduce;//0x000698[0x000008]
	CGClass1103<bool>* ZeroWeaponDeteriorationOnRepair;//0x0006A0[0x000008]
	void* BearAssaultoperations;//0x0006A8[0x000008]
	void* BearAuthority;//0x0006B0[0x000008]
	void* BearAksystems;//0x0006B8[0x000008]
	void* BearHeavycaliber;//0x0006C0[0x000008]
	void* BearRawpower;//0x0006C8[0x000008]
	void* UsecArsystems;//0x0006D0[0x000008]
	void* UsecDeepweaponmodding;//0x0006D8[0x000008]
	void* UsecLongrangeoptics;//0x0006E0[0x000008]
	void* UsecNegotiations;//0x0006E8[0x000008]
	void* UsecTactics;//0x0006F0[0x000008]
	void* BotReload;//0x0006F8[0x000008]
	void* BotSoundGoef;//0x000700[0x000008]
	CGClass1103<float>* BotReloadSpeed;//0x000708[0x000008]
	CGClass1103<float>* BotSoundCoef;//0x000710[0x000008]
	__int32 ExtraSkillsPoints;//0x000718[0x000004]
	unsigned char _0x0000071C[0x4];//0x0000071C (0x4) MISSED OFFSET
};
class CGClass1180 : public CObject
{
public:
	__int32 Role;//0x000010[0x000004]
	__int32 BotDifficulty;//0x000014[0x000004]
	__int32 Experience;//0x000018[0x000004]
	float StandingForKill;//0x00001C[0x000004]
	float AggressorBonus;//0x000020[0x000004]
};
class CGClass1194 : public CObject
{
public:
	CUnityString* Nickname;//0x000010[0x000008]
	CUnityString* GroupId;//0x000018[0x000008]
	CUnityString* EntryPoint;//0x000020[0x000008]
	CUnityString* Voice;//0x000028[0x000008]
	void* Bans;//0x000030[0x000008]
	CGClass1180* Settings;//0x000038[0x000008]
	void* action_0;//0x000040[0x000008]
	void* action_1;//0x000048[0x000008]
	__int32 Side;//0x000050[0x000004]
	__int32 RegistrationDate;//0x000054[0x000004]
	double SavageLockTime;//0x000058[0x000008]
	__int32 NicknameChangeDate;//0x000060[0x000004]
	bool IsStreamerModeAvailable;//0x000064[0x000001]
	unsigned char _0x00000065[0x3];//0x00000065 (0x3) MISSED OFFSET
	__int32 MemberCategory;//0x000068[0x000004]
	__int32 int_0;//0x00006C[0x000004]
};
class CProfile : public CObject
{
public:
	CUnityString* Id;//0x000010[0x000008]
	CUnityString* AccountId;//0x000018[0x000008]
	CUnityString* PetId;//0x000020[0x000008]
	CGClass1194* Info;//0x000028[0x000008]
	void* Customization;//0x000030[0x000008]
	void* Encyclopedia;//0x000038[0x000008]
	void* Health;//0x000040[0x000008]
	CGClass1781* Inventory;//0x000048[0x000008]
	void* QuestItems;//0x000050[0x000008]
	void* InsuredItems;//0x000058[0x000008]
	CGClass1205* Skills;//0x000060[0x000008]
	void* Notes;//0x000068[0x000008]
	void* Quests;//0x000070[0x000008]
	void* ConditionCounters;//0x000078[0x000008]
	void* BackendCounters;//0x000080[0x000008]
	void* TradersInfo;//0x000088[0x000008]
	void* Bonuses;//0x000090[0x000008]
	void* Hideout;//0x000098[0x000008]
	void* RagfairInfo;//0x0000A0[0x000008]
	void* bonusController_0;//0x0000A8[0x000008]
	void* IdGenerator;//0x0000B0[0x000008]
	void* WishList;//0x0000B8[0x000008]
	void* _emptyResourceCollection;//0x0000C0[0x000008]
	void* fenceTraderInfo_0;//0x0000C8[0x000008]
	void* OnItemZoneDropped;//0x0000D0[0x000008]
	void* OnTraderStandingChanged;//0x0000D8[0x000008]
	void* OnTraderLoyaltyChanged;//0x0000E0[0x000008]
	void* Stats;//0x0000E8[0x000008]
	void* CheckedMagazines;//0x0000F0[0x000008]
	void* CheckedChambers;//0x0000F8[0x000008]
};
class CGClass1797 : public CGClass1795
{
public:
	void* action_13;//0x0000E0[0x000008]
	void* action_14;//0x0000E8[0x000008]
	void* action_15;//0x0000F0[0x000008]
	void* action_16;//0x0000F8[0x000008]
	void* action_17;//0x000100[0x000008]
	void* action_18;//0x000108[0x000008]
	void* dictionary_0;//0x000110[0x000008]
	void* SearchOperations;//0x000118[0x000008]
	CGClass1781* gclass1781_0;//0x000120[0x000008]
	CProfile* profile_0;//0x000128[0x000008]
	bool bool_2;//0x000130[0x000001]
	bool bool_3;//0x000131[0x000001]
	unsigned char _0x00000132[0x6];//0x00000132 (0x6) MISSED OFFSET
};
class CGClass1134 : public CObject
{
public:
	char _0x000010[0x01C0];
	float float_0;//0x0001D0[0x000004]
	bool bool_0;//0x0001D4[0x000001]
	unsigned char _0x000001D5[0x3];//0x000001D5 (0x3) MISSED OFFSET
	__int32 BlindFire;//0x0001D8[0x000004]
	bool IgnoreDeltaMovement;//0x0001DC[0x000001]
	unsigned char _0x000001DD[0x3];//0x000001DD (0x3) MISSED OFFSET
	float float_1;//0x0001E0[0x000004]
	float float_2;//0x0001E4[0x000004]
	bool CanSlope;//0x0001E8[0x000001]
	unsigned char _0x000001E9[0x3];//0x000001E9 (0x3) MISSED OFFSET
	float float_3;//0x0001EC[0x000004]
	float float_4;//0x0001F0[0x000004]
	float float_5;//0x0001F4[0x000004]
	float float_6;//0x0001F8[0x000004]
	float float_7;//0x0001FC[0x000004]
	__int32 int_0;//0x000200[0x000004]
	FVec2 vector2_0;//0x000204[0x000008]
	FVec2 vector2_1;//0x00020C[0x000008]
	FVec2 vector2_2;//0x000214[0x000008]
	BYTE raycastHit_0[0x00002C];//0x00021C[0x00002C]
	float CheckGroundedRayDistance;//0x000248[0x000004]
	float float_8;//0x00024C[0x000004]
	float float_9;//0x000250[0x000004]
	float float_10;//0x000254[0x000004]
	__int32 layerMask_0;//0x000258[0x000004]
	__int32 layerMask_1;//0x00025C[0x000004]
	__int32 layerMask_2;//0x000260[0x000004]
	__int32 int_1;//0x000264[0x000004]
	FVec2 vector2_3;//0x000268[0x000008]
	FVec2 vector2_4;//0x000270[0x000008]
	FVec2 vector2_5;//0x000278[0x000008]
	FVec3 vector3_0;//0x000280[0x00000C]
	float float_11;//0x00028C[0x000004]
	float CovertEfficiency;//0x000290[0x000004]
	bool SoftSurface;//0x000294[0x000001]
	bool bool_1;//0x000295[0x000001]
	unsigned char _0x00000296[0x2];//0x00000296 (0x2) MISSED OFFSET
	__int32 ephysicalCondition_0;//0x000298[0x000004]
	bool NextBreachResult;//0x00029C[0x000001]
	unsigned char _0x0000029D[0x3];//0x0000029D (0x3) MISSED OFFSET
	float float_16;//0x0002A0[0x000004]
	float LevelOnApproachStart;//0x0002A4[0x000004]
	bool bool_2;//0x0002A8[0x000001]
	unsigned char _0x000002A9[0x3];//0x000002A9 (0x3) MISSED OFFSET
	__int32 int_2;//0x0002AC[0x000004]
	float float_17;//0x0002B0[0x000004]
	bool bool_3;//0x0002B4[0x000001]
	unsigned char _0x000002B5[0x3];//0x000002B5 (0x3) MISSED OFFSET
	float float_18;//0x0002B8[0x000004]
	float float_19;//0x0002BC[0x000004]
	float float_20;//0x0002C0[0x000004]
	BYTE raycastHit_1[0x00002C];//0x0002C4[0x00002C]
	float FreefallTime;//0x0002F0[0x000004]
	FVec3 vector3_1;//0x0002F4[0x00000C]
	FVec4 PlatformRotation;//0x000300[0x000010]
	bool bool_4;//0x000310[0x000001]
	unsigned char _0x00000311[0x3];//0x00000311 (0x3) MISSED OFFSET
	float float_21;//0x000314[0x000004]
	FVec3 InputMotion;//0x000318[0x00000C]
	FVec3 InputMotionBeforeLimit;//0x000324[0x00000C]
	__int32 int_3;//0x000330[0x000004]
	bool bool_5;//0x000334[0x000001]
	unsigned char _0x00000335[0x3];//0x00000335 (0x3) MISSED OFFSET
	FVec3 vector3_2;//0x000338[0x00000C]
	float float_23;//0x000344[0x000004]
	FVec3 PreviousPosition;//0x000348[0x00000C]
	float float_24;//0x000354[0x000004]
	FVec3 vector3_3;//0x000358[0x00000C]
	FVec3 vector3_4;//0x000364[0x00000C]
	bool bool_6;//0x000370[0x000001]
	bool bool_7;//0x000371[0x000001]
	unsigned char _0x00000372[0x2];//0x00000372 (0x2) MISSED OFFSET
	float float_25;//0x000374[0x000004]
	FVec3 vector3_5;//0x000378[0x00000C]
	float float_26;//0x000384[0x000004]
	FVec3 vector3_6;//0x000388[0x00000C]
	float float_27;//0x000394[0x000004]
	float float_28;//0x000398[0x000004]
	FVec3 vector3_7;//0x00039C[0x00000C]
	FVec3 vector3_8;//0x0003A8[0x00000C]
	__int32 int_4;//0x0003B4[0x000004]
	float float_29;//0x0003B8[0x000004]
	bool bool_8;//0x0003BC[0x000001]
	bool bool_9;//0x0003BD[0x000001]
	bool bool_10;//0x0003BE[0x000001]
	unsigned char _0x000003BF[0x1];//0x000003BF (0x1) MISSED OFFSET
};
class CGClass439 : public CObject
{
public:
	void* TotalCapacity;//0x000010[0x000008]
	void* SelfRestoration;//0x000018[0x000008]
	void* Consumptions;//0x000020[0x000008]
	void* action_0;//0x000028[0x000008]
	void* action_1;//0x000030[0x000008]
	void* action_2;//0x000038[0x000008]
	void* action_3;//0x000040[0x000008]
	float Current;//0x000048[0x000004]
	float DisableRestoration;//0x00004C[0x000004]
	float float_0;//0x000050[0x000004]
	bool bool_0;//0x000054[0x000001]
	unsigned char _0x00000055[0x3];//0x00000055 (0x3) MISSED OFFSET
	__int32 int_0;//0x000058[0x000004]
	unsigned char _0x0000005C[0x4];//0x0000005C (0x4) MISSED OFFSET
};
class CGClass440 : public CObject
{
public:
	CPlayer* player_0;//0x000010[0x000008]
	void* MinStepSound;//0x000018[0x000008]
	void* TransitionSpeed;//0x000020[0x000008]
	CGClass439* Stamina;//0x000028[0x000008]
	CGClass439* HandsStamina;//0x000030[0x000008]
	CGClass439* Oxygen;//0x000038[0x000008]
	void* action_0;//0x000040[0x000008]
	void* action_1;//0x000048[0x000008]
	void* action_2;//0x000050[0x000008]
	void* action_3;//0x000058[0x000008]
	void* action_4;//0x000060[0x000008]
	void* action_5;//0x000068[0x000008]
	void* action_6;//0x000070[0x000008]
	float MaxPoseLevel;//0x000078[0x000004]
	float Overweight;//0x00007C[0x000004]
	float WalkOverweight;//0x000080[0x000004]
	float WalkSpeedLimit;//0x000084[0x000004]
	float SoundRadius;//0x000088[0x000004]
	bool bool_0;//0x00008C[0x000001]
	unsigned char _0x0000008D[0x3];//0x0000008D (0x3) MISSED OFFSET
	float float_2;//0x000090[0x000004]
	float Fatigue;//0x000094[0x000004]
	float CapacityBuff;//0x000098[0x000004]
	float float_3;//0x00009C[0x000004]
	float FallDamageMultiplier;//0x0000A0[0x000004]
	float StaminaCapacity;//0x0000A4[0x000004]
	float StaminaRestoreRate;//0x0000A8[0x000004]
	float HandsCapacity;//0x0000AC[0x000004]
	float HandsRestoreRate;//0x0000B0[0x000004]
	float OxygenCapacity;//0x0000B4[0x000004]
	float OxygenRestoreRate;//0x0000B8[0x000004]
	FVec2 WalkOverweightLimits;//0x0000BC[0x000008]
	FVec2 BaseOverweightLimits;//0x0000C4[0x000008]
	FVec2 SprintOverweightLimits;//0x0000CC[0x000008]
	FVec2 WalkSpeedOverweightLimits;//0x0000D4[0x000008]
	float float_4;//0x0000DC[0x000004]
	float PreviousWeight;//0x0000E0[0x000004]
	bool bool_1;//0x0000E4[0x000001]
	bool bool_2;//0x0000E5[0x000001]
	char gstruct22_0[0x000003];//0x0000E6[0x000003]
	bool bool_3;//0x0000E9[0x000001]
	bool bool_4;//0x0000EA[0x000001]
	bool bool_5;//0x0000EB[0x000001]
	bool bool_6;//0x0000EC[0x000001]
	unsigned char _0x000000ED[0x3];//0x000000ED (0x3) MISSED OFFSET
};
class CBreath//
{
public:
	char _0x0000[0xA4];							//0x0000
	float m_fIntensity;							//0x00A4
};
class CWalk//
{
public:
	char _0x0000[0x44];							//0x0000
	float m_fIntensity;							//0x0044
};
class CMotionEffector//
{
public:
	char _0x0000[0xD0];							//0x0000
	float m_fIntensity;							//0x00D0
};
class CForceEffector//
{
public:
	char _0x0000[0x30];							//0x0000
	float m_fIntensity;							//0x0030
};
class CShotEffector//
{
public:
	char _0x0000[0x68];							//0x0000
	float m_fIntensity;							//0x0068
};

class CProceduralWeaponAnimation : public CUnityMonoBehaviourScript
{
public:
	char _0x0018[0x10];							//0x0018
	class CBreath *m_lpBreath;					//0x0028
	class CWalk *m_lpWalk;						//0x0030
	class CMotionEffector *m_MotionReact;		//0x0038
	class CForceEffector *m_ForceReact;			//0x0040
	class CShotEffector *m_lpShooting;			//0x0048
	char _0x0050[0x00B0];						//0x0050
	DWORD Mask;									//0x0100
	char _0x0104[0x01EC];						//0x0050
	float Pitch;								//0x02F0
};
class CSkeleton : public CUnityMonoBehaviourScript
{
public:
	CUnityDictionary<CUnityString*, CMonoTransform*>* Bones;//0x000018[0x000008]
	void* _keys;//0x000020[0x000008]
	CUnityTList<CMonoTransform*>* _values;//0x000028[0x000008]
};
class CPlayerBody : public CUnityMonoBehaviourScript
{
public:
	void* _meshTransform;//0x000018[0x000008]
	class CPlayerBones* PlayerBones;//0x000020[0x000008]
	CSkeleton* SkeletonRootJoint;//0x000028[0x000008]
	CSkeleton* SkeletonHands;//0x000030[0x000008]
	void* BodySkins;//0x000038[0x000008]
	void* _watches;//0x000040[0x000008]
	void* _bodyRenderers;//0x000048[0x000008]
	void* SlotViews;//0x000050[0x000008]
	void* _itemInHands;//0x000058[0x000008]
	void* BodyCustomizationId;//0x000060[0x000008]
	void* PlayerSide;//0x000068[0x000008]
	void* PointOfView;//0x000070[0x000008]
	__int32 _layer;//0x000078[0x000004]
	__int32 _side;//0x00007C[0x000004]
	bool _active;//0x000080[0x000001]
	bool bool_0;//0x000081[0x000001]
	unsigned char _0x00000082[0x6];//0x00000082 (0x6) MISSED OFFSET
};

class CUnityTransform : public CUnityComponent
{
public:
	FVec3 GetPosition();
	FVec3 GetForward();
};
struct CBifacialTransform
{
	char _0x0000[0x10];                                        //0x0000
	CMonoTransform *_Transform;                            //0x0010
	void* uFunc__positionImitator;        //0x0018
	char _0x0020[0x88];                                        //0x0020
	bool __useImitation;                                    //0x00A8
	bool _accumulatePositionAndRotation;                    //0x00A9
	char _0x00AA[0x02];                                        //0x00AA
	FVec3 _accumulatedPosition;                                //0x00AC

	bool GetPosition(FVec3 *vOutput);
};
class CPlayerBones : public CUnityMonoBehaviourScript
{
public:
	char _0x00018[0xB8];
	CBifacialTransform* WeaponRoot;//0x0000D0[0x000008]
	CBifacialTransform* Ribcage;//0x0000D8[0x000008]
	CBifacialTransform* Head;//0x0000E0[0x000008]
	CBifacialTransform* LeftShoulder;//0x0000E8[0x000008]
	CBifacialTransform* RightShoulder;//0x0000F0[0x000008]
	CBifacialTransform* LeftThigh2;//0x0000F8[0x000008]
	CBifacialTransform* RightThigh2;//0x000100[0x000008]
	CBifacialTransform* BodyTransform;//0x000108[0x000008]
	CBifacialTransform* AnimatedTransform;//0x000110[0x000008]
	CBifacialTransform* Pelvis;//0x000118[0x000008]
	CBifacialTransform* LeftThigh1;//0x000120[0x000008]
	CBifacialTransform* RightThigh1;//0x000128[0x000008]
	CBifacialTransform* Spine3;//0x000130[0x000008]
	void* LeftHandCollider;//0x000138[0x000008]
	CBifacialTransform* Fireport;//0x000140[0x000008]
};
class CPlayer : public CUnityMonoBehaviourScript
{
public:
	char _0x0018[0x28];                                        //0x0018
	CGClass1134* m_lpMovementContext;                    //0x0040
	char _0x0040[0x60];                                        //0x0048
	CPlayerBody* m_lpPlayerBody;                            //0x00A8
	char _0x00A8[0xE0];                                        //0x00B0
	CProceduralWeaponAnimation* m_lpWeaponAni;                //0x0190
	char _0x0198[0x288];                                    //0x0198
	CUnityString* m_szLocation;                                //0x0420
	char _0x0428[0x8];                                        //0x0428
	void* m_lpDoor;                                    //0x0430
	char _0x0438[0x20];                                        //0x0438
	CProfile* m_lpProfile;                                    //0x0458
	char _0x0460[0x08];                                        //0x0460
	CGClass440* m_lpPhyiscal;                                //0x0468
	char _0x0470[0x8];                                        //0x0470
	void* m_lpBotData;                                //0x0478
	char _0x0480[0x10];                                        //0x0480
	void* m_lpHealth;                                    //0x0490
	char _0x0498[0x8];                                        //0x0498
	void* m_lpInventoryController;                    //0x04A0
	void* m_lpHandsController;                            //0x04A8
	char _0x04B0[0x40];                                        //0x04B0
	CPlayerBones* PlayerBones;                                //0x04F0
	char _0x04F8[0x2AB];                                    //0x04F8
	bool m_bIsLocalPlayer;                                    //0x07A3
};
//class CPlayer : public CUnityMonoBehaviourScript
//{
//public:
//	void* action_0;//0x000018[0x000008]
//	void* action_1;//0x000020[0x000008]
//	void* _characterController;//0x000028[0x000008]
//	void* _triggerColliderSearcher;//0x000030[0x000008]
//	void* worldInteractiveObject_0;//0x000038[0x000008]
//	CGClass1134* gclass1134_0;//0x000040[0x000008]
//	void* Pedometer;//0x000048[0x000008]
//	void* _mouseSensitivityModifiers;//0x000050[0x000008]
//	void* gdelegate25_0;//0x000058[0x000008]
//	void* LeftHandInteractionTarget;//0x000060[0x000008]
//	void* Grounder;//0x000068[0x000008]
//	void* HitReaction;//0x000070[0x000008]
//	void* _elbowBends;//0x000078[0x000008]
//	void* HandPosers;//0x000080[0x000008]
//	void* LMarkerRawBlender;//0x000088[0x000008]
//	void* LayerWeight;//0x000090[0x000008]
//	void* ThirdIkWeight;//0x000098[0x000008]
//	void* _fbbik;//0x0000A0[0x000008]
//	CPlayerBody* _playerBody;//0x0000A8[0x000008]
//	CUnityTArray<FVec3>* vector3_0;//0x0000B0[0x000008]
//	CUnityTArray<FVec4>* quaternion_3;//0x0000B8[0x000008]
//	CUnityTArray<void*>* transform_0;//0x0000C0[0x000008]
//	CUnityTArray<void*>* transform_1;//0x0000C8[0x000008]
//	CUnityTArray<void*>* transform_2;//0x0000D0[0x000008]
//	void* transform_3;//0x0000D8[0x000008]
//	void* transform_4;//0x0000E0[0x000008]
//	void* transform_5;//0x0000E8[0x000008]
//	CUnityTArray<void*>* twistRelax_0;//0x0000F0[0x000008]
//	CUnityTArray<void*>* limbIK_0;//0x0000F8[0x000008]
//	void* gameObject_0;//0x000100[0x000008]
//	void* action_2;//0x000108[0x000008]
//	void* previewMaterialSetter_0;//0x000110[0x000008]
//	void* beaconPlacer_0;//0x000118[0x000008]
//	void* firearmsEffects_0;//0x000120[0x000008]
//	void* firearmsEffects_1;//0x000128[0x000008]
//	void* compassArrow_0;//0x000130[0x000008]
//	CUnityTArray<void*>* transform_6;//0x000138[0x000008]
//	CUnityTArray<void*>* transform_7;//0x000140[0x000008]
//	void* list_0;//0x000148[0x000008]
//	void* PointOfViewChanged;//0x000150[0x000008]
//	void* AuthorityBlender;//0x000158[0x000008]
//	void* GrounderBlender;//0x000160[0x000008]
//	void* objectInHandsAnimator_0;//0x000168[0x000008]
//	void* gameObject_1;//0x000170[0x000008]
//	void* action_3;//0x000178[0x000008]
//	void* action_4;//0x000180[0x000008]
//	void* gameObject_2;//0x000188[0x000008]
//	CProceduralWeaponAnimation* proceduralWeaponAnimation_0;//0x000190[0x000008]
//	void* class726_0;//0x000198[0x000008]
//	void* DebugText;//0x0001A0[0x000008]
//	void* NestedStepSoundSource;//0x0001A8[0x000008]
//	void* _speechSource;//0x0001B0[0x000008]
//	void* FractureSound;//0x0001B8[0x000008]
//	void* PropIn;//0x0001C0[0x000008]
//	void* PropOut;//0x0001C8[0x000008]
//	void* FaceshieldOn;//0x0001D0[0x000008]
//	void* FaceshieldOff;//0x0001D8[0x000008]
//	void* audioClip_0;//0x0001E0[0x000008]
//	void* dictionary_0;//0x0001E8[0x000008]
//	void* surfaceSet_0;//0x0001F0[0x000008]
//	void* soundBank_0;//0x0001F8[0x000008]
//	void* soundBank_1;//0x000200[0x000008]
//	void* coroutine_0;//0x000208[0x000008]
//	void* coroutine_1;//0x000210[0x000008]
//	void* coroutine_2;//0x000218[0x000008]
//	void* coroutine_3;//0x000220[0x000008]
//	void* coroutine_4;//0x000228[0x000008]
//	void* coroutine_5;//0x000230[0x000008]
//	void* betterSource_0;//0x000238[0x000008]
//	void* audioClip_1;//0x000240[0x000008]
//	void* list_1;//0x000248[0x000008]
//	void* list_2;//0x000250[0x000008]
//	void* betterPropagationVolume_0;//0x000258[0x000008]
//	void* action_5;//0x000260[0x000008]
//	void* POM;//0x000268[0x000008]
//	void* TriggerZones;//0x000270[0x000008]
//	void* OnExitTriggerVisited;//0x000278[0x000008]
//	void* InteractingWithExfiltrationPoint;//0x000280[0x000008]
//	void* _animators;//0x000288[0x000008]
//	void* Speaker;//0x000290[0x000008]
//	void* gdelegate32_0;//0x000298[0x000008]
//	void* gdelegate33_0;//0x0002A0[0x000008]
//	void* Spirit;//0x0002A8[0x000008]
//	void* Logger;//0x0002B0[0x000008]
//	void* Corpse;//0x0002B8[0x000008]
//	CPlayer* LastAggressor;//0x0002C0[0x000008]
//	char LastDamageInfo[0x0000B0];//0x0002C8[0x0000B0]
//	void* GetSensitivity;//0x000378[0x000008]
//	void* GetAimingSensitivity;//0x000380[0x000008]
//	void* _openAction;//0x000388[0x000008]
//	void* ginterface136_0;//0x000390[0x000008]
//	void* renderer_0;//0x000398[0x000008]
//	void* camera_0;//0x0003A0[0x000008]
//	void* coroutine_6;//0x0003A8[0x000008]
//	void* coroutine_7;//0x0003B0[0x000008]
//	void* list_3;//0x0003B8[0x000008]
//	void* gclass2251_0;//0x0003C0[0x000008]
//	void* animator_0;//0x0003C8[0x000008]
//	void* runtimeAnimatorController_0;//0x0003D0[0x000008]
//	void* action_6;//0x0003D8[0x000008]
//	void* action_7;//0x0003E0[0x000008]
//	void* action_8;//0x0003E8[0x000008]
//	void* action_9;//0x0003F0[0x000008]
//	void* genericEventTranslator_0;//0x0003F8[0x000008]
//	void* gclass1107_0;//0x000400[0x000008]
//	void* gclass1107_1;//0x000408[0x000008]
//	void* gclass1107_2;//0x000410[0x000008]
//	void* gclass1107_3;//0x000418[0x000008]
//	CUnityString* string_0;//0x000420[0x000008]
//	void* ispawnPoint_0;//0x000428[0x000008]
//	void* interactableObject_0;//0x000430[0x000008]
//	CPlayer* player_0;//0x000438[0x000008]
//	void* placeItemTrigger_0;//0x000440[0x000008]
//	void* exfiltrationPoint_0;//0x000448[0x000008]
//	void* gclass1932_0;//0x000450[0x000008]
//	CProfile* profile_0;//0x000458[0x000008]
//	void* ginterface104_0;//0x000460[0x000008]
//	CGClass440* Physical;//0x000468[0x000008]
//	void* action_10;//0x000470[0x000008]
//	void* gclass285_0;//0x000478[0x000008]
//	void* dictionary_1;//0x000480[0x000008]
//	void* _healthController;//0x000488[0x000008]
//	void* _hitColliders;//0x000490[0x000008]
//	CGClass1797* _inventoryController;//0x000498[0x000008]
//	void* _handsController;//0x0004A0[0x000008]
//	void* _questController;//0x0004A8[0x000008]
//	void* playerToGrassConnector_0;//0x0004B0[0x000008]
//	void* action_11;//0x0004B8[0x000008]
//	CUnityString* string_1;//0x0004C0[0x000008]
//	void* Tracking;//0x0004C8[0x000008]
//	void* gdelegate26_1;//0x0004D0[0x000008]
//	void* waitForFixedUpdate_0;//0x0004D8[0x000008]
//	void* _playerLookRaycastTransform;//0x0004E0[0x000008]
//	CPlayerBones* PlayerBones;//0x0004E8[0x000008]
//	void* _preAllocatedArmorComponents;//0x0004F0[0x000008]
//	void* action_12;//0x0004F8[0x000008]
//	void* gclass270_0;//0x000500[0x000008]
//	void* ExfilUnsubscribe;//0x000508[0x000008]
//	void* SessionEndUnsubscribe;//0x000510[0x000008]
//	void* abstractProcess_0;//0x000518[0x000008]
//	void* slot_0;//0x000520[0x000008]
//	void* action_13;//0x000528[0x000008]
//	void* action_14;//0x000530[0x000008]
//	CUnityTArray<__int32>* equipmentSlot_0;//0x000538[0x000008]
//	void* _removeFromHandsCallback;//0x000540[0x000008]
//	void* callback_0;//0x000548[0x000008]
//	bool bool_0;//0x000550[0x000001]
//	unsigned char _0x00000551[0x3];//0x00000551 (0x3) MISSED OFFSET
//	float float_0;//0x000554[0x000004]
//	float float_1;//0x000558[0x000004]
//	bool bool_1;//0x00055C[0x000001]
//	bool bool_2;//0x00055D[0x000001]
//	unsigned char _0x0000055E[0x2];//0x0000055E (0x2) MISSED OFFSET
//	FVec3 HeadRotation;//0x000560[0x00000C]
//	float _mouseSensitivityModifier;//0x00056C[0x000004]
//	FVec2 vector2_0;//0x000570[0x000008]
//	FVec2 vector2_1;//0x000578[0x000008]
//	float TrunkRotationLimit;//0x000580[0x000004]
//	float PoseMemo;//0x000584[0x000004]
//	float float_2;//0x000588[0x000004]
//	float float_3;//0x00058C[0x000004]
//	float float_4;//0x000590[0x000004]
//	float _prevHeight;//0x000594[0x000004]
//	float HeightSmoothTime;//0x000598[0x000004]
//	float float_5;//0x00059C[0x000004]
//	float float_6;//0x0005A0[0x000004]
//	float float_7;//0x0005A4[0x000004]
//	float RibcageScaleCurrent;//0x0005A8[0x000004]
//	float RibcageScaleCurrentTarget;//0x0005AC[0x000004]
//	FVec2 UtilityLayerRange;//0x0005B0[0x000008]
//	float UtilityLayerLerpSpeed;//0x0005B8[0x000004]
//	bool GripAutoAdjust;//0x0005BC[0x000001]
//	unsigned char _0x000005BD[0x3];//0x000005BD (0x3) MISSED OFFSET
//	float ThirdPersonWeaponRootAuthority;//0x0005C0[0x000004]
//	float float_9;//0x0005C4[0x000004]
//	float float_10;//0x0005C8[0x000004]
//	float float_11;//0x0005CC[0x000004]
//	float float_12;//0x0005D0[0x000004]
//	float float_13;//0x0005D4[0x000004]
//	float float_14;//0x0005D8[0x000004]
//	float float_15;//0x0005DC[0x000004]
//	float float_16;//0x0005E0[0x000004]
//	float float_17;//0x0005E4[0x000004]
//	float float_18;//0x0005E8[0x000004]
//	float float_19;//0x0005EC[0x000004]
//	bool bool_3;//0x0005F0[0x000001]
//	bool bool_4;//0x0005F1[0x000001]
//	bool bool_5;//0x0005F2[0x000001]
//	bool bool_6;//0x0005F3[0x000001]
//	bool bool_7;//0x0005F4[0x000001]
//	bool bool_8;//0x0005F5[0x000001]
//	unsigned char _0x000005F6[0x2];//0x000005F6 (0x2) MISSED OFFSET
//	FVec3 vector3_1;//0x0005F8[0x00000C]
//	FVec3 vector3_2;//0x000604[0x00000C]
//	FVec3 vector3_3;//0x000610[0x00000C]
//	FVec3 vector3_4;//0x00061C[0x00000C]
//	FVec3 vector3_5;//0x000628[0x00000C]
//	FVec4 quaternion_0;//0x000634[0x000010]
//	FVec4 quaternion_1;//0x000644[0x000010]
//	FVec4 quaternion_2;//0x000654[0x000010]
//	float float_20;//0x000664[0x000004]
//	float float_21;//0x000668[0x000004]
//	bool _isDeadAlready;//0x00066C[0x000001]
//	bool bool_9;//0x00066D[0x000001]
//	unsigned char _0x0000066E[0x2];//0x0000066E (0x2) MISSED OFFSET
//	FVec3 vector3_6;//0x000670[0x00000C]
//	FVec4 quaternion_4;//0x00067C[0x000010]
//	bool bool_10;//0x00068C[0x000001]
//	unsigned char _0x0000068D[0x3];//0x0000068D (0x3) MISSED OFFSET
//	int CurrentSurface;//0x000690[0x000004]
//	int environmentType_0;//0x000694[0x000004]
//	bool HeavyBreath;//0x000698[0x000001]
//	unsigned char _0x00000699[0x3];//0x00000699 (0x3) MISSED OFFSET
//	float VerticalSoundFactor;//0x00069C[0x000004]
//	bool Muffled;//0x0006A0[0x000001]
//	unsigned char _0x000006A1[0x3];//0x000006A1 (0x3) MISSED OFFSET
//	char raycastHit_0[0x00002C];//0x0006A4[0x00002C]
//	bool bool_11;//0x0006D0[0x000001]
//	bool OcclusionDirty;//0x0006D1[0x000001]
//	bool DistanceDirty;//0x0006D2[0x000001]
//	bool PreviousFaceShield;//0x0006D3[0x000001]
//	FVec3 SpeechLocalPosition;//0x0006D4[0x00000C]
//	int layerMask_0;//0x0006E0[0x000004]
//	bool bool_12;//0x0006E4[0x000001]
//	unsigned char _0x000006E5[0x3];//0x000006E5 (0x3) MISSED OFFSET
//	float float_25;//0x0006E8[0x000004]
//	float float_26;//0x0006EC[0x000004]
//	float float_28;//0x0006F0[0x000004]
//	float float_29;//0x0006F4[0x000004]
//	bool bool_13;//0x0006F8[0x000001]
//	unsigned char _0x000006F9[0x3];//0x000006F9 (0x3) MISSED OFFSET
//	float float_30;//0x0006FC[0x000004]
//	float float_31;//0x000700[0x000004]
//	float float_32;//0x000704[0x000004]
//	float float_33;//0x000708[0x000004]
//	float float_34;//0x00070C[0x000004]
//	float float_35;//0x000710[0x000004]
//	float float_36;//0x000714[0x000004]
//	float float_37;//0x000718[0x000004]
//	float float_38;//0x00071C[0x000004]
//	float float_39;//0x000720[0x000004]
//	float float_40;//0x000724[0x000004]
//	bool bool_14;//0x000728[0x000001]
//	unsigned char _0x00000729[0x3];//0x00000729 (0x3) MISSED OFFSET
//	int LastDamageType;//0x00072C[0x000004]
//	int LastDamagedBodyPart;//0x000730[0x000004]
//	bool PlacingBeacon;//0x000734[0x000001]
//	bool Destroyed;//0x000735[0x000001]
//	unsigned char _0x00000736[0x2];//0x00000736 (0x2) MISSED OFFSET
//	int EnabledAnimators;//0x000738[0x000004]
//	int LastBodyPart;//0x00073C[0x000004]
//	float _corpseAppliedForce;//0x000740[0x000004]
//	float float_41;//0x000744[0x000004]
//	float float_42;//0x000748[0x000004]
//	__int32 int_3;//0x00074C[0x000004]
//	bool bool_15;//0x000750[0x000001]
//	bool bool_16;//0x000751[0x000001]
//	bool bool_17;//0x000752[0x000001]
//	bool bool_18;//0x000753[0x000001]
//	bool bool_19;//0x000754[0x000001]
//	unsigned char _0x00000755[0x3];//0x00000755 (0x3) MISSED OFFSET
//	float float_43;//0x000758[0x000004]
//	bool bool_20;//0x00075C[0x000001]
//	bool bool_21;//0x00075D[0x000001]
//	unsigned char _0x0000075E[0x2];//0x0000075E (0x2) MISSED OFFSET
//	__int32 int_4;//0x000760[0x000004]
//	int _updateQueue;//0x000764[0x000004]
//	int _armsUpdateQueue;//0x000768[0x000004]
//	int _armsUpdateMode;//0x00076C[0x000004]
//	int _bodyUpdateMode;//0x000770[0x000004]
//	float float_44;//0x000774[0x000004]
//	bool _armsupdated;//0x000778[0x000001]
//	unsigned char _0x00000779[0x3];//0x00000779 (0x3) MISSED OFFSET
//	float _armsTime;//0x00077C[0x000004]
//	bool _bodyupdated;//0x000780[0x000001]
//	unsigned char _0x00000781[0x3];//0x00000781 (0x3) MISSED OFFSET
//	float _bodyTime;//0x000784[0x000004]
//	__int32 _nFixedFrames;//0x000788[0x000004]
//	float _fixedTime;//0x00078C[0x000004]
//	float LastDeltaTime;//0x000790[0x000004]
//	bool _manuallyUpdated;//0x000794[0x000001]
//	CEDoorState edoorState_0;//0x000795[0x000001]
//	bool bool_22;//0x000796[0x000001]
//	bool bool_23;//0x000797[0x000001]
//	bool bool_24;//0x000798[0x000001]
//	bool bool_25;//0x000799[0x000001]
//	bool AggressorFound;//0x00079A[0x000001]
//	bool bool_26;//0x00079B[0x000001]
//	int eprocessStatus_0;//0x00079C[0x000004]
//	float float_45;//0x0007A0[0x000004]
//	__int32 int_5;//0x0007A4[0x000004]
//
//};
class CPoolSafeMonoBehaviour : public CUnityMonoBehaviourScript
{
public:
	char _0x0018[0x08];									//0x0018
};
class CCamera : public CUnityMonoBehaviourScript
{
public:
	CUnityGameObject *GetGameObject();
};
struct CamerasArray
{
	CCamera**	Cameras;			//0x0000
	INT64		SizeMin;			//0x0008
	INT64		SizeCur;			//0x0010
	INT64		SizeMax;			//0x0018
};
class CVisorEffect
{
public:
	char _0x0000[0x00B8];
	float Intensity;//0x0000B8[0x000004]
};
class CNightvision
{
public:
	char _0x0000[0x00A8];
	float Intensity;//0x0000A8[0x000004]
	char _0x00AC[0x0020];
	bool _on;//0x0000CC[0x000001]
};
class CThermalVision
{
public:
	char _0x0000[0x00D0];
	bool _on;//0x0000D0[0x000001]
};
//class CInteractableObject : public CPoolSafeMonoBehaviour
//{
//public:
//	char _0x0020[0x20];
//};
//
//class CWorldInteractiveObject : public CInteractableObject
//{
//public:
//	CUnityString* KeyId;//0x000040[0x000008]
//	CUnityString* Id;//0x000048[0x000008]
//	class CDoorHandle* LockHandle;//0x000050[0x000008]
//	CUnityTArray<class CAudioClip*>* ShutSound;//0x000058[0x000008]
//	CUnityTArray<class CAudioClip*>* SqueakSound;//0x000060[0x000008]
//	CUnityTArray<class CAudioClip*>* OpenSound;//0x000068[0x000008]
//	class CNavMeshObstacle* Obstacle;//0x000070[0x000008]
//	class CCollider* collider_0;//0x000078[0x000008]
//	class CGDelegate45* gdelegate45_0;//0x000080[0x000008]
//	class CInteractionState* _interaction;//0x000088[0x000008]
//	class CInteractionState* _previousInteraction;//0x000090[0x000008]
//	class CDoorHandle* _handle;//0x000098[0x000008]
//	class CUnityTArray<class CGripPose*>* Grips;//0x0000A0[0x000008]
//	CEDoorState Snap;//0x0000A8[0x000001]
//	unsigned char _0x000000A9[0x3];//0x000000A9 (0x3) MISSED OFFSET
//	__int32 int_2;//0x0000AC[0x000004]
//	float _currentAngle;//0x0000B0[0x000004]
//	FVec3 interactPosition1;//0x0000B4[0x00000C]
//	FVec3 interactPosition2;//0x0000C0[0x00000C]
//	FVec3 viewTarget1;//0x0000CC[0x00000C]
//	float OpenAngle;//0x0000D8[0x000004]
//	float CloseAngle;//0x0000DC[0x000004]
//	int DoorAxis;//0x0000E0[0x000004]
//	int DoorForward;//0x0000E4[0x000004]
//	__int32 PushID;//0x0000E8[0x000004]
//	__int32 CloseID;//0x0000EC[0x000004]
//	float ShutShift;//0x0000F0[0x000004]
//	float _ignoreSyncUntil;//0x0000F4[0x000004]
//	CEDoorState edoorState_0;//0x0000F8[0x000001]
//	CEDoorState _doorState;//0x0000F9[0x000001]
//	CEDoorState edoorState_1;//0x0000FA[0x000001]
//	bool Operatable;//0x0000FB[0x000001]
//	bool _shutPlayed;//0x0000FC[0x000001]
//	bool bool_0;//0x0000FD[0x000001]
//	CEDoorState edoorState_2;//0x0000FE[0x000001]
//	unsigned char _0x000000FF[0x1];//0x000000FF (0x1) MISSED OFFSET
//	float float_4;//0x000100[0x000004]
//	unsigned char _0x00000104[0x4];//0x00000104 (0x4) MISSED OFFSET
//};
//class CDoor : public CWorldInteractiveObject
//{
//public:
//};