/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年11月17日 22时59分30秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "mainServer.h"
#include "common.h"

int main(void)
{
	
	if( CMainServer::Instance()->initServer() != 0 )
	{
		DBG_SRV_INFO("Init Server Failed\n");
	}
	if( CMainServer::Instance()->startServer() != 0 )
	{
		DBG_SRV_INFO("start Server Failed\n");
	}
	
	return 0;
}
