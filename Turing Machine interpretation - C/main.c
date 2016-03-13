/* LUPASCU Andrei 321 CB*/
#include "header.h"
char * rezolva_turing(char * w, int s,int sf, Stare *stari);
int main(int argc, char *argv[])
{
	FILE *fin,*fout;
	fin = fopen ("date.in" , "r");
	fout= fopen("date.out" , "w");
	char *w;
	int s,sf,i,j;
		//aloc memorie pentru banda
	w = malloc(105 * sizeof(char));
		//citesc banda
	if( fgets ( w , 103 , fin) == NULL)
	{
		EROARE;
		return 0;
	}
		//citesc s,sf
	fscanf(fin,"%d%d\n",&s,&sf);
		//aloc memorie si citesc starile
	Stare *stari ;
	stari = malloc( (s - sf ) * sizeof(Stare));
	for(i = 0 ; i < s-sf ; i ++) 
	{
		for(j = 0 ; j < 3 ; j ++)
		{
			fscanf(fin,"%d",&(stari[i].urmator[j]));
			if(stari[i].urmator[j] == -1)
				fscanf(fin,"\n");
			else
				fscanf(fin," %c %c\n",&(stari[i].caracter[j]),&(stari[i].deplasare[j]));
		}
	}
	fprintf(fout,"%s",rezolva_turing(w,s,sf,stari));
	free(w);
	free(stari);
	return 0;
}
char * rezolva_turing(char * w, int s,int sf, Stare *stari)
{
	//rezolvare iterativa
	int cursor = 1, stare_curenta = 0,indice;
	while ( stare_curenta < s - sf )  // cat timp nu sunt pe o stare finala
	{
		//if(cursor < 0 ) return w ;
		indice = 0;
		if(w[cursor] == '1') indice = 1;
		if(w[cursor] == '#') indice = 2;
		w[cursor] = stari[stare_curenta].caracter[indice];
		if(stari[stare_curenta].deplasare[indice] == 'R') cursor++;
		if(stari[stare_curenta].deplasare[indice] == 'L') cursor--;
		stare_curenta = stari[stare_curenta].urmator[indice];
		if(stare_curenta >= s ) return "Eroare!"; //tranzitie nedifinita
		if(stare_curenta == -1) return "Eroare!";
		
	}
	return w;
}

