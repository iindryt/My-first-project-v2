# Studentų pažymių valdymo programa 
# v1.2

Ši programa realizuoja `Studentas` klasę su visais būtinais metodais ir operatoriais pagal **Rule of Three** taisyklę. Projekto v1.2 tikslas – demonstruoti, kaip dirbti su klasėmis, operatoriais.
## v1.2 versijoje atlikta

1. **Rule of Three implementacija**  
   - Realizuotas kopijavimo konstruktorius:
     ```cpp
     Studentas::Studentas(const Studentas& kitas);
     ```
   - Realizuotas kopijavimo priskyrimo operatorius:
     ```cpp
     Studentas& Studentas::operator=(const Studentas& kitas);
     ```
   - Realizuotas destruktorius:
     ```cpp
     Studentas::~Studentas();
     ```
   - Demonstracija `main()` programoje:
     ```cpp
     Studentas original;
     std::cin >> original;
     Studentas kopija = original;      // kopijavimo konstruktorius
     Studentas priskyrimas;
     priskyrimas = original;           // operator=
     ```
     Destruktorius kviečiamas automatiškai bloko pabaigoje.

2. **Įvesties ir išvesties operatorių perdengimas**
   - Operatorius `>>` įvesties skaitymui:
     ```cpp
     std::istream& operator>>(std::istream& is, Studentas& s);
     ```
   - Operatorius `<<` duomenų išvedimui:
     ```cpp
     std::ostream& operator<<(std::ostream& os, const Studentas& s);
     ```
   - Šie operatoriai leidžia:
     ```cpp
     std::cin >> studentas;
     std::cout << studentas;
     ```
     
## V1.2 versijoje specialiai sukurtas meniu veiksmas 7 leidžia pamatyti, kaip veikia **Rule of Three** ir perdengti operatoriai:


     
| Veiksmas                       | Operatorius / metodas                           | Klasės dalis / paskirtis                                 |
| ------------------------------ | ----------------------------------------------- | -------------------------------------------------------- |
| `std::cin >> original;`        | `operator>>`                                    | Įvestis – leidžia įvesti studento duomenis iš `std::cin` |
| `std::cout << original;`       | `operator<<`                                    | Išvestis – spausdina studento duomenis į ekraną          |
| `Studentas kopija = original;` | kopijavimo konstruktorius                       | Kopijuoja `original` į `kopija` (Rule of Three)          |
| `priskyrimas = original;`      | kopijavimo priskyrimo operatorius (`operator=`) | Priskiria `original` duomenis objektui `priskyrimas`     |
| blokas baigiasi                | destruktorius                                   | Automatiškai kviečiamas, išvalo ir sunaikina objektus    |


Asmeniui leidžiama pasirinkti, kad būtų atliekamas testavimas (7)
Suvedus duomenis, atitinkamai įvykdoma ir parodoma, kad veikia tiek Rule of Three, tiek ir operatoriai:
<img width="1255" height="531" alt="image" src="https://github.com/user-attachments/assets/faa0443f-3fca-4c05-96df-a44b829395d9" />




Kalbant apie realų pritaikymą programoje, išskirčiau vieną funkciją – nuksiatymą iš failo, nes
Nuskaitant studentų įrašus iš failo, naudojamas perdengtas operatorius:
iss >> s;
Kadangi s yra Studentas, kviečiamas būtent:
operator>>(std::istream&, Studentas&)

Operatorius nėra naudojamas rankinėje įvestyje, programos rezultato išvedimas naudojamas rankiniu būdu, t.y., operatorius << Studentui nėra naudojamas bendrai rezultatų spausdinimo funkcijoje;

## Perdengtų operatorių naudojimas programoje

| Veiksmas / vieta programoje                     | Naudojamas operatorius | Ar tikras panaudojimas? | Aprašas / paskirtis |
|-------------------------------------------------|----------------------|------------------------|--------------------|
| Nuskaitant studentus iš failo (`iss >> s`)     | `operator>>`         | Taip                 | Įvedimas iš failo; leidžia naudoti tą patį formatą kaip cin |
| Testavimo režimas (Meniu #7) – įvedimas       | `operator>>`         |  Taip                 | Įvedamas studentas konsolėje; demonstruoja Rule of Three |
| Testavimo režimas (Meniu #7) – išvedimas      | `operator<<`         | Taip                 | Išvedamas studentas konsolėje; demonstruoja Rule of Three |
| Rankinis įvedimas (funkcija `ivesk()`)         | –                    |  Ne                   | Duomenys įvedami per cin, operatorius `>>` Studentui nenaudojamas |
| Rezultatų spausdinimas į ekraną / failą       | –                    | Ne                   | Duomenys išvedami atskirai: s.vardas(), s.pavarde(), s.getVid()/s.getMed(); operatorius `<<` Studentui nenaudojamas |






# v1.1
Versijoje v1.1 atlikta šie pakeitimai:

- Sukurta nauja repozicija iš ankstesnės užduoties, išlaikant visą git istoriją iki v1.0.
- Programos realizacija pakeista iš `struct` į `class` tipo `Student` objektus, pritaikant visus atitinkamus kodo pakeitimus.
- Palyginta abiejų realizacijų (`struct` vs `class`) sparta naudojant vieną fiksuotą konteinerį (`std::vector`) ir greičiausią dalijimo strategiją su failais dydžiu 100000 ir 1000000 įrašų.
- Atlikta eksperimentinė analizė pagal kompiliatoriaus optimizacijos flag’us (`-O1`, `-O2`, `-O3`).

# Studentų duomenų struktūrų palyginimas v1.1

Šiame projekte lyginama dviejų realizacijų `Student` objektų veikimo sparta naudojant **Strategiją 1 -**, tiek su `struct`, tiek su `class` tipo objektais.

## Strategija 1 – Du konteineriai (su struct)

| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|-------------|--------|----------------|--------------|-------------|--------------|
| vector      | studentai100000.txt  | 0.954551 | 0.378320 | 1.785649 | 21,620,012 |
| vector      | studentai1000000.txt | 6.804002 | 1.954002 | 10.600715 | 216,012,312 |

## Strategija 1 – Du konteineriai (su class)

| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|-------------|--------|----------------|--------------|-------------|--------------|
| vector      | studentai100000.txt  | 0.498979 | 0.179345 | 0.608324 | 14,378,544 |
| vector      | studentai1000000.txt | 4.397648 | 2.120036 | 6.617684 | 109,186,400 |

## Išvados
- `class` realizacija rodo mažesnį atminties naudojimą ir dažnai trumpesnį bendrą veikimo laiką šioje strategijoje.  
- `struct` realizacija užima daugiau atminties, tačiau nuskaitymo laikai šiek tiek didesni.
  # Studentų duomenų struktūrų palyginimas su kompiliatoriaus optimizacijos lygiais

Atliekant testus su **Strategija 1 – Du nauji konteineriai** (`struct` arba `class`), matyti, kaip kompiliatoriaus optimizacijos flag'ai (`-O1`, `-O2`, `-Ox`) daro įtaką nuskaitymo, įrašymo ir bendrą laiką.

---

## O1 class
*Naudota STRATEGIJA 1*

| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|-------------|--------|----------------|--------------|-------------|--------------|
| vector      | studentai100000.txt  | 0.404711 | 0.228556 | 0.633267 | 14,378,544 |
| vector      | studentai1000000.txt | 4.559094 | 2.033421 | 6.592515 | 109,186,400 |

---

## O2 class
*Naudota STRATEGIJA 1*

| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|-------------|--------|----------------|--------------|-------------|--------------|
| vector      | studentai100000.txt  | 0.498979 | 0.179345 | 0.608324 | 14,378,544 |
| vector      | studentai1000000.txt | 4.397648 | 2.120036 | 6.617684 | 109,186,400 |

---

## Ox class
*Naudota STRATEGIJA 1*

| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|-------------|--------|----------------|--------------|-------------|--------------|
| vector      | studentai100000.txt  | 0.422925 | 0.216015 | 0.638940 | 14,378,544 |
| vector      | studentai1000000.txt | 5.140793 | 2.245802 | 7.386596 | 109,186,400 |

## O1 struct

| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|-------------|--------|----------------|--------------|-------------|--------------|
| vector      | studentai100000.txt  | 0.490824 | 0.198727 | 0.689551  | 26,778,544  |
| vector      | studentai1000000.txt | 4.896540 | 2.102408 | 6.998948  | 233,186,400 |
## O2 struct 
| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|-------------|--------|----------------|--------------|-------------|--------------|
| vector      | studentai100000.txt  | 0.954551 | 0.378320 | 1.785649 | 21,620,012 |
| vector      | studentai1000000.txt | 6.804002 | 1.954002 | 10.600715 | 216,012,312 |
## OX struct
| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|-------------|--------|----------------|--------------|-------------|--------------|
| vector      | studentai100000.txt  | 0.672783 | 0.253848 | 0.926631  | 26,778,544  |
| vector      | studentai1000000.txt | 7.709458 | 3.816911 | 11.526369 | 233,186,400 |

---
## Versijos

| Versija | Tipas     |
|---------|-----------|
| v1.0    | struct    |
| v1.1    | class     |

---

## EXE failo dydis pagal optimizaciją

| Versija | Optimizacija | EXE dydis |
|---------|--------------|-----------|
| v1.0    | O1           | 86 KB     |
| v1.0    | O2           | 97 KB     |
| v1.0    | O3           | 104 KB    |
| v1.1    | O1           | 78 KB     |
| v1.1    | O2           | 93 KB     |
| v1.1    | O3           | 95 KB     |

## Išvados
- Skirtingi optimizacijos lygiai turi nedidelę, bet matomą įtaką veikimo laikams.  
- `-O2` dažnai duoda mažiausią bendrą laiką, ypač didesniems failams.  
- `-Ox` gali būti ne visada greitesnis, priklausomai nuo nuskaitymo/įrašymo operacijų pobūdžio.
- EXE failo dydis sumažėjo, naudojant Class, o ne Struct.



## Įdiegimo instrukcija
# CMake įdiegimas Windows naudojant `.msi` paketą

Prieš pradedant 

Atsisiųsti CMakeLists.txt, run.bat, .cpp ir .h failus iš GitHub.

Kompiuteryje sukurti aplanką pavadintą "cmaketest". Į jį įkelti CMakeLists.txt, run.bat, cmake.exe failus.

"cmaketest" aplanke sukurti du aplankus: "src", "include". Į "src" aplanką įkelti .cpp failus, o į "include" - .h failus.

## 1. Atsisiuntimas
1. Eikite į oficialų CMake puslapį: [https://cmake.org/download/](https://cmake.org/download/)
2. Pasirinkite **Windows x64 Installer (.msi)** versiją.
   - Pavyzdys: `cmake-3.25.0-windows-x86_64.msi`

## 2. Diegimas
1. Paleiskite atsisiųstą `.msi` failą.
2. Spauskite **Next** visuose langeliuose.
3. Svarbu: pasirinkite **"Add CMake to the system PATH for all users"** arba **"for current user"**.  
   - Tai leis naudoti `cmake` komandą bet kuriame terminale.

## 3. Baigimas
1. Spauskite **Finish**, kai diegimas baigtas.
2. Atidarykite naują **PowerShell** langą.
3. Patikrinkite diegimą įvedę:
   ```powershell
   cmake --version

# CMake projekto paleidimas Windows PowerShell
---

## 1. Atidarykite PowerShell

- Atidarykite **Windows PowerShell**.
2. **Eikite į savo projekto katalogą, pavyzdžiui:**
- cd C:\Users\aiste\Desktop\cmaketest
- 
3. **Paleiskite CMake projektą:**

cmake .\CMakeLists.txt

4. **Sukurkite projektą:**

cmake --build .

5. **Pereikite į Debug katalogą:**

cd Debug

6. **Paleiskite programą:**

.\Studentu_programa.exe

7. **Terminale matysite programos meniu:**

Pasirinkite veiksma:
1 - Prideti studenta rankiniu budu
2 - Nuskaityti studentus is failo
3 - Rodyti studentu rezultatus
4 - Baigti programa
5 - Generuoti studentu failus (1k - 10mln)
6 - Testuoti konteinerius (vector vs list)
7 - Automatinis testavimas su visais failais
Jusu pasirinkimas yra:



---
## Naudojimosi instrukcija

Programa veikia meniu principu ir leidžia valdyti studentų pažymius.

## Paleidimas

- Linux/MacOS: `./studentai`  
- Windows: `studentai.exe`

## Pagrindinis meniu

Pasirinkite veiksmą:

1. **Pridėti studentą rankiniu būdu**  
   - Įveskite vardą, pavardę, namų darbų ir egzamino pažymius (arba generuokite atsitiktinius).

2. **Nuskaityti studentus iš failo**  
   - Failas turi turėti antraštę: `Vardas Pavarde ND1 ND2 ... Egzaminas`.

3. **Rodyti studentų rezultatus**  
   - Pasirinkite galutinio balo skaičiavimo metodą: Vidurkis / Mediana / Abu.  
   - Rezultatai išsaugomi `rezultatai.txt`.  
   - Galima skirstyti studentus į:  
     - **Kietiakiai** (≥5) – `kietiakiai.txt`  
     - **Vargsiukai** (<5) – `vargsiukai.txt`

4. **Baigti programą**  

5. **Generuoti studentų failus (1k–10 mln)**  
   - Sukuria atsitiktinius studentų duomenų failus testavimui.

6. **Testuoti konteinerius (vector vs list)**  
   - Atliekami našumo testai nuskaitymui, rūšiavimui ir įrašymui.

7. **Automatinis testavimas su visais failais**  
   - Paleidžia visus testus automatiškai dideliems failams.

**Jūsų pasirinkimas yra:**



## v.01

Ši programa leidžia valdyti studentų pažymius, skaičiuoti galutinius balus ir išsaugoti rezultatus į failą. Programa suteikia galimybę studentus įvesti rankiniu būdu arba nuskaityti iš failo, generuoti atsitiktinius pažymius, ir skaičiuoti galutinį rezultatą naudojant vidurkį arba medianą.

---

## Funkcionalumas

1. **Studentų įvedimas rankiniu būdu**
   - Įvedamas vardas ir pavardė.
   - Galima įvesti namų darbų pažymius rankiniu būdu arba sugeneruoti atsitiktinius.
   - Egzamino pažymį galima įvesti rankiniu būdu arba sugeneruoti atsitiktinį.
   - Galutinis balas skaičiuojamas pagal vidurkį ir medianą:
     - `Galutinis (Vid.) = 0.4 * namų darbų vidurkis + 0.6 * egzamino pažymys`
     - `Galutinis (Med.) = 0.4 * namų darbų mediana + 0.6 * egzamino pažymys`

2. **Studentų nuskaitymas iš failo**
   - Failas turi būti tekstinis, su pirmąja eilute kaip header, pvz.:
     ```
     Vardas Pavarde ND1 ND2 ND3 ... Egzaminas
     ```
   - Programa perskaito studentus, patikrina, ar įvesti bent du pažymiai (namų darbai + egzaminas).

3. **Rezultatų atvaizdavimas ir išsaugojimas**
   - Rezultatai gali būti skaičiuojami pagal:
     - Vidurkį
     - Medianą
     - Abu (vidurkis ir mediana)
   - Rezultatai išsaugomi faile `rezultatai.txt`.

4. **Programa veikia meniu principu**
   - Galimi veiksmai:
     1. Pridėti studentą rankiniu būdu
     2. Nuskaityti studentus iš failo
     3. Rodyti studentų rezultatus
     4. Baigti programą
## Rezultatai

Programa skaičiuoja ir išsaugo studentų galutinius balus faile `rezultatai.txt`. Galutinis balas gali būti apskaičiuotas naudojant:

1. **Vidurkį (Galutinis (Vid.))**  
   - Skaičiuojamas taip:
     ```
     Galutinis (Vid.) = 0.4 * namų darbų vidurkis + 0.6 * egzamino pažymys
     ```
   - Šis metodas pabrėžia egzamino reikšmę (60% galutinio balo) ir naudoja visų namų darbų vidurkį kaip 40% galutinio balo dalį.
   - Tinka, kai norima, kad visų pažymių suma būtų atspindima vienu vidurkiu.

2. **Medianą (Galutinis (Med.))**  
   - Skaičiuojama taip:
     ```
     Galutinis (Med.) = 0.4 * namų darbų mediana + 0.6 * egzamino pažymys
     ```
   - Naudojama namų darbų mediana vietoje vidurkio, todėl vienas itin žemas arba aukštas pažymys mažiau įtakoja galutinį rezultatą.
   - Šis metodas suteikia stabilesnį galutinį balą, kai namų darbų pažymiai yra nevienodi.

3. **Abi (Vidurkis ir Mediana)**  
   - Programa gali išsaugoti tiek `Galutinis (Vid.)`, tiek `Galutinis (Med.)` stulpelius.
   - Tai leidžia palyginti, kaip skirtingi skaičiavimo metodai veikia studentų galutinius rezultatus.

**Pastaba:**  
- Visi rezultatai yra suformatuoti su dviem skaitmenimis po kablelio.
- Studentai rūšiuojami pagal vardą, kad rezultatai būtų tvarkingi ir lengvai skaitomi.
- Rezultatai išsaugomi faile `rezultatai.txt` tame pačiame kataloge, kuriame paleista programa.

# Studentų pažymių valdymo programa – Versija v.02

Ši dokumentacija tęsia ankstesnės versijos (v.01) aprašymą ir aptaria naujoves bei patobulinimus, įdiegtus versijoje Nr. 2.

---

## Naujos funkcijos ir patobulinimai v.02

1. **Studentų rūšiavimas pagal vardą**
   - Visi studentai dabar rūšiuojami pagal vardą prieš išvedant rezultatus.
   - Tai pagerina rezultatų tvarkingumą ir palengvina peržiūrą didesnėse grupėse.

2. **Galutinių balų pasirinkimas**
   - Vartotojas gali pasirinkti, kaip skaičiuoti galutinį balą:
     - Vidurkis (`Galutinis (Vid.)`)
     - Mediana (`Galutinis (Med.)`)
     - Abu variantai vienu metu
   - Šis patobulinimas suteikia daugiau lankstumo vertinant studentus.

3. **Studentų skirstymas į kategorijas**
   - Įdiegta funkcija automatiškai skirstyti studentus į dvi kategorijas:
     - **Kietiakiai** – galutinis balas ≥ 5
     - **Vargsiukai** – galutinis balas < 5
   - Rezultatai išsaugomi atskiruose failuose:
     - `kietiakiai.txt`
     - `vargsiukai.txt`

4. **Failų generavimas**
   - Pridėta galimybė generuoti studentų failus su atsitiktiniais duomenimis dideliam kiekiui studentų (nuo 1 tūkst. iki 10 mln.).
   - Naudinga testuojant programą su dideliais duomenų rinkiniais.

5. **Laikmatio matavimas**
   - Matuojamas laiką, reikalingą:
     - studentų rūšiavimui
     - rezultatų išvedimui į failą
     - skirstymui į kietiakiai/vargsiukai
   - Tai leidžia stebėti operacijų efektyvumą didelėse grupėse.

6. **Modulinė struktūra**
   - Programa padalinta į atskirus modulius:
     - `main.cpp` – pagrindinis meniu
     - `funkcijos.cpp/h` – studentų įvedimas, skaičiavimai, rezultatų spausdinimas
     - `duomenys.cpp/h` – failų nuskaitymas ir generavimas
     - `studentas.h` – studento struktūra
     - `laikmatis.h` – operacijų laiko matavimas

---

## Rezultatų aptarimas v.02

- **Galutinis balas pagal vidurkį:** naudoja visų namų darbų vidurkį; egzamino reikšmė – 60%.
- **Galutinis balas pagal medianą:** atsparus itin žemiems ar aukštiems pažymiams; egzamino reikšmė – 60%.
- **Skirstymas į kategorijas:** leidžia greitai identifikuoti stipriausius ir silpniausius studentus.
- **Išsaugomi failai:**
  - `rezultatai.txt` – visi studentai su galutiniu balu.
  - `kietiakiai.txt` – studentai su galutiniu balu ≥ 5.
  - `vargsiukai.txt` – studentai su galutiniu balu < 5.
- **Papildomas efektyvumo matavimas:** leidžia stebėti programos našumą dideliuose duomenų rinkiniuose.

---

## Pastabos

- Egzamino ir namų darbų pažymiai turi būti tarp 1 ir 10.
- Atsitiktinių pažymių generavimui naudojamas `rand()` su `srand(time(nullptr))`.
- Versija 0.02 išlaiko visą ankstesnės versijos funkcionalumą, bet prideda patogesnį rezultatų valdymą, rūšiavimą ir efektyvumo matavimą.






# Programos Testavimo Rezultatai v0.3 ir v1.0 (žemiau)

Šioje projekto dalyje atliekamas dviejų C++ konteinerių našumo testavimas, skirtas studentų duomenų nuskaitymui, rūšiavimui ir įrašymui.  
Šiame dokumente pateikiami išsamūs programos testavimo rezultatai, įskaitant dviejų konteinerių našumo matavimus pagal skirtingo dydžio failus.

**Testavimo data:** 2025–10–15

---

## Sistemos Parametrai

| Komponentas | Aprašymas |
|--------------|-----------|
| **Procesorius (CPU)** | AMD Ryzen 5 3550H with Radeon Vega Mobile Gfx, 2.10 GHz |
| **RAM** | 8 GB (naudojama ~5,88 GB) |
| **Grafika** | 6 GB, Radeon Vega Mobile Gfx |
| **Atmintis (HDD/SSD)** | 477 GB (SSD) |
| **Operacinė sistema (OS)** | Windows 11, 64-bit |

---

## Testavimo Metodika

Testuojami du C++ standartiniai konteineriai:  
- `std::vector`  
- `std::list`

Matavimai atliekami trimis pagrindinėmis operacijomis:
1. **Nuskaitymas** – duomenų nuskaitymas iš failo į konteinerį.  
2. **Rūšiavimas** – vargšiukai/kietiakiai skirstymas konteineryje.  
3. **Įrašymas** – duomenų įrašymas atgal į failą.  

Laikas matuojamas **sekundėmis** su tikslumu iki šešių skaičių po kablelio.

---

## Testavimo Rezultatai

| Failas | Konteineris | Nuskaitymas (s) | Skirstymas (s) | Įrašymas (s) | Visas testas (s) |
|----------------------|-------------|----------------|---------------|----------------|----------------|
| studentai_1000.txt | std::vector | 0.0056859 | 0.000215 | 0.002819 | 0.011070 |
| studentai_1000.txt | std::list | 0.006416 | 0.000157 | 0.014394 | 0.022621 |
| studentai_10000.txt | std::vector | 0.042181 | 0.002711 | 0.016948 | 0.066189 |
| studentai_10000.txt | std::list | 0.043124 | 0.002033 | 0.016385 | 0.064150 |
| studentai_100000.txt | std::vector | 0.440618 | 0.026316 | 0.133719 | 0.604092 |
| studentai_100000.txt | std::list | 0.426942 | 0.020604 | 0.140861 | 0.592571 |
| studentai_1000000.txt | std::vector | 4.40848 | 0.271929 | 1.274328 | 5.957573 |
| studentai_1000000.txt | std::list | 4.367253 | 0.209767 | 1.425252 | 6.005412 |
| studentai_10000000.txt | std::vector | 44.783089 | 5.682959 | 13.204492 | 63.676864 |
| studentai_10000000.txt | std::list | 43.502372 | 2.101811 | 14.136841 | 59.744353 |

---

## Išvados

### 1. Maži failai (1000–10 000 įrašų)
1.1 `std::vector` šiek tiek greitesnis įrašant duomenis su 1000, taip ir nuskaitant failą, o `std::list` greitesnis rūšiuojant. Bendras laikas greitesnis su vektoriumi.  
1.2 `std::list` įrašymas, rūšiavimas yra šiek tiek greitesnis, tačiau nuskaitymas užtrunka ilgiau. Bendras laikas labai panašus, tačiau `std::list` greitesnis. (10 000)

### 2. Vidutinio dydžio failai (100 000–1 000 000 įrašų)
2.1 `std::list` (100 000) pranašesnis nuskaityme ir skirstyme, o `std::vector` – įrašyme.  
2.2 Bendras laikas rodo, kad skirtumas tarp `std::vector` ir `std::list` mažėja – `std::list` pranašesnis vos 0.1 sek.  
2.3 `std::vector` (1 000 000) lėtesnis už `std::list` tiek nuskaityme, skirstyme, bet greitesnis įrašyme.  
2.4 Bendrame laike `std::vector` laimi 0,05 sek.

### 3. Dideli failai (10 000 000 įrašų)
3.1 `std::vector` įrašymo laikas yra šiek tiek trumpesnis nei `std::list`, 1,1 sek.  
3.2 Abu konteineriai užtrunka daug laiko, tačiau `std::list` šiek tiek greitesnis bendrame rezultate, daugiausia dėl efektyvesnio rūšiavimo.

---

## Bendros Išvados

- Mažuose duomenų kiekiuose (iki 10 000 įrašų) reikšmingo skirtumo tarp konteinerių beveik nėra.  
- Vidutinio dydžio failuose (100 000–1 000 000 įrašų) našumo skirtumas tarp konteinerių pakankamai mažas.  
- Labai dideliuose duomenų kiekiuose (10 000 000 įrašų) skirtumai išryškėja.

---
# v.1.0
# Testų rezultatai: vector vs list


# Studentų konteinerių testavimas

Šioje projekto dalyje testuojamas **std::vector** ir **std::list** konteinerių našumas skirtingais atvejais: nuskaitymas, skirstymas ir įrašymas į failus.  
Taip pat atliktas papildomas testas su **std::vector**, naudojant **STL algoritmus**.

---

## Skirstymo strategijos

1. **Dvi kopijos** – sukuriami atskiri konteineriai *kietiakiams* ir *vargšiukams*.  
2. **Viena kopija su trynimu** – duomenys skirstomi vietoje, ištrinant nereikalingus.  
3. **Automatinis pasirinkimas** – parenkama greičiausia strategija pagal konteinerį.

---

## Testavimo rezultatai (vector for ciklais, list for ciklais)

Šiame projekto etape testuojami `std::vector` ir `std::list` konteineriai studentų duomenų nuskaitymui, skirstymui ir įrašymui į failus. Testai atliekami su skirtingais failų dydžiais ir trimis skirstymo strategijomis.

### Pagal vidurkį

| Failas           | Konteineris | Studentų kiekis | Strategija 1 (s) | Strategija 2 (s) | Strategija 3 greitesnė (s) | Nuskaitymas (s) | Įrašymas (s) | Viso testas (s) |
|-----------------|------------|----------------|-----------------|-----------------|----------------------------|----------------|---------------|----------------|
| studentai_1k    | vector     | 1 000          | 0.00035         | 0.00045         | 0.00035                    | 0.015          | 0.0035        | 13.0           |
| studentai_1k    | list       | 1 000          | 0.00031         | 0.00028         | 0.00029                    | 0.0085         | 0.0046        | 5.3            |
| studentai_10k   | vector     | 10 000         | 0.0039          | 0.0038          | 0.0030                     | 0.072          | 0.011         | 15.2           |
| studentai_10k   | list       | 10 000         | 0.0031          | 0.0042          | 0.0025                     | 0.059          | 0.013         | 8.9            |
| studentai_100k  | vector     | 100 000        | 0.030           | 34.6751          | 0.03                      | 0.71           | 0.12          | 38.0           |
| studentai_100k  | list       | 100 000        | 0.031           | 0.038           | 0.03                       | 0.59           | 0.13          | 12.2           |
| studentai_1mln  | vector     | 1 000 000      | 0.38            | 48.512            | 0.31                       | 6.85           | 0.96          | 59.0           |
| studentai_1mln  | list       | 1 000 000      | 0.32            | 0.29            | 0.28                       | 5.24           | 1.05          | 19.8           |
| studentai_10mln | vector     | 10 000 000     | 3.5             | 101.145             | 3.4                        | 68.1           | 9.8           | 182.0          |
| studentai_10mln | list       | 10 000 000     | 5.25            | 4.12            | 3.23                       | 52.5           | 10.9          | 87.4           |

### Pagal medianą

| Failas           | Konteineris | Studentų kiekis | Strategija 1 (s) | Strategija 2 (s) | Strategija 3 greitesnė (s) | Nuskaitymas (s) | Įrašymas (s) | Viso testas (s) |
|-----------------|------------|----------------|-----------------|-----------------|----------------------------|----------------|---------------|----------------|
| studentai_1k    | vector     | 1 000          | 0.00037         | 0.00048         | 0.00037                    | 0.0154         | 0.0035        | 13.2           |
| studentai_1k    | list       | 1 000          | 0.00036         | 0.00050         | 0.00038                    | 0.0086         | 0.0046        | 5.29           |
| studentai_10k   | vector     | 10 000         | 0.0033          | 0.0042          | 0.0032                     | 0.073          | 0.011         | 15.5           |
| studentai_10k   | list       | 10 000         | 0.0033          | 0.0040          | 0.0033                     | 0.061          | 0.013         | 8.9            |
| studentai_100k  | vector     | 100 000        | 0.031           | 42.15           | 0.027                      | 0.72           | 0.12          | 48.2           |
| studentai_100k  | list       | 100 000        | 0.033           | 0.040           | 0.038                      | 0.61           | 0.13          | 12.4           |
| studentai_1mln  | vector     | 1 000 000      | 0.32            | 72.45           | 0.32                       | 6.91           | 0.97          | 92.5           |
| studentai_1mln  | list       | 1 000 000      | 0.33            | 0.40            | 0.33                       | 5.30           | 1.05          | 20.0           |
| studentai_10mln | vector     | 10 000 000     | 3.6             | 113.412             | 3.6                        | 74.8           | 9.9           | 201.0          |
| studentai_10mln | list       | 10 000 000     | 3.41            | 4.08            | 3.43                       | 62.1           | 10.9          | 88.2           |

### Atminties testavimas

| Konteineris | Failas                | Strategija | Pradinis (B) | Kietiakiai (B) | Vargsiukai (B) | Viso (B)      |
| ----------- | --------------------- | ---------- | ------------ | -------------- | -------------- | ------------- |
| vector      | studentai1000.txt     | 1          | 72 000       | 42 912         | 29 500         | 144 412       |
| list        | studentai1000.txt     | 1          | 42 912       | 42 912         | 14 256         | 100 080       |
| vector      | studentai1000.txt     | 2          | 70 000       | 42 000         | 24 652         | 136 652       |
| list        | studentai1000.txt     | 2          | 42 000       | 42 000         | 12 556         | 96 556        |
| vector      | studentai1000.txt     | 3          | 71 000       | 42 500         | 24 124         | 137 624       |
| list        | studentai1000.txt     | 3          | 42 500       | 42 500         | 16 512         | 101 512       |
| vector      | studentai10000.txt    | 1          | 720 000      | 429 120        | 290 724        | 1 439 844     |
| list        | studentai10000.txt    | 1          | 429 120      | 429 120        | 157 056        | 1 015 296     |
| vector      | studentai10000.txt    | 2          | 720 000      | 429 120        | 250 436        | 1 399 556     |
| list        | studentai10000.txt    | 2          | 260 000      | 260 000        | 156 316        | 676 316       |
| vector      | studentai10000.txt    | 3          | 720 000      | 429 120        | 238 332        | 1 387 452     |
| list        | studentai10000.txt    | 3          | 240 000      | 240 000        | 175 872        | 655 872       |
| vector      | studentai100000.txt   | 1          | 7 200 000    | 4 291 200      | 2 908 812      | 14 400 012    |
| list        | studentai100000.txt   | 1          | 4 000 000    | 4 000 000      | 814 204        | 8 814 204     |
| vector      | studentai100000.txt   | 2          | 7 200 000    | 4 291 200      | 250 772        | 11 742 972    |
| list        | studentai100000.txt   | 2          | 2 000 000    | 2 000 000      | 1 825 596      | 5 825 596     |
| vector      | studentai100000.txt   | 3          | 7 200 000    | 4 291 200      | 213 056        | 11 704 256    |
| list        | studentai100000.txt   | 3          | 2 000 000    | 2 000 000      | 818 776        | 4 818 776     |
| vector      | studentai1000000.txt  | 1          | 72 000 000   | 42 912 000     | 29 088 000     | 144 000 000   |
| list        | studentai1000000.txt  | 1          | 42 912 000   | 42 912 000     | 16 000 000     | 101 824 000   |
| vector      | studentai1000000.txt  | 2          | 72 000 000   | 42 912 000     | 21 318 640     | 136 230 640   |
| list        | studentai1000000.txt  | 2          | 24 000 000   | 24 000 000     | 18 075 436     | 66 075 436    |
| vector      | studentai1000000.txt  | 3          | 72 000 000   | 42 912 000     | 21 088 312     | 136 000 312   |
| list        | studentai1000000.txt  | 3          | 24 000 000   | 24 000 000     | 18 171 132     | 66 171 132    |
| vector      | studentai10000000.txt | 1          | 720 000 000  | 429 120 000    | 290 880 000    | 1 440 000 000 |
| list        | studentai10000000.txt | 1          | 429 120 000  | 429 120 000    | 160 000 000    | 1 018 240 000 |
| vector      | studentai10000000.txt | 2          | 720 000 000  | 429 120 000    | 1 524 600 352  | 2 673 720 352 |
| list        | studentai10000000.txt | 2          | 240 000 000  | 240 000 000    | 181 451 136    | 661 451 136   |
| vector      | studentai10000000.txt | 3          | 720 000 000  | 429 120 000    | 1 209 000 120  | 2 358 120 120 |
| list        | studentai10000000.txt | 3          | 240 000 000  | 240 000 000    | 181 177 624    | 661 177 624   |


## Testavimo išvados: `std::vector` vs `std::list` (be STL algoritmų)

Remiantis testų duomenimis, kai tiek `vector`, tiek `list` skirstymas vykdomas tik su for ciklais, galime pastebėti šias tendencijas:

### 1. Laikas skirstymui į grupes

- **`std::vector`**:
  - For ciklai tiesiogiai iteruoja per elementus, todėl skirstymas veikia paprastai.
  - Maži failai (1k–10k studentų) – greitis panašus kaip `list`.
  - Vidutinio dydžio failai (100k–1mln) – `vector` lėtesnis, nes kiekviena įterpimo operacija į kietiakiai ar vargšiai konteinerius gali sukelti vidinį masyvo perkėlimą (resize).
  - Dideli failai (10 mln.) – skirtumas aiškus: `vector` užtrunka daugiau laiko nei `list`.

- **`std::list`**:
  - For ciklai iteruoja per sąrašą, tačiau kiekvienas elementas jau turi nuorodą į kitą (pointer), todėl papildomų perkėlimų nėra.
  - Skirstymas į grupes tampa efektyvesnis dideliems duomenims, nes įterpimas į naujus sąrašus yra O(1).
  - Tiesioginis for ciklas čia išlaiko stabilumą ir greitį, todėl didelės apimties failuose `list` lėčiau auga tik šiek tiek dėl iteracijos per nuorodas.

### 2. Nuskaitymo ir įrašymo laikas

- Nuskaitymas iš failo: abiems konteineriams panašus, skirtumas minimalus.
- Įrašymas į failus: `vector` gali būti šiek tiek lėtesnis dėl nuoseklaus didelio bloko rašymo, bet skirtumas nereikšmingas.

### 3. Atminties naudojimas

- **`vector`**:
  - Naudoja nuoseklią atmintį, todėl bendras atminties poreikis mažesnis.
  - Dideli failai užima mažiau RAM nei `list`.

- **`list`**:
  - Kiekvienas elementas turi du papildomus pointerius (`next` ir `prev`).
  - Bendras atminties poreikis ~10–15% didesnis nei `vector`, ypač dideliems failams.

### 4. Strategijų palyginimas

- Strategijos greitis beveik vienodas abiems konteineriams, nes jos realizuojamos tik su for ciklais.
- `vector` gali užtrukti šiek tiek ilgiau dėl resize operacijų, jei konteineris padidinamas iteracijos metu.
- `list` visada O(1) įterpimas į naują sąrašą, todėl dideliems duomenims labiau stabilus.

### 5. Rezultatų stabilumas

- Rezultatai stabilūs tarp vidurkio ir medianos – konteinerio tipas įtakos proporcijoms neturi.

### 6. Bendros įžvalgos

- **`vector`**:
  - Mažesnis atminties poreikis.
  - Lėtesnis dideliems failams dėl vidinių masyvo kopijavimo operacijų.
  - Maži ir vidutinio dydžio failai – pakankamai efektyvus.

- **`list`**:
  - Šiek tiek didesnis atminties poreikis dėl pointerių.
  - Greitesnis dideliems failams, nes elementų įterpimas O(1).
  - Labiau stabilus, skirtumas tarp strategijų minimalus.

**Bendra santykinai išvada:**  
- Jei duomenys nedideli ir svarbus RAM taupymas – `vector`.  
- Jei duomenų daug ir svarbus greitis skirstant – `list` pranašesnis, net naudojant paprastus for ciklus.

# Studentų konteinerių testavimas (std::vector (pridėtas ir std::list, nors parametrai nekeisti) su STL

Šiame projekto etape testuojamas `std::vector` konteineris studentų duomenų nuskaitymui, skirstymui ir įrašymui į failus. Testai atliekami su skirtingais failų dydžiais ir trimis skirstymo strategijomis:

Pagal vidurkį
---
| Failas          | Konteineris | Studentų kiekis | Strategija 1 (s) | Strategija 2 (s) | Strategija 3 greitesnė (s) | Nuskaitymas (s) | Įrašymas (s) | Viso testas (s) |
| --------------- | ----------- | --------------- | ---------------- | ---------------- | -------------------------- | --------------- | ------------ | --------------- |
| studentai_1k    | std::vector | 1 000           | 0.000242         | 0.000379         | 0.000211                   | 0.015232        | 0.003362     | 12.548          |
| studentai_1k    | std::list   | 1 000           | 0.000312         | 0.000483         | 0.000295                   | 0.008451        | 0.004584     | 5.247           |
| studentai_10k   | std::vector | 10 000          | 0.00235          | 0.00312          | 0.00221                    | 0.072           | 0.011        | 14.7            |
| studentai_10k   | std::list   | 10 000          | 0.00312          | 0.00385          | 0.00305                    | 0.059           | 0.013        | 8.8             |
| studentai_100k  | std::vector | 100 000         | 0.0238           | 0.031            | 0.0215                     | 0.71            | 0.12         | 19.5            |
| studentai_100k  | std::list   | 100 000         | 0.0314           | 0.038            | 0.0296                     | 0.59            | 0.13         | 12.2            |
| studentai_1mln  | std::vector | 1 000 000       | 0.247            | 0.316            | 0.239                      | 6.85            | 0.96         | 26.4            |
| studentai_1mln  | std::list   | 1 000 000       | 0.317            | 0.384            | 0.305                      | 5.24            | 1.05         | 19.8            |
| studentai_10mln | std::vector | 10 000 000      | 2.61             | 3.25             | 2.53                       | 68.1            | 9.8          | 118.5           |
| studentai_10mln | std::list   | 10 000 000      | 3.25             | 3.88             | 3.15                       | 52.5            | 10.9         | 87.4            |

Pagal medianą

| Failas          | Konteineris | Studentų kiekis | Strategija 1 (s) | Strategija 2 (s) | Strategija 3 greitesnė (s) | Nuskaitymas (s) | Įrašymas (s) | Viso testas (s) |
| --------------- | ----------- | --------------- | ---------------- | ---------------- | -------------------------- | --------------- | ------------ | --------------- |
| studentai_1k    | std::vector | 1 000           | 0.00027          | 0.00041          | 0.00023                    | 0.0154          | 0.0035       | 12.7            |
| studentai_1k    | std::list   | 1 000           | 0.00036          | 0.00050          | 0.00034                    | 0.0086          | 0.0046       | 5.29            |
| studentai_10k   | std::vector | 10 000          | 0.00248          | 0.00320          | 0.00235                    | 0.073           | 0.011        | 14.9            |
| studentai_10k   | std::list   | 10 000          | 0.00328          | 0.00398          | 0.00315                    | 0.061           | 0.013        | 8.9             |
| studentai_100k  | std::vector | 100 000         | 0.0252           | 0.0325           | 0.0243                     | 0.72            | 0.12         | 19.7            |
| studentai_100k  | std::list   | 100 000         | 0.0336           | 0.0401           | 0.0321                     | 0.61            | 0.13         | 12.4            |
| studentai_1mln  | std::vector | 1 000 000       | 0.259            | 0.332            | 0.248                      | 6.91            | 0.97         | 26.8            |
| studentai_1mln  | std::list   | 1 000 000       | 0.334            | 0.398            | 0.320                      | 5.30            | 1.05         | 20.0            |
| studentai_10mln | std::vector | 10 000 000      | 2.73             | 3.41             | 2.61                       | 68.8            | 9.9          | 119.3           |
| studentai_10mln | std::list   | 10 000 000      | 3.41             | 4.08             | 3.25                       | 53.1            | 10.9         | 88.2            |


Atminties testavimas tiek pagal vidurkį, tiek pagal medianą

| Konteineris | Failas                | Strategija | Pradinis (B)  | Kietiakiai (B) | Vargsiukai (B) | Viso (B)       |
| ----------- | --------------------- | ---------- | ------------- | -------------- | -------------- | -------------- |
| vector      | studentai1000.txt     | 1          | 720 000       | 429 120        | 295 000        | 1 444 120      |
| list        | studentai1000.txt     | 1          | 429 120       | 429 120        | 142 560        | 1 000 800      |
| vector      | studentai1000.txt     | 2          | 700 000       | 420 000        | 246 520        | 1 366 520      |
| list        | studentai1000.txt     | 2          | 420 000       | 420 000        | 125 560        | 965 560        |
| vector      | studentai1000.txt     | 3          | 710 000       | 425 000        | 241 240        | 1 376 240      |
| list        | studentai1000.txt     | 3          | 425 000       | 425 000        | 165 120        | 1 015 120      |
| vector      | studentai10000.txt    | 1          | 7 200 000     | 4 291 200      | 2 907 240      | 14 398 440     |
| list        | studentai10000.txt    | 1          | 4 291 200     | 4 291 200      | 1 570 560      | 10 153 296     |
| vector      | studentai10000.txt    | 2          | 7 200 000     | 4 291 200      | 2 504 360      | 13 995 560     |
| list        | studentai10000.txt    | 2          | 2 600 000     | 2 600 000      | 1 563 160      | 6 763 160      |
| vector      | studentai10000.txt    | 3          | 7 200 000     | 4 291 200      | 2 383 320      | 13 874 520     |
| list        | studentai10000.txt    | 3          | 2 400 000     | 2 400 000      | 1 758 720      | 6 558 720      |
| vector      | studentai100000.txt   | 1          | 72 000 000    | 42 912 000     | 29 088 120     | 144 000 120    |
| list        | studentai100000.txt   | 1          | 40 000 000    | 40 000 000     | 8 142 040      | 88 142 040     |
| vector      | studentai100000.txt   | 2          | 72 000 000    | 42 912 000     | 2 507 720      | 117 419 720    |
| list        | studentai100000.txt   | 2          | 20 000 000    | 20 000 000     | 18 255 960     | 58 255 960     |
| vector      | studentai100000.txt   | 3          | 72 000 000    | 42 912 000     | 2 130 560      | 117 042 560    |
| list        | studentai100000.txt   | 3          | 20 000 000    | 20 000 000     | 8 187 760      | 48 187 760     |
| vector      | studentai1000000.txt  | 1          | 720 000 000   | 429 120 000    | 290 880 000    | 1 440 000 000  |
| list        | studentai1000000.txt  | 1          | 429 120 000   | 429 120 000    | 160 000 000    | 1 018 240 000  |
| vector      | studentai1000000.txt  | 2          | 720 000 000   | 429 120 000    | 2 131 864 000  | 3 280 984 000  |
| list        | studentai1000000.txt  | 2          | 240 000 000   | 240 000 000    | 1 807 543 600  | 2 287 543 600  |
| vector      | studentai1000000.txt  | 3          | 720 000 000   | 429 120 000    | 2 108 831 200  | 3 257 951 200  |
| list        | studentai1000000.txt  | 3          | 240 000 000   | 240 000 000    | 1 817 713 200  | 2 297 713 200  |
| vector      | studentai10000000.txt | 1          | 7 200 000 000 | 4 291 200 000  | 2 908 800 000  | 14 400 000 000 |
| list        | studentai10000000.txt | 1          | 4 291 200 000 | 4 291 200 000  | 1 600 000 000  | 10 182 400 000 |
| vector      | studentai10000000.txt | 2          | 7 200 000 000 | 4 291 200 000  | 15 246 003 520 | 26 673 203 520 |
| list        | studentai10000000.txt | 2          | 2 400 000 000 | 2 400 000 000  | 1 814 511 360  | 6 614 511 360  |
| vector      | studentai10000000.txt | 3          | 7 200 000 000 | 4 291 200 000  | 12 090 001 200 | 23 581 201 200 |
| list        | studentai10000000.txt | 3          | 2 400 000 000 | 2 400 000 000  | 1 811 776 240  | 6 611 776 240  |


## Testų rezultatai



## Vector su STL algoritmais

- **Strategija 1 (dvi kopijos)** – dažniausiai greičiausia.  
- **Strategija 2 (viena kopija su trynimu)** – efektyvi tik su mažais failais.  
- **Strategija 3 (automatinė)** – paprastai pasirenka skirtingas strategijas.  
- Atminties naudojimas auga proporcingai failo dydžiui.  
- Naudojant **STL algoritmus**, programa veikia greitai, bet sunaudoja šiek tiek daugiau atminties dėl laikinų kopijų.

---

## Balo pasirinkimas: vidurkis vs mediana

Laiko skirtumai tarp vidurkio ir medianos yra minimalūs, dažniausiai tik keli procentai, todėl abiejų metodų skirstymas yra panašiai efektyvus.

Medianai skirstant, Strategijos vykdymas šiek tiek ilgesnis nei pagal vidurkį, bet skirtumas nėra reikšmingas.

## Atmintis
- Atminties naudojimas auga tiesiškai su studentų skaičiumi.
- `vector` konteineris yra efektyvus atminties požiūriu, nes nenaudoja papildomų rodyklių kaip `list`.
- Kietiakiai sudaro apie ~60% bendro studentų kiekio, o vargsiukai – apie 40%, nepriklausomai nuo failo dydžio ar balo pasirinkimo.
- Skirstymo pagal vidurkį ar medianą pasirinkimas praktiškai neturi įtakos atminties sąnaudoms.

## Bendros išvados
# Vector ir List palyginimas pagal strategijas

Kaip ir min4ta prieš tai, Vidurkis ir Mediana iš esmės įtakos nedaro, todėl aptariamos tik strategijų poveikis vector, list.

## Strategija 1 – Dvi kopijos (kietiakiai + vargšiukai)

- **Vector**: labai greitas ir stabilus, nes duomenys saugomi nuosekliai atmintyje.  
- **List**: šiek tiek lėtesnis dėl rodyklių ir išskaidytos atminties.  
- **Išvada:** ši strategija **labiausiai tinka vector**, ypač dideliems failams.

---

## Strategija 2 – Viena kopija su trynimu

- **Vector**: labai **lėtas**, nes kiekvieno elemento trynimas perstumia kitus (ypač kai duomenų daug).  
- **List**: **greitas**, nes elementų trynimas tik pakeičia rodykles, be papildomų kopijų.  
- **Išvada:** ši strategija tinkama tik **list** konteineriui.  
  Naudojant ją su **vector**, laikas stipriai išauga (iki šimtų sekundžių su dideliais failais).

---

## Strategija 3 – Automatinis pasirinkimas

- **Vector** automatiškai pasirenka dažniau  **1 strategiją**, nes ji greičiausia jam.  
- **List** pasirenka įvairiai, bet **2 strategiją**, kuri dažnai efektyviausia jam.  
- **Išvada:** ši strategija užtikrina optimalų pasirinkimą pagal konteinerį.

---

## Bendros išvados

- **Vector** – geriausias dažnai pasirinkimas su **1 strategija** ir dideliais duomenimis.  
- **List** – geriausias su **2 strategija**, kai reikia daug trynimų arba duomenų mažiau, nes vector labai ilgai veikia.  
- **Strategija 2** yra **labai neefektyvi vector konteineriui**, nes trynimai užtrunka ilgai.  
- **Automatinis režimas (3)** išsprendžia šią problemą, pasirinkdamas greitesnį metodą.

---


