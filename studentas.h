#pragma once
#include <string>
#include <vector>
#include <iostream>

class Studentas {
private:
    std::string vard_;
    std::string pav_;
    std::vector<int> paz_;
    int egzas_;
    float rezVid_;
    float rezMed_;

public:
    // Konstruktoriai
    Studentas();
    Studentas(const std::string& vard, const std::string& pav, int egz, const std::vector<int>& nd);
    explicit Studentas(std::istream& is);

    // Kopijavimo konstruktorius (Rule of Three)
    Studentas(const Studentas& kitas);

    // Kopijavimo priskyrimo operatorius (Rule of Three)
    Studentas& operator=(const Studentas& kitas);

    // Destruktorius
    ~Studentas();

    // Get'eriai
    std::string vardas() const;
    std::string pavarde() const;
    const std::vector<int>& pazymiai() const;
    int egzaminas() const;
    float getVid() const;
    float getMed() const;

    // Skaitymas is srauto
    std::istream& skaitytiStudenta(std::istream& is);

    // Vidurkio ir medianos skaiciavimas
    float skaiciuotiVidurki() const;
    float skaiciuotiMediana() const;

    // Galutinio rezultato apskaiciavimas su svoriais
    void apskaiciuotiRezultatus();

    // Friend operatoriai ivesties/isvesties
    friend std::istream& operator>>(std::istream& is, Studentas& s);
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);
};

// Pagalbines funkcijos rikiavimui
bool pagalVarda(const Studentas& a, const Studentas& b);
bool pagalPavarde(const Studentas& a, const Studentas& b);
bool pagalGalutini(const Studentas& a, const Studentas& b);
