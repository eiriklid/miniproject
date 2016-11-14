#include "thread_com.h"
#include <string.h>
#include <stdio.h>


void channel_init(struct channel* channel){
	channel->head = 0;
	channel->tail = 0;
	sem_init(&channel->sem, 0, 0);
}

void channel_send(struct channel* channel, char* input){
	strcpy(channel->buffer[channel->tail], input);
	channel->tail = (channel->tail + 1) % CHANNEL_SIZE;
	sem_post(&channel->sem);

}

void channel_receive(struct channel* channel, char* output){
	sem_wait(&channel->sem);
	strcpy(output, channel->buffer[channel->head]);
	channel->head = (channel->head + 1) % CHANNEL_SIZE; 
}


