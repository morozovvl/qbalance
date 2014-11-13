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


bool DriverFR::open(int port)
{
    // Инициализация драйвера
/*
    fr = drvfrInitialize();
    if (fr != NULL)
    {
        prop = fr->prop;

        // Установление связи с ккм
        prop->ComPortNumber = port;         // COM1
        prop->BaudRate      = 6;            // 115200
        prop->Timeout       = 50;

        if (fr->Connect() != -1)
        {
            return true;
        }
    }
*/
    return false;
}


void DriverFR::close()
{
    fr->DisConnect();
}


int DriverFR::Beep()
{
    return fr->Beep();
}

