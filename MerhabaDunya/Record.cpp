/**
 * @file    Record.cpp
 * @author  Yigit ATA (152120221105)
 * @date    16/12/2024
 * @brief   Record sinifinin implementasyonu.
 *
 * Bu dosya, record islemlerini yapmamiza yarayan sinifin methodlarinin implementasyonlarini icerir.
 * Bu sinif ile dosya islemleri yapip verileri dosya icine kaydederiz ya da dosyadaki veriyi kullaniriz.
 */

 // Gerekli kutuphanelerin alinmasi
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "Record.h"

using namespace std;

/**
 * @brief   Dosyayi acar.
 * @return  Dosya basariyla acilarsa true, aksi halde false doner.
 */
bool Record::openFile() {
    file.open(fileName, ios::in | ios::out | ios::app); // Dosyayi hem okuma hem de yazma yapmak uzere aciyoruz.
    if (!file.is_open()) {
        cout << "Dosya acilamadi." << endl;
        return true; // Dosyanin acilamasi durumunda uyari verilir.
    }
    else return false;
}

/**
 * @brief   Dosyayi kapatir.
 * @return  Dosya basariyla kapatilarsa true, aksi halde false doner.
 */
bool Record::closeFile() {
    file.close(); // Dosyayi kapatiyoruz.
    if (!file.is_open()) {
        return false;
    } // Dosyanin kapanmamasi durumunda false doner.
    else return true;
}

/**
 * @brief   Dosya adini ayarlar.
 * @param   name Ayarlanacak dosya adi.
 */
void Record::setFileName(const string name) {
    fileName = name; // Belirtilen ismi dosya ismi olarak aliyoruz.
}

/**
 * @brief   Dosyadan bir satir okur.
 * @return  Okunan satiri string olarak doner. Eger dosya sonuna ulasilirse bos bir string doner.
 * @throws  runtime_error Eger dosya acik degilse hata firlatir.
 */
string Record::readLine() {
    string line; // Okunacak satir tanimlamasi.

    try {
        if (!file.is_open()) {
            throw runtime_error("Okuma Basarisiz: Dosya acilamadi");
        } // Dosya acikligi kontrolu.

        if (getline(file, line)) {
            return line;
        } // Okunan satiri degiskene atama ve donurma islemi.
        else if (file.eof()) {
            return "";
        } // Dosya sonuna gelindiyse bos deger donderir.
    }
    catch (const runtime_error& e) {
        cout << "Hata: " << e.what() << endl;
        return "";
    } // Dosya islemiyle ilgili olusabilecek hatayi donderir.
}

/**
 * @brief   Dosyaya bir satir yazar.
 * @param   str Yazilacak metin.
 * @return  Yazma islemi basarili olursa true, aksi halde false doner.
 */
bool Record::writeLine(const string str) {
    if (!file.is_open()) {
        cout << "Yazma islemi basarisiz." << endl;
        return false;
    } // Dosya acik kontrolu.

    file << str << endl; // Belirlenen degiskenin dosyaya yazilmasi.
    return true;
}

/**
 * @brief   ">>" operatoru icin asiri yukleme tanimi.
 *          Veriyi dosyaya yazar.
 * @param   str Yazilacak metin.
 * @return  Record nesnesini referans olarak doner.
 * @throws  runtime_error Yazma islemi basarisiz olursa hata firlatir.
 */
Record& Record::operator>>(const string str) {
    if (!writeLine(str)) {
        throw runtime_error("Yazma islemi basarisiz oldu");
    }
    return *this;
}

/**
 * @brief   "<<" operatoru icin asiri yukleme tanimi.
 *          Veriyi ostream nesnesine yazar.
 * @param   os Yazilacak ostream nesnesi.
 * @return  Record nesnesini referans olarak doner.
 * @throws  runtime_error Okuma islemi basarisiz olursa hata firlatir.
 */
Record& Record::operator<<(std::ostream& os) {
    string line;
    if (getline(file, line)) {
        os << line << endl;
    }
    else if (file.eof()) {
        os << line << endl;
        os << "Dosya sonuna gelindi." << endl;
    }
    else {
        throw runtime_error("Okuma Basarisiz: Dosya okunamadi");
    }
    return *this;
}

/**
 * @brief   Dosyanin sonuna ulasilip ulasilmadigini kontrol eder.
 * @return  Dosyanin sonuna ulasilmissa false, aksi halde true doner.
 */
bool Record::returnEof() {
    if (file.eof()) return false;
    else return true;
}
