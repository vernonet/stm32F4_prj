/**
  ******************************************************************************
  * @file    LwIP/LwIP_TCP_Echo_Client/Inc/lwipopts.h
  * @author  MCD Application Team
  * @brief   lwIP Options Configuration.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

/**
 * NO_SYS==1: Provides VERY minimal functionality. Otherwise,
 * use lwIP facilities.
 */
//--------------------------------------------
#define LWIP_DEBUG 0
//#define IP_DEBUG LWIP_DBG_ON
#define DBG_LVL 0

#if (DBG_LVL > 0)

#define UsrLog(...)   printf(__VA_ARGS__);//;\
                           // printf("\n");
#else
#define UsrLog(...)
#endif
//--------------------------------------------

/* Prevent having to link sys_arch.c (we don't test the API layers in unit tests) */
#define NO_SYS                          1
#define MEM_ALIGNMENT                   4
#define LWIP_RAW                        1
#define LWIP_NETCONN                    0
#define LWIP_SOCKET                     0
#define LWIP_DHCP                       0
#define LWIP_ICMP                       1
#define LWIP_UDP                        1
#define LWIP_DNS                        1
#define LWIP_TCP                        1
#define TCP_TTL                         255
#define ETH_PAD_SIZE                    0
//#define LWIP_IP_ACCEPT_UDP_PORT(p)      ((p) == PP_NTOHS(67))
#define DNS_SERVER_ADDRESS(a)          ip_addr_set_ip4_u32(a, ipaddr_addr("8.8.8.8")) /* google-public-dns-a.google.com */


#define MEM_SIZE                        0x2000//10000
/* MEMP_NUM_PBUF: the number of memp struct pbufs. If the application
   sends a lot of data out of ROM (or other static memory), this
   should be set high. */
//#define MEMP_NUM_PBUF           8
/* MEMP_NUM_UDP_PCB: the number of UDP protocol control blocks. One
   per active UDP "connection". */
//#define MEMP_NUM_UDP_PCB        6
/* MEMP_NUM_TCP_PCB: the number of simulatenously active TCP
   connections. */
#define MEMP_NUM_TCP_PCB        1
/* MEMP_NUM_TCP_PCB_LISTEN: the number of listening TCP
   connections. */
//#define MEMP_NUM_TCP_PCB_LISTEN 5
/* MEMP_NUM_TCP_SEG: the number of simultaneously queued TCP
   segments. */
//#define MEMP_NUM_TCP_SEG        8
#define TCP_MSS                         (1500 /*mtu*/ - 20 /*iphdr*/ - 20 /*tcphhr*/)  //1500
#define TCP_SND_BUF                     (2 * TCP_MSS)  //2
/* MEMP_NUM_SYS_TIMEOUT: the number of simulateously active
   timeouts. */
#define MEMP_NUM_SYS_TIMEOUT            10

#define ETHARP_SUPPORT_STATIC_ENTRIES   1  //1

#define LWIP_HTTPD_CGI                  0
#define LWIP_HTTPD_SSI                  0
#define LWIP_HTTPD_SSI_INCLUDE_TAG      0

//#define LWIP_CALLBACK_API               1
#define MEM_LIBC_MALLOC                 1
//#define MEMP_MEM_MALLOC                  1
//#define MEMP_OVERFLOW_CHECK             1
#define TCP_WND                          (2 * TCP_MSS)   //1  0x740
#define MEMP_NUM_TCP_PCB                 1
//#define LWIP_NETIF_TX_SINGLE_PBUF        1
#define LWIP_STATS_DISPLAY               0
//#define TCP_SND_QUEUELEN                   2

#define LWIP_SOCKET                     0
#define LWIP_NETCONN                    0
#define LWIP_NETIF_LINK_CALLBACK        0
#define SYS_LIGHTWEIGHT_PROT            0
#define LWIP_NOASSERT
//#define LWIP_TCP_KEEPALIVE              1

/* 
The STM32F4xx allows computing and verifying the IP, UDP, TCP and ICMP checksums by hardware:
 - To use this feature let the following define uncommented.
 - To disable it and process by CPU comment the  the checksum.
*/
//#define CHECKSUM_BY_HARDWARE 

//#ifdef CHECKSUM_BY_HARDWARE
//  /* CHECKSUM_GEN_IP==0: Generate checksums by hardware for outgoing IP packets.*/
//  #define CHECKSUM_GEN_IP                 1
//  /* CHECKSUM_GEN_UDP==0: Generate checksums by hardware for outgoing UDP packets.*/
//  #define CHECKSUM_GEN_UDP                0
//  /* CHECKSUM_GEN_TCP==0: Generate checksums by hardware for outgoing TCP packets.*/
//  #define CHECKSUM_GEN_TCP                1 
//  /* CHECKSUM_CHECK_IP==0: Check checksums by hardware for incoming IP packets.*/
//  #define CHECKSUM_CHECK_IP               1
//  /* CHECKSUM_CHECK_UDP==0: Check checksums by hardware for incoming UDP packets.*/
//  #define CHECKSUM_CHECK_UDP              0
//  /* CHECKSUM_CHECK_TCP==0: Check checksums by hardware for incoming TCP packets.*/
//  #define CHECKSUM_CHECK_TCP              1
//  /* CHECKSUM_CHECK_ICMP==0: Check checksums by hardware for incoming ICMP packets.*/
//  #define CHECKSUM_GEN_ICMP               1
//#else
//  /* CHECKSUM_GEN_IP==1: Generate checksums in software for outgoing IP packets.*/
//  #define CHECKSUM_GEN_IP                 1
//  /* CHECKSUM_GEN_UDP==1: Generate checksums in software for outgoing UDP packets.*/
//  #define CHECKSUM_GEN_UDP                1
//  /* CHECKSUM_GEN_TCP==1: Generate checksums in software for outgoing TCP packets.*/
//  #define CHECKSUM_GEN_TCP                1
//  /* CHECKSUM_CHECK_IP==1: Check checksums in software for incoming IP packets.*/
//  #define CHECKSUM_CHECK_IP               1
//  /* CHECKSUM_CHECK_UDP==1: Check checksums in software for incoming UDP packets.*/
//  #define CHECKSUM_CHECK_UDP              1
//  /* CHECKSUM_CHECK_TCP==1: Check checksums in software for incoming TCP packets.*/
//  #define CHECKSUM_CHECK_TCP              1
//  /* CHECKSUM_CHECK_ICMP==1: Check checksums by hardware for incoming ICMP packets.*/
//  #define CHECKSUM_GEN_ICMP               1
//#endif

#endif /* __LWIPOPTS_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
