#include <stdio.h>
#include "exokernel.h"
#include "ipc.h"
#include <exo_ipc.h>
/* Stubs delegating to user-space file server */
extern int fs_open(const char *path, int flags);
int
kern_open(const char *path, int flags)
{
    struct ipc_message msg = {
        .type = IPC_MSG_OPEN,
        .a = (uintptr_t)path,
        .b = (uintptr_t)flags
    };
    (void)ipc_queue_send(&kern_ipc_queue, &msg);
    struct ipc_message reply;
    struct ipc_mailbox *mb = ipc_mailbox_current();
    if (ipc_queue_recv_timed(&mb->queue, &reply, 1000) == EXO_IPC_OK) {
        if (reply.type != IPC_MSG_OPEN)
            return (int)reply.a;
    }
    return fs_open(path, flags);
}
