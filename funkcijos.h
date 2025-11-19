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
Studentas generuotiStudentaAutomatiskai();
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
template <typename Container>
void spausdintiRezultatusIrRusiavima(Container& Grupe) {
    using namespace std;

    if (Grupe.empty()) {
        cout << "Studentu sarasas tuscias.\n";
        return;
    }

    // ================================
    // RIKIUOJAME PAGAL VARDA (default)
    // ================================
    Laikmatis laikRusiavimui;

    if constexpr (is_same_v<Container, vector<Studentas>>)
        sort(Grupe.begin(), Grupe.end(), pagalVarda);
    else
        Grupe.sort(pagalVarda);

    double rusiavimoLaikas = laikRusiavimui.praejes_laikas();


    // ================================
    // PASIRINKIMAS – EKRANAS AR FAILAS
    // ================================
    int pasirinkimasRezultatu = 0;
    while (pasirinkimasRezultatu < 1 || pasirinkimasRezultatu > 2) {
        cout << "\nKur norite issaugoti rezultatus?\n"
            << "1 - I ekrana\n2 - I faila 'rezultatai.txt'\n"
            << "Jusu pasirinkimas: ";
        cin >> pasirinkimasRezultatu;
        if (!cin) { cin.clear(); cin.ignore(1000, '\n'); }
    }

    // ================================
    // PASIRINKIMAS – VIDURKIS / MEDIANA
    // ================================
    int pasirinkimasBalo = 0;
    while (pasirinkimasBalo < 1 || pasirinkimasBalo > 3) {
        cout << "\nPasirinkite galutinio balo skaiciavimo metoda:\n"
            << "1 - Vidurkis\n2 - Mediana\n3 - Abu\n"
            << "Jusu pasirinkimas: ";
        cin >> pasirinkimasBalo;
        if (!cin) { cin.clear(); cin.ignore(1000, '\n'); }
    }

    // ================================
    // I?VEDAME REZULTATUS
    // ================================
    Laikmatis laikIrasymui;

    auto spausdintiRez = [&](auto& out) {
        if (pasirinkimasBalo == 1) {
            out << left << setw(15) << "Pavarde" << setw(15)
                << "Vardas" << "Galutinis (Vid.)\n"
                << string(45, '-') << "\n";
            for (const auto& s : Grupe)
                out << left << setw(15) << s.pavarde()
                << setw(15) << s.vardas()
                << fixed << setprecision(2) << s.getVid() << "\n";
        }
        else if (pasirinkimasBalo == 2) {
            out << left << setw(15) << "Pavarde" << setw(15)
                << "Vardas" << "Galutinis (Med.)\n"
                << string(45, '-') << "\n";
            for (const auto& s : Grupe)
                out << left << setw(15) << s.pavarde()
                << setw(15) << s.vardas()
                << fixed << setprecision(2) << s.getMed() << "\n";
        }
        else {
            out << left << setw(15) << "Pavarde" << setw(15)
                << "Vardas" << setw(20) << "Galutinis (Vid.)"
                << setw(20) << "Galutinis (Med.)\n"
                << string(70, '-') << "\n";
            for (const auto& s : Grupe)
                out << left << setw(15) << s.pavarde()
                << setw(15) << s.vardas()
                << setw(20) << fixed << setprecision(2) << s.getVid()
                << setw(20) << fixed << setprecision(2) << s.getMed() << "\n";
        }
        };

    if (pasirinkimasRezultatu == 2) {
        ofstream out("rezultatai.txt");
        spausdintiRez(out);
    }
    else {
        spausdintiRez(cout);
    }

    cout << "Rusiavimas truko: " << fixed << setprecision(7)
        << rusiavimoLaikas << " sek.\n";
    cout << "Isvedimas truko: " << fixed << setprecision(7)
        << laikIrasymui.praejes_laikas() << " sek.\n";


    // ============================================
    // PASIRINKIMAS – PAGAL KA SKIRSTYTI (VID/MED)
    // ============================================
    int baloPasirinkimas = 0;
    while (baloPasirinkimas < 1 || baloPasirinkimas > 2) {
        cout << "\nPasirinkite pagal ka skirstyti studentus:\n"
            << "1 - Vidurkis\n2 - Mediana\n"
            << "Jusu pasirinkimas: ";
        cin >> baloPasirinkimas;
        if (!cin) { cin.clear(); cin.ignore(1000, '\n'); }
    }


    // ==========================
    // PAPRASTAS SKIRSTYMAS
    // ==========================
    Container kietiakiai, vargsiukai;

    Laikmatis laikSkirstymui;

    for (const auto& s : Grupe) {
        double balas = (baloPasirinkimas == 1) ? s.getVid() : s.getMed();
        if (balas >= 5.0)
            kietiakiai.push_back(s);
        else
            vargsiukai.push_back(s);
    }

    double skirstymoLaikas = laikSkirstymui.praejes_laikas();


    // ==========================
    // PASIRINKIMAS – RIKIAVIMAS
    // ==========================
    int rikiavimoPasirinkimas = 0;
    while (true) {
        cout << "\nKaip norite rikiuoti 'kietiakiai' ir 'vargsiukai'?\n"
            << "1 - Pagal varda\n2 - Pagal pavarde\n3 - Pagal galutini bala\n"
            << "Jusu pasirinkimas: ";
        cin >> rikiavimoPasirinkimas;

        if (!cin) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        if (rikiavimoPasirinkimas >= 1 && rikiavimoPasirinkimas <= 3) break;

        cout << "Klaida: iveskite 1, 2 arba 3.\n";
    }

    auto rikiuotiPagal = [&](Container& sar) {
        switch (rikiavimoPasirinkimas) {
        case 1:
            if constexpr (is_same_v<Container, vector<Studentas>>)
                sort(sar.begin(), sar.end(), pagalVarda);
            else sar.sort(pagalVarda);
            break;
        case 2:
            if constexpr (is_same_v<Container, vector<Studentas>>)
                sort(sar.begin(), sar.end(), pagalPavarde);
            else sar.sort(pagalPavarde);
            break;
        case 3:
            if constexpr (is_same_v<Container, vector<Studentas>>)
                sort(sar.begin(), sar.end(), pagalGalutini);
            else sar.sort(pagalGalutini);
            break;
        }
        };

    rikiuotiPagal(kietiakiai);
    rikiuotiPagal(vargsiukai);


    // ==========================
    // ISVEDIMAS I FAILUS
    // ==========================
    Laikmatis laikIrasymui2;

    ofstream outK("kietiakiai.txt");
    ofstream outV("vargsiukai.txt");

    auto spausdintiFailui = [&](ofstream& out, const Container& sar) {
        string antraste = (baloPasirinkimas == 1)
            ? "Galutinis (Vid.)" : "Galutinis (Med.)";

        out << left << setw(15) << "Pavarde" << setw(15)
            << "Vardas" << antraste << "\n"
            << string(45, '-') << "\n";

        for (const auto& s : sar) {
            double balas = (baloPasirinkimas == 1) ? s.getVid() : s.getMed();
            out << left << setw(15) << s.pavarde()
                << setw(15) << s.vardas()
                << fixed << setprecision(2) << balas << "\n";
        }
        };

    spausdintiFailui(outK, kietiakiai);
    spausdintiFailui(outV, vargsiukai);

    cout << "\nStudentai surusiuoti ir issaugoti:\n";
    cout << " - kietiakiai.txt: " << kietiakiai.size() << " studentu\n";
    cout << " - vargsiukai.txt: " << vargsiukai.size() << " studentu\n";
    cout << "Skirstymas i grupes truko: "
        << fixed << setprecision(7) << skirstymoLaikas << " sek.\n";
    cout << "Isvedimas i failus truko: "
        << fixed << setprecision(7) << laikIrasymui2.praejes_laikas() << " sek.\n";
}









#endif // FUNKCIJOS_H



