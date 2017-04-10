QT += widgets

HEADERS     = MeleeNotification.h
SOURCES     = MeleeNotification.cpp MeleeNotificationMain.cpp NotificationAPI.cpp ../smashbot.cpp
FORMS       = MeleeTutorBox.ui

# install
target.path = MeleeNotification
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS *.pro
sources.path = .
INSTALLS += target sources
