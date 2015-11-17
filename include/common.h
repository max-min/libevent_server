#ifndef __COMMON__H_
#define __COMMON__H_

#define SERVER_LISTEN_PORT 10081
#define LISTEN_BACKLOG     50

#define DBG_SRV_INFO(pFmt, ...) \
	do{\
	fprintf(stderr, "[%s/%d]:"pFmt, __FILE__, __LINE__, ##__VA_ARGS__);\
		fflush(stderr);\
	}while(0)


typedef struct _ClientInfo_S_
{
	struct sockaddr_in clientAddr;
	evutil_socket_t sockFd;
}ClientInfo_S;

typedef struct _MsgHeader_S_
{
	short  MsgType;	    // ��Ϣ����
	short  SubMsgType;  // ��Ϣ������
	int MsgLen;		    // ��Ϣ���ȣ�������ͷ 

}MsgHeader;
#endif  // common.h