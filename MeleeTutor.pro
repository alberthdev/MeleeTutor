QT += widgets

INCLUDEPATH = Goals/ Strategies/ Tactics/ Chains/ Util/ GUI/ .
HEADERS     = Goals/*.h Strategies/*.h Tactics/*.h Chains/*.h Util/*.h GUI/*.h *.h
SOURCES     = Goals/*.cpp Strategies/*.cpp Tactics/*.cpp Chains/*.cpp Util/*.cpp GUI/*.cpp smashbot.cpp
FORMS       = GUI/MeleeTutorBox.ui

# install
target.path = MeleeNotification
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS *.pro
sources.path = .
INSTALLS += target sources
