@echo off
echo wait...
g++ -c src/liep.cpp -o obj/liep.o -Ilib
g++ -c main.cpp -o main.o -Ilib
g++ obj/liep.o main.o -o main.exe
echo done!