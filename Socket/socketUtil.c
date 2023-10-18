
#include "SocketUtil.h"

// struct sockaddr_in* createTCPIpv4Address(char *ip, int port){
//    struct sockaddr_in *address = (struct sockaddr_in *)malloc(sizeof (struct sockaddr_in));
//    address->sin_family = AF_INET;
//    address->sin_port = htons(port);
//    inet_pton(AF_INET, ip, (struct sockaddr *)&address->sin_addr.s_addr);
//    return address;
// }

struct sockaddr_in* createTCPIpv4Address(char *ip, int port){
   struct sockaddr_in *address = (struct sockaddr_in *)malloc(sizeof (struct sockaddr_in));
   address->sin_family = AF_INET;
   address->sin_port = htons(port);

   if(strlen(ip) ==0)
   {
        address->sin_addr.s_addr = INADDR_ANY;
   }
    else
    {
        inet_pton(AF_INET, ip, (struct sockaddr *)&address->sin_addr.s_addr);
    }
   return address;
}


int createTCPIpv4Socket(){
return socket(AF_INET, SOCK_STREAM,0);
}