#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
ifstream fin("ins");
ofstream fout("out");
#define NMAX 10005
//plm am scris drone in unele locuri si drona in altele
#define drone_l drona_l
#define drone_c drona_c
int pas =1 ;
int stop = 0 ;
int sol ;
int drona_l[NMAX];
int drona_c[NMAX];
int cost_drona[NMAX];
int n,m,drone,deadline,maxload,produse,warehouse,comenzi;
int solve[NMAX], cost[NMAX];
int vprod[NMAX];
struct house
{
    int l,c ;
    int prodh[ NMAX] ;
    int pas;
};
struct command
{
    int l,c;
    int cprod[NMAX];
};
int comanda_curenta ;
command vcom[NMAX];
house  vhouse[NMAX];
void test2()
{


}

int drum(int i1,int j1,int i2,int j2)
{

    double x = sqrt ( ( i1-i2) * (i1-i2) + (j1-j2) * (j1-j2) );
    if( x == (double)((int )x)  )
        return (int) x+1;
    else
        return (int) x + 2 ;
}
void solve_comanda()
{
    int min_i,min_val,mi,mval;
    int cate_iau = 0, cate_pot_lua, cate_tre_sa_iau ;
    command curent = vcom[comanda_curenta];
    for(int i = 0 ; i < produse  ; i ++ )
    {
        if(stop)
            return ;
        int cicleaza_la_sfarsit  = 0 ;
        min_val = 99999999;

        if(curent.cprod[i] == 0 )
            continue;
        for(int j = 0 ; j < warehouse ; j ++ )
        {
           if( vhouse[j].prodh[i] )
           {
                int aux;
                if(aux = drum ( curent.l,curent.c, vhouse[j].l,vhouse[j].c)< min_val  )
                {
                    min_val = aux;
                    min_i = j ;
                }
           }
        }
        //cout<<maxload/vprod[i]<<endl;
        int cate_are = vhouse[min_i].prodh[i];
        //cout<<cate_are;
        cate_pot_lua =  maxload / vprod[i] ;
        if(cate_pot_lua > cate_are) cate_pot_lua = cate_are;
        cate_tre_sa_iau = curent.cprod[i];
        if(cate_tre_sa_iau <= cate_pot_lua ) cate_iau = cate_tre_sa_iau;
        else
        {
            cate_iau = cate_pot_lua;
            cicleaza_la_sfarsit = 1;
        }
        mval = 99999999;
        int aux;
        int aux3;
        for(int j = 0 ; j < drone ; j ++ )
        {
            if((aux = drum ( drone_l[j], drone_c[j], vhouse[min_i].l, vhouse[min_i].c)) + cost_drona[j] < mval)
            {
                if( cost_drona[j] + min_val + aux > deadline  ) continue;
                mi = j;
                mval = aux ;
            }
        }
        if(mval == 99999999)
        {
            stop = 1 ;
            return;
        }
        if( i == 0 && comanda_curenta == 0 )
        {
            cout << curent.cprod[i];
        }
        cost_drona[mi] += min_val + aux;
        drona_l[mi] = curent.l;
        drona_c[mi] = curent.c;
        vhouse[min_i].prodh[i] -= cate_iau;
        curent.cprod[i] -= cate_iau;


        fout<<mi<<" L "<<min_i<<" "<<i<<" "<<cate_iau<<"\n"; //nr de produse
        fout<<mi<<" D "<<comanda_curenta<<" "<<i<<" "<<cate_iau<<"\n";
        if(cicleaza_la_sfarsit)
        {
            i--;
        }
    }
}
void test()
{
    fout<<n<<" "<<m<<" "<<drone<<" "<<deadline<<" "<<maxload<<" "<<produse<<" \n";
    for(int i = 0 ; i < produse ; i ++ )
        fout<<vprod[i]<<" ";
    fout<<warehouse<<" \n";
    for(int i = 0 ; i < warehouse ; i ++ )
    {
        fout<<vhouse[i].l<<" "<<vhouse[i].c<<" \n";
        for(int j = 0 ; j < produse ; j ++ )
            fout<<vhouse[i].prodh[j]<<" ";
    }
    fout<<"!!! "<<comenzi<<"\n";

}
int cauta_in_warehouse(int produs_i,int cantitate,int l_com,int c_com)
{
    pas ++ ;
    if(cantitate == 0 ) return 0;
    int sol = 0 , cant_gasita= 0;
    int v[NMAX];
    int min_i, min_drum ;
    while( cant_gasita < cantitate )
    {
        min_i = -1;
        min_drum = 999999999;
        for(int i = 0 ; i < warehouse ; i ++ )
        {
            if(vhouse[i].pas == pas ) continue;
            if(vhouse[i].prodh[produs_i] )
            {
                if( min_drum > drum ( l_com , c_com , vhouse[i].l, vhouse[i]. c ) )
                {

                    min_drum =  drum ( l_com , c_com , vhouse[i].l, vhouse[i]. c );
                    min_i = i ;
                }
            }
        }
        cant_gasita +=  vhouse[min_i].prodh[produs_i];
        vhouse[min_i].pas = pas ;
        if( cant_gasita <= cantitate )
            sol += min_drum * ( vhouse[min_i].prodh[produs_i] * vprod[produs_i] ) / maxload;
        else
        {
            double val = ( vhouse[min_i].prodh[produs_i] + cantitate - cant_gasita) * vprod[produs_i] / maxload;
            if( (double)val == (int) val )
            sol += min_drum * (1 +( vhouse[min_i].prodh[produs_i] + cantitate - cant_gasita) * vprod[produs_i] ) / maxload;
                else
            sol += min_drum * (1 +(( vhouse[min_i].prodh[produs_i] + cantitate - cant_gasita) * vprod[produs_i] ) / maxload  );
        }
    }
    return sol ;
}

void prestare()
{
  //  fout<<"\n \n COSTURI : \n";
    int check = 1 ;
    for(int i = 0 ; i < comenzi ; i ++ )
    {
        cost[i] = 0 ;
        if( solve[i] ) continue ;
        check = 0 ;
        for(int j = 0; j < produse ; j ++ )
        {
            cost[i] += cauta_in_warehouse(j,vcom[i].cprod[j],vcom[i].l,vcom[i].c);

        }
       // fout<<cost[i]<<" ";
    }
    if(check )
    {
        stop = 1 ;
        return ;
    }
    int min_i,min_val=9999999;
    for(int i = 0 ; i < comenzi ; i ++)
    {
        if( solve[i] ) continue ;
        if(min_val > cost[i] )
        {
            min_val = cost[i];
            min_i = i ;
        }
    }
    solve[min_i] = 1 ;
    comanda_curenta = min_i;
}

int main()
{
    fin>>n>>m>>drone>>deadline>>maxload>>produse;
    deadline = deadline /6;
    for(int i = 0 ; i < produse ; i ++ )
        fin>>vprod[i];
    fin>>warehouse;
    for(int i = 0 ; i < warehouse ; i ++ )
    {
        fin>>vhouse[i].l>>vhouse[i].c;
        for(int j = 0 ; j < produse ; j ++ )
            fin >> vhouse[i].prodh[j];
    }
    fin>>comenzi;
    for(int i = 0 ; i < comenzi ; i ++ )
    {
        fin>>vcom[i].l>>vcom[i].c;
        int aux;
        fin>>aux;
        for(int j = 0 ; j < aux ; j ++)
        {

            int aux2;
            fin>>aux2;
            vcom[i].cprod[aux2]++;
        }

    }
    for(int i = 0 ; i < produse ; i ++)
    {
        drona_l[i] = vhouse[0].l;
        drona_c[i] = vhouse[0].c;
    }
    while(stop == 0 )
    {
        prestare();
        solve_comanda();
    }
    cout<<endl<<endl;
    for(int i = 0 ; i < drone ; i ++ )
        cout << cost_drona[i]<< endl;
//    cout<<drona[0];
}

