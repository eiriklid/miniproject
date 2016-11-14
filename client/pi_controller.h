#ifndef PI_CONTROLLER_H_
#define PI_CONTROLLER_H_



struct chan_param{
	struct udp_conn;
	struct channels;
};

void* sender(void* channelParam);
void* receiver(void* channelParam);
void* controller(void* channelParam);
unsigned long get_nstime();

double strip_response(char* buffer);


#endif
