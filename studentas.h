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
    //konstruktorius
    Studentas();
    Studentas(const std::string& vard, const std::string& pav, int egz, const std::vector<int>& nd);
    explicit Studentas(std::istream& is);

    //destruktorius
    ~Studentas();

    
    // get'eriai
    
    std::string vardas() const;
    std::string pavarde() const;
    const std::vector<int>& pazymiai() const;
    int egzaminas() const;
    float getVid() const;
    float getMed() const;

    std::istream& skaitytiStudenta(std::istream& is);

   
    float skaiciuotiVidurki() const;
    float skaiciuotiMediana() const;
    void apskaiciuotiRezultatus();
};

bool pagalVarda(const Studentas& a, const Studentas& b);
bool pagalPavarde(const Studentas& a, const Studentas& b);
bool pagalGalutini(const Studentas& a, const Studentas& b);
