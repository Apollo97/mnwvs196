#pragma once
#include "PacketFlags.hpp"

#define MAKE_CENTER_PACKET_FLAG(flagName, value) namespace FlagInstances{ const static CenterPacketFlag flagName {value, #flagName}; } const static int flagName = value

MAKE_FLAG_COLLECTION_BODY(CenterPacketFlag)
//�H�U�}�l���U�ʥ]Opcode Flag

MAKE_CENTER_PACKET_FLAG(RegisterCenterAck, 1);
MAKE_CENTER_PACKET_FLAG(CenterStatChanged, 2);
MAKE_CENTER_PACKET_FLAG(CharacterListResponse, 3);

//����Opcode Flag���U
FLAG_COLLECTION_BODY_END