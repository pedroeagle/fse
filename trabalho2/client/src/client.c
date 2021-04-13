
#include "client.h"
#define SERVER_IP "192.168.0.53"
#define SERVER_PORT 23900
#define MAX 512

int start_client() {
  struct sockaddr_in client;

  int socketid = socket(AF_INET, SOCK_STREAM, 0);
  if (socketid == -1) {
    printf("Could not create a socket!\n");
    exit(1);
  }

  client.sin_family = AF_INET;
  client.sin_addr.s_addr = inet_addr(SERVER_IP);
  client.sin_port = htons(SERVER_PORT);

  if (connect(socketid, (struct sockaddr*) &client, sizeof(client)) < 0) {
    printf("Error: Connection failed\n");
    exit(1);
  }

  char msgrecv[MAX];
  int n = recv(socketid, msgrecv, sizeof(msgrecv) - 1, 0);

  if (n < 0) {
    printf("Read error\n");
    exit(1);
  }

  printf("%s\n", msgrecv);

  close(socketid);

  return 0;
}
