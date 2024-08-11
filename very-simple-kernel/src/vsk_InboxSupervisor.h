/*----------------------------------------------------------------------------*/
#ifndef VSK_INBOXSUPERVISOR_H
#define VSK_INBOXSUPERVISOR_H
/*----------------------------------------------------------------------------*/
typedef struct vsk_InboxSupervisor vsk_InboxSupervisor;
/*----------------------------------------------------------------------------*/
#include "vsk_Inbox.h"
/*----------------------------------------------------------------------------*/
struct vsk_InboxSupervisor {
    ctb_LinkedList inboxes;
};
/*----------------------------------------------------------------------------*/
vsk_InboxSupervisor * vsk_InboxSupervisor_(void);
vsk_InboxSupervisor * vsk_InboxSupervisor_init(
    vsk_InboxSupervisor * const self
);
void vsk_InboxSupervisor_register(
    vsk_InboxSupervisor * const self, vsk_Inbox * const inbox
);
void vsk_InboxSupervisor_onTick(vsk_InboxSupervisor * const self);
#endif // VSK_INBOXSUPERVISOR_H
