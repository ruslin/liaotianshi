#include "client.h"
#include <stdio.h>

void clients_info_init(struct clients_info *info, int max_clients) {
    memset(info, 0, sizeof(*info));
    info->max_clients = max_clients;
}

struct client *new_add_client(struct clients_info *info, int fd) {
    if (info->nr_clients >= info->max_clients) {
        printf(">>>> too more clients\n");
        return NULL;
    }

    struct client *p = (struct client *)malloc(sizeof(struct client));
    if (!p) {
        printf("malloc client failed\n");
        return NULL;
    }

    memset(p, 0, sizeof(*p));
    p->fd = fd;

    if (!info->nr_clients) {
        info->nr_clients = 1;
        info->head = p;
        info->tail = p;
    } else {
        info->nr_clients++;
        info->tail->next = p;
        p->prev = info->tail;
    }
    
}

void del_client(struct clients_info *info, struct client *client) {

    if (client == info->head) {
        info->head = client->next;
        if (client->next)
            client->next->prev = 0;
    } else if(client == info->tail) {
        info->tail = client->prev;
        if (client->prev)
            client->prev->next = 0;
    } else {
//        struct client *p = client->next;
        client->prev->next = client->next;
        client->next->prev = client->prev;
    }

    info->nr_clients--;

    if (!info->nr_clients) {
        info->head = 0;
        info->tail = 0;
    }
    printf(">>> delete client %p now remain clients = %d\n", client, info->nr_clients);
    free(client);
}
