#include "miniproject.h"
#include "pi_controller.h"

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	/*
	unsigned long lastTime = 0;
	double Input, Output;
	double errSum = 0;
	Input = 0;

	Output = compute(Input, &lastTime, &errSum);
	*/

	int clientSocket, portNum, nBytes;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;

	/*Create UDP socket*/
	clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

	/*Configure settings in address struct*/
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	/*Initialize size variable to be used later on*/
	addr_size = sizeof serverAddr;

	nBytes = sprintf(buffer, "START") + 1;


	/*Send message to server*/
	sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);

	while(1){

		nBytes = sprintf(buffer, "GET")+ 1;

		/*Send message to server*/
		sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);

		/*Receive message from server*/
		nBytes = recvfrom(clientSocket,buffer,1024,0,NULL, NULL);

		printf("Received from server: %s\n",buffer);

	}
	return 0;

}