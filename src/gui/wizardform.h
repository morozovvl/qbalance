#ifndef WIZARDFORM_H
#define WIZARDFORM_H

#include "form.h"

class WizardForm : public Form
{
    Q_OBJECT
public:
    WizardForm(QObject* parent = NULL);
    virtual bool open(QWidget* pwgt = NULL);
    bool getResult() { return result; }
public slots:
    virtual void                cmdOk();
    void                        cmdForward();
    void                        cmdBackward();
protected:
    QList<QFrame*>              frames;
    QPushButton*                buttonForward;
    QPushButton*                buttonBackward;
    void                        addFrame(QVBoxLayout*, QString = "");
    virtual void                initFrames() = 0;
    virtual bool                setData() { return true; }
    virtual void                frameActivated(int) { ; }
    virtual void                frameDeactivated(int) { ; }
private:
    bool                        result;
    int                         frameIndex;
    int                         oldFrameIndex;
    QWidget*                    currentFrame;
    void                        setButtonsEnabled();
    void                        setFrame();
    virtual void                getData() { ; }
};

#endif // WIZARDFORM_H
