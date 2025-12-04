#include "pch.h"
#include "studentas.h"

TEST(StudentasTest, VidurkioSkaiciavimas) {
    std::vector<int> nd = { 6, 8, 10 };
    Studentas s("Aiste", "Petrauskaite", 9, nd);

    float vid = s.skaiciuotiVidurki();
    float expected = (6 + 8 + 10) / 3.0f;

    EXPECT_FLOAT_EQ(vid, expected);
}
TEST(StudentasTest, GalutinioBalSkaiciavimas) {
    std::vector<int> nd = { 6, 8, 10 };
    Studentas s("Aiste", "Petrauskaite", 9, nd);
    s.apskaiciuotiRezultatus();
    float expected = 0.4f * ((6 + 8 + 10) / 3.0f) + 0.6f * 9;
    EXPECT_FLOAT_EQ(s.getVid(), expected);
}

// ==========================
// Kopijavimo konstruktoriaus testas
// ==========================
TEST(StudentasTest, CopyConstructor) {
    std::vector<int> nd = { 5, 7, 9 };
    Studentas s1("Aiste", "Petrauskaite", 8, nd);
    Studentas s2(s1);

    EXPECT_EQ(s2.vardas(), s1.vardas());
    EXPECT_EQ(s2.pavarde(), s1.pavarde());
    EXPECT_EQ(s2.pazymiai(), s1.pazymiai());
    EXPECT_EQ(s2.egzaminas(), s1.egzaminas());
    EXPECT_FLOAT_EQ(s2.getVid(), s1.getVid());
    EXPECT_FLOAT_EQ(s2.getMed(), s1.getMed());
}
// ==========================
// Priskyrimo operatoriaus testas
// ==========================
TEST(StudentasTest, AssignmentOperator) {
    std::vector<int> nd1 = { 5, 7, 9 };
    std::vector<int> nd2 = { 2, 4, 6 };
    Studentas s1("Aiste", "Petrauskaite", 8, nd1);
    Studentas s2("Jonas", "Jonaitis", 6, nd2);

    s2 = s1;

    EXPECT_EQ(s2.vardas(), s1.vardas());
    EXPECT_EQ(s2.pavarde(), s1.pavarde());
    EXPECT_EQ(s2.pazymiai(), s1.pazymiai());
    EXPECT_EQ(s2.egzaminas(), s1.egzaminas());
    EXPECT_FLOAT_EQ(s2.getVid(), s1.getVid());
    EXPECT_FLOAT_EQ(s2.getMed(), s1.getMed());
}
