#include "wizardform.h"

WizardForm::WizardForm(QObject* parent/* = NULL*/): Form(parent)
{
    result = true;
    frameIndex = 0;
    currentFrame = 0;
}


bool WizardForm::open(QWidget* pwgt)
{
    if (Form::open(pwgt))
    {
        formWidget->setMinimumSize(500, 300);
        // добавим кнопки "Вперед" и "Назад"
        buttonForward = new QPushButton(QObject::trUtf8("&Вперед"));
        buttonForward->setObjectName("buttonForward");
        connect(buttonForward, SIGNAL(clicked()), this, SLOT(cmdForward()));
        cmdButtonLayout->insertWidget(0, buttonForward);
        buttonBackward = new QPushButton(QObject::trUtf8("&Назад"));
        buttonBackward->setObjectName("buttonBackward");
        connect(buttonBackward, SIGNAL(clicked()), this, SLOT(cmdBackward()));
        cmdButtonLayout->insertWidget(0, buttonBackward);
        setIcons();
        initFrames();
        currentFrame = frames.at(0);
        currentFrame->show();
        QFrame* line = new QFrame(formWidget);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        vbxLayout->insertWidget(0, line);
        vbxLayout->insertWidget(0, currentFrame);
        setButtonsEnabled();
        return true;
    }
    return false;
}


void WizardForm::addFrame(QFrame* frame)
{
    frame->hide();
    frames.append(frame);
}


void WizardForm::cmdForward()
{
    frameIndex++;
    setButtonsEnabled();
    setFrame();
}


void WizardForm::cmdBackward()
{
    frameIndex--;
    setButtonsEnabled();
    setFrame();
}


void WizardForm::cmdOk()
{
    Form::cmdOk();
    result = execute();
}


void WizardForm::setButtonsEnabled()
{
    if (frames.size() > 0)
    {
        buttonCancel->show();
        if (frameIndex == frames.size() - 1)
            buttonOk->show();
        else
            buttonOk->hide();
        if (frames.size() > 1)
        {
            if (frameIndex > 0)
                buttonBackward->setEnabled(true);
            else
                buttonBackward->setEnabled(false);
            if (frameIndex < frames.size() - 1)
                buttonForward->setEnabled(true);
            else
                buttonForward->setEnabled(false);
        }
        else
        {
            buttonBackward->hide();
            buttonForward->hide();
        }
    }
}


void WizardForm::setFrame()
{
    currentFrame->hide();
    vbxLayout->removeWidget(currentFrame);
    currentFrame = frames.at(frameIndex);
    currentFrame->show();
    vbxLayout->insertWidget(0, currentFrame);
}
