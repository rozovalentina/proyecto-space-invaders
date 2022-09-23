#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

#define TECLA_DER 77
#define TECLA_IZQ 75
#define EXIT 101
#define DISPARA 32
#define RAYCH 216
#define ESCUADRON_VUELTA_A 1
#define ESCUADRON_VUELTA_B 0
// Impresion de los aliens
static char *squid[]={
"   ██   ",
"  ████  ",
" ██████ ",
"██ ██ ██",
"████████",
"  █  █  ",
" █ ██ █ ",
"█ █  █ █",
};
static char *squid2[]={
"   ██   ",
"  ████  ",
" ██████ ",
"██ ██ ██",
"████████",
" █ ██ █ ",
"█      █",
" █    █ ",
};
static char *crab[]={
"    ████    ",
" ██████████ ",
"████████████",
"███  ██  ███",
"████████████",
"   ██  ██   ",
"  ██ ██ ██  ",
"██        ██",
};
static char *crab2[]={
"    ████    ",
" ██████████ ",
"████████████",
"███  ██  ███",
"████████████",
"  ███  ███  ",
" ██  ██  ██ ",
"  ██    ██  ",
};
static char *octopus[]={
"  █     █  ",
"   █   █   ",
"  ███████  ",
" ██ ███ ██ ",
"███████████",
"█ ███████ █",
"█ █     █ █",
"   ██  ██  ",
};
static char *octopus2[]={
"  █     █  ",
"█  █   █  █",
"█ ███████ █",
"███ ███ ███",
"███████████",
"  ███████  ",
"   █   █   ",
"  █     █  ",
};
static char  escuadron[7][5];
char tecla = 0;
char teclaAnt = 0;
float velo = 0.08;
unsigned char rayoON=0;
unsigned char rayoEnemigoON[7];
unsigned char rayoDisparado[7];
int rayoPosX = 0;
int rayoPosY = 0;
int rayoEnemX[7];
int rayoEnemY[7];
int posJugador = 39;
int proxAtaque = 0;
int navequeAtaca = 0;
int score = 0;
int nivelDeDif = 0;
int NUEVOATAQUE = 0;
int GameOver=0;
int SigueJugando=1;

void inicializoNaves();
void naves ();
void escuadronVuelta (int, int);
void dibujoJugador(int);
void comprueboRayo();
void disparaEnemigo(int);
void disparo(int);
void rayo(int);
void leoTecla();
void inicializoArrays();
void muestroScore();
int menuPrincipal();
int menuFin();
int getrand();
void gotoxy(int, int);
void sleep (float);
typedef enum { STATE1, STATE2 } STATE_T;

  STATE_T state = STATE1;

int main()
{

 /* Aca van las variables*/

/******** Definition of New Types of Data *********/

  while( 1 ){ /* se crea un loup infinito hasta que el programa finalize*/
    switch(state){
      case STATE1:
           if (SigueJugando==1){/* se define el estado 1*/
         nivelDeDif=menuPrincipal();
 	 NUEVOATAQUE=nivelDeDif;
 	 inicializoNaves();
 	 inicializoArrays();
 	 GameOver=0;
 	 srand(time(0));
	 while (GameOver==0)
  		{
      		naves();
      		if(proxAtaque==NUEVOATAQUE)
      		proxAtaque=0;
      		else
      		proxAtaque++;
  		}
          state = STATE1;
        }/* Se especifica a que estado debe pasar para continuar con el funcionamiento*/
  		else{
              state = STATE2; /* Se especifica a que estado debe pasar para continuar con el funcionamiento*/
                }

      break;

       case STATE2: /* se define el estado 2*/
       if(GameOver==1){ /* Se evalua la condicion si, no hay pared*/
          proxAtaque=0;
 	  NUEVOATAQUE=0;
 	  SigueJugando=menuFin();
 	  score=0;
                      }
                }
  }
	return (0);
}
void naves ()
{
   int i;
   int recorreNaves;

   if (proxAtaque == NUEVOATAQUE && rayoEnemigoON[navequeAtaca] == 0)
   	rayoEnemigoON[navequeAtaca] = 1;

   for (i=0; i<4; i++)
   	{
      	system("cls");

         if (i==0)
   		escuadronVuelta(ESCUADRON_VUELTA_B, ESCUADRON_VUELTA_B);
         if (i==1)
                escuadronVuelta(ESCUADRON_VUELTA_A, ESCUADRON_VUELTA_B);
         if (i==2)
                escuadronVuelta(ESCUADRON_VUELTA_A, ESCUADRON_VUELTA_A);
         if (i==3)
                escuadronVuelta(ESCUADRON_VUELTA_B, ESCUADRON_VUELTA_A);

         comprueboRayo();

         for (recorreNaves=0; recorreNaves<7; recorreNaves++)
         	{
         		if (rayoEnemigoON[recorreNaves] == 1)
      		                disparaEnemigo(recorreNaves);
			if (rayoDisparado[recorreNaves] == 1)
         			disparo(recorreNaves);
                }

	 leoTecla();
         dibujoJugador(posJugador);
         muestroScore();
         if (GameOver==1)
         	break;
	 sleep ((float) velo);
      }
   navequeAtaca = getrand();

}

void dibujoJugador(int PosNueva)
{
   int i;
   int ii;
   unsigned char x = 220;

    for(i=0; i<3; i++)
      {
      gotoxy(PosNueva+i, 23);
      printf("%c", x);
      }

    for(ii=0; ii<7; ii++)
      	{
          if ( (rayoEnemY[ii]==23) && (rayoEnemX[ii]==PosNueva || rayoEnemX[ii]==PosNueva+1 || rayoEnemX[ii]==PosNueva+2) )
          	GameOver=1;

         }

}
void inicializoNaves()
{
   int x;
   int i;
   int j;

   for (x=0; x<5; x++)
   {
 	  for (i=0; i<7; i++)
 	   	{
      		escuadron[i][x]='*' ;
        }
    }
}

void escuadronVuelta (int VueltaX, int VueltaY)
{
   int x;
   int i;

	for (x=2; x<7; x++)
          {
 	  for (i=1; i<8; i++)
 	   	{
         	gotoxy(10*i+VueltaX , x*2-VueltaY);
            if (rayoPosX == (10*i+VueltaX) && rayoPosY == (x*2-VueltaY) )
            	{
                if (escuadron[i-1][x-2] != ' ')
                {
                  escuadron[i-1][x-2] = ' ';
                  score=score+10;
                  rayoON = 0;
                }
               }
            if(x<2){
                    printf("%s" "\n",octopus[i]);
                 }else if( x<4){
                     printf("%s" "\n",crab[i]);
 	   	        }
 	   	        else printf("%s" "\n",squid[i]);

 	   }
         }
}

void comprueboRayo ()
{
if (rayoON == 1)
   	{
      rayo(rayoPosY);
      rayoPosY--;
      if (rayoPosY<1)
      	{
          rayoON = 0;
         }
      }
}

void rayo(int rayoPosNueva)
{
   gotoxy(rayoPosX, rayoPosNueva);
   printf("%c", RAYCH);
}

void disparaEnemigo(int quienDispara)
{
   int i;

   for(i=4; i>-1; i--)
   	{
       if ( escuadron[navequeAtaca][i] != ' ')
	{
         rayoEnemX[navequeAtaca] = (10*navequeAtaca) + 10;
         rayoEnemY[navequeAtaca] = ((i+2)*2) +1;
         gotoxy(rayoEnemX[navequeAtaca], rayoEnemY[navequeAtaca]);
         printf("X");

         proxAtaque=-1;
         rayoEnemigoON[quienDispara] = 0;
         rayoDisparado[quienDispara] = 1;
         break;
        }

      }

}

void disparo(int quienDispara)
{
   rayoEnemY[quienDispara]++;
   gotoxy(rayoEnemX[quienDispara], rayoEnemY[quienDispara]);
   printf("X");
   if (rayoEnemY[quienDispara]>23)
   	rayoDisparado[quienDispara] = 0;
}

void leoTecla ()
{
	if (kbhit())
   	    {
            teclaAnt = tecla;
          	tecla=getch();
            }

          switch (tecla)
				{
				case TECLA_DER:
               if (posJugador<78)
            		posJugador++;
            break;
				case TECLA_IZQ:
               if (posJugador>1)
            		posJugador--;
            break;
            case DISPARA:
            	if (rayoON==0)
               	{
               	rayoON=1;
                  rayoPosX=posJugador+1;
                  rayoPosY=22;
                  tecla=teclaAnt;
                  }
            break;
	    case EXIT:
                 exit(0);
            break;
            }
}

void muestroScore ()
{
 gotoxy(2,24);
 printf("Score: %d", score);
}

int menuPrincipal()
{
   int x;
   int y;
   char dif = ' ';
   int nivel = 0;

   system("cls");
   gotoxy(5,3);
   for (x=5; x<76; x++)
      {
       gotoxy(x,3);
       printf("%c", 219);
       gotoxy(x,20);
       printf("%c", 219);
      }
   for (y=3; y<20; y++)
      {
       gotoxy(5, y);
       printf("%c", 219);
       gotoxy(75, y);
       printf("%c", 219);
      }

   gotoxy(30,7);
   printf("INVASORES DEL ESPACIO");
   gotoxy(10,10);
   printf("Para comenzar un nuevo juego selecciona Nivel de Dificultad:");
   gotoxy(32,12);
   printf(" [d] Dificil");
   gotoxy(32,13);
   printf(" [n] Normal");
   gotoxy(32,14);
   printf(" [f] Facil");

   while ( (dif != 'd') && (dif != 'n') && (dif != 'f') )
	{
         dif=getch();
        }
	if (dif == 'd')
   	nivel=0;
   if (dif == 'n')
   	nivel=1;
   if (dif == 'f')
   	nivel=2;
return(nivel);
}

int menuFin()
{
char sigue = ' ';
int sig=1;

system("cls");

gotoxy(30, 10);
printf("GAME OVER !!!");
gotoxy(30, 12);
printf("Tu puntuacion fue de %d puntos.", score);
gotoxy(30, 14);
printf("-> Continuar jugando (s/n) ?");
while (sigue!= 's' && sigue != 'n')
	sigue=getch();

if (sigue == 'n')
	sig = 0;

return(sig);
}

void inicializoArrays()
{
   int i;
	for (i=0; i<7; i++)
   	{
       rayoEnemigoON[i]=0;
       rayoDisparado[i]=0;
       rayoEnemX[i] = 0;
       rayoEnemY[i] = 0;
        }
}

int getrand(){
	return(rand()%(7-0)+0);
}

void sleep (float nbr_seconds)
{
 	clock_t goal;
   goal = (nbr_seconds * CLOCKS_PER_SEC) + clock();

   while (goal > clock())
   {
    	;
   }

}

void gotoxy(int x, int y)
{
COORD coord;
coord.X = x-1;
coord.Y = y-1;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

