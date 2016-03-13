/* LUPASCU Andrei - 311 CB */
/*--- functiiLG.c -- functii din laboratorul cu liste generice,adaptate pentru cozi si stive implemenetate prin liste generice-*/
#include "tlg.h"
void AfiVal(void * ae,FILE *fout)
{
	proces p = *(proces*)ae;
	fprintf(fout,"%d ",p.id);
}
int priority_cmp( void *a,void *b) //returneaza prioritate(a)<= prioritate(b)
{
	proces m = *(proces*)a;
	proces n = *(proces*)b;
	if(m.priority == n.priority)
		return m.pas > n.pas;
	return m.priority < n.priority ; 
}
proces scoate_coada(ALG aL) //returneaza informatia primului element din coada
{			 // inainte sa il elimine din coada
	proces p = *(proces*)(( *aL)->info);
	TLG aux = *aL;
	(*aL) = (*aL) ->urm;
	free(aux->info);
	free(aux);
	return p;
}
void inserare_coada(ALG aL,proces p) //inserare in coada priority queue
{	//aloc memorie,verific daca am alocat-o,copiez informatia in memoria alocata
	TLG aux = malloc(sizeof(TCelulaG));
	TLG L = *aL;	
	if(!aux) return ;
	aux->urm = NULL;
	aux->info = malloc ( sizeof(proces)); 
	if(!aux->info) 
	{
		free(aux->info);
		free(aux);
		return ;
	}
	memcpy(aux->info, &p , sizeof(proces));
	if(*aL == NULL  || priority_cmp(L->info,aux->info)) 
	//inserez la inceput de coada daca aL e vida sau daca valoarea noua e mai mica decat inceputul lui aL
	{	
		if(*aL) 
		{
			aux-> urm = (*aL);
		}
		*aL =aux;
		return;
	}
	while(L->urm && priority_cmp(aux->info,L->urm->info))
		 //caut pozitia unde trebuie sa inserez valoarea noua(daca nu am inserat-o la inceput)
		L=L->urm;	
	aux->urm = L->urm; //inserez noua celula
	L->urm = aux;
}
void adauga_stiva(ALG stiva, proces p) //adauga structura proces la inceputul stivei
{
	TLG aux = malloc(sizeof(TCelulaG));
	if(!aux) return;
	aux->urm = *stiva;
	aux->info = malloc(sizeof(proces));
	memcpy(aux->info, &p, sizeof(proces));
	*stiva = aux;
}
proces sterge_stiva(ALG stiva) //sterge primul element din stiva si returneaza informatia acestuia
{
	proces p = *(proces*) (*stiva)->info;
	TLG aux = *stiva;
	(*stiva) = (*stiva) ->urm;
	free(aux->info);
	free(aux);
	return p;
}
void sterge_id_din_coada(ALG aL, int id)
{
	TLG aux2;
	TLG aux ;
	aux = NULL;
	if(*aL == NULL)
		return;
	proces p = scoate_coada(aL);
	while( p.id != id ) 
	{
		//folosesc o coada auxiliara AUX pentru a elimina 
		//elementul cu id-ul "id" din coada principala
		inserare_coada(&aux,p);	
		if(*aL == NULL ) break;
		p= scoate_coada(aL);	
	}
	while(aux) 
	{
		// aux2 = auxiliar,pentru eliberarea memoriei
		//reconstruiesc coada principala
		aux2= aux;
		p = *(proces*) (aux)->info;
		aux = aux->urm;
		free(aux2->info);
		free(aux2);
		inserare_coada(aL, p);		
	}
}
void muta_id_din_coada_in_eveniment(ALG aL, int id,ALG stiva) //aL = coada principala
{
	TLG aux2;
	TLG aux ;
	aux = NULL;
	if(*aL == NULL) return;
	proces p = scoate_coada(aL);
	while( p.id != id ) 
	{
		//folosesc o coada auxiliara AUX pentru a elimina 
		//elementul cu id-ul "id" din coada principala
		inserare_coada(&aux,p);
		if(*aL == NULL ) break;
		p= scoate_coada(aL);	
	}
	adauga_stiva(stiva,p);
	while(aux) 
	{
		// aux2 = auxiliar,pentru eliberarea memoriei
		//reconstruiesc coada principala
		aux2= aux;
		p = *(proces*) (aux)->info;
		aux = aux->urm;
		free(aux2->info);
		free(aux2);
		inserare_coada(aL, p);		
	}
}
void distruge_stiva_si_adauga_in_coada(ALG coada, ALG stiva)
{
	proces p;
	while(*stiva)
	{
		p = sterge_stiva(stiva);
		inserare_coada(coada, p);
	}

}
void Afisare(ALG aL, TF afiEL,FILE *fout)
{ 
  if(!*aL) { fprintf(fout,"\n"); return;}
  for(; *aL; aL = &(*aL)->urm)
    afiEL((*aL)->info,fout);
  fprintf(fout,"\n");
}
