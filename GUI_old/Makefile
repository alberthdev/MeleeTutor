all: helloworld liboverlay.so liboverlay2.so

helloworld: helloworld.o
	/usr/bin/c++ -g  -I/media/MyPassport/SDL2/include -std=c++11 -Wall -Wextra -std=c++11 -O3 -DNDEBUG  -L/media/MyPassport/SDL2/lib -Wl,-rpath,/media/MyPassport/SDL2/lib -Wl,--enable-new-dtags -lSDL2 -Wl,--no-undefined -lm -ldl -lpthread -lrt helloworld.o  -o helloworld -L. -lnanogui -lGL -lXxf86vm -lXrandr -lXinerama -lXcursor -lXi -lX11 -lpthread -ldl -lrt -lSDL2

helloworld.o: helloworld.cpp
	/usr/bin/c++ -g  -DEIGEN_DONT_ALIGN -DNANOGUI_LINUX -DNANOGUI_SHARED -DNANOVG_GL2_IMPLEMENTATION -I/media/MyPassport/SDL2/include -std=c++11 -Wall -Wextra -std=c++11 -O3 -DNDEBUG -I/media/MyPassport/nanogui-sdl/ext -I/media/MyPassport/nanogui-sdl/ext/eigen -I/media/MyPassport/nanogui-sdl/include -I/media/MyPassport/nanogui-sdl -I/media/MyPassport/nanogui-sdl/build    -o helloworld.o -c helloworld.cpp

liboverlay.so: oglinject.c
	gcc -g -o liboverlay.so -shared -fPIC oglinject.c -lGL -I/usr/include/freetype2 -I/media/MyPassport/ftgl/include -L/media/MyPassport/ftgl/lib -lftgl

liboverlay2.so: oglinject2.c
	gcc -g -o liboverlay2.so -shared -fPIC oglinject2.c -DTARGET_UNIX -lGL

liboverlay3.so: oglinject3_fps.c
	gcc -g -o liboverlay3.so -shared -fPIC oglinject3_fps.c -lGL
