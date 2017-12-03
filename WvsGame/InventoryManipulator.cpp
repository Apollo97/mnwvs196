#include "InventoryManipulator.h"
#include "..\Database\GA_Character.hpp"
#include "..\Database\GW_ItemSlotBundle.h"
#include "..\Database\GW_ItemSlotBase.h"
#include "ItemInfo.h"
#include "SkillInfo.h"

InventoryManipulator::InventoryManipulator()
{
}


InventoryManipulator::~InventoryManipulator()
{
}

bool InventoryManipulator::IsItemExist(GA_Character* pCharacterData, int nTI, int nItemID)
{
	return pCharacterData->GetItemCount(nTI, nItemID) > 0;
}

bool InventoryManipulator::RawAddItem(GA_Character * pCharacterData, int nTI, GW_ItemSlotBase * pItem, std::vector<ChangeLog>& aChangeLog, int * nIncRet)
{
	/*
	���B�ˬd�O��CashItem
	*/
	auto& itemSlot = pCharacterData->mItemSlot[nTI];
	if (pItem->IsTreatSingly())
	{
		short nPOS = pCharacterData->FindEmptySlotPosition(nTI);
		if (nPOS > 0) 
		{
			pCharacterData->mItemSlot[nTI][nPOS] = pItem;
			pItem->nPOS = nPOS;
			InsertChangeLog(aChangeLog, 0, nTI, nPOS, pItem, 0, 0);
			*nIncRet = 1;
			return true;
		}
		return false;
	}

	if (ItemInfo::GetInstance()->GetBundleItem(pItem->nItemID) != nullptr)
	{
		int nMaxPerSlot = SkillInfo::GetInstance()->GetBundleItemMaxPerSlot(pItem->nItemID, pCharacterData),
			nLastPos = pCharacterData->mItemSlot[nTI].rbegin()->first,
			nPOS = 1,
			nOnTrading = 0,
			nRemaining = 0,
			nSlotInc = 0,
			nTotalInc = 0,
			nNumber = ((GW_ItemSlotBundle*)pItem)->nNumber; //�n�[�J��쪺���~�ƶq

		while (nPOS <= nLastPos)
		{
			auto pItemInSlot = pCharacterData->GetItem(nTI, nPOS);
			
			//���q�I�]���ۦP�����~
			if (pItemInSlot != nullptr && pItemInSlot->nItemID == pItem->nItemID)
			{
				//�T�{������٥i�H��h�֭ӬۦP���~
				nRemaining = (nMaxPerSlot - ((GW_ItemSlotBundle*)pItemInSlot)->nNumber);
				
				//�����w���A�~���U�@��
				if (nRemaining <= 0)
					continue;
				nOnTrading = pCharacterData->mItemTrading[nTI][nPOS];
				nSlotInc = nNumber > nRemaining ? nRemaining : (nNumber - nRemaining); //�o���i�H�W�[�h��
				if (nSlotInc - nOnTrading > 0)
				{
					((GW_ItemSlotBundle*)pItemInSlot)->nNumber += (nSlotInc - nOnTrading);
					InsertChangeLog(aChangeLog, 1, nTI, nPOS, pItemInSlot, 0, nSlotInc - nOnTrading);
				}
				else
				{
					//�٤��T�wmItemTrading�Oԣ
				}
				nNumber -= nSlotInc;
				nTotalInc += nSlotInc;
				if (nNumber <= 0)
					break;
			}
		}

		//���L�ۦP���~�A��s����촡�J
		while (nNumber > 0)
		{
			nPOS = pCharacterData->FindEmptySlotPosition(nTI);
			if (nPOS <= 0)
				break;
			auto pClone = pItem->MakeClone();
			nSlotInc = nNumber > nMaxPerSlot ? nMaxPerSlot : (nNumber - nMaxPerSlot); //�o���i�H�W�[�h��
			((GW_ItemSlotBundle*)pClone)->nNumber = nSlotInc;
			pCharacterData->mItemSlot[nTI][nPOS] = pClone;
			pClone->nPOS = nPOS;

			nNumber -= nSlotInc;
			nTotalInc += nSlotInc;
		}
		*nIncRet = nTotalInc;
	}
}

void InventoryManipulator::InsertChangeLog(std::vector<ChangeLog>& aChangeLog, int nChange, int nTI, int nPOS, GW_ItemSlotBase * pi, int nPOS2, int nNumber)
{
	ChangeLog newLog;
	newLog.nChange = nChange;
	newLog.nTI = nTI;
	newLog.nPOS = nPOS;
	newLog.nPOS2 = nPOS2;
	newLog.nNumber = nNumber;
	newLog.pItem = pi;
	aChangeLog.push_back(newLog);
}

void InventoryManipulator::MakeInventoryOperation(OutPacket * oPacket, int bOnExclResult, std::vector<InventoryManipulator::ChangeLog>& aChangeLog)
{
	oPacket->Encode2(0x45);
	oPacket->Encode1(bOnExclResult);
	oPacket->Encode1((char)aChangeLog.size());
	oPacket->Encode1(0);
	for (auto& change : aChangeLog)
	{
		oPacket->Encode1((char)change.nChange);
		oPacket->Encode1((char)change.nTI);
		oPacket->Encode2((short)change.nPOS);
		if (change.nChange)
		{
			if (change.nChange == 1)
				oPacket->Encode2((short)change.nNumber);
			if (change.nChange == 2)
				oPacket->Encode2((short)change.nPOS2);
			if (change.nChange == 3 && change.nPOS < 0)
				oPacket->Encode1(1);
		}
		else
			change.pItem->Encode(oPacket);
	}
	oPacket->Encode4(0); // what's this?
}

bool InventoryManipulator::RawRemoveItem(GA_Character * pCharacterData, int nTI, int nPOS, int nCount, std::vector<ChangeLog>& aChangeLog, int * nDecRet, GW_ItemSlotBase ** ppItemRemoved)
{
	auto pItem = pCharacterData->GetItem(nTI, nPOS);
	GW_ItemSlotBase* pClone = ppItemRemoved ? pItem->MakeClone() : nullptr;
	printf("Raw Remove Item pClone == null ? %d\n", (int)(pClone == nullptr));
	if (pItem != nullptr)
	{
		//
		if (pItem->IsTreatSingly() && nCount == 1)
			pCharacterData->RemoveItem(nTI, nPOS);
		else if (nCount >= 1)
		{
			int nInSlotCount = ((GW_ItemSlotBundle*)pItem)->nNumber;
			if (nCount > nInSlotCount)
				nCount = nInSlotCount;
			((GW_ItemSlotBundle*)pItem)->nNumber -= nCount;
			if (((GW_ItemSlotBundle*)pItem)->nNumber <= 0)
				pCharacterData->RemoveItem(nTI, nPOS);
		}

		if (ppItemRemoved)
			*ppItemRemoved = pClone;
		if (ppItemRemoved && nCount > 1)
			((GW_ItemSlotBundle*)*ppItemRemoved)->nNumber = nCount;
		*nDecRet = nCount;
		InsertChangeLog(aChangeLog, 3, nTI, nPOS, pItem, 0, *nDecRet);
	}
	return true;
}
