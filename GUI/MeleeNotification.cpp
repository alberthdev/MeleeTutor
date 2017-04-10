#include <QtGui>
#include <QDesktopWidget>
#include "MeleeNotification.h"

// if we include <QtGui> there is no need to include every class used: <QString>, <QFileDialog>,...

MeleeNotificationApp::MeleeNotificationApp(QWidget *parent, QString title,
    QString msg, QString pushBtn1Lbl, QString pushBtn2Lbl, QString pushBtn3Lbl,
    int timer)
{
    QRect screenRect;
    setupUi(this); // this sets up GUI

    screenRect = QApplication::desktop()->availableGeometry(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    this->move(0, screenRect.bottom() - this->frameGeometry().bottom());

    connect( pushBtn1, SIGNAL( clicked() ), this, SLOT( pushBtn1Click() ) ); 
    connect( pushBtn2, SIGNAL( clicked() ), this, SLOT( pushBtn2Click() ) ); 
    connect( pushBtn3, SIGNAL( clicked() ), this, SLOT( pushBtn3Click() ) );

    this->updateNotification(title, msg, pushBtn1Lbl, pushBtn2Lbl, pushBtn3Lbl, timer);
}

void MeleeNotificationApp::updateNotification(QString title,
    QString msg, QString pushBtn1Lbl, QString pushBtn2Lbl, QString pushBtn3Lbl,
    int timer) {
    // signals/slots mechanism in action
    notificationLbl->setText(title);
    notificationTextLbl->setText(msg);
    
    if (pushBtn1Lbl.isEmpty()) {
        pushBtn1->setVisible(false);
    } else {
        pushBtn1->setVisible(true);
        pushBtn1->setText(pushBtn1Lbl);
    }
    
    if (pushBtn2Lbl.isEmpty()) {
        pushBtn2->setVisible(false);
    } else {
        pushBtn2->setVisible(true);
        pushBtn2->setText(pushBtn2Lbl);
    }
    
    if (pushBtn3Lbl.isEmpty()) {
        pushBtn3->setVisible(false);
    } else {
        pushBtn3->setVisible(true);
        pushBtn3->setText(pushBtn3Lbl);
    }

    if (timer > 0) {
        m_timer = new QTimer(this);
        connect(m_timer, SIGNAL(timeout()), this, SLOT(exitApp()));
        m_timer->setSingleShot(true);
        m_timer->start(timer * 1000);
    }
}

void MeleeNotificationApp::selectBtn(int button) {
    if (button == 1) {
        pushBtn1->setEnabled(true);
        pushBtn2->setEnabled(false);
        pushBtn3->setEnabled(false);
    } else if (button == 2) {
        pushBtn1->setEnabled(false);
        pushBtn2->setEnabled(true);
        pushBtn3->setEnabled(false);
    } else if (button == 3) {
        pushBtn1->setEnabled(false);
        pushBtn2->setEnabled(false);
        pushBtn3->setEnabled(true);
    } else {
        printf("WARNING: invalid button selection %d\n", button);
    }
}

void MeleeNotificationApp::exitApp() {
    QApplication::exit(0);
}

void MeleeNotificationApp::pushBtn1Click()
{
    QApplication::exit(1);
}

void MeleeNotificationApp::pushBtn2Click()
{
    QApplication::exit(2);
}

void MeleeNotificationApp::pushBtn3Click()
{
    QApplication::exit(3);
}
