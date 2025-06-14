#include "Pose.h"
/*
*  @file     Pose.cpp
 * @author  Akif Kaplan (152120221096)
 * @date    21/12/2024
 * @brief   2D bir noktayi temsil etmek ve bu noktayla islemler yapmak icin bir sinif.
 *
 * Bu sinif, 2D duzlemde bir noktayi (x, y) ve bir yon acisini (th) temsil eder.
 * Bu koordinatlarin alinmasi, ayarlanmasi, normalize edilmesi ve uzerinde cesitli islemler yapilmasini saglar.
 * Ayrica, baska bir noktayla karsilastirma yapmayi, mesafe ve aci hesaplamayi destekler. Bu kod parcasinda ise bu sinifin
 * implementasyonlari vardir.
*/

/**
 * @brief Pose sinifinin kurucu fonksiyonu.
 *
 * @param x x koordinati.
 * @param y y koordinati.
 * @param th Yon acisi.
 */
Pose::Pose(double x, double y, double th) : x(x), y(y), th(th) {
    setTh(th); // th degerini normalize etmek icin setTh fonksiyonunu cagirma.
}

/**
 * @brief x koordinatini donduren getter fonksiyonu.
 * @return double x koordinati.
 */
double Pose::getX() {
    return x; // X koordinatini donduren getter fonksiyonu.
}

/**
 * @brief y koordinatini donduren getter fonksiyonu.
 * @return double y koordinati.
 */
double Pose::getY() {
    return y; // y koordinatini donduren getter fonksiyonu.
}

/**
 * @brief Yon acisini donduren getter fonksiyonu.
 * @return double Yon acisi.
 */
double Pose::getTh() {
    return th; // Aci (th) degerini donduren getter fonksiyonu.
}

/**
 * @brief x koordinatini ayarlayan setter fonksiyonu.
 * @param x Yeni x koordinati.
 */
void Pose::setX(double x) {
    this->x = x; // X koordinatini ayarlayan setter fonksiyonu.
}

/**
 * @brief y koordinatini ayarlayan setter fonksiyonu.
 * @param y Yeni y koordinati.
 */
void Pose::setY(double y) {
    this->y = y; // y koordinatini ayarlayan setter fonksiyonu.
}

/**
 * @brief Yon acisini normalize ederek ayarlayan setter fonksiyonu.
 * @param th Yeni yon acisi.
 */
void Pose::setTh(double th) {
    while (th >= 360) { // th degerini 0-360 araligina getir
        th -= 360;
    }
    while (th < 0) { // Negatif acilari pozitif hale cevir
        th += 360;
    }
    this->th = th;
}

/**
 * @brief Iki Pose nesnesinin esit olup olmadigini kontrol eder.
 * @param other Karsilastirilacak diger Pose nesnesi.
 * @return bool Esit ise true, degilse false.
 */
bool Pose::operator==(const Pose& other) const {
    return (x == other.x && y == other.y && th == other.th);
}

/**
 * @brief Iki Pose nesnesini toplar.
 * @param other Toplanacak diger Pose nesnesi.
 * @return Pose Toplam sonucu.
 */
Pose Pose::operator+(const Pose& other) const {
    double newTh = th + other.th;
    if (newTh < 0) { // Aci optimize edildi
        newTh += 360;
    }
    if (newTh >= 360) { // Aci optimize edildi
        newTh -= 360;
    }
    return Pose(x + other.x, y + other.y, newTh);
}

/**
 * @brief Iki Pose nesnesinin farkini alir.
 * @param other Cikartilacak diger Pose nesnesi.
 * @return Pose Cikartma sonucu.
 */
Pose Pose::operator-(const Pose& other) const {
    double newTh = th - other.th;
    if (newTh < 0) { // Aci optimize edildi
        newTh += 360;
    }
    if (newTh >= 360) { // Aci optimize edildi
        newTh -= 360;
    }
    return Pose(x - other.x, y - other.y, newTh);
}

/**
 * @brief Mevcut Pose nesnesine baska bir Pose nesnesini ekler.
 * @param other Eklenilecek diger Pose nesnesi.
 * @return Pose& Toplam sonucu (bu nesne).
 */
Pose& Pose::operator+=(const Pose& other) {
    x += other.x;
    y += other.y;
    th += other.th;
    setTh(th); // th degerini normalize etme.
    return *this;
}

/**
 * @brief Mevcut Pose nesnesinden baska bir Pose nesnesini cikarir.
 * @param other Cikartilacak diger Pose nesnesi.
 * @return Pose& Cikartma sonucu (bu nesne).
 */
Pose& Pose::operator-=(const Pose& other) {
    x -= other.x;
    y -= other.y;
    th -= other.th;
    setTh(th); // th degerini normalize et.
    return *this;
}

/**
 * @brief Iki Pose nesnesini kiyaslar.
 * @param other Karsilastirilacak diger Pose nesnesi.
 * @return bool Kucuk ise true, degilse false.
 */
bool Pose::operator<(const Pose& other) const {
    return (x < other.x && y < other.y && th < other.th); // Kucukse true, degilse false dondurur.
}

/**
 * @brief Pose degerlerini donduren fonksiyon.
 * @param _x x koordinatini dondurmek icin referans.
 * @param _y y koordinatini dondurmek icin referans.
 * @param _th Yon acisini dondurmek icin referans.
 */
void Pose::getPose(double& _x, double& _y, double& _th) const {
    _x = x;
    _y = y;
    _th = th;
}

/**
 * @brief Pose degerlerini ayarlayan fonksiyon.
 * @param _x Yeni x koordinati.
 * @param _y Yeni y koordinati.
 * @param _th Yeni yon acisi.
 */
void Pose::setPose(double _x, double _y, double _th) {
    x = _x;
    y = _y;
    setTh(_th); // th degerini normalize ettim. 360 ile sifir araligina aldim.
}

/**
 * @brief Belirtilen bir Pose nesnesine olan mesafeyi hesaplar.
 * @param pos Diger Pose nesnesi.
 * @return double Hesaplanan mesafe.
 */
double Pose::findDistanceTo(Pose& pos) {
    return sqrt(pow((pos.getX() - x), 2) + pow((pos.getY() - y), 2));
}

/**
 * @brief Belirtilen bir Pose nesnesine olan aciyi hesaplar.
 * @param pos Diger Pose nesnesi.
 * @return double Hesaplanan aci (radyan cinsinden).
 */
double Pose::findAngleTo(Pose& pos) {
    double angle = atan2((pos.getY() - y), (pos.getX() - x)); // atan2 ile aci hesaplama
    if (angle >= 360) { // 360 dan buyukse -360 yaptim
        angle -= 360;
    }
    if (angle < 0) { // 0 dan kucukse +360 yaptim
        angle += 360;
    }
    return angle; // Aciyi dondur.
}
