CC ?= gcc
CFLAGS = -O3 -Wall -Wextra -std=c11

BIN = kmp_merge

SRC = src/kmp.c src/kmp_merge.c

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

test: $(BIN)
	tests/test_bytes.sh

clean:
	rm -f $(BIN)
