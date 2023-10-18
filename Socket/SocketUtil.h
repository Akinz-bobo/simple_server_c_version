#ifndef SocketUtil_h
#define SocketUtil_h

#include <stdbool.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int createTCPIpv4Socket();
struct sockaddr_in *createTCPIpv4Address(char *ip, int port);


#endif // SocketUtil_h