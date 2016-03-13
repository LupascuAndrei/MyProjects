/* LUPASCU Andrei - 311 CB */
/*-- tlg.h --- LISTA SIMPLU INLANTUITA GENERICA (laborator) ---*/
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
{ char *key, *value;
} web ;
typedef void (*TF)(void*,FILE *fout);     /* functie afisare un element */

/*-- operatii elementare - primul parametru este lista sau adresa de lista --*/

/*- inserare la inceput reusita sau nu (1/0) -*/
int InsLG(ALG aL, void* ae, size_t d);
void DistrugeLG(ALG);  
size_t LungimegLG(ALG);   /* numarul de elemente din lista */
void Afisare(ALG aL, TF afiEL,FILE *fout);
void AfiChar(void * ae,FILE *fout);
void AfiVal(void * ae,FILE *fout);
    /* afiseaza elementele din lista, folosind o functie de tip TFA */        

#endif
