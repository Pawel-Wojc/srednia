#include "klasy.h"

const string server = "tcp://127.0.0.1:3306";
//const string username = "root";
//const string password = "";

int main()
{
    setlocale(LC_CTYPE, "Polish");
    string username;
    string password;
    cout.precision(2);
    cout << "Podaj dane do logowania bazy:" << endl;
    cout << "Nazwa uzytkownika: ";
    cin >> username;
    cout << "Haslo: ";
    cin >> password;



    zapis nowy(server, username, password, ".txt"); // ostatni parametr to rozszerzenie do jakiego pliku ma byc zapisane
    nowy.pozyskiwanie_informacji();
    nowy.pokaz();
    nowy.otwarcie();
    system("pause");
    return 0;
}