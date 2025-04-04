@echo off

gcc -c ./src/test/main.c -I ./include
gcc -o ./bin/b32.exe main.o -L ./lib -lbase32
gcc -o ./bin/_b32.exe main.o -L ./lib -lbase32lib

del *.o