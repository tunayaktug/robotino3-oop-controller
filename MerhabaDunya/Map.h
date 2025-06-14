#pragma once

#include "Point.h"
#include <iostream>

/**
 * @file    IRSensor.h
 * @author  Emirhan Kesim (152120221116)
 * @date    20/12/2024
 * @brief   MAP sinifinin deklarasyonu.
 *
 * Bu dosya, harita olusturmak ve yonetmek icin kullanilan MAP sinifinin deklarasyonunu icerir.
 * Harita grid yapisi uzerinde nokta ekleme, silme, boyut ayarlama gibi islemleri gerceklestiren
 * metotlar sunar.
 */

 /**
  * @brief Harita olusturma ve yonetme islemlerini gerceklestiren sinif.
  *
  * MAP sinifi, grid tabanli bir harita uzerinde cesitli islemler yapmak icin tasarlanmistir.
  */
class MAP {
private:
    int** grid;          /**< Harita verilerini tutan iki boyutlu dinamik dizi. */
    int numberX;         /**< Haritanin x boyutundaki grid sayisi. */
    int numberY;         /**< Haritanin y boyutundaki grid sayisi. */
    double gridSize;     /**< Her bir grid hucresinin boyutu. */

public:
    /**
     * @brief Constructor: Haritayi belirtilen boyutlarda olusturur.
     * @param x Haritanin x boyutundaki grid sayisi.
     * @param y Haritanin y boyutundaki grid sayisi.
     */
    MAP(int x, int y);

    /**
     * @brief Destructor: Bellek sizintisini onlemek icin grid bellegini serbest birakir.
     */
    ~MAP();

    /**
     * @brief Haritaya bir nokta ekler.
     *
     * @param point Eklenmek istenen nokta.
     */
    void insertPoint(const Point& point);

    /**
     * @brief Belirtilen grid hucresindeki degeri dondurur.
     *
     * @param indexX X eksenindeki hucre indeksi.
     * @param indexY Y eksenindeki hucre indeksi.
     * @return Hucredeki deger.
     */
    int getGrid(int indexX, int indexY) const;

    /**
     * @brief Belirtilen grid hucresine bir deger atar.
     *
     * @param indexX X eksenindeki hucre indeksi.
     * @param indexY Y eksenindeki hucre indeksi.
     * @param value Atanacak deger.
     */
    void setGrid(int indexX, int indexY, int value);

    /**
     * @brief Tum grid'i sifirlar.
     */
    void clearMap();

    /**
     * @brief Harita bilgilerini yazdirir.
     */
    void printInfo() const;

    /**
     * @brief Harita grid'ini gorsel olarak konsola yazdirir.
     */
    void showMap() const;

    /**
     * @brief Haritanin x boyutundaki grid sayisini dondurur.
     * @return X boyutundaki grid sayisi.
     */
    int getNumberX() const;

    /**
     * @brief Haritanin y boyutundaki grid sayisini dondurur.
     * @return Y boyutundaki grid sayisi.
     */
    int getNumberY() const;

    /**
     * @brief Grid boyutunu yazdirir.
     */
    void addGridSize();

    /**
     * @brief Grid boyutunu ayarlar ve mevcut noktalari yeniden duzenler.
     *
     * @param GSize Yeni grid boyutu.
     */
    void setGridSize(double GSize);

    /**
     * @brief Harita grid'ini yazdirmak icin `<<` operatorunu asiri yukler.
     *
     * @param os Cikis akisi nesnesi.
     * @param map Yazdirilacak harita.
     * @return Akis nesnesi.
     */
    friend std::ostream& operator<<(std::ostream& os, const MAP& map);
};
