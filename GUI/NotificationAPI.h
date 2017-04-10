#ifndef NOTIFICATIONAPI_H
#define NOTIFICATIONAPI_H

#include <QApplication>

void initializeNotification();
void updateNotification(QString title, QString msg,
        QString pushBtn1Lbl,
        QString pushBtn2Lbl,
        QString pushBtn3Lbl,
        int timer);
void processAllEvents();
void waitToExit();

#endif // NOTIFICATIONAPI
