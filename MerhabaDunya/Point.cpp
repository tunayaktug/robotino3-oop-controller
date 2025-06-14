#include "Point.h"

/**
 * @file    Point.cpp
 * @author  Yusuf Yaman (152120221075)
 * @date    14/12/2024
 * @brief   Point sinifi yontemlerinin implementasyonu.
 *
 * Bu dosya, x ve y koordinatlarini almak ve ayarlamak, noktalarin esitlik anlaminda karsilastirilmasi,
 * iki nokta arasindaki mesafeyi hesaplamak ve iki nokta arasindaki aciyi bulmak
 * icin yontemler iceren Point sinifinin implementasyonunu icerir.
 */

using namespace std;

/**
 * @brief x koordinatini doner.
 * @return Noktanin x koordinati.
 */
double Point::getX() const {
    return x;
}

/**
 * @brief y koordinatini doner.
 * @return Noktanin y koordinati.
 */
double Point::getY() const {
    return y;
}

/**
 * @brief x koordinatini ayarlar.
 * @param _x Yeni x koordinati degeri.
 */
void Point::setX(double _x) {
    x = _x;
}

/**
 * @brief y koordinatini ayarlar.
 * @param _y Yeni y koordinati degeri.
 */
void Point::setY(double _y) {
    y = _y;
}

/**
 * @brief Noktanin x ve y koordinatlarini doner.
 * @param _x x koordinati referansi.
 * @param _y y koordinati referansi.
 */
void Point::getPoint(double& _x, double& _y) const {
    _x = x;
    _y = y;
}

/**
 * @brief Noktanin x ve y koordinatlarini ayarlar.
 * @param _x Yeni x koordinati.
 * @param _y Yeni y koordinati.
 */
void Point::setPoint(double _x, double _y) {
    x = _x;
    y = _y;
}

/**
 * @brief Iki noktayi esitlik acisindan karsilastirir.
 * @param other Karsilastirilacak diger nokta.
 * @return Noktalar esitse true, aksi halde false.
 */
bool Point::operator==(const Point& other) const {
    return (x == other.x && y == other.y);
}

/**
 * @brief Iki nokta arasindaki mesafeyi hesaplar.
 * @param pos Mesafe hesaplanacak diger nokta.
 * @return Iki nokta arasindaki mesafe.
 */
double Point::findDistanceTo(const Point& pos) const {
    return sqrt((x - pos.x) * (x - pos.x) + (y - pos.y) * (y - pos.y));
}

/**
 * @brief Iki nokta arasindaki dogrultu acisini hesaplar.
 * @param pos Acinin hesaplanacagi diger nokta.
 * @return Iki nokta arasindaki aci (derece cinsinden).
 */
double Point::findAngleTo(const Point& pos) const {
    double angleInRadians = atan2(pos.y - y, pos.x - x);
    return angleInRadians * (180.0 / 3.14159265358979323846); // Dereceye cevir.
}
