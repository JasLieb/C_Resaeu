#include "reseau.h"

BorneData this;

int main(int argc, char const *argv[]) {

    int scli, err, s = socket(AF_INET, SOCK_STREAM,0);
    struct sockaddr_in client;

	client.sin_family = AF_INET;
	client.sin_addr.s_addr = inet_addr("127.0.0.1");
	client.sin_port = htons(atoi(argv[1]));

	scli = connect(s, (struct sockaddr*)&client, sizeof(client));
	if (scli == -1) {
		perror("pb connect");
	}

    // 1 client arrive à la borne
    getInfo();

	err = send(s, this.plaque, strlen(this.plaque), 0);
    err = send(s, this.categorie, strlen(this.categorie), 0);
    //err = send(s, this.dureeEnvisagee, strlen(this.dureeEnvisagee), 0);
	if (err == -1) {
		perror("pb send");
	}


	return 0;
}

void getInfo(){
    printf("Saisissez votre plaque : ");
    scanf("%s", &this.plaque);
    printf("Catégorie de votre véhicule ?\n A : voiture\n B : moto\n Votre choix :");
    scanf("%s", &this.categorie);
    printf("Durée envisagée de stationnement : ");
    scanf("%d", &this.dureeEnvisagee);
}
