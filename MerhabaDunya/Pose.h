#pragma once
#include <iostream>
#include <cmath>
/*
* @file    Pose.h
 * @author  Akif Kaplan (152120221096)
 * @date    21/12/2024
 * @brief   2D bir noktayi temsil etmek ve bu noktayla islemler yapmak icin bir sinif.
 *
 * Bu sinif, 2D duzlemde bir noktayi (x, y) ve bir yon acisini (th) temsil eder.
 * Bu koordinatlarin alinmasi, ayarlanmasi, normalize edilmesi ve uzerinde cesitli islemler yapilmasini saglar.
 * Ayrica, baska bir noktayla karsilastirma yapmayi, mesafe ve aci hesaplamayi destekler.
*/

using namespace std;

/**
 * @class Pose
 * @brief 2D duzlemde bir noktayi ve yon acisini temsil eden sinif.
 */
class Pose {
private:
    double x;  ///< X koordinati.
    double y;  ///< Y koordinati.
    double th; ///< Yon acisi.

public:

    /**
     * @brief Varsayilan veya parametreli kurucu.
     */
    Pose(double x = 0, double y = 0, double th = 0);

    /**
     * @brief x koordinatini donderir.
     * @return double x koordinati.
     */
    double getX();

    /**
     * @brief y koordinatini donderir.
     * @return double y koordinati.
     */
    double getY();

    /**
     * @brief Yon acisini donderir.
     * @return double Yon acisi.
     */
    double getTh();

    /**
     * @brief x i ayarlar.
     */
    void setX(double x);

    /**
     * @brief y koordinatini ayarlar.
     */
    void setY(double y);

    /**
      * @brief Yon acisini ayarlar.
      * @param th Yeni yon acisi.
      */
    void setTh(double th);

    /**
     * @brief Iki Pose nesnesinin esit olup olmadigini kontrol eder.
     *
     * @param other Karsilastirilacak diger Pose nesnesi.
     * @return bool Esit ise true, degilse false.
     */
    bool operator==(const Pose& other) const;

    /**
     * @brief Iki Pose nesnesini toplar.
     *
     * @param other Toplanacak diger Pose nesnesi.
     * @return Pose Toplam sonucu.
     */
    Pose operator+(const Pose& other) const;

    /**
     * @brief Bir Pose nesnesini digerinden cikartir.
     *
     * @param other Cikartilacak diger Pose nesnesi.
     * @return Pose Cikartma sonucu.
     */
    Pose operator-(const Pose& other) const;

    /**
     * @brief Bir Pose nesnesini bu nesneye ekler.
     *
     * @param other Eklenilecek diger Pose nesnesi.
     * @return Pose& Toplam sonucu (bu nesne).
     */
    Pose& operator+=(const Pose& other);

    /**
     * @brief Bir Pose nesnesini bu nesneden cikartir.
     *
     * @param other Cikartilacak diger Pose nesnesi.
     * @return Pose& Cikartma sonucu (bu nesne).
     */
    Pose& operator-=(const Pose& other);

    /**
     * @brief Bu Pose nesnesinin digerinden kucuk olup olmadigini kontrol eder.
     *
     * @param other Karsilastirilacak diger Pose nesnesi.
     * @return bool Eger kucukse true, degilse false.
     */
    bool operator<(const Pose& other) const;

    /**
     * @brief Pose degerlerini donderir.
     *
     * @param _x x koordinatini dondermek icin referans.
     * @param _y y koordinatini dondermek icin referans.
     * @param _th Yon acisini dondermek icin referans.
     */
    void getPose(double& _x, double& _y, double& _th) const;

    /**
     * @brief Pose degerlerini ayarlar.
     *
     * @param _x Yeni x koordinati.
     * @param _y Yeni y koordinati.
     * @param _th Yeni yon acisi.
     */
    void setPose(double _x, double _y, double _th);

    /**
     * @brief Belirtilen baska bir Pose nesnesine olan mesafeyi hesaplar.
     *
     * @param pos Diger Pose nesnesi.
     * @return double Hesaplanan mesafe.
     */
    double findDistanceTo(Pose& pos);

    /**
     * @brief Belirtilen baska bir Pose nesnesine olan aciyi hesaplar.
     *
     * @param pos Diger Pose nesnesi.
     * @return double Hesaplanan aci (radyan cinsinden).
     */
    double findAngleTo(Pose& pos);
};
