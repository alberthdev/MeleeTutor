#include <QApplication>

#include "MeleeNotification.h"
#include "NotificationAPI.h"

int main(int argc, char *argv[])
{
    /*
    QApplication app(argc, argv);
    MeleeNotificationApp *dialog = new MeleeNotificationApp;

    dialog->show();
    return app.exec();
    */
    int i = 0;
    initializeNotification();
    for (i = 0; i < 5; i++) {
        printf("Round %d!\n", i);
        updateNotification("Hello", "world", QString(), QString(), QString(), 10);
        processAllEvents();
    }
    waitToExit();
    return 0;
}
