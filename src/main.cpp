/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015��11��17�� 22ʱ59��30��
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
