#include "client.h"
#define SERVER_IP "192.168.0.4"
#define SERVER_PORT 10125

int send_message(char * message) {
  int sockfd = 0,n = 0;
  char sendBuff[5000];
  struct sockaddr_in serv_addr;
 
  memset(sendBuff, '0' ,sizeof(sendBuff));
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
      printf("\n Error : Could not create socket \n");
      return 1;
    }
 
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(SERVER_PORT);
  serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
 
  if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
      printf("\n Error : Connect Failed \n");
      return 1;
    }
  strcpy(sendBuff, message);
  write(sockfd, sendBuff, strlen(sendBuff));

  close(sockfd);
 
  return 0;
}