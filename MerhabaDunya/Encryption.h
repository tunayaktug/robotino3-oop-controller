#pragma once
#include <iostream>

/**
 * @file    Encryption.h
 * @author  Yusuf Yaman (152120221075)
 * @date    12/12/2024
 * @brief   Encryption sinifinin deklarasyonu.
 *
 * Bu dosya, 4 basamkli sayilari sifrelemek ve sifresini cozumek icin yontemler saglayan Encryption sinifinin deklarasyonunu icerir.
 */

 /**
  * @class Encryption
  * @brief  4 basamakli sayilar icin sifreleme ve sifre cozulme islemlerini gerceklestiren sinif.
  */
class Encryption {
public:
    /**
     * @brief  4 basamakli bir sayiyi sifreler.
     */
    int encrypt(int);
    /**
     * @brief  4 basamakli sifrelenmis bir sayiyi cozumleyerek orijinal haline dondurur.
     */
    int decrypt(int);
};
