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
        getData();
        // Инициализируем страницы
        initFrames();
        if (frames.count() > 0)
        {
            formWidget->setMinimumSize(700, 400);
            // добавим кнопку "Вперед"
            buttonForward = new QPushButton(QObject::trUtf8("&Вперед"));
            buttonForward->setObjectName("buttonForward");
            connect(buttonForward, SIGNAL(clicked()), this, SLOT(cmdForward()));
            cmdButtonLayout->insertWidget(0, buttonForward);
            // и кнопку "Назад"
            buttonBackward = new QPushButton(QObject::trUtf8("&Назад"));
            buttonBackward->setObjectName("buttonBackward");
            connect(buttonBackward, SIGNAL(clicked()), this, SLOT(cmdBackward()));
            cmdButtonLayout->insertWidget(0, buttonBackward);
            // установим иконки
            setIcons();
            // Вставим разделительную линию
            QFrame* line = new QFrame(formWidget);
            line->setFrameShape(QFrame::HLine);
            line->setFrameShadow(QFrame::Sunken);
            vbxLayout->insertWidget(0, line);
            // Установим текущий фрейм
            currentFrame = frames.at(0);
            frameActivated(0);
            currentFrame->show();
            vbxLayout->insertWidget(0, currentFrame);
            // Установим кнопки
            setButtonsEnabled();
            return true;
        }
    }
    return false;
}


void WizardForm::addFrame(QVBoxLayout* layout, QString title/* = ""*/)
{
    if (title.size() > 0)
    {
        // Вставим разделительную линию
        QFrame* line = new QFrame(formWidget);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        layout->insertWidget(0, line);
        QLabel* label = new QLabel(title);
        label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        layout->insertWidget(0, label);
    }
    QFrame* frame = new QFrame(formWidget);
    frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    frame->setLayout(layout);
    frame->hide();
    frames.append(frame);
}


void WizardForm::cmdForward()
{
    oldFrameIndex = frameIndex;
    frameIndex++;
    setFrame();
    setButtonsEnabled();
}


void WizardForm::cmdBackward()
{
    oldFrameIndex = frameIndex;
    frameIndex--;
    setFrame();
    setButtonsEnabled();
}


void WizardForm::cmdOk()
{
    if (execute())
        Form::cmdOk();
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
    frameDeactivated(oldFrameIndex);
    currentFrame->hide();
    vbxLayout->removeWidget(currentFrame);
    currentFrame = frames.at(frameIndex);
    frameActivated(frameIndex);
    currentFrame->show();
    vbxLayout->insertWidget(0, currentFrame);
}
