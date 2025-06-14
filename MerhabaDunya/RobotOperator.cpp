#include <iostream>
#include "RobotOperator.h"

/**
 * @file    RobotOperator.cpp
 * @author  Yusuf Yaman (152120221075)
 * @date    13/12/2024
 * @brief   RobotOperator sinifinin implementasyonu.
 *
 * Bu dosya, erisim kodunu sifreleme ve sifresini cozme, girilen kodun sifreli kodla eslesip eslesmedigini
 * kontrol etme ve operator bilgilerini yazdirma gibi RobotOperator sinifi yontemlerinin
 * implementasyonunu icerir.
 */

using namespace std;

/**
 * @brief Erisim kodunu sifreler.
 * @param code Sifrelenecek 4 basamakli erisim kodu.
 * @return Sifrelenmis erisim kodu.
 */
int RobotOperator::encryptCode(int code) {
    return encryption.encrypt(code);
}

/**
 * @brief Sifrelenmis bir erisim kodunun sifresini cozer.
 * @param code Cozulecek sifreli 4 basamakli erisim kodu.
 * @return Cozumlenmis erisim kodu.
 */
int RobotOperator::decryptCode(int code) {
    return encryption.decrypt(code);
}

/**
 * @brief Girilen kodun, sifrelenmis olarak tutulan erisim koduyla eslesip eslesmedigini kontrol eder.
 * @param code Dogrulanacak erisim kodu.
 * @return Kod eslesirse true, aksi halde false doner. Ayrica accessState guncellenir.
 */
bool RobotOperator::checkAccessCode(int code) {
    if (decryptCode(accessCode) == code) {
        accessState = true;  ///< Kod eslesirse erisim durumu granted (true) olarak guncellenir.
        return true;
    }
    else {
        accessState = false; ///< Kod eslesmezse erisim durumu denied (false) olarak guncellenir.
        return false;
    }
}

/**
 * @brief Robot operatorunun bilgilerini ekrana yazdirir.
 *
 * Operatorun adi, soyadi ve erisim durumu goruntulenir.
 * Erisim durumu granted (true) ise "Granted", aksi takdirde "Denied" olarak yazdirilir.
 */
void RobotOperator::print() const {
    cout << "Robot Operator Information:" << endl;
    cout << "Name: " << name << endl;
    cout << "Surname: " << surname << endl;
    cout << "Access State: " << (accessState ? "Granted" : "Denied") << endl;
}

/**
 * @brief Operatorun erisim durumunu doner.
 * @return Erisim durumu (true: Granted, false: Denied).
 */
bool RobotOperator::getAccessState() const {
    return accessState;
}

/**
 * @brief Operatorun sifrelenmis erisim kodunu doner.
 * @return Sifrelenmis erisim kodu.
 */
int RobotOperator::getAccessCode() const {
    return accessCode;
}

