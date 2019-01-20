#ifndef DRIVERFRINTERFACE_H
#define DRIVERFRINTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QMetaObject>
#include <QtCore/QMetaProperty>
#include <QtCore/QDate>
#include <QtCore/QTime>
#include "driverfr.h"

class TApplication;
class QMyExtSerialPort;

class DriverFRInterface: public DriverFR
{
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "DriverFR")
        Q_INTERFACES(DriverFR)

public:
    virtual ~DriverFRInterface() {}

    virtual void setApp(TApplication* a) { DriverFR::setApp(a); }
    virtual bool open(QString s, int i1, int i2, int i3)  { return DriverFR::open(s, i1, i2, i3); }
    virtual void close() { DriverFR::close(); }
    Q_INVOKABLE virtual QVariant getProperty(QString s) { return DriverFR::getProperty(s); }
    Q_INVOKABLE virtual bool setProperty(QString s, QVariant v) { return DriverFR::setProperty(s, v); }
    virtual QMyExtSerialPort* getSerialPort() { return DriverFR::getSerialPort(); }
    virtual bool isRemote() { return DriverFR::isRemote(); }
    Q_INVOKABLE virtual bool isLocked() { return DriverFR::isLocked(); }
    virtual void setLock(bool b, QString s) { DriverFR::setLock(b, s); }
    virtual QString getLockedByHost() { return DriverFR::getLockedByHost(); }
    Q_INVOKABLE virtual void setProgressDialogValue(int i) { DriverFR::setProgressDialogValue(i); }
    Q_INVOKABLE virtual void setShowProgressBar(bool b) { DriverFR::setShowProgressBar(b); }
    Q_INVOKABLE virtual void writeLog(QString s) { DriverFR::writeLog(s); }
    virtual bool deviceIsReady() { return DriverFR::deviceIsReady(); }

// Функции для работы с фискальным регистратором
    Q_INVOKABLE virtual bool Connect(bool b = true) { return DriverFR::Connect(b); }
    Q_INVOKABLE virtual void DisConnect() { DriverFR::DisConnect(); }
    Q_INVOKABLE virtual int Beep() { return DriverFR::Beep(); }
    Q_INVOKABLE virtual int Buy() { return DriverFR::Buy(); }
    Q_INVOKABLE virtual int CancelCheck() { return DriverFR::CancelCheck(); }
    Q_INVOKABLE virtual int CashIncome() { return DriverFR::CashIncome(); }
    Q_INVOKABLE virtual int CashOutcome() { return DriverFR::CashOutcome(); }
    Q_INVOKABLE virtual int Charge() { return DriverFR::Charge(); }
    Q_INVOKABLE virtual int CheckSubTotal() { return DriverFR::CheckSubTotal(); }
    Q_INVOKABLE virtual int CloseCheck() { return DriverFR::CloseCheck(); }
    Q_INVOKABLE virtual int ConfirmDate() { return DriverFR::ConfirmDate(); }
    Q_INVOKABLE virtual int ContinuePrint() { return DriverFR::ContinuePrint(); }
    Q_INVOKABLE virtual int Correction() { return DriverFR::Correction(); }
    Q_INVOKABLE virtual int CutCheck() { return DriverFR::CutCheck(); }
    Q_INVOKABLE virtual int DampRequest() { return DriverFR::DampRequest(); }
    Q_INVOKABLE virtual int Discount() { return DriverFR::Discount(); }
    Q_INVOKABLE virtual int DozeOilCheck() { return DriverFR::DozeOilCheck(); }
    Q_INVOKABLE virtual int Draw() { return DriverFR::Draw(); }
    Q_INVOKABLE virtual int EjectSlipDocument() { return DriverFR::EjectSlipDocument(); }
    Q_INVOKABLE virtual int EKLZDepartmentReportInDatesRange() { return DriverFR::EKLZDepartmentReportInDatesRange(); }
    Q_INVOKABLE virtual int EKLZDepartmentReportInSessionsRange() { return DriverFR::EKLZDepartmentReportInSessionsRange(); }
    Q_INVOKABLE virtual int EKLZJournalOnSessionNumber() { return DriverFR::EKLZJournalOnSessionNumber(); }
    Q_INVOKABLE virtual int EKLZSessionReportInDatesRange() { return DriverFR::EKLZSessionReportInDatesRange(); }
    Q_INVOKABLE virtual int EKLZSessionReportInSessionRange() { return DriverFR::EKLZSessionReportInSessionRange(); }
    Q_INVOKABLE virtual int FeedDocument() { return DriverFR::FeedDocument(); }
    Q_INVOKABLE virtual int FeedDocument(int) { return DriverFR::FeedDocument(); }
    Q_INVOKABLE virtual int Fiscalization() { return DriverFR::Fiscalization(); }
    Q_INVOKABLE virtual int FiscalReportForDatesRange() { return DriverFR::FiscalReportForDatesRange(); }
    Q_INVOKABLE virtual int FiscalReportForSessionRange() { return DriverFR::FiscalReportForSessionRange(); }
    Q_INVOKABLE virtual int GetData() { return DriverFR::GetData(); }
    Q_INVOKABLE virtual int GetDeviceMetrics() { return DriverFR::GetDeviceMetrics(); }
    Q_INVOKABLE virtual int GetExchangeParam() { return DriverFR::GetExchangeParam(); }
    Q_INVOKABLE virtual int GetFieldStruct() { return DriverFR::GetFieldStruct(); }
    Q_INVOKABLE virtual int GetFiscalizationParameters() { return DriverFR::GetFiscalizationParameters(); }
    Q_INVOKABLE virtual int GetFMRecordsSum() { return DriverFR::GetFMRecordsSum(); }
    Q_INVOKABLE virtual int GetShortECRStatus() { return DriverFR::GetShortECRStatus(); }
    Q_INVOKABLE virtual int GetECRStatus() { return DriverFR::GetECRStatus(); }
    Q_INVOKABLE virtual int GetEKLZData() { return DriverFR::GetEKLZData(); }
    Q_INVOKABLE virtual int GetEKLZJournal() { return DriverFR::GetEKLZJournal(); }
    Q_INVOKABLE virtual int GetEKLZCode1Report() { return DriverFR::GetEKLZCode1Report(); }
    Q_INVOKABLE virtual int EKLZInterrupt() { return DriverFR::EKLZInterrupt(); }
    Q_INVOKABLE virtual int GetLastFMRecordDate() { return DriverFR::GetLastFMRecordDate(); }
    Q_INVOKABLE virtual int GetLiterSumCounter() { return DriverFR::GetLiterSumCounter(); }
    Q_INVOKABLE virtual int GetCashReg() { return DriverFR::GetCashReg(); }
    Q_INVOKABLE virtual int GetOperationReg() { return DriverFR::GetOperationReg(); }
    Q_INVOKABLE virtual int GetRangeDatesAndSessions() { return DriverFR::GetRangeDatesAndSessions(); }
    Q_INVOKABLE virtual int GetRKStatus() { return DriverFR::GetRKStatus(); }
    Q_INVOKABLE virtual int GetTableStruct() { return DriverFR::GetTableStruct(); }
    Q_INVOKABLE virtual int InitFM() { return DriverFR::InitFM(); }
    Q_INVOKABLE virtual int InitTable() { return DriverFR::InitTable(); }
    Q_INVOKABLE virtual int InterruptDataStream() { return DriverFR::InterruptDataStream(); }
    Q_INVOKABLE virtual int InterruptFullReport() { return DriverFR::InterruptFullReport(); }
    Q_INVOKABLE virtual int InterruptTest() { return DriverFR::InterruptTest(); }
    Q_INVOKABLE virtual int LaunchRK() { return DriverFR::LaunchRK(); }
    Q_INVOKABLE virtual int LoadLineData() { return DriverFR::LoadLineData(); }
    Q_INVOKABLE virtual int OilSale() { return DriverFR::OilSale(); }
    Q_INVOKABLE virtual int OpenDrawer() { return DriverFR::OpenDrawer(); }
    Q_INVOKABLE virtual int PrintBarCode() { return DriverFR::PrintBarCode(); }
    Q_INVOKABLE virtual int PrintDocumentTitle() { return DriverFR::PrintDocumentTitle(); }
    Q_INVOKABLE virtual int PrintOperationReg() { return DriverFR::PrintOperationReg(); }
    Q_INVOKABLE virtual int PrintReportWithCleaning() { return DriverFR::PrintReportWithCleaning(); }
    Q_INVOKABLE virtual int PrintReportWithoutCleaning() { return DriverFR::PrintReportWithoutCleaning(); }
    Q_INVOKABLE virtual int PrintString(QString s = "", int i = 1) { return DriverFR::PrintString(s, i); }
    Q_INVOKABLE virtual int PrintWideString() { return DriverFR::PrintWideString(); }
    Q_INVOKABLE virtual int ReadEKLZDocumentOnKPK() { return DriverFR::ReadEKLZDocumentOnKPK(); }
    Q_INVOKABLE virtual int ReadEKLZSessionTotal() { return DriverFR::ReadEKLZSessionTotal(); }
    Q_INVOKABLE virtual int ReadLicense() { return DriverFR::ReadLicense(); }
    Q_INVOKABLE virtual int ReadTable() { return DriverFR::ReadTable(); }
    Q_INVOKABLE virtual int ResetAllTRK() { return DriverFR::ResetAllTRK(); }
    Q_INVOKABLE virtual int ResetRK() { return DriverFR::ResetRK(); }
    Q_INVOKABLE virtual int ResetSettings() { return DriverFR::ResetSettings(); }
    Q_INVOKABLE virtual int ResetSummary() { return DriverFR::ResetSummary(); }
    Q_INVOKABLE virtual int ReturnBuy() { return DriverFR::ReturnBuy(); }
    Q_INVOKABLE virtual int ReturnSale() { return DriverFR::ReturnSale(); }
    Q_INVOKABLE virtual int Sale() { return DriverFR::Sale(); }
    Q_INVOKABLE virtual int SetDate() { return DriverFR::SetDate(); }
    Q_INVOKABLE virtual int SetDozeInMilliliters() { return DriverFR::SetDozeInMilliliters(); }
    Q_INVOKABLE virtual int SetDozeInMoney() { return DriverFR::SetDozeInMoney(); }
    Q_INVOKABLE virtual int SetExchangeParam() { return DriverFR::SetExchangeParam(); }
    Q_INVOKABLE virtual int SetPointPosition() { return DriverFR::SetPointPosition(); }
    Q_INVOKABLE virtual int SetRKParameters() { return DriverFR::SetRKParameters(); }
    Q_INVOKABLE virtual int SetSerialNumber() { return DriverFR::SetSerialNumber(); }
    Q_INVOKABLE virtual int SetTime() { return DriverFR::SetTime(); }
    Q_INVOKABLE virtual int StopEKLZDocumentPrinting() { return DriverFR::StopEKLZDocumentPrinting(); }
    Q_INVOKABLE virtual int StopRK() { return DriverFR::StopRK(); }
    Q_INVOKABLE virtual int Storno() { return DriverFR::Storno(); }
    Q_INVOKABLE virtual int StornoCharge() { return DriverFR::StornoCharge(); }
    Q_INVOKABLE virtual int StornoDiscount() { return DriverFR::StornoDiscount(); }
    Q_INVOKABLE virtual int SummOilCheck() { return DriverFR::SummOilCheck(); }
    Q_INVOKABLE virtual int Test() { return DriverFR::Test(); }
    Q_INVOKABLE virtual int WriteLicense() { return DriverFR::WriteLicense(); }
    Q_INVOKABLE virtual int WriteTable() { return DriverFR::WriteTable(); }
    Q_INVOKABLE virtual int OpenSession() { return DriverFR::OpenSession(); }
};

#endif // DRIVERFRINTERFACE_H
