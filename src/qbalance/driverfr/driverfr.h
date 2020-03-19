/***************************************************************************
                          drvfr.h  -  description
                             -------------------
    begin                : Sun Jan 20 2002
    copyright            : (C) 2002 by Igor V. Youdytsky
    email                : Pitcher@gw.tander.ru
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/************************************************************************************************************
Copyright (C) Morozov Vladimir Aleksandrovich
MorozovVladimir@mail.ru

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*************************************************************************************************************/


#ifndef DRIVERFR_H
#define DRIVERFR_H

#include <QtCore/QObject>
#include <QtCore/QMetaObject>
#include <QtCore/QMetaProperty>
#include <QtCore/QDate>
#include <QtCore/QTime>
#include <QtCore/QDebug>
#include <sys/time.h>
#include <stdint.h>
#include "../serialport/qmyextserialport.h"
#include "../gui/myprogressdialog.h"

class TApplication;

#define MAX_TRIES	3

#define ENQ 			0x05
#define STX 			0x02
#define ACK 			0x06
#define NAK 			0x15


#define DUMP_REQUEST			0x01
#define GET_DATA			0x02
#define INTERRUPT_DATA_STREAM		0x03
#define GET_SHORT_ECR_STATUS	0x10
#define GET_ECR_STATUS			0x11
#define PRINT_WIDE_STRING		0x12
#define BEEP				0x13
#define SET_EXCHANGE_PARAM		0x14
#define GET_EXCHANGE_PARAM		0x15
#define RESET_SETTINGS			0x16
#define PRINT_STRING			0x17
#define PRINT_DOCUMENT_TITLE		0x18
#define TEST				0x19
#define GET_CASH_REG			0x1a
#define GET_OPERATION_REG		0x1b
#define WRITE_LICENSE			0x1c
#define READ_LICENSE			0x1d
#define WRITE_TABLE			0x1e
#define READ_TABLE			0x1f
#define SET_POINT_POSITION		0x20
#define SET_TIME			0x21
#define SET_DATE			0x22
#define CONFIRM_DATE			0x23
#define INIT_TABLE			0x24
#define CUT_CHECK			0x25
#define RESET_SUMMARY			0x27
#define OPEN_DRAWER			0x28
#define FEED_DOCUMENT			0x29
#define EJECT_SLIP_DOC			0x2a
#define INTERRUPT_TEST			0x2b
#define PRINT_OPERATION_REG		0x2c
#define GET_TABLE_STRUCT		0x2d
#define GET_FIELD_STRUCT		0x2e
#define PRINT_REPORT_WITHOUT_CLEANING	0x40
#define PRINT_REPORT_WITH_CLEANING	0x41
#define CASH_INCOME			0x50
#define CASH_OUTCOME			0x51
#define SET_SERIAL_NUMBER		0x60
#define INIT_FM				0x61
#define GET_FM_RECORDS_SUM		0x62
#define GET_LAST_FM_RECORD_DATE		0x63
#define GET_RANGE_DATES_AND_SESSIONS	0x64
#define FISCALIZATION			0x65
#define FISCAL_REPORT_FOR_DATES_RANGE	0x66
#define FISCAL_REPORT_FOR_SESSION_RANGE	0x67
#define INTERRUPT_FULL_REPORT		0x68
#define GET_FISCALIZATION_PARAMETERS	0x69
#define FISCAL_PRINT_SLIP_DOC		0x70
#define PRINT_SLIP_DOC			0x71
#define SALE				0x80
#define BUY				0x81
#define RETURN_SALE			0x82
#define RETURN_BUY			0x83
#define STORNO				0x84
#define CLOSE_CHECK			0x85
#define DISCOUNT			0x86
#define CHARGE				0x87
#define CANCEL_CHECK			0x88
#define CHECK_SUBTOTAL			0x89
#define STORNO_DISCOUNT			0x8a
#define STORNO_CHARGE			0x8b
#define DOZE_OIL_CHECK			0x90
#define SUMM_OIL_CHECK			0x91
#define CORRECTION			0x92
#define SET_DOZE_IN_MILLILITERS		0x93
#define SET_DOZE_IN_MONEY		0x94
#define OIL_SALE			0x95
#define STOP_RK				0x96
#define LAUNCH_RK			0x97
#define RESET_RK			0x98
#define RESET_ALL_TRK			0x99
#define SET_RK_PARAMETERS		0x9a
#define GET_LITER_SUM_COUNTER		0x9b
#define GET_CURRENT_DOZE		0x9e
#define GET_RK_STATUS			0x9f
#define ECT_DEP_DATE_REP		0xa0
#define ECT_DEP_SHIFT_REP		0xa1
#define ECT_SHIFT_DATE_REP		0xa2
#define ECT_SHIFT_SHIFT_REP		0xa3
#define ECT_SHIFT_TOTAL			0xa4
#define ECT_PAY_DOC_BY_NUMBER		0xa5
#define ECT_BY_SHIFT_NUMBER		0xa6
#define ECT_REPORT_INTR			0xa7
#define EKLZ_INTERRUPT      	0xac
#define GET_EKLZ_CODE1_REPORT	0xad
#define CONTINUE_PRINTING		0xb0
#define GET_EKLZ_DATA           0xb3
#define GET_EKLZ_JOURNAL        0xb4
#define LOAD_LINE_DATA			0xc0
#define DRAW				0xc1
#define PRINT_BARCODE			0xc2
#define GET_DEVICE_METRICS		0xfc
#define CTRL_ADD_DEVICE			0xfd
#define OPEN_SESSION			0xe0


typedef struct
{
  int len;
  unsigned char buff[260];
} command;


typedef struct
{
  int len;
  unsigned char buff[260];
} answer;


typedef struct
{
    int len;
    unsigned char buff[260];
} parameter;


typedef struct
{
    int error;
    int recomendation;
} recomendations;


class frProp : public QObject
{
    Q_OBJECT
public:

    int    BatteryCondition;
    int    BaudRate;
    char   BarCode[14];
    double Change;
    int    CheckIsClosed;
    int    CheckIsMadeOut;
    double ContentsOfCashRegister;
    int    ContentsOfOperationRegister;
    int    CurrentDozeInMilliliters;
    double CurrentDozeInMoney;
    int    CutType;
    unsigned char DataBlock[32];
    int    DataBlockNumber;
    struct tm Date;
    int    Department;
    int    DeviceCode;
    char*  DeviceCodeDescription;
    double DiscountOnCheck;
    char   DocumentName[31];
    int    DocumentNumber;
    int    OpenDocumentNumber;
    int    DozeInMilliliters;
    double DozeInMoney;
    int    DrawerNumber;
    int    ECRAdvancedMode;
    char*  ECRAdvancedModeDescription;
    int    ECRBuild;
    int    ECRMode;
    int    ECRMode8Status;
    char*  ECRModeDescription;
    struct tm ECRSoftDate;
    char   ECRSoftVersion[4];
    QString   EKLZData;
    int    EKLZIsPresent;
    QString EKLZNumber;
    char   EKLZFlags;
    int    EmergencyStopCode;
    char*  EmergencyStopCodeDescription;
    char   FieldName[41];
    int    FieldNumber;
    int    FieldSize;
    int    FieldType;
    int    FirstLineNumber;
    struct tm FirstSessionDate;
    int    FirstSessionNumber;
    int    FM1IsPresent;
    int    FM2IsPresent;
    int    FMBuild;
    int    FMOverflow;
    struct tm FMSoftDate;
    char   FMSoftVersion[4];
    int    FreeRecordInFM;
    int    FreeRegistration;
    char   INN[13];
    int    JournalRibbonIsPresent;
    int    JournalRibbonOpticalSensor;
    int    JournalRibbonLever;
    int    KPKNumber;
    unsigned long int    LastKPKNumber;
    double  LastKPKDocumentResult;
    QDate LastKPKDate;
    QTime LastKPKTime;
    int    LastFMRecordType;
    int    LastLineNumber;
    struct tm LastSessionDate;
    int    LastSessionNumber;
    char   License[13];
    int    LicenseIsPresent;
    int    LidPositionSensor;
    int    LogicalNumber;
    int    LineNumber;
    unsigned char LineData[41];
    int    MAXValueOfField;
    int    MINValueOfField;
    int    Motor;
    char*  NameCashReg;
    char*  NameOperationReg;
    int    NewPasswordTI;
    int    OperatorNumber;
    int    Password;
    int    Pistol;
    int    PointPosition;
    int    PortNumber;
    double Price;
    double Quantity;
    int    QuantityOfOperations;
    int    ReceiptRibbonIsPresent;
    int    ReceiptRibbonOpticalSensor;
    int    ReceiptRibbonLever;
    int    Timeout;
    int    RegisterNumber;
    int    ReportType;
    int    RegistrationNumber;
    int    ResultCode;
    char*  ResultCodeDescription;
    int    RKNumber;
    char   RNM[15];
    int    RoughValve;
    int    RowNumber;
    int    RunningPeriod;
    char   SerialNumber[13];
    int    SessionNumber;
    int    SlipDocumentIsMoving;
    int    SlipDocumentIsPresent;
    int    SlowingInMilliliters;
    int    SlowingValve;
    int    StatusRK;
    char*  StatusRKDescription;
    char   StringForPrinting[250];
    int    StringQuantity;
    double Summ1;
    double Summ2;
    double Summ3;
    double Summ4;
    char*  TableName;
    int    TableNumber;
    int    Tax1;
    int    Tax2;
    int    Tax3;
    int    Tax4;
    struct tm Time;
    int    TRKNumber;
    int    TypeOfSumOfEntriesFM;
    int    UseJournalRibbon;
    int    UseReceiptRibbon;
    int    UseSlipDocument;
    int    UModel;
    int    UMajorType;
    int    UMinorType;
    int    UMajorProtocolVersion;
    int    UMinorProtocolVersion;
    int    UCodePage;
    QString   UDescription;
    int    ValueOfFieldInteger;
    char   ValueOfFieldString[41];

    Q_PROPERTY(int    BatteryCondition READ getBatteryCondition)
    Q_PROPERTY(int    BaudRate READ getBaudRate WRITE setBaudRate)
    Q_PROPERTY(QString  BarCode READ getBarCode WRITE setBarCode)
    Q_PROPERTY(double Change READ getChange)
    Q_PROPERTY(int    CheckIsClosed READ getCheckIsClosed WRITE setCheckIsClosed)
    Q_PROPERTY(int    CheckIsMadeOut READ getCheckIsMadeOut WRITE setCheckIsMadeOut)
    Q_PROPERTY(double ContentsOfCashRegister READ getContentsOfCashRegister)
    Q_PROPERTY(int    ContentsOfOperationRegister READ getContentsOfOperationRegister)
    Q_PROPERTY(int    CurrentDozeInMilliliters READ getCurrentDozeInMilliliters WRITE setCurrentDozeInMilliliters)
    Q_PROPERTY(double CurrentDozeInMoney READ getCurrentDozeInMoney WRITE setCurrentDozeInMoney)
    Q_PROPERTY(int    CutType READ getCutType WRITE setCutType)
    Q_PROPERTY(unsigned char* DataBlock READ getDataBlock)
    Q_PROPERTY(int    DataBlockNumber READ getDataBlockNumber)
    Q_PROPERTY(struct tm Date READ getDate WRITE setDate)
    Q_PROPERTY(int    Department READ getDepartment WRITE setDepartment)
    Q_PROPERTY(int    DeviceCode READ getDeviceCode WRITE setDeviceCode)
    Q_PROPERTY(QString  DeviceCodeDescription READ getDeviceCodeDescription)
    Q_PROPERTY(double DiscountOnCheck READ getDiscountOnCheck WRITE setDiscountOnCheck)
    Q_PROPERTY(QString  DocumentName READ getDocumentName WRITE setDocumentName)
    Q_PROPERTY(int    DocumentNumber READ getDocumentNumber WRITE setDocumentNumber)
    Q_PROPERTY(int    OpenDocumentNumber READ getOpenDocumentNumber WRITE setOpenDocumentNumber)
    Q_PROPERTY(int    DozeInMilliliters READ getDozeInMilliliters WRITE setDozeInMilliliters)
    Q_PROPERTY(double DozeInMoney READ getDozeInMoney WRITE setDozeInMoney)
    Q_PROPERTY(int    DrawerNumber READ getDrawerNumber WRITE setDrawerNumber)
    Q_PROPERTY(int    ECRAdvancedMode READ getECRAdvancedMode)
    Q_PROPERTY(QString  ECRAdvancedModeDescription READ getECRAdvancedModeDescription)
    Q_PROPERTY(int    ECRBuild READ getECRBuild)
    Q_PROPERTY(int    ECRMode READ getECRMode)
    Q_PROPERTY(int    ECRMode8Status READ getECRMode8Status)
    Q_PROPERTY(QString  ECRModeDescription READ getECRModeDescription)
    Q_PROPERTY(struct tm ECRSoftDate READ getECRSoftDate)
    Q_PROPERTY(QString  ECRSoftVersion READ getECRSoftVersion)
    Q_PROPERTY(QString  EKLZData READ getEKLZData)
    Q_PROPERTY(int    EKLZIsPresent READ getEKLZIsPresent WRITE setEKLZIsPresent)
    Q_PROPERTY(QString  EKLZNumber READ getEKLZNumber)
    Q_PROPERTY(char  EKLZFlags READ getEKLZFlags)
    Q_PROPERTY(int    EmergencyStopCode READ getEmergencyStopCode)
    Q_PROPERTY(QString  EmergencyStopCodeDescription READ getEmergencyStopCodeDescription)
    Q_PROPERTY(QString  FieldName READ getFieldName)
    Q_PROPERTY(int    FieldNumber READ getFieldNumber WRITE setFieldNumber)
    Q_PROPERTY(int    FieldSize READ getFieldSize)
    Q_PROPERTY(int    FieldType READ getFieldType)
    Q_PROPERTY(int    FirstLineNumber READ getFirstLineNumber WRITE setFirstLineNumber)
    Q_PROPERTY(struct tm FirstSessionDate READ getFirstSessionDate WRITE setFirstSessionDate)
    Q_PROPERTY(int    FirstSessionNumber READ getFirstSessionNumber WRITE setFirstSessionNumber)
    Q_PROPERTY(int    FM1IsPresent READ getFM1IsPresent)
    Q_PROPERTY(int    FM2IsPresent READ getFM2IsPresent)
    Q_PROPERTY(int    FMBuild READ getFMBuild)
    Q_PROPERTY(int    FMOverflow READ getFMOverflow)
    Q_PROPERTY(struct tm FMSoftDate READ getFMSoftDate)
    Q_PROPERTY(QString  FMSoftVersion READ getFMSoftVersion)
    Q_PROPERTY(int    FreeRecordInFM READ getFreeRecordInFM)
    Q_PROPERTY(int    FreeRegistration READ getFreeRegistration)
    Q_PROPERTY(QString  INN READ getINN WRITE setINN)
    Q_PROPERTY(int    JournalRibbonIsPresent READ getJournalRibbonIsPresent WRITE setJournalRibbonIsPresent)
    Q_PROPERTY(int    JournalRibbonOpticalSensor READ getJournalRibbonOpticalSensor WRITE setJournalRibbonOpticalSensor)
    Q_PROPERTY(int    JournalRibbonLever READ getJournalRibbonLever WRITE setJournalRibbonLever)
    Q_PROPERTY(int    KPKNumber READ getKPKNumber)
    Q_PROPERTY(QVariant LastKPKNumber READ getLastKPKNumber)
    Q_PROPERTY(double    LastKPKDocumentResult READ getLastKPKDocumentResult)
    Q_PROPERTY(QDate LastKPKDate READ getLastKPKDate)
    Q_PROPERTY(QTime LastKPKTime READ getLastKPKTime)
    Q_PROPERTY(int    LastFMRecordType READ getLastFMRecordType WRITE setLastFMRecordType)
    Q_PROPERTY(int    LastLineNumber READ getLastLineNumber WRITE setLastLineNumber)
    Q_PROPERTY(struct tm LastSessionDate READ getLastSessionDate WRITE setLastSessionDate)
    Q_PROPERTY(int    LastSessionNumber READ getLastSessionNumber WRITE setLastSessionNumber)
    Q_PROPERTY(QString  License READ getLicense WRITE setLicense)
    Q_PROPERTY(int    LicenseIsPresent READ getLicenseIsPresent)
    Q_PROPERTY(int    LidPositionSensor READ getLidPositionSensor)
    Q_PROPERTY(int    LogicalNumber READ getLogicalNumber WRITE setLogicalNumber)
    Q_PROPERTY(int    LineNumber READ getLineNumber WRITE setLineNumber)
    Q_PROPERTY(unsigned char* LineData READ getLineData WRITE setLineData)
    Q_PROPERTY(int    MAXValueOfField READ getMAXValueOfField)
    Q_PROPERTY(int    MINValueOfField READ getMINValueOfField)
    Q_PROPERTY(int    Motor READ getMotor WRITE setMotor)
    Q_PROPERTY(QString  NameCashReg READ getNameCashReg)
    Q_PROPERTY(QString  NameOperationReg READ getNameOperationReg)
    Q_PROPERTY(int    NewPasswordTI READ getNewPasswordTI WRITE setNewPasswordTI)
    Q_PROPERTY(int    OperatorNumber READ getOperatorNumber)
    Q_PROPERTY(int    Password READ getPassword WRITE setPassword)
    Q_PROPERTY(int    Pistol READ getPistol WRITE setPistol)
    Q_PROPERTY(int    PointPosition READ getPointPosition WRITE setPointPosition)
    Q_PROPERTY(int    PortNumber READ getPortNumber WRITE setPortNumber)
    Q_PROPERTY(double Price READ getPrice WRITE setPrice)
    Q_PROPERTY(double Quantity READ getQuantity WRITE setQuantity)
    Q_PROPERTY(int    ReceiptRibbonIsPresent READ getReceiptRibbonIsPresent)
    Q_PROPERTY(int    ReceiptRibbonOpticalSensor READ getReceiptRibbonOpticalSensor)
    Q_PROPERTY(int    ReceiptRibbonLever READ getReceiptRibbonLever)
    Q_PROPERTY(int    Timeout READ getTimeout WRITE setTimeout)
    Q_PROPERTY(int    RegisterNumber READ getRegisterNumber WRITE setRegisterNumber)
    Q_PROPERTY(int    ReportType READ getReportType WRITE setReportType)
    Q_PROPERTY(int    RegistrationNumber READ getRegistrationNumber WRITE setRegistrationNumber)
    Q_PROPERTY(int    ResultCode READ getResultCode)
    Q_PROPERTY(QString  ResultCodeDescription READ getResultCodeDescription)
    Q_PROPERTY(int    RKNumber READ getRKNumber WRITE setRKNumber)
    Q_PROPERTY(QString  RNM READ getRNM WRITE setRNM)
    Q_PROPERTY(int    RoughValve READ getRoughValve WRITE setRoughValve)
    Q_PROPERTY(int    RowNumber READ getRowNumber WRITE setRowNumber)
    Q_PROPERTY(int    RunningPeriod READ getRunningPeriod WRITE setRunningPeriod)
    Q_PROPERTY(QString  SerialNumber READ getSerialNumber WRITE setSerialNumber)
    Q_PROPERTY(int    SessionNumber READ getSessionNumber WRITE setSessionNumber)
    Q_PROPERTY(int    SlipDocumentIsMoving READ getSlipDocumentIsMoving)
    Q_PROPERTY(int    SlipDocumentIsPresent READ getSlipDocumentIsPresent)
    Q_PROPERTY(int    SlowingInMilliliters READ getSlowingInMilliliters WRITE setSlowingInMilliliters)
    Q_PROPERTY(int    SlowingValve READ getSlowingValve WRITE setSlowingValve)
    Q_PROPERTY(int    StatusRK READ getStatusRK)
    Q_PROPERTY(QString  StatusRKDescription READ getStatusRKDescription)
    Q_PROPERTY(QString StringForPrinting READ getStringForPrinting WRITE setStringForPrinting)
    Q_PROPERTY(int    StringQuantity READ getStringQuantity WRITE setStringQuantity)
    Q_PROPERTY(double Summ1 READ getSumm1 WRITE setSumm1)
    Q_PROPERTY(double Summ2 READ getSumm2 WRITE setSumm2)
    Q_PROPERTY(double Summ3 READ getSumm3 WRITE setSumm3)
    Q_PROPERTY(double Summ4 READ getSumm4 WRITE setSumm4)
    Q_PROPERTY(QString  TableName READ getTableName)
    Q_PROPERTY(int    TableNumber READ getTableNumber WRITE setTableNumber)
    Q_PROPERTY(int    Tax1 READ getTax1 WRITE setTax1)
    Q_PROPERTY(int    Tax2 READ getTax2 WRITE setTax2)
    Q_PROPERTY(int    Tax3 READ getTax3 WRITE setTax3)
    Q_PROPERTY(int    Tax4 READ getTax4 WRITE setTax4)
    Q_PROPERTY(struct tm Time READ getTime WRITE setTime)
    Q_PROPERTY(int    TRKNumber READ getTRKNumber WRITE setTRKNumber)
    Q_PROPERTY(int    TypeOfSumOfEntriesFM READ getTypeOfSumOfEntriesFM WRITE setTypeOfSumOfEntriesFM)
    Q_PROPERTY(int    UseJournalRibbon READ getUseJournalRibbon WRITE setUseJournalRibbon)
    Q_PROPERTY(int    UseReceiptRibbon READ getUseReceiptRibbon WRITE setUseReceiptRibbon)
    Q_PROPERTY(int    UseSlipDocument READ getUseSlipDocument WRITE setUseSlipDocument)
    Q_PROPERTY(int    UModel READ getUModel)
    Q_PROPERTY(int    UMajorType READ getUMajorType)
    Q_PROPERTY(int    UMinorType READ getUMinorType)
    Q_PROPERTY(int    UMajorProtocolVersion READ getUMajorProtocolVersion)
    Q_PROPERTY(int    UMinorProtocolVersion READ getUMinorProtocolVersion)
    Q_PROPERTY(int    UCodePage READ getUCodePage)
    Q_PROPERTY(QString  UDescription READ getUDescription)
    Q_PROPERTY(int    ValueOfFieldInteger READ getValueOfFieldInteger WRITE setValueOfFieldInteger)
    Q_PROPERTY(QString  ValueOfFieldString READ getValueOfFieldString WRITE setValueOfFieldString)


    frProp() { ; }
    ~frProp() { ; }

    int    getBatteryCondition() { return BatteryCondition; }
    int    getBaudRate() { return BaudRate; }
    QString  getBarCode() { return QString().append(BarCode); }
    double getChange() { return Change; }
    int    getCheckIsClosed() { return CheckIsClosed; }
    int    getCheckIsMadeOut() { return CheckIsMadeOut; }
    double getContentsOfCashRegister() { return ContentsOfCashRegister; }
    int    getContentsOfOperationRegister() { return ContentsOfOperationRegister; }
    int    getCurrentDozeInMilliliters() { return CurrentDozeInMilliliters; }
    double getCurrentDozeInMoney() { return CurrentDozeInMoney; }
    int    getCutType() { return CutType; }
    unsigned char* getDataBlock() { return DataBlock; }
    int    getDataBlockNumber() { return DataBlockNumber; }
    struct tm getDate() { return Date; }
    int    getDepartment() { return Department; }
    int    getDeviceCode() { return DeviceCode; }
    QString  getDeviceCodeDescription() { return QString().append(DeviceCodeDescription); }
    double getDiscountOnCheck() { return DiscountOnCheck; }
    QString  getDocumentName() { return QString().append(DocumentName); }
    int    getDocumentNumber() { return DocumentNumber; }
    int    getOpenDocumentNumber() { return OpenDocumentNumber; }
    int    getDozeInMilliliters() { return DozeInMilliliters; }
    double getDozeInMoney() { return DozeInMoney; }
    int    getDrawerNumber() { return DrawerNumber; }
    int    getECRAdvancedMode() { return ECRAdvancedMode; }
    QString  getECRAdvancedModeDescription() { return QString().append(ECRAdvancedModeDescription); }
    int    getECRBuild() { return ECRBuild; }
    int    getECRMode() { return ECRMode; }
    int    getECRMode8Status() { return ECRMode8Status; }
    QString  getECRModeDescription() { return QString().append(ECRModeDescription); }
    struct tm getECRSoftDate() { return ECRSoftDate; }
    QString  getECRSoftVersion() { return QString().append(ECRSoftVersion); }
    QString  getEKLZData() { return EKLZData; }
    int    getEKLZIsPresent() { return EKLZIsPresent; }
    QString  getEKLZNumber() { return EKLZNumber; }
    char  getEKLZFlags() { return EKLZFlags; }
    int    getEmergencyStopCode() { return EmergencyStopCode; }
    QString  getEmergencyStopCodeDescription() { return QString().append(EmergencyStopCodeDescription); }
    QString  getFieldName() { return QString().append(FieldName); }
    int    getFieldNumber() { return FieldNumber; }
    int    getFieldSize() { return FieldSize; }
    int    getFieldType() { return FieldType; }
    int    getFirstLineNumber() { return FirstLineNumber; }
    struct tm getFirstSessionDate() { return FirstSessionDate; }
    int    getFirstSessionNumber() { return FirstSessionNumber; }
    int    getFM1IsPresent() { return FM1IsPresent; }
    int    getFM2IsPresent() { return FM2IsPresent; }
    int    getFMBuild() { return FMBuild; }
    int    getFMOverflow() { return FMOverflow; }
    struct tm getFMSoftDate() { return FMSoftDate; }
    QString  getFMSoftVersion() { return QString().append(FMSoftVersion); }
    int    getFreeRecordInFM() { return FreeRecordInFM; }
    int    getFreeRegistration() { return FreeRegistration; }
    QString  getINN() { return QString().append(INN); }
    int    getJournalRibbonIsPresent() { return JournalRibbonIsPresent; }
    int    getJournalRibbonOpticalSensor() { return JournalRibbonOpticalSensor; }
    int    getJournalRibbonLever() { return JournalRibbonLever; }
    int    getKPKNumber() { return KPKNumber; }
    QVariant   getLastKPKNumber() { return QVariant(qulonglong(LastKPKNumber)); }
    double getLastKPKDocumentResult() { return LastKPKDocumentResult; }
    QDate    getLastKPKDate() { return LastKPKDate; }
    QTime    getLastKPKTime() { return LastKPKTime; }
    int    getLastFMRecordType() { return LastFMRecordType; }
    int    getLastLineNumber() { return LastLineNumber; }
    struct tm getLastSessionDate() { return LastSessionDate; }
    int    getLastSessionNumber() { return LastSessionNumber; }
    QString  getLicense() { return QString().append(License); }
    int    getLicenseIsPresent() { return LicenseIsPresent; }
    int    getLidPositionSensor() { return LidPositionSensor; }
    int    getLogicalNumber() { return LogicalNumber; }
    int    getLineNumber() { return LineNumber; }
    unsigned char* getLineData() { return LineData; }
    int    getMAXValueOfField() { return MAXValueOfField; }
    int    getMINValueOfField() { return MINValueOfField; }
    int    getMotor() { return MINValueOfField; }
    QString  getNameCashReg() { return QString().append(NameCashReg); }
    QString  getNameOperationReg() { return QString().append(NameOperationReg); }
    int    getNewPasswordTI() { return NewPasswordTI; }
    int    getOperatorNumber() { return OperatorNumber; }
    int    getPassword() { return Password; }
    int    getPistol() { return Pistol; }
    int    getPointPosition() { return PointPosition; }
    int    getPortNumber() { return PortNumber; }
    double getPrice() { return Price; }
    double getQuantity() { return Quantity; }
    int    getReceiptRibbonIsPresent() { return ReceiptRibbonIsPresent; }
    int    getReceiptRibbonOpticalSensor() { return ReceiptRibbonOpticalSensor; }
    int    getReceiptRibbonLever() { return ReceiptRibbonLever; }
    int    getTimeout() { return Timeout; }
    int    getRegisterNumber() { return RegisterNumber; }
    int    getReportType() { return ReportType; }
    int    getRegistrationNumber() { return RegistrationNumber; }
    int    getResultCode() { return ResultCode; }
    QString  getResultCodeDescription() { return QString().append(ResultCodeDescription); }
    int    getRKNumber() { return RKNumber; }
    QString  getRNM() { return QString().append(RNM); }
    int    getRoughValve() { return RoughValve; }
    int    getRowNumber() { return RowNumber; }
    int    getRunningPeriod() { return RunningPeriod; }
    QString  getSerialNumber() { return QString().append(SerialNumber); }
    int    getSessionNumber() { return SessionNumber; }
    int    getSlipDocumentIsMoving() { return SlipDocumentIsMoving; }
    int    getSlipDocumentIsPresent() { return SlipDocumentIsPresent; }
    int    getSlowingInMilliliters() { return SlowingInMilliliters; }
    int    getSlowingValve() { return SlowingValve; }
    int    getStatusRK() { return StatusRK; }
    QString  getStatusRKDescription() { return QString().append(StatusRKDescription); }
    QString getStringForPrinting() { return QString().append(StringForPrinting); }
    int    getStringQuantity() { return StringQuantity; }
    double getSumm1() { return Summ1; }
    double getSumm2() { return Summ2; }
    double getSumm3() { return Summ3; }
    double getSumm4() { return Summ4; }
    QString  getTableName() { return QString().append(TableName); }
    int    getTableNumber() { return TableNumber; }
    int    getTax1() { return Tax1; }
    int    getTax2() { return Tax2; }
    int    getTax3() { return Tax3; }
    int    getTax4() { return Tax4; }
    struct tm getTime() { return Time; }
    int    getTRKNumber() { return TRKNumber; }
    int    getTypeOfSumOfEntriesFM() { return TypeOfSumOfEntriesFM; }
    int    getUseJournalRibbon() { return UseJournalRibbon; }
    int    getUseReceiptRibbon() { return UseReceiptRibbon; }
    int    getUseSlipDocument() { return UseSlipDocument; }
    int    getUModel() { return UModel; }
    int    getUMajorType() { return UMajorType; }
    int    getUMinorType() { return UMinorType; }
    int    getUMajorProtocolVersion() { return UMajorProtocolVersion; }
    int    getUMinorProtocolVersion() { return UMinorProtocolVersion; }
    int    getUCodePage() { return UCodePage; }
    QString  getUDescription() { return UDescription; }
    int    getValueOfFieldInteger() { return ValueOfFieldInteger; }
    QString  getValueOfFieldString() { return ValueOfFieldString; }

    void setBaudRate(int a) { BaudRate = a; }
    void setBarCode(QString a) { memcpy(BarCode, a.toLocal8Bit().data(), 13); }
    void setCheckIsClosed(int a) { CheckIsClosed = a; }
    void setCheckIsMadeOut(int a) { CheckIsMadeOut = a; }
    void setCurrentDozeInMilliliters(int a) { CurrentDozeInMilliliters = a; }
    void setCurrentDozeInMoney(double a) { CurrentDozeInMoney = a; }
    void setCutType(int a) { CutType = a; }
    void setDate(struct tm a) { Date = a; }
    void setDepartment(int a) { Department = a; }
    void setDeviceCode(int a) { DeviceCode = a; }
    void setDiscountOnCheck(double a) { DiscountOnCheck = a; }
    void setDocumentName(QString a) { memcpy(DocumentName, a.toLocal8Bit().data(), 30); }
    void setDocumentNumber(int a) { DocumentNumber = a; }
    void setOpenDocumentNumber(int a) { OpenDocumentNumber = a; }
    void setDozeInMilliliters(int a) { DozeInMilliliters = a; }
    void setDozeInMoney(double a) { DozeInMoney = a; }
    void setDrawerNumber(int a) { DrawerNumber = a; }
    void setEKLZIsPresent(int a) { EKLZIsPresent = a; }
    void setFieldNumber(int a) { FieldNumber = a; }
    void setFirstLineNumber(int a) { FirstLineNumber = a; }
    void setFirstSessionDate(struct tm a) { FirstSessionDate = a; }
    void setFirstSessionNumber(int a) { FirstSessionNumber = a; }
    void setINN(QString a) { memcpy(INN, a.toLocal8Bit().data(), 12); }
    void setJournalRibbonIsPresent(int a) { JournalRibbonIsPresent = a; }
    void setJournalRibbonOpticalSensor(int a) { JournalRibbonOpticalSensor = a; }
    void setJournalRibbonLever(int a) { JournalRibbonLever = a; }
    void setLastFMRecordType(int a) { LastFMRecordType = a; }
    void setLastLineNumber(int a) { LastLineNumber = a; }
    void setLastSessionDate(struct tm a) { LastSessionDate = a; }
    void setLastSessionNumber(int a) { LastSessionNumber = a; }
    void setLicense(QString a) { memcpy(License, a.toLocal8Bit().data(), 5); }
    void setLogicalNumber(int a) { LogicalNumber = a; }
    void setLineNumber(int a) { LineNumber = a; }
    void setLineData(unsigned char* a) { strncpy((char*)LineData, (char*)a, 41); }
    void setMotor(int a) { Motor = a; }
    void setNewPasswordTI(int a) { NewPasswordTI = a; }
    void setPassword(int a) { Password = a; }
    void setPistol(int a) { Pistol = a; }
    void setPointPosition(int a) { PointPosition = a; }
    void setPortNumber(int a) { PortNumber = a; }
    void setPrice(double a) { Price = a; }
    void setQuantity(double a) { Quantity = a; }
    void setTimeout(int a) { Timeout = a; }
    void setRegisterNumber(int a) { RegisterNumber = a; }
    void setReportType(int a) { ReportType = a; }
    void setRegistrationNumber(int a) { RegistrationNumber = a; }
    void setRKNumber(int a) { RKNumber = a; }
    void setRNM(QString a) { memcpy(RNM, a.toLocal8Bit().data(), 14); }
    void setRoughValve(int a) { RoughValve = a; }
    void setRowNumber(int a) { RowNumber = a; }
    void setRunningPeriod(int a) { RunningPeriod = a; }
    void setSerialNumber(QString a) { memcpy(SerialNumber, a.toLocal8Bit().data(), 7); }
    void setSessionNumber(int a) { SessionNumber = a; }
    void setSlowingInMilliliters(int a) { SlowingInMilliliters = a; }
    void setSlowingValve(int a) { SlowingValve = a; }
    void setStringForPrinting(QString a)
    {
        memset(StringForPrinting, 0, (int)sizeof(StringForPrinting));
        int size = a.size() > (int)sizeof(StringForPrinting) - 1 ? (int)sizeof(StringForPrinting) - 1 : a.size();
        if (size > 0)
            memcpy(StringForPrinting, a.toLocal8Bit().data(), size);
    }
    void setStringQuantity(int a) { StringQuantity = a; }
    void setSumm1(double a) { Summ1 = a; }
    void setSumm2(double a) { Summ2 = a; }
    void setSumm3(double a) { Summ3 = a; }
    void setSumm4(double a) { Summ4 = a; }
    void setTableNumber(int a) { TableNumber = a; }
    void setTax1(int a) { Tax1 = a; }
    void setTax2(int a) { Tax2 = a; }
    void setTax3(int a) { Tax3 = a; }
    void setTax4(int a) { Tax4 = a; }
    void setTime(struct tm a) { Time = a; }
    void setTRKNumber(int a) { TRKNumber = a; }
    void setTypeOfSumOfEntriesFM(int a) { TypeOfSumOfEntriesFM = a; }
    void setUseJournalRibbon(int a) { UseJournalRibbon = a; }
    void setUseReceiptRibbon(int a) { UseReceiptRibbon = a; }
    void setUseSlipDocument(int a) { UseSlipDocument = a; }
    void setValueOfFieldInteger(int a) { ValueOfFieldInteger = a; }
    void setValueOfFieldString(QString a)
    {
        memset(StringForPrinting, 0, (int)sizeof(ValueOfFieldString));
        int size = a.size() > (int)sizeof(ValueOfFieldString) - 1 ? (int)sizeof(ValueOfFieldString) - 1 : a.size();
        if (size > 0)
            memcpy(ValueOfFieldString, a.toLocal8Bit().data(), size);
    }
};


class DriverFR : public QObject
{
    Q_OBJECT
public:
    explicit DriverFR(QObject *parent = 0 /*nullptr*/);
    ~DriverFR();
    virtual void setApp(TApplication* a) { app = a; }
    virtual bool open(QString, int, int, int);
    virtual void close();
    Q_INVOKABLE virtual QVariant getProperty(QString name);
    Q_INVOKABLE virtual bool setProperty(QString name, QVariant value);
    virtual QMyExtSerialPort* getSerialPort() { return serialPort; }
    virtual bool isRemote() { return remote; }
    Q_INVOKABLE virtual bool isLocked();
    virtual void        setLock(bool lock, QString lockedByHost = "");
    virtual QString     getLockedByHost() { return lockedByHost; }          // Вернуть кем заблокирован фискальник
    Q_INVOKABLE virtual void setProgressDialogValue(int value);
    Q_INVOKABLE virtual void setShowProgressBar(bool);
    Q_INVOKABLE virtual void writeLog(QString = "");
    virtual bool deviceIsReady();


// Функции для работы с фискальным регистратором
    Q_INVOKABLE virtual bool Connect(bool showError = true);
    Q_INVOKABLE virtual void DisConnect();
    Q_INVOKABLE virtual int Beep();
    Q_INVOKABLE virtual int Buy();
    Q_INVOKABLE virtual int CancelCheck();
    Q_INVOKABLE virtual int CashIncome();
    Q_INVOKABLE virtual int CashOutcome();
    Q_INVOKABLE virtual int Charge();
    Q_INVOKABLE virtual int CheckSubTotal();
    Q_INVOKABLE virtual int CloseCheck();
    Q_INVOKABLE virtual int ConfirmDate();
    Q_INVOKABLE virtual int ContinuePrint();
    Q_INVOKABLE virtual int Correction();
    Q_INVOKABLE virtual int CutCheck();
    Q_INVOKABLE virtual int DampRequest();
    Q_INVOKABLE virtual int Discount();
    Q_INVOKABLE virtual int DozeOilCheck();
    Q_INVOKABLE virtual int Draw();
    Q_INVOKABLE virtual int EjectSlipDocument();
    Q_INVOKABLE virtual int EKLZDepartmentReportInDatesRange();
    Q_INVOKABLE virtual int EKLZDepartmentReportInSessionsRange();
    Q_INVOKABLE virtual int EKLZJournalOnSessionNumber();
    Q_INVOKABLE virtual int EKLZSessionReportInDatesRange();
    Q_INVOKABLE virtual int EKLZSessionReportInSessionRange();
    Q_INVOKABLE virtual int FeedDocument();
    Q_INVOKABLE virtual int FeedDocument(int);
    Q_INVOKABLE virtual int Fiscalization();
    Q_INVOKABLE virtual int FiscalReportForDatesRange();
    Q_INVOKABLE virtual int FiscalReportForSessionRange();
    Q_INVOKABLE virtual int GetData();
    Q_INVOKABLE virtual int GetDeviceMetrics();
    Q_INVOKABLE virtual int GetExchangeParam();
    Q_INVOKABLE virtual int GetFieldStruct();
    Q_INVOKABLE virtual int GetFiscalizationParameters();
    Q_INVOKABLE virtual int GetFMRecordsSum();
    Q_INVOKABLE virtual int GetShortECRStatus();
    Q_INVOKABLE virtual int GetECRStatus();
    Q_INVOKABLE virtual int GetEKLZData();
    Q_INVOKABLE virtual int GetEKLZJournal();
    Q_INVOKABLE virtual int GetEKLZCode1Report();
    Q_INVOKABLE virtual int EKLZInterrupt();
    Q_INVOKABLE virtual int GetLastFMRecordDate();
    Q_INVOKABLE virtual int GetLiterSumCounter();
    Q_INVOKABLE virtual int GetCashReg();
    Q_INVOKABLE virtual int GetOperationReg();
    Q_INVOKABLE virtual int GetRangeDatesAndSessions();
    Q_INVOKABLE virtual int GetRKStatus();
    Q_INVOKABLE virtual int GetTableStruct();
    Q_INVOKABLE virtual int InitFM();
    Q_INVOKABLE virtual int InitTable();
    Q_INVOKABLE virtual int InterruptDataStream();
    Q_INVOKABLE virtual int InterruptFullReport();
    Q_INVOKABLE virtual int InterruptTest();
    Q_INVOKABLE virtual int LaunchRK();
    Q_INVOKABLE virtual int LoadLineData();
    Q_INVOKABLE virtual int OilSale();
    Q_INVOKABLE virtual int OpenDrawer();
    Q_INVOKABLE virtual int PrintBarCode();
    Q_INVOKABLE virtual int PrintDocumentTitle();
    Q_INVOKABLE virtual int PrintOperationReg();
    Q_INVOKABLE virtual int PrintReportWithCleaning();
    Q_INVOKABLE virtual int PrintReportWithoutCleaning();
    Q_INVOKABLE virtual int PrintString(QString = "", int = 1);
    Q_INVOKABLE virtual int PrintWideString();
    Q_INVOKABLE virtual int ReadEKLZDocumentOnKPK();
    Q_INVOKABLE virtual int ReadEKLZSessionTotal();
    Q_INVOKABLE virtual int ReadLicense();
    Q_INVOKABLE virtual int ReadTable();
    Q_INVOKABLE virtual int ResetAllTRK();
    Q_INVOKABLE virtual int ResetRK();
    Q_INVOKABLE virtual int ResetSettings();
    Q_INVOKABLE virtual int ResetSummary();
    Q_INVOKABLE virtual int ReturnBuy();
    Q_INVOKABLE virtual int ReturnSale();
    Q_INVOKABLE virtual int Sale();
    Q_INVOKABLE virtual int SetDate();
    Q_INVOKABLE virtual int SetDozeInMilliliters();
    Q_INVOKABLE virtual int SetDozeInMoney();
    Q_INVOKABLE virtual int SetExchangeParam();
    Q_INVOKABLE virtual int SetPointPosition();
    Q_INVOKABLE virtual int SetRKParameters();
    Q_INVOKABLE virtual int SetSerialNumber();
    Q_INVOKABLE virtual int SetTime();
    Q_INVOKABLE virtual int StopEKLZDocumentPrinting();
    Q_INVOKABLE virtual int StopRK();
    Q_INVOKABLE virtual int Storno();
    Q_INVOKABLE virtual int StornoCharge();
    Q_INVOKABLE virtual int StornoDiscount();
    Q_INVOKABLE virtual int SummOilCheck();
    Q_INVOKABLE virtual int Test();
    Q_INVOKABLE virtual int WriteLicense();
    Q_INVOKABLE virtual int WriteTable();
    Q_INVOKABLE virtual int OpenSession();

private:

    short int readByte();
    short int readBytes(unsigned char *, int);
    int readMessage(answer *);
    int sendENQ();
    int sendNAK();
    int sendACK();
    unsigned short int LRC(unsigned char *, int, int = 0);
    int readAnswer(answer*, short int = 0);
    int composeComm(command*, int, int, parameter*);
    int sendCommand(int, int, parameter*);
    int errHand(answer*);
    int evalint(unsigned char*, int);
    int32_t evalint32(unsigned char*, int);
    int64_t evalint64(unsigned char*, int);
    void evaldate(unsigned char*, struct tm*);
    void evaltime(unsigned char *, struct tm *);
    void DefineECRModeDescription();
    void logCommand(int, QString);
    int processCommand(int, parameter*, answer*);

    QMyExtSerialPort*         serialPort;
    bool            remote;

    frProp         fr;     // Функции фискального регистратора
    bool            connected;
    bool            locked;     // Фискальный регистратор заблокирован на период работы с клиентом
    QString         lockedByHost;   // IP адрес хоста, который заблокировал фискальник. Если заблокирован локальным хостом, то пустая строка
    struct timeval  timeout;
    static unsigned commlen[0x100];
    static const char* errmsg[];
    static const char* errrecomendations[];
    static recomendations referrrecomendations[];
    static const char* ecrmodedesc[];
    static const char* ecrmode8desc[];
    static const char* ecrsubmodedesc[];
    static const char* devcodedesc[];
    static const char* failConnectErrorMessage;

    QTextCodec *codec;
    TApplication* app;
    MyProgressDialog* progressDialog;
    bool    showProgressBar;
    int     maxTries;
};

Q_DECLARE_INTERFACE(DriverFR, "org.QBalance.DriverFR")

#endif // DRIVERFR_H
