#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "foge.h"
#include "mapa.h"
#include "ui.h"

MAPA m;
POSICAO p_heroi;

int** fantasmas;
int** bombas;
int** pilulas;

int ganhou =0;
int perdeu =0;
int tembomba=0;
int n_fantasmas =0;
int n_bombas =0;
int n_pilulas =0;
int tempilula = 0;
int morreu_fantasma = 0;

void achaboneco(POSICAO* p_boneco,char c){
	int achou =0;
	for(int i =0;i< m.linhas;i++){
		for(int j=0;j< m.colunas;j++){
			if (m.matriz[i][j]== c){
				achou =1;
				p_boneco->x = i;
				p_boneco->y = j;
				break;
			}
		}
		if (achou)
			break;
	}
	
}


void conta_coisas(){
	for(int i =0;i< m.linhas;i++){
		for(int j=0;j< m.colunas;j++){
			if (m.matriz[i][j]== FANTASMA){
				n_fantasmas++;
			}
			else if(m.matriz[i][j]== BOMBA){
				n_bombas++;
			}
			else if(m.matriz[i][j]== PILULA){
				n_pilulas++;
			}
		}
	}
}


void pega_coisas(){
	int achou_fantasma =0;
	int achou_bomba =0;
	int achou_pilula =0;
	
	for(int i =0;i< m.linhas;i++){
		for(int j=0;j< m.colunas;j++){
			if (m.matriz[i][j]== FANTASMA){
				fantasmas[achou_fantasma][0]=i;
				fantasmas[achou_fantasma][1]=j;
				achou_fantasma++;
			}
			else if (m.matriz[i][j]== BOMBA){
				bombas[achou_bomba][0]=i;
				bombas[achou_bomba][1]=j;
				achou_bomba++;
			}
			else if (m.matriz[i][j]== PILULA){
				pilulas[achou_pilula][0]=i;
				pilulas[achou_pilula][1]=j;
				achou_pilula++;
			}
		}
	}
}



void libera_fantasmas(){
	for (int i= 0;i <n_fantasmas;i++)
		free(fantasmas[i]); 
	free(fantasmas);
	
}
void libera_bombas(){  
	
	for (int i= 0;i <n_bombas;i++)
		free(bombas[i]); 
	free(bombas);

}

void libera_pilulas(){  
	
	for (int i= 0;i <n_pilulas;i++)
		free(pilulas[i]); 
	free(pilulas);

}

void aloca_coisas(){
	fantasmas = malloc(sizeof(int*) * n_fantasmas); 
	for(int i = 0;i < n_fantasmas;i++)
		fantasmas[i]= malloc(sizeof(int)*(2));
	
	bombas = malloc(sizeof(int*) * n_bombas); 
	for(int i = 0;i < n_bombas;i++)
		bombas[i]= malloc(sizeof(int)*(4));
	
	pilulas = malloc(sizeof(int*) * n_pilulas); 
	for(int i = 0;i < n_pilulas;i++)
		pilulas[i]= malloc(sizeof(int)*(2));
	
	
}




int ehdirecao(char comando){
	if ((comando != ESQUERDA)&&(comando!=CIMA)&&(comando != DIREITA)&&(comando != BAIXO))
		return 0;
	
	else{
		return 1;
	}

}

void prox_passo(char comando,int *proximo_x,int *proximo_y){
	switch(comando){
		
		case CIMA:
			(*proximo_x)--;
			break;
			
		case ESQUERDA:
			(*proximo_y)--;
			break;
		
		case DIREITA:
			(*proximo_y)++;
			break;
			
		case BAIXO:
			(*proximo_x)++;
			break;
	
	}
}
int ehcaminho(int proximo_x, int proximo_y){ 
	
	if(m.matriz[proximo_x][proximo_y] != VAZIO)
		return 0;
	
	else if((proximo_x == m.linhas)||(!proximo_x))
		return 0;
		
	else if ((proximo_y ==  m.colunas)|| (!proximo_y))
		return 0;
	
	else {
		return 1;
	}
	
}

void move(int proximo_x,int proximo_y){
	m.matriz[p_heroi.x][p_heroi.y]= VAZIO;
	p_heroi.x = proximo_x;
	p_heroi.y = proximo_y;
	m.matriz[p_heroi.x][p_heroi.y]= HEROI;

}



void joga_bomba(int proximo_x,int proximo_y){
	
	m.matriz[p_heroi.x][p_heroi.y]= BOMBA;
	
	for(int i = 0;i< n_bombas;i++)
		if(bombas[i][2]){
		bombas[i][0] = p_heroi.x;
		bombas[i][1] = p_heroi.y;
		bombas[i][2] = 0;
		bombas[i][3] = 1;
		break;
		}
	p_heroi.x = proximo_x;
	p_heroi.y = proximo_y;
	
	m.matriz[p_heroi.x][p_heroi.y]= HEROI;
	
	tembomba--;

}

void controla_heroi(char comando){
	
	
	if((!ehdirecao(comando))&& (comando != 'b'))
		return;
	
	
	int proximo_x = p_heroi.x; 
	int proximo_y = p_heroi.y;
	
	
	if (comando == 'b'){
		if(!tembomba)
			return;
		scanf(" %c",&comando);
		if(!ehdirecao(comando))
			return;
		prox_passo(comando,&proximo_x,&proximo_y);
		if(!ehcaminho(proximo_x,proximo_y))
			return;
		joga_bomba(proximo_x,proximo_y);
	}

	
	prox_passo(comando,&proximo_x,&proximo_y);
	
	if (m.matriz[proximo_x][proximo_y] == BOMBA){
		tembomba++;
		for(int i = 0;i< n_bombas;i++){
			if ((proximo_x == bombas[i][0]) && (proximo_y == bombas[i][1])){
				bombas[i][2] =1;
				break;
			}
		}
	}
	
	else if(m.matriz[proximo_x][proximo_y] == PILULA)
		tempilula++;
	
	else if (!ehcaminho(proximo_x,proximo_y))
		return;
		
	move(proximo_x,proximo_y);
		
}



void move_fantasma(){
	srand( (unsigned)time(NULL) );
	for (int i = 0;i < n_fantasmas;i++){
		int opcoes[4][2]={
			{fantasmas[i][0],fantasmas[i][1] + 1},
			{fantasmas[i][0],fantasmas[i][1] -1},
			{fantasmas[i][0]+ 1,fantasmas[i][1]},
			{fantasmas[i][0]- 1,fantasmas[i][1]}
		};
		
		for(int cont = 0; cont<10;cont++){
			int escolha = rand() %4;			
			if ((opcoes[escolha][0] == p_heroi.x) && (opcoes[escolha][1] == p_heroi.y)){
				perdeu =1;
				m.matriz[p_heroi.x][p_heroi.y]=FANTASMA;
				m.matriz[fantasmas[i][0]][fantasmas[i][1]]=VAZIO;
				return;
			}
			if (ehcaminho(opcoes[escolha][0],opcoes[escolha][1])){
				m.matriz[fantasmas[i][0]][fantasmas[i][1]]= VAZIO;
				fantasmas[i][0] = opcoes[escolha][0];
				fantasmas[i][1]= opcoes[escolha][1];
				m.matriz[fantasmas[i][0]][fantasmas[i][1]]= FANTASMA;
				break;
			}
		}
		
	}
}
/*
void explode_bomba(){
	for(int i = 0;i < n_bombas;i++){
		if(bombas[i][3]){   
			if (bombas[i][3] == 4){
				printf("bomba[%d] x:%d  y:%d  \n",i,bombas[i][0],bombas[i][1]);
				explode_bomba2(bombas[i][0], bombas[i][1], 0, 1, 3);
				explode_bomba2(bombas[i][0], bombas[i][1], 0,(-1), 3);
				explode_bomba2(bombas[i][0], bombas[i][1], 1, 0, 3);
				explode_bomba2(bombas[i][0], bombas[i][1], (-1), 0, 3);

				bombas[i][3] = 0;
			}
			else{
				bombas[i][3]++;
			}
		}
	}
}
	
void explode_bomba2(int x, int y, int soma_x,int soma_y,int qtd){
	
	
	if (!qtd) return;
	
	int novo_x = x + soma_x;
	int novo_y = y + soma_y;
	
	if((novo_x == m.linhas)||(!novo_x))
		return;
		
	else if ((novo_y ==  m.colunas)||(!novo_y))
		return;
	
	if (m.matriz[novo_x][novo_y] == FANTASMA){
		m.matriz[novo_x][novo_y] = VAZIO;
		morreu_fantasma =1;
	}
	
	else if(m.matriz[novo_x][novo_y] == HEROI){
		m.matriz[novo_x][novo_y] = VAZIO;
		acabou=1;
	}
	explode_bomba2(novo_x, novo_y, soma_x, soma_y, (qtd -1));
}

*/

void volta_bomba(int i){
	srand( (unsigned)time(NULL) );
	
	int x;
	int y;
	int achou = 0;
	do{
		x = rand ()% (m.linhas);
		y = rand ()% (m.colunas);
		if(m.matriz[x][y] == VAZIO){
			m.matriz[x][y] = BOMBA;
			achou = 1;
			bombas[i][0] =x;
			bombas[i][1] =y;
		}			
	}while(!achou);
}

void explode_bomba(){
	for(int i = 0;i < n_bombas;i++){
		if(bombas[i][3]){   
			if (bombas[i][3] == 4){ 
				for(int j = 1;j <= 3;j++){
					for (int w = 0; w < 4;w++){
						int opcoes[4][2]={
							{bombas[i][0],bombas[i][1] + j},
							{bombas[i][0],bombas[i][1] -j},
							{bombas[i][0]+ j,bombas[i][1]},
							{bombas[i][0]- j,bombas[i][1]}
						};
						for(int z =0;z < n_fantasmas;z++){
							
							if((opcoes[w][0] == fantasmas[z][0]) && (opcoes[w][1] == fantasmas[z][1])){
								m.matriz[fantasmas[z][0]][fantasmas[z][1]]= VAZIO;
								morreu_fantasma =1;

							}
							else if((opcoes[w][0] == p_heroi.x) && (opcoes[w][1] == p_heroi.y)){
								m.matriz[p_heroi.x][p_heroi.y] = VAZIO;
								perdeu =1;
								return;
							}
						}	
					}
				}
				
				bombas[i][3] = 0;
				m.matriz[bombas[i][0]][bombas[i][1]] = VAZIO;
				volta_bomba(i);
			}
			
			else bombas[i][3]++;
			
		}
		
	}
}




void inicializa(){
	for(int i = 0;i < n_bombas;i++){
		bombas[i][2]=0;
		bombas[i][3]=0;
	}
}


void mata_fantasma(){
	libera_fantasmas();
	
	n_fantasmas = 0;
	
	for(int i =0;i< m.linhas;i++){
		for(int j=0;j< m.colunas;j++){
			if (m.matriz[i][j]== FANTASMA){
				n_fantasmas++;
			}
		}
	}
	
	fantasmas = malloc(sizeof(int*) * n_fantasmas); 	
	for(int i = 0;i < n_fantasmas;i++){
		fantasmas[i]= malloc(sizeof(int)*(2));
	}
	
	int achou_fantasma =0;
	for(int i =0;i< m.linhas;i++){
		for(int j=0;j< m.colunas;j++){
			if (m.matriz[i][j]== FANTASMA){
				fantasmas[achou_fantasma][0]=i;
				fantasmas[achou_fantasma][1]=j;
				achou_fantasma++;
			}
		}
	}
	
	morreu_fantasma =0;
	if(!n_fantasmas){
		ganhou =1;
	}
	
	
}

int main(){
	lemapa(&m);
	achaboneco(&p_heroi,HEROI);
	
	conta_coisas();
	aloca_coisas();
	pega_coisas();
	inicializa();
	imprimemapa(&m);
	do {
		
		char comando;
		scanf(" %c",&comando);
		controla_heroi(comando);
		move_fantasma();
		explode_bomba();
		if (morreu_fantasma) mata_fantasma();
		imprimemapa(&m);
		
	
	}while((!ganhou) && (!perdeu));
	
	if (ganhou) printf("--------- PARABENS VOCE GANHOU!! --------\n\n");
	else printf("-------O FANTASMA COMEU VOCE---------\n\n");
	
	libera_fantasmas();
	libera_bombas();
	libera_pilulas();
	liberamapa(&m);

		
}



