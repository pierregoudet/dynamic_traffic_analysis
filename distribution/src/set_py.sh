swig -python -o main_wrap.c main.i
gcc -I/usr/include/python2.7 -c main_wrap.c
gcc -c main.c
gcc -shared main.o main_wrap.o -o _main.so