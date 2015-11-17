#ifndef __COMMON__H_
#define __COMMON__H_

#include <stdio.h>
#include <errno.h>
#include <string.h>


#define SERVER_LISTEN_PORT 10081
#define LISTEN_BACKLOG     50

#define DBG_SRV_INFO(pFmt, ...) \
	do{\
		fprintf(stderr, "[%s/%d]:"pFmt, __FILE__, __LINE__, ##__VA_ARGS__);\
		fflush(stderr);\
	}while(0)

#endif  // common.h
