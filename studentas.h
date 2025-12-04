#pragma once
#include "zmogus.h"
#include <vector>
#include <iostream>

/**
 * @class Studentas
 * @brief Paveldi is Zmogus, reprezentuoja studenta su pazymiais, egzaminu ir galutiniais rezultatais.
 */
class Studentas : public Zmogus {
private:
    std::vector<int> paz_;  /**< Namu darbu pazymiai */
    int egzas_;              /**< Egzamino pazymys */
    float rezVid_;           /**< Galutinis rezultatas pagal vidurki */
    float rezMed_;           /**< Galutinis rezultatas pagal mediana */

public:
    /** @brief Numatytoji konstruktoriaus versija */
    Studentas();

    /**
     * @brief Konstruktorius su duomenimis
     * @param vard Vardas
     * @param pav Pavarde
     * @param egz Egzamino pazymys
     * @param nd Vektorius namu darbu pazymiu
     */
    Studentas(const std::string& vard, const std::string& pav, int egz, const std::vector<int>& nd);

    /**
     * @brief Konstruktorius is srauto
     * @param is Ivesties srautas (std::istream)
     */
    explicit Studentas(std::istream& is);

    /** @brief Kopijavimo konstruktorius */
    Studentas(const Studentas& kitas);

    /** @brief Kopijavimo priskyrimo operatorius */
    Studentas& operator=(const Studentas& kitas);

    /** @brief Destruktorius */
    ~Studentas() override;

    /** @brief Grazina pazymiu vektoriu */
    const std::vector<int>& pazymiai() const;

    /** @brief Grazina egzamino pazymi */
    int egzaminas() const;

    /** @brief Grazina galutini rezultata pagal vidurki */
    float getVid() const;

    /** @brief Grazina galutini rezultata pagal mediana */
    float getMed() const;

    /**
     * @brief Skaito studento duomenis is srauto
     * @param is Ivesties srautas
     * @return Ivesties srautas
     */
    std::istream& skaitytiStudenta(std::istream& is);

    /** @brief Skaito bendra informacija (polimorfizmas) */
    void skaitytiInfo(std::istream& is) override;

    /** @brief Spausdina studento informacija i srauta */
    void spausdintiInfo(std::ostream& os) const override;

    /** @brief Apskaiciuoja vidurki */
    float skaiciuotiVidurki() const;

    /** @brief Apskaiciuoja mediana */
    float skaiciuotiMediana() const;

    /** @brief Apskaiciuoja galutinius rezultatus (vidurkis ir mediana) */
    void apskaiciuotiRezultatus();

    /** @brief Ivesties operatorius */
    friend std::istream& operator>>(std::istream& is, Studentas& s);

    /** @brief Isvesties operatorius */
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);
};

/** @brief Rikiavimo pagal varda funkcija */
bool pagalVarda(const Studentas& a, const Studentas& b);

/** @brief Rikiavimo pagal pavarde funkcija */
bool pagalPavarde(const Studentas& a, const Studentas& b);

/** @brief Rikiavimo pagal galutini rezultata funkcija */
bool pagalGalutini(const Studentas& a, const Studentas& b);
