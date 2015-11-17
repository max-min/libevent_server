
#ifndef __PROTOCOLTYPE_H__
#define __PROTOCOLTYPE_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


typedef struct _MsgHeader_S_
{
	short  MsgType;	    // 消息类型
	short  SubMsgType;  // 消息子类型
	int MsgLen;		    // 消息长度，不包括头 

}MsgHeader;

typedef struct _ClientInfo_S_
{
	struct sockaddr_in clientAddr;
	evutil_socket_t sockFd;
}ClientInfo_S;



#endif // protocolType.h
