#ifndef DUOMENYS_H
#define DUOMENYS_H

#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "studentas.h"
#include "laikmatis.h"
#include "funkcijos.h"

// Failo generavimas
void generuotiFaila(int kiekis, const std::string& failoVardas, int ndKiekis = 5);

// Paprasta funkcija su std::vector
std::vector<Studentas> nuskaitytiIsFailo(const std::string& failoVardas);

// Sablonine funkcija konteineriams (vector arba list)
template <typename Container>
Container nuskaitytiIsFailoTemplate(const std::string& failoVardas, bool spausdinti = true) {
    Laikmatis tNuskaitymui;
    Container studentai;

    std::ifstream in(failoVardas);
    if (!in) {
        std::cerr << "Nepavyko atidaryti failo: " << failoVardas << "\n";
        return studentai;
    }

    std::string eilute;
    std::getline(in, eilute); 

    while (std::getline(in, eilute)) {
        if (eilute.empty()) continue;

        std::istringstream iss(eilute);

        Studentas s;
        s.skaitytiStudenta(iss);  // panaudojame vienoda skaitymo funkcija
        studentai.push_back(s);
    }

    if (spausdinti) {
        std::cout << "Failas nuskaitytas per " << tNuskaitymui.praejes_laikas() << " s.\n";
    }

    return studentai;
}


#endif // DUOMENYS_H

