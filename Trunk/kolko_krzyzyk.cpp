//komentarz z vima
//Komentarz mastera
#include <iostream>
#include <string>    //do napisów
#include <conio.h>   //do clrscr
#include <vector>    //do vector<string>
#include <fstream>   //do ifstream
#include <sstream>   //do stringstream
#include <time.h>    //daty i czasu
#include <windows.h> //do Sleep

//przestrzenie nazw
using namespace std;

//funkcje
void menu();  //deklaracja funkcji menu potrzebna np. do rekurencji
void ustawienia();

//zmienne
char wybor;
int kk,ww,krok,krzyzyki,kolka,kx,wx,numer_znaku_wypunktowania,jezyk;
char tablica[3][3];
bool blad,koniec,wstawione;
string gracz1,gracz2,przegr,zwyc,styl_gry_komputera,sposob_blokowania;
string miesiace[12] = {"I","II","III","IV","V","VI","VII","VIII","IX","X","XI","XII"};
string miesiaces[12] = {"stycznia","lutego","marca","kwietnia","maja","czerwca","lipca","sierpnia","wrzeœnia","paŸdziernika","listopada","grudnia"};
string teksty[2][55];

int strtoint(string tekst)
{
stringstream konwersja(tekst);
int liczba;
konwersja>>liczba;
return liczba;
}

void pauza()
{
printf("%s",teksty[jezyk][51].c_str());
getch();
}
void zerowanie()
{
tablica[0][0]=' ';
tablica[0][1]=' ';
tablica[0][2]=' ';
tablica[1][0]=' ';
tablica[1][1]=' ';
tablica[1][2]=' ';
tablica[2][0]=' ';
tablica[2][1]=' ';
tablica[2][2]=' ';
}

void druk()
{
printf("\n%s\n\n",teksty[jezyk][44].c_str());
printf("%c%c%c%c%c\n",tablica[0][0],(char)(179),tablica[1][0],(char)(179),tablica[2][0]);
printf("%c%c%c%c%c\n",(char)(196),(char)(197),(char)(196),(char)(197),(char)(196));
printf("%c%c%c%c%c\n",tablica[0][1],(char)(179),tablica[1][1],(char)(179),tablica[2][1]);
printf("%c%c%c%c%c\n",(char)(196),(char)(197),(char)(196),(char)(197),(char)(196));
printf("%c%c%c%c%c\n\n",tablica[0][2],(char)(179),tablica[1][2],(char)(179),tablica[2][2]);
}

bool wygrana(char znaczek, int k, int w)
{
//badanie wiersza
if ((tablica[0][w]==znaczek)&&(tablica[1][w]==znaczek)&&(tablica[2][w]==znaczek))
return true;

//badanie kolumny
if ((tablica[k][0]==znaczek)&&(tablica[k][1]==znaczek)&&(tablica[k][2]==znaczek))
return true;

//badanie przek¹tnych
if ((k==w)||(k+w==2))
{
if (((tablica[0][0]==znaczek)&&(tablica[1][1]==znaczek)&&(tablica[2][2]==znaczek))||((tablica[2][0]==znaczek)&&(tablica[1][1]==znaczek)&&(tablica[0][2]==znaczek)))
return true;
}
//jesli dosz³o dot¹d to zwróæ 0 (false)
return 0;
}

void ruch(char znak)
{
do
{
blad=false;
printf("%s\n",teksty[jezyk][37].c_str());

do
{
printf("%s ",teksty[jezyk][38].c_str());
scanf("%d",&kk);
if ((kk>3)||(kk<1))
printf("%s\n",teksty[jezyk][39].c_str());
}
while ((kk>3)||(kk<1));
kk--;

do
{
printf("%s ",teksty[jezyk][40].c_str());
scanf("%d",&ww);
if ((ww>3)||(ww<1))
printf("%s\n",teksty[jezyk][39].c_str());
}
while ((ww>3)||(ww<1));
ww--;

if ((ww==1)&&(kk==1)&&((krok==1)||(krok==2))&&((sposob_blokowania=="graczom")||(sposob_blokowania=="wszystkim")))
{
printf("\n%s\n\n",teksty[jezyk][41].c_str());
blad=true;
}
else
{
//czytanie kolumnami w dol
for (int i=0; i<3; i++)
{
for (int j=0; j<3; j++)
{
if ((i==kk)&&(j==ww))
{
if (tablica[kk][ww]==' ')
tablica[kk][ww]=znak;
else
{
printf("%s%d,%d%s\n",teksty[jezyk][42].c_str(),kk+1,ww+1,teksty[jezyk][43].c_str());
blad=true;
break;//petla j
}
}
if (blad)//w petli i
break;//petla i
}
}
}
}
while (blad);
druk(); //pokaz plansze
if (wygrana(znak,kk,ww))
{
if (znak=='O')
zwyc=gracz1;
else
zwyc=gracz2;
koniec=true;
}
}

//funkcje do ruchu komputera
//funkcje z "I" to próba wygrania
bool spr_pion_I(int kol)
{
krzyzyki=0;
if (tablica[kol][0]=='O')
return false;
if (tablica[kol][0]=='X')
krzyzyki++;
if (tablica[kol][1]=='O')
return false;
if (tablica[kol][1]=='X')
krzyzyki++;
if (tablica[kol][2]=='O')
return false;
if (tablica[kol][2]=='X')
krzyzyki++;

if (krzyzyki==2)
return true;
else
return false;
}

bool spr_poziom_I(int wiersz)
{
krzyzyki=0;
if (tablica[0][wiersz]=='O')
return false;
if (tablica[0][wiersz]=='X')
krzyzyki++;
if (tablica[1][wiersz]=='O')
return false;
if (tablica[1][wiersz]=='X')
krzyzyki++;
if (tablica[2][wiersz]=='O')
return false;
if (tablica[2][wiersz]=='X')
krzyzyki++;

if (krzyzyki==2)
return true;
else
return false;
}

bool spr_ukos1_I()
{
krzyzyki=0;
if (tablica[0][0]=='O')
return false;
if (tablica[0][0]=='X')
krzyzyki++;
if (tablica[1][1]=='O')
return false;
if (tablica[1][1]=='X')
krzyzyki++;
if (tablica[2][2]=='O')
return false;
if (tablica[2][2]=='X')
krzyzyki++;

if (krzyzyki==2)
return true;
else
return false;
}

bool spr_ukos2_I()
{
krzyzyki=0;
if (tablica[2][0]=='O')
return false;
if (tablica[2][0]=='X')
krzyzyki++;
if (tablica[1][1]=='O')
return false;
if (tablica[1][1]=='X')
krzyzyki++;
if (tablica[0][2]=='O')
return false;
if (tablica[0][2]=='X')
krzyzyki++;

if (krzyzyki==2)
return true;
else
return false;
}

//sprawdŸ czy mo¿esz wygraæ, jeœli tak to wype³nij ca³¹ dan¹ liniê
bool sprawdz_dwojki_I()
{
//sprawdzanie linii pionowych
if (spr_pion_I(0))
{
tablica[0][0]='X';
tablica[0][1]='X';
tablica[0][2]='X';
kx=0;
wx=1;//np, moze byc tez 0 lub 2
return true;
}
if (spr_pion_I(1))
{
tablica[1][0]='X';
tablica[1][1]='X';
tablica[1][2]='X';
kx=1;
wx=1;//np
return true;
}
if (spr_pion_I(2))
{
tablica[2][0]='X';
tablica[2][1]='X';
tablica[2][2]='X';
kx=2;
wx=1;
return true;
}

//sprawdzanie linii poziomych
if (spr_poziom_I(0))
{
tablica[0][0]='X';
tablica[1][0]='X';
tablica[2][0]='X';
wx=0;
kx=1;//np
return true;
}
if (spr_poziom_I(1))
{
tablica[0][1]='X';
tablica[1][1]='X';
tablica[2][1]='X';
wx=1;
kx=1;//np
return true;
}
if (spr_poziom_I(2))
{
tablica[0][2]='X';
tablica[1][2]='X';
tablica[2][2]='X';
wx=2;
kx=1;//np
return true;
}

//sprawdzanie glownej przekatnej
if (spr_ukos1_I())
{
tablica[0][0]='X';
tablica[1][1]='X';
tablica[2][2]='X';
kx=1;//np
wx=1;//np
return true;
}

//sprawdzanie drugiej przekatnej
if (spr_ukos2_I())
{
tablica[2][0]='X';
tablica[1][1]='X';
tablica[0][2]='X';
kx=1;//np
wx=1;//np
return true;
}
return false;
}

//funkcje z "II" to próba nieprzegrania
bool spr_pion_II(int kol)
{
kolka=0;
if (tablica[kol][0]=='X')
return false;
if (tablica[kol][0]=='O')
kolka++;
if (tablica[kol][1]=='X')
return false;
if (tablica[kol][1]=='O')
kolka++;
if (tablica[kol][2]=='X')
return false;
if (tablica[kol][2]=='O')
kolka++;

if (kolka==2)
return true;
else
return false;
}

bool spr_poziom_II(int wiersz)
{
kolka=0;
if (tablica[0][wiersz]=='X')
return false;
if (tablica[0][wiersz]=='O')
kolka++;
if (tablica[1][wiersz]=='X')
return false;
if (tablica[1][wiersz]=='O')
kolka++;
if (tablica[2][wiersz]=='X')
return false;
if (tablica[2][wiersz]=='O')
kolka++;

if (kolka==2)
return true;
else
return false;
}

bool spr_ukos1_II()
{
kolka=0;
if (tablica[0][0]=='X')
return false;
if (tablica[0][0]=='O')
kolka++;
if (tablica[1][1]=='X')
return false;
if (tablica[1][1]=='O')
kolka++;
if (tablica[2][2]=='X')
return false;
if (tablica[2][2]=='O')
kolka++;

if (kolka==2)
return true;
else
return false;
}

bool spr_ukos2_II()
{
kolka=0;
if (tablica[2][0]=='X')
return false;
if (tablica[2][0]=='O')
kolka++;
if (tablica[1][1]=='X')
return false;
if (tablica[1][1]=='O')
kolka++;
if (tablica[0][2]=='X')
return false;
if (tablica[0][2]=='O')
kolka++;

if (kolka==2)
return true;
else
return false;
}

//sprawdŸ czy mo¿esz przegraæ, jeœli tak to wype³nij puste pole w danej linii
bool sprawdz_dwojki_II()
{
if (spr_pion_II(0))
{
if (tablica[0][0]==' ')
tablica[0][0]='X';
if (tablica[0][1]==' ')
tablica[0][1]='X';
if (tablica[0][2]==' ')
tablica[0][2]='X';
return true;
}
if (spr_pion_II(1))
{
if (tablica[1][0]==' ')
tablica[1][0]='X';
if (tablica[1][1]==' ')
tablica[1][1]='X';
if (tablica[1][2]==' ')
tablica[1][2]='X';
return true;
}
if (spr_pion_II(2))
{
if (tablica[2][0]==' ')
tablica[2][0]='X';
if (tablica[2][1]==' ')
tablica[2][1]='X';
if (tablica[2][2]==' ')
tablica[2][2]='X';
return true;
}

if (spr_poziom_II(0))
{
if (tablica[0][0]==' ')
tablica[0][0]='X';
if (tablica[1][0]==' ')
tablica[1][0]='X';
if (tablica[2][0]==' ')
tablica[2][0]='X';
return true;
}
if (spr_poziom_II(1))
{
if (tablica[0][1]==' ')
tablica[0][1]='X';
if (tablica[1][1]==' ')
tablica[1][1]='X';
if (tablica[2][1]==' ')
tablica[2][1]='X';
return true;
}
if (spr_poziom_II(2))
{
if (tablica[0][2]==' ')
tablica[0][2]='X';
if (tablica[1][2]==' ')
tablica[1][2]='X';
if (tablica[2][2]==' ')
tablica[2][2]='X';
return true;
}

if (spr_ukos1_II())
{
if (tablica[0][0]==' ')
tablica[0][0]='X';
if (tablica[1][1]==' ')
tablica[1][1]='X';
if (tablica[2][2]==' ')
tablica[2][2]='X';
return true;
}

if (spr_ukos2_II())
{
if (tablica[2][0]==' ')
tablica[2][0]='X';
if (tablica[1][1]==' ')
tablica[1][1]='X';
if (tablica[0][2]==' ')
tablica[0][2]='X';
return true;
}
return false;
}

//ruch komputera, trzeba go nauczyc grac !!!
void komputer()
{
int klos,wlos;
if (sprawdz_dwojki_I()) //jesli jest mozliwosc wygrania
{
if (wygrana('X',kx,wx))
{
zwyc=gracz2;
koniec=true;
}
}
else   //a jesli brak mozliwosci wygrania to sprawdz czy mozesz przegrac
{
if (!sprawdz_dwojki_II())  //jesli nie bylo ryzyka przegrania to kombinuj :)
{
//"sztuczna inteligencja" :)
printf("%s ",teksty[jezyk][45].c_str());
if (styl_gry_komputera=="kolejno")
{
printf("%s\n",teksty[jezyk][46].c_str());
for (int i=0; i<3; i++)   //po wierszach
{
for (int j=0; j<3; j++)  //po kolumnach
{
if (tablica[j][i]==' ') //jesli pole wolne
{
tablica[j][i]='X';     //wstaw X
wstawione=true;
break; //do j
}
}
if (wstawione)
{
wstawione=false;
break; //do i
}
}
}
else
{
printf("%s\n",teksty[jezyk][47].c_str());
do
{
srand(time(NULL)); // "wymieszaj"
klos = rand()%3; // lusuj liczbe z przedzialu od 0 do 2
wlos = rand()%3; // lusuj liczbe z przedzialu od 0 do 2

if ((tablica[klos][wlos]==' ')&&(!((wlos==1)&&(klos==1)&&((krok==1)||(krok==2))&&((sposob_blokowania=="komputerowi")||(sposob_blokowania=="wszystkim")))))
{
tablica[klos][wlos]='X';
wstawione=true;
}
}
while (!wstawione);
wstawione=false;
}
} //koniec kombinowania czyli "sztucznej inteligencji"
}
druk();
}

void zapis(string zwyciezca,string przegrany)    //zapis  do pliku
{
FILE *plik;
int lp=1;
//liczenie linii
plik=fopen("wyniki.txt","r");
if (plik!=NULL)
{
vector<string> v;
ifstream zrodlo("wyniki.txt");
string linia;
while(getline(zrodlo,linia))
v.push_back(linia);
for(int i=0;i<v.size();i++)
lp++;
}
fclose(plik);
//koniec liczenia linii

//dopisywanie
plik=fopen("wyniki.txt","a+");
if (plik!=NULL)
{
time_t teraz;
struct tm *czas;
teraz = time(NULL);
czas = localtime(&teraz);
fprintf(plik,"%d) Dnia %d.%s.%d o godz. %d:%d:%d ",lp,czas->tm_mday,miesiace[czas->tm_mon].c_str(),czas->tm_year+1900,czas->tm_hour,czas->tm_min,czas->tm_sec);

if (zwyc!="Komputer")
fprintf(plik,"gracz ");
fprintf(plik,"%s wygral z ",zwyciezca.c_str());
if (przegr=="Komputer")
fprintf(plik,"komputerem.\n");
else
{
fprintf(plik,"graczem %s",przegrany.c_str());
fprintf(plik,".\n");
}
}
else
printf("\n%s\n\n",teksty[jezyk][21].c_str());
fclose(plik);
//koniec dopisywania
}

void z_komputerem()  //gra z komputerem
{
printf("%s ",teksty[jezyk][9].c_str());
/*if (getch()==(char)(27))
{
clrscr();
menu();
}*/
cin>>gracz1;
gracz2="Komputer";
printf("\n");
druk();
for (krok=1; krok<10; krok++)//maksymalnie 9 ruchów
{
if ((krok%2)==1)
{
printf("%s %s\n",gracz1.c_str(),teksty[jezyk][10].c_str());
ruch('O');
}
else
{
printf("%s\n",teksty[jezyk][11].c_str());
komputer();
}
if (koniec)
break;
}//koniec petli for 9
if (koniec)
{
printf("\n%s\n",teksty[jezyk][12].c_str());
printf("%s %s.\n",teksty[jezyk][13].c_str(),zwyc.c_str());
if (zwyc!="Komputer")
{
printf("%s\n",teksty[jezyk][14].c_str());
if (zwyc==gracz1)
przegr=gracz2;
else
przegr=gracz1;
}
else  //wygra³ komputer
{
przegr=gracz1;
printf("%s\n",teksty[jezyk][15].c_str());
}
zapis(zwyc,przegr);
}
else
printf("\n%s\n",teksty[jezyk][16].c_str());
printf("\n");
pauza();
clrscr();
menu();
}//koniec gry z komputerem

void dwuch_graczy()
{
printf("\n%s ",teksty[jezyk][17].c_str());
cin>>gracz1;
printf("%s ",teksty[jezyk][18].c_str());
cin>>gracz2;
druk();
for (krok=1; krok<10; krok++) //maksymalnie 9 ruchów
{
if ((krok%2)==1)
{
printf("%s %s\n",gracz1.c_str(),teksty[jezyk][10].c_str());
ruch('O');
}
else
{
printf("%s %s\n",gracz2.c_str(),teksty[jezyk][19].c_str());
ruch('X');
}
if (koniec)
break; //przerwanie petli 9-u ruchow
} //koniec petli 9
if (koniec)
{
printf("\n%s\n",teksty[jezyk][12].c_str());
printf("%s %s.\n",teksty[jezyk][13].c_str(),zwyc.c_str());
printf("%s\n",teksty[jezyk][14].c_str());
if (zwyc==gracz1)
przegr=gracz2;
else
przegr=gracz1;

zapis(zwyc,przegr);
}
else
printf("\n%s\n",teksty[jezyk][16].c_str());
printf("\n");
pauza();
clrscr();
menu();
} //koniec trybu 2 graczy

void gra()
{
//clrscr();
zerowanie();
kx=0;
wx=0;
koniec=false;

//menu_wewnetrzne();
do
{
clrscr();
for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");

printf(" %s\n",teksty[jezyk][5].c_str());

for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");

printf("1 - %s\n",teksty[jezyk][6].c_str());
printf("2 - %s\n",teksty[jezyk][7].c_str());
printf("3 - %s\n\n\n\n",teksty[jezyk][8].c_str());

for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");

wybor=getch();
printf("\n");
}
while ((wybor!='1')&&(wybor!='2')&&(wybor!='3'));

switch (wybor)
{
case '1': z_komputerem();
break;
case '2': dwuch_graczy();
break;
case '3': clrscr();
menu();
}
}

void wyniki()
{
FILE *plik;
plik=fopen("wyniki.txt","r");
if (plik!=NULL)
{
clrscr();
ifstream zrodlo("wyniki.txt");
string linia;
for (int i=1; i<=75; i++)
printf("%c",(char)(196));
printf("\n");

printf("                               %s\n",teksty[jezyk][20].c_str());

for (int i=1; i<=75; i++)
printf("%c",(char)(196));
printf("\n");

while (getline(zrodlo,linia))
printf("%s\n",linia.c_str());

for (int i=1; i<=75; i++)
printf("%c",(char)(196));
printf("\n\n");
}
else
printf("%s\n\n",teksty[jezyk][53].c_str());

fclose(plik);
pauza();
clrscr();
menu();
}

void wczytaj_ustawienia()
{
FILE *plik;

plik=fopen("pl.lng","r");
if (plik!=NULL)
{
ifstream zrodlo("pl.lng");
for (int i=0; i <= 54; i++)
{
getline(zrodlo,teksty[0][i]);
}
}
fclose(plik);

plik=fopen("en.lng","r");
if (plik!=NULL)
{
ifstream zrodlo("en.lng");
for (int j=0; j <= 54; j++)
{
getline(zrodlo,teksty[1][j]);
}
}
fclose(plik);

printf("Wczytywanie ustawien / Loading settings\n\n");
Sleep(1000);
plik=fopen("ustawienia.ini","r");
if (plik!=NULL)
{
ifstream zrodlo("ustawienia.ini");
string linia;
//dane s¹ w liniach parzystych
getline(zrodlo,linia);
getline(zrodlo,styl_gry_komputera);
getline(zrodlo,linia);
getline(zrodlo,sposob_blokowania);
getline(zrodlo,linia);
getline(zrodlo,linia);
numer_znaku_wypunktowania=strtoint(linia);
getline(zrodlo,linia);
getline(zrodlo,linia);
if (linia=="polski")
jezyk=0;
else
jezyk=1;
if (((styl_gry_komputera=="kolejno")||(styl_gry_komputera=="losowo"))&&((sposob_blokowania=="komputerowi")||(sposob_blokowania=="graczom")||(sposob_blokowania=="wszystkim")||(sposob_blokowania=="nikomu"))&&((linia=="polski")||(linia=="angielski")))
{
printf("%s\n\n",teksty[jezyk][48].c_str());
}
else
{
styl_gry_komputera="kolejno";
sposob_blokowania="nikomu";
numer_znaku_wypunktowania=3;
jezyk=0;
printf("Blad odczytu pliku \"ustawienia.ini\".\nZaladowano ustawienia domyslne.\n\n");
}
}
else
{
styl_gry_komputera="kolejno";
sposob_blokowania="nikomu";
printf("Blad odczytu pliku \"ustawienia.ini\".\nZaladowano ustawienia domyslne.\n\n");
}
fclose(plik);

printf("%s\n\n",teksty[jezyk][54].c_str());

pauza();

clrscr();
return;
}

void zapisz_ustawienia()
{
FILE *plik;
//zapisywanie
plik=fopen("ustawienia.ini","w");
if (plik!=NULL)
{
fprintf(plik,"[styl gry komputera]\n");
fprintf(plik,"%s\n",styl_gry_komputera.c_str());
fprintf(plik,"[blokuj srodkowe pole]\n");
fprintf(plik,"%s\n",sposob_blokowania.c_str());
fprintf(plik,"[numer znaczka wypunktowania]\n");
fprintf(plik,"%d\n",numer_znaku_wypunktowania);
fprintf(plik,"[jezyk]\n");
if (jezyk==0)
fprintf(plik,"polski");
else
fprintf(plik,"angielski");
}
else
{
printf("%s\n\n",teksty[jezyk][52].c_str());
pauza();
}
fclose(plik);
//koniec dopisywania
}

void wypunktowanie()
{
printf("%c",(char)(numer_znaku_wypunktowania));
}

void styl()
{
clrscr();
for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");
printf(" %s\n",teksty[jezyk][28].c_str());
for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");
printf("1 - %s  ",teksty[jezyk][29].c_str());
if (styl_gry_komputera=="losowo")
wypunktowanie();
printf("\n");
printf("2 - %s  ",teksty[jezyk][30].c_str());
if (styl_gry_komputera=="kolejno")
wypunktowanie();
printf("\n");
printf("3 - %s\n",teksty[jezyk][31].c_str());
printf("4 - %s\n\n\n",teksty[jezyk][8].c_str());
for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");

wybor=getch();
printf("\n");
switch (wybor)
{
case '1': styl_gry_komputera="losowo";
styl();
break;
case '2': styl_gry_komputera="kolejno";
styl();
break;
case '3': zapisz_ustawienia();
ustawienia();
break;
case '4': zapisz_ustawienia();
clrscr();
menu();
default : styl();
}
}

void blokowanie()
{
clrscr();
for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");
printf(" %s\n",teksty[jezyk][32].c_str());
for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");
printf("1 - %s ",teksty[jezyk][33].c_str());
if (sposob_blokowania=="komputerowi")
wypunktowanie();
printf("\n");
printf("2 - %s ",teksty[jezyk][34].c_str());
if (sposob_blokowania=="graczom")
wypunktowanie();
printf("\n");
printf("3 - %s ",teksty[jezyk][35].c_str());
if (sposob_blokowania=="wszystkim")
wypunktowanie();
printf("\n");
printf("4 - %s ",teksty[jezyk][36].c_str());
if (sposob_blokowania=="nikomu")
wypunktowanie();
printf("\n");
printf("5 - %s\n",teksty[jezyk][31].c_str());
printf("6 - %s\n",teksty[jezyk][8].c_str());
for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");

wybor=getch();
printf("\n");
switch (wybor)
{
case '1': sposob_blokowania="komputerowi";
blokowanie();
break;
case '2': sposob_blokowania="graczom";
blokowanie();
break;
case '3': sposob_blokowania="wszystkim";
blokowanie();
break;
case '4': sposob_blokowania="nikomu";
blokowanie();
break;
case '5': zapisz_ustawienia();
ustawienia();
break;
case '6': zapisz_ustawienia();
clrscr();
menu();
default : blokowanie();
}
}

void ustawienia_znaczka()
{
clrscr();
for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");
printf(" %s\n",teksty[jezyk][50].c_str());
for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");
for (int i = 1; i <= 5; i++)
{
printf("%d - %c ASCII %d  ",i,(char)(i),i);
if (numer_znaku_wypunktowania==i)
wypunktowanie();
printf("\n");
}
printf("6 - %c ASCII 14 ",(char)(14));
if (numer_znaku_wypunktowania==14)
wypunktowanie();
printf("\n");
printf("7 - %c ASCII 15 ",(char)(15));
if (numer_znaku_wypunktowania==15)
wypunktowanie();
printf("\n");

printf("8 - %s\n",teksty[jezyk][31].c_str());
printf("9 - %s\n",teksty[jezyk][8].c_str());
for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");

wybor=getch();
printf("\n");
switch (wybor)
{
case '1': numer_znaku_wypunktowania=1;
ustawienia_znaczka();
break;
case '2': numer_znaku_wypunktowania=2;
ustawienia_znaczka();
break;
case '3': numer_znaku_wypunktowania=3;
ustawienia_znaczka();
break;
case '4': numer_znaku_wypunktowania=4;
ustawienia_znaczka();
break;
case '5': numer_znaku_wypunktowania=5;
ustawienia_znaczka();
break;
case '6': numer_znaku_wypunktowania=14;
ustawienia_znaczka();
break;
case '7': numer_znaku_wypunktowania=15;
ustawienia_znaczka();
break;
case '8': zapisz_ustawienia();
ustawienia();
break;
case '9': zapisz_ustawienia();
clrscr();
menu();
default : ustawienia_znaczka();
}
}

void ustawienia_jezyka()
{
clrscr();
for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");
printf(" %s\n",teksty[jezyk][27].c_str());
for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");
printf("1 - Polski   ");
if (jezyk==0)
wypunktowanie();
printf("\n");
printf("2 - English  ");
if (jezyk==1)
wypunktowanie();
printf("\n");
printf("3 - %s\n",teksty[jezyk][31].c_str());
printf("4 - %s\n\n\n",teksty[jezyk][8].c_str());
for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");

wybor=getch();
printf("\n");
switch (wybor)
{
case '1': jezyk=0;
ustawienia_jezyka();
break;
case '2': jezyk=1;
ustawienia_jezyka();
break;
case '3': zapisz_ustawienia();
ustawienia();
break;
case '4': zapisz_ustawienia();
clrscr();
menu();
default : ustawienia_jezyka();
}
}

void ustawienia()
{
clrscr();
for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");
printf(" %s\n",teksty[jezyk][22].c_str());
for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");
printf("1 - %s\n",teksty[jezyk][23].c_str());
printf("2 - %s\n    %s\n",teksty[jezyk][24].c_str(),teksty[jezyk][25].c_str());
printf("3 - %s\n",teksty[jezyk][49].c_str());
printf("4 - %s\n",teksty[jezyk][26].c_str());
printf("5 - %s\n",teksty[jezyk][8].c_str());
for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");

wybor=getch();
printf("\n");
switch (wybor)
{
case '1': styl();
break;
case '2': blokowanie();
break;
case '3': ustawienia_znaczka();
break;
case '4': ustawienia_jezyka();
break;
case '5': clrscr();
menu();
default : ustawienia();
}
}

void menu()
{
for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");

printf(" %s\n",teksty[jezyk][0].c_str());
for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");

printf("1 - %s\n",teksty[jezyk][1].c_str());
printf("2 - %s\n",teksty[jezyk][2].c_str());
printf("3 - %s\n",teksty[jezyk][3].c_str());
printf("4 - %s\n\n\n",teksty[jezyk][4].c_str());
for (int i=1; i<=45; i++)
printf("%c",(char)(196));
printf("\n");

wybor=getch();
switch (wybor)
{
case '1': gra();
break;
case '2': wyniki();
break;
case '3': ustawienia();
break;
case '4':
case (char)(27): abort();    //ESC
default : clrscr();
menu();
}
}

//*************    PROGRAM GLOWNY    *************
//aby wygrac z kompuerem przy stylu gry "kolejno":
//1,1 -> 2,2 -> 1,3 -> 3,1

int main()
{
wczytaj_ustawienia();
menu();
return 0;
}
