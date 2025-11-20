#include "studentas.h"
#include <algorithm>
#include <numeric>
#include <limits>
#include <iostream>

// ==========================
// Konstruktoriai
// ==========================
Studentas::Studentas()
    : Zmogus(), paz_(), egzas_(0), rezVid_(0.0f), rezMed_(0.0f) {
}

Studentas::Studentas(const std::string& vard, const std::string& pav, int egz, const std::vector<int>& nd)
    : Zmogus(vard, pav), paz_(nd), egzas_(egz), rezVid_(0.0f), rezMed_(0.0f) {
}

Studentas::Studentas(std::istream& is)
    : rezVid_(0.0f), rezMed_(0.0f) {
    skaitytiStudenta(is);
}

// ==========================
// Rule of Three
// ==========================
Studentas::Studentas(const Studentas& kitas)
    : Zmogus(kitas), paz_(kitas.paz_), egzas_(kitas.egzas_),
    rezVid_(kitas.rezVid_), rezMed_(kitas.rezMed_) {
}

Studentas& Studentas::operator=(const Studentas& kitas) {
    if (this != &kitas) {
        Zmogus::operator=(kitas);
        paz_ = kitas.paz_;
        egzas_ = kitas.egzas_;
        rezVid_ = kitas.rezVid_;
        rezMed_ = kitas.rezMed_;
    }
    return *this;
}

Studentas::~Studentas() {
    paz_.clear();
    egzas_ = 0;
    rezVid_ = 0.0f;
    rezMed_ = 0.0f;
}

// ==========================
// Get'eriai
// ==========================
const std::vector<int>& Studentas::pazymiai() const { return paz_; }
int Studentas::egzaminas() const { return egzas_; }
float Studentas::getVid() const { return rezVid_; }
float Studentas::getMed() const { return rezMed_; }

// ==========================
// Skaitymas
// ==========================
std::istream& Studentas::skaitytiStudenta(std::istream& is) {
    is >> vard_ >> pav_;
    paz_.clear();
    int paz;

    while (true) {
        bool eiluteBaigta = false;
        while (!eiluteBaigta && is >> paz) {
            if (paz < 1 || paz > 10) {
                std::cerr << "Klaida: pazymys " << paz << " turi buti nuo 1 iki 10!\n";
                if (is.fail()) {
                    is.clear();
                    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                continue;
            }
            paz_.push_back(paz);
            if (is.peek() == '\n' || is.eof()) {
                eiluteBaigta = true;
                break;
            }
        }
        if (is.fail()) {
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        break;
    }

    if (!paz_.empty()) {
        egzas_ = paz_.back();
        paz_.pop_back();
    }
    else {
        egzas_ = 0;
    }

    apskaiciuotiRezultatus();
    return is;
}

void Studentas::skaitytiInfo(std::istream& is) { skaitytiStudenta(is); }

void Studentas::spausdintiInfo(std::ostream& os) const {
    os << vard_ << " " << pav_ << " |Pazymiai: ";
    for (int p : paz_) os << p << " ";
    os << "|Egzamino pazymys: " << egzas_ << " ";
    os << "|Galutinis (Vid.): " << rezVid_ << " ";
    os << "|Galutinis (Med.): " << rezMed_;
}

// ==========================
// Vidurkio ir medianos skaiciavimas
// ==========================
float Studentas::skaiciuotiVidurki() const {
    if (paz_.empty()) return 0.0f;
    float suma = std::accumulate(paz_.begin(), paz_.end(), 0);
    return suma / paz_.size();
}

float Studentas::skaiciuotiMediana() const {
    if (paz_.empty()) return 0.0f;
    std::vector<int> kopija = paz_;
    std::sort(kopija.begin(), kopija.end());
    size_t n = kopija.size();
    if (n % 2 == 0)
        return (kopija[n / 2 - 1] + kopija[n / 2]) / 2.0f;
    else
        return kopija[n / 2];
}

// ==========================
// Galutinis rezultatas
// ==========================
void Studentas::apskaiciuotiRezultatus() {
    rezVid_ = 0.4f * skaiciuotiVidurki() + 0.6f * egzas_;
    rezMed_ = 0.4f * skaiciuotiMediana() + 0.6f * egzas_;
}

// ==========================
// Operatoriai
// ==========================
std::istream& operator>>(std::istream& is, Studentas& s) { return s.skaitytiStudenta(is); }
std::ostream& operator<<(std::ostream& os, const Studentas& s) { s.spausdintiInfo(os); return os; }

// ==========================
// Rikiavimo funkcijos
// ==========================
bool pagalVarda(const Studentas& a, const Studentas& b) { return a.vardas() < b.vardas(); }
bool pagalPavarde(const Studentas& a, const Studentas& b) { return a.pavarde() < b.pavarde(); }
bool pagalGalutini(const Studentas& a, const Studentas& b) { return a.getVid() < b.getVid(); }
