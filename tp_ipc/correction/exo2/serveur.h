#ifndef __SERVEUR_H__
#define __SERVEUR_H__

#define CLE_MSG		42
#define MSG_SIZE	2*sizeof(int)
#define ANSWER_SIZE	sizeof(int)

typedef struct mymsg_s {
	long type;
	int a;
	int b;
} mymsg_t;

typedef struct myanswer_s {
	long type;
	int result;
} myanswer_t;

#endif
