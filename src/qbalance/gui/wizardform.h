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

#ifndef WIZARDFORM_H
#define WIZARDFORM_H

#include "form.h"

class WizardForm : public Form
{
    Q_OBJECT
public:
    WizardForm(QObject* parent = nullptr);
    virtual bool open(QWidget* pwgt = nullptr);
    bool getResult();
public slots:
    virtual void                cmdOk();
    void                        cmdForward();
    void                        cmdBackward();
protected:
    QList<QWidget*>             frames;
    QPushButton*                buttonForward;
    QPushButton*                buttonBackward;
    void                        addFrame(QVBoxLayout*, QString = "");
    virtual void                initFrames() = 0;
    virtual bool                setData();
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
