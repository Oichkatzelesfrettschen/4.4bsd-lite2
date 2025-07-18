#include "exo_ipc.h"
#include "ipc.h"
#include <stdio.h>

/** Simple unit test for mailbox send/receive. */
int main(void) {
    ipc_mailbox_init();
    struct ipc_mailbox *a = ipc_mailbox_lookup(1);
    struct ipc_mailbox *b = ipc_mailbox_lookup(2);

    struct ipc_message msg = {.type = IPC_MSG_HEARTBEAT, .a = 123};
    ipc_queue_send(&a->queue, &msg);

    if (ipc_queue_recv_timed(&b->queue, &msg, 5) != EXO_IPC_TIMEOUT) {
        printf("unexpected message\n");
        return 1;
    }

    ipc_queue_send_yield(&b->queue, &msg);
    if (ipc_queue_recv_timed(&b->queue, &msg, 5) != EXO_IPC_OK) {
        printf("recv failed\n");
        return 1;
    }

    printf("mailbox ok\n");
    return 0;
}
