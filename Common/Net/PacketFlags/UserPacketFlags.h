#pragma once
#ifndef USER_FLAG
#define USER_FLAG

#include "PacketFlags.hpp"

#define MAKE_USER_PACKET_FLAG(flagName, value) namespace FlagInstances{ const static UserPacketFlag flagName {value, #flagName}; } const static int flagName = value

MAKE_FLAG_COLLECTION_BODY(UserPacketFlag)
//�H�U�}�l���U�ʥ]Opcode Flag

MAKE_USER_PACKET_FLAG(UserLocal_OnStatChanged, 0x47);
MAKE_USER_PACKET_FLAG(USerLocal_OnTemporaryStatSet, 0x48);
MAKE_USER_PACKET_FLAG(USerLocal_OnTemporaryStatReset, 0x49);
MAKE_USER_PACKET_FLAG(UserCommon_OnChat, 0x21E);
MAKE_USER_PACKET_FLAG(UserRemote_OnAvatarModified, 0x2A7);

//����Opcode Flag���U
FLAG_COLLECTION_BODY_END

#endif