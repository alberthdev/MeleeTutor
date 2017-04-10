# MeleeTutor
Newbie to pro in no time flat!

More info at:

https://devpost.com/software/meleetutor

# Quick Build Instructions
Currently, this will only work properly on Linux/Mac due to limitations
in memory access support in Dolphin on other platforms. (See
[this Dolphin issue](https://bugs.dolphin-emu.org/issues/10126) for
more information.)

You will need Qt 5.6+ to build MeleeTutor, and Dolphin 5.0+ to pair
MeleeTutor with.

 1. Run `qmake`. Alternatively, create a build directory and run `qmake ..`.

 2. Run `make`.

 3. Run `./MeleeTutor` first - it will wait for a Dolphin Melee instance to
    start up. MeleeTutor may be unresponsive for a bit until Melee is running
    on Dolphin.

 4. Copy GCPadNew.ini into your Dolphin configuration directory.

 5. Now open your Dolphin emulator. Set your gamepad controller configuration
    to the "pipe" Gamecube input for player #2.

 6. Start Melee in Dolphin. If everything is working, the menu will be moving
    on its own.

 7. Navigate to the arena. Player 2 should automatically pick Fox.

 8. Start training!
    

