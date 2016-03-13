/*-- tlg.h --- LISTA SIMPLU INLANTUITA GENERICA (laborator) ---*/
/* LUPASCU Andrei - 311 CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_
typedef struct celg
{ struct celg *urm;   /* adresa urmatoarei celule */
  void* info;           /* adresa informatie */
} TCelulaG, *TLG, **ALG; /* tipurile Celula, Lista si Adresa_Lista */
typedef struct 
{ int id,priority,pas;
} proces ;
typedef void (*TF)(void*,FILE *);     /* functie afisare un element */

/*-- operatii elementare - primul parametru este lista sau adresa de lista --*/

/*- inserare la inceput reusita sau nu (1/0) -*/
int InsLg(ALG, void*);         
void DistrugeLG(ALG);  
size_t LungimegLG(ALG);   /* numarul de elemente din lista */
void AfisareLG(TLG, TF,FILE *fout);
void AfiVal(void * ae,FILE *fout);
void inserare_coada(ALG aL,proces p);
proces scoate_coada(ALG aL);
void adauga_stiva(ALG stiva, proces p);
proces sterge_stiva(ALG stiva);
void sterge_id_din_coada(ALG aL, int id);
void Afisare(ALG aL, TF afiEL,FILE *fout);
void muta_id_din_coada_in_eveniment(ALG aL, int id,ALG stiva);
void distruge_stiva_si_adauga_in_coada(ALG coada, ALG stiva);
    /* afiseaza elementele din lista, folosind o functie de tip TFA */        

#endif
