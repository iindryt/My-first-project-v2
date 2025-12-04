#pragma once
#include <string>
#include <iostream>

/**
 * @class Zmogus
 * @brief Bazine klase zmogui, sauganti varda ir pavarde.
 *
 * Si klase yra abstrakti ir naudojama kaip pagrindas kitoms klasems,
 * pvz., Studentas ar Destytojas. Reikalauja implementuoti skaitymo ir
 * spausdinimo funkcijas.
 */
class Zmogus {
protected:
    std::string vard_; /**< Vardas */
    std::string pav_;  /**< Pavarde */

public:
    /**
     * @brief Numatytoji konstruktorius
     */
    Zmogus() = default;

    /**
     * @brief Konstruktorius su vardu ir pavarde
     * @param vard Vardas
     * @param pav Pavarde
     */
    Zmogus(const std::string& vard, const std::string& pav) : vard_(vard), pav_(pav) {}

    /**
     * @brief Virtualus destruktorius
     */
    virtual ~Zmogus() = default;

    /**
     * @brief Grazina varda
     * @return std::string Vardas
     */
    std::string vardas() const { return vard_; }

    /**
     * @brief Grazina pavarde
     * @return std::string Pavarde
     */
    std::string pavarde() const { return pav_; }

    /**
     * @brief Abstrakti funkcija, skirta ivesti zmogaus informacija
     * @param is Ivesties srautas (std::cin ar std::ifstream)
     */
    virtual void skaitytiInfo(std::istream& is) = 0;

    /**
     * @brief Abstrakti funkcija, skirta isvesti zmogaus informacija
     * @param os Isvesties srautas (std::cout ar std::ofstream)
     */
    virtual void spausdintiInfo(std::ostream& os) const = 0;
};
