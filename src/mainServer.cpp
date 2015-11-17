
#include <unistd.h>

#include "mainServer.h"
#include "common.h"
#include "event2/event_compat.h"
#include "event2/event.h"


CMainServer* CMainServer::m_MainSvrInstance = NULL;
CMainServer::CMainServer()
{

}

CMainServer::~CMainServer()
{

}

CMainServer* CMainServer::Instance()
{
	if(m_MainSvrInstance == NULL)
		m_MainSvrInstance = new CMainServer();

	return m_MainSvrInstance;
}

int CMainServer::exitInstance()
{
	if (m_MainSvrInstance)
	{
		delete m_MainSvrInstance;
		m_MainSvrInstance = NULL;
	}

	return 0;
}

int CMainServer::initServer()
{
	m_EventBase = event_init();
	if (m_EventBase == NULL)
	{
		DBG_SRV_INFO("event init failed, m_EventBase is null!\n");
		return -1;
	}
	return 0;
}

void doReadClientRequest(evutil_socket_t sockFd, short event, void* arg)
{
	MsgHeader stMsgHead;
	int readLen = 0;
	if( sizeof(MsgHeader) !=(readLen = read(sockFd, &stMsgHead, sizeof(MsgHeader))))
	{
		DBG_SRV_INFO("read Msg Head failed: realen=%d,Headlen=%d\n", readLen, sizeof(MsgHeader));
		return;
	}
	
	switch(stMsgHead.MsgType)
	{
	

	}
}
void doAcceptClientRequest(evutil_socket_t sockFd, short event, void* arg)
{
	CMainServer* pMainSrv = (CMainServer*)arg;
	ClientInfo_S *pClientInfo = new ClientInfo_S;
	if(pMainSrv == NULL || pClientInfo == NULL)
	{
		DBG_SRV_INFO("pMainSrv == NULL || pClientInfo == NULL\n");
		return;
	}
	socklen_t slen = sizeof(pClientInfo->clientAddr);	
	pClientInfo->sockFd = accept(sockFd, (struct sockaddr*)&pClientInfo->clientAddr, &slen);
	if(pClientInfo->sockFd < 0 || pClientInfo->sockFd > FD_SETSIZE)
	{
		DBG_SRV_INFO("accept error");
		return ;
	}
	pMainSrv->m_ClientList.push_back(pClientInfo);
	struct event*  client = event_new(pMainSrv->m_EventBase, pClientInfo->sockFd, EV_READ|EV_PERSIST, doReadClientRequest, (void *)pClientInfo);
	event_add(client, NULL);
}


int CMainServer::startServer()
{
	// ½¨Á¢socket
	if (listenNetWork() != 0 )
	{
		DBG_SRV_INFO(" listen failed!\n");
		return -1;
	}

	m_ListenEvent = event_new(m_EventBase, m_LstSock, EV_READ|EV_PERSIST, doAcceptClientRequest, (void *)this);
	event_add(m_ListenEvent, NULL);
	event_base_dispatch(m_EventBase);
	return 0;
}

int CMainServer::stopServer()
{
	return 0;
}

int CMainServer::listenNetWork()
{
	struct sockaddr_in sin;

	m_LstSock = socket(AF_INET, SOCK_STREAM, 0);
	if( m_LstSock <= 0 )
	{
		DBG_SRV_INFO("create listen socket error!\n");
		return -1;
	}
	evutil_make_listen_socket_reuseable(m_LstSock);


	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(SERVER_LISTEN_PORT);

	if (bind(m_LstSock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
	{
		DBG_SRV_INFO(" bind failed:%s\n", strerror(errno));
		return -1;
	}
	if (listen(m_LstSock, LISTEN_BACKLOG) < 0) 
	{
		DBG_SRV_INFO(" listen failed:%s\n", strerror(errno));
		return -1;
	}
	evutil_make_socket_nonblocking(m_LstSock);
	return 0;
}
