#ifndef THREAD_COM_H_
#define THREAD_COM_H_

#define BUFFER_SIZE 30
#define CHANNEL_SIZE 10 

#include <semaphore.h>


struct channel{
	char buffer[CHANNEL_SIZE][BUFFER_SIZE];
	int head;
	int tail;
	sem_t sem;
};

void channel_init(struct channel* channel);
void channel_send(struct channel* channel, char* input);
void channel_receive(struct channel* channel, char* output);

#endif
