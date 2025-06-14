#pragma once

/**
 * @file    LidarSensor.h
 * @author  Yigit ATA (152120221106)
 * @date    14/12/2024
 * @brief   LidarSensor sinifinin baslik dosyasi.
 *
 * Bu dosya, robot uzerindeki lidar sensorunun verilerini almak ve islemek icin gereken
 * fonksiyonlari icerir. Lidar sensorunden alinan mesafe verileri, aci hesaplamalari ve
 * menzil degerlerinin analiz edilmesi gibi islemler icin kullanilir.
 */

#include "FestoRobotSensorInterface.h"

 /**
  * @class LidarSensor
  * @brief Lidar sensorunden veri almayi ve islemi saglayan sinif.
  *
  * Bu sinif, robotun uzerindeki lidar sensorunden alinan mesafe verilerini depolar ve
  * bu verilerle cesitli analizler yapmaniza olanak tanir. Ayrica, sensorden gelen verilerle
  * en yuksek ve en dusuk mesafe degerlerini bulma, aci hesaplamalari yapma gibi islevsellikler sunar.
  */
class LidarSensor : public FestoRobotSensorInterface {
private:
    double* ranges = nullptr; ///< Lidar sensorunden alinan mesafe verilerini tutan dinamik dizi
    int rangeNumber = 0; ///< Lidar sensorunden alinan verilerin sayisi

public:
    /**
     * @brief LidarSensor sinifinin baslangic fonksiyonu.
     *
     * Bu fonksiyon, robotla baglantiyi kurar, lidar sensorunun veri sayisini alir ve
     * sensorun verilerini saklayacak bir dizi olusturur. Baglanti saglandiktan sonra
     * lidar verilerini almaya hazir hale gelir.
     */
    LidarSensor();

    /**
     * @brief LidarSensor sinifinin yikim fonksiyonu.
     *
     * Bu fonksiyon, siniftan cikarken sinif tarafindan kullanilan kaynaklari serbest birakarak
     * gereksiz bellek kullanimini engeller. Bu sayede, bellek sizintilari onlenir ve kaynaklarin verimli
     * bir sekilde yonetilmesi saglanir.
     */
    ~LidarSensor();

    /**
     * @brief Belirtilen index'teki menzil degerini dondurur.
     *
     * Lidar sensorunden alinan mesafe verileri dizisinde verilen index numarasina karsilik
     * gelen menzil degerini dondurur. Eger index gecerli bir aralikta degilse, bir hata firlatilir.
     *
     * @param index Menzil degeri istenen index numarasi.
     * @return double Verilen index numarasindaki menzil degeri.
     * @throws std::out_of_range Eger index gecerli aralik disinda ise bir hata firlatilir.
     */
    double getRange(int index);

    /**
     * @brief Lidar sensorundeki en yuksek menzil degerini bulur ve dondurur.
     *
     * Bu fonksiyon, lidar sensorunun dondurdugu tum menzil verileri arasindan en yuksek degeri
     * bulur ve bu degeri geri dondurur. Ayrica en yuksek degerin bulundugu index bilgisini de
     * parametre olarak alir.
     *
     * @param index En yuksek degerin bulundugu index'i dondurur.
     * @return double Lidar sensorundeki en yuksek menzil degeri.
     */
    double getMax(int& index);

    /**
     * @brief Lidar sensorundeki en dusuk menzil degerini bulur ve dondurur.
     *
     * Bu fonksiyon, lidar sensorunun dondurdugu tum menzil verileri arasindan en dusuk degeri
     * bulur ve bu degeri geri dondurur. Ayrica en dusuk degerin bulundugu index bilgisini de
     * parametre olarak alir.
     *
     * @param index En dusuk degerin bulundugu index'i dondurur.
     * @return double Lidar sensorundeki en dusuk menzil degeri.
     */
    double getMin(int& index);

    /**
     * @brief Lidar sensorundeki verileri gunceller.
     *
     * Bu fonksiyon, lidar sensorunden yeni veriler alir ve mevcut veri dizisini gunceller.
     * Onceden alinmis olan veriler silinir ve yerine yeni veriler atanir.
     */
    void update();

    /**
     * @brief Indis operatorunu asiri yukler.
     *
     * Bu fonksiyon, dizinin elemanlarina indeks ile erisim saglamak icin operatoru asiri yukler.
     * Boylece dizinin elemanlarina daha kolay erisebilirsiniz. Gecersiz bir index girilirse, hata firlatilir.
     *
     * @param index Erisilmek istenen index.
     * @return double Belirtilen index'teki menzil degeri.
     * @throws std::out_of_range Eger index gecerli aralik disinda ise bir hata firlatilir.
     */
    double operator[](int index);

    /**
     * @brief Verilen bir index icin aci degerini hesaplar ve dondurur.
     *
     * Lidar sensorunun her verisi icin bir aci degeri hesaplanir. Bu fonksiyon, verilen index icin
     * o degerin karsilik geldigi aciyi dondurur.
     *
     * @param i Aci degeri istenen index numarasi.
     * @return double Hesaplanan aci degeri.
     */
    double getAngle(int i);

    /**
     * @brief Lidar sensorundeki veri sayisini dondurur.
     *
     * Bu fonksiyon, lidar sensorunden alinan verilerin toplam sayisini dondurur.
     *
     * @return int Lidar verilerinin sayisi.
     */
    int getRangeNumber();

    /**
     * @brief Lidar sensorundeki tum menzil degerlerini dondurur.
     *
     * Bu fonksiyon, lidar sensorunden alinan tum mesafe verilerini iceren diziyi dondurur.
     *
     * @return double* Lidar verilerini iceren dizinin isaretcisi.
     */
    double* getRanges();

    /**
     * @brief Belirtilen bir index'teki sensor degerini dondurur.
     *
     * Bu fonksiyon, getRange fonksiyonunun kolay erisim saglayan bir sarmasidir.
     *
     * @param i Sensor degeri istenen index numarasi.
     * @return double Belirtilen index'teki sensor degeri.
     */
    double getSensorValue(int i);

    /**
     * @brief Sensor tipini dondurur.
     *
     * Bu fonksiyon, sensor tipini bir string olarak dondurur.
     *
     * @return std::string Sensor tipi ("Lidar").
     */
    string getSensorType();
};
