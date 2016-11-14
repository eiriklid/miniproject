#include "miniproject.h"
#include "thread_com.h"

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define Kp 10
#define Ki 0.8
#define SETPOINT 1
#define PERIOD 3000
#define PERIOD_MS PERIOD/1000


#define ch_network 0
#define ch_controller 1

static struct udp_conn conn;

unsigned long get_nstime(){
	struct timespec tv;
	clock_gettime(CLOCK_REALTIME, &tv);
	return (1000000000*tv.tv_sec + tv.tv_nsec);
}

double strip_response(char* buffer){

	char val[1024];
	strncpy(val, buffer+8,1024);
	double response = atof(val);
	return response;
}


void* sender(void* channelParam){
	struct channel* channels = (struct channel*) channelParam;
	udp_send(&conn, "START", 6);
	channel_send(&channels[ch_controller], "START");
	char buff[BUFFER_SIZE];
	while(1){
		channel_receive(&channels[ch_network], buff);
		if (strncmp(buff, "GET", 3) == 0){
			udp_send(&conn, buff, 4);
		}
		else if(strncmp(buff, "SET", 3) == 0){
			udp_send(&conn, buff, strlen(buff) + 1);
		}else if(strncmp(buff, "STOP", 4) == 0){
			udp_send(&conn, buff, 5);
			return NULL;
		}
	}

}

void* receiver(void* channelParam){
	struct channel* channels = (struct channel*) channelParam;
	char buff[BUFFER_SIZE];

	while(1){
		udp_receive(&conn, buff, BUFFER_SIZE);

		if(strncmp(buff, "GET_ACK", 7) == 0){
			channel_send(&channels[ch_controller], buff);
		}
	}
}

void* controller(void* channelParam){	
	struct channel* channels = (struct channel*) channelParam;

	char output[BUFFER_SIZE];
	char input[BUFFER_SIZE];

	channel_receive(&channels[ch_controller], input);
	unsigned long time_start = get_nstime();
	unsigned long now = time_start;
	double y, error, u, integral;

	struct timespec next;
	clock_gettime(CLOCK_REALTIME, &next);


	while(now - time_start < 500000000){

		channel_send(&channels[ch_network],"GET");
		channel_receive(&channels[ch_controller], input);
		y = strip_response(input);
		error = SETPOINT - y;
		integral += error * PERIOD_MS;

		u =  (Kp * error + Ki * integral);

		sprintf(output, "SET:%f", u);
		channel_send(&channels[ch_network], output);

		now = get_nstime();

		timespec_add_us(&next, PERIOD);
		clock_nanosleep(&next); 

	}
	channel_send(&channels[ch_network], "STOP");
	return NULL;
}




int main(int argc, char* argv[]){

	udp_init_client(&conn, 9999, "192.168.0.1");
	
	struct channel channels[2];
	int i;
	for (i = 0; i < 2; i ++){
		channel_init(&channels[i]);
	}


	pthread_t send_t;
	pthread_t receive_t;
	pthread_t compute_t;

	pthread_create(&send_t, NULL, sender, (void*) channels);
	pthread_create(&receive_t, NULL, receiver, (void*) channels);
	pthread_create(&compute_t, NULL, controller, (void*) channels);

	pthread_join(send_t, NULL);
	pthread_join(receive_t, NULL);
	pthread_join(compute_t, NULL);



	return 0;

}

