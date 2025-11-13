#include "studentas.h"
#include <algorithm>
#include <numeric>
#include <iomanip>

//konstruktoriai

Studentas::Studentas()
    : vard_(""), pav_(""), paz_(), egzas_(0), rezVid_(0.0f), rezMed_(0.0f) {
}

Studentas::Studentas(const std::string& vard, const std::string& pav, int egz, const std::vector<int>& nd)
    : vard_(vard), pav_(pav), paz_(nd), egzas_(egz), rezVid_(0.0f), rezMed_(0.0f) {
}

Studentas::Studentas(std::istream& is) {
    skaitytiStudenta(is);
}

//destruktorius

Studentas::~Studentas() {
    vard_.clear();
    pav_.clear();
    paz_.clear();
    egzas_ = 0;
    rezVid_ = 0.0f;
    rezMed_ = 0.0f;
}
//get'eriai

std::string Studentas::vardas() const { return vard_; }
std::string Studentas::pavarde() const { return pav_; }
const std::vector<int>& Studentas::pazymiai() const { return paz_; }
int Studentas::egzaminas() const { return egzas_; }
float Studentas::getVid() const { return rezVid_; }
float Studentas::getMed() const { return rezMed_; }


std::istream& Studentas::skaitytiStudenta(std::istream& is) {
    is >> vard_ >> pav_;
    paz_.clear();

    int paz;
    
    while (is >> paz) {
        paz_.push_back(paz);
    }

    
    if (!paz_.empty()) {
        egzas_ = paz_.back();
        paz_.pop_back();
    }
    else {
        egzas_ = 0;
    }

    
    is.clear();

    apskaiciuotiRezultatus();
    return is;
}


float Studentas::skaiciuotiVidurki() const {
    if (paz_.empty()) return 0.0f;
    float suma = std::accumulate(paz_.begin(), paz_.end(), 0);
    float vid = suma / paz_.size();
    return 0.4f * vid + 0.6f * egzas_;
}

float Studentas::skaiciuotiMediana() const {
    if (paz_.empty()) return 0.0f;

    std::vector<int> kopija = paz_;
    std::sort(kopija.begin(), kopija.end());
    float med;

    size_t n = kopija.size();
    if (n % 2 == 0)
        med = (kopija[n / 2 - 1] + kopija[n / 2]) / 2.0f;
    else
        med = kopija[n / 2];

    return 0.4f * med + 0.6f * egzas_;
}

void Studentas::apskaiciuotiRezultatus() {
    rezVid_ = skaiciuotiVidurki();
    rezMed_ = skaiciuotiMediana();
}



bool pagalVarda(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

bool pagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}

bool pagalGalutini(const Studentas& a, const Studentas& b) {
    return a.getVid() < b.getVid();
}
