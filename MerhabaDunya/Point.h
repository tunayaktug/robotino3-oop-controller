#pragma once
#include <cmath>

/**
 * @file    Point.h
 * @author  Yusuf Yaman (152120221075)
 * @date    14/12/2024
 * @brief   2D bir noktayi temsil etmek ve bu noktayla islemler yapmak icin bir sinif.
 *
 * Bu sinif, 2D nokta koordinatlarini depolamak, degistirmek ve uzerinde cesitli islemler yapmayi saglar.
 * Noktanin koordinatlarini almak ve ayarlamak, esitlik kontrolu yapmak, iki nokta arasindaki
 * mesafeyi ve aciyi hesaplamak gibi islemleri icerir.
 */

class Point {
private:
    double x;  ///< Noktanin x koordinati.
    double y;  ///< Noktanin y koordinati.

public:
    /**
     * @brief Yapici fonksiyon: Noktayi verilen x ve y koordinatlariyla baslatir.
     * @param _x Baslangic x koordinati (varsayilan deger: 0.0).
     * @param _y Baslangic y koordinati (varsayilan deger: 0.0).
     */
    Point(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}

    /**
     * @brief x koordinatini doner.
     * @return Noktanin x koordinati.
     */
    double getX() const;

    /**
     * @brief y koordinatini doner.
     * @return Noktanin y koordinati.
     */
    double getY() const;

    /**
     * @brief x koordinatini ayarlar.
     * @param _x Yeni x koordinati.
     */
    void setX(double _x);

    /**
     * @brief y koordinatini ayarlar.
     * @param _y Yeni y koordinati.
     */
    void setY(double _y);

    /**
     * @brief Noktanin x ve y koordinatlarini doner.
     * @param _x x koordinatini alacak referans.
     * @param _y y koordinatini alacak referans.
     */
    void getPoint(double& _x, double& _y) const;

    /**
     * @brief Noktanin x ve y koordinatlarini ayarlar.
     * @param _x Yeni x koordinati.
     * @param _y Yeni y koordinati.
     */
    void setPoint(double _x, double _y);

    /**
     * @brief Iki noktanin esit olup olmadigini kontrol eder.
     * @param other Karsilastirilacak diger nokta.
     * @return Eger noktalar esitse true, aksi halde false.
     */
    bool operator==(const Point& other) const;

    /**
     * @brief Iki nokta arasindaki mesafeyi hesaplar.
     * @param pos Mesafenin hesaplanacagi diger nokta.
     * @return Iki nokta arasindaki mesafe.
     */
    double findDistanceTo(const Point& pos) const;

    /**
     * @brief Iki nokta arasindaki dogrultu acisini hesaplar.
     * @param pos Acinin hesaplanacagi diger nokta.
     * @return Iki nokta arasindaki aci (derece cinsinden).
     */
    double findAngleTo(const Point& pos) const;
};
