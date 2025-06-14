#include "FestoRobotInterface.h"
#include <iostream>

FestoRobotInterface::FestoRobotInterface()
{
    robotAPI = new FestoRobotAPI(); ///< Yeni bir robot nesnesi olusturulur.
    connectionStatus = false; ///< Baslangicta baglanti yoktur.
    position = new Pose(); ///< Pozisyon bilgisi null olarak baslar.
}

FestoRobotInterface::~FestoRobotInterface()
{
    if (connectionStatus)
    {
        robotAPI->disconnect(); ///< Robot baglantisi kesilir.
        connectionStatus = false;
        delete robotAPI; ///< robotAPI nesnesi serbest birakilir.
        delete position; ///< position nesnesi serbest birakilir.
    }
    delete robotAPI; ///< robotAPI nesnesi serbest birakilir.
    delete position; ///< position nesnesi serbest birakilir.
}

void FestoRobotInterface::turnLeft()
{
    if (connectionStatus == true)
    {
        robotAPI->rotate(LEFT); ///< Robota sola donme komutu verilir.
        getPose(); ///< Pozisyon bilgisi alinir.
        double tempTh = position->getTh(); ///< Pozisyon bilgisi elde edilir.
        position->setTh(tempTh);
        tempTh = position->getTh();
    }
    else
    {
        robotAPI->connect();
        connectionStatus = true; ///< Tekrar baglanti kurulur.
        cout << "Cihaza baglanilamiyor, tekrardan deneniyor.\n";
        if (connectionStatus == false)
        {
            cout << "Cihaza baglanilamadi.\n";
        }
    }
}

void FestoRobotInterface::turnRight()
{
    if (connectionStatus == true)
    {
        robotAPI->rotate(RIGHT); ///< Robota saga donme komutu verilir.
        getPose(); ///< Pozisyon bilgisi alinir.
        double tempTH = position->getTh(); ///< Pozisyon bilgisi elde edilir.
        position->setTh(tempTH); ///< Pozisyon bilgisi guncellenir.
        tempTH = position->getTh();
    }
    else
    {
        robotAPI->connect();
        connectionStatus = true; ///< Tekrar baglanti kurulur.
        cout << "Cihaza baglanilamiyor, tekrardan deneniyor.\n";
        if (connectionStatus == false)
        {
            cout << "Cihaza baglanilamadi.\n";
        }
    }
}

void FestoRobotInterface::moveForward()
{
    if (connectionStatus == true)
    {
        robotAPI->move(FORWARD); ///< Robota ileri hareket komutu verilir.
    }
    else
    {
        robotAPI->connect();
        connectionStatus = true; ///< Tekrar baglanti kurulur.
        cout << "Cihaza baglanilamiyor, tekrardan deneniyor.\n";
        if (connectionStatus == false)
        {
            cout << "Cihaza baglanilamadi.\n";
        }
    }
}

void FestoRobotInterface::moveBackward()
{
    if (connectionStatus == true)
    {
        robotAPI->move(BACKWARD); ///< Robota geri hareket komutu verilir.
    }
    else
    {
        robotAPI->connect();
        connectionStatus = true; ///< Tekrar baglanti kurulur.
        cout << "Cihaza baglanilamiyor, tekrardan deneniyor.\n";
        if (connectionStatus == false)
        {
            cout << "Cihaza baglanilamadi.\n";
        }
    }
}

void FestoRobotInterface::moveLeft()
{
    if (connectionStatus == true)
    {
        robotAPI->move(LEFT); ///< Robota sola hareket komutu verilir.
    }
    else
    {
        robotAPI->connect();
        connectionStatus = true; ///< Tekrar baglanti kurulur.
        cout << "Cihaza baglanilamiyor, tekrardan deneniyor.\n";
        if (connectionStatus == false)
        {
            cout << "Cihaza baglanilamadi.\n";
        }
    }
}

void FestoRobotInterface::moveRight()
{
    if (connectionStatus == true)
    {
        robotAPI->move(RIGHT); ///< Robota saga hareket komutu verilir.
    }
    else
    {
        robotAPI->connect();
        connectionStatus = true; ///< Tekrar baglanti kurulur.
        cout << "Cihaza baglanilamiyor, tekrardan deneniyor.\n";
        if (connectionStatus == false)
        {
            cout << "Cihaza baglanilamadi.\n";
        }
    }
}

void FestoRobotInterface::stop()
{
    if (connectionStatus == true)
    {
        robotAPI->stop(); ///< Robota durdurma komutu verilir.
        getPose(); ///< Pozisyon bilgisi alinir.
    }
    else
    {
        robotAPI->connect();
        connectionStatus = true; ///< Tekrar baglanti kurulur.
        cout << "Cihaza baglanilamiyor, tekrardan deneniyor.\n";
        if (connectionStatus == false)
        {
            cout << "Cihaza baglanilamadi.\n";
        }
    }
}

Pose FestoRobotInterface::getPose()
{
    if (connectionStatus)
    {
        double x, y, Th;
        robotAPI->getXYTh(x, y, Th); ///< Robotun X, Y ve Th degerleri alinir.
        position->setX(x);
        position->setY(y);
        position->setTh(Th);

        return *position;  ///< Pozisyon bilgisi geri dondurulur.
    }
    else
    {
        cout << "Hata!!! Robota baglanilamadi.\n"; ///< Baglanti yoksa hata mesaji yazdirilir.
        return Pose();  ///< Varsayilan pozisyon bilgisi dondurulur.
    }
}

void FestoRobotInterface::print()
{
    if (connectionStatus == false)
    {
        cout << "Baglanti durumu(0 kapali, 1 acik)=" << connectionStatus; ///< Baglanti durumu yazdirilir.
        return;
    }

    else
    {
        Pose robotAPIPose = getPose();
        cout << "Pozisyon degerleri: X(" << robotAPIPose.getX() << ") Y("
            << robotAPIPose.getY() << ") TH(" << robotAPIPose.getTh() << ") "
            << "Baglanti durumu(0 kapali, 1 acik)="
            << connectionStatus << endl; ///< Pozisyon bilgileri ve baglanti durumu yazdirilir.
    }
}

bool FestoRobotInterface::connectRobot()
{
    if (connectionStatus == false)
    {
        robotAPI->connect(); ///< Robota baglanilir.
        connectionStatus = true; ///< Baglanti durumu true yapilir.
        if (connectionStatus == true)
        {
            cout << "Robota baglandi.\n"; ///< Baglanti basariliysa mesaj yazdirilir.
            return true;
        }
        else
        {
            cout << "Baglanirken bir problem olustu.\n"; ///< Hala baglanti saglanamamissa mesaj yazdirilir.
            return false;
        }
    }
    else
    {
        cout << "Hali hazirda acik.\n"; ///< Robot zaten bagliysa mesaj yazdirilir.
        return false;
    }
}

bool FestoRobotInterface::disconnectRobot()
{
    if (connectionStatus == true)
    {
        robotAPI->disconnect(); ///< Baglanti kesilir.
        connectionStatus = false;
        if (connectionStatus == false)
        {
            cout << "Robot basarili bir sekilde kapatildi \n"; ///< Robot basariyla kapatildi mesaji yazdirilir.
            return true;
        }
        else
        {
            cout << "Hata!!! Cihaz kapatilamiyor.\n"; ///< Hata varsa mesaj yazdirilir.
            return false;
        }
    }
    else
    {
        cout << "Halihazirda kapali\n"; ///< Robot zaten kapaliysa mesaj yazdirilir.
        return false;
    }
}