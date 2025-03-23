CC = clang
CFLAGS = -I./include -D_CRT_SECURE_NO_WARNINGS

SRC = $(wildcard src/*.c)  
OUT = bin/shell.exe  

$(OUT): $(SRC)
	@if not exist bin mkdir bin
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

clean:
	rm -f $(OUT)
