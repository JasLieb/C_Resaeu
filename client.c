#include "reseau.h"


int main(int argc, char const *argv[]) {
  	int scli, err, s = socket(AF_INET, SOCK_STREAM,0);
	struct sockaddr_in client;

	client.sin_family = AF_INET;
	client.sin_addr.s_addr = inet_addr("127.0.0.1");
	client.sin_port = htons(2000);

	scli = connect(s, (struct sockaddr*)&client, sizeof(client));
	if (scli == -1) {
		perror("pb connect");
	}

	err = send(s, "hello", sizeof("hello"), 0);
	if (err == -1) {
		perror("pb send");
	}


	return 0;
}
