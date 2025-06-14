#pragma once
#include <iostream>
#include "FestoRobotSensorInterface.h"

/**
 * @file    IRSensor.h
 * @author  Tunay Aktug (152120221046)
 * @date    29/12/2024
 * @brief   IR sensor degerlerini okumak ve yonetmek icin kullanilan IRSensor sinifi.
 *
 * Bu dosya, IR sensorlerinden deger okumak ve bu degerleri yonetmek icin kullanilan
 * IRSensor sinifinin deklarasyonunu icerir.
 */

 /**
  * @class IRSensor
  * @brief IR sensorlerini yonetmek icin kullanilan sinif.
  *
  * Bu sinif, IR sensorlerinden alinan mesafe verilerini yonetir ve bu verilere erisim saglar.
  * Ayrica FestoRobotAPI ile haberlesmek icin gerekli olan bir isaretci barindirir.
  */
class IRSensor : public FestoRobotSensorInterface {
private:
    /**
     * @brief IR sensorlerin mesafe degerlerini saklayan dizi.
     */
    double ranges[9];

    /**
     * @brief FestoRobotAPI sinifina ait bir isaretci.
     */
    FestoRobotAPI* robotAPI;

public:

    /**
     * @brief Varsayilan kurucu fonksiyon.
     *
     * Bu fonksiyon IR sensor degerlerini sifirlar ve robotAPI isaretcisini nullptr olarak baslatir.
     */
    IRSensor();

    /**
     * @brief Parametreli kurucu fonksiyon.
     *
     * Bu fonksiyon, IR sensor degerlerini sifirlar ve robotAPI isaretcisini parametre olarak gelen
     * FestoRobotAPI nesnesi ile iliskilendirir.
     *
     * @param api FestoRobotAPI sinifina ait bir isaretci.
     */
    IRSensor(FestoRobotAPI* api);

    /**
     * @brief Yikici fonksiyon.
     *
     * Bu fonksiyon gerekli kaynaklarin serbest birakilmasini saglar.
     */
    ~IRSensor();

    /**
     * @brief IR sensor degerlerini gunceller.
     *
     * Bu fonksiyon, FestoRobotAPI uzerinden alinan degerleri ranges dizisine yazar.
     */
    void update();

    /**
     * @brief Belirtilen sensorun mesafe degerini dondurur.
     *
     * Bu fonksiyon, kullanici tarafindan belirtilen indeks degerine gore ilgili sensorun
     * mesafe degerini dondurur.
     *
     * @param i Sensor dizisinin indeksi (0-8).
     * @return Ilgili sensorun mesafe degeri.
     */
    double getRange(int i) const;

    /**
     * @brief [] operatorunun asiri yuklenmis hali.
     *
     * Bu fonksiyon, sensorlerin mesafe degerlerine dizi operatoru [] kullanilarak erisim
     * saglanmasina olanak tanir.
     *
     * @param i Sensor dizisinin indeksi (0-8).
     * @return Ilgili sensorun mesafe degeri.
     */
    double operator[](int i) const;

    /**
     * @brief Sensor tipini donduren fonksiyon.
     *
     * Bu fonksiyon, sensorun turunu temsil eden bir string degeri dondurur.
     *
     * @return Sensorun tipi.
     */
    string getSensorType();

    /**
     * @brief Belirtilen indeksteki sensorun degerini dondurur.
     *
     * Bu fonksiyon, belirtilen indeksteki sensorun mesafe degerini dondurur.
     *
     * @param i Sensor dizisinin indeksi (0-8).
     * @return Ilgili sensorun mesafe degeri.
     */
    double getSensorValue(int i);
};