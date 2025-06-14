#pragma once
#include "SensorInterface.h"
#include "RobotControler.h"
#include <iostream>

/**
 * @file    SafeNavigation.h
 * @author  Tunay Aktug (152120221046)
 * @date    29/12/2024
 * @brief   SafeNavigation sinifinin deklarasyonu.
 *
 * Bu dosya, robotun guvenli bir sekilde ileriye veya geriye dogru hareket etmesini
 * saglayan SafeNavigation sinifinin deklarasyonunu icerir.
 */

 /**
  * @enum MOVESTATE
  * @brief Robotun hareket durumunu ifade eden enum.
  */
enum MOVESTATE {
    MOVING, /**< Robot su anda hareket halinde. */
    STOP    /**< Robot durmus durumda. */
};

/**
 * @class SafeNavigation
 * @brief Robotun ileri veya geri guvenli bir sekilde hareket etmesini yoneten sinif.
 *
 * SensorInterface kullanarak ortamda bulunan engelleri algilar ve robotun kontrollu bir sekilde
 * hareket etmesini saglar. RobotControler sinifina ait fonksiyonlari kullanarak robotu yonlendirir.
 */
class SafeNavigation {
private:
    /**
     * @brief Sensor degerlerini almak icin SensorInterface sinifina ait bir isaretci.
     */
    SensorInterface* IR;

    /**
     * @brief Robotu kontrol etmek icin RobotControler sinifina ait bir isaretci.
     */
    RobotControler* controller;

    /**
     * @brief Robotun hareket durumunu ifade eden degisken.
     */
    MOVESTATE state;

public:
    /**
     * @brief Parametreli kurucu fonksiyon.
     * @param irSensor SensorInterface nesnesine ait bir isaretci.
     * @param robotController RobotControler nesnesine ait bir isaretci.
     */
    SafeNavigation(SensorInterface* irSensor, RobotControler* robotController);

    /**
     * @brief Yikici (destructor) fonksiyon.
     */
    ~SafeNavigation();

    /**
     * @brief Robotu ileriye dogru guvenli bir sekilde hareket ettirir.
     */
    void moveForwardSafe();

    /**
     * @brief Robotu geriye dogru guvenli bir sekilde hareket ettirir.
     */
    void moveBackwardSafe();

    /**
     * @brief Robotun mevcut hareket durumunu dondurur.
     * @return MOVESTATE turunde hareket durumu.
     */
    MOVESTATE getState() const;
};