#pragma once
#include "biblioteki.h"

class laczenie
{
public:

    sql::Driver* driver = nullptr;
    sql::Connection* con = nullptr;
    sql::Statement* stmt = nullptr;
    sql::ResultSet* res = nullptr;
    sql::ResultSet* res2 = nullptr;


    int ilosc_przedmiotow{};
    int ilosc_studentow{};

    string uczniowie[100];
    string przedmioty[100];
    float oceny[100][100];



    /*tring* uczniowie = new string[ilosc_studentow + 1];
    string* przedmioty = new string[ilosc_przedmiotow + 1];
    float oceny[100][100];

    float ** oceny = new float * [ilosc_studentow];

    for (int i = 1; i < ilosc_studentow + 1; i++) {
        oceny[i] = new float[ilosc_przedmiotow];

    }*/




    laczenie() {};
    laczenie(string server, string username, string password) {
       

        try
        {
            driver = get_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (sql::SQLException e)
        {
            cout << "Nie mozna polaczyc sie z baza danych " << e.what() << endl;
            system("pause");
            exit(1);
        }

    }


    ~laczenie() {
        delete stmt;
        delete con;
        delete res;
        delete res2;

    }

    void pozyskiwanie_informacji();
    void pokaz();

};
class zapis : public laczenie {
public:
    string rozszerzenie{};
    zapis(string server, string username, string password, string rozszerzenie1) : laczenie(server, username, password) {
        rozszerzenie = rozszerzenie1;
    }
    void otwarcie() {
        system("mkdir uczniowie");
        system("cd uczniowie");
        for (int d = 1; d < ilosc_studentow + 1; d++) {

            string sciezka = "uczniowie\\" + uczniowie[d] + rozszerzenie;
            ofstream plik(sciezka);
            for (int j = 1; j < ilosc_przedmiotow + 1; j++) {
                plik << przedmioty[j] << " = " << setprecision(3) << oceny[d][j] << endl;
            }
            plik.close();
        }

    }
    ~zapis() {

    }

};

