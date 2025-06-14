#pragma once

#include <list>
#include "SensorInterface.h"
#include "RobotInterface.h"
#include "RobotOperator.h"
#include "Pose.h"
#include <string>

using std::list;

/**
 * @class RobotControler
 * Robot kontrol islemleri icin kullanilan sinif.
 */

class RobotControler {
private:
    list<SensorInterface*> sensorList; ///< Robotun sensor listesini tutar.

    RobotInterface* robot;///< Robot arayuzu nesnesi.

    RobotOperator robotOperator;///< Robot operator nesnesi.

    bool accessGranted; ///< Erisim izni durumu.


public:
    /**
   * Parametreli kurucu fonksiyon.
   * @param param1 Ilk parametre (string).
   * @param param2 Ikinci parametre (string).
   * @param param3 Ucuncu parametre (unsigned int).
   * @param param4 Dorduncu parametre (bool).
   */
    RobotControler(std::string, std::string, unsigned int, bool);
    /**
     * Parametresiz kurucu fonksiyon.
     */
    RobotControler();

    /**
     * Yikici (destructor) fonksiyon.
     */
    ~RobotControler();

    /**
     * Robotun sola donmesini saglar.
     */
    void turnLeft();

    /**
     * Robotun saga donmesini saglar.
     */
    void turnRight();

    /**
     * Robotun ileri hareket etmesini saglar.
     */
    void moveForward();

    /**
     * Robotun geri hareket etmesini saglar.
     */
    void moveBackward();

    /**
     * Robotun sola hareket etmesini saglar.
     */
    void moveLeft();
    /**
     * Robotun saga hareket etmesini saglar.
     */
    void moveRight();

    /**
    * Robotun durmasini saglar.
    */
    void stop();

    /**
     * Robotun mevcut pozisyonunu dondurur.
     * @return Robotun pozisyonu.
     */
    Pose getPose();

    /**
    * Robotun mevcut durumunu yazdirir.
    */
    void print();

    /**
    * Robot ile baglanti kurar.
    * @return Baglanti basarili ise true, aksi halde false.
    */
    bool connectRobot();

    /**
    * Robot ile baglanti keser.
    * @return Baglanti kesme basarili ise true, aksi halde false.
    */
    bool disconnectRobot();

    /**
     * Sensor ekler.
     * @param sensor Eklemek istenen sensor nesnesi.
     */
    void addSensor(SensorInterface* sensor);

    /**
   * Sensorlerin durumunu gunceller.
   */
    void updateSensors();

    /**
     * Robot icin erisimi acar.
     * @param id Erisim acilacak kullanici veya islem kimligi.
     * @return Erisim acma basarili ise true, aksi halde false.
     */
    bool openAccess(int);

    /**
    * Robot icin erisimi kapatir.
    * @param id Erisim kapatilacak kullanici veya islem kimligi.
    * @return Erisim kapatma basarili ise true, aksi halde false.
    */
    bool closeAccess(int);

    /**
     * Erisim izni durumunu dondurur.
     * @return Erisim izni verilmis ise true, aksi halde false.
     */
    bool isAccessGranted()const;

    /**
     * Robotun baglanti durumunu dondurur.
     * @return Robot bagli ise true, aksi halde false.
     */
    bool isConnected()const;
};