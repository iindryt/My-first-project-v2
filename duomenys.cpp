#include "duomenys.h"
#include "funkcijos.h"
#include "studentas.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

void testuotiRuleOfThreeIrOperatorius() {
    Studentas original;
    std::cout << "Iveskite studenta pagal originalius duomenis (pvz.: Jonas Jonaitis nd nd ... egz):\n";
    std::cin >> original;

    std::cout << "\nJus ivedete:\n" << original << std::endl;

    Studentas kopija = original; // kopijavimo konstruktorius
    std::cout << "\nKopijuotas studentas (kopijavimo konstruktorius):\n" << kopija << std::endl;

    Studentas priskyrimas;
    priskyrimas = original; // operator=
    std::cout << "\nStudentas po priskyrimo (operator=):\n" << priskyrimas << std::endl;
}

// ============================
//    NUSKAITYMAS IS FAILO
// ============================
std::vector<Studentas> nuskaitytiIsFailo(const std::string& failoVardas) {
    std::vector<Studentas> studentai;
    std::ifstream in(failoVardas);

    if (!in) {
        std::cerr << "Klaida: nepavyko atidaryti failo: " << failoVardas << std::endl;
        return studentai;
    }

    std::string eilute;
    std::getline(in, eilute); 

    while (std::getline(in, eilute)) {
        if (eilute.empty()) continue;

        std::istringstream ss(eilute);
        std::string vard, pav;
        ss >> vard >> pav;

        std::vector<int> laikPaz;
        int paz;

        while (ss >> paz) {
            laikPaz.push_back(paz);
        }

        if (laikPaz.size() < 2) {
            std::cerr << "Klaida: per ma?ai pa?ymi? eilut?je: " << eilute << std::endl;
            continue;
        }

        int egzas = laikPaz.back();
        laikPaz.pop_back();

        // Sukuriam studenta per konstruktr
        Studentas s(vard, pav, egzas, laikPaz);

        
        s.apskaiciuotiRezultatus();

        //itraukkam i srauta
        studentai.push_back(s);
    }

    return studentai;
}

// ============================
//    FAILO GENERAVIMAS
// ============================
void generuotiFaila(int kiekis, const std::string& failoVardas, int ndKiekis) {
    std::ofstream out(failoVardas);
    if (!out) {
        std::cerr << "Nepavyko sukurti failo: " << failoVardas << std::endl;
        return;
    }

    // Antraste
    out << "Vardas Pavarde";
    for (int i = 1; i <= ndKiekis; i++) {
        out << " ND" << i;
    }
    out << " Egzaminas\n";

    // Duomenu generavimas
    for (int i = 1; i <= kiekis; ++i) {
        out << "Vardas" << i << " Pavarde" << i;
        for (int j = 0; j < ndKiekis; ++j) {
            out << " " << random(1, 10);
        }
        out << " " << random(1, 10) << "\n";
    }

    out.close();
    std::cout << "Failas '" << failoVardas << "' sukurtas su " << kiekis << " ?ra??." << std::endl;
}
