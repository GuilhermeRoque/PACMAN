//#ifndef _MAPA_H_
//#define _MAPA_H_

struct mapa{
	char** matriz;	
	int linhas;
	int colunas;
};

typedef struct mapa MAPA;


#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'
#define VAZIO '.'
#define HEROI 'H'
#define FANTASMA 'F'
#define BOMBA '@'
#define PILULA '*'
#define PAREDE_V '|'
#define PAREDE_L '-'

void liberamapa(MAPA* m);
void alocamapa(MAPA* m);
void lemapa(MAPA* m);

//#endif