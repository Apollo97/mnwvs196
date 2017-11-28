#pragma once
#include <map>
#include <functional>
#include "User.h"
#include "Task\AsnycScheduler.h"

class LifePool;

class Field
{
	std::map<int, User*> mUser; //m_lUser in WvsGame.idb
	int nFieldID = 0;
	LifePool *pLifePool;

	std::string m_sStreetName, m_sMapName;

	std::string m_sWeatherMsg; //�ӫ��߱��D��T��?

	int m_nWeatherItemID, //�ӫ��߱��D�㪫�~ID?
		m_nJukeBoxItemID; //Juke Box?

	double m_dIncRate_EXP = 1.0, m_dIncRate_Drop = 1.0; //�[��?

	bool m_bCloud, m_bTown, m_bSwim, m_bFly;

	int m_nReturnMap, m_nForcedReturn, m_nMobRate, m_nFieldType, m_nFieldLimit, m_nCreateMobInterval, m_nFixedMobCapacity, m_nMapSizeX, m_nMapSizeY;

	std::string m_strFirstUserEnter, m_strUserEnter;


	static void UpdateTrigger(Field* pField)
	{
		pField->Update();
	}

	std::_Binder<std::_Unforced, void(*)(Field* pField), Field* const> m_updateBinder;
	AsnycScheduler::AsnycScheduler<decltype(m_updateBinder)>* m_asyncUpdateTimer;

public:
	Field();
	~Field();

	void BroadcastPacket(OutPacket* oPacket);

	void SetCould(bool cloud);
	bool IsCloud() const;

	void SetTown(bool town);
	bool IsTown() const;

	void SetSwim(bool swim);
	bool IsSwim() const;

	void SetFly(bool fly);
	bool IsFly() const;

	void SetFieldID(int nFieldID);
	int GetFieldID() const;

	void SetReturnMap(int returnMap);
	int GetReturnMap() const;

	void SetForcedReturn(int forcedReturn);
	int GetForcedReturn() const;

	void SetMobRate(int mobRate);
	int GetMobRate() const;

	void SetFieldType(int fieldType);
	int GetFieldType() const;

	void SetFieldLimit(int fieldLimit);
	int GetFieldLimit() const;

	void SetCreateMobInterval(int interval);
	int GetCreateMobInterval() const;

	void SetFiexdMobCapacity(int capacity);
	int GetFixedMobCapacity() const;

	void SetFirstUserEnter(const std::string& script);
	const std::string& GetFirstUserEnter() const;

	void SetUserEnter(const std::string& script);
	const std::string& GetUserEnter() const;

	void SetMapSizeX(int x);
	int GetMapSizeX();

	void SetMapSizeY(int y);
	int GetMapSizeY();

	void InitLifePool();

	LifePool *GetLifePool();

	void OnEnter(User *pUser);
	void OnLeave(User *pUser);

	//�o�eoPacket���Ӧa�Ϫ���LUser�A�䤤pExcept�O�ҥ~��H
	void SplitSendPacket(OutPacket *oPacket, User *pExcept);

	//���PField �ۦ�B�z
	virtual void OnPacket(InPacket *iPacket);

	void Update();
};

