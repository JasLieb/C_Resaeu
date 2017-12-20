#include "reseau.h"
#define BUF_LEN 100

ServerData this;
HereData thisServ;


char msg[] = "Bienvenue sur le Serveur\npseudo : ";
char buf[BUF_LEN];
void init() {
    printf("=== INITIALISATION ===\n");
    printf("Numéro de l'étage (un chiffre) : ");
    scanf("%d", &this.etagePark);

    printf("Prix du forfait : ");
    scanf("%f", &this.prixForfait);

    printf("Prix Hors forfait : ");
    scanf("%f", &this.prixHorsForfait);

    thisServ.nbVoiture =2;
    thisServ.nbMoto =2;

    thisServ.prixForfait[0] = 1;
    thisServ.prixForfait[1] = 2;
    thisServ.prixHorsForfait[0] = 2;
    thisServ.prixHorsForfait[1] = 4;

    printf("Etage du parking : %d\n", this.etagePark);
    printf("Etage du parking : %f\n", this.prixForfait);
    printf("Etage du parking : %f\n\n", this.prixHorsForfait);
}



int main(int argc, char **argv){
    int err, scli, s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serveur, client;

    init(this);

    serveur.sin_family = AF_INET;
    serveur.sin_addr.s_addr = INADDR_ANY;
    serveur.sin_port = htons(atoi(argv[1]));
    printf("%s:%d\n", inet_ntoa(serveur.sin_addr), atoi(argv[1]));

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
            int lbuf = (int) recv(scli, buf, 10, 0);
            buf[lbuf]= (char) "\0";
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
