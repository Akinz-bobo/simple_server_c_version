
#include "SocketUtil.h"
#include <pthread.h>
#include <stdint.h>

struct AcceptedSocket 
{
  int acceptedSocketFD;
  struct sockaddr_in address;
  int error;
  bool acceptedSuccessfully; 
};
struct AcceptedSocket * acceptIncomingConnection(int serverSocketFD);

void* receiveAndPrintIncomingRequest( void* socketFD);
void startAcceptingIncommingConnection(int serverSocketFD);
void receiveAndPrintIncomingDataOnSeparateThread(struct AcceptedSocket* clientSocket);
 struct AcceptedSocket acceptedSockets[10];
int acceptedSocketCount = 0;
void sendReceivedMesageToOtherClient(char *buffer, int socketFD);

struct AcceptedSocket* acceptIncomingConnection(int serverSocketFD)
{
  struct sockaddr_in clientAddress;
socklen_t clientAddressSize = sizeof(struct sockaddr_in);
int clientSocketFD = accept(serverSocketFD,(struct sockaddr *)&clientAddress, &clientAddressSize ); 
struct AcceptedSocket * acceptedSocket = (struct AcceptedSocket *)malloc( sizeof (struct AcceptedSocket));
acceptedSocket->address = clientAddress;
acceptedSocket->acceptedSocketFD = clientSocketFD;
acceptedSocket->acceptedSuccessfully = clientSocketFD >0;
if(!acceptedSocket->acceptedSuccessfully) {
  acceptedSocket->error = clientSocketFD;
}
return acceptedSocket;
}


void receiveAndPrintIncomingDataOnSeparateThread(struct AcceptedSocket* clientSocket)
{
   
  pthread_t id;
  pthread_create(&id, NULL,receiveAndPrintIncomingRequest,(void *)(intptr_t)clientSocket->acceptedSocketFD);
}

void* receiveAndPrintIncomingRequest(void* socketFD)
{
int fd = (intptr_t)socketFD;
  char buffer[1024];
while(true)
  {
    
      size_t amountRev = recv(fd, buffer, 1024, 0);
      if(amountRev >0)
      {
        buffer[amountRev] = 0;
      printf(">%s\n", buffer);
      sendReceivedMesageToOtherClient(buffer, fd);

      }else
      {
        break;
      }
  }
  close(fd);
  return NULL;


}

void sendReceivedMesageToOtherClient(char *buffer, int socketFD)
{
  for (int i = 0; i <acceptedSocketCount; i++)
  {
    if(acceptedSockets[i].acceptedSocketFD != socketFD)
    {
      send(acceptedSockets[i].acceptedSocketFD, buffer, strlen(buffer),0);
    }
  }
}

void startAcceptingIncommingConnection(int serverSocketFD)
{
  while(true)
  {
  struct AcceptedSocket* clientSocket = acceptIncomingConnection(serverSocketFD);
  acceptedSockets[acceptedSocketCount++] = *clientSocket;
  receiveAndPrintIncomingDataOnSeparateThread(clientSocket);
  
  }
}


int main()
{

int serverSocketFD = createTCPIpv4Socket();
struct sockaddr_in *address = createTCPIpv4Address(" ",2000);
int result = bind(serverSocketFD, (struct sockaddr *)address, sizeof (*address));

if(result == 0)
{
    printf("server socket was bound successfully\n");
}

int listenResult = listen(serverSocketFD, 10);

startAcceptingIncommingConnection(serverSocketFD);

 shutdown(serverSocketFD, SHUT_RDWR);
return 0; 
}