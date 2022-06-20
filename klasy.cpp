#include "klasy.h"
void laczenie::pozyskiwanie_informacji() {
    try {

        stmt = con->createStatement();
        con->setSchema("uczelnia"); // to jet wybranie bazy danych


        res = stmt->executeQuery("SELECT COUNT(*) FROM studenci"); //zliczanie ilosc studentow
        res->next();
        ilosc_studentow = res->getInt(1);

        res = stmt->executeQuery("SELECT COUNT(*) FROM przedmioty"); // zliczanie ilosc przedmiotow
        res->next();
        ilosc_przedmiotow = res->getInt(1);


        res = stmt->executeQuery("SELECT id, imie, nazwisko FROM studenci"); //uzupelniamy tabele uczniowie   
        while (res->next()) {
            uczniowie[res->getInt("id")] = (res->getString("imie") + " " + res->getString("nazwisko"));                                                                                                                                            // ... or column names for accessing results    
        }

        res = stmt->executeQuery("SELECT id, nazwa FROM przedmioty"); // uzupelnianie tabeli przedmiotow
        while (res->next()) {
            przedmioty[res->getInt("id")] = res->getString("nazwa");
        }

        res = stmt->executeQuery("SELECT id_studenta, id_przedmiotu, ocena FROM oceny"); // uzupelnianie tabeli oceny, tabela laczace id ucznia z id przedmiotu i ocena
        while (res->next()) {
            string ocena = res->getString("ocena");
            oceny[res->getInt("id_studenta")][res->getInt("id_przedmiotu")] += stof(ocena);
        }




        //uzupelnienie do tabeli oceny, wczesniej je tylko zsumowalo
        res = stmt->executeQuery("SELECT DISTINCT id_studenta, id_przedmiotu FROM oceny");
        while (res->next()) {
            string id_studenta = to_string(res->getInt("id_studenta"));
            string id_przedmiotu = to_string(res->getInt("id_przedmiotu"));

            res2 = stmt->executeQuery("SELECT COUNT(*), id_przedmiotu, id_studenta FROM oceny where id_studenta =" + id_studenta + " and id_przedmiotu = " + id_przedmiotu);
            res2->next();
            if (res2->getInt(1) != 0) {
                oceny[res->getInt("id_studenta")][res->getInt("id_przedmiotu")] = oceny[res->getInt("id_studenta")][res->getInt("id_przedmiotu")] / res2->getInt(1);
            }
        }

        cout << "Liczba uczniów: " << ilosc_studentow << "     " << "Liczba przedmiotów: " << ilosc_przedmiotow << endl;
    }
    catch (sql::SQLException e) {
        cout << "Blad w zapytaniach " << endl;
        system("pause");
    }

}
void laczenie::pokaz() {

    for (int d = 1; d < ilosc_studentow + 1; d++) {
        cout << d << " = " << uczniowie[d] << " ";
        for (int j = 1; j < ilosc_przedmiotow + 1; j++) {
            cout << przedmioty[j] << " = " << oceny[d][j] << " ";
        }
        cout << endl;
    }

}


