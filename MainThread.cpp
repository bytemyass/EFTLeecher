#include "globals.h"
#include "MonoClasses.h"

DWORD dwConnectionStatusColor = RGB(255, 0, 0);
float fMaxStamina = 0.0f;
bool bWorldPointerFound = false;
bool bLocalPlayerFound = false;
bool bLocalPlayerTextSet = false;
bool bAutoDisconnectAfterRaidEnds = false;
bool bRemoveVisorEffects = false;
bool bNightVisionEffect = false;
bool bThermalVisionEffect = false;
bool bNoWeight = false;
bool bNoRecoil = false;
bool bNoStamina = false;
bool bUnlockEverything = false;
#ifdef ENABLE_AIMBOT
bool bAimbotEnabled = false;
int iAimbotBone = 0;
int iAimbotHotkey = 0;
#endif
int iJumpMultiplier = 1;
int iThrowMultiplier = 1;
int iHearingMultiplier = 1;

//normal map names
wchar_t *szMapNames[] =
{
	L"Factory",
	L"Factory",
	L"Woods",
	L"Customs",
	L"Shoreline",
	L"Interchange",
	L"Reserve",
	L"Labs"
};
wchar_t *szEFTMapNames[] =
{
	L"factory4_day",
	L"factory4_night",
	L"Woods",
	L"bigmap",
	L"Shoreline",
	L"Interchange",
	L"RezervBase",
	L"laboratory"
};

CGameWorld *GetGameWorld(CGameWorld *lpWorldData)
{
	CUnityGameObjectManager* objManagerPtr = DMADevice::MemReadPtr<CUnityGameObjectManager*>(DMADevice::dwUnityPlayerBaseAddress + UNITY_OBJECT_LIST);
	if (objManagerPtr == 0)
		return 0;

	CUnityGameObjectManager objManager = {};
	if (!DMADevice::MemRead(objManagerPtr, &objManager, sizeof(CUnityGameObjectManager)))
		return 0;

	int iCount = 0;
	CUnityListElement<CUnityListNode<CUnityGameObject>> *lpObject = objManager.m_Active.m_lpNext;
	while (lpObject != objManager.m_Active.m_lpPrev)
	{
		iCount++;
		if (iCount > 5000)
			return 0;

		CUnityListNode<CUnityGameObject> lpObjectDataLoop = {};
		if (!lpObject || !DMADevice::MemRead(lpObject, &lpObjectDataLoop, sizeof(CUnityListNode<CUnityGameObject>)))
			break;

		CUnityGameObject lpGameObject = {};
		if (DMADevice::MemRead(lpObjectDataLoop.m_lpData, &lpGameObject, sizeof(CUnityGameObject)))
		{
			char szObjectName[64] = {};
			if (DMADevice::MemRead(lpGameObject.m_szObjectName, szObjectName, 32, false) && strcmp(szObjectName, "GameWorld") == 0)
			{
				CGameWorld* lpGameWorld = (CGameWorld*)lpGameObject.m_aComponents.GetByName("ClientNetworkGameWorld,ClientLocalGameWorld");
				if (lpGameWorld && DMADevice::MemRead(lpGameWorld, lpWorldData, sizeof(CGameWorld)) && lpWorldData->m_lpComponent)
				{
					CUnityTList<CPlayer*> lpPlayerList = {};
					if (DMADevice::MemRead(lpWorldData->RegisteredPlayers, &lpPlayerList, sizeof(CUnityTList<CPlayer*>)) && lpPlayerList.dwSize > 0)
						return lpGameWorld;
				}
			}
		}
		lpObject = (CUnityListElement<CUnityListNode<CUnityGameObject>>*)lpObjectDataLoop.m_lpNext;
	}
	return 0;
}

CUnityGameObject *GetMainCamera()
{
	CamerasArray *lpCameras = DMADevice::MemReadPtr<CamerasArray*>(DMADevice::dwUnityPlayerBaseAddress + UNITY_CAMERA_LIST);
	if (lpCameras)
	{
		CamerasArray lpCameraArray = {};
		if (DMADevice::MemRead(lpCameras, &lpCameraArray, sizeof(CamerasArray)) && lpCameraArray.Cameras && lpCameraArray.SizeCur > 0)
		{
			CCamera **lpCameraList = (CCamera**)calloc(lpCameraArray.SizeCur, sizeof(void*));
			if (lpCameraList == 0)
				return 0;

			if (DMADevice::MemRead(lpCameraArray.Cameras, lpCameraList, sizeof(void*) * lpCameraArray.SizeCur))
			{
				for (int i = 0; i < lpCameraArray.SizeCur; i++)
				{
					CCamera* pCamera = lpCameraList[i];
					if (pCamera)
					{
						CUnityGameObject *lpGameObject = DMADevice::MemReadPtr<CUnityGameObject*>((DWORD_PTR)pCamera + 0x30);
						if (lpGameObject)
						{
							CUnityGameObject pGameObject = {};
							if (DMADevice::MemRead(lpGameObject, &pGameObject, sizeof(CUnityGameObject)))
							{
								char szObjectName[64] = {};
								if (DMADevice::MemRead(pGameObject.m_szObjectName, szObjectName, 64))
								{
									if (strcmp(szObjectName, "FPS Camera") == 0)
									{
										free(lpCameraList);
										return lpGameObject;
									}
								}
							}
						}
					}
				}
			}
			free(lpCameraList);
			lpCameraList = 0;
		}
	}
	return 0;
}

CPlayer* GetLocalPlayer(CGameWorld *lpWorldData, CUnityString* lpLocalProfileId)
{
	CPlayer lpPlayerData = {};
	CProfile lpPlayerProfileData = {};
	CUnityString lpUnityStringData = {};
	CUnityTList<CPlayer*> lpPlayerList = {};
	CUnityTListCounter<CPlayer*, 100> lpPlayerListArray = {};
	if (DMADevice::MemRead(lpWorldData->RegisteredPlayers, &lpPlayerList, sizeof(CUnityTList<CPlayer*>)) && lpPlayerList.dwSize > 0)
	{
		if (DMADevice::MemRead(lpPlayerList.lpList, &lpPlayerListArray, TLIST_SIZE(CPlayer*, lpPlayerList.dwSize)))
		{
			for (int i = 0; i < lpPlayerList.dwSize; i++)
			{
				CPlayer* lpPlayerPtr = lpPlayerListArray.lpListArray[i];
				if (!lpPlayerPtr || 
					!DMADevice::MemRead(lpPlayerPtr, &lpPlayerData, sizeof(CPlayer)) || 
					!DMADevice::MemRead(lpPlayerData.m_lpProfile, &lpPlayerProfileData, sizeof(CProfile)))
					continue;

				DMADevice::MemReadUnityString(lpPlayerProfileData.Id, &lpUnityStringData);

				if (lpPlayerData.m_bIsLocalPlayer || (lpUnityStringData == (*lpLocalProfileId)))
					return lpPlayerPtr;
			}
		}
	}
	return 0;
}

void Camera_Hack_Effects(CUnityGameObject* lpMainCameraGameObject)
{
	float fSet = 0.0f;

	if (lpMainCameraGameObject)
	{
		CUnityGameObject pGameObject = {};
		if (DMADevice::MemRead(lpMainCameraGameObject, &pGameObject, sizeof(CUnityGameObject)))
		{
			CVisorEffect* lpCamGameVisorEffect = (CVisorEffect*)pGameObject.m_aComponents.GetByName("VisorEffect");
			if (lpCamGameVisorEffect)
			{
				fSet = bRemoveVisorEffects ? 0.0f : 1.0f;

				DMADevice::MemWrite((DWORD_PTR)lpCamGameVisorEffect + offsetof(CVisorEffect, Intensity), &fSet, sizeof(float));
			}

			CNightvision* lpCamGameNightVisionEffect = (CNightvision*)pGameObject.m_aComponents.GetByName("NightVision");
			if (lpCamGameNightVisionEffect)
			{
				fSet = bNightVisionEffect ? 0.0f : 1.0f;

				DMADevice::MemWrite((DWORD_PTR)lpCamGameNightVisionEffect + offsetof(CNightvision, Intensity), &fSet, sizeof(float));
				DMADevice::MemWrite((DWORD_PTR)lpCamGameNightVisionEffect + offsetof(CNightvision, _on), &bNightVisionEffect, sizeof(bool));
			}

			CThermalVision* lpCamGameThermalEffect = (CThermalVision*)pGameObject.m_aComponents.GetByName("ThermalVision");
			if (lpCamGameThermalEffect)
			{
				DMADevice::MemWrite((DWORD_PTR)lpCamGameThermalEffect + offsetof(CThermalVision, _on), &bThermalVisionEffect, sizeof(bool));

				DWORD64 dwThermial1 = DMADevice::MemReadPtr<DWORD64>((DWORD_PTR)lpCamGameThermalEffect + 0x90);
				if (dwThermial1)
				{
					DWORD64 dwThermial2 = DMADevice::MemReadPtr<DWORD64>((DWORD_PTR)dwThermial1 + 0x10);
					if (dwThermial2)
					{
						/*BYTE bValue = 224;
						DMADevice::MemWrite(dwThermial2 + 0x38, &bValue, sizeof(BYTE));*/
					}

				}
			}
		}
	}	
}

void LocalPlayerHacks(CPlayer* lpLocalPlayerPointer, bool bIsThisMapInterchange)
{
	CPlayer lpLocalPlayer = {};
	if (!DMADevice::MemRead(lpLocalPlayerPointer, &lpLocalPlayer, sizeof(lpLocalPlayer)))
		return;

	//physical stuff
	float fSet = 100.0f;

	//check variable and pointer
	if (bNoStamina)
	{
		//keep a variable for data
		CGClass440 bPhyData = {};

		//read the whole class
		if (DMADevice::MemRead(lpLocalPlayer.m_lpPhyiscal, &bPhyData, sizeof(CGClass440)))
		{
			//again read the whole class so we can grab current stamina
			CGClass439 gStamina = {};
			if (DMADevice::MemRead(bPhyData.Stamina, &gStamina, sizeof(CGClass439)))
			{
				//check our variable if its been set if its not then lets set stamina to the "default value"
				if (fMaxStamina == 0.0f)
					fMaxStamina = gStamina.Current;
				else
					//we have the default value so just keep setting it ;)
					DMADevice::MemWrite(((QWORD)bPhyData.Stamina) + offsetof(CGClass439, Current), &fMaxStamina, sizeof(float));
			}
			if (DMADevice::MemRead(bPhyData.HandsStamina, &gStamina, sizeof(CGClass439)))
			{
				DMADevice::MemWrite(((QWORD)bPhyData.HandsStamina) + offsetof(CGClass439, Current), &fSet, sizeof(float));
			}
			if (DMADevice::MemRead(bPhyData.Oxygen, &gStamina, sizeof(CGClass439)))
			{
				DMADevice::MemWrite(((QWORD)bPhyData.Oxygen) + offsetof(CGClass439, Current), &fSet, sizeof(float));
			}
		}
	}

	//weapon stuff
	//check the variable
	if (bNoRecoil)
	{
		//value we want to set
		fSet = 0.0f;

		//Grab all the class data
		CProceduralWeaponAnimation bProWeaponAnimation = {};
		if (DMADevice::MemRead(lpLocalPlayer.m_lpWeaponAni, &bProWeaponAnimation, sizeof(CProceduralWeaponAnimation)))
		{
			//&=~ means REMOVE bit's from a DWORD or BYTE &=| means set bits yeah alot of learning if you want to understand bits google it :) lol
			//please read online about bit mask there VERY VERY hard to explain and take awhile to understand bit mask and flags is what you want to look for!
			bProWeaponAnimation.Mask &= ~CEProceduralAnimationMask::Walking;

			//set the breath intensity to 0.0f
			if (bProWeaponAnimation.m_lpBreath)
				DMADevice::MemWrite(((QWORD)bProWeaponAnimation.m_lpBreath) + offsetof(CBreath, m_fIntensity), &fSet, sizeof(float));

			//set the walk intensity to 0.0f
			if (bProWeaponAnimation.m_lpWalk)
				DMADevice::MemWrite(((QWORD)bProWeaponAnimation.m_lpWalk) + offsetof(CWalk, m_fIntensity), &fSet, sizeof(float));

			//set the motion react to 0.0f
			if (bProWeaponAnimation.m_MotionReact)
				DMADevice::MemWrite(((QWORD)bProWeaponAnimation.m_MotionReact) + offsetof(CMotionEffector, m_fIntensity), &fSet, sizeof(float));

			//set the force react to 0.0f
			if (bProWeaponAnimation.m_ForceReact)
				DMADevice::MemWrite(((QWORD)bProWeaponAnimation.m_ForceReact) + offsetof(CForceEffector, m_fIntensity), &fSet, sizeof(float));

			//this is no recoil ONLY everything else is no sway :')
			if (bProWeaponAnimation.m_lpShooting)
				DMADevice::MemWrite(((QWORD)bProWeaponAnimation.m_lpShooting) + offsetof(CShotEffector, m_fIntensity), &fSet, sizeof(float));

			//set the new mask on the weapon
			DMADevice::MemWrite(((QWORD)lpLocalPlayer.m_lpWeaponAni) + offsetof(CProceduralWeaponAnimation, Mask), &bProWeaponAnimation.Mask, sizeof(DWORD));
		}
		
	}

	////unlock all doors etc
	//if (bUnlockEverything)
	//{
	//	//variable to store the saved results
	//	CDoor bInteractableData = {};
	//
	//	//grab the whole struct data its QUICKER and easyer
	//	if (DMADevice::MemRead(lpLocalPlayer.interactableObject_0, &bInteractableData, sizeof(CDoor)))
	//	{
	//		//first we declare what we want to find which is EVERYTHING
	//		char *szToFind = "KeycardDoor,Door,LootableContainer,Trunk";
	//
	//		//now we check if this map is interchange if so then we declare that we want everything BUT keycard doors 
	//		if(bIsThisMapInterchange)
	//			szToFind = "Door,LootableContainer,Trunk";
	//
	//		//now look for this 
	//		if(bInteractableData.GetComonent(szToFind))
	//		{
	//			//we check the status of the door is it locked?
	//			if (bInteractableData._doorState == CEDoorState::DS_Locked)
	//			{
	//				//we have to declare a variable to set memory (well we dont but easyer)
	//				CEDoorState ioDoorState = CEDoorState::DS_Shut;
	//
	//				//now write memory there no need to check if written as if a door dont open its not gonna kill us? well i hope not!
	//				DMADevice::MemWrite(((QWORD)lpLocalPlayer.interactableObject_0) + offsetof(CWorldInteractiveObject, _doorState), &ioDoorState, sizeof(CEDoorState));
	//			}
	//		}
	//	}
	//}

	//variable to store the saved results
	CProfile lpProfile = {};

	//grab the whole struct data its QUICKER and easyer
	if (DMADevice::MemRead(lpLocalPlayer.m_lpProfile, &lpProfile, sizeof(CProfile)))
	{
		//variable to store the saved results
		CGClass1205 lpSkills = {};

		//grab the whole struct data its QUICKER and easyer
		if (DMADevice::MemRead(lpProfile.Skills, &lpSkills, sizeof(CGClass1205)))
		{
			//keep an array a variable
			CUnityTArrayCounter<CGClass1097*, 100> lpSkillArray = {};

			//grab the first part which is the start "size and first data" then we grab it ALL!
			if (DMADevice::MemRead(lpSkills.Skills, &lpSkillArray, sizeof(CUnityTArray<CGClass1097*>)))
			{
				//we grab ALL the tarray which is unity lovly arrays!
				if (DMADevice::MemRead(lpSkills.Skills, &lpSkillArray, TARRAY_SIZE(CGClass1097*, lpSkillArray.dwSize)))
				{
					//loop ALL the skills!
					for (int i = 0; i < lpSkillArray.dwSize; i++)
					{
						//grab the pointer to the skill
						CGClass1097 *lpSkill = lpSkillArray.lpListArray[i];
						if (!lpSkill)
							continue;
							
						//keep a copy of the data
						CGClass1097 SkillData = {};

						//we need to read the skill data BECAUSE EFT dont sort the skill's meaning str could be 10 index etc etc
						if (DMADevice::MemRead(lpSkill, &SkillData, sizeof(CGClass1097)))
						{
							//loop all the skills to find ours
							for (int s = 0; s < Skills_Max; s++)
							{
								//check this index
								if (SkillData.Id == s)
								{
									//do we want to change this skill level?
									if (sSkillData[s].m_bLvlEnabled)
									{
										//100 exp * level 51 max level is 50 but EFT checks if level is > 50 which would need to be 51
										float fSkillExp = (100.0f * sSkillData[s].m_iLevel);

										//set the memory for the EXP
										DMADevice::MemWrite(((QWORD)lpSkill) + offsetof(CGClass1097, Current), &fSkillExp, sizeof(float));
									}
								}
							}
						}
					}
				}
			}
#define SKILL_SET_BUFF(t,x,v) if(lpSkills.##x) { t val = v; DMADevice::MemWrite((((DWORD64)lpSkills.##x) + offsetof(CGClass1103<t>, Value)), &val, sizeof(t)); }

			//Endurance
			SKILL_SET_BUFF(float, EnduranceBuffEnduranceInc, 1.5f);
			SKILL_SET_BUFF(float, EnduranceHands, 1.0f);
			SKILL_SET_BUFF(float, EnduranceBuffJumpCostRed, 1.0f);
			SKILL_SET_BUFF(float, EnduranceBuffBreathTimeInc, 1.0f);
			SKILL_SET_BUFF(float, EnduranceBuffRestoration, 1.5f);
			SKILL_SET_BUFF(float, EnduranceBreathElite, 1.5f);

			//Strength
			//SKILL_SET_BUFF(float, StrengthBuffLiftWeightInc, 10.0f);
			SKILL_SET_BUFF(float, StrengthBuffSprintSpeedInc, 0.3f);
			SKILL_SET_BUFF(float, StrengthBuffJumpHeightInc, (0.1f * iJumpMultiplier));//oi michael cunt? leave the values alone?
			SKILL_SET_BUFF(float, StrengthBuffAimFatigue, 0.2f);
			SKILL_SET_BUFF(float, StrengthBuffThrowDistanceInc, (0.1f * iThrowMultiplier));//oi michael cunt? leave the values alone?
			SKILL_SET_BUFF(float, StrengthBuffMeleePowerInc, 0.3f);
			//SKILL_SET_BUFF(bool, StrengthBuffElite, true);
			SKILL_SET_BUFF(float, StrengthBuffMeleeCrits, 0.5f);

			//Vitality
			SKILL_SET_BUFF(float, VitalityBuffBleedChanceRed, 1.0f);
			SKILL_SET_BUFF(float, VitalityBuffSurviobilityInc, 1.0f);
			SKILL_SET_BUFF(bool, VitalityBuffRegeneration, true);
			SKILL_SET_BUFF(bool, VitalityBuffBleedStop, true);

			//Health
			SKILL_SET_BUFF(float, HealthBreakChanceRed, 1.0f);
			SKILL_SET_BUFF(float, HealthOfflineRegenerationInc, 999.0f);
			SKILL_SET_BUFF(float, HealthEnergy, 1.0f);
			SKILL_SET_BUFF(float, HealthHydration, 1.0f);
			SKILL_SET_BUFF(bool, HealthEliteAbsorbDamage, true);
			//SKILL_SET_BUFF(float, HealthElitePosion, 999.0f);

			//Stress
			SKILL_SET_BUFF(float, StressPain, 1.0f);
			//SKILL_SET_BUFF(float, StressTremor, 999.0f);
			SKILL_SET_BUFF(bool, StressBerserk, true);

			//Metabolism
			SKILL_SET_BUFF(float, MetabolismRatioPlus, 1.0f);
			SKILL_SET_BUFF(bool, MetabolismEliteBuffNoDyhydration, true);

			//Perception
			SKILL_SET_BUFF(float, PerceptionHearing, (1.2f * iHearingMultiplier));//oi michael cunt? leave the values alone?
			SKILL_SET_BUFF(float, PerceptionLootDot, 1.0f);
			SKILL_SET_BUFF(bool, PerceptionEliteNoIdea, true);

			//Intellect
			SKILL_SET_BUFF(float, IntellectLearningSpeed, 1.0f);
			SKILL_SET_BUFF(float, IntellectWeaponMaintance, 1.0f);
			SKILL_SET_BUFF(bool, IntellectEliteNaturalLearner, true);
			SKILL_SET_BUFF(bool, IntellectEliteAmmoCounter, true);
			SKILL_SET_BUFF(bool, IntellectEliteContainerScope, true);

			//Attention
			SKILL_SET_BUFF(float, AttentionLootSpeed, 1.0f);
			SKILL_SET_BUFF(float, AttentionExamine, 10.0f);
			SKILL_SET_BUFF(float, AttentionEliteLuckySearch, 100.0f);
			SKILL_SET_BUFF(bool, AttentionEliteExtraLootExp, true);

			//Magdrills
			//SKILL_SET_BUFF(float, MagDrillsLoadSpeed, 180.0f);
			//SKILL_SET_BUFF(float, MagDrillsUnloadSpeed, 100.0f);
			//SKILL_SET_BUFF(float, MagDrillsInventoryCheckSpeed, 100.0f);
			//SKILL_SET_BUFF(float, MagDrillsInventoryCheckAccuracy, 100.0f);
			//SKILL_SET_BUFF(bool, MagDrillsInstantCheck, true);
			//SKILL_SET_BUFF(bool, MagDrillsLoadProgression, true);

			//Charisma
			/*
			SKILL_SET_BUFF(float, CharismaBuff1, 999.0f);
			SKILL_SET_BUFF(float, CharismaBuff2, 999.0f);
			SKILL_SET_BUFF(bool, CharismaEliteBuff1, true);
			SKILL_SET_BUFF(float, CharismaEliteBuff2, 999.0f);
			SKILL_SET_BUFF(float, MemoryMentalForget1, 999.0f);
			SKILL_SET_BUFF(float, MemoryMentalForget2, 999.0f);
			SKILL_SET_BUFF(bool, MemoryEliteMentalRecoil, true);
			SKILL_SET_BUFF(float, AimMasterSpeed, 999.0f);
			SKILL_SET_BUFF(float, AimMasterWiggle, 999.0f);
			SKILL_SET_BUFF(bool, AimMasterElite, true);
			SKILL_SET_BUFF(float, RecoilControlImprove, 999.0f);
			SKILL_SET_BUFF(float, RecoilControlElite, 999.0f);
			SKILL_SET_BUFF(float, TroubleFixing, 999.0f);
			SKILL_SET_BUFF(float, TroubleFixingElite, 999.0f);
			SKILL_SET_BUFF(float, ThrowingStrengthBuff, 999.0f);
			SKILL_SET_BUFF(float, ThrowingEnergyExpenses, 999.0f);
			SKILL_SET_BUFF(bool, ThrowingEliteBuff, true);
			SKILL_SET_BUFF(float, DrawSpeed, 999.0f);
			SKILL_SET_BUFF(float, DrawSound, 999.0f);
			SKILL_SET_BUFF(bool, DrawElite, true);
			SKILL_SET_BUFF(bool, DrawTremor, true);
			SKILL_SET_BUFF(float, CovertMovementSoundVolume, 999.0f);
			SKILL_SET_BUFF(float, CovertMovementEquipment, 999.0f);
			SKILL_SET_BUFF(float, CovertMovementSpeed, 999.0f);
			SKILL_SET_BUFF(bool, CovertMovementElite, true);
			SKILL_SET_BUFF(float, CovertMovementLoud, 999.0f);
			SKILL_SET_BUFF(float, ProneMovementSpeed, 999.0f);
			SKILL_SET_BUFF(float, ProneMovementVolume, 999.0f);
			SKILL_SET_BUFF(bool, ProneMovementEliteSprint, true);
			*/

			//Search
			SKILL_SET_BUFF(float, SearchBuffSpeed, 10.0f);
			SKILL_SET_BUFF(bool, SearchDouble, true);

			//Surgery
			//SKILL_SET_BUFF(float, SurgeryReducePenalty, 999.0f);
			//SKILL_SET_BUFF(float, SurgerySpeed, 999.0f);



		}
	}

	//check variable
	//if (bNoWeight)
	//{
	//	//keep a variable for data
	//	CGClass1797 bInvData = {};

	//	//read the whole class
	//	if (DMADevice::MemRead(lpLocalPlayer._inventoryController, &bInvData, sizeof(CGClass1797)))
	//	{
	//		//keep a variable for data
	//		CGClass1781 bClass1752Data = {};

	//		//read the whole class
	//		if (DMADevice::MemRead(bInvData.gclass1781_0, &bClass1752Data, sizeof(CGClass1781)))
	//		{
	//			float fMax = 1.0f;

	//			//set both total weight and total weight elite skill to 1.0f some reason they didnt put these together but if you enable max skill it uses total weight elite skill not total weight
	//			DMADevice::MemWrite(((QWORD)bClass1752Data.TotalWeight) + offsetof(CGClass503<float>, gparam_0), &fMax, sizeof(float));
	//			DMADevice::MemWrite(((QWORD)bClass1752Data.TotalWeightEliteSkill) + offsetof(CGClass503<float>, gparam_0), &fMax, sizeof(float));
	//		}
	//	}

	//	//keep a variable for data
	//	CGClass440 bPhyData = {};

	//	//read the whole class
	//	if (DMADevice::MemRead(lpLocalPlayer.m_lpPhyiscal, &bPhyData, sizeof(CGClass440)))
	//	{
	//		float fMax = 5.0f;
	//		DMADevice::MemWrite(((QWORD)lpLocalPlayer.m_lpPhyiscal) + offsetof(CGClass440, PreviousWeight), &fMax, sizeof(float));

	//		fMax = 0.0f;
	//		DMADevice::MemWrite(((QWORD)lpLocalPlayer.m_lpPhyiscal) + offsetof(CGClass440, float_4), &fMax, sizeof(float));
	//		DMADevice::MemWrite(((QWORD)lpLocalPlayer.m_lpPhyiscal) + offsetof(CGClass440, Overweight), &fMax, sizeof(float));
	//		DMADevice::MemWrite(((QWORD)lpLocalPlayer.m_lpPhyiscal) + offsetof(CGClass440, WalkOverweight), &fMax, sizeof(float));

	//		fMax = 1.0f;
	//		DMADevice::MemWrite(((QWORD)lpLocalPlayer.m_lpPhyiscal) + offsetof(CGClass440, WalkSpeedLimit), &fMax, sizeof(float));

	//		bool bUpdated = true;
	//		DMADevice::MemWrite(((QWORD)lpLocalPlayer.m_lpPhyiscal) + offsetof(CGClass440, bool_1), &bUpdated, sizeof(bool));
	//	}
	//}
}

#ifdef ENABLE_AIMBOT
bool GetPlayerBonePosition(CPlayer* lpPlayerPtr, int iBone, FVec3 *vOutput)
{
	CPlayerBody lpPlayerBody = {};
	if (!lpPlayerPtr || !DMADevice::MemRead(lpPlayerPtr->m_lpPlayerBody, &lpPlayerBody, sizeof(CPlayerBody), false))
		return false;

	CSkeleton lpSkeleton = {};
	if (!DMADevice::MemRead(lpPlayerBody.SkeletonRootJoint, &lpSkeleton, sizeof(CSkeleton), false))
		return false;

	CUnityTList<CMonoTransform*> lpBoneData = {};
	if (!DMADevice::MemRead(lpSkeleton._values, &lpBoneData, sizeof(CUnityTList<CMonoTransform*>), false))
		return false;

	if (lpBoneData.dwSize == 0 || iBone > lpBoneData.dwSize || lpBoneData.lpList == 0)
		return false;

	CMonoTransform *lpPointer = 0;
	if (!DMADevice::MemRead(((DWORD64)lpBoneData.lpList) + 0x20 + (iBone * sizeof(CMonoTransform*)), &lpPointer, sizeof(CMonoTransform*)))
		return false;

	return lpPointer->GetPosition(vOutput);
}
bool IsKeyDown(CThreadData *lpData, int iKeyCode)
{
	BYTE bKeyManager[PAGE_SIZE] = {};
	if (!DMADevice::MemRead(lpData->m_dwInputManager, &bKeyManager, PAGE_SIZE, false))
		return false;

	DWORD64 dwKeyStatePtr1 = *(DWORD64*)(bKeyManager + 0x58);
	DWORD64 dwKeyStatePtr2 = *(DWORD64*)(bKeyManager + 0x78);

	DWORD dwKeyState1 = 0;
	if (dwKeyStatePtr1 && DMADevice::MemRead(dwKeyStatePtr1, &bKeyManager, PAGE_SIZE, false))
		dwKeyState1 = *(DWORD*)(bKeyManager + 4 * (iKeyCode >> 5));

	DWORD dwKeyState2 = 0;
	if (dwKeyStatePtr2 && DMADevice::MemRead(dwKeyStatePtr2, &bKeyManager, PAGE_SIZE, false))
		dwKeyState2 = *(DWORD*)(bKeyManager + 4 * (iKeyCode >> 5));

	return ((1 << (iKeyCode & 31)) & dwKeyState1) != 0 || ((1 << (iKeyCode & 31)) & dwKeyState2) != 0;
}

FVec4 FromEulerRad(FVec3 euler)
{
	float yaw = euler.x;
	float pitch = euler.y;
	float roll = euler.z;
	float rollOver2 = roll * 0.5f;
	float sinRollOver2 = sinf(rollOver2);
	float cosRollOver2 = cosf(rollOver2);
	float pitchOver2 = pitch * 0.5f;
	float sinPitchOver2 = sinf(pitchOver2);
	float cosPitchOver2 = cosf(pitchOver2);
	float yawOver2 = yaw * 0.5f;
	float sinYawOver2 = sinf(yawOver2);
	float cosYawOver2 = cosf(yawOver2);

	FVec4 result;
	result.x = cosYawOver2 * cosPitchOver2 * cosRollOver2 + sinYawOver2 * sinPitchOver2 * sinRollOver2;
	result.y = cosYawOver2 * cosPitchOver2 * sinRollOver2 - sinYawOver2 * sinPitchOver2 * cosRollOver2;
	result.z = cosYawOver2 * sinPitchOver2 * cosRollOver2 + sinYawOver2 * cosPitchOver2 * sinRollOver2;
	result.w = sinYawOver2 * cosPitchOver2 * cosRollOver2 - cosYawOver2 * sinPitchOver2 * sinRollOver2;
	return result;

}

FVec2 ClampRotation(CGClass1134 *lpMovementContextPtr, FVec2 rotation)
{
	CGClass1134 lpMovementContext = {};
	if (!DMADevice::MemRead(lpMovementContextPtr, &lpMovementContext, sizeof(CGClass1134)))
		return FVec2();

	return FVec2(ClampAngle360Sensitive(rotation.x, lpMovementContext.vector2_3.x, lpMovementContext.vector2_3.y), ClampAngle(rotation.y, lpMovementContext.vector2_4.x + lpMovementContext.float_28, lpMovementContext.vector2_4.y + lpMovementContext.float_28));
}
VOID SetLocalAngles(CProceduralWeaponAnimation* lpWeaponAni, CGClass1134 *lpMovementContext, FVec2 vNewRotation, FVec2 vOldRotation)
{
	FVec2 vNew = ClampRotation(lpMovementContext, vNewRotation);
	DMADevice::MemWrite(((DWORD64)lpMovementContext) + offsetof(CGClass1134, vector2_2), &vOldRotation, sizeof(FVec2));
	DMADevice::MemWrite(((DWORD64)lpMovementContext) + offsetof(CGClass1134, vector2_1), &vNew, sizeof(FVec2));


	FVec3 vOld = FromEulerRad(FVec3(vNew.y, vNew.x, 0.0f) * 0.017453292f) * FVec3(0.0f, 0.0f, 1.0f);
	vOld.z = -vOld.z;
	DMADevice::MemWrite(((DWORD64)lpMovementContext) + offsetof(CGClass1134, vector3_3), &vOld, sizeof(FVec2));

	vOld = FromEulerRad(FVec3(0.0f, vNew.x, 0.0f) * 0.017453292f) * FVec3(0.0f, 0.0f, 1.0f);
	vOld.z = -vOld.z;
	DMADevice::MemWrite(((DWORD64)lpMovementContext) + offsetof(CGClass1134, vector3_4), &vOld, sizeof(FVec2));
	
	DMADevice::MemWrite(((DWORD64)lpWeaponAni) + offsetof(CProceduralWeaponAnimation, Pitch), &vNew.y, sizeof(float));
}
float GetFOV(FVec2& ViewAngles, FVec2& vAimAngles)
{
	FVec2 vDelta = (vAimAngles - ViewAngles).NormalizeAngles();
	return sqrt(pow(vDelta.x, 2.0f) + pow(vDelta.y, 2.0f));
}
bool GetLocalFirepoint(CPlayer* lpLocalData, FVec3* vOutput)
{
	CPlayerBones lpLocalPlayerBones = {};
	if (!DMADevice::MemRead(lpLocalData->PlayerBones, &lpLocalPlayerBones, sizeof(CPlayerBones), false))
		return false;

	CBifacialTransform lpFireportBiTransform = {};
	if (!DMADevice::MemRead(lpLocalPlayerBones.Fireport, &lpFireportBiTransform, sizeof(CBifacialTransform), false))
		return false;

	return lpFireportBiTransform.GetPosition(vOutput);
}
bool IsSameGroup(CPlayer* lpLocalData, CGClass1194* lpProfileData)
{
	CProfile lpLocalProfileData = {};
	if (!DMADevice::MemRead(lpLocalData->m_lpProfile, &lpLocalProfileData, sizeof(CProfile)))
		return false;

	CGClass1194 lpLocalProfileInfo = {};
	if (!DMADevice::MemRead(lpLocalProfileData.Info, &lpLocalProfileInfo, sizeof(CGClass1194)))
		return false;

	CUnityString szLocalGroupId = {};
	CUnityString szPlayerGroupId = {};
	if (!DMADevice::MemRead(lpLocalProfileInfo.GroupId, &szLocalGroupId, sizeof(CUnityString)) || !DMADevice::MemRead(lpProfileData->GroupId, &szPlayerGroupId, sizeof(CUnityString)))
		return false;

	return (szLocalGroupId == szPlayerGroupId);
}
bool GetMainCameraPosition(CUnityGameObject* lpMainCameraGameObject, FVec3* vOutput)
{
	CUnityGameObject pGameObject = {};
	if (!DMADevice::MemRead(lpMainCameraGameObject, &pGameObject, sizeof(CUnityGameObject)))
		return false;

	CMonoTransform* lpTransform = (CMonoTransform*)pGameObject.m_aComponents.GetById(CLASS_MonoTransform);
	if (lpTransform == 0)
		return false;

	return lpTransform->GetPosition(vOutput);
}
int RandomInt(int a, int b)
{
	return a + (rand() % (int)(b - a + 1));
}
DWORD WINAPI AimbotThread(LPVOID lpParam)
{
	CThreadData *lpThreadData = (CThreadData*)lpParam;

	//keep a variable to copy the world data into this process
	CGameWorld lpWorldData = {};

	constexpr int iNextSwitchTimer = 200;//this is in MS 1000 = 1 second

	DWORD dwSwitchTimer = 0;

	CPlayerData* lpBestTarget = 0;

	int iRandomBoneArray[] = { EHumanBones::HumanPelvis, EHumanBones::HumanSpine1, EHumanBones::HumanNeck, EHumanBones::HumanHead, EHumanBones::HumanHead /*, EHumanBones::HumanLFoot, EHumanBones::HumanRFoot  ADD MORE HERE IF YOU WANT */ };

	srand(GetTickCount());

	//check if we are running and waiting!
	while (lpThreadData->m_bGameRunnning)
	{
		//random bone
		if (iAimbotBone == EHumanBones::BONE_MAX)
		{
			if ((GetTickCount() - dwSwitchTimer) > iNextSwitchTimer)
			{
				
				lpThreadData->m_iBone = iRandomBoneArray[RandomInt(0, ARRAYSIZE(iRandomBoneArray))];
				
				dwSwitchTimer = GetTickCount();
			}
		}
		else
		{
			//we want this bone :)
			lpThreadData->m_iBone = iAimbotBone;
		}

		if (!lpThreadData->m_lpLocalPlayerPointer && !lpThreadData->m_lpMainCameraGameObject)
			Sleep(2000);
		else
		{
			//i made the aimbot as i made mine IF the aimbot finds a target IT WILL KEEP THE LOCK ONTO THE TARGET TILL ITS DEAD OR YOU STOP PRESSING THE AIM KEY TO REMOVE THIS FUNCTION UNCOMMENT BELOW!
			//lpBestTarget = 0;

			CPlayer lpLocalData = { };
			CGClass1134 lpAimData = { };
			FVec3 vCameraPosition = FVec3();
			FVec3 vFireport = FVec3();
			if ( GetMainCameraPosition(lpThreadData->m_lpMainCameraGameObject, &vCameraPosition) && 
				DMADevice::MemRead(lpThreadData->m_lpLocalPlayerPointer, &lpLocalData, sizeof(CPlayer)) && 
				GetLocalFirepoint(&lpLocalData, &vFireport) &&
				DMADevice::MemRead(lpLocalData.m_lpMovementContext, &lpAimData, sizeof(CGClass1134)))
			{
				if (lpBestTarget == 0)
				{
					float fMaxDistance = (float)0xffffffff;
					for (int i = 0; i < lpThreadData->m_iPlayerObjectCount; i++)
					{
						CPlayerData* lpPlayerData = lpThreadData->m_lpPlayerObjects[i];
						if (lpPlayerData == 0 || lpPlayerData->m_lpPointer == 0 || lpPlayerData->m_bSameGroup || !lpPlayerData->m_bBasePositionVaild || !lpPlayerData->m_bBoneIsVaild)
							continue;

						FVec3 vForward = (FromEulerRad(FVec3(lpAimData.vector2_1.y, lpAimData.vector2_1.x, 0.0f) * 0.017453292f)) * FVec3(0.0f, 0.0f, 1.0f);
						vForward.z = -vForward.z;

						FVec3 vTDelta = (lpPlayerData->m_vBonePosition - vCameraPosition);
						FVec3 vDeltaNor = vTDelta.Normalize();
						float fFOV = vForward.GetFOV(vDeltaNor);
						if (fFOV >= 15.0f)
							continue;

						fFOV *= vTDelta.Length();
						if (fFOV < fMaxDistance)
						{
							fMaxDistance = fFOV;
							lpBestTarget = lpPlayerData;
						}
					}
				}
				bool bKeyPressed = IsKeyDown(lpThreadData, iAimbotHotkey);
				if (!bKeyPressed)
					lpBestTarget = 0;

				CPlayer bPlayer = {};
				FVec3 vBonePos = FVec3();
				if (lpBestTarget && lpBestTarget->m_lpPointer && DMADevice::MemRead(lpBestTarget->m_lpPointer,&bPlayer, sizeof(CPlayer)) && GetPlayerBonePosition(&bPlayer, lpThreadData->m_iBone, &vBonePos))
				{
					if (bKeyPressed)
					{
						FVec2 vAimbot = (vBonePos - vFireport).Normalize().ToRotator();

						SetLocalAngles(lpLocalData.m_lpWeaponAni, lpLocalData.m_lpMovementContext, vAimbot, lpAimData.vector2_1);
					}
				}


			}
		}
		Sleep(1);
	}

	return TRUE;
}
#endif
#ifdef ENABLE_AIMBOT
DWORD WINAPI PlayerThread(LPVOID lpParam)
{
	CThreadData *lpThreadData = (CThreadData*)lpParam;

	//keep a variable to copy the world data into this process
	CGameWorld lpWorldData = {};

	//before we begin! create player list so we can save pointers here
	CUnityTList<CPlayer*>* g_lpPlayers = (CUnityTList<CPlayer*>*)LocalAlloc(LMEM_ZEROINIT, (100 * sizeof(CPlayer*)) + sizeof(CUnityTList<CPlayer*>));
	if (g_lpPlayers == NULL)
		return FALSE;

	//check if we are running and waiting!
	while (lpThreadData->m_bGameRunnning)
	{
		//check if we have a pointer from the other thread!
		while (lpThreadData->m_lpMainWorldPointer)
		{
			//copy world data we dont need all we only need 1 variable but dma device reads in PAGE size so if trying to read 8 bytes your still reading 4096 bytes
			if (DMADevice::MemRead(lpThreadData->m_lpMainWorldPointer, &lpWorldData, sizeof(CGameWorld), false))
			{
				if (lpThreadData->m_lpLocalPlayerPointer)
				{
					CPlayer lpLocalPlayerData = {};
					if (DMADevice::MemRead(lpThreadData->m_lpLocalPlayerPointer, &lpLocalPlayerData, sizeof(CPlayer), false))
					{
						//and here we go!
						CUnityTList<CPlayer*> lpPlayerList = {};
						if (lpWorldData.RegisteredPlayers && DMADevice::MemRead(lpWorldData.RegisteredPlayers, &lpPlayerList, sizeof(CUnityTList<CPlayer*>), false))
						{
							if (lpPlayerList.dwSize > 0 && DMADevice::MemRead(lpPlayerList.lpList, g_lpPlayers, TLIST_SIZE(CPlayer*, lpPlayerList.dwSize), false))
							{
								CPlayer* lpBestTarget = 0;
								float fMaxDistance = 999999.0f;
								for (int i = 0; i < lpPlayerList.dwSize; i++)
								{
									CPlayer lpPlayerData = {};
									CPlayer* lpPlayerPtr = g_lpPlayers->lpListArray[i];

									lpThreadData->m_lpPlayerObjects[i]->m_lpPointer = lpPlayerPtr;
									if (!lpPlayerPtr || lpPlayerPtr == lpThreadData->m_lpLocalPlayerPointer || !DMADevice::MemRead(lpPlayerPtr, &lpPlayerData, sizeof(CPlayer), false) || !lpPlayerData.m_lpComponent)
										continue;

									CGClass1194 lpPlayerProfileInfo = {};
									CProfile lpPlayerProfileData = {};
									if (!DMADevice::MemRead(lpPlayerData.m_lpProfile, &lpPlayerProfileData, sizeof(CProfile)) ||
										!DMADevice::MemRead(lpPlayerProfileData.Info, &lpPlayerProfileInfo, sizeof(CGClass1194)))
										continue;

									lpThreadData->m_lpPlayerObjects[i]->m_bBasePositionVaild = lpPlayerData.GetPosition(&lpThreadData->m_lpPlayerObjects[i]->m_vBasePosition);
									lpThreadData->m_lpPlayerObjects[i]->m_bSameGroup = IsSameGroup(&lpLocalPlayerData, &lpPlayerProfileInfo);
									lpThreadData->m_lpPlayerObjects[i]->m_bBoneIsVaild = GetPlayerBonePosition(&lpPlayerData, lpThreadData->m_iBone, &lpThreadData->m_lpPlayerObjects[i]->m_vBonePosition);
								}
							}
							lpThreadData->m_iPlayerObjectCount = lpPlayerList.dwSize;
						}
					}
				}
			}
		}
		Sleep(100);
	}

	//free me!
	SAFE_FREE_ALLOC(g_lpPlayers);

	return TRUE;
}
#endif
DWORD WINAPI MainThread(LPVOID lpParam)
{
	CThreadData *lpThreadData = (CThreadData*)lpParam;

	//grab the hwnd from the argument!
	HWND hMainWindow = (HWND)lpThreadData->m_hDlg;

	//keep a variable to copy the world data into this process
	CGameWorld lpWorldData = {};

	//a buffer for the script data!
	CUnityMonoBehaviourScript lpWorldScriptData = {};

	//local profile id
	CUnityString lpLocalProfileId = {};

	//keep a variable for the location?
	CUnityString lpMapLocation = {};

	//a variable to know if this is interchange YOU can set this as a global variable meaning at the top of the file BUT why? its quicker and easyer this way
	bool bIsThisMapInterchange = false;

	//
	//create an endless loop
	while (lpThreadData->m_bGameRunnning)
	{
		//check to see if we have connected we have attached to process and we have a unityplayer base address else we have not fully set up and we shouldnt be reading / writing memory till its done!
		if (DMADevice::bConnected && DMADevice::dwAttachedProcessId && DMADevice::dwUnityPlayerBaseAddress)
		{
			//clear the buffer for new world data
			ZeroMemory(&lpWorldData, sizeof(CGameWorld));

			lpThreadData->m_lpMainWorldPointer = 0;

			if (lpThreadData->m_dwInputManager == 0)
				lpThreadData->m_dwInputManager = DMADevice::MemReadPtr<DWORD64>(DMADevice::dwUnityPlayerBaseAddress + INPUT_MANAGER);

			//first things first! get a game world pointer before anything else!
			CGameWorld *lpMainWorldPointer = NULL;
			while (lpMainWorldPointer == NULL)
			{
				//grab the world pointer and the data from the struct so we dont need to process more reads then required
				lpMainWorldPointer = GetGameWorld(&lpWorldData);

				//check if we have a pointer
				if (lpMainWorldPointer != NULL)
				{
					//break out of the (lpMainWorldPointer == NULL) loop and continue on the MAIN loop!
					lpThreadData->m_lpMainWorldPointer = lpMainWorldPointer;

					//let the world know we found the world ;) lol!
					bWorldPointerFound = true;
					
					//set the dlg item text
					SetDlgItemTextA(hMainWindow, IDC_WORLD_STATUS, "Found");
					break;
				}
				//refresh ALL data meaning all memory cache etc we dont need to but meh i like to
				VMMDLL_ConfigSet(VMMDLL_OPT_REFRESH_ALL, TRUE);

				//sleep for 2 seconds we dont need to see if we are in game every 100ms 2 seconds is enough?
				Sleep(2000);
			}

			//Clean out buffer from these variables so we can use them
			ZeroMemory(&lpWorldScriptData,sizeof(CUnityMonoBehaviourScript));
			ZeroMemory(&lpLocalProfileId, sizeof(CUnityString));
			ZeroMemory(&lpMapLocation, sizeof(CUnityString));

			//set to false because why not?
			bIsThisMapInterchange = false;

			//string_0 is the location id if this is NULL then it means your offline or in hideout :)
			if (lpWorldData.string_0 && DMADevice::MemReadUnityString(lpWorldData.string_0, &lpMapLocation))
			{
				//loop the ammount of map names we have
				for (int i = 0; i < ARRAYSIZE(szEFTMapNames); i++)
				{
					//compare the map names
					if (lpMapLocation == szEFTMapNames[i])
					{
						//now set the REAL map name
						SetDlgItemTextW(hMainWindow, IDC_STATUS_LOCATION, szMapNames[i]);

						//interchange map id is 5
						bIsThisMapInterchange = (i == 5);

						//break the loop so we dont need to continue as waste of cpu :)
						break;
					}
				}
			}
			else
			{
				//we cant grab the god damn name because offline raid eft dont like to save the location but hey! just use offline raid we dont need it
				SetDlgItemTextW(hMainWindow, IDC_STATUS_LOCATION, L"Offline Raid");
			}

			//we make ANOTHER endless loop as we now have a world pointer and we can now read memory
			while (1)
			{
				//it dont have to read this but update always needed!
				DMADevice::MemRead(lpMainWorldPointer, &lpWorldScriptData, sizeof(CUnityMonoBehaviourScript));

				//every world needs a component
				//no component so break the while loop?
				if (!lpWorldScriptData.m_lpComponent)
				{
					lpThreadData->m_lpMainWorldPointer = 0;

					lpMainWorldPointer = NULL;

					//let the world know we found the world ;) lol!
					bWorldPointerFound = false;

					//set the dlg item text
					SetDlgItemTextA(hMainWindow, IDC_WORLD_STATUS, "Not Found");
					break;
				}
				//grab our local player id(this should only be done ONCE! profile id dont change?)
				if (lpLocalProfileId.dwStringSize == 0 && !DMADevice::MemReadUnityString(lpWorldData.CurrentProfileId, &lpLocalProfileId))
					continue;

				//grab main camera
				if (lpThreadData->m_lpMainCameraGameObject == 0)
					lpThreadData->m_lpMainCameraGameObject = GetMainCamera();

				//we have everything now!

				//first lets do the camera shit
				Camera_Hack_Effects(lpThreadData->m_lpMainCameraGameObject);

				//get the local player from the world data
				CPlayer *lpLocalPlayer = GetLocalPlayer(&lpWorldData, &lpLocalProfileId);

				//update local player ALWAYS!
				lpThreadData->m_lpLocalPlayerPointer = lpLocalPlayer;

				//check it
				if (lpLocalPlayer)
				{
					//we should be false? just saves keep setting it!
					if (!bLocalPlayerTextSet)
					{
						//set the flags or bool!
						bLocalPlayerFound = true;

						//set the dlg item text
						SetDlgItemTextA(hMainWindow, IDC_PLAYER_STATUS, "Alive / Found");

						//set it to true so we dont keep setting the text or the flags!
						bLocalPlayerTextSet = true;
					}

					//now do all other hacks
					LocalPlayerHacks(lpLocalPlayer, bIsThisMapInterchange);
				}

				//we always need to sleep inside a thread when doing a while loop AKA endless loop because if you leave a thread running none stop at 99% or 100% load time you will have a high CPU usage :(
				Sleep(30);
			}

			//set the local pointer to null now!
			lpThreadData->m_lpLocalPlayerPointer = 0;

			//main camera should be null?
			lpThreadData->m_lpMainCameraGameObject = 0;

			//reset this so we can set the text!
			bLocalPlayerTextSet = false;

			//set the flags
			bLocalPlayerFound = false;

			//set the dlg item text
			SetDlgItemTextA(hMainWindow, IDC_PLAYER_STATUS, "Dead / Not Found");

			//we have broken the loop due to no world has been found OR the world has been deleted so we post a message to the dlg to say disconnect IF auto disconnect is enabled!
			if (bAutoDisconnectAfterRaidEnds)
			{
				//now post a message to tell the device to disconnect!
				PostMessageA(hMainWindow, WM_COMMAND, MAKEWPARAM(ID_BTN_DMA_SHUTDOWN, 0) , NULL);
			}

		}

		//we always need to sleep inside a thread when doing a while loop AKA endless loop because if you leave a thread running none stop at 99% or 100% load time you will have a high CPU usage :(
		Sleep(10);
	}

	//it dont matter what you return on your own threads there is a winapi function GetThreadExitCode which is what you use if thread has issues creating etc but we dont need to worry do we?
	return TRUE;
}