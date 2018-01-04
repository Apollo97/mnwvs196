#pragma once
#include <map>
#include "FieldObj.h"

class MobTemplate;
class Controller;
class User;

class Mob : public FieldObj
{
private:
	const MobTemplate* m_pMobTemplate;

	std::map<User*, long long int> m_mAttackRecord;
	Controller* m_pController;

public:
	Mob();
	~Mob();

	void MakeEnterFieldPacket(OutPacket *oPacket);
	void MakeLeaveFieldPacket(OutPacket *oPacket);
	void EncodeInitData(OutPacket *oPacket, bool bIsControl = false);
	void SendChangeControllerPacket(User* pUser, int nLevel);
	void SendReleaseControllPacket(User* pUser, int dwMobID);
	void SetMobTemplate(MobTemplate *pTemplate);
	const MobTemplate* GetMobTemplate() const;

	void SetController(Controller* pController);
	Controller* GetController();

	void SetMovePosition(int x, int y, char bMoveAction, short nSN);

	//�ѪR�Ǫ����ʮɡALucid���ǩǪ����ʫʥ]�h���bytes
	static bool IsLucidSpecialMob(int dwTemplateID);
	void OnMobHit(User* pUser, long long int nDamage, int nAttackType);
	void GiveReward(unsigned int dwOwnerID, unsigned int dwOwnPartyID, int nOwnType, int nX, int nY, int tDelay, int nMesoUp, int nMesoUpByItem);
};

