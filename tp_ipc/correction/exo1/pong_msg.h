#ifndef __PONG_MSG_H__
#define __PONG_MSG_H__ 	1

#define KEY		(key_t)1000
#define MSGSIZE	25

typedef struct pong_msg_s {
	long type;
	char msg[MSGSIZE];
} pong_msg_t;


#endif
