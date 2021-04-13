#include "server.h"
#define SERVER_PORT 23900
#define MAX 512

int start_server() {
	struct sockaddr_in server, client;

	int serverid = socket(AF_INET, SOCK_STREAM, 0);

	memset(&server, '0', sizeof(server));

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(SERVER_PORT);

	bind(serverid, (struct sockaddr*) &server, sizeof(server));

	if (listen(serverid, 10) == -1) {
		printf("ERROR");
		exit(1);
	}

	int len = sizeof(client);
	int clientid = accept(serverid, (struct sockaddr*) &client, &len);
	char msgsend[MAX] = "pedroigor";
	send(clientid, msgsend, sizeof(msgsend) - 1, 0);

	close(serverid);

	return 0;
}