#ifndef _REQUEST_H_
#define _REQUEST_H_

#include "client.h"

#define RQ_REGISTER_TYPE 0 
#define RQ_LOGIN_TYPE 1 
#define RQ_LOGOUT_TYPE 2
#define RQ_SHOW_ACTIVE_USERS_TYPE 3
#define RQ_SND_MSG_TYPE 4
#define RQ_SND_MSG_ALL_TYPE 5
#define RQ_HEART_BEAT_TYPE 6
#define RQ_ERROR_TYPE 7
#define RQ_UNREQUESTED 100


#define RET_SUCCESS 0
#define RET_FAIL 1

#define REQUEST_HEAD_SIZE 52

typedef struct request {
    client_t *client;

    //read from socket,if change must modify REQUEST_HEAD_SIZE
    int version;
    char from[20];
    char to[20];
    int type;
    int body_size;
    char body[0];
} request_t;

typedef struct response {
    int ret;
    int type;
    int msg_len;
    char msg[0];
} response_t;



struct request * read_request(struct client *p);

int send_response(client_t *p, int ret, int type, char *msg);

int do_request(struct request *rq);

void do_login_request(request_t *rq);

void do_register_request(request_t *rq);

void do_show_active_users_request(request_t *rq);

void do_snd_msg_request(request_t *rq);

void do_snd_msg_all_request(request_t *rq);

void do_heart_beat_request(request_t *rq);

void do_logout_request(request_t *rq);

#endif
