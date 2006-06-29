/**
 * @file IxOsalOsTypes.h
 *
 * @brief Linux-specific data type
 * 
 * 
 * @par
 * IXP400 SW Release version 2.1
 * 
 * -- Copyright Notice --
 * 
 * @par
 * Copyright (c) 2001-2005, Intel Corporation.
 * All rights reserved.
 * 
 * @par
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Intel Corporation nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 
 * 
 * @par
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * 
 * @par
 * -- End of Copyright Notice --
 */

#ifndef IxOsalOsTypes_H
#define IxOsalOsTypes_H

#include <linux/types.h>
#include <asm/semaphore.h>

typedef long long INT64;	      /**< 64-bit signed integer */
typedef unsigned long long UINT64;    /**< 64-bit unsigned integer */
typedef int INT32;		      /**< 32-bit signed integer */
typedef unsigned int UINT32;	      /**< 32-bit unsigned integer */
typedef short INT16;		      /**< 16-bit signed integer */
typedef unsigned short UINT16;	      /**< 16-bit unsigned integer */
typedef char INT8;		      /**< 8-bit signed integer */
typedef unsigned char UINT8;	      /**< 8-bit unsigned integer */
typedef UINT32 ULONG;		      /**< alias for UINT32 */
typedef UINT16 USHORT;		      /**< alias for UINT16 */
typedef UINT8 UCHAR;		      /**< alias for UINT8 */
typedef UINT32 BOOL;		      /**< alias for UINT32 */

/* Default stack limit is 10 KB */
#define IX_OSAL_OS_THREAD_DEFAULT_STACK_SIZE  (10240) 

/* Maximum stack limit is 32 MB */
#define IX_OSAL_OS_THREAD_MAX_STACK_SIZE      (33554432)  /* 32 MBytes */

/* Default thread priority */
#define IX_OSAL_OS_DEFAULT_THREAD_PRIORITY    (90)

/* Thread maximum priority (0 - 255). 0 - highest priority */
#define IX_OSAL_OS_MAX_THREAD_PRIORITY	      (255)

#define IX_OSAL_OS_WAIT_FOREVER (-1L)  

#define IX_OSAL_OS_WAIT_NONE	0


/* Thread handle is eventually an int type */
typedef int IxOsalOsThread;

/* Semaphore handle */   
typedef struct semaphore *IxOsalOsSemaphore;

/* Mutex handle */
typedef struct semaphore *IxOsalOsMutex;

/* 
 * Fast mutex handle - fast mutex operations are implemented in
 * native assembler code using atomic test-and-set instructions 
 */
typedef int IxOsalOsFastMutex;

typedef struct
{
    UINT32 msgLen;	   /* Message Length */
	UINT32 maxNumMsg;  /* max number of msg in the queue */
	UINT32 currNumMsg; /* current number of msg in the queue */
	INT8   msgKey;     /* key used to generate the queue */
    INT8   queueId;	   /* queue ID */

} IxOsalOsMessageQueue;

#endif /* IxOsalOsTypes_H */