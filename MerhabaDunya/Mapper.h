/**
 * @file    Mapper.h
 * @author  Emirhan Kesim (152120221116)
 * @date    20/12/2024
 * @brief   Mapper sinifinin tanimlamalarini iceren baslik dosyasi.
 *
 * Mapper sinifi, harita olusturma, guncelleme, dosyaya kaydetme ve
 * ekranda gostermeye gibi islemleri gerceklestirmek icin gerekli fonksiyonlari saglar.
 * Ayrica, RobotControler ve LidarSensor gibi diger siniflari kullanir.
 */

#pragma once
#include "MAP.h"
#include "SensorInterface.h"
#include "Record.h"
#include "RobotControler.h"

 /**
  * @brief Mapper sinifi, robot hareketlerini ve sensor verilerini kullanarak harita olusturur ve yonetir.
  */
class Mapper {
private:
    MAP map;                      /**< Haritanin tutuldugu MAP nesnesi. */
    RobotControler* controller;   /**< Robotun kontrolunu saglayan nesne. */
    SensorInterface* lidar;            /**< Lidar sensor verilerini yoneten nesne. */

public:
    /**
     * @brief Mapper sinifinin kurucusu.
     *
     * @param mapWidth Haritanin genisligi.
     * @param mapHeight Haritanin yuksekligi.
     */
    Mapper(int mapWidth, int mapHeight, RobotControler& robotObj);

    /**
     * @brief Mapper sinifinin yikicisi.
     */
    ~Mapper();

    /**
     * @brief Haritayi lidar verilerine ve robotun konum bilgilerine gore gunceller.
     */
    void updateMap();

    /**
     * @brief Haritayi bir dosyaya kaydeder.
     *
     * @return Basarili olursa true, aksi halde false doner.
     */
    bool recordMap() const;

    /**
     * @brief Haritayi ekranda gosterir.
     */
    void showMap() const;
};
