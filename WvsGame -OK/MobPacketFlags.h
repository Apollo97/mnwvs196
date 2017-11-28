#pragma once
#ifndef MOB_FLAG
#define MOB_FLAG

#include "Net\PacketFlags\PacketFlags.hpp"

#define MAKE_USER_PACKET_FLAG(flagName, value) namespace FlagInstances{ const static MobSendPacketFlag flagName {value, #flagName}; } const static int flagName = value

MAKE_FLAG_COLLECTION_BODY(MobSendPacketFlag)
//�H�U�}�l���U�ʥ]Opcode Flag

MAKE_USER_PACKET_FLAG(MobToClient_SpawnMonster, 0x3C1);


//����Opcode Flag���U
FLAG_COLLECTION_BODY_END

#define MAKE_USER_PACKET_FLAG(flagName, value) namespace FlagInstances{ const static MobRecvPacketFlag flagName {value, #flagName}; } const static int flagName = value

MAKE_FLAG_COLLECTION_BODY(MobRecvPacketFlag)
//�H�U�}�l���U�ʥ]Opcode Flag

MAKE_USER_PACKET_FLAG(MobToClient_SpawnMonster, 0x3C1);


//����Opcode Flag���U
FLAG_COLLECTION_BODY_END

#endif