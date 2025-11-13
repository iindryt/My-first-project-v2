#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <type_traits>
#include "studentas.h"
#include "laikmatis.h"

int random(int min, int max);
float Mediana(const std::vector<int>& pazymiai);
float Mediana(std::list<int> pazymiai);
float Vidurkis(const std::vector<int>& pazymiai);
float Vidurkis(const std::list<int>& pazymiai);
int ivestiEgzamina();
Studentas ivesk();

enum class Balas { Vidurkis, Mediana };

// =============================
// STRATEGIJOS
// =============================
template <typename Container>
void strategija1_paprasta(const Container& visi, Container& kietiakiai, Container& vargsiukai, Balas pagal = Balas::Vidurkis) {
    auto kriterijus = [pagal](const Studentas& s) {
        return (pagal == Balas::Vidurkis) ? (s.getVid() >= 5.0f) : (s.getMed() >= 5.0f);
        };

    for (auto it = visi.begin(); it != visi.end(); ++it) {
        if (kriterijus(*it))
            kietiakiai.push_back(*it);
        else
            vargsiukai.push_back(*it);
    }
}

template <typename Container>
void strategija2_rankine(Container& visi, Container& kietiakiai, Container& vargsiukai, Balas pagal = Balas::Vidurkis) {
    auto kriterijus = [pagal](const Studentas& s) {
        return (pagal == Balas::Vidurkis) ? (s.getVid() >= 5.0f) : (s.getMed() >= 5.0f);
        };

    for (auto it = visi.begin(); it != visi.end();) {
        if (!kriterijus(*it)) {
            vargsiukai.push_back(*it);
            it = visi.erase(it);
        }
        else {
            ++it;
        }
    }

    kietiakiai = visi;
}

template <typename Container>
void strategija1(const Container& visi, Container& kietiakiai, Container& vargsiukai, Balas pagal = Balas::Vidurkis) {
    auto kriterijus = [pagal](const Studentas& s) {
        return (pagal == Balas::Vidurkis) ? (s.getVid() >= 5.0f) : (s.getMed() >= 5.0f);
        };

    std::copy_if(visi.begin(), visi.end(), std::back_inserter(kietiakiai), kriterijus);
    std::copy_if(visi.begin(), visi.end(), std::back_inserter(vargsiukai),
        [pagal](const Studentas& s) {
            return !((pagal == Balas::Vidurkis) ? (s.getVid() >= 5.0f) : (s.getMed() >= 5.0f));
        });
}

template <typename Container>
void strategija2(Container& visi, Container& kietiakiai, Container& vargsiukai, Balas pagal = Balas::Vidurkis) {
    auto kriterijus = [pagal](const Studentas& s) {
        return (pagal == Balas::Vidurkis) ? (s.getVid() >= 5.0f) : (s.getMed() >= 5.0f);
        };

    auto it = std::partition(visi.begin(), visi.end(), kriterijus);

    kietiakiai.assign(visi.begin(), it);
    vargsiukai.assign(it, visi.end());
    visi = kietiakiai;
}

// =============================
// STRATEGIJA 3 (testavimas)
// =============================
template <typename Container>
void strategija3(Container& visi, Container& kietiakiai, Container& vargsiukai, Balas pagal, int& pasirinktaTikra) {
    bool yraVector = std::is_same_v<Container, std::vector<Studentas>>;

    if (yraVector) {
        Container k1, v1, k2, v2;
        Container visiKopija = visi;

        std::cout << "Testuojamos rankines strategijos (vektoriui):\n";

        Laikmatis t1;
        strategija1_paprasta(visi, k1, v1, pagal);
        double laikas1 = t1.praejes_laikas();

        Laikmatis t2;
        strategija2_rankine(visiKopija, k2, v2, pagal);
        double laikas2 = t2.praejes_laikas();

        std::cout << "Strategija 1 (rankine) laikas: " << laikas1 << " s\n";
        std::cout << "Strategija 2 (rankine) laikas: " << laikas2 << " s\n";

        int greitesne = (laikas1 <= laikas2) ? 1 : 2;
        pasirinktaTikra = greitesne;

        std::cout << "Pasirinkta greitesne rankine strategija: " << greitesne << "\n";

        Laikmatis tSTL;
        if (greitesne == 1)
            strategija1(visi, kietiakiai, vargsiukai, pagal);
        else
            strategija2(visi, kietiakiai, vargsiukai, pagal);

        double laikasSTL = tSTL.praejes_laikas();
    }
    else {
        Container k1, v1, k2, v2;
        Container visiKopija = visi;

        std::cout << "Testuojamos rankines strategijos (list/kitam konteineriui):\n";

        Laikmatis t1;
        strategija1_paprasta(visi, k1, v1, pagal);
        double laikas1 = t1.praejes_laikas();

        Laikmatis t2;
        strategija2_rankine(visiKopija, k2, v2, pagal);
        double laikas2 = t2.praejes_laikas();

        if (laikas1 <= laikas2) {
            kietiakiai = std::move(k1);
            vargsiukai = std::move(v1);
            pasirinktaTikra = 1;
        }
        else {
            kietiakiai = std::move(k2);
            vargsiukai = std::move(v2);
            pasirinktaTikra = 2;
        }
    }
}

// =============================
// ATMINTIES SKAI?IAVIMAS
// =============================
template <typename Container>
size_t skaiciuotiAtminti(const Container& konteineris) {
    bool arList = std::is_same_v<Container, std::list<Studentas>>;
    size_t dydis = sizeof(Studentas);
    if (arList) dydis += 2 * sizeof(void*);
    return konteineris.size() * dydis;
}

// =============================
// I?VEDIMAS ? FAILUS
// =============================
template <typename Container>
void irasytiIFailus(const Container& kietiakiai,
    const Container& vargsiukai,
    Balas pagal)
{
    Container kietiakiaiR = kietiakiai;
    Container vargsiukaiR = vargsiukai;

    auto rikiuotiPagalBalus = [pagal](auto& sarasas) {
        if constexpr (std::is_same_v<std::decay_t<decltype(sarasas)>, std::vector<Studentas>>) {
            std::sort(sarasas.begin(), sarasas.end(), [&](const Studentas& a, const Studentas& b) {
                float ga = (pagal == Balas::Vidurkis) ? a.getVid() : a.getMed();
                float gb = (pagal == Balas::Vidurkis) ? b.getVid() : b.getMed();
                return ga < gb;
                });
        }
        else if constexpr (std::is_same_v<std::decay_t<decltype(sarasas)>, std::list<Studentas>>) {
            sarasas.sort([&](const Studentas& a, const Studentas& b) {
                float ga = (pagal == Balas::Vidurkis) ? a.getVid() : a.getMed();
                float gb = (pagal == Balas::Vidurkis) ? b.getVid() : b.getMed();
                return ga < gb;
                });
        }
        };

    rikiuotiPagalBalus(kietiakiaiR);
    rikiuotiPagalBalus(vargsiukaiR);

    std::ofstream outK("kietiakiai.txt");
    std::ofstream outV("vargsiukai.txt");

    for (const auto& s : kietiakiaiR)
        outK << s.vardas() << " " << s.pavarde() << " "
        << ((pagal == Balas::Vidurkis) ? s.getVid() : s.getMed()) << "\n";

    for (const auto& s : vargsiukaiR)
        outV << s.vardas() << " " << s.pavarde() << " "
        << ((pagal == Balas::Vidurkis) ? s.getVid() : s.getMed()) << "\n";
}





// ==========================================================
// Templatine funkcija spausdinimui ir rusiavimui
// ==========================================================
template <typename Container>
void spausdintiRezultatusIrRusiavima(Container& Grupe) {
    using std::cout;
    using std::endl;
    using std::left;
    using std::setw;
    using std::fixed;
    using std::setprecision;
    using std::ofstream;
    using std::string;

    if (Grupe.empty()) {
        cout << "Studentu sarasas tuscias." << endl;
        return;
    }

    // --- Rikiavimas pagal varda kaip default ---
    if constexpr (std::is_same_v<Container, std::vector<Studentas>>)
        std::sort(Grupe.begin(), Grupe.end(), pagalVarda);
    else if constexpr (std::is_same_v<Container, std::list<Studentas>>)
        Grupe.sort(pagalVarda);


    Laikmatis laikRusiavimui;
    double rusiavimoLaikas = laikRusiavimui.praejes_laikas();

    // --- Galutinio balo skaiciavimo pasirinkimas ---
    int pasirinkimas = 0;
    while (pasirinkimas < 1 || pasirinkimas > 3) {
        cout << "\nPasirinkite galutinio balo skaiciavimo metoda:\n";
        cout << "1 - Vidurkis\n2 - Mediana\n3 - Abu (vidurkis ir mediana)\n";
        cout << "Jusu pasirinkimas: ";
        std::cin >> pasirinkimas;
        if (pasirinkimas < 1 || pasirinkimas > 3)
            cout << "Neteisingas pasirinkimas, bandykite dar karta.\n";
    }

    Laikmatis laikIrasymui;
    ofstream fout("rezultatai.txt");
    if (!fout) { cout << "Klaida: nepavyko sukurti rezultatu failo." << endl; return; }

    if (pasirinkimas == 1) {
        fout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << "Galutinis (Vid.)" << endl;
        fout << string(45, '-') << endl;
        for (const auto& s : Grupe)
            fout << left << setw(15) << s.pavarde() << setw(15) << s.vardas()
            << fixed << setprecision(2) << s.getVid() << endl;
    }
    else if (pasirinkimas == 2) {
        fout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << "Galutinis (Med.)" << endl;
        fout << string(45, '-') << endl;
        for (const auto& s : Grupe)
            fout << left << setw(15) << s.pavarde() << setw(15) << s.vardas()
            << fixed << setprecision(2) << s.getMed() << endl;
    }
    else {
        fout << left << setw(15) << "Pavarde" << setw(15) << "Vardas"
            << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
        fout << string(70, '-') << endl;
        for (const auto& s : Grupe)
            fout << left << setw(15) << s.pavarde() << setw(15) << s.vardas()
            << setw(20) << fixed << setprecision(2) << s.getVid()
            << setw(20) << fixed << setprecision(2) << s.getMed() << endl;
    }
    fout.close();

    cout << "Rezultatai issaugoti faile 'rezultatai.txt'\n";
    cout << "Rusiavimas truko: " << rusiavimoLaikas << " sek.\n";
    cout << "Isvedimas i 'rezultatai.txt' truko: " << laikIrasymui.praejes_laikas() << " sek.\n";

    // --- Strategijos pasirinkimas ---
    int strategija = 0;
    while (strategija < 1 || strategija > 3) {
        cout << "\nPasirinkite strategija (1, 2 arba 3, 3 - palyginti laikus): ";
        std::cin >> strategija;
        if (strategija < 1 || strategija > 3)
            cout << "Neteisingas pasirinkimas, bandykite dar karta.\n";
    }

    // --- Pagal ka skirstyti studentus ---
    int baloPasirinkimas = 0;
    while (baloPasirinkimas < 1 || baloPasirinkimas > 2) {
        cout << "Pasirinkite pagal ka skirstyti studentus:\n";
        cout << "1 - Vidurkis\n2 - Mediana\n";
        cout << "Jusu pasirinkimas: ";
        std::cin >> baloPasirinkimas;
        if (baloPasirinkimas < 1 || baloPasirinkimas > 2)
            cout << "Neteisingas pasirinkimas, bandykite dar karta.\n";
    }

    Container kietiakiai, vargsiukai;
    double laikas1 = 0, laikas2 = 0;
    Balas pagal = (baloPasirinkimas == 1) ? Balas::Vidurkis : Balas::Mediana;

    if (strategija == 1) {
        Laikmatis t;
        strategija1(Grupe, kietiakiai, vargsiukai, pagal);
        laikas1 = t.praejes_laikas();
        cout << "Strategija 1 truko: " << laikas1 << " s\n";
    }
    else if (strategija == 2) {
        Laikmatis t;
        strategija2(Grupe, kietiakiai, vargsiukai, pagal);
        laikas2 = t.praejes_laikas();
        cout << "Strategija 2 truko: " << laikas2 << " s\n";
    }
    else {
        Container k1, v1, k2, v2;
        Laikmatis t1, t2;
        strategija1(Grupe, k1, v1, pagal); laikas1 = t1.praejes_laikas();
        strategija2(Grupe, k2, v2, pagal); laikas2 = t2.praejes_laikas();

        cout << "Strategija 1 truko: " << laikas1 << " s\n";
        cout << "Strategija 2 truko: " << laikas2 << " s\n";

        if (laikas1 <= laikas2) { kietiakiai = k1; vargsiukai = v1; cout << "Pasirinkta strategija 1 (greitesne)\n"; }
        else { kietiakiai = k2; vargsiukai = v2; cout << "Pasirinkta strategija 2 (greitesne)\n"; }
    }

    // --- Rikiavimas kietiakiai / vargsiukai ---
    int rikiavimoPasirinkimas = 0;
    while (true) {
        std::cout << "\nKaip norite, kad butu surikiuoti 'kietiakiai' ir 'vargsiukai'?\n";
        std::cout << "1 - Pagal varda\n2 - Pagal pavarde\n3 - Pagal galutini bala\n";
        std::cout << "Jusu pasirinkimas: ";
        std::cin >> rikiavimoPasirinkimas;

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Klaida: iveskite 1, 2 arba 3.\n";
            continue;
        }

        if (rikiavimoPasirinkimas < 1 || rikiavimoPasirinkimas > 3) {
            std::cout << "Klaida: iveskite 1, 2 arba 3.\n";
            continue;
        }

        break;
    }

    auto rikiuotiPagal = [&](Container& sarasas) {
        switch (rikiavimoPasirinkimas) {
        case 1: // pagal varda
            if constexpr (std::is_same_v<Container, std::vector<Studentas>>)
                std::sort(sarasas.begin(), sarasas.end(), pagalVarda);
            else
                sarasas.sort(pagalVarda);
            break;
        case 2: // pagal pavarde
            if constexpr (std::is_same_v<Container, std::vector<Studentas>>)
                std::sort(sarasas.begin(), sarasas.end(), pagalPavarde);
            else
                sarasas.sort(pagalPavarde);
            break;
        case 3: // pagal galutini bala
            if constexpr (std::is_same_v<Container, std::vector<Studentas>>)
                std::sort(sarasas.begin(), sarasas.end(), pagalGalutini);
            else
                sarasas.sort(pagalGalutini);
            break;
        default:
            cout << "Neteisingas pasirinkimas, paliekama be papildomo rikiavimo.\n";
        }
        };


    rikiuotiPagal(kietiakiai);
    rikiuotiPagal(vargsiukai);

    // --- Isvedimas i failus ---
    Laikmatis laikIrasymui2;
    ofstream outKiet("kietiakiai.txt");
    ofstream outVarg("vargsiukai.txt");

    if (!outKiet || !outVarg) {
        cout << "Klaida: nepavyko sukurti failu." << endl;
        return;
    }

    auto spausdinti = [](ofstream& fout, const Container& sarasas, bool pagalVidurki) {
        string antraste = pagalVidurki ? "Galutinis (Vid.)" : "Galutinis (Med.)";
        fout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << antraste << endl;
        fout << string(45, '-') << endl;

        for (const auto& s : sarasas) {
            float balas = pagalVidurki ? s.getVid() : s.getMed();
            fout << left << setw(15) << s.pavarde() << setw(15) << s.vardas()
                << fixed << setprecision(2) << balas << endl;
        }
        };

    bool pagalVidurki = (baloPasirinkimas == 1);
    spausdinti(outKiet, kietiakiai, pagalVidurki);
    spausdinti(outVarg, vargsiukai, pagalVidurki);

    outKiet.close();
    outVarg.close();

    cout << "Studentai surusiuoti ir issaugoti:\n";
    cout << " - kietiakiai.txt: " << kietiakiai.size() << " studentu\n";
    cout << " - vargsiukai.txt: " << vargsiukai.size() << " studentu\n";
    cout << "Rusiavimas i kietiakus/vargsiukus truko: " << laikRusiavimui.praejes_laikas() << " sek.\n";
    cout << "Isvedimas i failus truko: " << laikIrasymui2.praejes_laikas() << " sek.\n";
}




#endif // FUNKCIJOS_H


