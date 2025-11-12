#ifndef TESTAVIMAS_H
#define TESTAVIMAS_H

#include <iostream>
#include <vector>
#include <list>
#include <type_traits>
#include <fstream>
#include <string>

#include "studentas.h"
#include "duomenys.h"
#include "laikmatis.h"
#include "funkcijos.h" // deklaracijos strategijoms ir pagalbin?ms funkcijoms

template <typename Container>
void testuotiKonteineri(const std::string& failoVardas, const std::string& pavadinimas) {
    std::cout << "\n=== Testuojamas konteineris: " << pavadinimas << " ===\n";
    Laikmatis tViso;

    // 1. Nuskaitymas is failo
    Laikmatis tNuskaitymui;
    Container studentai = nuskaitytiIsFailoTemplate<Container>(failoVardas, false);
    double laikasNuskaitymas = tNuskaitymui.praejes_laikas();

    if (studentai.empty()) {
        std::cout << "Failas tuscias.\n";
        return;
    }

    // 2. Pasirinkimai
    int strategija = 0;
    while (strategija < 1 || strategija > 3) {
        std::cout << "Pasirinkite strategija:\n";
        std::cout << "1 - Dvi kopijos (rankine)\n";
        std::cout << "2 - Viena kopija su trynimu (rankine)\n";
        std::cout << "3 - Automatinis palyginimas (vector -> STL, kiti -> rankine)\n";
        std::cout << "Jusu pasirinkimas: ";
        if (!(std::cin >> strategija)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            strategija = 0;
            std::cout << "Neteisinga ivestis, bandykite dar karta.\n";
        }
    }

    int baloPasirinkimas = 0;
    while (baloPasirinkimas < 1 || baloPasirinkimas > 2) {
        std::cout << "Pagal ka skirstyti?\n1 - Vidurkis\n2 - Mediana\nJusu pasirinkimas: ";
        if (!(std::cin >> baloPasirinkimas)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            baloPasirinkimas = 0;
            std::cout << "Neteisinga ivestis, bandykite dar karta.\n";
        }
    }

    Balas pasirinktasBalsas = (baloPasirinkimas == 1) ? Balas::Vidurkis : Balas::Mediana;

    Container kietiakiai, vargsiukai;
    double laikasStrategija = 0;
    int pasirinktaTikra = strategija;

    // 3. Strategijos vykdymas
    if (strategija == 1) {
        Laikmatis tStrategijai;
        strategija1_paprasta(studentai, kietiakiai, vargsiukai, pasirinktasBalsas);
        laikasStrategija = tStrategijai.praejes_laikas();
    }
    else if (strategija == 2) {
        Laikmatis tStrategijai;
        strategija2_rankine(studentai, kietiakiai, vargsiukai, pasirinktasBalsas);
        laikasStrategija = tStrategijai.praejes_laikas();
    }
    else if (strategija == 3) {
        Laikmatis tStrategijai;
        strategija3(studentai, kietiakiai, vargsiukai, pasirinktasBalsas, pasirinktaTikra);
        laikasStrategija = tStrategijai.praejes_laikas();
    }

    // 4. Atmintis ir isvedimas
    std::cout << "\n--- Atminties sunaudojimas po strategijos ---\n";

    size_t atmStudentai = skaiciuotiAtminti(studentai);
    size_t atmKietiakiai = skaiciuotiAtminti(kietiakiai);
    size_t atmVargsiukai = skaiciuotiAtminti(vargsiukai);

    if (strategija == 1 || (strategija == 3 && pasirinktaTikra == 1)) {
        // strategija 1: visi konteineriai turi duomenis
        std::cout << "Studentai: " << atmStudentai << " B, "
            << "Kietiakiai: " << atmKietiakiai << " B, "
            << "Vargsiukai: " << atmVargsiukai << " B\n";
        size_t atmViso = atmStudentai + atmKietiakiai + atmVargsiukai;
        std::cout << "Viso apytiksliai: " << atmViso << " B\n";
    }
    else {
        // strategija 2: studentai konteineryje jau tik kietiakiai
        std::cout << "Studentai/kietiakiai: " << atmStudentai << " B, "
            << "Vargsiukai: " << atmVargsiukai << " B\n";
        size_t atmViso = atmStudentai + atmVargsiukai;
        std::cout << "Viso apytiksliai: " << atmViso << " B\n";
    }





    Laikmatis tIrasymui;
    irasytiIFailus(kietiakiai, vargsiukai, pasirinktasBalsas);
    double laikasIrasymas = tIrasymui.praejes_laikas();

    std::cout << "Failo nuskaitymas truko: " << laikasNuskaitymas << " s\n";

    if (strategija == 3) {
        if constexpr (std::is_same_v<Container, std::vector<Studentas>>) {
            std::cout << "Pasirinktos STL strategijos vykdymo laikas: " << laikasStrategija << " s\n";
        }
        else {
            // list atveju   nieko papildomai nebespausdinam
        }
    }
    else {
        std::cout << "Strategijos (" << strategija << ") vykdymo laikas: "
            << laikasStrategija << " s\n";
    }

    std::cout << "Failo irasymas truko: " << laikasIrasymas << " s\n";
    std::cout << "Visas testas truko: " << tViso.praejes_laikas() << " s\n";
}

#endif // TESTAVIMAS_H
