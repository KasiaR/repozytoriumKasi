//Komentarz z vima
//Komentarz mastera\
//komentarz mastera z vima
#include "stdafx.h"
#include "glut.h"
#include "glut_funcs.h"
#include "pole.h"
#include "cegielka.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#define default_speed 300
//###################################################################
//DEKLARACJE FUNKCJI
void drawScene();
void handleKeypress(unsigned char key, int x, int y);
void rysuj_kostke(float x, float y,int w, float *kolor);
void rysuj_gre();
void update(int value);
void end_game();
//###################################################################
//ZMIENNE GLOBALNE
int h=31,w=19;              //wymiary pola gry
cegielka *element;
pole obszar(h,w);           //utworzenie obiektu bedacego polem gry
ofstream wynik;             //strumien wyjscia do zapisu do pliku
int score=0;
int speed=default_speed;    //predkosc opadania cegielek
bool mov = false;           //zmienna logiczna okreslajaca czy cegielka w danej chwili spada
float kolor[][3] =
{
{0.2,0.2,0.2},      //kolor ramki
{0.88,0.93,0.88},   //kolor tla
{0.54,0.17,0.89},{0.5,1,0},{0.18,0.31,0.31},{1,0.14,0},{1,1,0},{1,0.41,0.71},{0.55,0.15,0},{0.75,0.24,1}
};
//###################################################################
int _tmain(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(400, 800);

glutCreateWindow("Tetris");
initRendering();

glutDisplayFunc(drawScene);
glutKeyboardFunc(handleKeypress);
glutReshapeFunc(handleResize);
glutTimerFunc(25, update, 0);

glutMainLoop();

system("pause");
return 0;
}
//###################################################################
void drawScene() {

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

glPushMatrix();
glTranslatef(0,0,-50);
rysuj_gre();
glPopMatrix();

glutSwapBuffers();
}
//###################################################################
void handleKeypress(unsigned char key, //The key that was pressed
int x, int y) {    //The current mouse coordinates

switch (key) {
case 27: //Escape key
end_game();
case 'a'://lewo
if (element->l_check(obszar.wsk))
{
element->mov_left(obszar.wsk);
}
break;
case 'd'://prawo
if (element->r_check(obszar.wsk))
{
element->mov_right(obszar.wsk);
}
break;
case 's':
if (mov)
{
if (element->rot_check(obszar.wsk))
{
element = element->rotate(obszar.wsk,w);
}
}
break;
case 'f':
speed=20;
break;
}
glutPostRedisplay();
}
//###################################################################
void update(int value)
{
if (!mov)
{
obszar.line_check();                //sprawdz czy juz cala linia

if (obszar.wsk[2][7]!=0)            //warunek  game over
{
end_game();
}

speed = default_speed;

srand (time(NULL));                 //inicjalizacja ziarna dla gen liczb losowych

int ktory;
do                                  //losuj numer klocka az wypadnie 0 v 2 v 4 v 6 v 10 v 14 v 15
{
ktory = rand() % 19;
}while (!(ktory == 0 || ktory == 1 || ktory == 2 || ktory == 4 || ktory == 6 || ktory == 10 || ktory == 14 || ktory == 15));
//ktory = 6;


int wybor_koloru = rand() % 8 + 1;      //losuj kolor

element = new cegielka(wybor_koloru, ktory, 7, 2, obszar.wsk);      //tworz nowa cegielke w punkcie (x,y)=(7,2)
mov=true;
}else
{
mov = element->d_check(obszar.wsk);                  //sprawdz czy cegielka moze spasc w dol
if (mov == true) element->mov_down(obszar.wsk);      //jak tak to opusc o jeden w dol
if (mov == false) delete element;                   //jak nie to usun wskaznik na cegielke
}

glutPostRedisplay();
glutTimerFunc(speed, update, 0);
}
//###################################################################
void rysuj_kostke(float x, float y,int w, float *kolor)
// (x,y) - wspolrzedne lewego gornego wierzcholka kostki
// w - wybor koloru
// *kolor - wskaznik na macierz przechowujaca kolory [x][3]w rgb
{
glBegin(GL_QUADS);
//rysuje kostke w podanych wspolrzendych
glColor3f(*(kolor+0+(w+1)*3),*(kolor+1+(w+1)*3),*(kolor+2+(w+1)*3));
glVertex3f(x, y, 0);
glVertex3f(x, y-1, 0);
glVertex3f(x+1, y-1, 0);
glVertex3f(x+1, y, 0);

glEnd();

//rysuje ramki kostki, jesli kostka nie jeste tlem lub obramowaniem
if (w>0)
{
glBegin(GL_LINES);

glColor3f(0,0,0);
//lewa
glVertex3f(x, y, 0.0001);
glVertex3f(x, y-1, 0.0001);
//dolna
glVertex3f(x, y-1, 0.0001);
glVertex3f(x+1, y-1, 0.0001);
//gorna
glVertex3f(x, y, 0.0001);
glVertex3f(x+1, y, 0.0001);
//prawa
glVertex3f(x+1, y, 0.0001);
glVertex3f(x+1, y-1, 0.0001);
glEnd();
}
}
//###################################################################
void rysuj_gre()
{
//wizualizuje macierz bedaca obszarem gry
for (int i=0; i<obszar.zwroc_wysokosc(); i++)
{
for (int j=0; j<obszar.zwroc_szerokosc(); j++)
{
rysuj_kostke(j-9,-i+15,obszar.zwroc_komorke(i,j),&kolor[0][0]);
}
}
}
void end_game()
{
//zapis wyniku do pliku
score = obszar.get_score();
wynik.open("score.txt",fstream::app);
wynik<<"Twoj wynik to: "<<score<<endl;
wynik.close();
exit(0); //Exit the program
}

tetris/cegielka.cpp:
#include "StdAfx.h"
#include "cegielka.h"
//tablice zawierajace wspolrzedne kwadratow wchodzacych w sklad kazdej cegielki wzgledem ukladu wspolrzednych o poczatku w kwadracie bedacym hot pointem
int y_elementy[][4]=
{
{0,1,2,3},{0,0,0,0},                        //0,1
{0,0,1,1},{0,1,1,2},                        //2,3
{1,1,0,0},{0,1,1,2},                        //4,5
{0,0,1,2},{0,1,1,1},{0,1,2,2},{0,-1,-1,-1}, //6,7,8,9
{0,0,1,2},{0,0,0,1},{0,0,-1,-2},{0,1,1,1},  //10,11,12,13
{0,0,1,1},                                  //14
{0,0,0,1},{0,1,2,1},{0,0,0,-1},{0,1,2,1}    //15,16,17,18
};
int x_elementy[][4]=
{
{0,0,0,0},{0,1,2,3},
{0,1,1,2},{1,1,0,0},
{0,1,1,2},{0,0,1,1},
{0,1,1,1},{0,0,-1,-2},{0,0,0,1},{0,0,1,2},
{0,-1,-1,-1},{0,1,2,2},{0,1,1,1},{0,0,1,2},
{0,1,1,0},
{0,1,2,1},{0,0,0,-1},{0,1,2,1},{0,0,0,1}
};
//##############################################################################
cegielka::cegielka(int k, int n, int x, int y, int **ptr)
{
kolor = k;
numer = n;
for (int i=0; i<4; i++)
{
ptr[y+y_elementy[numer][i]][x+x_elementy[numer][i]]=kolor;
xcoords[i]=x+x_elementy[numer][i];
ycoords[i]=y+y_elementy[numer][i];
}
}
//##############################################################################
cegielka::~cegielka(void)
{
}
//##############################################################################
int cegielka::get_numer()
{
return numer;
}
//##############################################################################
bool cegielka::l_check(int **ptr)
{
switch (numer)
{
case 0:
for (int i=0; i<4; i++)
{
if( ptr[ycoords[i]][xcoords[i]-1]!=0) return false;
}
return true;
break;
case 1:
if( ptr[ycoords[0]][xcoords[0]-1]!=0) return false;
return true;
break;
case 2:
if (ptr[ycoords[0]][xcoords[0]-1]!=0) return false;
if (ptr[ycoords[2]][xcoords[2]-1]!=0) return false;
return true;
break;
case 3:
if (ptr[ycoords[0]][xcoords[0]-1]!=0) return false;
if (ptr[ycoords[2]][xcoords[2]-1]!=0) return false;
if (ptr[ycoords[3]][xcoords[3]-1]!=0) return false;
return true;
break;
case 4:
if (ptr[ycoords[0]][xcoords[0]-1]!=0) return false;
if (ptr[ycoords[2]][xcoords[2]-1]!=0) return false;
return true;
break;
case 5:
if (ptr[ycoords[0]][xcoords[0]-1]!=0) return false;
if (ptr[ycoords[1]][xcoords[1]-1]!=0) return false;
if (ptr[ycoords[3]][xcoords[3]-1]!=0) return false;
return true;
break;
case 6:
if (ptr[ycoords[0]][xcoords[0]-1]!=0) return false;
if (ptr[ycoords[2]][xcoords[2]-1]!=0) return false;
if (ptr[ycoords[3]][xcoords[3]-1]!=0) return false;
return true;
break;
case 7:
if (ptr[ycoords[0]][xcoords[0]-1]!=0) return false;
if (ptr[ycoords[3]][xcoords[3]-1]!=0) return false;
return true;
break;
case 8:
if (ptr[ycoords[0]][xcoords[0]-1]!=0) return false;
if (ptr[ycoords[1]][xcoords[1]-1]!=0) return false;
if (ptr[ycoords[2]][xcoords[2]-1]!=0) return false;
return true;
break;
case 9:
if (ptr[ycoords[0]][xcoords[0]-1]!=0) return false;
if (ptr[ycoords[1]][xcoords[1]-1]!=0) return false;
return true;
break;
case 10:
if (ptr[ycoords[1]][xcoords[1]-1]!=0) return false;
if (ptr[ycoords[2]][xcoords[2]-1]!=0) return false;
if (ptr[ycoords[3]][xcoords[3]-1]!=0) return false;
return true;
break;
case 11:
if (ptr[ycoords[0]][xcoords[0]-1]!=0) return false;
if (ptr[ycoords[3]][xcoords[3]-1]!=0) return false;
return true;
break;
case 12:
if (ptr[ycoords[0]][xcoords[0]-1]!=0) return false;
if (ptr[ycoords[2]][xcoords[2]-1]!=0) return false;
if (ptr[ycoords[3]][xcoords[3]-1]!=0) return false;
return true;
break;
case 13:
if (ptr[ycoords[0]][xcoords[0]-1]!=0) return false;
if (ptr[ycoords[1]][xcoords[1]-1]!=0) return false;
return true;
break;
case 14:
if (ptr[ycoords[0]][xcoords[0]-1]!=0) return false;
if (ptr[ycoords[3]][xcoords[3]-1]!=0) return false;
return true;
break;
case 15:
if (ptr[ycoords[0]][xcoords[0]-1]!=0) return false;
if (ptr[ycoords[3]][xcoords[3]-1]!=0) return false;
return true;
break;
case 16:
if (ptr[ycoords[0]][xcoords[0]-1]!=0) return false;
if (ptr[ycoords[2]][xcoords[2]-1]!=0) return false;
if (ptr[ycoords[3]][xcoords[3]-1]!=0) return false;
return true;
break;
case 17:
if (ptr[ycoords[0]][xcoords[0]-1]!=0) return false;
if (ptr[ycoords[3]][xcoords[3]-1]!=0) return false;
return true;
break;
case 18:
if (ptr[ycoords[0]][xcoords[0]-1]!=0) return false;
if (ptr[ycoords[1]][xcoords[1]-1]!=0) return false;
if (ptr[ycoords[2]][xcoords[2]-1]!=0) return false;
return true;
break;
}
return false;
}
//##############################################################################
bool cegielka::r_check(int **ptr)
{
switch (numer)
{
case 0:
for (int i=0; i<4; i++)
{
if( ptr[ycoords[i]][xcoords[i]+1]!=0) return false;
}
return true;
break;
case 1:
if( ptr[ycoords[3]][xcoords[3]+1]!=0) return false;
return true;
break;
case 2:
if( ptr[ycoords[1]][xcoords[1]+1]!=0) return false;
if( ptr[ycoords[3]][xcoords[3]+1]!=0) return false;
return true;
break;
case 3:
if( ptr[ycoords[0]][xcoords[0]+1]!=0) return false;
if( ptr[ycoords[1]][xcoords[1]+1]!=0) return false;
if( ptr[ycoords[3]][xcoords[3]+1]!=0) return false;
return true;
break;
case 4:
if( ptr[ycoords[1]][xcoords[1]+1]!=0) return false;
if( ptr[ycoords[3]][xcoords[3]+1]!=0) return false;
return true;
break;
case 5:
if( ptr[ycoords[0]][xcoords[0]+1]!=0) return false;
if( ptr[ycoords[2]][xcoords[2]+1]!=0) return false;
if( ptr[ycoords[3]][xcoords[3]+1]!=0) return false;
return true;
break;
case 6:
if( ptr[ycoords[1]][xcoords[1]+1]!=0) return false;
if( ptr[ycoords[2]][xcoords[2]+1]!=0) return false;
if( ptr[ycoords[3]][xcoords[3]+1]!=0) return false;
return true;
break;
case 7:
if( ptr[ycoords[0]][xcoords[0]+1]!=0) return false;
if( ptr[ycoords[1]][xcoords[1]+1]!=0) return false;
return true;
break;
case 8:
if( ptr[ycoords[0]][xcoords[0]+1]!=0) return false;
if( ptr[ycoords[1]][xcoords[1]+1]!=0) return false;
if( ptr[ycoords[3]][xcoords[3]+1]!=0) return false;
return true;
break;
case 9:
if( ptr[ycoords[0]][xcoords[0]+1]!=0) return false;
if( ptr[ycoords[3]][xcoords[3]+1]!=0) return false;
return true;
break;
case 10:
if( ptr[ycoords[0]][xcoords[0]+1]!=0) return false;
if( ptr[ycoords[2]][xcoords[2]+1]!=0) return false;
if( ptr[ycoords[3]][xcoords[3]+1]!=0) return false;
return true;
break;
case 11:
if( ptr[ycoords[2]][xcoords[2]+1]!=0) return false;
if( ptr[ycoords[3]][xcoords[3]+1]!=0) return false;
return true;
break;
case 12:
if( ptr[ycoords[1]][xcoords[1]+1]!=0) return false;
if( ptr[ycoords[2]][xcoords[2]+1]!=0) return false;
if( ptr[ycoords[3]][xcoords[3]+1]!=0) return false;
return true;
break;
case 13:
if( ptr[ycoords[0]][xcoords[0]+1]!=0) return false;
if( ptr[ycoords[3]][xcoords[3]+1]!=0) return false;
return true;
break;
case 14:
if( ptr[ycoords[1]][xcoords[1]+1]!=0) return false;
if( ptr[ycoords[2]][xcoords[2]+1]!=0) return false;
return true;
break;
case 15:
if( ptr[ycoords[2]][xcoords[2]+1]!=0) return false;
if( ptr[ycoords[3]][xcoords[3]+1]!=0) return false;
return true;
break;
case 16:
if( ptr[ycoords[0]][xcoords[0]+1]!=0) return false;
if( ptr[ycoords[1]][xcoords[1]+1]!=0) return false;
if( ptr[ycoords[2]][xcoords[2]+1]!=0) return false;
return true;
break;
case 17:
if( ptr[ycoords[2]][xcoords[2]+1]!=0) return false;
if( ptr[ycoords[3]][xcoords[3]+1]!=0) return false;
return true;
break;
case 18:
if( ptr[ycoords[0]][xcoords[0]+1]!=0) return false;
if( ptr[ycoords[2]][xcoords[2]+1]!=0) return false;
if( ptr[ycoords[3]][xcoords[3]+1]!=0) return false;
return true;
break;
}
return false;
}
//##############################################################################
bool cegielka::d_check(int **ptr)
{
switch (numer)
{
case 0:
if( ptr[ycoords[3]+1][xcoords[3]]!=0) return false;
return true;
break;
case 1:
for (int i=0;i<4;i++)
{
if (ptr[ycoords[i]+1][xcoords[i]]!=0) return false;
}
return true;
break;
case 2:
if( ptr[ycoords[0]+1][xcoords[0]]!=0) return false;
if( ptr[ycoords[2]+1][xcoords[2]]!=0) return false;
if( ptr[ycoords[3]+1][xcoords[3]]!=0) return false;
return true;
break;
case 3:
if( ptr[ycoords[1]+1][xcoords[1]]!=0) return false;
if( ptr[ycoords[3]+1][xcoords[3]]!=0) return false;
return true;
break;
case 4:
if( ptr[ycoords[0]+1][xcoords[0]]!=0) return false;
if( ptr[ycoords[1]+1][xcoords[1]]!=0) return false;
if( ptr[ycoords[3]+1][xcoords[3]]!=0) return false;
return true;
break;
case 5:
if( ptr[ycoords[1]+1][xcoords[1]]!=0) return false;
if( ptr[ycoords[3]+1][xcoords[3]]!=0) return false;
return true;
break;
case 6:
if( ptr[ycoords[0]+1][xcoords[0]]!=0) return false;
if( ptr[ycoords[3]+1][xcoords[3]]!=0) return false;
return true;
break;
case 7:
if( ptr[ycoords[1]+1][xcoords[1]]!=0) return false;
if( ptr[ycoords[2]+1][xcoords[2]]!=0) return false;
if( ptr[ycoords[3]+1][xcoords[3]]!=0) return false;
return true;
break;
case 8:
if( ptr[ycoords[2]+1][xcoords[2]]!=0) return false;
if( ptr[ycoords[3]+1][xcoords[3]]!=0) return false;
return true;
break;
case 9:
if( ptr[ycoords[0]+1][xcoords[0]]!=0) return false;
if( ptr[ycoords[2]+1][xcoords[2]]!=0) return false;
if( ptr[ycoords[3]+1][xcoords[3]]!=0) return false;
return true;
break;
case 10:
if( ptr[ycoords[0]+1][xcoords[0]]!=0) return false;
if( ptr[ycoords[3]+1][xcoords[3]]!=0) return false;
return true;
break;
case 11:
if( ptr[ycoords[0]+1][xcoords[0]]!=0) return false;
if( ptr[ycoords[1]+1][xcoords[1]]!=0) return false;
if( ptr[ycoords[3]+1][xcoords[3]]!=0) return false;
return true;
break;
case 12:
if( ptr[ycoords[0]+1][xcoords[0]]!=0) return false;
if( ptr[ycoords[1]+1][xcoords[1]]!=0) return false;
return true;
break;
case 13:
if( ptr[ycoords[1]+1][xcoords[1]]!=0) return false;
if( ptr[ycoords[2]+1][xcoords[2]]!=0) return false;
if( ptr[ycoords[3]+1][xcoords[3]]!=0) return false;
return true;
break;
case 14:
if( ptr[ycoords[2]+1][xcoords[2]]!=0) return false;
if( ptr[ycoords[3]+1][xcoords[3]]!=0) return false;
return true;
break;
case 15:
if( ptr[ycoords[0]+1][xcoords[0]]!=0) return false;
if( ptr[ycoords[2]+1][xcoords[2]]!=0) return false;
if( ptr[ycoords[3]+1][xcoords[3]]!=0) return false;
return true;
break;
case 16:
if( ptr[ycoords[2]+1][xcoords[2]]!=0) return false;
if( ptr[ycoords[3]+1][xcoords[3]]!=0) return false;
return true;
break;
case 17:
if( ptr[ycoords[0]+1][xcoords[0]]!=0) return false;
if( ptr[ycoords[1]+1][xcoords[1]]!=0) return false;
if( ptr[ycoords[2]+1][xcoords[2]]!=0) return false;
return true;
break;
case 18:
if( ptr[ycoords[2]+1][xcoords[2]]!=0) return false;
if( ptr[ycoords[3]+1][xcoords[3]]!=0) return false;
return true;
break;
}
return false;
}
//##############################################################################
bool cegielka::rot_check(int **ptr)
{
switch (numer)
{
case 0:
if( ptr[ycoords[0]][xcoords[0]+1]!=0) return false;
if( ptr[ycoords[0]][xcoords[0]+2]!=0) return false;
if( ptr[ycoords[0]][xcoords[0]+3]!=0) return false;
return true;
case 1:
if( ptr[ycoords[0]+1][xcoords[0]]!=0) return false;
if( ptr[ycoords[0]+2][xcoords[0]]!=0) return false;
if( ptr[ycoords[0]+3][xcoords[0]]!=0) return false;
return true;
case 2:
if( ptr[ycoords[0]+1][xcoords[0]]!=0) return false;
if( ptr[ycoords[0]+2][xcoords[0]]!=0) return false;
return true;
case 3:
if( ptr[ycoords[0]][xcoords[0]-1]!=0) return false;
if( ptr[ycoords[0]+1][xcoords[0]+1]!=0) return false;
return true;
case 4:
if( ptr[ycoords[0]-1][xcoords[0]]!=0) return false;
if( ptr[ycoords[0]+1][xcoords[0]+1]!=0) return false;
return true;
case 5:
if( ptr[ycoords[0]][xcoords[0]+1]!=0) return false;
if( ptr[ycoords[0]][xcoords[0]+2]!=0) return false;
return true;
case 6:
if( ptr[ycoords[0]+1][xcoords[0]]!=0) return false;
if( ptr[ycoords[0]][xcoords[0]+2]!=0) return false;
if( ptr[ycoords[0]+1][xcoords[0]+2]!=0) return false;
return true;
case 7:
if( ptr[ycoords[0]][xcoords[0]-1]!=0) return false;
if( ptr[ycoords[0]+2][xcoords[0]]!=0) return false;
if( ptr[ycoords[0]+2][xcoords[0]-1]!=0) return false;
return true;
case 8:
if( ptr[ycoords[0]+1][xcoords[0]+1]!=0) return false;
if( ptr[ycoords[0]+1][xcoords[0]-1]!=0) return false;
if( ptr[ycoords[0]+2][xcoords[0]-1]!=0) return false;
return true;
case 9:
if( ptr[ycoords[0]-2][xcoords[0]]!=0) return false;
if( ptr[ycoords[0]-2][xcoords[0]+1]!=0) return false;
if( ptr[ycoords[0]][xcoords[0]+1]!=0) return false;
return true;
case 10:
if( ptr[ycoords[0]+1][xcoords[0]]!=0) return false;
if( ptr[ycoords[0]+1][xcoords[0]-2]!=0) return false;
if( ptr[ycoords[0]+2][xcoords[0]]!=0) return false;
return true;
case 11:
if( ptr[ycoords[0]+1][xcoords[0]]!=0) return false;
if( ptr[ycoords[0]-1][xcoords[0]+1]!=0) return false;
if( ptr[ycoords[0]+1][xcoords[0]+1]!=0) return false;
return true;
case 12:
if( ptr[ycoords[0]-1][xcoords[0]]!=0) return false;
if( ptr[ycoords[0]-1][xcoords[0]+2]!=0) return false;
if( ptr[ycoords[0]-2][xcoords[0]]!=0) return false;
return true;
case 13:
if( ptr[ycoords[0]][xcoords[0]+1]!=0) return false;
if( ptr[ycoords[0]+2][xcoords[0]+1]!=0) return false;
if( ptr[ycoords[0]][xcoords[0]+2]!=0) return false;
return true;
case 15:
if( ptr[ycoords[0]+2][xcoords[0]+2]!=0) return false;
if( ptr[ycoords[0]+1][xcoords[0]+2]!=0) return false;
return true;
case 16:
if( ptr[ycoords[0]+2][xcoords[0]-1]!=0) return false;
if( ptr[ycoords[0]+2][xcoords[0]-2]!=0) return false;
return true;
case 17:
if( ptr[ycoords[0]-1][xcoords[0]]!=0) return false;
if( ptr[ycoords[0]-2][xcoords[0]]!=0) return false;
return true;
case 18:
if( ptr[ycoords[0]][xcoords[0]+1]!=0) return false;
if( ptr[ycoords[0]][xcoords[0]+2]!=0) return false;
return true;
}
return false;
}
//##############################################################################
int cegielka::get_xcoords(int i)
{
return xcoords[i];
}
//##############################################################################
int cegielka::get_ycoords(int i)
{
return ycoords[i];
}
//##############################################################################
void cegielka::set_xcoords(int i, int value)
{
xcoords[i] = value;
}
//##############################################################################
void cegielka::set_ycoords(int i, int value)
{
ycoords[i] = value;
}
//##############################################################################
void cegielka::mov_down(int **ptr)
{
for (int i=0; i<4; i++)
{
ptr[ycoords[i]++][xcoords[i]]=0;
}
for (int i=0; i<4; i++)
{
ptr[ycoords[i]][xcoords[i]]=kolor;
}
}
//##############################################################################
void cegielka::mov_right(int **ptr)
{
for (int i=0; i<4; i++)
{
ptr[ycoords[i]][xcoords[i]++]=0;
}
for (int i=0; i<4; i++)
{
ptr[ycoords[i]][xcoords[i]]=kolor;
}
}
//##############################################################################
void cegielka::mov_left(int **ptr)
{
for (int i=0; i<4; i++)
{
ptr[ycoords[i]][xcoords[i]--]=0;
}
for (int i=0; i<4; i++)
{
ptr[ycoords[i]][xcoords[i]]=kolor;
}
}
//##############################################################################
cegielka* cegielka::rotate(int **ptr, int w)
{
erase(ptr);
cegielka *wsk;
switch (numer)
{
case 0:
wsk = new cegielka(kolor, 1, xcoords[0],ycoords[0], ptr);
delete this;
return wsk;
case 1:
wsk = new cegielka(kolor, 0, xcoords[0], ycoords[0], ptr);
delete this;
return wsk;
case 2:
wsk = new cegielka(kolor, 3, xcoords[0], ycoords[0], ptr);
delete this;
return wsk;
case 3:
wsk = new cegielka(kolor, 2, xcoords[0]-1,ycoords[0], ptr);
delete this;
return wsk;
case 4:
wsk = new cegielka(kolor, 5, xcoords[0], ycoords[0]-1, ptr);
delete this;
return wsk;
case 5:
wsk = new cegielka(kolor, 4, xcoords[0],ycoords[0], ptr);
delete this;
return wsk;
case 6:
wsk = new cegielka(kolor, 7, xcoords[0]+2, ycoords[0], ptr);
delete this;
return wsk;
case 7:
wsk = new cegielka(kolor, 8, xcoords[0]-1,ycoords[0], ptr);
delete this;
return wsk;
case 8:
wsk = new cegielka(kolor, 9, xcoords[0]-1,ycoords[0]+2, ptr);
delete this;
return wsk;
case 9:
wsk = new cegielka(kolor, 6, xcoords[0], ycoords[0]-2, ptr);
delete this;
return wsk;
case 10:
wsk = new cegielka(kolor, 11, xcoords[0]-2,ycoords[0]+1, ptr);
delete this;
return wsk;
case 11:
wsk = new cegielka(kolor, 12, xcoords[0], ycoords[0]+1, ptr);
delete this;
return wsk;
break;
case 12:
wsk = new cegielka(kolor, 13, xcoords[0],ycoords[0]-2, ptr);
delete this;
return wsk;
break;
case 13:
wsk = new cegielka(kolor, 10, xcoords[0]+2, ycoords[0], ptr);
delete this;
return wsk;
//14 skipnieta bo to kwadrat
case 15:
wsk = new cegielka(kolor, 16, xcoords[0]+2, ycoords[0], ptr);
delete this;
return wsk;
case 16:
wsk = new cegielka(kolor, 17, xcoords[0]-2,ycoords[0]+2, ptr);
delete this;
return wsk;
case 17:
wsk = new cegielka(kolor, 18, xcoords[0], ycoords[0]-2, ptr);
delete this;
return wsk;
case 18:
wsk = new cegielka(kolor, 15, xcoords[0],ycoords[0], ptr);
delete this;
return wsk;
}
wsk = new cegielka(kolor, numer, xcoords[0],ycoords[0], ptr);
delete this;
return wsk;
}
//##############################################################################
void cegielka::erase(int **ptr)
{
for (int i=0; i<4; i++)
{
ptr[ycoords[i]][xcoords[i]]=0;
}
}
