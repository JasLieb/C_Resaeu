#include "reseau.h"
#define BUF_LEN 100

char buf[BUF_LEN];
char msg[] = "Bienvenue sur le Serveur\npseudo : ";

void repondreCli(int scli){
	//send(scli, msg, strlen(msg), 0);
	//Cal lbuf = recv(scli, buf, BUF_LEN, 0);
	//buf[lbuf]='\0'; // PAS DE DOUBLE QUOTE CAR SINON \o COMPRIS COMME CHAINE DE CARACTERE !!!

	/*int res;
	switch(lbuf.op){
		case '+':
			res = lbuf.a + lbuf.b;
			break;
		case "-":
			res = lbuf.a - lbuf.b;
			break;
		case "*":
			res = lbuf.a * lbuf.b;
			break;
		case "/":
			res = lbuf.a / lbuf.b;
			break;
	}*/
	//printf("%d", res);

//	printf("%s\n", buf);

/*	char msg2[] = "Mot de passe : ";
	send(scli, msg2, strlen(msg2), 0);
	lbuf = recv(scli, buf, BUF_LEN, 0);
	buf[lbuf]='\0';
	char br[] = "toto\0";

	if(!strcmp(br, buf)){
		char msg3[] = "ok\n";
		send(scli, msg3, strlen(msg3), 0);
	}else{
		char msg3[] = "PAS OK !!!!\n";
		send(scli, msg3, strlen(msg3), 0);
	}*/
}

int main(){
	int err, scli, s = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serveur, client;

	serveur.sin_family = AF_INET;
	serveur.sin_addr.s_addr = INADDR_ANY;
	serveur.sin_port = htons(2000);

	err = bind(s, (struct sockaddr *) &serveur, sizeof(serveur));
	if (err == -1){
		perror("pb BIND");
		exit(0);
	}

	err = listen(s, 1);
	if (err == -1){
		exit(0);
		perror("pb LISTEN");
	}

//	sleep(20);

	while(1){
		socklen_t lg = sizeof(client);
		scli = accept(s, (struct sockaddr *) &client, &lg);
		if (scli == -1)
			perror("pb ACCEPT");

		printf("1 nouveau client accepté\n");
		printf("add client : %s\n", inet_ntoa(client.sin_addr));
		printf("port client : %d\n\n", ntohs(client.sin_port));

		int pid = fork();
		if(pid == 0){
//			repondreCli(scli);
		int lbuf = recv(scli, buf, BUF_LEN, 0);
		buf[lbuf]="\0";
		printf("%s\n", buf);
			close(scli);
			exit(EXIT_SUCCESS);
		}
		else{
			close(scli);
		}

		/*send(scli, msg, strlen(msg), 0);
		int lbuf = recv(scli, buf, BUF_LEN, 0);
		buf[lbuf]="\0";
		printf("%s\n", buf);


		err = getsockname(s, (struct sockaddr *) &infoser, &lg);
		if (err == -1)
			perror("pb GETSOCKNAME");
		else{
			printf("add serveur : %s\n", inet_ntoa(infoser.sin_addr));
			printf("port serveur : %d\n\n", ntohs(infoser.sin_port));
		}

		err = getpeername(s, (struct sockaddr *) &infoser, &lg);
		if (err == -1)
			perror("pb GETPEERNAME");*/


	}
	close(s);

	return 0;
}
