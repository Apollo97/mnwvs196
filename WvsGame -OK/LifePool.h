#pragma once
#include <map>
#include "Npc.h"
#include "Mob.h"
#include "..\Common\Wz\WzResMan.hpp"
#include <atomic>
#include <mutex>

class User;
class Field;
class Controller;

class LifePool
{
	const static int MAX_WINDOW_VIEW_X = 1280, MAX_WINDOW_VIEW_Y = 1024, MAX_MOB_GEN = 40;

	std::mutex m_lifePoolMutex;

	std::atomic<int> atomicObjectCounter = 0x1000;

	//�b�o�Ӧa�Ϥ��Ҧ��i�઺NPC����
	std::vector<Npc> m_lNpc;

	//�b�o�Ӧa�Ϥ��Ҧ��i�઺�Ǫ�����
	std::vector<Mob> m_lMob;

	//�b�o�Ӧa�Ϥ��u�����ͥX���Ǫ�, key�OObject ID
	std::map<int, Mob*> m_aMobGen;

	//�b�o�Ӧa�Ϥ��u�����ͥX��Npc, key�OObject ID
	std::map<int, Npc*> m_aNpcGen;

	/* �a�Ϥ��������a�����v�������A�ϥ�std::map ���������A�Ы� Max Heap �P Min Heap
	   Key�O ����ƶq Value : Controller�O�N����̪��������
	   User�����O�smap��iterator �H�K�i��ֳt�R�� [ std::map��iterator���|�]���e�������s�W�R���ӵL�� ]
	*/
	std::map<int, Controller*> m_hCtrl;

	//����User�����쪺m_hCtrl 
	std::map<User*, decltype(m_hCtrl)::iterator> m_mController;

	void SetFieldObjAttribute(FieldObj* pFieldObj, WZ::Node& dataNode);

	int m_nMobCapacityMin, m_nMobCapacityMax, m_aInitMobGenCount = 0, m_nSubMobCount = -1, m_nMobDamagedByMobState = 0;

	bool m_bMobGenEnable = true;

	Field* m_pField;

public:
	LifePool();
	~LifePool();

	void SetMaxMobCapacity(int max)
	{
		m_nMobCapacityMax = max;
	}

	int GetMaxMobCapacity() const
	{
		return m_nMobCapacityMax;
	}

	//�qWz��Ū�����a�Ϥ�Npc��T�A�s��m_lNpc��
	void LoadNpcData(WZ::Node& dataNode);

	//�qWz��Ū�����a�Ϥ�Mob��T�A�s��m_lMob��
	void LoadMobData(WZ::Node& dataNode);

	void CreateNpc(const Npc&);

	void TryCreateMob(bool reset);
	void CreateMob(const Mob&);
	
	/*void PrintNpc()
	{
		for (auto& x : mNpcMap)
			std::cout << x.second.GetTemplateID() << std::endl;
	}*/

	void Init(Field* pField, int nFieldID);
	void OnEnter(User* pUser);

	void InsertController(User* pUser);
	void RemoveController(User* pUser);
};

