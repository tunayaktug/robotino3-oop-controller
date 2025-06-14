#pragma once
#include <iostream>
#include <string>
#include "Encryption.h"

/**
 * @file    RobotOperator.h
 * @author  Yusuf Yaman (152120221075)
 * @date    13/12/2024
 * @brief   RobotOperator sinifinin deklarasyonu.
 *
 * Bu dosya, ad, soyad ve erisim kodu gibi ozelliklere sahip bir robot operatorunu temsil eden
 * RobotOperator sinifinin deklarasyonunu icerir. Sinif, erisim kodlarini sifrelemek, sifresini cozmek,
 * dogrulamak ve operator bilgilerini gosterme icin yontemler saglar.
 */

using namespace std;

/**
 * @class RobotOperator
 * @brief Robot operatorunu temsil eden sinif.
 *
 * RobotOperator sinifi, bir robot operatorunun adini, soyadini, erisim kodunu ve erisim durumunu
 * yonetmek icin gerekli yontemleri saglar. Ayrica, erisim kodlarini sifrelemek ve sifrelerini cozumlemek
 * icin Encryption sinifini kullanir.
 */
class RobotOperator {
private:
    string name;              ///< Robot operatorunun adi.
    string surname;           ///< Robot operatorunun soyadi.
    unsigned int accessCode;  ///< Operatorun erisim kodu.
    bool accessState;         ///< Operatorun erisim durumunu belirtir (true: erisim acik, false: erisim kapali).

    /**
     * @brief Erisim kodunu sifreler.
     * @param code Sifrelenecek erisim kodu.
     * @return Sifrelenmis erisim kodu.
     */
    int encryptCode(int code);

    /**
     * @brief Sifrelenmis erisim kodunu cozer.
     * @param code Cozulecek sifreli erisim kodu.
     * @return Cozulmus erisim kodu.
     */
    int decryptCode(int code);

    Encryption encryption;    ///< Sifreleme islemleri icin Encryption sinifi nesnesi.

public:
    /**
     * @brief RobotOperator yapici fonksiyonu.
     * @param _name Robot operatorunun adi.
     * @param _surname Robot operatorunun soyadi.
     * @param _accessCode Operatorun erisim kodu.
     * @param _accessState Operatorun erisim durumu (varsayilan: false).
     */
    RobotOperator(string _name, string _surname, unsigned int _accessCode, bool _accessState = false)
        : name(_name), surname(_surname), accessCode(_accessCode), accessState(_accessState) {
    }

    /**
     * @brief Kullanicinin erisim kodunu dogrular.
     * @param code Dogrulacak erisim kodu.
     * @return Erisim kodu dogruysa true, yanlissa false.
     */
    bool checkAccessCode(int code);

    /**
     * @brief Robot operatorunun bilgilerini yazdirir.
     */
    void print() const;

    /**
     * @brief Operatorun erisim durumunu doner.
     * @return Erisim durumu (true: erisim acik, false: erisim kapali).
     */
    bool getAccessState() const;

    /**
     * @brief Operatorun erisim kodunu doner.
     * @return Erisim kodu.
     */
    int getAccessCode() const;
};
