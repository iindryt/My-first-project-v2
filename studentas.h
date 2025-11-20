#pragma once
#include "zmogus.h"
#include <vector>
#include <iostream>

class Studentas : public Zmogus {
private:
    std::vector<int> paz_;
    int egzas_;
    float rezVid_;
    float rezMed_;

public:
    Studentas();
    Studentas(const std::string& vard, const std::string& pav, int egz, const std::vector<int>& nd);
    explicit Studentas(std::istream& is);

    Studentas(const Studentas& kitas);
    Studentas& operator=(const Studentas& kitas);
    ~Studentas() override;

    const std::vector<int>& pazymiai() const;
    int egzaminas() const;
    float getVid() const;
    float getMed() const;

    std::istream& skaitytiStudenta(std::istream& is);
    void skaitytiInfo(std::istream& is) override;
    void spausdintiInfo(std::ostream& os) const override;

    float skaiciuotiVidurki() const;
    float skaiciuotiMediana() const;

    void apskaiciuotiRezultatus();

    friend std::istream& operator>>(std::istream& is, Studentas& s);
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);
};

bool pagalVarda(const Studentas& a, const Studentas& b);
bool pagalPavarde(const Studentas& a, const Studentas& b);
bool pagalGalutini(const Studentas& a, const Studentas& b);
