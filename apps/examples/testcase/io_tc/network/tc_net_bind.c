/****************************************************************************
 *
 * Copyright 2016 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/

/// @file tc_net_bind.c
/// @brief Test Case Example for bind() API
#include <tinyara/config.h>
#include <stdio.h>
#include <errno.h>

#include <sys/stat.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/in.h>
//#include <arch/board/board.h>
#include <apps/netutils/netlib.h>

#include <sys/socket.h>

#include "tc_internal.h"
/**
   * @fn                   :tc_net_bind_p
   * @brief                :
   * @scenario             :
   * API's covered         :bind()
   * Preconditions         :
   * Postconditions        :
   * @return               :void
   */
static void tc_net_bind_p(void)
{
	struct sockaddr_in sa;
	int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&sa, 0, sizeof sa);

	sa.sin_family = AF_INET;
	sa.sin_port = htons(1100);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(SocketFD, (struct sockaddr *)&sa, sizeof(sa));
	close(SocketFD);

	if (ret == -1) {
		printf("tc_net_bind_p: fail\n");

		nw_total_fail++;
		RETURN_ERR;
	}

	printf("tc_net_bind_p: PASS\n");
	nw_total_pass++;
}

/**
   * @fn                   :tc_net_bind_udp_p
   * @brief                :
   * @scenario             :
   * API's covered         :bind()
   * Preconditions         :
   * Postconditions        :
   * @return               :void
   */
static void tc_net_bind_udp_p(void)
{
	struct sockaddr_in sa;
	int SocketFD = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	memset(&sa, 0, sizeof sa);

	sa.sin_family = AF_INET;
	sa.sin_port = htons(1100);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(SocketFD, (struct sockaddr *)&sa, sizeof(sa));
	close(SocketFD);

	if (ret == -1) {
		printf("tc_net_bind_udp_p: fail\n");

		nw_total_fail++;
		RETURN_ERR;
	}

	printf("tc_net_bind_udp_p: PASS\n");
	nw_total_pass++;
}

/**
   * @fn                   :tc_net_bind_broadcast_p
   * @brief                :
   * @scenario             :
   * API's covered         :bind()
   * Preconditions         :
   * Postconditions        :
   * @return               :void
*/
static void tc_net_bind_broadcast_p(void)
{

	struct sockaddr_in sa;
	int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&sa, 0, sizeof sa);

	sa.sin_family = AF_INET;
	sa.sin_port = htons(1105);
	sa.sin_addr.s_addr = htonl(INADDR_BROADCAST);

	int ret = bind(SocketFD, (struct sockaddr *)&sa, sizeof(sa));
	close(SocketFD);

	if (ret == -1) {
		printf("tc_net_bind_broadcast_p: FAIL\n");

		nw_total_fail++;
		RETURN_ERR;
	}

	printf("tc_net_bind_broadcast_p: PASS\n");
	nw_total_pass++;
}

/**
   * @fn                   :tc_net_bind_fd_n
   * @brief                :
   * @scenario             :
   * API's covered         :bind()
   * Preconditions         :
   * Postconditions        :
   * @return               :void
   */
static void tc_net_bind_fd_n(void)
{
	struct sockaddr_in sa;
	int fd = -1;
	memset(&sa, 0, sizeof sa);

	sa.sin_family = AF_INET;
	sa.sin_port = htons(1110);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(fd, (struct sockaddr *)&sa, sizeof(sa));

	if (ret == 0) {
		printf("tc_net_bind_fd_n: FAIL\n");

		nw_total_fail++;
		RETURN_ERR;
	}

	printf("tc_net_bind_fd_n: PASS\n");
	nw_total_pass++;
}

/**
   * @fn                   :tc_net_bind_addrfamily_n
   * @brief                :
   * @scenario             :
   * API's covered         :bind()
   * Preconditions         :
   * Postconditions        :
   * @return               :void
   */
static void tc_net_bind_addrfamily_n(void)
{
	struct sockaddr_in sa;
	int fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	memset(&sa, 0, sizeof sa);

	sa.sin_family = AF_UNIX;
	sa.sin_port = htons(5123);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(fd, (struct sockaddr *)&sa, sizeof(sa));
	close(fd);

	if (ret == 0) {
		printf("tc_net_bind_addrfamily_n: FAIL\n");

		nw_total_fail++;
		RETURN_ERR;
	}

	printf("tc_net_bind_addrfamily_n: PASS\n");
	nw_total_pass++;
}

/**
   * @fn                   :tc_net_bind_size_n
   * @brief                :
   * @scenario             :
   * API's covered         :bind()
   * Preconditions         :
   * Postconditions        :
   * @return               :void
*/
static void tc_net_bind_size_n(void)
{
	struct sockaddr_in sa;
	int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&sa, 0, sizeof sa);

	sa.sin_family = AF_INET;
	sa.sin_port = htons(1109);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(SocketFD, (struct sockaddr *)&sa, -1);
	close(SocketFD);

	if (ret == 0) {
		printf("tc_net_bind_size_n: fail\n");

		nw_total_fail++;
		RETURN_ERR;
	}

	printf("tc_net_bind_size_n: PASS\n");
	nw_total_pass++;
}

/**
   * @fn                   :tc_net_bind_fd_size_n
   * @brief                :
   * @scenario             :
   * API's covered         :bind()
   * Preconditions         :
   * Postconditions        :
   * @return               :void
   */
static void tc_net_bind_fd_size_n(void)
{
	struct sockaddr_in sa;

	memset(&sa, 0, sizeof sa);

	sa.sin_family = AF_INET;
	sa.sin_port = htons(1108);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(-1, (struct sockaddr *)&sa, 0);

	if (ret == 0) {
		printf("tc_net_bind_fd_size_n: fail\n");

		nw_total_fail++;
		RETURN_ERR;
	}

	printf("tc_net_bind_fd_size_n: PASS\n");
	nw_total_pass++;
}

/****************************************************************************
 * Name: bind()
 ****************************************************************************/

int net_bind_main(void)
{

	tc_net_bind_p();
	tc_net_bind_fd_n();
	tc_net_bind_fd_size_n();
	tc_net_bind_udp_p();
	tc_net_bind_broadcast_p();
	tc_net_bind_size_n();
	tc_net_bind_addrfamily_n();
	return 0;
}
