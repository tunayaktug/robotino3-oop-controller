#include "SafeNavigation.h"
#include <chrono>
#include <thread>
#include <iostream>

/**
 * @file    SafeNavigation.cpp
 * @author  Tunay Aktug (152120221046)
 * @date    29/12/2024
 * @brief   SafeNavigation sinifinin implementasyonu.
 *
 * Bu dosya, robotun guvenli bir sekilde hareket etmesini saglayan SafeNavigation
 * sinifinin implementasyonunu icerir. moveForwardSafe() ve moveBackwardSafe()
 * fonksiyonlari, robotun guvenli bir sekilde ileriye veya geriye dogru hareket
 * etmesini saglar.
 */

using namespace std;

constexpr int NUM_SENSORS = 9;                // Kullanilan sensor sayisi
constexpr double OBSTACLE_THRESHOLD = 0.395; // Engel algilama mesafesi (metre)

/**
 * @brief SafeNavigation sinifinin kurucu fonksiyonu.
 *
 * SensorInterface ve RobotControler siniflarina ait nesneleri baglar ve hareket durumunu STOP olarak baslatir.
 *
 * @param irSensor SensorInterface sinifina ait bir isaretci.
 * @param robotController RobotControler sinifina ait bir isaretci.
 */
SafeNavigation::SafeNavigation(SensorInterface* irSensor, RobotControler* robotController)
    : IR(irSensor), controller(robotController), state(STOP) {
}

/**
 * @brief SafeNavigation sinifinin yikici (destructor) fonksiyonu.
 */
SafeNavigation::~SafeNavigation() {}

/**
 * @brief Robotun mevcut hareket durumunu dondurur.
 *
 * @return Robotun hareket durumu (MOVESTATE turunde).
 */
MOVESTATE SafeNavigation::getState() const {
    return state;
}

/**
 * @brief Robotun guvenli bir sekilde ileri hareket etmesini saglar.
 *
 * SensorInterface'i kullanarak engelleri algilar. Engel tespit edildiginde robotu durdurur.
 * Robot kontrolu icin RobotControler sinifini kullanir.
 */
void SafeNavigation::moveForwardSafe() {
    // Sensor veya kontrol sinifi bagli degilse hata mesaji bas
    if (!IR || !controller) {
        cout << "Hata: Sensor veya RobotControler bagli degil!" << endl;
        return;
    }

    state = MOVING;
    cout << "Robot guvenli ileri hareketine basladi..." << endl;

    // Hareket ederken durum MOVING olarak kalir
    while (state == MOVING) {
        // Sensor degerlerini guncelle
        IR->update();

        // Tum sensor degerlerini al
        double ranges[NUM_SENSORS];
        for (int i = 0; i < NUM_SENSORS; i++) {
            ranges[i] = IR->getSensorValue(i); // SensorInterface API'si ile deger aliniyor
        }

        bool obstacleDetected = false; // Engel tespit durumu
        int forwardSensors[] = { 0, 1, 8 }; // Ileri algilama yapan sensorler

        // Ileri sensorler icin engel tespiti yap
        for (int i : forwardSensors) {
            if (ranges[i] < 0.0) {
                cout << "Hata: Sensor " << i << " icin gecersiz mesafe degeri!" << endl;
                continue;
            }
            if (ranges[i] <= OBSTACLE_THRESHOLD) {
                obstacleDetected = true;
                cout << "Engel tespit edildi! Sensor " << i
                    << " mesafesi " << ranges[i]
                    << " m, threshold = " << OBSTACLE_THRESHOLD << endl;
                break;
            }
        }

        // Engel tespit edildiyse robot durdurulur
        if (obstacleDetected) {
            state = STOP;
            cout << "Robot durduruldu. Engel ile aradaki mesafe = "
                << OBSTACLE_THRESHOLD << " m veya daha az." << endl;
            break;
        }

        // Robot ileri hareket eder
        controller->moveForward();
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Kisa bir gecikme
        controller->stop(); // Duraklat
    }

    // Robotu durdur
    controller->stop();
}

/**
 * @brief Robotun guvenli bir sekilde geri hareket etmesini saglar.
 *
 * SensorInterface'i kullanarak engelleri algilar. Engel tespit edildiginde robotu durdurur.
 * Robot kontrolu icin RobotControler sinifini kullanir.
 */
void SafeNavigation::moveBackwardSafe() {
    // Sensor veya kontrol sinifi bagli degilse hata mesaji bas
    if (!IR || !controller) {
        cout << "Hata: Sensor veya RobotControler bagli degil!" << endl;
        return;
    }

    state = MOVING;
    cout << "Robot guvenli geri hareketine basladi..." << endl;

    // Hareket ederken durum MOVING olarak kalir
    while (state == MOVING) {
        // Sensor degerlerini guncelle
        IR->update();

        // Tum sensor degerlerini al
        double ranges[NUM_SENSORS];
        for (int i = 0; i < NUM_SENSORS; i++) {
            ranges[i] = IR->getSensorValue(i);
        }

        bool obstacleDetected = false; // Engel tespit durumu
        int backwardSensors[] = { 4, 5 }; // Geri algilama yapan sensorler

        // Geri sensorler icin engel tespiti yap
        for (int i : backwardSensors) {
            if (ranges[i] < 0.0) {
                cout << "Hata: Sensor " << i << " icin gecersiz mesafe degeri!" << endl;
                continue;
            }
            if (ranges[i] <= OBSTACLE_THRESHOLD) {
                obstacleDetected = true;
                cout << "Engel tespit edildi! Sensor " << i
                    << " mesafesi " << ranges[i]
                    << " m, threshold = " << OBSTACLE_THRESHOLD << endl;
                break;
            }
        }

        // Engel tespit edildiyse robot durdurulur
        if (obstacleDetected) {
            state = STOP;
            cout << "Robot durduruldu. Engel ile aradaki mesafe = "
                << OBSTACLE_THRESHOLD << " m veya daha az." << endl;
            break;
        }

        // Robot geri hareket eder
        controller->moveBackward();
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Kisa bir gecikme
        controller->stop(); // Duraklat
    }

    // Robotu durdur
    controller->stop();
}