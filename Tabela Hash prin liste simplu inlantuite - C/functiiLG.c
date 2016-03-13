/* LUPASCU Andrei - 311 CB */
/*--- functii din laborator---*/
#include "tlg.h"
void AfiChar(void * ae,FILE *fout)
{
	web p = *(web*)ae;
	fprintf(fout,"[%s %s] ", p.key, p.value);
}
void AfiVal(void * ae,FILE *fout)
{
	web p = *(web*)ae;
	fprintf(fout,"%s ",p.value);
}
int InsLG(ALG aL, void* ae, size_t d)
{
	
  	TLG p = *aL,aux = calloc(sizeof(TCelulaG),1);
  	if(!aux) return 0;
  	aux->info = calloc(d,1);
  	if (!aux->info)          
  	{ free(aux); return 0;}
  	memcpy(aux->info, ae, d);
	if(*aL == NULL)
	{
		*aL = aux;
		return 0;
	}
	if(strcmp((*(web*) aux->info).key ,(*(web*) p->info).key ) < 0)
	{
		aux->urm  = p ;
		*aL = aux;
		return 1;
	}
	while(p != NULL)	//inserare ordonata in caz de coliziune
	{
		
		if((p-> urm == NULL )|| (strcmp((*(web*) aux->info).key ,(*(web*) p->info).key ) > 0 &&
		strcmp((*(web*) aux->info).key ,(*(web*) p->urm->info).key ) < 0))
		{
			aux->urm = p->urm ;
			p->urm = aux;
			return 1;
		}
		p=p->urm ;
	}
	//p->urm = aux; //inserare la sfarsit
  	return 1;
}

void DistrugeLG(ALG aL) /* eliminare celula si element */
{ 	TLG aux = *aL;     /* adresa celulei eliminate */
  	if (!aux) return; /* lista vida */
  	free(aux->info);  /* elib.spatiul ocupat de element*/
  	*aL = aux->urm;    /* deconecteaza celula din lista */
  	free(aux);   /* elibereaza spatiul ocupat de celula */
}

size_t LungimeLG(ALG a)      /* numarul de elemente din lista */
{ 	size_t lg = 0;
  	TLG p = *a;
  	for (; p != NULL; p = p->urm) lg++;  /* parcurge lista, numarand celulele */
 	 return lg;
}

void Afisare(ALG aL, TF afiEL,FILE *fout)
{ 
  	if(!*aL) { fprintf(fout,"VIDA\n"); return;}
  	for(; *aL; aL = &(*aL)->urm)
    		afiEL((*aL)->info,fout);
  	fprintf(fout,"\n");
}
