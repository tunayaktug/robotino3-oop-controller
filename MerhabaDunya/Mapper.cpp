/**
 * @file    Mapper.cpp
 * @author  Emirhan Kesim (152120221116)
 * @date    20/12/2024
 * @brief   Mapper sinifi ve robot harita guncellemeleriyle ilgili islevlerin implementasyonu.
 *
 * Bu dosya, Mapper sinifina ait metodlari icerir. Robotun konum verileri ve lidar sensorunden alinan
 * olcumlerle harita guncellenir. Ayrica, harita kaydi ve harita gorsellestirme islemleri de burada gerceklestirilir.
 */

#include "Mapper.h"
#include "LidarSensor.h"
#include "SensorInterface.h"
#include "FestoRobotSensorInterface.h"
#include <cmath>
#include <iostream>

 /**
  * @brief Mapper sinifinin kurucusu.
  *
  * Mapper sinifi, robotun konum bilgileri ve harita boyutlarini kullanarak bir harita nesnesi olusturur.
  * Robot kontrolcusu ile baglantiyi kurar ve lidar sensoru icin bellek tahsisi yapar.
  *
  * @param mapWidth Haritanin genisligi.
  * @param mapHeight Haritanin yuksekligi.
  * @param robotObj Robot kontroloru nesnesi.
  */
Mapper::Mapper(int mapWidth, int mapHeight, RobotControler& robotObj) : map(mapWidth, mapHeight)
{
    controller = &robotObj;  // Robot kontrolorusunun referansini sakliyoruz
    controller->connectRobot();  // Robotla baglantiyi kuruyoruz
    lidar = new LidarSensor();  // Lidar sensoru icin dinamik bellek tahsisi yapiyoruz

    // Harita boyutlarini ekrana yazdiriyoruz
    std::cout << mapWidth << "x" << mapHeight << "." << std::endl;
}

/**
 * @brief Mapper sinifinin yikicisi.
 *
 * Dinamik olarak tahsis edilen lidar nesnesini serbest birakir.
 */
Mapper::~Mapper() {
    delete lidar;
}

/**
 * @brief Haritayi gunceller.
 *
 * Lidar sensorunden alinan veriler ve robotun konum bilgileri kullanilarak harita guncellenir.
 * Robotun X, Y koordinatlari ve yonu dikkate alinarak, lidar olcumleri dunya koordinatlarina
 * donusturulur ve harita grid'ine eklenir.
 */
void Mapper::updateMap() {
    if (!controller) {  // Robot kontrolorusunun gecerli olup olmadigini kontrol ediyoruz
        std::cerr << "Robot controller is not initialized!" << std::endl;
        return;
    }

    controller->connectRobot();  // Robot ile baglantiyi tekrar kontrol ediyoruz
    Pose robotPose = controller->getPose();  // Robotun konum bilgisini aliyoruz
    double robotX = robotPose.getX();  // Robotun X koordinatini aliyoruz
    double robotY = robotPose.getY();  // Robotun Y koordinatini aliyoruz
    double robotTh = robotPose.getTh();  // Robotun yonunu aliyoruz

    lidar->update();  // Lidar sensorunden gelen verileri guncelliyoruz

    // Lidar verilerini isliyoruz
    for (int i = 0; i < 667; ++i) {
        double range = lidar->getSensorValue(i);  // Lidar olcum degerini aliyoruz
        if (range <= 0) continue;  // Gecersiz olcum varsa atliyoruz

        double angle = robotTh + (120 - (i * 0.36));  // Dunya koordinatlarinda olcum acisini hesapliyoruz
        double worldX = robotX + range * cos(angle * 3.14159265358979323846 / 180.0);  // Dunya X koordinatini hesapliyoruz
        double worldY = robotY + range * sin(angle * 3.14159265358979323846 / 180.0);  // Dunya Y koordinatini hesapliyoruz

        double gridX = (worldX)+7.5;  // Dunya X koordinatini harita grid'ine donusturuyoruz
        double gridY = (worldY)+7.5;  // Dunya Y koordinatini harita grid'ine donusturuyoruz

        // Harita sinirlari disinda bir nokta ise atliyoruz
        if (gridX < 0 || gridX >= map.getNumberX() || gridY < 0 || gridY >= map.getNumberY()) {
            continue;
        }

        map.insertPoint(Point(gridX, gridY));  // Noktayi haritaya ekliyoruz
    }

    // Robotun konumunu ve harita guncellemesinin tamamlandigini yazdiriyoruz
    std::cout << "Robot Position: " << controller->getPose().getX() << ", "
        << controller->getPose().getY() << std::endl;
    std::cout << "Map updated." << std::endl;
}

/**
 * @brief Haritayi bir dosyaya kaydeder.
 *
 * Harita, "map.txt" adli bir dosyaya kaydedilir. Her harita noktasi icin 'x' veya '.' karakteri
 * kullanilarak harita grid'i dosyaya yazilir.
 *
 * @return Basarili olursa true, aksi halde false doner.
 */
bool Mapper::recordMap() const {
    const std::string filename = "map.txt";  // Harita dosyasinin adi

    Record record;  // Kayit nesnesi olusturuluyor
    record.setFileName(filename);  // Dosya adi belirleniyor

    if (record.openFile()) {  // Dosya acma islemi basarisizsa hata veriyoruz
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    // Harita verilerini dosyaya yaziyoruz
    for (int i = 0; i < map.getNumberX(); ++i) {
        std::string line;
        for (int j = 0; j < map.getNumberY(); ++j) {
            // Harita grid'inde isaretli alanlari 'x', bos alanlari '.' olarak yaziyoruz
            line += (map.getGrid(i, j) == 1) ? "x" : ".";
        }
        record.writeLine(line);  // Satiri dosyaya yaziyoruz
    }

    if (record.closeFile()) {  // Dosya kapatma islemi basarisizsa hata veriyoruz
        std::cerr << "Failed to close file: " << filename << std::endl;
        return false;
    }

    std::cout << "Map successfully saved to " << filename << "." << std::endl;
    return true;
}

/**
 * @brief Haritayi konsolda gosterir.
 *
 * Harita, kullaniciya gorsel olarak konsolda gosterilir.
 */
void Mapper::showMap() const {
    map.showMap();  // Haritayi ekranda gosteriyoruz
}
