CC = clang
CFLAGS = -I./include -D_CRT_SECURE_NO_WARNINGS

SRC = $(wildcard src/*.c) 
OBJ = $(SRC:src/%.c=obj/%.o)  
OUT = bin/shell.exe


$(OUT): $(OBJ)
	@if not exist bin mkdir bin
	@if not exist obj mkdir obj
	$(CC) -o $(OUT) $(OBJ)


obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OUT)
