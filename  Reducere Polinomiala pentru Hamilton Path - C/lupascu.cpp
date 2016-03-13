// LUPASCU ANDREI 321 CB
#include <stdlib.h>
#include <stdio.h>
using namespace std;
FILE *f = fopen("test.in","r");
FILE *g = fopen("test.out","w");
int n,m;
bool muchii[4000][4000];
inline int value(int i,int j )
{
    return (i - 1 ) * n + j;
}
int main()
{
    int i,j,k;
    fscanf(f,"%d %d\n", &n,&m);
    i=n;
    //clauzele 2,4
    do // complexitate n^3
    {
        j = i - 1;
        do
        {
            k=n;
            do
            {
                fprintf(g,"(~x%dV~x%d)^(~x%dV~x%d)^", value(i,k), value(j,k), value(k,i), value(k,j));
            }
            while(--k);
        }
        while(--j);
    }
    while(--i>1);
    do
    {
        int x,y;
        fscanf(f,"%d %d\n",&x,&y);
        muchii[x][y] = muchii[y][x] = true;
    }
    while(--m);
    i=n;
    //clauza 5
    do // complexitate n^3
    {
        j = i - 1;
        do
        {
            if(muchii[j][i]) continue;
            k=n-1;
            do
            {
                fprintf(g,"(~x%dV~x%d)^(~x%dV~x%d)^",value(k,i),value(k+1,j),value(k,j),value(k+1,i));
            }
            while(--k);
        }
        while(--j);
    }
    while(--i>1);
    i=n;
    //  clauzele 1,3
    do // complexitate n^2
    {
        fprintf(g,"(");
        j=1;
        do
        {
            fprintf(g,"x%d", value(i,j));
            if(j<n)
                fprintf(g,"V");
        }
        while(j++<n);
        fprintf(g,")^");
    }
    while(--i);
    i=n ;
    do // complexitate n^2
    {
        fprintf(g,"(");
        j=1;
        do
        {
            fprintf(g,"x%d", value(j,i));
            if(j<n)
                fprintf(g,"V");
        }
        while(j++<n);
        fprintf(g,")");
        if(i>1) fprintf(g,"^");
    }
     while(--i);
}
