// author: Benedykt Bernard Bela
// Code::Blocks 17.12

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <iomanip>


using namespace std;


struct dane                     //  struktura sluzaca do przechowywania statystyk
{
    int popodp = 0;             //  poprawne odpowiedzi
    int odp = 0;                //  odpowiedzi
};


const int MAX_ZAKRES = 10;
const int LICZBA_NUT = 3;
const int MAX_NIEPOPRAWNYCH = 100;


void wypisznuty (char znaki[LICZBA_NUT]);
void pisz_menu (void);
void pisz_statystyki (dane statystyki[]);
void procent_poprawnych(int a, int b);
int wybierz_opcje(dane statystyki[]);
void zwraca_znak(char nuty[LICZBA_NUT], int x);
char quiz (dane statystyki[]);
void wypelnij_nieodgadniete(char nieodgadniete[MAX_NIEPOPRAWNYCH]);
void sprawdzam_stan_quizu(char nuty[LICZBA_NUT], char nieodgadniete[MAX_NIEPOPRAWNYCH], int i);



int main()
{
    dane statystyki[8];
    pisz_menu();

    while (wybierz_opcje(statystyki));

    return 0;
}



int wybierz_opcje(dane statystyki[])
{
    char test;
    cin>>test;                      //  wybor jednej z opcji menu quizu
    system( "cls" );
    pisz_menu();

    do
    {
        switch (test)                       //  wybor dzialania w zaleznosci od wyboru gracza
        {
            case '1':
            case '3':     test = quiz(statystyki); break;                       //  powoduje rozpoczecie quizu, nadanie zmiennej 'test' wartosci funkcji 'quiz' 
                                                                                //  pozwala na sterowanie opcjami programu z funcji 'quiz'

            case '2':     cout<<"\n\n"<<"KONIEC PROGRAMU";
                        pisz_statystyki(statystyki);
                        return 0;                       //  powoduje zakonczenie programu

            case '4':     pisz_statystyki(statystyki);
                        return 1;                       //  powoduje ponowne wykonanie instrukcji wybierz_opcje

            default:    cout<<"Niepoprawna opcja! Sprobuj jeszcze raz >  ";
                        return 1;
        }
    } while (1);
}



char quiz(dane statystyki[])
{
    int zakres = MAX_ZAKRES, ktora = 0, nuta;                        // 4 kolejne linijki to definicja zmiennych potrzebnych do dzialania quizu
    char nuty[LICZBA_NUT], sprawdzam_char;
    char nieodgadniete[MAX_NIEPOPRAWNYCH];
    bool check = true;

    wypelnij_nieodgadniete(nieodgadniete);
    zwraca_znak(nuty, 0);                       //  3 kolejne linijki losowo wybieraja pierwsze trzy nuty do quizu
    zwraca_znak(nuty, 1);
    zwraca_znak(nuty, 2);


    for (int i = 0; i < zakres; i++)                        //  glowny mechanizm quizu
    {
        do
        {

            check = true;

            cout<<i+1<<" / "<<zakres<<endl<<endl;                     //    wypisuje ktora z kolei nutke zgadujemy i ile razem mamy do odgadniecia
            wypisznuty(nuty);
            cout<<"\n"<<"Jaka to nuta? >  ";

            cin>>sprawdzam_char;
            system( "cls" );
            pisz_menu();


            switch (sprawdzam_char)                     //  w zaleznosci od znaku podanego na wejsciu program wykonuje rozne instrukcje
            {
                case 'a': nuta = 5; break;
                case 'h': nuta = 6; break;
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                case 'g':   nuta = (int)sprawdzam_char - 99; break;
                case '2':   return '2';                             //  KONIEC PROGRAMU
                case '3':   return '1';
                case '4':   system("cls");
                            pisz_statystyki(statystyki);
                            check = false;                          //  powoduje wykonanie petli while kolejny raz
                            char k;
                            cout<<"\n\nABY KONTYNUOWAC NACISNIJ JAKAS LITERE I ENTER > ";
                            cin>>k;
                            system("cls");
                            pisz_menu();
                            break;
                default: cout<<"Niepoprawne dane!  "; check = false;
            }

        }
        while (!check);


        if (sprawdzam_char == nuty[0]){                     //  10 kolejnych linijek aktualizuje statystyki
            statystyki[nuta].odp++;
            statystyki[nuta].popodp++;
        }
        else {
            statystyki[nuta].odp++;
            nieodgadniete[ktora] = nuty[0];                     //  2 kolejne linijki zapisuje nieodgadniete nutki, aby moc je dodac na koncu quizu
            ktora++;
            zakres++;                       //  jezeli nutka nie zostala poprawnie odgadnieta zostaje przeniesiona na koniec, 
                                            //  czyli zwieksza sie ilosc wykonan petli for
        }


        sprawdzam_stan_quizu(nuty, nieodgadniete, i);           //  mechanizm dopisujacy nieodgadniete nutki na koniec quizu, dla czytelnosci przeniesony do tejze funkcji

    }

    cout<<"\n\nKONIEC QUIZU";

    return '4';                         //  na zakonczenie quizu wyswietlane sa statystyki rozegranej gry

}



void sprawdzam_stan_quizu(char nuty[LICZBA_NUT], char nieodgadniete[MAX_NIEPOPRAWNYCH], int i)
{
    static int pomocnicza = 0;

    if (i < 7){                     //  pierwsze 7 nut jest generowane przez program, wiec przesuwam nuty o jeden w lewo
        nuty[0] = nuty[1];
        nuty[1] = nuty[2];
        zwraca_znak(nuty, 2);
        }
    else if (nuty[2] != 'x'){                       //  zostaly conajmniej 3 nuty do odgadniecia
        nuty[0] = nuty[1];
        nuty[1] = nuty[2];
        nuty[2] = nieodgadniete[pomocnicza]; if (nieodgadniete[pomocnicza] != 'x') pomocnicza++;
        }
    else if (nuty[1] != 'x'){           //  zostaly 2 nuty do odgadniecia
        nuty[0] = nuty[1];
        nuty[1] = nieodgadniete[pomocnicza]; if (nieodgadniete[pomocnicza] != 'x') pomocnicza++;
        nuty[2] =  'x';
        }
    else {                      //  zostala 1 nuta do odgadniecia
        nuty[0] = nieodgadniete[pomocnicza]; if (nieodgadniete[pomocnicza] != 'x') pomocnicza++;
        nuty[1] = 'x';
        nuty[2] = 'x';
        }

}



void zwraca_znak(char nuty[LICZBA_NUT], int x)                      //  generuje losowo nuty do quizu
{
    int help;

    if (x == 0){                        //  dla pierwszej nuty
        srand(time(NULL));
        help = rand()%7;

        switch (help)
        {
            case 0:    nuty[x] = 'c'; break;
            case 1:    nuty[x] = 'd'; break;
            case 2:    nuty[x] = 'e'; break;
            case 3:    nuty[x] = 'f'; break;
            case 4:    nuty[x] = 'g'; break;
            case 5:    nuty[x] = 'a'; break;
            case 6:    nuty[x] = 'h'; break;
        }

    }
    else{                       //  dla drugiej lub 3 nuty

        do{
            srand(time(NULL));
            help = rand()%7;

            switch (help)
            {
                case 0:    nuty[x] = 'c'; break;
                case 1:    nuty[x] = 'd'; break;
                case 2:    nuty[x] = 'e'; break;
                case 3:    nuty[x] = 'f'; break;
                case 4:    nuty[x] = 'g'; break;
                case 5:    nuty[x] = 'a'; break;
                case 6:    nuty[x] = 'h'; break;
            }

        } while (nuty[x-1] == nuty[x]);             //  wykonuje petle az sasiednie nuty beda rozne

    }

}



void pisz_statystyki(dane statystyki[])
{
    cout<<"\n\n"
        <<"Statystyki Twojej gry:"<<"\n\n";


    for (int i = 0; i < 7; i++)                     //  liczy sume odpowiedzi i sume poprawnych odpowiedzi
    {
        statystyki[7].popodp += statystyki[i].popodp;
        statystyki[7].odp += statystyki[i].odp;
    }


    cout<<"\n\n|             |  Liczba poprawnych  |  Liczba odpowiedzi:  |  Liczba poprawnych odpowiedzi/  |"<<endl
        <<    "|             |  odpowiedzi:        |                      |  liczba odpowiedzi:             |"<<endl
        <<    "----------------------------------------------------------------------------------------------"<<endl;
        cout<<"| Sumaryczna  |  "  <<setw(11)<<statystyki[7].popodp<<"        |  "<<setw(11)<<statystyki[7].odp<<"         |  "; procent_poprawnych(statystyki[7].popodp, statystyki[7].odp );
        cout<<"| nuta \"c\"    |  "<<setw(11)<<statystyki[0].popodp<<"        |  "<<setw(11)<<statystyki[0].odp<<"         |  "; procent_poprawnych(statystyki[0].popodp, statystyki[0].odp );
        cout<<"| nuta \"d\"    |  "<<setw(11)<<statystyki[1].popodp<<"        |  "<<setw(11)<<statystyki[1].odp<<"         |  "; procent_poprawnych(statystyki[1].popodp, statystyki[1].odp );
        cout<<"| nuta \"e\"    |  "<<setw(11)<<statystyki[2].popodp<<"        |  "<<setw(11)<<statystyki[2].odp<<"         |  "; procent_poprawnych(statystyki[2].popodp, statystyki[2].odp );
        cout<<"| nuta \"f\"    |  "<<setw(11)<<statystyki[3].popodp<<"        |  "<<setw(11)<<statystyki[3].odp<<"         |  "; procent_poprawnych(statystyki[3].popodp, statystyki[3].odp );
        cout<<"| nuta \"g\"    |  "<<setw(11)<<statystyki[4].popodp<<"        |  "<<setw(11)<<statystyki[4].odp<<"         |  "; procent_poprawnych(statystyki[4].popodp, statystyki[4].odp );
        cout<<"| nuta \"a\"    |  "<<setw(11)<<statystyki[5].popodp<<"        |  "<<setw(11)<<statystyki[5].odp<<"         |  "; procent_poprawnych(statystyki[5].popodp, statystyki[5].odp );
        cout<<"| nuta \"h\"    |  "<<setw(11)<<statystyki[6].popodp<<"        |  "<<setw(11)<<statystyki[6].odp<<"         |  "; procent_poprawnych(statystyki[6].popodp, statystyki[6].odp );


        statystyki[7].popodp = 0;                       //  zeruje sume odpowiedzi i sume poprawnych odpowiedzi
        statystyki[7].odp = 0;

}



void procent_poprawnych(int a, int b)                       //  a - liczba poprawnych odpowiedzi, b - liczba odpowiedzi
{

    if (b != 0){         // sprawdza, czy liczba odpowiedzi nie wynosi 0, aby nie dzielic przez 0
        cout<<setw(17)<<setprecision(0)<<fixed<<((float)a/b)*100<<"%             |"<<endl;
    }
    else
        cout<<setw(23)<<"Brak odpowiedzi"<<"        |"<<endl;

}



void pisz_menu (void)
{

    cout<<"\n"
        <<"Uruchom Quiz > 1"<<endl
        <<"Zakoncz Quiz > 2"<<endl
        <<"Rozpocznij od nowa > 3"<<endl
        <<"Pokaz statystyki > 4"<<endl
        <<">  ";

}



void wypisznuty (char znak[LICZBA_NUT])                     //  wypisuje pieciolinie z nutami w zaleznosci od wygenerowanych nut
{

    cout<<"---------------------------------------"<<endl<<endl
        <<"---------------------------------------"<<endl<<endl;


    for (int i = 0; i < 3; i++){
        if (znak[i] == 'h')
            cout<<"-----( )-----";
        else
            cout<<"-------------";
    }
    cout<<endl;


    for (int i = 0; i < 3; i++){
        if (znak[i] == 'a')
            cout<<"     ( )     ";
        else
            cout<<"             ";
    }
    cout<<endl;


    for (int i = 0; i < 3; i++){
        if (znak[i] == 'g')
            cout<<"-----( )-----";
        else
            cout<<"-------------";
    }
    cout<<endl;


    for (int i = 0; i < 3; i++){
        if (znak[i] == 'f')
            cout<<"     ( )     ";
        else
            cout<<"             ";
    }
    cout<<endl;


    for (int i = 0; i < 3; i++){
        if (znak[i] == 'e')
            cout<<"-----( )-----";
        else
            cout<<"-------------";
    }
    cout<<endl;


    for (int i = 0; i < 3; i++){
        if (znak[i] == 'd')
            cout<<"     ( )     ";
        else
            cout<<"             ";
    }
    cout<<endl;


    for (int i = 0; i < 3; i++){
        if (znak[i] == 'c')
            cout<<"-----( )-----";
        else
            cout<<"             ";
    }
    cout<<endl;

}



void wypelnij_nieodgadniete(char nieodgadniete[MAX_NIEPOPRAWNYCH])
{
    for (int i = 0; i < MAX_NIEPOPRAWNYCH; i++)
        nieodgadniete[i] = 'x';
}




