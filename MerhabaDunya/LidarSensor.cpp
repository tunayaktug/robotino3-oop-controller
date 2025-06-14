#ifndef LIDAR_SENSOR_H
#define LIDAR_SENSOR_H

/**
 * @file    LidarSensor.cpp
 * @author  Yigit ATA (152120221106)
 * @date    28/12/2024
 * @brief   LidarSensor sinifinin implementasyonu.
 *
 * Bu dosya robotta bulunan lidar sensorunun verilerini elde etmeye ve islemeye yarar.
 */

#include <iostream>
#include "LidarSensor.h"
#include "FestoRobotAPI.h"

using namespace std;

/**
 * @class LidarSensor
 * @brief Robotun lidar sensorunden veri almak ve bu verileri islemek icin kullanilan sinif.
 */

 /**
  * @brief LidarSensor sinifinin constructor fonksiyonu.
  *
  * Bu fonksiyon, robotla baglanti kurar ve lidar sensorunun veri boyutunu (rangeNumber) alir.
  * Ayrica lidar verilerinin depolanacagi dinamik bir dizi (ranges) olusturur.
  */
LidarSensor::LidarSensor() {
    robotAPI = new FestoRobotAPI(); // FestoRobotAPI sinifina ait robotAPI nesnesi olusturulur.
    robotAPI->connect(); // Robot baglantisini kurar.
    rangeNumber = robotAPI->getLidarRangeNumber(); // Lidar sensorunun verileri icin boyut alinir.
    ranges = new double[rangeNumber]; // Ranges dizisini olusturur.
    for (int i = 0; i < rangeNumber; i++) {
        ranges[i] = 0.0; // Dizinin tum elemanlari sifirlanir.
    }
}

/**
 * @brief LidarSensor sinifinin yikim fonksiyonu.
 *
 * Bu fonksiyon, siniftan cikarken sinif tarafindan kullanilan kaynaklari serbest birakarak
 * gereksiz bellek kullanimini engeller. Bu sayede, bellek sizintilari onlenir ve kaynaklarin verimli
 * bir sekilde yonetilmesi saglanir.
 */
LidarSensor::~LidarSensor() {
    delete[] ranges;
}

/**
 * @brief Belirtilen indisteki menzil degerini dondurur.
 *
 * @param index Menzil degeri istenen index.
 * @return double Menzil degeri.
 * @throws std::out_of_range Eger index gecerli aralik disinda ise bir hata firlatilir.
 */
double LidarSensor::getRange(int index) {
    if (index < 0 || index >= rangeNumber) {
        throw std::out_of_range("Index out of range");
    }

    return ranges[index];
}

/**
 * @brief Lidar sensorundeki en yuksek menzil degerini dondurur.
 *
 * @param index En yuksek degerin bulundugu indexi dondurur.
 * @return double En yuksek menzil degeri.
 */
double LidarSensor::getMax(int& index) {
    double maxVal = INT16_MIN;
    index = -1; // Baslangic degeri
    for (int i = 0; i < rangeNumber; i++) {
        if (maxVal < ranges[i] && ranges[i] < 10) {
            maxVal = ranges[i];
            index = i; // Maksimum degerin indeksini kaydeder
        }
    }
    return maxVal;
}

/**
 * @brief Lidar sensorundeki en dusuk menzil degerini dondurur.
 *
 * @param index En dusuk degerin bulundugu indexi dondurur.
 * @return double En dusuk menzil degeri.
 */
double LidarSensor::getMin(int& index) {
    double minVal = INT16_MAX;
    index = -1; // Baslangic degeri
    for (int i = 0; i < rangeNumber; i++) {
        if (minVal > ranges[i]) {
            minVal = ranges[i];
            index = i; // Minimum degerin indeksini kaydeder
        }
    }
    return minVal;
}

/**
 * @brief Lidar sensorunun menzil degerlerini gunceller.
 *
 * Bu fonksiyon, lidar sensorunden yeni veriler alir ve mevcut diziyi gunceller.
 */
void LidarSensor::update() {
    delete[] ranges; // Onceki degerleri silme islemi

    // Yeni veriler icin yer acma
    float* tempRanges = new float[rangeNumber];
    ranges = new double[rangeNumber];

    robotAPI->getLidarRange(tempRanges); // Yeni lidar verilerini alir

    // Verileri double turune donusturme
    for (int i = 0; i < rangeNumber; i++) {
        ranges[i] = static_cast<double>(tempRanges[i]);
    }

    delete[] tempRanges; // Gecici float dizisini sil
}

/**
 * @brief Indis operatoru asiri yuklemesi.
 *
 * @param index Lidar sensorundeki degeri almak icin kullanilan index.
 * @return double Ilgili indisteki menzil degeri.
 * @throws std::out_of_range Eger index gecerli aralik disinda ise bir hata firlatilir.
 */
double LidarSensor::operator[](int index) {
    if (index < 0 || index >= rangeNumber) {
        throw out_of_range("Index out of range");
    }

    return ranges[index];
}

/**
 * @brief Verilen bir indisteki aci degerini dondurur.
 *
 * @param i Aci degeri istenen index.
 * @return double Hesaplanan aci degeri.
 */
double LidarSensor::getAngle(int i) {
    return 120 - (i * 0.36); // Aci hesaplama
}

/**
 * @brief Lidar sensorundeki veri sayisini dondurur.
 *
 * @return int Lidar verilerinin sayisi.
 */
int LidarSensor::getRangeNumber() {
    return rangeNumber;
}

/**
 * @brief Lidar sensorundeki tum menzil degerlerini dondurur.
 *
 * @return double* Lidar verilerini iceren dizinin isaretcisi.
 */
double* LidarSensor::getRanges() {
    return ranges; // Tum menzil verilerini dondurur.
}

/**
 * @brief Verilen indeks icin sensor degerini dondurur.
 *
 * @param i Sensor degeri istenen index.
 * @return double Sensor degeri.
 */
double LidarSensor::getSensorValue(int i) {
    return getRange(i);
}

/**
 * @brief Sensor tipini dondurur.
 *
 * @return string Sensor tipi (“Lidar”).
 */
string LidarSensor::getSensorType() {
    return "Lidar";
}

#endif // LIDAR_SENSOR_H
