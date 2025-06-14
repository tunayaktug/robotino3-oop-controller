/**
 * @file    menu.cpp
 * @brief   Kalitim kullanarak menu tabanli robot kontrol ornegi.
 * @author  Yusuf Yaman (152120221075)
 * @date    27.12.2024
 */

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "RobotControler.h"
#include "IRSensor.h"
#include "LidarSensor.h"
#include "Mapper.h"
#include "SafeNavigation.h"
#include "Encryption.h"

using namespace std;

/**
 * @class Menu
 * @brief Tum menuler icin temel (base) soyut sinif.
 *
 * Ortak islevleri (menu basligini ve seceneklerini ekrana yazdirma, kullanicidan secim alma) icerir.
 * Alt siniflar "execute(int)" metodunu override ederek ozel islemlerini uygular.
 */
class Menu {
protected:
    string title;              ///< Menu basligi
    vector<string> items;      ///< Menude gosterilecek secenek metinleri

public:
    /**
     * @brief Menu sinifi kurucu fonksiyonu.
     * @param t Menu basligi.
     * @param i Menu ogeleri.
     */
    Menu(const string& t, const vector<string>& i)
        : title(t), items(i) {
    }

    virtual ~Menu() = default;

    /**
     * @brief Menuyu ekrana yazar.
     */
    void display() const {
        cout << "\n========================================" << endl;
        cout << "              " << title << "              " << endl;
        cout << "========================================" << endl;

        for (size_t i = 0; i < items.size(); ++i) {
            cout << "   [" << (i + 1) << "] " << items[i] << endl;
        }
        cout << "----------------------------------------" << endl;
        cout << "   Please select an option: ";
    }

    /**
     * @brief Kullanicidan menu secimini alir.
     * @return Secilen menu maddesinin numarasi.
     */
    int select() const {
        int choice;
        cin >> choice;
        return choice;
    }

    /**
     * @brief Secime gore islemleri gerceklestirmek icin alt siniflarda override edilir.
     * @param option Kullanicinin menude sectigi madde.
     */
    virtual void execute(int option) = 0;
};

/**
 * @class AccessMenu
 * @brief openAccess / closeAccess islemlerini yonetir.
 */
class AccessMenu : public Menu {
private:
    RobotControler* controller; ///< Robot kontrolcusu

public:
    /**
     * @brief AccessMenu sinifi kurucu fonksiyonu.
     * @param rc Robot kontrolcusu isaretcisi.
     */
    AccessMenu(RobotControler* rc)
        : Menu("ACCESS MENU", { "Open Access", "Close Access", "Back" }),
        controller(rc) {
    }

    void execute(int option) override {
        switch (option) {
        case 1: {
            cout << "\n>> Enter access code (Hint:1234): ";
            int code;
            cin >> code;
            controller->openAccess(code);
            break;
        }
        case 2: {
            cout << "\n>> Enter access code (Hint:1234): ";
            int code;
            cin >> code;
            controller->closeAccess(code);
            break;
        }
        case 3:
            cout << "\n>> Going back to the previous menu..." << endl;
            break;
        default:
            cout << "\n!! Invalid selection! Try again." << endl;
            break;
        }
    }
};

/**
 * @class ConnectionMenu
 * @brief Robot baglanti/baglanti kesme islemleri.
 */
class ConnectionMenu : public Menu {
private:
    RobotControler* controller; ///< Robot kontrolcusu

public:
    /**
     * @brief ConnectionMenu sinifi kurucu fonksiyonu.
     * @param rc Robot kontrolcusu isaretcisi.
     */
    ConnectionMenu(RobotControler* rc)
        : Menu("CONNECTION MENU", { "Connect Robot", "Disconnect Robot", "Back" }),
        controller(rc) {
    }

    void execute(int option) override {
        switch (option) {
        case 1: {
            if (controller->connectRobot()) {
                cout << "\n>> Robot successfully connected!" << endl;
            }
            else {
                cout << "\n!! Failed to connect robot!" << endl;
            }
            break;
        }
        case 2: {
            if (controller->disconnectRobot()) {
                cout << "\n>> Robot successfully disconnected!" << endl;
            }
            else {
                cout << "\n!! Failed to disconnect robot!" << endl;
            }
            break;
        }
        case 3:
            cout << "\n>> Returning to the previous menu..." << endl;
            break;
        default:
            cout << "\n!! Invalid selection! Please try again." << endl;
            break;
        }
    }
};

/**
 * @class MotionMenu
 * @brief Robot hareket komutlarini yoneten menu.
 */
class MotionMenu : public Menu {
private:
    RobotControler* controller; ///< Robot kontrolcusu
    SafeNavigation* safeNav;    ///< Guvenli navigasyon nesnesi

public:
    /**
     * @brief MotionMenu sinifi kurucu fonksiyonu.
     * @param rc Robot kontrolcusu isaretcisi.
     * @param sn Guvenli navigasyon nesnesi isaretcisi.
     */
    MotionMenu(RobotControler* rc, SafeNavigation* sn)
        : Menu("MOTION MENU",
            { "Move Forward", "Move Backward", "Move Right", "Move Left",
             "Safe Move Forward", "Safe Move Backward",
             "Turn Left", "Turn Right", "Stop", "Back" }),
        controller(rc), safeNav(sn) {
    }

    void execute(int option) override {
        if (!controller->isAccessGranted()) {
            cout << "\n!! Access denied! Please provide the correct access code first." << endl;
            return;
        }

        if (!controller->isConnected()) {
            cout << "\n!! Robot is not connected! Please connect the robot first." << endl;
            return;
        }

        switch (option) {
        case 1:
            controller->moveForward();
            break;
        case 2:
            controller->moveBackward();
            break;
        case 3:
            controller->moveRight();
            break;
        case 4:
            controller->moveLeft();
            break;
        case 5:
            safeNav->moveForwardSafe();
            break;
        case 6:
            safeNav->moveBackwardSafe();
            break;
        case 7:
            controller->turnLeft();
            break;
        case 8:
            controller->turnRight();
            break;
        case 9:
            controller->stop();
            break;
        case 10:
            cout << "\n>> Returning to the previous menu..." << endl;
            break;
        default:
            cout << "\n!! Invalid selection! Please try again." << endl;
            break;
        }
    }
};

/**
 * @class SensorMenu
 * @brief Sensor islemleri menusu.
 */
class SensorMenu : public Menu {
private:
    RobotControler* controller; ///< Robot kontrolcusu
    IRSensor* irSensor;        ///< Kizilotesi sensor nesnesi
    LidarSensor* lidarSensor;  ///< Lidar sensor nesnesi
    Mapper* mapper;            ///< Harita isleyici nesnesi

public:
    /**
     * @brief SensorMenu sinifi kurucu fonksiyonu.
     * @param rc Robot kontrolcusu isaretcisi.
     * @param ir IR sensor isaretcisi.
     * @param lidar Lidar sensor isaretcisi.
     * @param mapPtr Harita isleyici isaretcisi.
     */
    SensorMenu(RobotControler* rc, IRSensor* ir, LidarSensor* lidar, Mapper* mapPtr)
        : Menu("SENSOR MENU",
            { "Update IR Sensor", "Show IR Sensor Distance",
             "Show Lidar Sensor Distance", "Update Map",
             "Print Map", "Record Map", "Back" }),
        controller(rc), irSensor(ir), lidarSensor(lidar), mapper(mapPtr) {
    }

    void execute(int option) override {
        if (!controller->isAccessGranted()) {
            cout << "\n!! Access denied! Please provide the correct access code first." << endl;
            return;
        }

        if (!controller->isConnected()) {
            cout << "\n!! Robot is not connected! Please connect the robot first." << endl;
            return;
        }

        switch (option) {
        case 1:
            irSensor->update();
            break;
        case 2:
            for (int i = 0; i < 9; ++i) {
                double distance = irSensor->getRange(i);
                cout << "   -> IR Sensor " << i << " distance: " << distance << " m" << endl;
            }
            break;
        case 3:
            lidarSensor->update();
            for (int i = 0; i < lidarSensor->getRangeNumber(); ++i) {
                cout << "   -> Lidar dist[" << i << "]: " << lidarSensor->getRange(i) << " m" << endl;
            }
            break;
        case 4:
            if (mapper) {
                mapper->updateMap();
            }
            else {
                cout << "\n!! Mapper not initialized!" << endl;
            }
            break;
        case 5:
            if (mapper) {
                mapper->showMap();
            }
            else {
                cout << "\n!! Mapper not initialized!" << endl;
            }
            break;
        case 6:
            if (mapper) {
                mapper->recordMap();
            }
            else {
                cout << "\n!! Mapper not initialized!" << endl;
            }
            break;
        case 7:
            cout << "\n>> Returning to the previous menu..." << endl;
            break;
        default:
            cout << "\n!! Invalid selection! Please try again." << endl;
            break;
        }
    }
};

/**
 * @class MainMenu
 * @brief Ana menu, alt menuleri yonetir.
 */
class MainMenu : public Menu {
private:
    RobotControler* controller; ///< Robot kontrolcusu
    SafeNavigation* safeNav;    ///< Guvenli navigasyon nesnesi
    IRSensor* irSensor;        ///< Kizilotesi sensor nesnesi
    LidarSensor* lidarSensor;  ///< Lidar sensor nesnesi
    Mapper* mapper;            ///< Harita isleyici nesnesi

public:
    /**
     * @brief MainMenu sinifi kurucu fonksiyonu.
     * @param rc Robot kontrolcusu isaretcisi.
     * @param sn Guvenli navigasyon nesnesi isaretcisi.
     * @param ir IR sensor isaretcisi.
     * @param lidar Lidar sensor isaretcisi.
     * @param mp Harita isleyici isaretcisi.
     */
    MainMenu(RobotControler* rc, SafeNavigation* sn,
        IRSensor* ir, LidarSensor* lidar, Mapper* mp)
        : Menu("MAIN MENU", { "Access", "Connection", "Motion", "Sensor", "Quit" }),
        controller(rc), safeNav(sn), irSensor(ir), lidarSensor(lidar), mapper(mp) {
    }

    void execute(int option) override {
        switch (option) {
        case 1: {
            AccessMenu accessMenu(controller);
            while (true) {
                accessMenu.display();
                int sel = accessMenu.select();
                if (sel == 3) break;
                accessMenu.execute(sel);
            }
            break;
        }
        case 2: {
            ConnectionMenu connectionMenu(controller);
            while (true) {
                connectionMenu.display();
                int sel = connectionMenu.select();
                if (sel == 3) break;
                connectionMenu.execute(sel);
            }
            break;
        }
        case 3: {
            MotionMenu motionMenu(controller, safeNav);
            while (true) {
                motionMenu.display();
                int sel = motionMenu.select();
                if (sel == 10) break;
                motionMenu.execute(sel);
            }
            break;
        }
        case 4: {
            SensorMenu sensorMenu(controller, irSensor, lidarSensor, mapper);
            while (true) {
                sensorMenu.display();
                int sel = sensorMenu.select();
                if (sel == 7) break;
                sensorMenu.execute(sel);
            }
            break;
        }
        case 5:
            cout << "\n>> Exiting program..." << endl;
            exit(0);
        default:
            cout << "\n!! Invalid selection!" << endl;
            break;
        }
    }
};

/**
 * @brief Programin baslangic noktasi.
 *
 * Ana menuyu olusturur ve program dongusunu baslatir.
 * @return Program cikis durumu.
 */
int main() {
    Encryption encryption;
    RobotControler controller("Yusuf", "Yaman", encryption.encrypt(1234), false);
    IRSensor irSensor;
    LidarSensor lidarSensor;
    SafeNavigation safeNav(&irSensor, &controller);
    Mapper mapper(15, 15, controller);

    MainMenu mainMenu(&controller, &safeNav, &irSensor, &lidarSensor, &mapper);

    while (true) {
        mainMenu.display();
        int choice = mainMenu.select();
        mainMenu.execute(choice);
    }

    return 0;
}
