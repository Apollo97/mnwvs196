#include "WvsLogin.h"
#include <thread>
#include <iostream>
#include <functional>
#include "Net\OutPacket.h"
#include "Task\AsnycScheduler.h"

#include "Constants\ConfigLoader.hpp"
#include "Constants\ServerConstants.hpp"

WvsLogin::WvsLogin()
{
}


WvsLogin::~WvsLogin()
{
}

void WvsLogin::ConnectToCenter(int nCenterIdx)
{
	aCenterServerService[nCenterIdx].reset( new asio::io_service() );		
	aCenterList[nCenterIdx] = std::make_shared<Center>(*aCenterServerService[nCenterIdx]);
	aCenterList[nCenterIdx]->SetDisconnectedNotifyFunc(&Center::OnNotifyCenterDisconnected);
	aCenterList[nCenterIdx]->SetCenterIndex(nCenterIdx);
	aCenterList[nCenterIdx]->OnConnectToCenter(
		ConfigLoader::GetInstance()->StrValue("Center" + std::to_string(nCenterIdx) + "_IP"),
		ConfigLoader::GetInstance()->IntValue("Center" + std::to_string(nCenterIdx) + "_Port")
	);
	asio::io_service::work work(*aCenterServerService[nCenterIdx]);
	std::error_code ec;
	aCenterServerService[nCenterIdx]->run(ec);
}

void WvsLogin::CenterAliveMonitor()
{
	printf("=================�w���ˬdCenter Server�s�u�{��=================\n");
	int centerSize = ConfigLoader::GetInstance()->IntValue("CenterCount");
	for (int i = 0; i < centerSize; ++i)
		if (aCenterList[i] && !aCenterList[i]->IsConnected()) {
			printf("Center Server %d �|���s�u�A���խ��s�s�u�C\n", i);
			new std::thread(&WvsLogin::ConnectToCenter, this, i);
		}
}

void WvsLogin::InitializeCenter()
{
	int centerSize = ConfigLoader::GetInstance()->IntValue("CenterCount");
	for (int i = 0; i < centerSize; ++i)
		aCenterWorkThread[i].reset(new std::thread(&WvsLogin::ConnectToCenter, this, i));

	//Periodic Task, �˴��O�_�PCenter���_�s�u�A�ù��խץ�
	auto holderFunc = std::bind(&WvsLogin::CenterAliveMonitor, this);
	auto aliveHolder = AsnycScheduler::CreateTask(holderFunc, 10 * 1000, true);
	aliveHolder->Start();
}

void WvsLogin::OnNotifySocketDisconnected(SocketBase *pSocket)
{
}