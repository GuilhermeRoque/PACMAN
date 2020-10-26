//#ifndef _FOGE_H_
//#define _FOGE_H_

struct posicao{
	int x;
	int y;
	
};

typedef struct posicao POSICAO;


void libera_pilulas();
void abertura();
void achaboneco(POSICAO* p_boneco,char c);
void conta_coisas();
void pega_coisas();
void libera_fantasmas();
void libera_bombas();
void aloca_coisas();
int ehdirecao(char comando);
void prox_passo(char comando,int *proximo_x,int *proximo_y);
int ehcaminho(int proximo_x, int proximo_y);
void controla_heroi(char comando);
void move_fantasma();
void move(int proximo_x,int proximo_y);
void joga_bomba(int proximo_x,int proximo_y);
void inicializa();
void explode_bomba();
void explode_bomba2(int x, int y, int soma_x,int soma_y,int qtd);
void mata_fantasma();

//#endif