#ifndef CONNECTIONFORM_H
#define CONNECTIONFORM_H

#define CONNECTION_GROUP_NAME   "connections"

#include <QString>
#include <QComboBox>
#include <QLineEdit>
#include "form.h"
#include "../dbfactory.h"

class TApplication;

class ConnectionForm : public Form {
    Q_OBJECT
public:
    virtual bool open(QWidget* pwgt = 0, Essence* par = 0);
    void initForm(QString, QString, int, bool readSettings = true);
    QString connectionName() { return pcmbConnection->currentText(); }
public slots:
    virtual int exec(DBFactory*);
protected:
private slots:
    void cmdSave();
    void cmdDelete();
    void cmdOk();
    void connectionChanged(int);
private:
    DBFactory* db;
    QComboBox* pcmbConnection;
    QLineEdit* ptxtHost;
    QLineEdit* ptxtPort;
    QLineEdit* ptxtDatabase;
    void readConnectionsList();
    void readDefaultSettings();
    void writeDefaultSettings();
    void readSettings(QString);
    void writeSettings();
    void deleteSettings(QString);
};

#endif // CONNECTIONFORM_H
