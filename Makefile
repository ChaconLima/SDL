SRC_DIR=source/
CPP_FILES=${SRC_DIR}*.cpp
INCLUDE=include
BINARY=build/prog.exe

all: modelo

run:run_modelo

modelo:
	g++ -std=c++17 ${CPP_FILES} -o ${BINARY} -I${INCLUDE} -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

run_modelo: modelo
	modelo
clean: 
	rm ${SRC_DIR}*.o