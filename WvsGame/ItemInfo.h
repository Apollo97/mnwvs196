#pragma once
#include <string>
#include <map>
#include <vector>

class GW_ItemSlotBase;

class ItemInfo
{
private:
	bool m_bInitialized = false;

public:

	/*
	�Ӫ��~�y������O�����ݩ� -- ���A�S���o��class
	*/
	struct BasicIncrementStat
	{
		//�W�[ inc
		int	niSTR,
			niDEX,
			niINT,
			niLUK,
			niMaxHP,
			niMaxMP,
			niPAD,
			niMAD,
			niPDD,
			niMDD,
			niACC,
			niEVA,
			niCraft,
			niSpeed,
			niJump,
			niSwim,
			niFatigue;
	};

	/*
	�Ӫ��~�������ݩʡA�Ҧp�i�_����� -- ���A�S���o��class
	*/
	struct BasicAbilityStat
	{
		bool bTimeLimited,
			bCash,
			bQuest,
			bPartyQuest,
			bOnly,
			bTradeBlock,
			bNotSale,
			bExpireOnLogout,
			bBigSize;
	};

	struct EquipItem 
	{
		std::string sItemName;
		BasicAbilityStat abilityStat;
		BasicIncrementStat incStat;

		//��O�ݨD request
		int nItemID, 
			nrSTR, 
			nrINT, 
			nrDEX, 
			nrLUK, 
			nrPOP, 
			nrJob, 
			nrLevel, 
			nrMobLevel,
			nRUC, 
			nSellPrice, 
			nSwim, 
			nTamingMob, 
			nKnockBack,
			
			//�ϥΦ��˳ƹ��d�����v�T
			dwPetAbilityFlag;
	};

	struct BundleItem 
	{
		std::string sItemName;
		double dSellUnitPrice;
		int nItemID, 
			nPAD, 
			nMAD, 
			nRequiredLEV, 
			nSellPrice, 
			nMaxPerSlot;

		BasicAbilityStat abilityStat;
	};

	struct UpgradeItem 
	{
		std::string sItemName;
		BasicIncrementStat incStat;
		int nItemID,
			nSuccessRate, 
			nCursedRate;
	};

	struct StateChangeItem
	{
		std::string sItemName;
		int nItemID;
		std::vector<std::pair<std::string, int>> spec;
	};

	struct PortalScrollItem
	{
		std::string sItemName;
		int nItemID;
		std::vector<std::pair<std::string, int>> spec;
	};

	struct MobSummonItem
	{
		std::string sItemName;
		int nItemID, 
			nType;
		
		// pair < MobID, Prob >
		std::vector<std::pair<int ,int>> lMob;
	};

	struct PetFoodItem
	{
		std::string sItemName;
		int nItemID, 
			niRepleteness;
		std::vector<int> ldwPet;
	};

	struct TamingMobFoodItem
	{
		std::string sItemName;
		int nItemID, 
			niFatigue;
	};

	struct BridleItem
	{
		std::string sItemName;
		int nItemID, 
			nCreateItemID, 
			dwTargetMobID, 
			nBridleMsgType, 
			nBridleProp, 
			nBridleHP, 
			nUseDelay;

		double dBridlePropChg;
	};

	struct SkillLearnItem
	{
		std::string sItemName;
		int nItemID,
			nMasterLevel,
			nSuccessRate,
			nReqLevel;

		std::vector<int> aSkill;
	};

	struct PortableChairItem
	{
		std::string sItemName;
		int nItemID,
			nReqLevel,
			nPortableChairRecoveryRateHP,
			nPortableChairRecoveryRateMP;
	};

	ItemInfo();
	~ItemInfo();

	static ItemInfo* GetInstance();
	void Initialize();
	void IterateMapString();
	void IterateItemString(void *dataNode);
	void IterateEquipItem(void *dataNode);
	void IterateBundleItem();
	void IteratePetItem();
	void IterateCashItem();
	void RegisterSpecificItems();
	void RegisterNoRollbackItem();
	void RegisterSetHalloweenItem();

	void RegisterEquipItemInfo(ItemInfo::EquipItem* pEqpItem, int nItemID, void* pProp);

	/*
	�@��ɯťΨ��b
	*/
	void RegisterUpgradeItem(int nItemID, void *pProp);

	/*
	���ʨ��b
	*/
	void RegisterPortalScrollItem(int nItemID, void *pProp);

	/*
	�l��U������
	*/
	void RegisterMobSummonItem(int nItemID, void *pProp);

	/*
	�d��������
	*/
	void RegisterPetFoodItem(int nItemID, void *pProp);

	/*
	�M�d������
	*/
	void RegisterTamingMobFoodItem(int nItemID, void *pProp);

	/*
	
	*/
	void RegisterBridleItem(int nItemID, void *pProp);

	/*
	�Ȥl
	*/
	void RegisterPortableChairItem(int nItemID, void *pProp);

	/*
	�ޯ��
	*/
	void RegisterSkillLearnItem(int nItemID, void *pProp);

	/*
	�|���ܨ��⪬�A�����~�A�Ҧp�Ĥ�
	*/
	void RegisterStateChangeItem(int nItemID, void *pProp);

	ItemInfo::EquipItem* GetEquipItem(int nItemID);
	ItemInfo::BundleItem* GetBundleItem(int nItemID);
	ItemInfo::UpgradeItem* GetUpgradeItem(int nItemID);
	ItemInfo::PortalScrollItem* GetPortalScrollItem(int nItemID);

	ItemInfo::MobSummonItem* GetMobSummonItem(int nItemID);
	ItemInfo::PetFoodItem* GetPetFoodItem(int nItemID);
	ItemInfo::TamingMobFoodItem* GetTamingMobFoodItem(int nItemID);
	ItemInfo::BridleItem* GetBridleItem(int nItemID);
	ItemInfo::SkillLearnItem* GetSkillLearnItem(int nItemID);
	ItemInfo::PortableChairItem* GetPortableChairItem(int nItemID);
	ItemInfo::StateChangeItem* GetStateChangeItem(int nItemID);

	bool ConsumeOnPickup(int nItemID);
	bool ExpireOnLogout(int nItemID);
	int GetBulletPAD(int nItemID);
	long GetItemDateExpire(const std::string& sDate);
	const std::string& GetItemName(int nItemID);
	bool IsAbleToEquip(int nGender, int nLevel, int nJob, int nSTR, int nDEX, int nINT, int nLUK, int nPOP, GW_ItemSlotBase* pPetItem, int nItemID);
	bool IsNotSaleItem(int nItemID);
	bool IsOnlyItem(int nItemID);
	bool IsTradeBlockItem(int nItemID);
	bool IsQuestItem(int nItemID);

private:
	std::map<int, ItemInfo::EquipItem*> m_mEquipItem;
	std::map<int, ItemInfo::BundleItem*> m_mBundleItem;
	std::map<int, ItemInfo::UpgradeItem*> m_mUpgradeItem;
	std::map<int, ItemInfo::StateChangeItem*> m_mStateChangeItem;
	std::map<int, ItemInfo::PortalScrollItem*> m_mPortalScrollItem;
	std::map<int, ItemInfo::MobSummonItem*> m_mMobSummonItem;
	std::map<int, ItemInfo::PetFoodItem*> m_mPetFoodItem;
	std::map<int, ItemInfo::TamingMobFoodItem*> m_mTamingMobFoodItem;
	std::map<int, ItemInfo::BridleItem*> m_mBridleItem;
	std::map<int, ItemInfo::SkillLearnItem*> m_mSkillLearnItem;
	std::map<int, ItemInfo::PortableChairItem*> m_mPortableChairItem;

	std::map<int, std::string> m_mItemString, m_mMapString;
	
	void LoadIncrementStat(ItemInfo::BasicIncrementStat& refStat, void *pProp);
	void LoadAbilityStat(ItemInfo::BasicAbilityStat& refStat, void *pProp);
};

