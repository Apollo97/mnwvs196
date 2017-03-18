#pragma once
#include "Net\SocketBase.h"

//Server �ݤ� Session
class ServerBase : public SocketBase
{
private:
	void OnClosed();

public:
	ServerBase(asio::io_service& serverService);
	~ServerBase();

	void OnPacket(InPacket *iPacket);
};

