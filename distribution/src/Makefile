TEXT := >>>>> File Compiled:

CC=gcc
CFLAGS=-Wall -Wextra -g 
LDFLAGS=-lm 

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,$(OBJ_PATH)/%.o,$(SRCS))
OBJ_PATH=obj
BIN_PATH=../bin
PY_PATH=/usr/include/python2.7

all: dir main

dir:
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(BIN_PATH)

python:
	@swig -python  main.i
	@$(CC) -O2 -fPIC $(CFLAGS) -I$(PY_PATH) -c *.c
	@$(CC) -shared $(CFLAGS) *.o -o _main.so
	@rm -f *.o

main: $(OBJS)
	@$(CC) $(CFLAGS) $^ -o ./$(BIN_PATH)/$@ $(LDFLAGS) 


$(OBJ_PATH)/%.o: %.c
	@ $(CC) $(CFLAGS)  -ggdb -g -c $< -o $@ $(LDFLAGS) 
	$(info $(TEXT)$<)		
	@rm -f *.o

clean:
	@rm -f $(OBJ_PATH)/*.o
	@rm  _* *_wrap*
	@rm main.py*