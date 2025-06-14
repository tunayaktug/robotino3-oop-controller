#include "RobotControler.h"
#include "FestoRobotInterface.h"
#include "LidarSensor.h"
#include "IRSensor.h"
#include <iostream>
using namespace std;

/**
 * @file    RobotControler.cpp
 * @author  Akif Kaplan (152120221096)
 * @date    29/12/2024
 * @class RobotControler
 * @brief Robotu kontrol etmek icin gerekli olan sinif.
 * Robotu kontrol etmek, sensorleri yonetmek, erisim saglamak ve robotun durumunu almak icin fonksiyonlari icerir.
 */

 /**
   * @brief Parametreli kurucu fonksiyon.
   * Bu fonksiyon robot operatorunu ve sensorleri baslatir.
   * @param name Kullaniici adi.
   * @param surname Kullanici soyadi.
   * @param code Erisim kodu.
   * @param state Baslangic durumu.
   */
RobotControler::RobotControler(string name, string surname, unsigned int code, bool state)
    : robotOperator(name, surname, code, state) {
    robot = new FestoRobotInterface();// Robot nesnesi olusturuluyor
    // Sensorler listeye ekleniyor
    sensorList.push_back(new LidarSensor());
    sensorList.push_back(new IRSensor());
    accessGranted = false;// Baslangicta erisim izni yok

}

/**
 * @brief Parametresiz kurucu fonksiyon.
 * Varsayilan degerlerle robot kontrol nesnesi olusturur.
 */
RobotControler::RobotControler() : robotOperator("Default", "Operator", 1234, false) {
    robot = nullptr;// Robot nesnesi henuz olusturulmamis durumda
    accessGranted = false;// Baslangicta erisim izni yok

}

/**
 * @brief Yikici (destructor) fonksiyon.
 * Robot ve sensor nesnelerini serbest birakir.
 */
RobotControler::~RobotControler() {
    // Robot nesnesi serbest birakiliyor
    delete robot;

    // Sensor listesi temizleniyor ve serbest birakiliyor
    for (auto sensor : sensorList) {
        delete sensor;
    }
    sensorList.clear();
}

/**
 * @brief Robotu sola dondurur.
 * @details Erisim izni olmadan bu islem yapilamaz.
 */
void RobotControler::turnLeft() {
    // Erisim izni kontrolu
    if (!accessGranted) {
        cout << "Access denied! Operation requires access to be granted." << endl;
        return;
    }
    cout << "RobotController: Turning left..." << endl;
    robot->turnLeft();
}

/**
 * @brief Robotu saga dondurur.
 * @details Erisim izni olmadan bu islem yapilamaz.
 */
void RobotControler::turnRight() {
    if (!accessGranted) {// Erisim izni kontrolu
        cout << "Access denied! Operation requires access to be granted." << endl;
        return;
    }
    cout << "RobotController: Turning right..." << endl;
    robot->turnRight();
}

/**
 * @brief Robotu ileri hareket ettirir.
 * @details Erisim izni olmadan bu islem yapilamaz.
 */
void RobotControler::moveForward() {
    if (!accessGranted) {// Erisim izni kontrolu
        cout << "Access denied! Operation requires access to be granted." << endl;
        return;
    }
    cout << "RobotController: Moving forward..." << endl;
    robot->moveForward();
}

/**
 * @brief Robotu geri hareket ettirir.
 * @details Erisim izni olmadan bu islem yapilamaz.
 */
void RobotControler::moveBackward() {
    if (!accessGranted) {// Erisim izni kontrolu
        cout << "Access denied! Operation requires access to be granted." << endl;
        return;
    }
    cout << "RobotController: Moving backward..." << endl;
    robot->moveBackward();
}

/**
 * @brief Robotu sola hareket ettirir.
 * @details Erisim izni olmadan bu islem yapilamaz.
 */
void RobotControler::moveLeft() {
    if (!accessGranted) {// Erisim izni kontrolu
        cout << "Access denied! Operation requires access to be granted." << endl;
        return;
    }
    cout << "RobotController: Moving left..." << endl;
    robot->moveLeft();
}

/**
 * @brief Robotu saga hareket ettirir.
 * @details Erisim izni olmadan bu islem yapilamaz.
 */
void RobotControler::moveRight() {
    if (!accessGranted) {// Erisim izni kontrolu
        cout << "Access denied! Operation requires access to be granted." << endl;
        return;
    }
    cout << "RobotController: Moving right..." << endl;
    robot->moveRight();
}

/**
 * @brief Robotu durdurur.
 * @details Erisim izni olmadan bu islem yapilamaz.
 */
void RobotControler::stop() {
    if (!accessGranted) {// Erisim izni kontrolu
        cout << "Access denied! Operation requires access to be granted." << endl;
        return;
    }
    cout << "RobotController: Stopping the robot..." << endl;
    robot->stop();
}

/**
 * @brief Robotun mevcut pozisyonunu dondurur.
 * @return Robotun pozisyonu (Pose).
 * @details Erisim izni olmadan varsayilan bir pozisyon doner.
 */
Pose RobotControler::getPose() {
    if (!accessGranted) {// Erisim izni kontrolu
        cout << "Access denied! Operation requires access to be granted." << endl;
        return Pose(); // Varsayýlan pozisyon döner
    }
    return robot->getPose();
}

/**
 * @brief Robotun mevcut durumunu yazdirir.
 * @details Erisim izni olmadan islem yapilamaz.
 */
void RobotControler::print() {
    if (!accessGranted) {// Erisim izni kontrolu
        cout << "Access denied! Operation requires access to be granted." << endl;
        return;
    }
    robot->print();
}

/**
 * @brief Robot ile baglantiyi kurar.
 * @return Baglanti basarili ise true, aksi takdirde false doner.
 * @details Erisim izni olmadan baglanti kurulamaz.
 */
bool RobotControler::connectRobot() {
    if (!accessGranted) {// Erisim izni kontrolu
        cout << "Access denied! Operation requires access to be granted." << endl;
        return false;
    }
    return robot->connectRobot();
}

/**
 * @brief Robot ile baglantiyi keser.
 * @return Baglanti kesildiyse true, aksi takdirde false doner.
 * @details Erisim izni olmadan baglanti kesilemez.
 */
bool RobotControler::disconnectRobot() {
    if (!accessGranted) {// Erisim izni kontrolu
        cout << "Access denied! Operation requires access to be granted." << endl;
        return false;
    }
    return robot->disconnectRobot();
}

/**
 * @brief Bir sensor ekler.
 * @param sensor Eklenen sensor nesnesi.
 * @details Erisim izni olmadan sensor eklenemez.
 */
void RobotControler::addSensor(SensorInterface* sensor) {
    if (!accessGranted) {// Erisim izni kontrolu
        cout << "Access denied! Operation requires access to be granted." << endl;
        return;
    }
    sensorList.push_back(sensor);
}

/**
 * @brief Tum sensorleri gunceller.
 * @details Erisim izni olmadan sensorler guncellenemez.
 */
void RobotControler::updateSensors() {
    if (!accessGranted) {// Erisim izni kontrolu
        cout << "Access denied! Operation requires access to be granted." << endl;
        return;
    }
    for (auto sensor : sensorList) {
        sensor->update();
    }
}

/**
 * @brief Erisimi acar.
 * @param code Erisim kodu.
 * @return Erisim basarili ise true, aksi takdirde false doner.
 * @details Eger erisim kodu dogru ise erisim acilir.
 */
bool RobotControler::openAccess(int code) {
    if (robotOperator.checkAccessCode(code)) {
        accessGranted = true;
        cout << "Access granted!" << endl;
        return true;
    }
    cout << "Access denied!" << endl;
    return false;
}

/**
 * @brief Erisimi kapatir.
 * @param code Erisim kodu.
 * @return Erisim kapali ise true, aksi takdirde false doner.
 * @details Eger erisim kodu dogru ise erisim kapatilir.
 */
bool RobotControler::closeAccess(int code) {
    if (robotOperator.checkAccessCode(code)) {
        accessGranted = false;
        cout << "Access closed!" << endl;
        return true;
    }
    cout << "Access denied!" << endl;
    return false;
}

/**
 * @brief Erisimin verilip verilmedigini kontrol eder.
 * @return Erisim verildiyse true, verilmediyse false doner.
 */
bool RobotControler::isAccessGranted() const {
    return accessGranted;
}

/**
 * @brief Robotun baglantisinin aktif olup olmadigini kontrol eder.
 * @return Robot bagli ise true, degilse false doner.
 */
bool RobotControler::isConnected() const {
    return robot->isConnected();
}