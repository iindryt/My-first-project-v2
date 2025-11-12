#include "studentas.h"
#include "funkcijos.h"
#include <sstream>
#include <algorithm>
#include <iostream>

// ========================= Konstruktoriai =========================
Studentas::Studentas()
    : vardas_(""), pavarde_(""), egzaminas_(0), rezVid_(0), rezMed_(0) {
    nd_.clear(); // „aktyvus“ veiksmas
}

Studentas::Studentas(const std::string& vardas, const std::string& pavarde,
    const std::vector<int>& nd, int egzaminas)
    : vardas_(vardas), pavarde_(pavarde), nd_(nd), egzaminas_(egzaminas) {
    float vid = static_cast<float>(VidurkisVector(nd_));
    float med = static_cast<float>(MedianaVector(nd_));
    rezVid_ = 0.4f * vid + 0.6f * egzaminas_;
    rezMed_ = 0.4f * med + 0.6f * egzaminas_;
}

Studentas::Studentas(std::istream& is) {
    readStudent(is);
}

// ========================= Destruktorius =========================
Studentas::~Studentas() {
    // aktyvus destruktorius, atlaisvina resursus
    nd_.clear();
    vardas_.clear();
    pavarde_.clear();
    egzaminas_ = 0;
    rezVid_ = rezMed_ = 0.0f;
    // Debug galima ijungti, jei reikia
    // std::cout << "Studentas sunaikintas\n";
}

// ========================= Get'eriai =========================
std::string Studentas::vardas() const { return vardas_; }
std::string Studentas::pavarde() const { return pavarde_; }
std::vector<int> Studentas::nd() const { return nd_; }
int Studentas::egzaminas() const { return egzaminas_; }
float Studentas::galVid() const { return rezVid_; }
float Studentas::galMed() const { return rezMed_; }

// ========================= Member funkcijos =========================
double Studentas::galBalas(double(*f)(const std::vector<int>&)) const {
    double ndRez = f(nd_);
    return 0.4 * ndRez + 0.6 * egzaminas_;
}

double Studentas::galBalasVidurkis() const { return galBalas(VidurkisVector); }
double Studentas::galBalasMediana() const { return galBalas(MedianaVector); }

std::istream& Studentas::readStudent(std::istream& is) {
    std::string eilute;
    if (!std::getline(is, eilute)) return is;

    std::istringstream iss(eilute);
    iss >> vardas_ >> pavarde_;

    nd_.clear();
    int paz;
    while (iss >> paz) {
        if (paz < 1) paz = 1;
        if (paz > 10) paz = 10;
        nd_.push_back(paz);
    }

    if (!nd_.empty()) {
        egzaminas_ = nd_.back();
        nd_.pop_back();
    }
    else {
        egzaminas_ = 1;
    }

    float vid = static_cast<float>(VidurkisVector(nd_));
    float med = static_cast<float>(MedianaVector(nd_));
    rezVid_ = 0.4f * vid + 0.6f * egzaminas_;
    rezMed_ = 0.4f * med + 0.6f * egzaminas_;
    return is;
}

// ========================= Operatoriai =========================
bool Studentas::operator<(const Studentas& kitas) const {
    return pavarde_ < kitas.pavarde_;
}
// ========================= Comparatoriai =========================
bool compare(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

bool comparePagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}

bool comparePagalEgza(const Studentas& a, const Studentas& b) {
    return a.egzaminas() < b.egzaminas();
}
