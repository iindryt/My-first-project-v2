#pragma once
#include <string>
#include <iostream>

class Zmogus {
protected:
    std::string vard_;
    std::string pav_;

public:
    Zmogus() = default;
    Zmogus(const std::string& vard, const std::string& pav) : vard_(vard), pav_(pav) {}

    virtual ~Zmogus() = default;

    std::string vardas() const { return vard_; }
    std::string pavarde() const { return pav_; }

    
    virtual void skaitytiInfo(std::istream& is) = 0;
    virtual void spausdintiInfo(std::ostream& os) const = 0;
};

