./bin/Linux/main: src/main.cpp src/camera.cpp src/glad.c src/textrendering.cpp src/matrices.cpp include/utils.h include/dejavufont.h
	mkdir -p bin/Linux
	g++ -std=c++11 -Wall -Wno-unused-function -g -I ./include/ -o ./bin/Linux/main \
		src/main.cpp src/glad.c src/textrendering.cpp src/camera.cpp src/matrices.cpp ./lib-linux/libglfw3.a \
		-lrt -lm -ldl -lX11 -lpthread -lXrandr -lXinerama -lXxf86vm -lXcursor

.PHONY: clean run

clean:
	rm -f bin/Linux/main

run: ./bin/Linux/main
	cd bin/Linux && ./main
