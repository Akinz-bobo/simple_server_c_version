#include "SocketUtil.h"
#include <stdint.h>
#include <pthread.h>


void startListeningAndPrintMessagesOnNewThread(int socketFD);
void* listenAndPrint(void* socketFD);
int main()
{
   int socketFD =  createTCPIpv4Socket();
   struct sockaddr_in *address = createTCPIpv4Address("127.0.0.1", 2000);

   int result = connect(socketFD, (struct sockaddr *)address, sizeof (*address));
   if(result ==0){
    printf("connection was successful\n");
   }

   char *line =NULL;
   size_t lineSize = 0;
   printf("type and we send()...\n");


   char *name =NULL;
   size_t nameSize = 0;
   printf("please enter your name...\n");
   size_t nameCount = getline(&name, &nameSize, stdin );
   name[nameCount-1] = 0;

   startListeningAndPrintMessagesOnNewThread(socketFD);

char buffer[1024];
   while(true)
   {
     
      size_t charCount = getline(&line, &lineSize, stdin );
      line[charCount-1] = 0;

      sprintf(buffer, "%s:%s", name, line);
      if(charCount >0 )
      {
         if(strcmp(line, "exit") == 0)
         {
            break;
         }

      size_t amountSent = send(socketFD,buffer, strlen(buffer), 0);
      }
   }

   close(socketFD);
   return 0;
}

void startListeningAndPrintMessagesOnNewThread(int socketFD)
{

   pthread_t id;
   pthread_create(&id,NULL,listenAndPrint, (void *)(intptr_t )socketFD);
}

void* listenAndPrint(void* socketFD)
{
int fd = (intptr_t)socketFD;
  char buffer[1024];

while(true)
  {
    
      size_t amountRev = recv(fd, buffer, 1024, 0);
      if(amountRev >0)
      {
        buffer[amountRev] = 0;
      printf("%s\n", buffer);
      }else
      {
        break;
      }
  }
  close(fd);
  return NULL;
}