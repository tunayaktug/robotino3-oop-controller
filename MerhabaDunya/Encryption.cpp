#include <iostream>
#include "Encryption.h"

/**
 * @file    Encryption.cpp
 * @author  Yusuf Yaman (152120221075)
 * @date    12/12/2024
 * @brief   Encryption sinifinin implementasyonu.
 *
 * Bu dosya, bir sifreleme algoritmasi kullanarak 4 basamakli sayilari sifrelemek ve sifresini cozumlemek icin yontemler saglayan Encryption sinifinin implementasyonunu icerir.
 */

using namespace std;
/**
 * @brief  4 basamakli bir sayiyi sifreler.
 * @param  num Sifrelecek 4 basamakli sayi.
 * @return Sifrelenmis 4 basamakli sayi. Hata durumunda -1 dondurur.
 *
 */
int Encryption::encrypt(int num) {
    if (num < 0 || num > 9999) { // 4 basamakli olup olmadigini kontrol et.
        cerr << "Error: Number must be a 4-digit!" << endl;
        return -1; // Hata kodu dondur.
    }

    int numPlace[4];

    // Her bir basamagi bir diziye at.
    for (int i = 3; i >= 0; i--) {
        numPlace[i] = num % 10;
        num = num / 10;
    }

    // Her rakami, o rakama 7 ekleyip 10'a bolundugunde elde edilen kalanla degistir.
    for (int i = 0; i < 4; i++) {
        numPlace[i] = (numPlace[i] + 7) % 10;
    }

    // Sifrelenmis sayinin ilk ve ucuncu rakamlarinin, ikinci ve dorduncu rakamlarinin yerini degistir.
    for (int i = 0; i < 2; i++) {
        int temp = numPlace[i];
        numPlace[i] = numPlace[i + 2];
        numPlace[i + 2] = temp;
    }

    // Dizideki rakamlari tekrar sayi haline getir.
    int encryptedNum = 0;
    encryptedNum += numPlace[0] * 1000;
    encryptedNum += numPlace[1] * 100;
    encryptedNum += numPlace[2] * 10;
    encryptedNum += numPlace[3];

    return encryptedNum;
}

/**
 * @brief  4 basamakli sifrelenmis bir sayiyi cozumleyerek orijinal haline dondurur.
 * @param  encryptedNum Sifrelenmis 4 basamakli sayi.
 * @return Cozumlenmis (orijinal) 4 basamakli sayi. Hata durumunda -1 dondurur.
 *
 */
int Encryption::decrypt(int encryptedNum) {
    if (encryptedNum < 0 || encryptedNum > 9999) { // 4 basamakli olup olmadigini kontrol et.
        cerr << "Error: Encrypted number must be a 4-digit!" << endl;
        return -1; // Hata kodu dondur
    }

    int numPlace[4];

    // Sifrelenmis sayiyi tekrar bir diziye bol.
    for (int i = 3; i >= 0; i--) {
        numPlace[i] = encryptedNum % 10;
        encryptedNum = encryptedNum / 10;
    }

    // Ilk ve ucuncu rakamlarin, ikinci ve dorduncu rakamlarla yerini tekrar degistir.
    for (int i = 0; i < 2; i++) {
        int temp = numPlace[i];
        numPlace[i] = numPlace[i + 2];
        numPlace[i + 2] = temp;
    }

    // Her rakami sifreleme islemini tersine cevirerek orijinal rakama donustur.
    for (int i = 0; i < 4; i++) {
        numPlace[i] = (numPlace[i] + 3) % 10;
    }

    // Dizideki rakamlari tekrar sayi haline getir.
    int decryptedNum = 0;
    decryptedNum += numPlace[0] * 1000;
    decryptedNum += numPlace[1] * 100;
    decryptedNum += numPlace[2] * 10;
    decryptedNum += numPlace[3];

    return decryptedNum;
}
