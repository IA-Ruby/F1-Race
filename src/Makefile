all: compile link execute

compile: 
	g++ -c main.cpp -I"..\include" -DSFML_STATIC

link: 
	g++ main.o -o main -L"..\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main

execute:
	./main

clean: 
	rm -f main *.o
