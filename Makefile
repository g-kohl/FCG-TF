./bin/Linux/main: src/*.cpp include/*.h include/*.hpp
	mkdir -p bin/Linux
	g++ -std=c++11 -Wall -Wno-unused-function -g -I ./include/ -o ./bin/Linux/main src/main.cpp src/glad.c src/textrendering.cpp src/tiny_obj_loader.cpp \
	src/stb_image.cpp src/camera.cpp src/object_model.cpp src/callbacks.cpp src/gpu_functions.cpp src/show_text.cpp src/animation_functions.cpp \
	./lib-linux/libglfw3.a -lrt -lm -ldl -lX11 -lpthread -lXrandr -lXinerama -lXxf86vm -lXcursor

.PHONY: clean run
clean:
	rm -f bin/Linux/main

run: ./bin/Linux/main
	cd bin/Linux && ./main
