#pragma once

/**
 * @file    FestoRobotSensorInterface.h
 * @author  Yigit ATA (152120221106)
 * @date    28/12/2024
 * @brief   FestoRobotSensorInterface sinifini tanimlar.
 *
 * Bu dosya, FestoRobotAPI ile etkilesim kuran bir sensor arayuzunu tanimlar.
 */

#include "SensorInterface.h"
#include "FestoRobotAPI.h"

 /**
  * @class FestoRobotSensorInterface
  * @brief FestoRobotAPI tabanli sensor arayuzunu temsil eder.
  *
  * Bu sinif, FestoRobotAPI ile sensorlerin entegrasyonunu saglamak icin bir arayuz tanimlar.
  * Sensorlerin FestoRobotAPI ile uyumlu bir sekilde calismasini saglar.
  */
class FestoRobotSensorInterface : public SensorInterface {
protected:
    /**
     * @brief FestoRobotAPI nesnesi.
     *
     * FestoRobotAPI ile etkilesim kurmak icin kullanilir. Sensorlerin veri alisverisini ve
     * robotik sistemlerle etkilesimini gerceklestirir.
     */
    FestoRobotAPI* robotAPI;
};
