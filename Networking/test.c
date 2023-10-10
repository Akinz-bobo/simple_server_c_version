#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Server.h"

void launch( struct Server * server)
{
    printf("3\n");
    char buffer[300000];
    int address_length = sizeof(server->address);
    int new_socket;
 char *hello = "HTTP/1.1 200 OK\nGMT\nServer: Apache/2.2.14 (Win32)\nLast-Modified: Sun, 8 October 2023 0:55:56GMT\nContent-Type: text/html\nConnection: close\n\n<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>From Server</title></head><body><h2>Hello, Gourab please mentor me!</h2></body></html>";

    while (1)
    
{
    printf( "====== Waiting For Connection ======\n");
    new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
    printf("6\n");
    read(new_socket, buffer, 300000);
   // printf("%s\n", buffer);
 write(new_socket, hello, strlen(hello));

   
   printf("7\n");
    close(new_socket);
    }
}



int main()
{
    printf("1\n");
    struct Server server = server_contructor(AF_INET,SOCK_STREAM, 0, INADDR_ANY, 8087, 10, launch);
printf("2\n");
    server.launch(&server);
}