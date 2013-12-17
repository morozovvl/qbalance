#include "driverfr.h"
#include "../kernel/app.h"
#include "../../drvfr/drvfr.h"


DriverFR* DriverFR::Exemplar = 0;


DriverFR::DriverFR(QObject *parent) : QObject(parent)
{
    fr = 0;
    prop = 0;
    if (!Exemplar)
        Exemplar = this;
}


bool DriverFR::open()
{
    // Инициализация драйвера
//    fr = drvfrInitialize();
//    prop = fr->prop;

    // Установление связи с ккм
//    prop->ComPortNumber = 1;            // COM1
//    prop->BaudRate      = 6;            // 115200
//    prop->Timeout       = 50;

    return true;
}


int DriverFR::Connect()
{
    return fr->Connect();
}


int DriverFR::DisConnect()
{
    return 0;
}


int DriverFR::Beep()
{
    return 0;
}

