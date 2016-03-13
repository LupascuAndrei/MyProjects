/* LUPASCU Andrei - 311 CB */
1)explicarea subprogramelor:

int hash(char *string,int M) - intoarce valoarea (suma_ascii(string)) % H

void removeL(ALG a,char *key) - cauta cheia KEY in 'a' si elimina structura ce 				contine acea cheie din lista.

void put(ALG L,char *key, char *value,web punct ) - insereaza in lista L o structura noua in care structura->info primeste structura WEB cu valorile KEY si VALUE

InsLG(L,&punct,sizeof(web)) - in lista L,insereaza o structura noua cu valorile trimise prin parametrul &punct
			    - daca lista L nu este vida,atunci insereaza o structura noua a.i. lista L sa ramana sortata

void print(ALG L,int M,FILE *fout) - afiseaza in fisierul FOUT M liste de tip TLG din L

void AfiVal(void * ae,FILE *fout) - functie de afisare a string-ului VALUE (struct web) din lista->info

functiile -void DistrugeLG(ALG aL)- si -void Afisare(ALG aL, TF afiEL,FILE *fout)- sunt preluate din laboratorul cu liste generice

2) main() + explicarea metodei:
- initializez M liste de tip TLG 
- citesc fiecare linie intr-un buffer de 500 de caractere,pe care il separ apoi cu STRTOK intr-un *token (sau 2,pentru "put") alocate dinamic
- in functie de primul cuvant de pe linia citita,apelez unul dintre subprogramele explicate anterior cu parametrii ( lista , urmatoarele cuvinte citite pana la '\n')
- salvez toate string-urile intr-un vector "web artificiu[]" inainte sa le introduc in lista si eliberez la sfarsitul main-ului (aveam probleme cu valgrind daca eliberam memoria auxiliara dupa fiecare introducere)
- la sfarsitul main-ului,eliberez toata memoria alocata in main 

 
