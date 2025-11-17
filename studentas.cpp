#include "studentas.h"
#include <algorithm>
#include <numeric>

// Konstruktoriai
Studentas::Studentas()
    : vard_(""), pav_(""), paz_(), egzas_(0), rezVid_(0.0f), rezMed_(0.0f) {
}

Studentas::Studentas(const std::string& vard, const std::string& pav, int egz, const std::vector<int>& nd)
    : vard_(vard), pav_(pav), paz_(nd), egzas_(egz), rezVid_(0.0f), rezMed_(0.0f) {
}

Studentas::Studentas(std::istream& is) {
    skaitytiStudenta(is);
}

// Kopijavimo konstruktorius
Studentas::Studentas(const Studentas& kitas)
    : vard_(kitas.vard_), pav_(kitas.pav_), paz_(kitas.paz_),
    egzas_(kitas.egzas_), rezVid_(kitas.rezVid_), rezMed_(kitas.rezMed_) {
}

// Kopijavimo priskyrimo operatorius
Studentas& Studentas::operator=(const Studentas& kitas) {
    if (this != &kitas) {
        vard_ = kitas.vard_;
        pav_ = kitas.pav_;
        paz_ = kitas.paz_;
        egzas_ = kitas.egzas_;
        rezVid_ = kitas.rezVid_;
        rezMed_ = kitas.rezMed_;
    }
    return *this;
}

// Destruktorius su clear()
Studentas::~Studentas() {
    vard_.clear();
    pav_.clear();
    paz_.clear();
    egzas_ = 0;
    rezVid_ = 0.0f;
    rezMed_ = 0.0f;
}

// Get'eriai
std::string Studentas::vardas() const { return vard_; }
std::string Studentas::pavarde() const { return pav_; }
const std::vector<int>& Studentas::pazymiai() const { return paz_; }
int Studentas::egzaminas() const { return egzas_; }
float Studentas::getVid() const { return rezVid_; }
float Studentas::getMed() const { return rezMed_; }

// Skaitymas i? srauto
std::istream& Studentas::skaitytiStudenta(std::istream& is) {
    is >> vard_ >> pav_;
    paz_.clear();
    int paz;
    while (is >> paz) {
        paz_.push_back(paz);
        if (is.peek() == '\n' || is.eof()) break;
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

// Vidurkio ir medianos skai?iavimas
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

// Galutini? rezultat? apskai?iavimas su svoriais
void Studentas::apskaiciuotiRezultatus() {
    rezVid_ = 0.4f * skaiciuotiVidurki() + 0.6f * egzas_;
    rezMed_ = 0.4f * skaiciuotiMediana() + 0.6f * egzas_;
}

// Ivesties/isvesties operatoriai
std::istream& operator>>(std::istream& is, Studentas& s) {
    return s.skaitytiStudenta(is);
}

std::ostream& operator<<(std::ostream& os, const Studentas& s) {
    os << s.vard_ << " " << s.pav_ << " Egz: " << s.egzas_
        << " Vid: " << s.rezVid_ << " Med: " << s.rezMed_
        << " Pazymiai: ";
    for (int p : s.paz_) os << p << " ";
    return os;
}

// Pagalbines funkcijos rikiavimui
bool pagalVarda(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

bool pagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}

bool pagalGalutini(const Studentas& a, const Studentas& b) {
    return a.getVid() < b.getVid();
}
