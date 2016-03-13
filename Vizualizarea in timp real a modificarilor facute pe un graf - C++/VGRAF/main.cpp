#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif
#include <fstream>
#include <vector>
#define NMAX 51
#define pb push_back
#include <algorithm>
#include <stdlib.h>
#define PTS 789
#define random_color rand()%4280000000
#define yellow 0x0000FF00
#define blue 0x00FF0000
#include <iostream>
using namespace std;
ifstream fin("data.in");
ofstream fout("data.out");
ofstream cdout("coord.out");
ifstream cdin("coord.in");
vector <int> v[NMAX];
int n,m;
int k1=1,k3=1,k2=1,p1=2; // pentru change_graph()
struct coordonate{
    int a,b;
};
coordonate cd[PTS]; // din input
coordonate grafcd[PTS]; // noduri
void read();
void tipar();
void graf_init();
void draw_graph(SDL_Surface *surface);
void change_graph(SDL_Surface *surface);
void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void linie(SDL_Surface *surface,int x1,int y1,int const x2,int const y2,Uint32 pixel);
/*
DATA.in : se citeste graful,sub formatul
n m ; (noduri,muchii)
x y   (m linii cu 2 elemente,cu semnificatia ca e muchie intre x si y)
x y
x y
...
x y*/

/*/ COORD.in FORMATION
struct meebo
{
    int a, b;
};
bool cmp(meebo z,meebo x)
{
    if(z.a==x.a)
        return z.b>x.b;
    return z.a>x.a;
}
bool bmp(meebo z,meebo x)
{
    if(z.a==x.a)
        return z.b<x.b;
    return z.a<x.a;
}
meebo met[900];
meebo bet[900];
bool check[300][300];
void aux()
{
    int o,p,k=1,b=1;
    for(int i=1;i<=900;i++)
    {
        cdin>>o>>p;
        if(p>160)
        {
            bet[b].a=o;
            bet[b].b=p;
            b++;
        }
       // if(check[o][p]) continue;
       // check[o][p]=true;
        else
        {
            met[k].a=o;
            met[k].b=p;
            k++;
        }
    }
    sort(met+1,met+k,cmp);
    sort(bet+1,bet+b,bmp);
    for(int i=1;i<=k;i++)
        cdout<<met[i].a<<" "<<met[i].b<<"\n";
    cdout<<"********\n";
    for(int i=1;i<=b;i++)
        cdout<<bet[i].a<<" "<<bet[i].b<<"\n";
}
*/

/*SDL DRAW FUNCTIONS :
void Draw_Pixel(SDL_Surface *super,
                Sint16 x, Sint16 y,
                Uint32 color);
void Draw_Line(SDL_Surface *super,
               Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2,
               Uint32 color);*/
void readcd();
void cerc(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel);
int main ( int argc, char** argv )
{
    //the next 4 lines are for your first impression only,feel free to delete them after.
    cout<<"VGRAF; insert: \n'1' to display written graph in 'data.in'\n'2' to visualise dinamically changed graph written in 'data.in'"
        <<"\n insert anything else to not understand what`s happening\n";
    int mode;
    cin>>mode;
    int pas=1;
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    atexit(SDL_Quit);
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16,SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }
   // aux();
    read();
    readcd();
    graf_init();
    while(1)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                //tipar();
                return 0;
            }
        }
        SDL_LockSurface(screen);
        cerc(screen, 160, 160,140, 0xffffffff);
        /*  DEBUG
        set_pixel(screen,cd[pas].a,cd[pas].b,yellow);
        pas++;
        if(pas>PTS) pas=1;
        linie(screen, cd[5].a,cd[5].b,cd[705].a,cd[705].b,yellow);
        set_pixel(screen,grafcd[pas].a,grafcd[pas].b,random_color);
        pas++;
        if(pas>n) pas=1;*/
        if(mode==2)
            change_graph(screen);
        draw_graph(screen);
        SDL_FreeSurface(screen);
        SDL_Flip(screen);
    }
}
void read()
{
    int a,b;
    fin>>n>>m;
    for(int i=0;i<m;i++)
    {
        fin>>a>>b;
        if(a<=b) // graf neorientat
            v[a].pb(b);
        else
            v[b].pb(a);
    }
}
void tipar()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<v[i].size();j++)
            fout<<v[i][j]<<" ";
        fout<<"\n";
    }
}
void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
    *(Uint32 *)target_pixel = pixel;
}
void cerc(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel)
{
    double error = (double)-radius;
    double x = (double)radius -0.5;
    double y = (double)0.5;
    double cx = n_cx - 0.5;
    double cy = n_cy - 0.5;

    while (x >= y)
    {
        set_pixel(surface, (int)(cx + x), (int)(cy + y), pixel);
        set_pixel(surface, (int)(cx + y), (int)(cy + x), pixel);

        if (x != 0)
        {
            set_pixel(surface, (int)(cx - x), (int)(cy + y), pixel);
            set_pixel(surface, (int)(cx + y), (int)(cy - x), pixel);
        }

        if (y != 0)
        {
            set_pixel(surface, (int)(cx + x), (int)(cy - y), pixel);
            set_pixel(surface, (int)(cx - y), (int)(cy + x), pixel);
        }

        if (x != 0 && y != 0)
        {
            set_pixel(surface, (int)(cx - x), (int)(cy - y), pixel);
            set_pixel(surface, (int)(cx - y), (int)(cy - x), pixel);
        }

        error += y;
        ++y;
        error += y;

        if (error >= 0)
        {
            --x;
            error -= x;
            error -= x;
        }
    }
}
void linie(SDL_Surface *surface,int x1,int y1,int const x2,int const y2,Uint32 pixel)
{
    //clasicul bersenham
    int delta_x(x2 - x1);
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;

    int delta_y(y2 - y1);
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;
    set_pixel(surface,x1,y1,pixel);
    if (delta_x >= delta_y)
    {
        int error(delta_y - (delta_x >> 1));

        while (x1 != x2)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }

            error += delta_y;
            x1 += ix;
            set_pixel(surface,x1,y1,pixel);
        }
    }
    else
    {
        int error(delta_x - (delta_y >> 1));

        while (y1 != y2)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }

            error += delta_x;
            y1 += iy;
            set_pixel(surface,x1,y1,pixel);
        }
    }
}
void readcd()
{
    for(int i=1;i<PTS;i++)
        cdin>>cd[i].a>>cd[i].b;
}
void graf_init()
{
    int pas = PTS/n - 1;
    int step=pas;
    grafcd[1].a=cd[1].a;
    grafcd[1].b=cd[1].b;
    for(int i=2;i<=n;i++)
    {
        grafcd[i].a=cd[step].a;
        grafcd[i].b=cd[step].b;
        step+=pas;
    }
    for(int i=1;i<=n;i++)
        fout<<grafcd[i].a<<" "<<grafcd[i].b<<"\n";
}
void draw_graph(SDL_Surface *surface)
{
    for(int i=1;i<=n;i++)
        for(int j=0;j<v[i].size();j++)
            linie(surface,grafcd[i].a,grafcd[i].b,grafcd[v[i][j]].a,grafcd[v[i][j]].b,yellow);
}
void change_graph(SDL_Surface *surface)
{
    //STILL UNDER TESTING
    //k1,k2si p1 cauta prin noduri,k3 e doar pentru a schimba intre "taie muchie" si "adauga muchie"
    if(k3==1)
    {
        k2=rand()%n+1;
        k3=0;
        while(v[k2].empty())
        {
            k2++;
            if(k2>n) k2=1;
        }
       // v[k2][0] = v[k2][v[k2].size() - 1];
        linie(surface,grafcd[k2].a,grafcd[k2].b,grafcd[v[k2].back()].a,grafcd[v[k2].back()].b,blue);
        v[k2].pop_back();
    }
    else
    {
        k3=1;
        k1=rand()%n+1;
        p1=rand()%(n-k1+1)  + k1;
        v[k1].pb(p1);
    }
    /*
    vector <int> vecc;
    for(int i=1;i<=n;i++)
    {
        if(!v[i].empty()) vecc.pb(i);
    }
    if(vecc.empty()) return;
    nod=vecc[rand() % vecc.size()] ;
    v[nod][0]=v[nod][v[nod].size() -1];
    v[nod].pop_back();*/
}
