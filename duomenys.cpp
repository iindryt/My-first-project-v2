#include "duomenys.h"
#include "funkcijos.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

// ===============================
// Nuskaitymas i vector<Studentas>
// ===============================
std::vector<Studentas> nuskaitytiIsFailo(const std::string& failoVardas) {
    std::vector<Studentas> studentai;
    Laikmatis t;

    std::ifstream in(failoVardas);
    if (!in) {
        std::cerr << "Klaida: nepavyko atidaryti failo: " << failoVardas << std::endl;
        return studentai;
    }

    std::string eilute;
    std::getline(in, eilute); // praleid?iame antra?t?

    while (in) {
        Studentas s(in);  // Naudojame Studentas::readStudent() per konstruktori?
        if (!s.vardas().empty() && !s.pavarde().empty())
            studentai.push_back(s);
    }

    std::cout << "Failas nuskaitytas per " << t.praejes_laikas() << " s.\n";
    return studentai;
}

// ===============================
// Failo generavimas
// ===============================
void generuotiFaila(int kiekis, const std::string& failoVardas, int ndKiekis) {
    std::ofstream out(failoVardas);
    if (!out) {
        std::cerr << "Nepavyko sukurti failo: " << failoVardas << std::endl;
        return;
    }

    out << "Vardas Pavarde";
    for (int i = 1; i <= ndKiekis; i++) {
        out << " ND" << i;
    }
    out << " Egzaminas\n";

    for (int i = 1; i <= kiekis; ++i) {
        out << "Vardas" << i << " Pavarde" << i;
        for (int j = 0; j < ndKiekis; ++j) {
            out << " " << random(1, 10);
        }
        out << " " << random(1, 10) << "\n";
    }

    out.close();
    std::cout << "Failas '" << failoVardas << "' sukurtas su " << kiekis << " irasu.\n";
}
