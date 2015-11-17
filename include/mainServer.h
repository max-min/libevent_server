/*
 *@rmark : 程序启动的入口类
 *@author：maxmin
 *@email : zy573124937@163.com
 */

#ifndef __MAINSERVER_H__
#define __MAINSERVER_H__

#include <list>
#include "event2/event_struct.h"
#include "protocolType.h"


class CMainServer 
{
public:
	CMainServer();
	virtual ~CMainServer();
	
public:
	static CMainServer* Instance();
	static int exitInstance();
	int initServer();
	int startServer();
	int stopServer();

private:
	int listenNetWork();

public:
	static CMainServer* m_MainSvrInstance;
	struct event_base * m_EventBase;
	struct event* m_ListenEvent;
	evutil_socket_t m_LstSock;
	//struct list<struct event *> m_EventList;
	std::list<ClientInfo_S *> m_ClientList;
};


#endif // MainServer.h
