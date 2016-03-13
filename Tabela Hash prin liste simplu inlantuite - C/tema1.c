/* LUPASCU Andrei - 311 CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tlg.h"

int hash(char *string,int M)
{
	/* functie hash = (suma ascii) % M */
	int val=0,i;
	for(i=0;i<strlen(string);i++)
		val += string[i];
	return val % M;
}
void removeL(ALG a,char *key)
{
	/* cauta cheia in lista si sterge casuta corespunzatoare cheii*/
	TLG p = *a,aux;
	if(!p) return;
	if( strcmp(key,(*(web*) p->info).key ) == 0 )
	{
		aux = *a;
		*a = (*a) -> urm;
		free(aux->info);
		free(aux);
		return;
	}
	for (; p->urm != NULL; p = p->urm) 
		if( strcmp(key,(*(web*) (p->urm)->info).key ) == 0 )
		{
			aux=p->urm;
			p->urm = p->urm->urm;
			free(aux->info);
			free(aux);
			return;
		}
}
void put(ALG L,char *key, char *value,web punct) 
{
	/* adauga structura WEB in lista prin functia InsLG*/
	strcpy(punct.key,key);
	strcpy(punct.value,value);
	InsLG(L,&punct,sizeof(web));
}
int find(TLG p, char *key)
{
	/* cauta sirul KEY in lista P  ( p->info.key) */
  	for (; p != NULL; p = p->urm) 
		if( strcmp(key,(*(web*) p->info).key ) == 0 )
			return 1;
	return 0;

}
void get(TLG p, char *key,FILE *fout) 
{
	/* cauta cheia KEY si afiseaza valoarea corespunzatoare
		sau NULL daca KEY nu exista in lista  */
  	for (; p != NULL; p = p->urm) 
		if( strcmp(key,(*(web*) p->info).key ) == 0 )
		{
			fprintf(fout,"%s\n",(*(web*) p->info).value);
			return;
		}
	fprintf(fout,"NULL\n");
}
void print(ALG L,int M,FILE *fout)
{
	int i;
	for(i=0;i<M;i++)
	{
		if(!L[i]) continue;
		fprintf(fout,"%d: ",i);
		Afisare(&L[i], AfiVal,fout);
	}
}
int main(int argc, char *argv[])
{
	
	int i=0,pas=0,val=0,length=500,M = atoi(argv[1]);
	char  *token2 = NULL, * token = NULL;
	char buffer[500];
	web artificiu[500];
	ALG liste = calloc( sizeof(TLG),M);
	if(!liste) return 0;
	FILE * fin ,*fout;
	fin = fopen ( argv[2] , "r");
	fout= fopen( argv[3], "w");
	while (fgets(buffer,length,fin)!= NULL) 
	{
		token = strtok(buffer," \n");
			/*separa linia citita in buffer prin STRTOK si
			apeleaza functia corespunzatoare datelor citite
 			de pe linia curenta (remove,get,find...)*/
		if(token == NULL) return 0;
		if(strcmp(token,"find")==0)
		{
			token2 = strtok ( NULL," \n");
			/* caut string-ul TOKEN2 in lista ce corespunde
			functiei hash:	*/
			if(find(liste[hash(token2,M)],token2))
				fprintf(fout,"True\n");
			else
				fprintf(fout,"False\n");
			continue;
		}
		if(strcmp(token,"print")==0)
		{
			print(liste,M,fout);
			continue;
		}
		if(strcmp(token,"remove")==0)
		{
			token2 = strtok ( NULL," \n");
			removeL(&liste[hash(token2,M)],token2);
			continue;
		}
		if(strcmp(token,"put")==0)
		{
			token = strtok ( NULL," \n");
			token2 = strtok ( NULL,"\n ");
			if(find(liste[hash(token,M)],token)==0)
			{
				/*salvez datele dinamic in artificiu[] pentru a le elibera ulterior intr-un singur for() */
				artificiu[pas].key = calloc(strlen(token)+1,1); 
				artificiu[pas].value =calloc(strlen(token2)+1,1);
				put(&liste[hash(token,M)],token,token2,artificiu[pas]);
				pas++;
			}
			continue;
		}
		if(strcmp(token,"print_bucket")==0)
		{
			token2 = strtok ( NULL," \n");
			val = atoi(token2);
			if(val>=M)
			{
				continue;
			}
			Afisare(&liste[val], AfiVal,fout);
			continue;
		}
		if(strcmp(token,"get")==0)
		{
			token2 = strtok ( NULL," \n");
			get(liste[hash(token2,M)],token2,fout);
			continue;
		}
       	}
	//free(token);
	//free(token2);
	for(i=0;i<M;i++) //elibereaza memoria ocupata de liste
		while(liste[i])
		{
			DistrugeLG(&liste[i]);
		//	free(liste[i]);
		}
	for(i=0;i<pas;i++)
	{
		free(artificiu[i].key);
		free(artificiu[i].value);
	}

	free(liste);
	fclose(fin);
	fclose(fout);
	return 0;
}
