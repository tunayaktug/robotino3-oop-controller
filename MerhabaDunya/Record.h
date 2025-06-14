#pragma once

#include <fstream>
#include <iostream>

/**
 * @file    Record.h
 * @author  Yigit ATA (152120221105)
 * @date    16/12/2024
 * @brief   Record sinifinin ilani.
 *
 * Bu dosya, record islemlerini yapmamiza yarayan sinifin methodlarinin tanimlarini icerir.
 * Bu sinif ile dosya islemleri yapip verileri dosya icine kaydederiz ya da dosyadaki veriyi kullaniriz.
 */

using namespace std;

class Record {

private:
    string fileName;  ///< Islem yapilacak dosyanin adi.
    fstream file;     ///< Dosya islemleri icin kullanilan fstream nesnesi.

public:
    /**
     * @brief   Dosyayi acar.
     * @return  Dosya basariyla acilarsa true, aksi halde false doner.
     */
    bool openFile();

    /**
     * @brief   Dosyayi kapatir.
     * @return  Dosya basariyla kapatilarsa true, aksi halde false doner.
     */
    bool closeFile();

    /**
     * @brief   Dosya adini ayarlar.
     * @param   name Ayarlanacak dosya adi.
     */
    void setFileName(string name);

    /**
     * @brief   Dosyadan bir satir okur.
     * @return  Okunan satiri string olarak doner. Eger dosya sonuna ulasilirsa bos bir string doner.
     */
    string readLine();

    /**
     * @brief   Dosyaya bir satir yazar.
     * @param   str Yazilacak metin.
     * @return  Yazma islemi basarili olursa true, aksi halde false doner.
     */
    bool writeLine(string str);

    /**
     * @brief   "<<" operatoru icin asiri yukleme tanimi.
     *          Veriyi ostream nesnesine yazar.
     * @param   os Yazilacak ostream nesnesi.
     * @return  Record nesnesini referans olarak doner.
     */
    Record& operator<<(ostream& os);

    /**
     * @brief   ">>" operatoru icin asiri yukleme tanimi.
     *          Veriyi dosyaya yazar.
     * @param   str Yazilacak metin.
     * @return  Record nesnesini referans olarak doner.
     */
    Record& operator>>(string str);

    /**
     * @brief   Dosyanin sonuna ulasilip ulasilmadigini kontrol eder.
     * @return  Dosyanin sonuna ulasilmissa true, aksi halde false doner.
     */
    bool returnEof();
};
