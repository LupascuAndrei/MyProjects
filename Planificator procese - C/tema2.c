/*LUPASCU Andrei - 311 CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tlg.h"

int main(int argc, char *argv[])
{
	int i,pas=1,length=500,M;
	int X,Y;
	char buffer[500],*token,*token2; //pentru citire parsata
	FILE * fin ,*fout;
	fin = fopen ( argv[1] , "r");
	fout= fopen( argv[2], "w");
	fscanf(fin,"%d\n",&M);
	TLG coada = NULL;
	ALG stiva = calloc( sizeof(TLG),M+1);
	if(!stiva) return 0; //nu s-a alocat
	proces p;
	while (fgets(buffer,length,fin)!= NULL)  //citire parsata
	{
		//printf("%s",buffer);
		if(buffer[0] == '\n') break;
		token = strtok (buffer," ");
		//if(token==NULL) break;
		//printf("%s",token);
		fprintf(fout,"%d\n",pas++);
		if(strcmp(token,"start")==0) //transformarea sirului char in valori intregi 
		{
			token = strtok (NULL," \n");
			X= atoi(token);
			token2 = strtok(NULL, " \n");
			Y= atoi(token2);
			p.id = X;
			p.priority = Y;
			p.pas = pas;
			inserare_coada(&coada,p);
			//printf("%d%d",X,Y);
		}
		if(strcmp(token,"wait")==0) //transformarea sirului char in valori intregi 
		{
			token = strtok (NULL," \n");
			X= atoi(token);
			token2 = strtok(NULL, " \n");
			Y= atoi(token2);
			muta_id_din_coada_in_eveniment(&coada,Y,&stiva[X]);
			//Afisare(stiva[X],AfiVal,fout);
			//printf("%d%d",X,Y);
		}
		if(strcmp(token,"end")==0) //transformarea sirului char in valori intregi 
		{
			token = strtok (NULL," \n");
			X= atoi(token);
			sterge_id_din_coada(&coada,X);
			//printf("%d",X);
		}
		if(strcmp(token,"event")==0) //transformarea sirului char in valori intregi 
		{
			token = strtok (NULL," \n");
			X= atoi(token);
			distruge_stiva_si_adauga_in_coada(&coada,&stiva[X]);
		}
		Afisare(&coada,AfiVal,fout);
		for(i = 0; i < M ; i ++ )
		{
			if(stiva[i] != NULL ) 		
			{
				fprintf(fout,"%d: ",i);
				Afisare(&stiva[i],AfiVal,fout);
			}
		}
		fprintf(fout,"\n");
	}
	for(i=0;i<M;i++)
	{
		free(stiva[i]);
	}
	//free(token);
	//free(token2);
	free(coada);
	free(stiva);
	fclose(fin);
	fclose(fout);
	return 0;
}
