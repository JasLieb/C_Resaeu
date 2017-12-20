#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int nbVoiture;
    int nbMoto;
    float prixForfait[2];
    float prixHorsForfait[2];
}HereData;

typedef struct {
	int etagePark;
	int nbPlace;
	float prixForfait;
	float prixHorsForfait;
}ServerData;

typedef struct {
	char plaque[10];
	char categorie;
	int dureeEnvisagee;
}BorneData;

void getInfo();