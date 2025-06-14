/**
 * @file    MAP.cpp
 * @author  Emirhan Kesim (152120221116)
 * @date    20/12/2024
 * @brief   MAP sinifinin fonksiyon kodlari.
 *
 * Bu dosya, MAP sinifi ile harita olusturmak ve yonetmek icin gerekli fonksiyonlarin
 * implementasyonunu icerir.
 */

#include "MAP.h"
#include "Point.h"
#include <iostream>
#include <cmath>

 /**
  * @brief Constructor: MAP sinifinin yeni bir ornegini olusturur.
  *
  * @param x Haritanin X eksenindeki grid boyutu.
  * @param y Haritanin Y eksenindeki grid boyutu.
  *
  * Bu fonksiyon, harita icin gerekli boyutlari (x, y) alir ve grid'i olusturur.
  * Gecersiz boyutlar verilirse, harita olusturulmaz ve hata mesaji verilir.
  */
MAP::MAP(int x, int y) {
    if (x <= 0 || y <= 0) {
        std::cerr << "Invalid map dimensions!" << std::endl;
        numberX = numberY = 0;
        grid = nullptr;
        return;
    }

    numberX = x;
    numberY = y;
    gridSize = 1.0; // Varsayilan grid boyutu

    grid = new int* [numberX];
    for (int i = 0; i < numberX; ++i) {
        grid[i] = new int[numberY]();  // Grid hucreleri sifirlanir
    }

    std::cout << "MAP created with dimensions " << numberX << "x" << numberY << std::endl;
}

/**
 * @brief Destructor: MAP sinifinin yikicisi.
 *
 * Grid icin ayrilan bellegi serbest birakir.
 */
MAP::~MAP() {
    if (grid) {
        for (int i = 0; i < numberX; ++i) {
            delete[] grid[i];  // Her satirin bellegini serbest birakir
        }
        delete[] grid;  // Grid'in kendisini serbest birakir
    }
    std::cout << "MAP destroyed." << std::endl;
}

/**
 * @brief Haritaya bir nokta ekler.
 *
 * @param point Eklenmek istenen nokta.
 *
 * Bu fonksiyon, verilen noktanin grid boyutuna gore uygun hucreye yerlestirilmesini saglar.
 * Eger nokta gecerli sinirlar icindeyse, haritaya eklenir. Aksi takdirde hata mesaji verir.
 */
void MAP::insertPoint(const Point& point) {
    int gridX = point.getX() / gridSize;  // X koordinatini grid boyutuna gore hesapla
    int gridY = point.getY() / gridSize;  // Y koordinatini grid boyutuna gore hesapla

    if (gridX >= 0 && gridX < numberX && gridY >= 0 && gridY < numberY) {
        grid[gridX][gridY] = 1;  // Nokta eklenir
        std::cout << "Point inserted at (" << gridX << ", " << gridY << ")." << std::endl;
    }
    else {
        std::cerr << "Invalid point insertion: (" << gridX << ", " << gridY << ") out of bounds." << std::endl;
    }
}

/**
 * @brief Belirtilen grid hucresindeki degeri dondurur.
 *
 * @param indexX X eksenindeki grid indeksi.
 * @param indexY Y eksenindeki grid indeksi.
 * @return Hucredeki deger. Gecersiz erisimde -1 doner.
 */
int MAP::getGrid(int indexX, int indexY) const {
    if (indexX >= 0 && indexX < numberX && indexY >= 0 && indexY < numberY) {
        return grid[indexX][indexY];
    }
    std::cerr << "Invalid grid access: (" << indexX << ", " << indexY << ") out of bounds." << std::endl;
    return -1;  // Gecersiz erisimde -1 doner
}

/**
 * @brief Belirtilen grid hucresine bir deger atar.
 *
 * @param indexX X eksenindeki grid indeksi.
 * @param indexY Y eksenindeki grid indeksi.
 * @param value Atanacak deger.
 *
 * Bu fonksiyon, verilen (indexX, indexY) hucresine bir deger atar.
 * Eger hucre gecerli degilse, hata mesaji verilir.
 */
void MAP::setGrid(int indexX, int indexY, int value) {
    if (indexX >= 0 && indexX < numberX && indexY >= 0 && indexY < numberY) {
        grid[indexX][indexY] = value;  // Yeni degeri atar
        std::cout << "Grid at (" << indexX << ", " << indexY << ") set to " << value << "." << std::endl;
    }
    else {
        std::cerr << "Invalid grid access: (" << indexX << ", " << indexY << ") out of bounds." << std::endl;
    }
}

/**
 * @brief Haritanin tamamini sifirlar.
 *
 * Haritadaki tum hucreler sifirlanir. Eger grid henuz olusturulmamissa,
 * hata mesaji verilir.
 */
void MAP::clearMap() {
    if (grid) {
        for (int i = 0; i < numberX; ++i) {
            std::fill(grid[i], grid[i] + numberY, 0);  // Her hucreyi sifirla
        }
        std::cout << "Map cleared." << std::endl;
    }
    else {
        std::cerr << "Grid not initialized. Cannot clear." << std::endl;
    }
}

/**
 * @brief Harita hakkinda bilgi verir.
 *
 * Haritanin boyutlari ve grid boyutunu ekrana yazdirir.
 */
void MAP::printInfo() const {
    std::cout << "MAP Size: " << numberX << " x " << numberY << std::endl;
    std::cout << "Grid Size: " << gridSize << std::endl;
    std::cout << "Map: " << std::endl;
    showMap();  // Haritayi ekrana yazdirir
}

/**
 * @brief Harita grid'ini konsola yazdirir.
 *
 * Harita grid'ini her satirda hucreleri gostererek ekrana yazdirir.
 * 0'lar bos hucreleri, 1'ler dolu hucreleri temsil eder.
 */
void MAP::showMap() const {
    if (!grid) {
        std::cerr << "Grid not initialized. Cannot display map." << std::endl;
        return;
    }

    for (int i = 0; i < numberX; ++i) {
        for (int j = 0; j < numberY; ++j) {
            std::cout << (grid[i][j] == 0 ? ". " : "x ");  // 0 bos, 1 dolu hucreyi goster
        }
        std::cout << '\n';
    }
}

/**
 * @brief Grid boyutunu donduru (X ekseni).
 *
 * @return X boyutundaki grid sayisi.
 */
int MAP::getNumberX() const {
    return numberX;
}

/**
 * @brief Grid boyutunu donduru (Y ekseni).
 *
 * @return Y boyutundaki grid sayisi.
 */
int MAP::getNumberY() const {
    return numberY;
}

/**
 * @brief Grid boyutunu buyutme islemi (sadece gosterim icin).
 */
void MAP::addGridSize() {
    std::cout << "Grid Size: " << gridSize << std::endl;
}

/**
 * @brief Grid boyutunu degistirir ve haritayi gunceller.
 *
 * @param GSize Yeni grid boyutu.
 *
 * Bu fonksiyon grid boyutunu gunceller. Yeni boyuta gore harita yeniden boyutlandirilir.
 * Gecerli grid noktalarina uygun olarak harita yeniden yerlestirilir.
 */
void MAP::setGridSize(double GSize) {
    int maxPoints = numberX * numberY;

    // Dinamik olarak 2 boyutlu bir dizi olustur
    int** markedPoints = new int* [maxPoints];
    for (int i = 0; i < maxPoints; ++i) {
        markedPoints[i] = new int[2];
    }

    int markedCount = 0;

    // Isaretli noktalari bul ve kaydet
    for (int i = 0; i < numberX; ++i) {
        for (int j = 0; j < numberY; ++j) {
            if (grid[i][j] == 1) {
                markedPoints[markedCount][0] = i;
                markedPoints[markedCount][1] = j;
                markedCount++;
            }
        }
    }

    clearMap(); // Mevcut haritayi temizle

    gridSize = GSize;

    // Gecersiz grid boyutu kontrolu
    if (gridSize <= 0) {
        std::cerr << "Invalid grid size!" << std::endl;
        return;
    }

    // Yeni grid boyutlarini hesapla
    numberX = static_cast<int>(ceil(static_cast<double>(numberX) / gridSize));
    numberY = static_cast<int>(ceil(static_cast<double>(numberY) / gridSize));

    // Yeni gridi sifirla (yeni griddeki tum elemanlari 0 yap)
    grid = new int* [numberX];
    for (int i = 0; i < numberX; ++i) {
        grid[i] = new int[numberY]();  // Her satir sifirlanmis olacak
    }

    // Isaretli noktalari yeni gride ekle
    for (int i = 0; i < markedCount; ++i) {
        // Isaretli noktayi yeni grid boyutuna gore olceklendir
        int newX = static_cast<int>(markedPoints[i][0]);
        int newY = static_cast<int>(markedPoints[i][1]);

        // Yeni noktayi ekle
        insertPoint(Point(newX, newY));
    }

    // Bellegi serbest birak
    for (int i = 0; i < maxPoints; ++i) {
        delete[] markedPoints[i];
    }
    delete[] markedPoints;
}

/**
 * @brief Haritayi konsola yazdirmak icin `<<` operatoru.
 *
 * @param os Cikis akisi nesnesi.
 * @param map MAP nesnesi.
 * @return Cikis akisi nesnesi.
 */
std::ostream& operator<<(std::ostream& os, const MAP& map) {
    for (int i = 0; i < map.numberX; ++i) {
        for (int j = 0; j < map.numberY; ++j) {
            os << (map.grid[i][j] == 0 ? ". " : "x ");
        }
        os << '\n';
    }
    return os;
}
