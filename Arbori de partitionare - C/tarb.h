// LUPASCU Andrei - 311 CB
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
typedef struct infoh
{
	char mod; //mod = 'p' e de tip punct, 'd' e de tip dreapta
	int d_a,d_b,d_c; //valorile a,b,c pentru dreapta
	int p_x,p_y,p_p; //valorile x,y,partitionare pentru puncte ( frunze )
}	TInfo;
typedef struct nod 
{ 
	TInfo info;
	struct nod*st, *dr;
} 	TNod, *TArb, **AArb;
void DistrArb(TArb *a) ;
void distruge(TArb r);
void cerinta_1(TArb arbore,int *aux1,int *aux2,int *aux3,FILE *fin); //construieste arborele in functie de datele de intrare
void postordine(TArb a,FILE *fout);//afiseaza arborele in postordine
void adaug_dreapta(int a,int b,int c,TArb arbore); //adauga dreapta ax+by+c =0 in arbore
void adaug_punct(TArb arbore,int x,int y,int i);	//adauga frunza de tip punct (X,Y) in arbore
int cauta(TArb arbore,int x,int y);//cauta partitionarea punctului (X,Y) in arbrore si o returneaza

