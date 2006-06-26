/**
 * @file IxOsalOsThread.c (linux)
 *
 * @brief OS-specific thread implementation.
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

#include <linux/sched.h>

#include "IxOsal.h"

PRIVATE struct
{
    IxOsalVoidFnVoidPtr entryPoint;
    void *arg;
} IxOsalOsThreadData;

/* declaring mutex */
DECLARE_MUTEX (IxOsalThreadMutex);

static int
thread_internal (void *unused)
{
    IxOsalVoidFnVoidPtr entryPoint = IxOsalOsThreadData.entryPoint;
    void *arg = IxOsalOsThreadData.arg;
    static int seq = 0;

    daemonize ();
    reparent_to_init ();

    exit_files (current);

    snprintf(current->comm, sizeof(current->comm), "IxOsal %d", ++seq);

    up (&IxOsalThreadMutex);

    entryPoint (arg);
    return 0;
}

/* Thread attribute is ignored */
PUBLIC IX_STATUS
ixOsalThreadCreate (IxOsalThread * ptrTid,
    IxOsalThreadAttr * threadAttr, IxOsalVoidFnVoidPtr entryPoint, void *arg)
{
    down (&IxOsalThreadMutex);
    IxOsalOsThreadData.entryPoint = entryPoint;
    IxOsalOsThreadData.arg = arg;

    /*
     * kernel_thread takes: int (*fn)(void *)  as the first input.
     */
    *ptrTid = kernel_thread (thread_internal, NULL, CLONE_SIGHAND);

    if (*ptrTid < 0)
    {
        up (&IxOsalThreadMutex);
        ixOsalLog (IX_OSAL_LOG_LVL_ERROR,
            IX_OSAL_LOG_DEV_STDOUT,
            "ixOsalThreadCreate(): fail to generate thread \n",
            0, 0, 0, 0, 0, 0);
        return IX_FAIL;
    }

    return IX_SUCCESS;

}

/* 
 * Start thread after given its thread handle
 */
PUBLIC IX_STATUS
ixOsalThreadStart (IxOsalThread * tId)
{
    /* Thread already started upon creation */
    return IX_SUCCESS;
}

/*
 * In Linux threadKill does not actually destroy the thread,
 * it will stop the signal handling.
 */
PUBLIC IX_STATUS
ixOsalThreadKill (IxOsalThread * tid)
{
    kill_proc (*tid, SIGKILL, 1);
    return IX_SUCCESS;
}

PUBLIC void
ixOsalThreadExit (void)
{
    ixOsalLog (IX_OSAL_LOG_LVL_MESSAGE,
        IX_OSAL_LOG_DEV_STDOUT,
        "ixOsalThreadExit(): not implemented \n", 0, 0, 0, 0, 0, 0);
}

PUBLIC IX_STATUS
ixOsalThreadPrioritySet (IxOsalOsThread * tid, UINT32 priority)
{
    return IX_SUCCESS;
}

PUBLIC IX_STATUS
ixOsalThreadSuspend (IxOsalThread * tId)
{
    ixOsalLog (IX_OSAL_LOG_LVL_WARNING,
        IX_OSAL_LOG_DEV_STDOUT,
        "ixOsalThreadSuspend(): not implemented in linux \n",
        0, 0, 0, 0, 0, 0);
    return IX_SUCCESS;

}

PUBLIC IX_STATUS
ixOsalThreadResume (IxOsalThread * tId)
{
    ixOsalLog (IX_OSAL_LOG_LVL_WARNING,
        IX_OSAL_LOG_DEV_STDOUT,
        "ixOsalThreadResume(): not implemented in linux \n",
        0, 0, 0, 0, 0, 0);
    return IX_SUCCESS;

}
