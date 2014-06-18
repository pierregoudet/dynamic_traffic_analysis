TEXT := >>>>> File Compiled: 

CC=gcc
CFLAGS=-Wall -Wextra -g
LDFLAGS=-lm

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,$(OBJ_PATH)/%.o,$(SRCS))
OBJ_PATH=obj
BIN_PATH=../bin

all: dir main
	

dir:
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(BIN_PATH)

main: $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $(BIN_PATH)/$@ $(LDFLAGS)
	
$(OBJ_PATH)/%.o: %.c
	@ $(CC) $(CFLAGS) -ggdb -g -c $< -o $@ $(LDFLAGS)
	
	@rm -f *.o
	$(info $(TEXT)$<)

clean:
	rm -f $(OBJ_PATH)/*.o