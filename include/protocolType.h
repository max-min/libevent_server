
#ifndef __PROTOCOLTYPE_H__
#define __PROTOCOLTYPE_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


typedef struct _MsgHeader_S_
{
	short  MsgType;	    // ��Ϣ����
	short  SubMsgType;  // ��Ϣ������
	int MsgLen;		    // ��Ϣ���ȣ�������ͷ 

}MsgHeader;

typedef struct _ClientInfo_S_
{
	struct sockaddr_in clientAddr;
	evutil_socket_t sockFd;
}ClientInfo_S;



#endif // protocolType.h
