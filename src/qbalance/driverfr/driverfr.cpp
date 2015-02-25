#include "../kernel/app.h"
#include "../kernel/tcpserver.h"


unsigned DriverFR::commlen[0x100] =
{
   0,  6,  5,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 0x00 - 0x0f
   0,  5, 26,  5,  8,  6,  1, 46, 37,  6,  6,  6, 10,  5,  255,  9, // 0x10 - 0x1f
   6,  8,  8,  8,  5,  6,  0,  5,  6,  7,  5,  5,  5,  6,  7,  0, // 0x20 - 0x2f
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 0x30 - 0x3f
   5,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 0x40 - 0x4f
  10, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 0x50 - 0x5f
   9,  1,  6,  5,  5, 20, 12, 10,  5,  6,  0,  0,  0,  0,  0,  0, // 0x60 - 0x6f
 255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 0x70 - 0x7f
  60, 60, 60, 60, 60, 71, 54, 54,  5,  5, 54, 54,  0,  0,  0,  0, // 0x80 - 0x8f
  61, 57, 52, 11, 12, 52,  7,  7,  7,  5, 13,  7,  0,  0,  7,  7, // 0x90 - 0x9f
  13, 11, 12, 10, 10,  8,  7,  5,  0,  0,  0,  0,  0,  0,  0,  0, // 0xa0 - 0xaf
   5,  0,  0,  5,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 0xb0 - 0xbf
  46,  7, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 0xc0 - 0xcf
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 0xd0 - 0xdf
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 0xe0 - 0xef
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,255,  0,  0  // 0xf0 - 0xff
};

BaudRateType DriverFR::LineSpeedVal[7] = {BAUD2400, BAUD4800, BAUD9600, BAUD19200, BAUD38400, BAUD57600, BAUD115200};

const char* DriverFR::errmsg[] =
{
  "No errors found",													//00
  "Fiscal memory or timer error",											//01
  "Fiscal memory 1 is missing",												//02
  "Fiscal memory 2 is missing",												//03
  "Invalid arguments",													//04
  "There is no queried data",												//05
  "Output mode",													//06
  "Invalid arguments for the particular device",									//07
  "Invalid command for the particular device",										//08
  "Invalid command lengh",												//09
  "Invalid data format",												//0a
  "",															//0b
  "",															//0c
  "",															//0d
  "",															//0e
  "",															//0f
  "",															//10
  "No License",														//11
  "Factory number is already entered",											//12
  "Current date is less then last operation date",									//13
  "Subtotal memory is full",												//14
  "Shift ia opened",													//15
  "Shift is not opened",												//16
  "The number of the first shift larger then the last shift number",							//17
  "The date of the first shift is later then the last shift date",							//18
  "There is no queried data",												//19
  "",															//1a
  "Factory number is not entered",											//1b
  "There is corrupt data in the sertain range",										//1c
  "The last subtotal record is corrupt",										//1d
  "Registration limit is achieved",											//1e
  "Register memory is not present",											//1f
  "Money register overflow while adding data",										//20
  "Register value is less",												//21
  "Invalid date",													//22
  "",															//23
  "",															//24
  "",															//25
  "",															//26
  "",															//27
  "",															//28
  "",															//29
  "",															//2a
  "",															//2b
  "",															//2c
  "",															//2d
  "",															//2e
  "",															//2f
  "",															//30
  "",															//31
  "",															//32
  "Invalid command parameters",												//33
  "There is no queried data",												//34
  "Invalid command parameter for the current settings",									//35
  "Invalid command parameters for the particular device",								//36
  "Invalid command for the particular device",										//37
  "User memory error",													//38
  "Internal software error",												//39
  "",															//3a
  "",															//3b
  "Operation is not completed. Shift is opened",									//3c
  "Operation is not completed. Shift is not opened",									//3d
  "",															//3e
  "",															//3f
  "",															//40
  "",															//41
  "",															//42
  "",															//43
  "",															//44
  "Сумма всех типов оплаты меньше итога чека",					//45
  "",															//46
  "",															//47
  "Subtotal overflow",													//48
  "Operation is not completed with this type of opened bill",								//49
  "Operation is not completed. Bill is not opened",									//4a
  "Bill's buffer is full",												//4b
  "",															//4c
  "Non cash summ is greater of bill summ",										//4d
  "Shift is active more then 24 hours",											//4e
  "Invalid password",													//4f
  "Printing the previous command",											//50
  "",															//51
  "",															//52
  "",															//53
  "",															//54
  "Operation is not completed. Bill is closed",										//55
  "",															//56
  "",															//57
  "Waiting for printing command continuing",										//58
  "Document is opened by another operator",										//59
  "Discount is greater of the proffit",											//5a
  "",															//5b
  "",															//5c
  "Table is not defined",												//5d
  "",															//5e
  "",															//5f
  "",															//60
  "",															//61
  "",															//62
  "",															//63
  "Fiscal memory is not present",											//64
  "",															//65
  "",															//66
  "Error connecting to the device",											//67
  "",															//68
  "",															//69
  "",															//6a
  "Bill tape is out",													//6b
  "Controll tape is out",												//6c
  "",															//6d
  "",															//6e
  "",															//6f
  "Fiscal memory overflow",												//70
  "Knife error",													//71
  "Invalid command in this submode",											//72
  "Invalid command in this mode",											//73
  "Base memory error",                                          //74
  "",           // 75
    "",         // 76
    "",         // 77
    "",         // 78
    "",         // 79
    "",         // 7a
    "",         // 7b
    "",         // 7c
    "",         // 7d
    "",         // 7e
    "",         // 7f
    "",         // 80
    "",         // 81
    "",         // 82
    "",         // 83
    "",         // 84
    "",         // 85
    "",         // 86
    "",         // 87
    "",         // 88
    "",         // 89
    "",         // 8a
    "",         // 8b
    "",         // 8c
    "",         // 8d
    "",         // 8e
    "",         // 8f

    "",         // 90
    "",         // 91
    "",         // 92
    "",         // 93
    "",         // 94
    "",         // 95
    "",         // 96
    "",         // 97
    "",         // 98
    "",         // 99
    "",         // 9a
    "",         // 9b
    "",         // 9c
    "",         // 9d
    "",         // 9e
    "",         // 9f

    "",         // a0
    "",         // a1
    "",         // a2
    "Некорректное состояние ЭКЛЗ",         // a3
    "",         // a4
    "",         // a5
    "",         // a6
    "",         // a7
    "",         // a8
    "ЭКЛЗ: Нет запрошенных данных",         // a9
    "",         // aa
    "",         // ab
    "",         // ac
    "",         // ad
    "",         // ae
    "",         // af

    "",         // b0
    "",         // b1
    "",         // b2
    "",         // b3
    "",         // b4
    "",         // b5
    "",         // b6
    "",         // b7
    "",         // b8
    "",         // b9
    "",         // ba
    "",         // bb
    "",         // bc
    "",         // bd
    "",         // be
    "",         // bf

    "",         // c0
    "",         // c1
    "",         // c2
    "",         // c3
    "",         // c4
    "",         // c5
    "",         // c6
    "",         // c7
    "",         // c8
    "",         // c9
    "",         // ca
    "",         // cb
    "",         // cc
    "",         // cd
    "",         // ce
    "",         // cf

    "",         // d0
    "",         // d1
    "",         // d2
    "",         // d3
    "",         // d4
    "",         // d5
    "",         // d6
    "",         // d7
    "",         // d8
    "",         // d9
    "",         // da
    "",         // db
    "",         // dc
    "",         // dd
    "",         // de
    "",         // df

    "",         // e0
    "",         // e1
    "",         // e2
    "",         // e3
    "",         // e4
    "",         // e5
    "",         // e6
    "",         // e7
    "",         // e8
    "",         // e9
    "",         // ea
    "",         // eb
    "",         // ec
    "",         // ed
    "",         // ee
    "",         // ef

    "",         // f0
    "",         // f1
    "",         // f2
    "",         // f3
    "",         // f4
    "",         // f5
    "",         // f6
    "",         // f7
    "",         // f8
    "",         // f9
    "",         // fa
    "",         // fb
    "",         // fc
    "",         // fd
    "",         // fe
    ""         // ff
};

const char* DriverFR::ecrmodedesc[] =
{
  "",
  "Data output",													//0
  "Shift is opened less then 24 hours",											//1
  "Shift is opened more then 24 hours",											//2
  "Shift is closed",													//3
  "Blocked due to wrong Tax Inspector password entry",									//4
  "Waiting for date entry confirmation",										//5
  "Changing decimal point position mode",										//6
  "Document is opened",													//7
  "Tech. reset & tables init. mode",											//8
  "Test feed",														//9
  "Full fiscal report printing",											//10
  "EKLZ report printing"												//11
};

const char* DriverFR::ecrmode8desc[] =
{
  "Sale check is opened",
  "Buy check is opened",
  "Sale return check is opened",
  "Buy return check is opened"
};

const char* DriverFR::ecrsubmodedesc[] =
{
  "",
  "Passive out of paper",
  "Active out of paper",
  "Waiting for print continue",
  "Printing operation",
  "Full printing operation"
};

const char* DriverFR::devcodedesc[] =
{
  "FM1 flash",
  "FM2 flash",
  "Clock",
  "Powerindependent memory",
  "FM processor",
  "FR usr memory",
  "FR base memory"
};


DriverFR::DriverFR(QObject *parent) : QObject(parent)
{
    connected = false;
    remote = false;
    locked = false;
    codec = QTextCodec::codecForName("Windows-1251");
}


bool DriverFR::open(int port, int rate, int password, QString ipAddress, int ipPort)
{
    // Установление связи с ккм
    fr.ComPortNumber = port;
    fr.BaudRate      = rate;
    fr.Timeout       = 50;
    fr.Password      = password;

    serialPort = new QMyExtSerialPort(devName(fr.ComPortNumber), QextSerialPort::Polling);
    if (serialPort != 0)
    {
        // Сначала поищем фискальник на этом компьютере

        serialPort->setBaudRate(LineSpeedVal[fr.BaudRate]);
        serialPort->setFlowControl(FLOW_OFF);
        serialPort->setParity(PAR_NONE);
        serialPort->setDataBits(DATA_8);
        serialPort->setStopBits(STOP_2);
        if (serialPort->open(QIODevice::ReadWrite))
        {
            serialPort->writeLog(QString("Скорость: %1").arg(fr.BaudRate));
            serialPort->writeLog(QString("Таймаут: %1").arg(fr.Timeout));
            return true;
        }

        // а теперь поищем на удаленном, если указан его IP
        if (ipAddress.size() > 0)
        {
            serialPort->setTcpClient(ipAddress, ipPort);        // Создадим TCP клиент для удаленной работы с ФР
            TApplication::exemplar()->timeOut(1000);
            if (serialPort->getTcpClient()->isValid())
            {
                remote = true;
                return true;                                            // тогда все нормально
            }
            serialPort->closeTcpClient();                               // иначе закроем TCP клиент
                                                                        // и все плохо
                                                                        // к фискальнику не удалось подсоединиться
        }
    }
    return false;
}


void DriverFR::close()
{
    connected = false;
    serialPort->close();
    delete serialPort;
}


QString DriverFR::devName(int number)
{
    if (number > 0 && number < 10)
    {
#ifdef Q_OS_WIN32
        return QString("COM%1").arg(number);
#else
        return QString("/dev/ttyUSB%1").arg(number - 1);
#endif
    }
    return "";
}


int DriverFR::checkState()
{
  short int repl;

  sendENQ();
  repl = readByte(fr.Timeout * 2);
  switch(repl)
    {
      case NAK:
        return NAK;
      case ACK:
        return ACK;
      default:
        return -1;
    }
}


int DriverFR::sendENQ()
{
    qint64 result;
    char buff[2];
    buff[0] = ENQ;
    result = serialPort->writeData(buff,1);
    serialPort->writeLog();
    return result;
}


int DriverFR::sendNAK()
{
    qint64 result;
    char buff[2];
    buff[0] = NAK;
    result = serialPort->writeData(buff, 1);
    serialPort->writeLog();
    return result;
}


int DriverFR::sendACK()
{
    qint64 result;
    char buff[2];
    buff[0] = ACK;
    result = serialPort->writeData(buff,1);
    serialPort->writeLog();
    return result;
}


unsigned short int DriverFR::readByte(int msec)
{
    for (int tries = 0; tries < MAX_TRIES; tries++)
    {
        if (msec > 0)
            TApplication::exemplar()->timeOut(msec);
        unsigned char readbuff[2] = "";
        int result = readBytes(readbuff, 1);
        if (result > 0)
        {
            return (unsigned int) readbuff[0];
        }
        else
            break;
    }
    return 0;
}


int DriverFR::readBytes(unsigned char *buff, int len)
{
    for(int i = 0; i < len; i++)
    {
           if (serialPort->readData((char*)(buff+i), 1) == -1)
           {
               return -1;
           }
    }
    return len;
}


int DriverFR::readAnswer(answer *ans)
{
    if (connected)
    {
        short int  len, crc, tries, repl;
        for (tries = 0; tries < MAX_TRIES; tries++)
        {
            repl = readByte(fr.Timeout*2);
            if (repl == STX)
            {
                len = readByte(fr.Timeout);
                if (readBytes(ans->buff, len) == len)
                {
                    crc = readByte(fr.Timeout);
                    if (crc == (LRC(ans->buff, len, 0) ^ len))
                    {
                        TApplication::exemplar()->timeOut(fr.Timeout*2);
                        sendACK();
                        ans->len = len;
                        return len;
                    }
                    else
                        sendNAK();
                }
            }
        }
        sendENQ();
        repl = readByte(fr.Timeout*2);
        if (connected != 1 || repl != ACK)
            tries++;
    }
    return -1;
}


unsigned short int DriverFR::LRC(unsigned char *str, int len, int offset)
{
  int i;
  unsigned char *ptr;
  unsigned char ch = 0;

  ptr = str + offset;
  for(i=0; i<len; i++)ch ^= ptr[i];
  return ch;
}


int DriverFR::composeComm(command *cmd, int comm, int pass, parameter *param)
{

    int len;
    for (unsigned int i = 0; i < sizeof(cmd->buff); i++)
        cmd->buff[i] = 0;

    len = commlen[comm];
    if (len >= 5 && param->len > (len - 5))
        param->len = len - 5;
    cmd->buff[0] = STX;
    cmd->buff[1] = len;
    cmd->buff[2] = comm;
    if (len >= 5)
    {
        memcpy(cmd->buff + 3, &pass, sizeof(int));
        if (param->len > 0)
            memcpy(cmd->buff + 7, param->buff, param->len);
    }
    cmd->buff[len + 2] = LRC(cmd->buff, len + 1, 1);
    cmd->len = len + 3;
    return 1;
}


int DriverFR::sendCommand(int comm, int pass, parameter *param)
{
    command cmd;
    int result = -1;
    composeComm(&cmd, comm, pass, param);
    if (serialPort->writeData((char *)cmd.buff, cmd.len) != -1)
    {
        for(int tries = 1; tries <= MAX_TRIES; tries++)
        {
            short int repl = readByte(fr.Timeout*2);
            if (repl == ACK)
            {
                serialPort->writeLog();
                result = 1;
                break;
            }
        }
    }
    return result;
}


QVariant DriverFR::getProperty(QString name)
{
    QVariant result;
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));
    const char* propName = name.toAscii().data();
    result = fr.property(propName);
    QTextCodec::setCodecForLocale(TApplication::codec());
    return result;
}


bool DriverFR::setProperty(QString name, QVariant value)
{
    bool result;
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));
    const char* propName = name.toAscii().data();
    result = fr.setProperty(propName, value);
    QTextCodec::setCodecForLocale(TApplication::codec());
    return result;
}


int DriverFR::errHand(answer *a)
{
  fr.ResultCode = a->buff[1];
  fr.ResultCodeDescription = (char*)errmsg[fr.ResultCode];
  return fr.ResultCode;
}


int DriverFR::evalint(unsigned char *str, int len)
{
    int result = 0;
    while(len--)
    {
        result <<= 8;
        result += str[len];
    }
    return result;
}


int64_t DriverFR::evalint64(unsigned char *str, int len)
{
    int64_t result = 0;
    while(len--)
    {
        result <<= 8;
        result += str[len];
    }
    return result;
}


void DriverFR::evaldate(unsigned char *str, struct tm *date)
{
  date->tm_mday = evalint(str    , 1);
  date->tm_mon  = evalint(str + 1, 1) - 1;
  date->tm_year = evalint(str + 2, 1) + 100;
  mktime(date);
}


void DriverFR::evaltime(unsigned char *str, struct tm *time)
{
  time->tm_hour = evalint(str    , 1);
  time->tm_min  = evalint(str + 1, 1);
  time->tm_sec  = evalint(str + 2, 1);
  mktime(time);
}


void DriverFR::DefineECRModeDescription(void)
{
  fr.ECRMode8Status = fr.ECRMode >> 4;
  if((fr.ECRMode & 8) == 8)
  {
    fr.ECRModeDescription = (char*)ecrmode8desc[fr.ECRMode8Status];
    return;
  }
  fr.ECRModeDescription = (char*)ecrmodedesc[fr.ECRMode];
}


bool DriverFR::Connect()
{
    int state = 0;
    connected = false;
    bool result = false;

    if (remote)
    {
        if (serialPort->isReadyDriverFR())
            locked = serialPort->setLock(true);
    }
    else
        locked = true;

    if (locked)
    {
        state = checkState();
        switch (state)
        {
            case NAK:
                {
                    connected = true;
                    result = true;
                }
                break;
            case ACK:
                {
                    connected = true;
                    result = true;
                }
                break;
            case -1:
                {
                    locked = false;
                }
                break;
        }
        if (result)
        {
            if (GetECRStatus() != 0)
                result = false;
            else if (TApplication::debugMode() == 4)
            {
                serialPort->writeLog(QString("Режим: %1 %2").arg(fr.ECRMode).arg(fr.ECRModeDescription));
                serialPort->writeLog(QString("Подрежим: %1 %2").arg(fr.ECRAdvancedMode).arg(fr.ECRAdvancedModeDescription));
            }
        }
    }
    return result;
}


void DriverFR::DisConnect()
{
    serialPort->writeLog();
    connected = false;
    locked = false;
    if (remote)
        locked = serialPort->setLock(false);
    else
        locked = false;
}


bool DriverFR::isLocked()
{
    if (remote)
        return serialPort->isLockedDriverFR();
    return locked;
}


int DriverFR::Beep()
{
    TApplication::debug(4, "<Beep>");

    parameter  p;
    answer     a;
    int result = -1;
    if (connected)
    {

        if (sendCommand(BEEP, fr.Password, &p) >= 0)
        {
            if (readAnswer(&a) >= 0)
            {
                if (a.buff[0] == BEEP)
                {
                    if (errHand(&a) != 0)
                        result = fr.ResultCode;
                    else
                    {
                        fr.OperatorNumber = a.buff[2];
                        result = 0;
                    }
                }
            }
        }
    }
    TApplication::debug(4, "</Beep>");
    return result;
}


int DriverFR::Buy()
{
  parameter  p;
  answer     a;
  p.len   = 55;

  if (!connected)
      return -1;

  int64_t quant = llround(fr.Quantity * 1000);
  int64_t price = llround(fr.Price * 100);

  memcpy(p.buff,    &quant, 5);
  memcpy(p.buff+5,  &price, 5);
  p.buff[10] = fr.Department;

  p.buff[11] = fr.Tax1;
  p.buff[12] = fr.Tax2;
  p.buff[13] = fr.Tax3;
  p.buff[14] = fr.Tax4;

  strncpy((char*)p.buff+15, (char*)fr.StringForPrinting, 40);

  if (sendCommand(BUY, fr.Password, &p) < 0)
      return -1;

  if (readAnswer(&a) < 0)
      return -1;

  if (a.buff[0] != BUY)
      return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];

  return 0;
}


int DriverFR::CutCheck()
{
  parameter  p;
  answer     a;
  p.len    = 1;

  if (!connected) return -1;

  p.buff[0] = fr.CutType;

  if (sendCommand(CUT_CHECK, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != CUT_CHECK) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];

  return 0;
}





//-----------------------------------------------------------------------------
int DriverFR::PrintString()
{
  parameter  p;
  answer     a;
  p.len	  = 41;

  if (!connected) return -1;

  p.buff[0]  = (fr.UseJournalRibbon == true) ? 1 : 0;
  p.buff[0] |= (fr.UseReceiptRibbon == true) ? 2 : 0;

  strncpy((char*)&p.buff+1, (char*)fr.StringForPrinting, 40);

  if (sendCommand(PRINT_STRING, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != PRINT_STRING) return -1;

  if (errHand(&a) != 0) return  fr.ResultCode;;

  fr.OperatorNumber = a.buff[2];

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::PrintWideString()
{
  parameter  p;
  answer     a;
  p.len	  = 21;

  if (!connected) return -1;

  p.buff[0]  = (fr.UseJournalRibbon == true) ? 1 : 0;
  p.buff[0] |= (fr.UseReceiptRibbon == true) ? 2 : 0;

  strncpy((char*)&p.buff+1, (char*)fr.StringForPrinting, 20);

  if (sendCommand(PRINT_WIDE_STRING, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != PRINT_WIDE_STRING) return -1;

  if (errHand(&a) != 0) return  fr.ResultCode;;

  fr.OperatorNumber = a.buff[2];

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::FeedDocument()
{
  parameter  p;
  answer     a;
  p.len    = 2;

  if (!connected) return -1;

  p.buff[0]  = (fr.UseJournalRibbon == true) ? 1 : 0;
  p.buff[0] |= (fr.UseReceiptRibbon == true) ? 2 : 0;
  p.buff[0] |= (fr.UseSlipDocument  == true) ? 4 : 0;

  p.buff[1] = fr.StringQuantity;

  if (sendCommand(FEED_DOCUMENT, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != FEED_DOCUMENT) return -1;

  if (errHand(&a) != 0) return  fr.ResultCode;;

  fr.OperatorNumber = a.buff[2];

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::SetExchangeParam()
{
  parameter  p;
  answer     a;
  p.len    = 3;

  if (!connected) return -1;

  p.buff[0] = fr.PortNumber;
  p.buff[1] = fr.BaudRate;
  p.buff[2] = fr.Timeout;

  if (sendCommand(SET_EXCHANGE_PARAM, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != SET_EXCHANGE_PARAM) return -1;

  return errHand(&a);
}
//-----------------------------------------------------------------------------
int DriverFR::GetExchangeParam()
{
  parameter  p;
  answer     a;
  p.len    = 1;

  if (!connected) return -1;

  p.buff[0] = fr.PortNumber;

  if (sendCommand(GET_EXCHANGE_PARAM, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != GET_EXCHANGE_PARAM) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.BaudRate = a.buff[2];
  fr.Timeout  = a.buff[3];
  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::GetECRStatus()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  if (sendCommand(GET_ECR_STATUS, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != GET_ECR_STATUS) return -1;
  if (errHand(&a))	return  fr.ResultCode;

  fr.OperatorNumber = a.buff[2];

  fr.ECRSoftVersion[0] = a.buff[3];
  fr.ECRSoftVersion[1] = 0x2e;
  fr.ECRSoftVersion[2] = a.buff[4];
  fr.ECRSoftVersion[3] = 0;

  fr.ECRBuild = evalint((unsigned char*)&a.buff + 5, 2);
  evaldate((unsigned char*)&a.buff + 7, &fr.ECRSoftDate);
  fr.LogicalNumber = evalint((unsigned char*)&a.buff + 10, 1);
  fr.OpenDocumentNumber = evalint((unsigned char*)&a.buff + 11, 2);
  fr.ReceiptRibbonIsPresent     = (a.buff[13] &   1)  ==   1; //0
  fr.JournalRibbonIsPresent     = (a.buff[13] &   2)  ==   2; //1
  fr.SlipDocumentIsPresent      = (a.buff[13] &   4)  ==   4; //2
  fr.SlipDocumentIsMoving       = (a.buff[13] &   8)  ==   8; //3
  fr.PointPosition              = (a.buff[13] &  16)  ==  16; //4
  fr.EKLZIsPresent              = (a.buff[13] &  32)  ==  32; //5
  fr.JournalRibbonOpticalSensor = (a.buff[13] &  64)  ==  64; //6
  fr.ReceiptRibbonOpticalSensor = (a.buff[13] & 128)  == 128; //6

  fr.JournalRibbonLever         = (a.buff[14] &   1)  ==   1; //0
  fr.ReceiptRibbonLever         = (a.buff[14] &   2)  ==   2; //1
  fr.LidPositionSensor          = (a.buff[14] &   4)  ==   4; //2

  fr.ECRMode  = evalint((unsigned char*)&a.buff + 15, 1);
  DefineECRModeDescription();

  fr.ECRAdvancedMode = evalint((unsigned char*)&a.buff + 16, 1);
  fr.ECRAdvancedModeDescription = (char*)ecrsubmodedesc[fr.ECRAdvancedMode];

  fr.PortNumber  = evalint((unsigned char*)&a.buff + 17, 1);
  fr.FMSoftVersion[0] = a.buff[18];
  fr.FMSoftVersion[1] = 0x2e;
  fr.FMSoftVersion[2] = a.buff[19];
  fr.FMSoftVersion[3] = 0;
  fr.FMBuild = evalint((unsigned char*)&a.buff + 20, 2);
  evaldate((unsigned char*)&a.buff + 22, &fr.FMSoftDate);
  evaldate((unsigned char*)&a.buff + 25, &fr.Date);
  evaltime((unsigned char*)&a.buff + 28, &fr.Time);
  fr.FM1IsPresent = (a.buff[31] & 1) == 1;
  fr.FM2IsPresent = (a.buff[31] & 2) == 2;
  fr.LicenseIsPresent = (a.buff[31] & 4) == 4;
  fr.FMOverflow = (a.buff[31] & 8) == 8;
  fr.BatteryCondition = (a.buff[31] & 16) == 16;
  sprintf(fr.SerialNumber, "%d", evalint((unsigned char*)&a.buff + 32, 4));
  fr.SessionNumber = evalint((unsigned char*)&a.buff + 36, 2);
  fr.FreeRecordInFM = evalint((unsigned char*)&a.buff + 38, 2);
  fr.RegistrationNumber = evalint((unsigned char*)&a.buff + 40, 1);
  fr.FreeRegistration = evalint((unsigned char*)&a.buff + 41, 1);
  sprintf(fr.INN, "%.0lg", (double)evalint64((unsigned char*)&a.buff + 42, 6));

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::GetDeviceMetrics()
{
  int len  = 0;
  parameter  p;
  answer     a;
  p.len    = 1;

  if (!connected) return -1;

  if (sendCommand(GET_DEVICE_METRICS, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != GET_DEVICE_METRICS) return -1;
  if (errHand(&a)) return  fr.ResultCode;
  len = a.len - 7;
  fr.UMajorType            = evalint((unsigned char*)&a.buff + 2, 1);
  fr.UMinorType            = evalint((unsigned char*)&a.buff + 3, 1);
  fr.UMajorProtocolVersion = evalint((unsigned char*)&a.buff + 4, 1);
  fr.UMinorProtocolVersion = evalint((unsigned char*)&a.buff + 5, 1);
  fr.UModel                = evalint((unsigned char*)&a.buff + 6, 1);
  fr.UCodePage             = evalint((unsigned char*)&a.buff + 7, 1);

  QByteArray data;
  data.append((char*)&a.buff+8);
  fr.UDescription = codec->toUnicode(data);

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::Test()
{
  parameter  p;
  answer     a;
  p.len    = 1;

  if (!connected) return -1;

  p.buff[0] = fr.RunningPeriod;

  if (sendCommand(TEST, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != TEST) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::InterruptTest()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  if (sendCommand(INTERRUPT_TEST, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != INTERRUPT_TEST) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::ContinuePrinting()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  if (sendCommand(CONTINUE_PRINTING, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != CONTINUE_PRINTING) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::OpenDrawer()
{
  parameter  p;
  answer     a;
  p.len    = 1;

  if (!connected) return -1;

  p.buff[0] = fr.DrawerNumber;

  if (sendCommand(OPEN_DRAWER, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != OPEN_DRAWER) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::PrintDocumentTitle()
{
  parameter  p;
  answer     a;
  p.len	  = 32;

  if (!connected) return -1;

  strncpy((char*)p.buff, (char*)fr.DocumentName, 30);
  memcpy(&p.buff+30, &fr.DocumentNumber, 2);

  if (sendCommand(PRINT_DOCUMENT_TITLE, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != PRINT_DOCUMENT_TITLE) return -1;

  if (errHand(&a) != 0) return  fr.ResultCode;;

  fr.OperatorNumber = a.buff[2];

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::ResetSettings()
{
  parameter  p;

  if (!connected) return -1;

  if (sendCommand(RESET_SETTINGS, fr.Password, &p) < 0) return -1;

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::ResetSummary()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  if (sendCommand(RESET_SUMMARY, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != RESET_SUMMARY) return -1;

  return errHand(&a);
}

//-----------------------------------------------------------------------------
int DriverFR::ReturnBuy()
{
  parameter  p;
  answer     a;
  p.len   = 55;

  if (!connected) return -1;

  int64_t quant = llround(fr.Quantity * 1000);
  int64_t price = llround(fr.Price * 100);

  memcpy(p.buff,    &quant, 5);
  memcpy(p.buff+5,  &price, 5);
  p.buff[10] = fr.Department;

  p.buff[11] = fr.Tax1;
  p.buff[12] = fr.Tax2;
  p.buff[13] = fr.Tax3;
  p.buff[14] = fr.Tax4;

  strncpy((char*)p.buff+15, (char*)fr.StringForPrinting, 40);

  if (sendCommand(RETURN_BUY, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != RETURN_BUY) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];

  return 0;
}

//-----------------------------------------------------------------------------
int DriverFR::Sale()
{
  TApplication::debug(4, "<Sale>");

  parameter  p;
  answer     a;
  int result = -1;

  p.len   = 55;

  if (connected)
  {
    int64_t quant = llround(fr.Quantity * 1000);
    int64_t price = llround(fr.Price * 100);

    memcpy(p.buff,    &quant, 5);
    memcpy(p.buff+5,  &price, 5);
    p.buff[10] = fr.Department;

    p.buff[11] = fr.Tax1;
    p.buff[12] = fr.Tax2;
    p.buff[13] = fr.Tax3;
    p.buff[14] = fr.Tax4;

    strncpy((char*)p.buff+15, (char*)fr.StringForPrinting, 40);

    if (sendCommand(SALE, fr.Password, &p) >= 0)
    {
        if (readAnswer(&a) >= 0)
        {
            if (a.buff[0] == SALE)
            {
                if (errHand(&a) != 0)
                    result = fr.ResultCode;
                else
                {
                  fr.OperatorNumber = a.buff[2];
                  result = 0;
                }
            }
        }
    }
  }

  TApplication::debug(4, "</Sale>");

  return result;
}

//-----------------------------------------------------------------------------
int DriverFR::ReturnSale()
{
  TApplication::debug(4, "<ReturnSale>");
  parameter  p;
  answer     a;
  int result = -1;

  p.len   = 55;

  if (connected)
  {

    int64_t quant = llround(fr.Quantity * 1000);
    int64_t price = llround(fr.Price * 100);

    memcpy(p.buff,    &quant, 5);
    memcpy(p.buff+5,  &price, 5);
    p.buff[10] = fr.Department;

    p.buff[11] = fr.Tax1;
    p.buff[12] = fr.Tax2;
    p.buff[13] = fr.Tax3;
    p.buff[14] = fr.Tax4;

    strncpy((char*)p.buff+15, (char*)fr.StringForPrinting, 40);

    if (sendCommand(RETURN_SALE, fr.Password, &p) >= 0)
    {
        if (readAnswer(&a) >= 0)
        {
            if (a.buff[0] == RETURN_SALE)
            {
                if (errHand(&a) != 0)
                    result = fr.ResultCode;
                else
                {
                    fr.OperatorNumber = a.buff[2];
                    result = 0;
                }
            }
        }
    }
  }
  TApplication::debug(4, "</ReturnSale>");
  return result;
}

//-----------------------------------------------------------------------------
int DriverFR::CancelCheck()
{
  TApplication::debug(4, "<CancelCheck>");
  parameter  p;
  answer     a;
  int result = -1;

  if (connected)
  {
        if (sendCommand(CANCEL_CHECK, fr.Password, &p) >= 0)
        {
            if (readAnswer(&a) >= 0)
            {
                if (a.buff[0] == CANCEL_CHECK)
                {
                    if (errHand(&a) != 0)
                        result = fr.ResultCode;
                    else
                    {
                        fr.OperatorNumber = a.buff[2];
                        result = 0;
                    }
                }
            }
        }
    }
  TApplication::debug(4, "</CancelCheck>");
  return result;
}


//-----------------------------------------------------------------------------
int DriverFR::GetEKLZJournal()
{
  TApplication::debug(4, "<GetEKLZJournal>");
  parameter  p;
  answer     a;
  int result = -1;

  if (connected)
  {
        memcpy(&p.buff, &fr.SessionNumber, 2);
        if (sendCommand(GET_EKLZ_JOURNAL, fr.Password, &p) >= 0)
        {
            if (readAnswer(&a) >= 0)
            {
                if (a.buff[0] == GET_EKLZ_JOURNAL)
                {
                    if (errHand(&a) != 0)
                        result = fr.ResultCode;
                    else
                    {
                        QByteArray data;
                        data.append((char*)&a.buff+2);
                        fr.UDescription = codec->toUnicode(data);
                        result = 0;
                    }
                }
            }
        }
    }
  TApplication::debug(4, "</GetEKLZJournal>");
  return result;
}


//-----------------------------------------------------------------------------
int DriverFR::GetEKLZData()
{
  TApplication::debug(4, "<GetEKLZData>");
  parameter  p;
  answer     a;
  int result = -1;

  if (connected)
  {
        if (sendCommand(GET_EKLZ_DATA, fr.Password, &p) >= 0)
        {
            if (readAnswer(&a) >= 0)
            {
                if (a.buff[0] == GET_EKLZ_DATA)
                {
                    if (errHand(&a) != 0)
                        result = fr.ResultCode;
                    else
                    {
                        QByteArray data;
                        data.append((char*)&a.buff+2);
                        fr.EKLZData = codec->toUnicode(data);
                        result = 0;
                    }
                }
            }
        }
    }
  TApplication::debug(4, "</GetEKLZData>");
  return result;
}


//-----------------------------------------------------------------------------
int DriverFR::CashIncome()
{
  parameter  p;
  answer     a;
  p.len    = 5;

  if (!connected) return -1;

  int64_t  sum = llround(fr.Summ1 * 100);

  memcpy(p.buff, &sum, 5);

  if (sendCommand(CASH_INCOME, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != CASH_INCOME) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];
  fr.OpenDocumentNumber = evalint((unsigned char*)&a.buff+3, 2);

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::CashOutcome()
{
  parameter  p;
  answer     a;
  p.len    = 5;

  if (!connected) return -1;

  int64_t  sum = llround(fr.Summ1 * 100);

  memcpy(p.buff, &sum, 5);

  if (sendCommand(CASH_OUTCOME, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != CASH_OUTCOME) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];
  fr.OpenDocumentNumber = evalint((unsigned char*)&a.buff+3, 2);

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::Charge()
{
  parameter  p;
  answer     a;
  p.len   = 49;

  if (!connected) return -1;

  int64_t  sum = llround(fr.Summ1 * 100);

  memcpy(p.buff, &sum, 5);

  p.buff[5] = fr.Tax1;
  p.buff[6] = fr.Tax2;
  p.buff[7] = fr.Tax3;
  p.buff[8] = fr.Tax4;

  strncpy((char*)p.buff+9, (char*)fr.StringForPrinting, 40);

  if (sendCommand(CHARGE, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != CHARGE) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::StornoCharge()
{
  parameter  p;
  answer     a;
  p.len   = 49;

  if (!connected) return -1;

  int64_t  sum = llround(fr.Summ1 * 100);

  memcpy(p.buff, &sum, 5);

  p.buff[5] = fr.Tax1;
  p.buff[6] = fr.Tax2;
  p.buff[7] = fr.Tax3;
  p.buff[8] = fr.Tax4;

  strncpy((char*)p.buff+9, (char*)fr.StringForPrinting, 40);

  if (sendCommand(STORNO_CHARGE, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != STORNO_CHARGE) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::Discount()
{
  parameter  p;
  answer     a;
  p.len   = 49;

  if (!connected) return -1;

  int64_t  sum = llround(fr.Summ1 * 100);

  memcpy(p.buff, &sum, 5);

  p.buff[5] = fr.Tax1;
  p.buff[6] = fr.Tax2;
  p.buff[7] = fr.Tax3;
  p.buff[8] = fr.Tax4;

  strncpy((char*)p.buff+9, (char*)fr.StringForPrinting, 40);

  if (sendCommand(DISCOUNT, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != DISCOUNT) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::StornoDiscount()
{
  parameter  p;
  answer     a;
  p.len   = 49;

  if (!connected) return -1;

  int64_t sum = llround(fr.Summ1 * 100);

  memcpy(p.buff, &sum, 5);

  p.buff[5] = fr.Tax1;
  p.buff[6] = fr.Tax2;
  p.buff[7] = fr.Tax3;
  p.buff[8] = fr.Tax4;

  strncpy((char*)p.buff+9, (char*)fr.StringForPrinting, 40);

  if (sendCommand(STORNO_DISCOUNT, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != STORNO_DISCOUNT) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::CheckSubTotal()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  if (sendCommand(CHECK_SUBTOTAL, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != CHECK_SUBTOTAL) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];
  fr.Summ1 = evalint64((unsigned char*)&a.buff+3, 5);
  fr.Summ1 /= 100;

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::CloseCheck()
{

  TApplication::debug(4, "<CloseCheck>");

  parameter  p;
  answer     a;
  int result = -1;

  if (connected)
  {
    int64_t  sum;
    p.len   = 67;

    sum = llround(fr.Summ1 * 100);
    memcpy(p.buff,    &sum, 5);			// 0-4
    sum = llround(fr.Summ2 * 100);
    memcpy(p.buff+ 5, &sum, 5);			// 5-9
    sum = llround(fr.Summ3 * 100);
    memcpy(p.buff+10, &sum, 5);			//10-14
    sum = llround(fr.Summ4 * 100);
    memcpy(p.buff+15, &sum, 5);			//15-19

    sum = llround(fr.DiscountOnCheck * 100);
    memcpy(p.buff+20, &sum, 3);			//20-22

    p.buff[23] = fr.Tax1;				//23
    p.buff[24] = fr.Tax2;				//24
    p.buff[25] = fr.Tax3;				//25
    p.buff[26] = fr.Tax4;				//26

    strncpy((char*)p.buff+27, (char*)fr.StringForPrinting, 40);
    if (sendCommand(CLOSE_CHECK, fr.Password, &p) >= 0)
    {
        if (readAnswer(&a) >= 0)
        {
            if (a.buff[0] == CLOSE_CHECK)
            {
                if (errHand(&a) != 0)
                    result = fr.ResultCode;
                else
                {
                    fr.OperatorNumber = a.buff[2];
                    fr.Change = evalint64((unsigned char*)&a.buff+3, 5);
                    fr.Change /= 100;
                    result = 0;
                }
            }
        }
    }
  }

  TApplication::debug(4, "</CloseCheck>");
  return result;
}
//-----------------------------------------------------------------------------
int DriverFR::Storno()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  int64_t quant = llround(fr.Quantity * 1000);
  int64_t price = llround(fr.Price * 100);
  p.len   = 55;

  memcpy(p.buff,    &quant, 5);
  memcpy(p.buff+5,  &price, 5);
  p.buff[10] = fr.Department;

  p.buff[11] = fr.Tax1;
  p.buff[12] = fr.Tax2;
  p.buff[13] = fr.Tax3;
  p.buff[14] = fr.Tax4;

  strncpy((char*)p.buff+15, (char*)fr.StringForPrinting, 40);

  if (sendCommand(STORNO, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != STORNO) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::PrintReportWithCleaning()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  if (sendCommand(PRINT_REPORT_WITH_CLEANING, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != PRINT_REPORT_WITH_CLEANING) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];
  fr.SessionNumber = evalint((unsigned char*)&a.buff+3, 2);

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::PrintReportWithoutCleaning()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  if (sendCommand(PRINT_REPORT_WITHOUT_CLEANING, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != PRINT_REPORT_WITHOUT_CLEANING) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];
  fr.SessionNumber = evalint((unsigned char*)&a.buff+3, 2);

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::PrintOperationReg()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  if (sendCommand(PRINT_OPERATION_REG, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != PRINT_OPERATION_REG) return -1;

  return errHand(&a);
}
//-----------------------------------------------------------------------------
int DriverFR::DampRequest()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  p.len    = 1;

  p.buff[0] = fr.DeviceCode;

  if (sendCommand(DUMP_REQUEST, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != DUMP_REQUEST) return -1;

  if (errHand(&a) != 0) return -1;

  return a.buff[2];  			//number of data blocks to return
}
//-----------------------------------------------------------------------------
int DriverFR::GetData()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  if (sendCommand(GET_DATA, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != GET_DATA) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.DeviceCode = a.buff[2];
  fr.DeviceCodeDescription = (char*)devcodedesc[fr.DeviceCode];
  fr.DataBlockNumber = evalint((unsigned char*)&a.buff+3, 2);
  memcpy(fr.DataBlock, a.buff+5, 32);

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::InterruptDataStream()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  if (sendCommand(INTERRUPT_DATA_STREAM, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != INTERRUPT_DATA_STREAM) return -1;

  return errHand(&a);
}
//-----------------------------------------------------------------------------
int DriverFR::GetCashReg()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  p.len    = 1;

  p.buff[0] = fr.RegisterNumber;

  if (sendCommand(GET_CASH_REG, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != GET_CASH_REG) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];
  fr.ContentsOfCashRegister = evalint64((unsigned char*)&a.buff+3, 6);
  fr.ContentsOfCashRegister /= 100;

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::GetOperationReg()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  p.len    = 1;

  p.buff[0] = fr.RegisterNumber;

  if (sendCommand(GET_OPERATION_REG, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != GET_OPERATION_REG) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];
  fr.ContentsOfOperationRegister = evalint((unsigned char*)&a.buff+3, 2);

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::SetSerialNumber()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  p.len    = 4;
  int num = atol(fr.SerialNumber);

  memcpy(p.buff, &num, sizeof(int));

  if (sendCommand(SET_SERIAL_NUMBER, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != SET_SERIAL_NUMBER) return -1;

  return errHand(&a);
}
//-----------------------------------------------------------------------------
int DriverFR::SetPointPosition()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  p.len    = 1;

  p.buff[0] = fr.PointPosition;

  if (sendCommand(SET_POINT_POSITION, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != SET_POINT_POSITION) return -1;

  return errHand(&a);
}
//-----------------------------------------------------------------------------
int DriverFR::SetTime()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  p.len    = 3;

  p.buff[2] = fr.Time.tm_sec;
  p.buff[1] = fr.Time.tm_min;
  p.buff[0] = fr.Time.tm_hour;

  if (sendCommand(SET_TIME, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != SET_TIME) return -1;

  return errHand(&a);
}
//-----------------------------------------------------------------------------
int DriverFR::SetDate()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  p.len    = 3;

  p.buff[0] = fr.Date.tm_mday;
  p.buff[1] = fr.Date.tm_mon + 1;
  p.buff[2] = fr.Date.tm_year - 100;

  if (sendCommand(SET_DATE, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != SET_DATE) return -1;

  return errHand(&a);
}
//-----------------------------------------------------------------------------
int DriverFR::ConfirmDate()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  p.len    = 3;

  p.buff[0] = fr.Date.tm_mday;
  p.buff[1] = fr.Date.tm_mon + 1;
  p.buff[2] = fr.Date.tm_year - 100;

  if (sendCommand(CONFIRM_DATE, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != CONFIRM_DATE) return -1;

  return errHand(&a);
}
//-----------------------------------------------------------------------------
int DriverFR::InitTable()
{
  parameter  p;

  if (!connected) return -1;

  if (sendCommand(INIT_TABLE, fr.Password, &p) < 0) return -1;
  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::WriteTable()
{
  parameter  p;
  answer     a;
  int      len;
  char    *tmp;

  if (!connected) return -1;

  GetFieldStruct();
  if (fr.FieldType == 1)
  {
    len = strlen(fr.ValueOfFieldString);
    tmp = fr.ValueOfFieldString;
  }
  else
  {
    len = fr.FieldSize;
    tmp = (char*)fr.ValueOfFieldInteger;
  }
  p.len = 4 + len;

  p.buff[0] = fr.TableNumber;
  memcpy(p.buff+1, &fr.FieldNumber, 2);
  p.buff[3] = fr.RowNumber;
  memcpy(p.buff+4, &tmp, len);

  if (sendCommand(WRITE_TABLE, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != WRITE_TABLE) return -1;

  return errHand(&a);
}
//-----------------------------------------------------------------------------
int DriverFR::ReadTable()
{
  parameter  p;
  answer     a;
  int      len;

  if (!connected) return -1;

  p.len    = 4;

  p.buff[0] = fr.TableNumber;
  memcpy(p.buff+1, &fr.FieldNumber, 2);
  p.buff[3] = fr.RowNumber;

  if (sendCommand(READ_TABLE, fr.Password, &p) < 0) return -1;
  if ((len = errHand(&a)) < 0) return -1;
  if (a.buff[0] != READ_TABLE) return -1;

  GetFieldStruct();

  if (fr.FieldType == 1) strncpy(fr.ValueOfFieldString, (char*)a.buff, len - 2);
  else fr.ValueOfFieldInteger = evalint64((unsigned char*)&a.buff+2, fr.FieldSize);

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::GetFieldStruct()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  p.len    = 2;

  p.buff[0] = fr.TableNumber;
  p.buff[1] = fr.FieldNumber;

  if (sendCommand(GET_FIELD_STRUCT, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != GET_FIELD_STRUCT) return -1;

  strncpy(fr.FieldName, (char*)&a.buff+1, 40);
  fr.FieldType = a.buff[41];
  fr.FieldSize = a.buff[42];
  fr.MINValueOfField = evalint64((unsigned char*)&a.buff+43, fr.FieldSize);
  fr.MAXValueOfField = evalint64((unsigned char*)&a.buff+43 + fr.FieldSize, fr.FieldSize);

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::GetTableStruct()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  p.len    = 1;

  p.buff[0] = fr.TableNumber;

  if (sendCommand(GET_TABLE_STRUCT, fr.Password, &p) < 0) return -1;
  if ((errHand(&a)) < 0) return -1;
  if (a.buff[0] != GET_TABLE_STRUCT) return -1;

  strncpy(fr.TableName, (char*)&a.buff+1, 40);
  fr.RowNumber   = evalint((unsigned char*)&a.buff+41, 2);;
  fr.FieldNumber = a.buff[43];

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::WriteLicense()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  int64_t num = atoll(fr.License);
  p.len    = 5;

  memcpy(p.buff, &num, 5);

  if (sendCommand(WRITE_LICENSE, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != WRITE_LICENSE) return -1;

  return errHand(&a);
}
//-----------------------------------------------------------------------------
int DriverFR::ReadLicense()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  if (sendCommand(READ_LICENSE, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != READ_LICENSE) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  sprintf(fr.License, "%.0lg", (double)evalint64((unsigned char*)&a.buff+2, 5));

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::InitFM()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  if (sendCommand(INIT_FM, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != INIT_FM) return -1;

  return errHand(&a);
}
//-----------------------------------------------------------------------------
int DriverFR::Fiscalization()
{
  parameter  p;
  answer 	   a;

  if (!connected) return -1;

  int     nti = fr.NewPasswordTI;
  int64_t rnm = atoll(fr.RNM);
  int64_t inn = atoll(fr.INN);
  p.len   = 14;

  memcpy(p.buff,   &nti, 4);
  memcpy(p.buff+4, &rnm, 5);
  memcpy(p.buff+9, &inn, 6);

  if (sendCommand(FISCALIZATION, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != FISCALIZATION) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.RegistrationNumber = evalint((unsigned char*)&a.buff+2, 1);
  fr.FreeRegistration   = evalint((unsigned char*)&a.buff+3, 1);
  fr.SessionNumber      = evalint((unsigned char*)&a.buff+4, 2);
  evaldate((unsigned char*)&a.buff+6, &fr.Date);

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::FiscalReportForDatesRange()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  p.len    = 7;

  p.buff[0] = fr.ReportType;

  p.buff[1] = fr.FirstSessionDate.tm_year - 100;
  p.buff[2] = fr.FirstSessionDate.tm_mon  + 1;
  p.buff[3] = fr.FirstSessionDate.tm_mday;

  p.buff[4] = fr.LastSessionDate.tm_year - 100;
  p.buff[5] = fr.LastSessionDate.tm_mon  + 1;
  p.buff[6] = fr.LastSessionDate.tm_mday;

  if (sendCommand(FISCAL_REPORT_FOR_DATES_RANGE, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != FISCAL_REPORT_FOR_DATES_RANGE) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  evaldate((unsigned char*)&a.buff+2, &fr.FirstSessionDate);
  evaldate((unsigned char*)&a.buff+5, &fr.LastSessionDate);
  fr.FirstSessionNumber = evalint((unsigned char*)&a.buff+8, 2);
  fr.LastSessionNumber  = evalint((unsigned char*)&a.buff+10, 2);

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::FiscalReportForSessionRange()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  p.len    = 5;

  p.buff[0] = fr.ReportType;

  memcpy(p.buff+1, &fr.FirstSessionNumber, 2);
  memcpy(p.buff+3, &fr.LastSessionNumber, 2);

  if (sendCommand(FISCAL_REPORT_FOR_SESSION_RANGE, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != FISCAL_REPORT_FOR_SESSION_RANGE) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  evaldate((unsigned char*)&a.buff+2, &fr.FirstSessionDate);
  evaldate((unsigned char*)&a.buff+5, &fr.LastSessionDate);
  fr.FirstSessionNumber = evalint((unsigned char*)&a.buff+8, 2);
  fr.LastSessionNumber  = evalint((unsigned char*)&a.buff+10, 2);

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::InterruptFullReport()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  if (sendCommand(INTERRUPT_FULL_REPORT, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != INTERRUPT_FULL_REPORT) return -1;

  return errHand(&a);
}
//-----------------------------------------------------------------------------
int DriverFR::GetFiscalizationParameters()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  p.len    = 1;

  p.buff[0] = fr.RegistrationNumber;

  if (sendCommand(GET_FISCALIZATION_PARAMETERS, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != GET_FISCALIZATION_PARAMETERS) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.NewPasswordTI = evalint((unsigned char*)&a.buff+2, 4);
  sprintf(fr.RNM, "%.0lg", (double)evalint64((unsigned char*)&a.buff+6,  5));
  sprintf(fr.INN, "%.0lg", (double)evalint64((unsigned char*)&a.buff+11, 6));
  fr.SessionNumber = evalint((unsigned char*)&a.buff+17, 2);
  evaldate((unsigned char*)&a.buff+19, &fr.Date);

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::GetFMRecordsSum()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  p.len    = 1;

  p.buff[0] = fr.TypeOfSumOfEntriesFM;

  if (sendCommand(GET_FM_RECORDS_SUM, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != GET_FM_RECORDS_SUM) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];
  fr.Summ1 = evalint64((unsigned char*)&a.buff+3,  8);
  fr.Summ1 /= 100;
  fr.Summ2 = evalint64((unsigned char*)&a.buff+11, 6);
  fr.Summ2 /= 100;
  fr.Summ3 = evalint64((unsigned char*)&a.buff+17, 6);
  fr.Summ3 /= 100;
  fr.Summ4 = evalint64((unsigned char*)&a.buff+23, 6);
  fr.Summ4 /= 100;

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::GetLastFMRecordDate()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  if (sendCommand(GET_LAST_FM_RECORD_DATE, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != GET_LAST_FM_RECORD_DATE) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber   = a.buff[2];
  fr.LastFMRecordType = a.buff[3];
  evaldate((unsigned char*)&a.buff+4, &fr.Date);

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::GetRangeDatesAndSessions()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  if (sendCommand(GET_RANGE_DATES_AND_SESSIONS, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != GET_RANGE_DATES_AND_SESSIONS) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  evaldate((unsigned char*)&a.buff+2, &fr.FirstSessionDate);
  evaldate((unsigned char*)&a.buff+5, &fr.LastSessionDate);
  fr.FirstSessionNumber = evalint((unsigned char*)&a.buff+8,  2);
  fr.LastSessionNumber  = evalint((unsigned char*)&a.buff+10, 2);

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::EKLZDepartmentReportInDatesRange(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::EKLZDepartmentReportInSessionsRange(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::EKLZJournalOnSessionNumber(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::EKLZSessionReportInDatesRange(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::EKLZSessionReportInSessionRange(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::ReadEKLZDocumentOnKPK(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::ReadEKLZSessionTotal(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::StopEKLZDocumentPrinting(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::Correction(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::DozeOilCheck(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::SummOilCheck(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::SetDozeInMilliliters(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::SetDozeInMoney(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::OilSale(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::GetLiterSumCounter(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::GetRKStatus(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::LaunchRK(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::StopRK(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::ResetRK(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::ResetAllTRK(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::SetRKParameters(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::EjectSlipDocument(){return 0;}
//-----------------------------------------------------------------------------
int DriverFR::LoadLineData()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  p.len    = 41;

  p.buff[0]  = fr.LineNumber;
  memcpy(p.buff + 1, fr.LineData, 40);

  if (sendCommand(LOAD_LINE_DATA, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != LOAD_LINE_DATA) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::Draw()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  p.len    = 2;

  p.buff[0]  = fr.FirstLineNumber;
  p.buff[1]  = fr.LastLineNumber;

  if (sendCommand(DRAW, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != DRAW) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];

  return 0;
}
//-----------------------------------------------------------------------------
int DriverFR::PrintBarCode()
{
  parameter  p;
  answer     a;

  if (!connected) return -1;

  int64_t barcode = atoll(fr.BarCode);
  p.len    = 5;

  memcpy(p.buff, &barcode, 5);

  if (sendCommand(PRINT_BARCODE, fr.Password, &p) < 0) return -1;
  if (readAnswer(&a) < 0) return -1;
  if (a.buff[0] != PRINT_BARCODE) return -1;

  if (errHand(&a) != 0) return fr.ResultCode;

  fr.OperatorNumber = a.buff[2];

  return 0;
}
//-----------------------------------------------------------------------------
