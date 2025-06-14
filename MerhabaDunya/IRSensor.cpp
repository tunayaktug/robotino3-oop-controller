#include "IRSensor.h"

/**
 * @file    IRSensor.cpp
 * @author  Tunay Aktug (152120221046)
 * @date    29/12/2024
 * @brief   IRSensor sinifinin implementasyonu.
 *
 * Bu dosya, IRSensor sinifinin constructor ve destructor fonksiyonlarini,
 * sensor degerlerini guncellemek ve geri dondurmek icin kullanilan metodlarini
 * ve [] operatorunun asiri yuklenmis surumunu icerir.
 */

 /**
  * @brief IRSensor sinifinin varsayilan kurucu fonksiyonu.
  *
  * RobotAPI'yi dinamik olarak baslatir ve sensor degerlerini sifirlar.
  */
IRSensor::IRSensor() {
    robotAPI = new FestoRobotAPI();  // API'yi dinamik olarak baslatir
    for (int i = 0; i < 9; i++) {
        ranges[i] = 0.0;  // Tum sensor degerlerini sifirlar
    }
}

/**
 * @brief Parametreli kurucu fonksiyon.
 *
 * Gelen FestoRobotAPI nesnesi ile robotAPI isaretcisini baglar ve sensor degerlerini sifirlar.
 *
 * @param api FestoRobotAPI sinifina ait bir isaretci.
 */
IRSensor::IRSensor(FestoRobotAPI* api) : robotAPI(api) {
    for (int i = 0; i < 9; ++i) {
        ranges[i] = 0.0;  // Tum sensor degerlerini sifirlar
    }
}

/**
 * @brief IRSensor sinifinin yikici (destructor) fonksiyonu.
 *
 * Dinamik olarak ayrilan robotAPI kaynagini serbest birakir.
 */
IRSensor::~IRSensor() {
    delete robotAPI;  // Hafiza kaybini onlemek icin ayrilan bellek serbest birakilir
}

/**
 * @brief Sensor degerlerini gunceller.
 *
 * FestoRobotAPI uzerinden alinan degerleri ranges dizisine yazar.
 * Eger robotAPI gecerli degilse bir hata mesaji basar.
 */
void IRSensor::update() {
    if (!robotAPI) {
        std::cout << "Hata: Robot API baglantisi yok!" << std::endl;
    }
    else {
        for (int i = 0; i < 9; ++i) {
            ranges[i] = robotAPI->getIRRange(i);  // Sensor degerini gunceller
            std::cout << "Sensor " << i << " mesafesi: " << ranges[i] << " m" << std::endl;
        }
    }
}

/**
 * @brief Belirli bir sensorun mesafe degerini dondurur.
 *
 * @param i Sensor dizisinin indeksi (0-8).
 * @return Istek uzerine sensorun mesafe degeri. Gecersiz indeks girildiginde 0.0 dondurur.
 */
double IRSensor::getRange(int i) const {
    if (i < 0 || i > 8) {
        std::cout << "Gecersiz deger girdiniz. Sensor indeksi 0 ile 8 arasinda olmali! (Toplam 9 sensor var.)" << std::endl;
        return 0.0;
    }
    return ranges[i];
}

/**
 * @brief [] operatorunun asiri yuklenmis surumu.
 *
 * getRange fonksiyonu ile ayni islevi gerceklestirir. Kullanici sensorlere [] operatoru ile erisebilir.
 *
 * @param i Sensor dizisinin indeksi (0-8).
 * @return Istek uzerine sensorun mesafe degeri. Gecersiz indeks girildiginde 0.0 dondurur.
 */
double IRSensor::operator[](int i) const {
    if (i < 0 || i > 8) {
        std::cout << "Gecersiz deger girdiniz. Sensor indeksi 0 ile 8 arasinda olmali! (Toplam 9 sensor var.)" << std::endl;
        return 0.0;
    }
    return getRange(i);
}

/**
 * @brief Sensorun tipini donduren fonksiyon.
 *
 * IR sensor tipini string olarak geri dondurur.
 *
 * @return Sensorun tipi "IR" olarak dondurulur.
 */
string IRSensor::getSensorType() {
    return "IR";
}

/**
 * @brief Belirtilen indeksteki sensorun mesafe degerini dondurur.
 *
 * @param i Sensor dizisinin indeksi (0-8).
 * @return Sensorun mesafe degeri.
 */
double IRSensor::getSensorValue(int i) {
    return getRange(i);  // getRange fonksiyonunu kullanarak deger dondurur
}