#include "funkcijos.h"
#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

// ==========================================================
// Random skaicius
// ==========================================================
int random(int min, int max) {
    return min + rand() % (max - min + 1);
}

// ==========================================================
// Mediana
// ==========================================================
float Mediana(const vector<int>& pazymiai) {
    if (pazymiai.empty()) return 0.0f;
    vector<int> kopija = pazymiai;
    std::sort(kopija.begin(), kopija.end());

    size_t n = kopija.size();
    if (n % 2 == 1)
        return kopija[n / 2];
    else
        return (kopija[n / 2 - 1] + kopija[n / 2]) / 2.0f;
}

float Mediana(std::list<int> pazymiai) {
    if (pazymiai.empty()) return 0.0f;

    pazymiai.sort();
    size_t n = pazymiai.size();
    auto it = pazymiai.begin();
    std::advance(it, n / 2);

    if (n % 2 == 1) {
        return *it;
    }
    else {
        auto it2 = it;
        std::advance(it2, -1);
        return (*it + *it2) / 2.0f;
    }
}

// ==========================================================
// Vidurkis
// ==========================================================
float Vidurkis(const vector<int>& pazymiai) {
    if (pazymiai.empty()) return 0.0f;
    int suma = 0;
    for (int paz : pazymiai) suma += paz;
    return static_cast<float>(suma) / pazymiai.size();
}

float Vidurkis(const std::list<int>& pazymiai) {
    if (pazymiai.empty()) return 0.0f;
    int suma = 0;
    for (int paz : pazymiai) suma += paz;
    return static_cast<float>(suma) / pazymiai.size();
}

// ==========================================================
// Ivesti egzamina
// ==========================================================
int ivestiEgzamina() {
    int egz;
    while (true) {
        cout << "Iveskite egzamino pazymi (1-10): ";
        if (!(cin >> egz)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Klaida: iveskite skaiciu nuo 1 iki 10." << endl;
            continue;
        }
        if (egz < 1 || egz > 10) {
            cout << "Egzamino pazymys turi buti tarp 1 ir 10." << endl;
            continue;
        }
        return egz;
    }
}


// Ivesti studenta

Studentas ivesk() {
    std::string vard, pav;
    int pazymiuSkaicius = 0;

    std::cout << "Iveskite varda (arba 0 jei norite baigti): ";
    std::cin >> vard;
    if (vard == "0") return Studentas(); // grazina tuscia objekta

    std::cout << "Iveskite pavarde: ";
    std::cin >> pav;

    std::vector<int> paz;
    char pasirinkimas;

    // Generuoti atsitiktinius ND pazymius?
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
            int m = random(1, 10);
            std::cout << "Sugeneruoto namu darbo nr. " << i + 1 << " pazymys: " << m << std::endl;
            paz.push_back(m);
        }
    }
    else {
        std::cout << "Iveskite namu darbu pazymius po viena. Norint baigti, iveskite ne skaiciu." << std::endl;
        while (true) {
            int m;
            std::cout << "Iveskite namu darba nr. " << pazymiuSkaicius + 1 << ": ";
            if (!(std::cin >> m)) break;
            if (m < 1 || m > 10) continue;
            paz.push_back(m);
            pazymiuSkaicius++;
        }
    }

    // Egzamino pazymys
    int egzas;
    char genEgz;
    do {
        std::cout << "Ar norite generuoti egzamino pazymi? (t/n): ";
        std::cin >> genEgz;
    } while (genEgz != 't' && genEgz != 'T' && genEgz != 'n' && genEgz != 'N');

    if (genEgz == 't' || genEgz == 'T') {
        egzas = random(1, 10);
        std::cout << "Sugeneruotas egzamino pazymys: " << egzas << std::endl;
    }
    else {
        egzas = ivestiEgzamina();
    }

    // Sukuriam Studentas objekta
    Studentas s(vard, pav, egzas, paz);
    s.apskaiciuotiRezultatus();

    return s;
}
