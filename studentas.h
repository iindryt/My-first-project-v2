#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include <iostream>

// Funkcijos, kurios apskaičiuoja vidurkį ar medianą
double VidurkisVector(const std::vector<int>& paz);
double MedianaVector(const std::vector<int>& paz);

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> nd_;
    int egzaminas_;
    float rezVid_;
    float rezMed_;

public:
    // Konstruktoriai
    Studentas();                        // default konstruktorius
    Studentas(const std::string& vardas, const std::string& pavarde,
        const std::vector<int>& nd, int egzaminas); // parametrinis
    Studentas(std::istream& is);        // srauto konstruktorius

    // Destruktorius (pilnai realizuotas)
    ~Studentas();

    // Get'eriai
    std::string vardas() const;
    std::string pavarde() const;
    std::vector<int> nd() const;
    int egzaminas() const;
    float galVid() const;
    float galMed() const;

    // Member funkcijos
    std::istream& readStudent(std::istream& is);
    double galBalas(double(*f)(const std::vector<int>&)) const;
    double galBalasVidurkis() const;
    double galBalasMediana() const;

    // Operatoriai
    bool operator<(const Studentas& kitas) const;
};
// Comparatoriai kaip funkcijos
bool compare(const Studentas& a, const Studentas& b);               
bool comparePagalPavarde(const Studentas& a, const Studentas& b);  
bool comparePagalEgza(const Studentas& a, const Studentas& b);

#endif // STUDENTAS_H
