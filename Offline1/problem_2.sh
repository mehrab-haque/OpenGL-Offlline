g++ -c Sphere.cpp -o Sphere.o -lglut -lGLU -lGL
g++ -c Cubesphere.cpp -o Cubesphere.o -lglut -lGLU -lGL

g++ -o demo problem_2.cpp Sphere.o Cubesphere.o -lglut -lGLU -lGL

./demo