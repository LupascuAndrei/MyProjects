// LUPASCU Andrei - 311 CB
#include "tarb.h"

int main (int argc, char *argv[]){ 
	int i,n,m,*aux1,*aux2,*aux3,*aux4,*aux5; //auxI -> valori auxiliare pentru citire
	FILE *fin,*fout;
	fin = fopen( argv[2], "r");
	//aux 1-3 = ecuatii pentru drepte, aux 4-5 = coordonatele celor M puncte
	fscanf(fin,"%d",&n);
	fscanf(fin,"\n");
	aux1= calloc(n+1,sizeof(int));
	aux2= calloc(n+1,sizeof(int));
	aux3= calloc(n+1,sizeof(int));
	for(i=1;i<=n;i++)
	{
		fscanf(fin,"%d%d%d",&aux1[i],&aux2[i],&aux3[i]); //citesc ecuatiile a N drepte
		fscanf(fin,"\n");
	}
	fscanf(fin,"%d",&m);
	fscanf(fin,"\n");
	aux4= calloc(m+1,sizeof(int));
	aux5= calloc(m+1,sizeof(int));
	for(i=1;i<=m;i++)
	{
		fscanf(fin,"%d%d",&aux4[i],&aux5[i]); //citesc coordonatele a M puncte
		fscanf(fin,"\n");
	}
	TArb arbore = NULL;
	if( atoi(argv[1]) == 1 ) //cerinta 1
	{
		arbore =calloc(1,sizeof(TNod)); //creez radacina
		int i,s,d;
		fscanf(fin,"%d%d%d",&i,&s,&d);	
		fscanf(fin,"\n");
		arbore->info.mod = 'd';//nodul este de tip dreapta si salvez ecuatia dreptei in el
		arbore->info.d_a = aux1[i+1]; //am salvat dreptele incepand cu indicele 1
		arbore->info.d_b = aux2[i+1];
		arbore->info.d_c = aux3[i+1];
		if(s)
		{
			TArb aux_s = calloc(1,sizeof(TNod));
			arbore->st = aux_s;
			cerinta_1(arbore->st,aux1,aux2,aux3,fin); // DFS pe subarborele stang
		}
		if(d)
		{
			TArb aux_d = calloc(1,sizeof(TNod));
			arbore->dr = aux_d;
			cerinta_1(arbore->dr,aux1,aux2,aux3,fin); //DFS pe subarborele drept
		}
	}
	if( atoi(argv[1]) == 2 )
	{
		arbore =calloc(1,sizeof(TNod)); //creez radacina
		arbore->info.mod = 'd';//nodul este de tip dreapta si salvez ecuatia dreptei in el
		arbore->info.d_a = aux1[1]; //radacina este prima dreapta citita
		arbore->info.d_b = aux2[1];
		arbore->info.d_c = aux3[1];
		for(i = 2 ; i <= n ; i ++ )
		{
			adaug_dreapta(aux1[i],aux2[i],aux3[i],arbore); 
			//adaug fiecare ecuatie de dreapta in arbore,in ordinea citita
		}
	}
	for(i = 1 ; i <= m ; i ++ )
	{
		adaug_punct(arbore,aux4[i],aux5[i],i-1); //adaug M frunze in arbore (puncte)
	}
	fout = fopen( argv[3],"w");
	postordine(arbore,fout);
	int q,x,y;
	fscanf(fin,"%d",&q);
	for(i = 1;i <= q ; i ++ )
	{
		fscanf(fin,"%d%d",&x,&y);
		fscanf(fin,"\n");
		fprintf(fout,"\n%d",cauta(arbore,x,y));
		//citesc Q puncte si afisez partitionarea acestora in arbore
	}
	fprintf(fout,"\n");
	DistrArb (&arbore);
	free(aux1);
	free(aux2);
	free(aux3);
	free(aux4);
	free(aux5);
	return 0;
}
void postordine(TArb a,FILE *fout)
{
	//afisez arborele in postordine
	if(a->info.mod == 'p')
	{
		fprintf(fout,"((%d,%d)-%d)",a->info.p_x,a->info.p_y,a->info.p_p);
		return;
	}
	if(a->info.mod == 'd')
	{
		if(!a->st)
			fprintf(fout,"null");
		else
			postordine(a->st,fout);
		if(!a->dr)
			fprintf(fout,"null");
		else
			postordine(a->dr,fout);
		fprintf(fout,"(%d,%d,%d)",a->info.d_a,a->info.d_b,a->info.d_c);
	}
}
void cerinta_1(TArb arbore,int *aux1,int *aux2,int *aux3,FILE *fin)
{
	int i,s,d;
	fscanf(fin,"%d%d%d",&i,&s,&d);	
	fscanf(fin,"\n");
	arbore->info.mod = 'd';//nodul este de tip dreapta si salvez ecuatia dreptei in el
	arbore->info.d_a = aux1[i+1]; //am salvat dreptele incepand cu indicele 1
	arbore->info.d_b = aux2[i+1];
	arbore->info.d_c = aux3[i+1];
	if(s)
	{
		TArb aux_s = calloc(1,sizeof(TNod));
		arbore->st = aux_s;
		cerinta_1(arbore->st,aux1,aux2,aux3,fin); // DFS pe subarborele stang
	}
	if(d)
	{
		TArb aux_d = calloc(1,sizeof(TNod));
		arbore->dr = aux_d;
		cerinta_1(arbore->dr,aux1,aux2,aux3,fin); //DFS pe subarborele drept
	}
}
int nu_sunt_paralele(TArb arb,int a,int b)
{
	return (float) arb->info.d_a / a != (float) arb->info.d_b / b;
}
void adaug_dreapta(int a,int b,int c,TArb arbore){
	if(nu_sunt_paralele(arbore,a,b))//daca dreptele nu sunt paralele
	{	//parcurg ambii subarbori 
		if(arbore-> dr == NULL)
		{	
			TArb aux1 = calloc(1,sizeof(TNod)); //daca am atins o frunza
			if(aux1==NULL) return; 	//creez un nod nou si il leg de arbore,iar apoi ies din recursivitate
			arbore->dr = aux1;
			aux1->info.mod = 'd'; 
			aux1->info.d_a = a;
			aux1->info.d_b = b;
			aux1->info.d_c = c;
		}
		else	
			adaug_dreapta(a,b,c,arbore->dr);
		if(arbore->st == NULL)
		{	
			TArb aux2 = calloc(1,sizeof(TNod));
			if(aux2==NULL) return;
			arbore->st = aux2;
			aux2->info.mod = 'd'; //tip dreapta
			aux2->info.d_a = a;
			aux2->info.d_b = b;
			aux2->info.d_c = c;
		}
			
		else	
			adaug_dreapta(a,b,c,arbore->st);
		return;
	}
	if(arbore->info.d_c > c) //subarborele drept
	{
		if(arbore-> dr){
			adaug_dreapta(a,b,c,arbore->dr);
			return;
		}
		else	{	
			TArb aux1 = calloc(1,sizeof(TNod));
			if(aux1==NULL) return; 
			arbore->dr = aux1;
			aux1->info.mod = 'd';
			aux1->info.d_a = a;
			aux1->info.d_b = b;
			aux1->info.d_c = c;
			return;
		}
	}
	else
	{
		if(arbore->st){
			adaug_dreapta(a,b,c,arbore->st);
			return;
		}
		else	{	
			TArb aux1 = calloc(1,sizeof(TNod));
			if(aux1==NULL) return; 
			arbore->st = aux1;
			aux1->info.mod = 'd';
			aux1->info.d_a = a;
			aux1->info.d_b = b;
			aux1->info.d_c = c;
			return;
		}
	}
}
void adaug_punct(TArb arbore,int x,int y,int i)
{
	int directie = arbore->info.d_a * x + arbore->info.d_b * y + arbore->info.d_c < 0; // compar ax+by+c cu 0
	if(directie ) // ecuatia ax+by+c < 0 
	{
		if(!arbore-> st ) 
		{
			TArb aux = calloc(1,sizeof(TNod));
			if(aux==NULL) return;
			arbore->st = aux;
			aux->info.mod = 'p'; //nodul este de tip punct	
			aux->info.p_x = x;
			aux->info.p_y = y;
			aux->info.p_p = i;
			return;
		}	
		adaug_punct(arbore->st,x,y,i);
	}
	else
	{
		if(!arbore-> dr ) 
		{
			TArb aux = calloc(1,sizeof(TNod));
			if(aux==NULL) return;
			arbore->dr = aux;
			aux->info.mod = 'p'; //nodul este de tip punct	
			aux->info.p_x = x;
			aux->info.p_y = y;
			aux->info.p_p = i;
			return;
		}	
		adaug_punct(arbore->dr,x,y,i);
	}
}
int cauta(TArb arbore,int x,int y)//cauta partitionarea punctului (X,Y) in arbrore si o returneaza
{
	if(arbore->info.mod== 'p')
	{
		return arbore->info.p_p;
	}
	int directie = arbore->info.d_a * x + arbore->info.d_b * y + arbore->info.d_c < 0; // compar ax+by+c cu 0
	if(directie ) 
		return cauta(arbore->st,x,y);
	else
		return cauta(arbore->dr,x,y);
}
void distruge(TArb r) 	/* functie auxiliara - distruge toate nodurile */
{ if (!r) return;
  distruge (r->st);     /* distruge subarborele stang */
  distruge (r->dr);     /* distruge subarborele drept */
  free (r);             /* distruge nodul radacina */
}

void DistrArb(TArb *a) /* distruge toate nodurile arborelui de la adresa a */
{ if (!(*a)) return;       /* arbore deja vid */
  distruge (*a);           /* distruge toate nodurile */
  *a = NULL;               /* arborele este vid */
}
