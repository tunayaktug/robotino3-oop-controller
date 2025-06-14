#pragma once

/**
 * @file    SensorInterface.h
 * @author  Yigit ATA (152120221106)
 * @date    28/12/2024
 * @brief   SensorInterface sinifinin baslik dosyasi.
 *
 * Bu dosya, robotik sistemlerde farkli sensor tiplerini temsil eden soyut bir sinif sunar.
 * Turetilen siniflar, farkli sensorlerden veri almayi ve bu verileri islemede kullanilan
 * temel metodlari icermelidir.
 */

#include <iostream>
using namespace std;

/**
 * @class SensorInterface
 * @brief Sensorler icin bir arayuz sinifi.
 *
 * Bu soyut sinif, turetilen sensor siniflarinda implement edilmesi gereken temel metodlari tanimlar.
 * Bu sinif, sensorlerin tipini tanimlama, veri alma ve guncelleme gibi islevleri icermektedir.
 */
class SensorInterface {
private:
    string sensorType; ///< Sensorun tipi (string olarak tanimlanmistir).

public:
    /**
     * @brief Sensor verilerini gunceller.
     *
     * Bu soyut metod, sensorun mevcut verilerini yenilemek icin turetilen siniflarda implement edilmelidir.
     */
    virtual void update() = 0;

    /**
     * @brief Sensor tipini dondurur.
     *
     * Bu soyut metod, sensorun turunu string olarak dondurmek icin turetilen siniflarda implement edilmelidir.
     *
     * @return string Sensor tipi.
     */
    virtual string getSensorType() = 0;

    /**
     * @brief Belirtilen bir index'teki sensor degerini dondurur.
     *
     * Bu soyut metod, belirli bir index'e karsilik gelen sensor degerini dondurmek icin turetilen siniflarda
     * implement edilmelidir.
     *
     * @param index Sensor degeri istenen index numarasi.
     * @return double Belirtilen index'teki sensor degeri.
     */
    virtual double getSensorValue(int index) = 0;
};
