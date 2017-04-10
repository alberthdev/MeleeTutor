#ifndef MELEENOTIFICATION_H
#define MELEENOTIFICATION_H

#include "ui_MeleeTutorBox.h"

class MeleeNotificationApp : public QMainWindow, private Ui::MeleeTutorBoxWindow
{
    Q_OBJECT

public:
    MeleeNotificationApp(QWidget *parent = 0, QString title = "Hello, world!", QString msg = "Hello, msg!",
        QString pushBtn1Lbl = "Button 1",
        QString pushBtn2Lbl = "Button 2",
        QString pushBtn3Lbl = "Button 3",
        int timer = -1);
    QTimer *m_timer;
    void selectBtn(int button);
    void updateNotification(QString title, QString msg,
        QString pushBtn1Lbl,
        QString pushBtn2Lbl,
        QString pushBtn3Lbl,
        int timer);

public slots:
    void pushBtn1Click();
    void pushBtn2Click();
    void pushBtn3Click();
    void exitApp();
};

#endif
