#include "funkcijos.h"
#include "studentas.h"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <sstream>   // d?l std::stringstream
#include <ctime>     // d?l std::time
#include <cstdlib> 

using std::cout;
using std::cin;
using std::endl;
using std::vector;

// ===============================
// Random skaicius
// ===============================
int random(int min, int max) {
    return min + rand() % (max - min + 1);
}



// ===============================
// Ivesti egzamina
// ===============================
int ivestiEgzamina() {
    int egz;
    while (true) {
        cout << "Iveskite egzamino pazymi (1-10): ";
        if (!(cin >> egz)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        if (egz >= 1 && egz <= 10) return egz;
        cout << "Egzamino pazymys turi buti tarp 1 ir 10.\n";
    }
}

// ===============================
// Ivesti studenta
// ===============================
Studentas ivesk() {
    std::string vard, pav;
    std::cout << "Iveskite varda (arba 0 jei norite baigti): ";
    std::cin >> vard;
    if (vard == "0") return Studentas(); // tu??ias studentas

    std::cout << "Iveskite pavarde: ";
    std::cin >> pav;

    std::vector<int> ndPaz;
    int pazymiuSkaicius = 0;

    char pasirinkimas;
    do {
        std::cout << "Ar norite generuoti atsitiktinius namu darbu pazymius? (t/n): ";
        std::cin >> pasirinkimas;
    } while (pasirinkimas != 't' && pasirinkimas != 'T' &&
        pasirinkimas != 'n' && pasirinkimas != 'N');

    if (pasirinkimas == 't' || pasirinkimas == 'T') {
        while (true) {
            std::cout << "Iveskite kiek namu darbu generuoti (1-20): ";
            if (!(std::cin >> pazymiuSkaicius)) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                continue;
            }
            if (pazymiuSkaicius >= 1 && pazymiuSkaicius <= 20) break;
        }
        for (int i = 0; i < pazymiuSkaicius; i++) {
            ndPaz.push_back(random(1, 10));
        }

        //  parodyti tik sugeneruotus pa?ymius
        std::cout << "Sugeneruoti namu darbu pazymiai: ";
        for (int paz : ndPaz) std::cout << paz << " ";
        std::cout << std::endl;
    }
    else {
        std::cout << "Iveskite namu darbu pazymius po viena. Norint baigti, iveskite ne skaiciu.\n";
        while (true) {
            int m;
            std::cout << "Iveskite namu darba nr. " << pazymiuSkaicius + 1 << ": ";
            if (!(std::cin >> m)) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                break;
            }
            if (m < 1 || m > 10) {
                std::cout << "Pazymys turi buti tarp 1 ir 10.\n";
                continue;
            }
            ndPaz.push_back(m);
            pazymiuSkaicius++;
        }
    }

    int egz;
    char genEgz;
    do {
        std::cout << "Ar norite generuoti egzamino pazymi? (t/n): ";
        std::cin >> genEgz;
    } while (genEgz != 't' && genEgz != 'T' && genEgz != 'n' && genEgz != 'N');

    egz = (genEgz == 't' || genEgz == 'T') ? random(1, 10) : ivestiEgzamina();

    // parodyti tik egzamino pa?ym?
    std::cout << "Egzamino pazymys: " << egz << std::endl;

    // Sukuriame Studentas objekta
    return Studentas(vard, pav, ndPaz, egz);
}


