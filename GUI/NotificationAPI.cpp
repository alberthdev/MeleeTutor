#include <QApplication>
#include "NotificationAPI.h"
#include "MeleeNotification.h"

static int BSargc = 1;
static int &BSargv_p = BSargc;
char *BSargv_1 = "hello";
static char **BSargv = &BSargv_1;

QApplication *app = NULL;
MeleeNotificationApp *dialog = NULL;

void initializeNotification() {
    if (app == NULL) {
        app = new QApplication(BSargv_p, &BSargv_1);
    } else {
        printf("WARNING: QApplication already initialized!\n");
    }

    if (dialog == NULL) {
        dialog = new MeleeNotificationApp(0, "MeleeTutor", "Nothing to display yet, hold tight!",
            QString(), QString(), QString(), -1); // were not confirmed.
        dialog->show();
    } else {
        printf("WARNING: Dialog already initialized!\n");
    }
}

void updateNotification(QString title, QString msg,
        QString pushBtn1Lbl,
        QString pushBtn2Lbl,
        QString pushBtn3Lbl,
        int timer)
{
    dialog->updateNotification(title, msg, pushBtn1Lbl, pushBtn2Lbl, pushBtn3Lbl, timer);
}

void processAllEvents() {
    printf("Processing events...\n");
    printf("  -> processEvents\n");
    app->processEvents();
    printf("  -> sendPostedEvents\n");
    app->sendPostedEvents();
}

void waitToExit() {
    printf("Waiting until app exits by itself...\n");
    app->exec();
}